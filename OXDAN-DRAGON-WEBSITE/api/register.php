<?php

session_start();

if (empty($_SESSION['oauth_state'])) {
    $_SESSION['oauth_state'] = bin2hex(random_bytes(16));
}

include __DIR__ . '/crypto_functions.php';
require __DIR__ . '/../files/resources/vendor/autoload.php';
include __DIR__ . '/database.php';

use Aws\Ses\SesClient;
use Aws\Exception\AwsException;
use Dotenv\Dotenv;

$dotenv = Dotenv::createImmutable(__DIR__ . '/../../../');
$dotenv->load();

$oauth_state = $_SESSION['oauth_state'] ?? '';

function generateCode($length = 6) {
    $characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    $charactersLength = strlen($characters);
    $code = '';
    for ($i = 0; $i < $length; $i++) {
        $code .= $characters[rand(0, $charactersLength - 1)];
    }
    return $code;
}

function getRandomEmail($emails) {
    return $emails[array_rand($emails)];
}

function verifyRecaptcha($recaptchaResponse) {
    $secret_key = $_ENV['RECAPTCHA_SECRET_ACCESS_KEY'] ?? null;
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
    $data_2 = json_decode(file_get_contents('php://input'), true);

    if (empty($data_2['recaptcha_response'])) {
        echo json_encode(['status' => 'error', 'message' => 'reCAPTCHA verification required.']);
        exit;
    }
    
    $recaptchaSuccess = verifyRecaptcha($data_2['recaptcha_response']);
    if (!$recaptchaSuccess) {
        echo json_encode(['status' => 'error', 'message' => 'reCAPTCHA verification failed.']);
        exit;
    }

    if (empty($_SESSION['csrf_token']) || empty($data_2['csrf_token']) || 
        !hash_equals($_SESSION['csrf_token'], $data_2['csrf_token'])) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token.']);
        exit;
    }

    $username_2 = trim($data_2['username'] ?? '');

    if (strpos($username_2, '@') !== false) {
        echo json_encode(['status' => 'error', 'message' => 'Username cannot contain "@" symbol.']);
        exit;
    }

    $email_2 = filter_var(trim($data_2['email'] ?? ''), FILTER_SANITIZE_EMAIL);
    $password_2 = $data_2['password'] ?? '';

    if (empty($username_2) || empty($email_2) || empty($password_2)) {
        echo json_encode(['status' => 'error', 'message' => 'All fields are required.']);
        exit;
    }

    if (!filter_var($email_2, FILTER_VALIDATE_EMAIL)) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid email format.']);
        exit;
    }

    if (!preg_match('/^[a-zA-Z0-9_-]+$/', $username_2)) {
        echo json_encode(['status' => 'error', 'message' => 'Username can only contain letters, numbers, underscores, and hyphens.']);
        exit;
    }

    if (strlen($username_2) < 3 || strlen($username_2) > 30) {
        echo json_encode(['status' => 'error', 'message' => 'Username must be between 3 and 30 characters.']);
        exit;
    }

    if (strlen($password_2) < 8) {
        echo json_encode(['status' => 'error', 'message' => 'Password must be at least 8 characters long.']);
        exit;
    }

    try {
        $checkStmt = $pdo->prepare("SELECT id, verified FROM users WHERE email = ? OR username = ?");
        $checkStmt->execute([$email_2, $username_2]);
        $existingUser = $checkStmt->fetch();
        
        if ($existingUser) {
            if ($existingUser['verified']) {
                echo json_encode(['status' => 'error', 'message' => 'Username or email already taken.']);
            }
        }
    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Database error during user check.']);
        exit;
    }

    $randomCode = generateCode();
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
    $subject = 'Oxdan Email Verification Code.';
    $plaintext_body = "Hi 😀 thanks a lot for your Register! Here is the verification code to verify your email. $randomCode Thanks For Choosing Us! ❤️ Have fun and wonderful day!";
    $html_body = "<h1>Oxdan Email Verification Code. </h1><p>Hi, thanks a lot for your Register! Here is the verification code to verify your email. $randomCode Thanks For Choosing Us! ❤️ Have fun and wonderful day! ⚠️ Warning! Do not share this code with anyone, this is only for email verification purposes.</p><h1> $randomCode</h1><p>ℹ️ If you didn't register, this means someone else have access or attempt to use your email, change password immediately and text us support@oxdan.com to remove suspicious login.</p>";

    try {
        $SesClient->sendEmail([
            'Destination' => ['ToAddresses' => [$email_2]],
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

        $passwordHash = password_hash($password_2, PASSWORD_DEFAULT);

        $_SESSION['pending_verification'] = [
            'username' => $username_2,
            'email' => $email_2,
            'verification_code' => $randomCode,
            'password_hash' => $passwordHash,
            'created_at' => time()
        ];
        
        $_SESSION['pending_expiry'] = time() + 3600;
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
        $_SESSION['pending_ip'] = $_SERVER['REMOTE_ADDR'];

        echo json_encode(['status' => 'success', 'message' => 'Email sent successfully.']);
        exit;

    } catch (AwsException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Email notification failed.']);
        exit;
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method.']);
    exit;
}
