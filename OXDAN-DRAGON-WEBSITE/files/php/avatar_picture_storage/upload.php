<?php
session_start();

require __DIR__ . '/../database.php';

$targetDir = __DIR__ . "/../../php/avatar_picture_storage/uploads/";
$uploadOk = 1;

if (!isset($_SESSION['username'])) {
    echo json_encode(['success' => false, 'error' => 'User not logged in.']);
    exit;
}

$username = $_SESSION['username'];

if (!isset($_FILES["file"])) {
    echo json_encode(['success' => false, 'error' => 'No file uploaded.']);
    exit;
}

$check = getimagesize($_FILES["file"]["tmp_name"]);
if ($check === false) {
    echo json_encode(['success' => false, 'error' => 'File is not an image.']);
    exit;
}

$detectedType = $check[2];
$extensionMap = [
    IMAGETYPE_JPEG => 'jpg',
    IMAGETYPE_PNG => 'png', 
    IMAGETYPE_GIF => 'gif'
];
$realExtension = $extensionMap[$detectedType] ?? null;

if (!$realExtension) {
    echo json_encode(['success' => false, 'error' => 'Invalid image format.']);
    exit;
}

$allowedFormats = ['jpg', 'png', 'gif'];
if (!in_array($realExtension, $allowedFormats)) {
    echo json_encode(['success' => false, 'error' => 'Only JPG, JPEG, PNG, GIF files are allowed.']);
    exit;
}

if ($_FILES["file"]["size"] > 5000000) {
    echo json_encode(['success' => false, 'error' => 'File is too large. Max 5MB.']);
    exit;
}

$targetFile = $targetDir . uniqid() . '.' . $realExtension;

$stmt = $pdo->prepare("SELECT avatar_filename FROM users WHERE username = ?");
$stmt->execute([$username]);
$user = $stmt->fetch(PDO::FETCH_ASSOC);

if ($user && !empty($user['avatar_filename'])) {
    $oldFile = $targetDir . $user['avatar_filename'];
    if (file_exists($oldFile)) {
        unlink($oldFile);
    }
}

if (!move_uploaded_file($_FILES["file"]["tmp_name"], $targetFile)) {
    echo json_encode(['success' => false, 'error' => 'Error uploading file.']);
    exit;
}

$newFileName = basename($targetFile);
$stmt = $pdo->prepare("UPDATE users SET avatar_filename = ? WHERE username = ?");
$stmt->execute([$newFileName, $username]);

echo json_encode(['status' => 'success', 'file' => $newFileName]);

?>
