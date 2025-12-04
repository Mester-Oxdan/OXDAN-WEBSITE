<?php
include __DIR__ . '/database.php';

$stmt = $pdo->query("SELECT COUNT(*) as total_ratings, AVG(rating) as average_score FROM feedbacks");
$result = $stmt->fetch(PDO::FETCH_ASSOC);

echo json_encode([
    'total_ratings' => (int)$result['total_ratings'],
    'average_score' => $result['average_score'] ? number_format($result['average_score'], 2) : '0.00'
]);

?>
