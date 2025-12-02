<?php

session_start();
header('Content-Type: application/json');

require __DIR__ . '/../resources/vendor/autoload.php';
use Aws\Ses\SesClient;
use Aws\Exception\AwsException;
use Dotenv\Dotenv;

$dotenv = Dotenv::createImmutable(__DIR__ . '/../../../');
$dotenv->load();

if (!isset($_SESSION['verified_password_reset'])) {
    if (!isset($_SESSION['user_id'])) {
        echo json_encode(['status' => 'error', 'message' => 'Not authenticated.']);
        exit;
    }
}

function getUserIP() {
    if (!empty($_SERVER['HTTP_CLIENT_IP'])) return $_SERVER['HTTP_CLIENT_IP'];
    if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) return explode(',', $_SERVER['HTTP_X_FORWARDED_FOR'])[0];
    return $_SERVER['REMOTE_ADDR'];
}

function getGeoLocation($ip) {
    $api_url = "http://ip-api.com/json/$ip?fields=country,regionName,city,proxy,status,message";
    $response = @file_get_contents($api_url);
    if ($response) {
        $data = json_decode($response, true);
        if ($data && $data['status'] === 'success') {
            return [
                'location' => "{$data['city']}, {$data['regionName']}, {$data['country']}",
                'vpn' => $data['proxy'] ? 'Detected' : 'Not detected'
            ];
        }
    }
    return ['location' => 'Unknown', 'vpn' => 'Unknown'];
}

function getRandomEmail($emails) {
    return $emails[array_rand($emails)];
}

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method.']);
    exit;
}

$data = json_decode(file_get_contents('php://input'), true);

if (!$data) {
    echo json_encode(['status' => 'error', 'message' => 'No data received']);
    exit;
}

if (empty($data['recaptcha_response'])) {
    echo json_encode(['status' => 'error', 'message' => 'reCAPTCHA verification required.']);
    exit;
}

function verifyRecaptcha($recaptchaResponse) {
    $secret_key = $_ENV['RECAPTCHA_SECRET_ACCESS_KEY'] ?? null;
    
    if (!$secret_key) {
        return false;
    }
    
    $url = 'https://www.google.com/recaptcha/api/siteverify';
    
    $data = [
        'secret' => $secret_key,
        'response' => $recaptchaResponse
    ];
    
    $options = [
        'http' => [
            'header' => "Content-type: application/x-www-form-urlencoded\r\n",
            'method' => 'POST',
            'content' => http_build_query($data)
        ]
    ];
    
    $context = stream_context_create($options);
    $result = file_get_contents($url, false, $context);
    $response = json_decode($result);
    
    return $response->success;
}

$recaptchaSuccess = verifyRecaptcha($data['recaptcha_response']);
if (!$recaptchaSuccess) {
    echo json_encode(['status' => 'error', 'message' => 'reCAPTCHA verification failed.']);
    exit;
}

if (empty($_SESSION['csrf_token']) || empty($data['csrf_token']) || 
    !hash_equals($_SESSION['csrf_token'], $data['csrf_token'])) {
    echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token.']);
    exit;
}

$newpassword = $data['newpassword'] ?? null;
$deviceInfo = $data['deviceInfo'] ?? [];
$userAgent = $deviceInfo['userAgent'] ?? ($_SERVER['HTTP_USER_AGENT'] ?? 'Unknown');
$screenResolution = $deviceInfo['screenResolution'] ?? 'Unknown';
$password = $data['password'] ?? null;

if (!$newpassword) {
    echo json_encode(['status' => 'error', 'message' => 'New password is required.']);
    exit;
}

if (strlen($newpassword) < 8) {
    echo json_encode(['status' => 'error', 'message' => 'New password must be at least 8 characters long.']);
    exit;
}

require __DIR__ . '/../php/database.php';

if (isset($_SESSION['verified_password_reset'])) {
    $resetData = $_SESSION['verified_password_reset'];
    
    if (time() > $resetData['expiry']) {
        unset($_SESSION['verified_password_reset']);
        echo json_encode(['status' => 'error', 'message' => 'Reset session expired.']);
        exit;
    }
    
    $email = $resetData['email'];
    $username = $resetData['username'];
    
    $stmt = $pdo->prepare("SELECT * FROM users WHERE email = ?");
    $stmt->execute([$email]);
    $user = $stmt->fetch();
    
    if (!$user) {
        echo json_encode(['status' => 'error', 'message' => 'User not found.']);
        exit;
    }
    
    $flow_type = 'reset';
    
} else {
    if (!$password) {
        echo json_encode(['status' => 'error', 'message' => 'Current password is required.']);
        exit;
    }
    
    $stmt = $pdo->prepare("SELECT * FROM users WHERE id = ?");
    $stmt->execute([$_SESSION['user_id']]);
    $user = $stmt->fetch();

    if (!$user) {
        echo json_encode(['status' => 'error', 'message' => 'User not found.']);
        exit;
    }

    if (!password_verify($password, $user['password_hash'])) {
        echo json_encode(['status' => 'error', 'message' => 'Current password is incorrect.']);
        exit;
    }
    
    $flow_type = 'change';
}

if (password_verify($newpassword, $user['password_hash'])) {
    echo json_encode(['status' => 'error', 'message' => 'New password cannot be the same as current password.']);
    exit;
}

$newPasswordHash = password_hash($newpassword, PASSWORD_DEFAULT);
$stmt = $pdo->prepare("UPDATE users SET password_hash = ? WHERE id = ?");
$stmt->execute([$newPasswordHash, $user['id']]);

if ($flow_type === 'change') {
    session_regenerate_id(true);
    $_SESSION['last_activity'] = time();
}

if ($flow_type === 'reset') {
    unset($_SESSION['verified_password_reset']);
    if (isset($_SESSION['password_reset'])) {
        unset($_SESSION['password_reset']);
    }
    
    session_regenerate_id(true);
    $_SESSION['user_id'] = $user['id'];
    $_SESSION['username'] = $user['username'];
    $_SESSION['email'] = $user['email'];
    $_SESSION['ip'] = $_SERVER['REMOTE_ADDR'];
    $_SESSION['ua'] = $_SERVER['HTTP_USER_AGENT'] ?? '';
    $_SESSION['login_time'] = time();
    $_SESSION['last_activity'] = time();
}

$suspicious_ip = getUserIP();
$geo = getGeoLocation($suspicious_ip);
$suspicious_location = $geo['location'];
$vpn_status = $geo['vpn'];

try {
    $SesClient = new SesClient([
        'version' => 'latest',
        'region'  => $_ENV['AWS_REGION_ACCESS_KEY'],
        'credentials' => [
            'key'    => $_ENV['AWS_ID_ACCESS_KEY'] ?? null,
            'secret' => $_ENV['AWS_SECRET_ACCESS_KEY'] ?? null,
        ],
        'http' => ['verify' => 'cacert.pem'],
    ]);

    $sender_email = getRandomEmail(["support@oxdan.com"]);
    $action = ($flow_type === 'reset') ? 'reset' : 'changed';
    $subject = "Oxdan Email ⚠️ Password $action Notification.";
    
    $plaintext_body = "Hi, the password for your account {$user['username']} has been $action.
    IP: $suspicious_ip
    Location: $suspicious_location
    VPN: $vpn_status
    Device: $userAgent
    Screen: $screenResolution";

    $html_body = "
    <h1>Oxdan Email ⚠️ Password $action Notification.</h1>
    <p>Hi, the password for your account <b>{$user['username']}</b> has been successfully $action.</p>
    <ul>
    <li><b>IP:</b> $suspicious_ip</li>
    <li><b>Location:</b> $suspicious_location</li>
    <li><b>VPN:</b> $vpn_status</li>
    <li><b>Device:</b> $userAgent</li>
    <li><b>Screen:</b> $screenResolution</li>
    </ul>
    <p>ℹ️ If it's not you, this means someone else have access or attempt to use your account, change password immediately and text us support@oxdan.com to remove suspicious login.</p>";

    $SesClient->sendEmail([
        'Destination' => ['ToAddresses' => [$user['email']]],
        'ReplyToAddresses' => [$sender_email],
        'Source' => $sender_email,
        'Message' => [
            'Body' => [
                'Html' => ['Charset' => 'UTF-8', 'Data' => $html_body],
                'Text' => ['Charset' => 'UTF-8', 'Data' => $plaintext_body],
            ],
            'Subject' => ['Charset' => 'UTF-8', 'Data' => $subject],
        ],
    ]);
} catch (AwsException $e) {
    
}

echo json_encode([
    'status' => 'success', 
    'username' => $user['username'],
    'flow' => $flow_type
]);
exit;
?>