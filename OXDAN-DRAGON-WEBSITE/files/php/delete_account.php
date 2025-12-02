<?php
session_start();

require __DIR__ . '/../resources/vendor/autoload.php';
use Dotenv\Dotenv;

header('Content-Type: application/json');

if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method.']);
    exit;
}

if (empty($_SERVER['HTTP_X_REQUESTED_WITH']) || strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) !== 'xmlhttprequest') {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request.']);
    exit;
}

try {
    $dotenv = Dotenv::createImmutable(__DIR__ . '/../../../');
    $dotenv->load();

    $encryptionKey = $_ENV['ENCRYPTION_KEY'] ?? null;
    if (!$encryptionKey) {
        throw new Exception('Encryption key not configured');
    }

    $pdo = new PDO($_ENV['DB_DSN']);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if (!isset($_SESSION['user_id']) || !isset($_SESSION['username'])) {
        echo json_encode(['status' => 'error', 'message' => 'Not logged in.']);
        exit;
    }

    $input = json_decode(file_get_contents('php://input'), true);
    
    if (empty($_SESSION['csrf_token']) || empty($input['csrf_token']) || 
        !hash_equals($_SESSION['csrf_token'], $input['csrf_token'])) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token.']);
        exit;
    }

    $isGoogleUser = ($_SESSION['oauth_provider'] ?? '') === 'google';
    
    $user_id = $_SESSION['user_id'];
    
    $stmt = $pdo->prepare("SELECT password_hash, email, oauth_provider FROM users WHERE id = ?");
    $stmt->execute([$user_id]);
    $user = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$user) {
        echo json_encode(['status' => 'error', 'message' => 'User not found.']);
        exit;
    }

    if (!$isGoogleUser) {
        if (empty($input['password'])) {
            echo json_encode(['status' => 'error', 'message' => 'Password confirmation required.']);
            exit;
        }

        $password = trim($input['password']);
        if (empty($password)) {
            echo json_encode(['status' => 'error', 'message' => 'Password cannot be empty.']);
            exit;
        }

        if (!password_verify($input['password'], $user['password_hash'])) {
            echo json_encode(['status' => 'error', 'message' => 'Invalid password.']);
            exit;
        }
    } else {
        if (($user['oauth_provider'] ?? '') !== 'google') {
            echo json_encode(['status' => 'error', 'message' => 'Account type mismatch.']);
            exit;
        }
    }

    $stmt = $pdo->prepare("DELETE FROM users WHERE id = ?");
    $stmt->execute([$user_id]);
    $deletedCount = $stmt->rowCount();

    if ($deletedCount === 0) {
        echo json_encode(['status' => 'error', 'message' => 'User not found or already deleted.']);
        exit;
    }

    echo json_encode([
        'status' => 'success', 
        'message' => 'Account deleted successfully.',
        'redirect' => '/start'
    ]);
    
    session_destroy();

} catch (Exception $e) {
    echo json_encode([
        'status' => 'error', 
        'message' => 'Deletion failed: ' . $e->getMessage()
    ]);
}
?>