<?php

session_start();

header('Content-Type: application/json');

$input = json_decode(file_get_contents('php://input'), true);

$type = $input['type'] ?? 'registration';

if ($type === 'password_reset') {
    if (!isset($_SESSION['password_reset'])) {
        echo json_encode(['status' => 'error', 'message' => 'Session expired. Please restart registration.']);
        exit;
    }
    $resetData = $_SESSION['password_reset'];
    $email = $resetData['email'];
    $username = $resetData['username'];
    
} else {
    if (!isset($_SESSION['pending_verification'])) {
        echo json_encode(['status' => 'error', 'message' => 'Session expired. Please restart registration.']);
        exit;
    }
    $pendingData = $_SESSION['pending_verification'];
    $email = $pendingData['email'];
    $username = $pendingData['username'];
}

require __DIR__ . '/../files/resources/vendor/autoload.php';
use Aws\Ses\SesClient;
use Aws\Exception\AwsException;
use Dotenv\Dotenv;

$dotenv = Dotenv::createImmutable(__DIR__ . '/../../../');
$dotenv->load();

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

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request']);
    exit;
}

if (empty($_SESSION['csrf_token']) || empty($input['csrf_token']) || 
    !hash_equals($_SESSION['csrf_token'], $input['csrf_token'])) {
    echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token.']);
    exit;
}

if ($type === 'password_reset') {
    if (isset($_SESSION['password_reset']['expiry']) && time() > $_SESSION['password_reset']['expiry']) {
        unset($_SESSION['password_reset']);
        echo json_encode(['status' => 'error', 'message' => 'Session expired. Please restart registration.']);
        exit;
    }
} else {
    if (isset($_SESSION['pending_expiry']) && time() > $_SESSION['pending_expiry']) {
        unset($_SESSION['pending_verification']);
        unset($_SESSION['pending_expiry']);
        echo json_encode(['status' => 'error', 'message' => 'Session expired. Please restart registration.']);
        exit;
    }
}

$randomCode = generateCode(CODE_LENGTH);

if ($type === 'password_reset') {
    $_SESSION['password_reset']['verification_code'] = $randomCode;
    $_SESSION['password_reset']['expiry'] = time() + 3600;
} else {
    $_SESSION['pending_verification']['verification_code'] = $randomCode;
    $_SESSION['pending_verification']['created_at'] = time();
    $_SESSION['pending_expiry'] = time() + 3600;
}

$subject = 'Oxdan Email Verification Code.';
$plaintext_body = "Hi 😀 thanks a lot for your Register! Here is the new verification code to verify your email. $randomCode Thanks For Choosing Us! ❤️ Have fun and wonderful day!";
$html_body = "<h1>Oxdan Email Verification Code. </h1><p>Hi, thanks a lot for your Register! Here is the new verification code to verify your email. $randomCode Thanks For Choosing Us! ❤️ Have fun and wonderful day! ⚠️ Warning! Do not share this code with anyone, this is only for email verification purposes.</p><h1> $randomCode</h1><p>ℹ️ If you didn't register, this means someone else have access or attempt to use your email, change password immediately and text us support@oxdan.com to remove suspicious login.</p>";
$source = 'support@oxdan.com';

if (!sendSesEmail($email, $source, $html_body, $plaintext_body, $subject)) {
    echo json_encode(['status' => 'error', 'message' => 'Email sending failed. Check server logs.']);
    exit;
}

echo json_encode(['status' => 'success', 'message' => 'New verification code sent!']);
exit;

?>
