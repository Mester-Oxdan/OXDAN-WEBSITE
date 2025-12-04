<?php

session_set_cookie_params([
    'lifetime' => 0,
    'path' => '/',
    'secure' => true,
    'httponly' => true,
    'samesite' => 'Lax'
]);

if (session_status() === PHP_SESSION_NONE) {
    session_start();
    
    if (empty($_SESSION['initialized'])) {
        session_regenerate_id(true);
        $_SESSION['initialized'] = true;
        $_SESSION['created_time'] = time();
    }
} else {
    session_start();
}

if (empty($_SESSION['oauth_state'])) {
    $_SESSION['oauth_state'] = bin2hex(random_bytes(16));
}

include __DIR__ . '/crypto_functions.php';
include __DIR__ . '/database.php';
require __DIR__ . '/../files/resources/vendor/autoload.php';

use Aws\Ses\SesClient;
use Aws\Exception\AwsException;
use Dotenv\Dotenv;

$dotenv = Dotenv::createImmutable(__DIR__ . '/../');
$dotenv->load();

function failLogin(&$limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section) {
    if (!isset($limits[$ip]['attempts'][$section]) || !is_array($limits[$ip]['attempts'][$section])) {
        $limits[$ip]['attempts'][$section] = [];
    }

    $limits[$ip]['attempts'][$section] = array_filter($limits[$ip]['attempts'][$section], fn($ts) => $ts > $now - 3600);
    $limits[$ip]['attempts'][$section][] = $now;

    if (count($limits[$ip]['attempts'][$section]) >= $threshold) {
        $limits[$ip]['stage'][$section] = min(($limits[$ip]['stage'][$section] ?? 0) + 1, count($cooldowns) - 1);
        $limits[$ip]['blocked_until'][$section] = $now + $cooldowns[$limits[$ip]['stage'][$section]];
        $limits[$ip]['attempts'][$section] = [];
    }

    file_put_contents($limitFile, json_encode($limits));

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] > $now) {
        echo json_encode([
            'status' => 'error',
            'message' => "Too many attempts for $section" . '_' . ($limits[$ip]['stage'][$section] + 1)
        ]);
    } else {
        echo json_encode([
            'status' => 'error',
            'message' => 'Invalid credentials.'
        ]);
    }
    exit;
}

function getRandomEmail($emails) {
    $randomIndex = array_rand($emails);
    return $emails[$randomIndex];
}

function validateSession() {
    if (!isset($_SESSION['user_id']) || 
        !isset($_SESSION['ip']) || 
        !isset($_SESSION['ua']) ||
        !isset($_SESSION['login_time'])) {
        return false;
    }
    
    if ($_SESSION['ip'] !== $_SERVER['REMOTE_ADDR']) {
        return false;
    }
    
    if ($_SESSION['ua'] !== ($_SERVER['HTTP_USER_AGENT'] ?? '')) {
        return false;
    }
    
    $_SESSION['last_activity'] = time();
    
    return true;
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

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = json_decode(file_get_contents('php://input'), true);

    if (empty($data['recaptcha_response'])) {
        echo json_encode(['status' => 'error', 'message' => 'reCAPTCHA verification required.']);
        exit;
    }
    
    $recaptchaSuccess = verifyRecaptcha($data['recaptcha_response']);
    if (!$recaptchaSuccess) {
        echo json_encode(['status' => 'error', 'message' => 'reCAPTCHA verification failed.']);
        exit;
    }

    $deviceInfo = $data['deviceInfo'] ?? [];
    $userAgent = $deviceInfo['userAgent'] ?? ($_SERVER['HTTP_USER_AGENT'] ?? 'Unknown');
    $screenResolution = $deviceInfo['screenResolution'] ?? 'Unknown';
    $usernameOrEmail = trim($data['usernameOrEmail'] ?? '');
    $password = $data['password'] ?? '';

    if (empty($_SESSION['csrf_token']) || empty($data['csrf_token']) || 
        !hash_equals($_SESSION['csrf_token'], $data['csrf_token'])) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token.']);
        exit;
    }

    if (empty($usernameOrEmail) || empty($password)) {
        echo json_encode(['status' => 'error', 'message' => 'All fields are required.']);
        exit;
    }

    if (strpos($usernameOrEmail, '@') !== false) {
        $usernameOrEmail = filter_var($usernameOrEmail, FILTER_SANITIZE_EMAIL);
        if (!filter_var($usernameOrEmail, FILTER_VALIDATE_EMAIL)) {
            echo json_encode(['status' => 'error', 'message' => 'Invalid email format.']);
            exit;
        }
    } else {
        if (!preg_match('/^[a-zA-Z0-9_-]+$/', $usernameOrEmail)) {
            echo json_encode(['status' => 'error', 'message' => 'Invalid username format.']);
            exit;
        }
    }
    
    $ip = $_SERVER['REMOTE_ADDR'];
    $limitFile = __DIR__ . '/../rate_limits.json';

    if (!file_exists($limitFile)) {
        file_put_contents($limitFile, json_encode([]));
    }

    $limits = json_decode(file_get_contents($limitFile), true) ?? [];
    if (!isset($limits[$ip])) {
        $limits[$ip] = [
            'attempts' => [],
            'stage' => [],
            'blocked_until' => []
        ];
    }
    
    $now = time();
    $cooldowns = [60, 300, 600, 900];
    $threshold = 5;
    $section = 'login';

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] <= $now) {
        $limits[$ip]['attempts'][$section] = [];
        $limits[$ip]['stage'][$section] = 0;
        $limits[$ip]['blocked_until'][$section] = 0;
    }

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] > $now) {
        $stage = $limits[$ip]['stage'][$section] ?? 0;
        echo json_encode([
            'status' => 'error',
            'message' => 'Too many attempts for login_' . ($stage + 1)
        ]);
        exit;
    }
    
    $stmt = $pdo->prepare("SELECT * FROM users WHERE username = ? OR email = ?");
    $stmt->execute([$usernameOrEmail, $usernameOrEmail]);
    $user = $stmt->fetch();
    
    if (!$user) {
        failLogin($limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section);
    }

    if (isset($user['verified']) && (int)$user['verified'] !== 1) {
        echo json_encode([
            'status' => 'error',
            'message' => 'Not verified user.'
        ]);
        exit;
    }
    
    $needed_email = $user['email'];

    if (!password_verify($password, $user['password_hash'])) {
        failLogin($limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section);
    }
    
    $username = $user['username'];
    
    if (isset($limits[$ip]['attempts'][$section])) {
        $limits[$ip]['attempts'][$section] = [];
        $limits[$ip]['stage'][$section] = 0;
        $limits[$ip]['blocked_until'][$section] = 0;
        file_put_contents($limitFile, json_encode($limits));
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
                $vpn_status = $data['proxy'] ? 'Detected' : 'Not detected';
                return [
                    'location' => "{$data['city']}, {$data['regionName']}, {$data['country']}",
                    'vpn' => $vpn_status
                ];
            }
        }
        return ['location' => 'Unknown', 'vpn' => 'Unknown'];
    }
    
    $suspicious_ip = getUserIP();
    $suspicious_data = getGeoLocation($suspicious_ip);
    $suspicious_location = $suspicious_data['location'];
    $vpn_status = $suspicious_data['vpn'];
    
    $emails = ["support@oxdan.com"];

    $SesClient = new SesClient([
        'version' => 'latest',
        'region'  => $_ENV['AWS_REGION_ACCESS_KEY'] ?? null,
        'credentials' => [
            'key'    => $_ENV['AWS_ID_ACCESS_KEY'] ?? null,
            'secret' => $_ENV['AWS_SECRET_ACCESS_KEY'] ?? null,
        ],
        'http' => ['verify' => 'cacert.pem'],
    ]);
    
    $sender_email = getRandomEmail($emails);
    $subject = 'Oxdan Email ⚠️ Warning Notification.';
    $plaintext_body = "Hi, someone just logged into your account $username.
    IP: $suspicious_ip
    Location: $suspicious_location
    VPN: $vpn_status
    Device: $userAgent
    Screen: $screenResolution";
    
    $html_body = "
    <h1>Oxdan Email ⚠️ Warning Notification.</h1>
    <p>Hi, someone just logged into your account <b>$username</b>.</p>
    <ul>
        <li><b>IP:</b> $suspicious_ip</li>
        <li><b>Location:</b> $suspicious_location</li>
        <li><b>VPN:</b> $vpn_status</li>
        <li><b>Device:</b> $userAgent</li>
        <li><b>Screen:</b> $screenResolution</li>
    </ul>
    <p>ℹ️ If it's not you, someone else may have accessed your account. Change your password immediately and contact support@oxdan.com.</p>";
    
    try {
        $SesClient->sendEmail([
            'Destination' => ['ToAddresses' => [$needed_email]],
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

        session_regenerate_id(true);

        $_SESSION['pending_verification'] = [
            'username' => $username,
            'email' => $user['email'],
            'created_at' => time()
        ];

        $_SESSION['user_id'] = $user['id'];
        $_SESSION['username'] = $username;
        $_SESSION['email'] = $user['email'];
        $_SESSION['ip'] = $_SERVER['REMOTE_ADDR'];
        $_SESSION['ua'] = $_SERVER['HTTP_USER_AGENT'] ?? '';
        $_SESSION['login_time'] = time();
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
        $_SESSION['oauth_state'] = bin2hex(random_bytes(16));
        $_SESSION['login_method'] = 'normal';
        $_SESSION['pending_ip'] = $_SERVER['REMOTE_ADDR'];
        $_SESSION['pending_expiry'] = time() + 3600;
        
        echo json_encode(['status' => 'success', 'username' => $username]);
    } catch (AwsException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Email notification failed.']);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method.']);
}
?>
