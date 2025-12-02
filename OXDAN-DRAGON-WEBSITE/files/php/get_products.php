<?php
header('Content-Type: application/json');

include __DIR__ . '/../php/database.php';

$category = $_GET['category'] ?? 'all';
$search = $_GET['search'] ?? '';

$category = htmlspecialchars($category, ENT_QUOTES, 'UTF-8');
$search = htmlspecialchars($search, ENT_QUOTES, 'UTF-8');
$search = substr($search, 0, 100);

$query = "SELECT * FROM products WHERE 1=1";
$params = [];

if ($category !== 'all' && $category !== '') {
  $query .= " AND category LIKE ?";
  $params[] = "%$category%";
}

if ($search !== '') {
  $query .= " AND LOWER(name) LIKE ?";
  $params[] = strtolower($search) . "%";
}

$stmt = $pdo->prepare($query);
$stmt->execute($params);

echo json_encode($stmt->fetchAll(PDO::FETCH_ASSOC));
?>