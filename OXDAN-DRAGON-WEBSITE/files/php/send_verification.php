<?php

session_start();
ini_set('session.cookie_secure', 1);
ini_set('session.cookie_httponly', 1);
ini_set('session.use_strict_mode', 1);

header('Content-Type: application/json');

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method']);
    exit;
}

$input = json_decode(file_get_contents('php://input'), true);

if (empty($_SESSION['csrf_token']) || empty($input['csrf_token']) || 
    !hash_equals($_SESSION['csrf_token'], $input['csrf_token'])) {
    echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token']);
    exit;
}

$identifier = trim($input['email'] ?? '');

if (empty($identifier)) {
    echo json_encode(['status' => 'error', 'message' => 'Email is required']);
    exit;
}

if (strpos($identifier, '@') !== false) {
    $identifier = filter_var($identifier, FILTER_SANITIZE_EMAIL);
    if (!filter_var($identifier, FILTER_VALIDATE_EMAIL)) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid email format']);
        exit;
    }
} else {
    if (!preg_match('/^[a-zA-Z0-9_-]+$/', $identifier)) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid username format']);
        exit;
    }
}

$limitFile = __DIR__ . '/../../../rate_limits.json';
if (!file_exists($limitFile)) {
    file_put_contents($limitFile, json_encode([]));
}

$limits = json_decode(file_get_contents($limitFile), true) ?? [];
$ip = $_SERVER['REMOTE_ADDR'];
$now = time();
$section = 'password_reset_request';
$cooldown = 60;

if (!isset($limits[$ip])) {
    $limits[$ip] = ['last_request' => 0];
}

if (($now - $limits[$ip]['last_request']) < $cooldown) {
    echo json_encode(['status' => 'error', 'message' => 'Please wait before requesting another reset']);
    exit;
}

$limits[$ip]['last_request'] = $now;
file_put_contents($limitFile, json_encode($limits));

require __DIR__ . '/../resources/vendor/autoload.php';
use Aws\Ses\SesClient;
use Aws\Exception\AwsException;
use Dotenv\Dotenv;

$dotenv = Dotenv::createImmutable(__DIR__ . '/../../../');
$dotenv->load();

include __DIR__ . '/../php/database.php';

define('CODE_LENGTH', 6);

function generateCode($length = CODE_LENGTH) {
    $characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    $max = strlen($characters) - 1;
    $code = '';
    for ($i = 0; $i < $length; $i++) {
        $code .= $characters[random_int(0, $max)];
    }
    return $code;
}

function sendSesEmail($recipient, $source, $htmlBody, $textBody, $subject) {
    $SesClient = new SesClient([
        'version' => 'latest',
        'region'  => $_ENV['AWS_REGION_ACCESS_KEY'] ?? null,
        'credentials' => [
            'key'    => $_ENV['AWS_ID_ACCESS_KEY'] ?? null,
            'secret' => $_ENV['AWS_SECRET_ACCESS_KEY'] ?? null,
        ],
        'http' => ['verify' => 'cacert.pem'],
    ]);

    try {
        return $SesClient->sendEmail([
            'Destination' => ['ToAddresses' => [$recipient]],
            'ReplyToAddresses' => [$source],
            'Source' => $source,
            'Message' => [
                'Body' => [
                    'Html' => ['Charset' => 'UTF-8', 'Data' => $htmlBody],
                    'Text' => ['Charset' => 'UTF-8', 'Data' => $textBody]
                ],
                'Subject' => ['Charset' => 'UTF-8', 'Data' => $subject]
            ],
        ]);
    } catch (AwsException $e) {
        return false;
    }
}

try {
    $stmt = $pdo->prepare("SELECT username, email FROM users WHERE email = ? OR username = ?");
    $stmt->execute([$identifier, $identifier]);
    $user = $stmt->fetch();

    if (!$user) {
        echo json_encode(['status' => 'success', 'message' => 'If an account exists with that email, a reset code has been sent.']);
        exit;
    }

    $username = $user['username'];
    $email = $user['email'];
    $source = 'support@oxdan.com';
    $randomCode = generateCode(CODE_LENGTH);
    $subject = 'Oxdan Email Verification Code.';
    $plaintext_body = "Hi 😀 thanks a lot for your Register! Here is the new verification code to verify your email. $randomCode Thanks For Choosing Us! ❤️ Have fun and wonderful day!";
    $html_body = "<h1>Oxdan Email Verification Code. </h1><p>Hi, thanks a lot for your Register! Here is the new verification code to verify your email. $randomCode Thanks For Choosing Us! ❤️ Have fun and wonderful day! ⚠️ Warning! Do not share this code with anyone, this is only for email verification purposes.</p><h1> $randomCode</h1><p>ℹ️ If you didn't register, this means someone else have access or attempt to use your email, change password immediately and text us support@oxdan.com to remove suspicious login.</p>";

    $stmt = $pdo->prepare("UPDATE users SET verification_code = ? WHERE email = ?");
    $stmt->execute([$randomCode, $email]);

    if (!sendSesEmail($email, $source, $html_body, $plaintext_body, $subject)) {
        throw new Exception('Failed to send email');
    }

    $_SESSION['pending_verification'] = [
        'username' => $username,
        'email' => $email,
        'created_at' => time()
    ];

    $_SESSION['password_reset'] = [
        'email' => $email,
        'username' => $username,
        'verification_code' => $randomCode,
        'expiry' => time() + 3600,
        'type' => 'password_reset',
        'csrf_token' => bin2hex(random_bytes(32))
    ];
    $_SESSION['pending_ip'] = $_SERVER['REMOTE_ADDR'];
    $_SESSION['pending_expiry'] = time() + 3600;

    echo json_encode(['status' => 'success', 'message' => 'Password reset code sent successfully']);

} catch (Exception $e) {
    echo json_encode(['status' => 'error', 'message' => 'Failed to process reset request']);
}
?>