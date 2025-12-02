<?php
session_start();
include __DIR__ . '/../php/database.php';

$query = isset($_GET['query']) ? trim($_GET['query']) : '';
$query = substr($query, 0, 100);
$query = htmlspecialchars($query, ENT_QUOTES, 'UTF-8');

$limitFile = __DIR__ . '/../../../rate_limits.json';
if (!file_exists($limitFile)) file_put_contents($limitFile, json_encode([]));
$limits = json_decode(file_get_contents($limitFile), true) ?? [];

$ip = $_SERVER['REMOTE_ADDR'];
$now = time();
$section = 'search';
$cooldown = 2;

if (!isset($limits[$ip])) {
    $limits[$ip] = ['last_search' => 0];
}

if (($now - $limits[$ip]['last_search']) < $cooldown) {
    header('Content-Type: application/json');
    echo json_encode(['error' => 'Please wait between searches']);
    exit;
}

$limits[$ip]['last_search'] = $now;
file_put_contents($limitFile, json_encode($limits));

if ($query === '') {
    $stmt = $pdo->query("SELECT question, answer, tags FROM faq ORDER BY id ASC");
} else {
    $searchQuery = '%' . strtolower($query) . '%';
    $stmt = $pdo->prepare("
        SELECT question, answer, tags 
        FROM faq
        WHERE LOWER(question) LIKE ?
           OR LOWER(tags) LIKE ?
        ORDER BY id ASC
    ");
    $stmt->execute([$searchQuery, $searchQuery]);
}

$results = $stmt->fetchAll(PDO::FETCH_ASSOC);

header('Content-Type: application/json');
echo json_encode($results);

?>
