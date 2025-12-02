<?php
session_start();
header('Content-Type: application/json');

if (empty($_SESSION['csrf_token']) || empty($_POST['csrf_token']) || 
    !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
    echo json_encode(['status'=>'fail','message'=>'Invalid CSRF token.']);
    exit;
}

include __DIR__ . '/../php/database.php';

function sanitizeInput($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data, ENT_QUOTES | ENT_HTML5, 'UTF-8');
    return $data;
}

$username = sanitizeInput($_POST['username'] ?? '');
$comment = sanitizeInput($_POST['comment'] ?? '');

if (empty($username) || empty($comment)) {
    echo json_encode([
        'status' => 'fail',
        'message' => 'Username and comment are required.'
    ]);
    exit;
}

if (strlen($comment) > 500) {
    echo json_encode([
        'status' => 'fail', 
        'message' => 'Comment is too long. Maximum 500 characters allowed.'
    ]);
    exit;
}

try {
    $stmt = $pdo->prepare("INSERT INTO comments (username, comment) VALUES (?, ?)");
    $stmt->execute([$username, $comment]);

    echo json_encode([
        'status' => 'success',
        'message' => 'New comment saved successfully'
    ]);
} catch (PDOException $e) {
    echo json_encode([
        'status' => 'fail',
        'message' => 'Failed to save comment: ' . $e->getMessage()
    ]);
}
?>