<?php
ini_set('session.cookie_secure', 1);
ini_set('session.cookie_httponly', 1);
ini_set('session.use_strict_mode', 1);
ini_set('session.cookie_samesite', 'Lax');

if (session_status() === PHP_SESSION_ACTIVE && empty($_SESSION['oauth_state'])) {
    session_regenerate_id(true);
}

if (session_status() === PHP_SESSION_NONE) {
    session_start();
}

require __DIR__ . '/../files/resources/vendor/autoload.php';
use Dotenv\Dotenv;
use Google\Client;
use Google\Service\Oauth2;

$dotenv = Dotenv::createImmutable(__DIR__ . '/../../../');
$dotenv->load();

header('Content-Type: application/json');

$data = json_decode(file_get_contents('php://input'), true);
$token = $data['credential'] ?? null;
$received_state = $data['state'] ?? null;

if (!$token) {
    echo json_encode(['status' => 'error', 'message' => 'No token received']);
    exit;
}

if (empty($_SESSION['oauth_state']) || empty($received_state) || 
    !hash_equals($_SESSION['oauth_state'], $received_state)) {
    echo json_encode(['status' => 'error', 'message' => 'Invalid state parameter']);
    exit;
}

unset($_SESSION['oauth_state']);

$client_id = $_ENV['GOOGLE_CLIENT_ID_ACCESS_KEY'] ?? null;
$client_secret = $_ENV['GOOGLE_CLIENT_SECRET_ACCESS_KEY'] ?? null;
if (!$client_id || !$client_secret) {
    echo json_encode(['status' => 'error', 'message' => 'Google OAuth not configured']);
    exit;
}

try {
    $client = new Client();
    $client->setClientId($client_id);
    $client->setClientSecret($client_secret);

    $payload = $client->verifyIdToken($token);
    
    if (!$payload) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid token signature']);
        exit;
    }
    
    if ($payload['aud'] !== $client_id) {
        echo json_encode(['status' => 'error', 'message' => 'Token audience mismatch']);
        exit;
    }
    
    $valid_issuers = ['https://accounts.google.com', 'accounts.google.com'];
    if (!in_array($payload['iss'], $valid_issuers)) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid token issuer']);
        exit;
    }
    
    if (isset($payload['exp']) && $payload['exp'] < time()) {
        echo json_encode(['status' => 'error', 'message' => 'Token has expired']);
        exit;
    }
    
    if (empty($payload['email']) || empty($payload['sub'])) {
        echo json_encode(['status' => 'error', 'message' => 'Missing required token claims']);
        exit;
    }

    $email = $payload['email'];
    $name = $payload['name'] ?? 'Unknown';
    $username = explode("@", $email)[0];
    $google_id = $payload['sub'];

    include __DIR__ . '/database.php';

    $stmt = $pdo->prepare("SELECT * FROM users WHERE email = ? OR oauth_id = ?");
    $stmt->execute([$email, $google_id]);
    $existingUser = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($existingUser) {
        $user_id = $existingUser['id'];
        $username = $existingUser['username'];
        
        if (empty($existingUser['oauth_id'])) {
            $stmt = $pdo->prepare("UPDATE users SET oauth_provider = 'google', oauth_id = ? WHERE id = ?");
            $stmt->execute([$google_id, $user_id]);
        }
    } else {
        $stmt = $pdo->prepare("
            INSERT INTO users (username, email, password_hash, encryption_key, verified, oauth_provider, oauth_id) 
            VALUES (?, ?, NULL, NULL, 1, 'google', ?)
        ");
        $stmt->execute([$username, $email, $google_id]);
        $user_id = $pdo->lastInsertId();
    }

    session_regenerate_id(true);
    $_SESSION['user_id'] = $user_id;
    $_SESSION['username'] = $username;
    $_SESSION['email'] = $email;
    $_SESSION['ip'] = $_SERVER['REMOTE_ADDR'];
    $_SESSION['ua'] = $_SERVER['HTTP_USER_AGENT'] ?? '';
    $_SESSION['login_time'] = time();
    $_SESSION['last_activity'] = time();
    $_SESSION['oauth_provider'] = 'google';
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
    $_SESSION['login_method'] = 'google';

    echo json_encode(['status' => 'success', 'message' => 'Logged in successfully']);

} catch (Exception $e) {
    echo json_encode(['status' => 'error', 'message' => 'Login failed: ' . $e->getMessage()]);
}
?>
