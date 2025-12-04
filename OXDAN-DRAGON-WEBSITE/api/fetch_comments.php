<?php
header('Content-Type: application/json');
include __DIR__ . '/database.php';

function sanitizeOutput($data) {
    return htmlspecialchars($data, ENT_QUOTES | ENT_HTML5, 'UTF-8');
}

try {
    $stmt = $pdo->query("SELECT username, comment, timestamp FROM comments ORDER BY id DESC");
    $comments = $stmt->fetchAll(PDO::FETCH_ASSOC);
    
    $sanitizedComments = array_map(function($comment) {
        return [
            'username' => sanitizeOutput($comment['username']),
            'comment' => sanitizeOutput($comment['comment']),
            'timestamp' => $comment['timestamp']
        ];
    }, $comments);
    
    echo json_encode($sanitizedComments);
} catch (PDOException $e) {
    echo json_encode([
        'status' => 'fail',
        'message' => 'Failed to fetch comments: ' . $e->getMessage()
    ]);
}
?>
