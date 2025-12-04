<?php
session_start();

require __DIR__ . '/../database.php';

$targetDir = __DIR__ . "/uploads/";
$defaultImage = 'default.png';

if (!isset($_SESSION['username'])) {
    echo json_encode(['status' => 'error', 'message' => 'User not logged in']);
    exit;
}

$username = $_SESSION['username'];
$stmt = $pdo->prepare("SELECT avatar_filename FROM users WHERE username = ?");
$stmt->execute([$username]);
$user = $stmt->fetch(PDO::FETCH_ASSOC);

if ($user && !empty($user['avatar_filename']) && file_exists($targetDir . $user['avatar_filename'])) {
    $imagePath = $targetDir . $user['avatar_filename'];
} else {
    $imagePath = $targetDir . $defaultImage;
}

echo json_encode([
    'status' => 'success',
    'file' => $imagePath
]);

?>
