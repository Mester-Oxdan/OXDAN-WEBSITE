<?php
session_start();

$rating = filter_var($_POST['rate'] ?? null, FILTER_VALIDATE_INT);

if (!$rating || $rating < 1 || $rating > 5) {
    echo json_encode(['status'=>'error','message'=>'Rating must be 1-5.']);
    exit;
}

if (empty($_SESSION['csrf_token']) || empty($_POST['csrf_token']) || 
    !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
    echo json_encode(['status'=>'error','message'=>'Invalid CSRF token.']);
    exit;
}

include __DIR__ . '/../php/database.php';

function getUserIP() {
    if (!empty($_SERVER['HTTP_CLIENT_IP'])) return $_SERVER['HTTP_CLIENT_IP'];
    if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) return explode(',', $_SERVER['HTTP_X_FORWARDED_FOR'])[0];
    return $_SERVER['REMOTE_ADDR'];
}

$limitFile = __DIR__ . '/../../../rate_limits.json';
if (!file_exists($limitFile)) file_put_contents($limitFile, json_encode([]));
$limits = json_decode(file_get_contents($limitFile), true) ?? [];

$threshold = 3;
$cooldowns = [60, 300, 1800, 3600];
$section = 'feedback';
$now = time();

$user_ip = getUserIP();
if (!isset($limits[$user_ip])) {
    $limits[$user_ip] = ['attempts' => [], 'stage' => [], 'blocked_until' => []];
}

if (!empty($limits[$user_ip]['blocked_until'][$section]) && $limits[$user_ip]['blocked_until'][$section] <= $now) {
    $limits[$user_ip]['attempts'][$section] = [];
    $limits[$user_ip]['stage'][$section] = 0;
    $limits[$user_ip]['blocked_until'][$section] = 0;
}

if (!empty($limits[$user_ip]['blocked_until'][$section]) && $limits[$user_ip]['blocked_until'][$section] > $now) {
    $stage = $limits[$user_ip]['stage'][$section] ?? 0;
    echo json_encode(['status'=>'error','message'=>'Too many feedbacks, try later.']);
    exit;
}

$stmt = $pdo->prepare("INSERT INTO feedbacks (rating, user_ip) VALUES (?, ?)");
$stmt->execute([$rating, $user_ip]);

$limits[$user_ip]['attempts'][$section][] = $now;
if (count($limits[$user_ip]['attempts'][$section]) >= $threshold) {
    $limits[$user_ip]['stage'][$section] = min(($limits[$user_ip]['stage'][$section] ?? 0) + 1, count($cooldowns)-1);
    $limits[$user_ip]['blocked_until'][$section] = $now + $cooldowns[$limits[$user_ip]['stage'][$section]];
    $limits[$user_ip]['attempts'][$section] = [];
}
file_put_contents($limitFile, json_encode($limits));

echo json_encode(['status'=>'success','message'=>'Thank you for your feedback!']);

?>
