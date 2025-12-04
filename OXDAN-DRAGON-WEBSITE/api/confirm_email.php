<?php

session_start();

if (!isset($_SESSION['pending_verification'])) {
    echo json_encode(['status' => 'error', 'message' => 'Session expired or invalid.']);
    exit;
}

$pendingData = $_SESSION['pending_verification'];
$email_2 = $pendingData['email'];
$username_2 = $pendingData['username'];
$storedCode = $pendingData['verification_code'];
$passwordHash = $pendingData['password_hash'];

include __DIR__ . '/crypto_functions.php';
include __DIR__ . '/database.php';

function failAction(&$limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section) {
    if (!isset($limits[$ip]['attempts'][$section]) || !is_array($limits[$ip]['attempts'][$section])) {
        $limits[$ip]['attempts'][$section] = [];
    }

    $limits[$ip]['attempts'][$section] = array_filter($limits[$ip]['attempts'][$section], fn($ts) => $ts > $now - 3600);
    $limits[$ip]['attempts'][$section][] = $now;

    if (count($limits[$ip]['attempts'][$section]) >= $threshold) {
        $limits[$ip]['stage'][$section] = min(($limits[$ip]['stage'][$section] ?? 0) + 1, count($cooldowns) - 1);
        $limits[$ip]['blocked_until'][$section] = $now + $cooldowns[$limits[$ip]['stage'][$section]];
        $limits[$ip]['attempts'][$section] = [];
    }

    file_put_contents($limitFile, json_encode($limits));

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] > $now) {
        echo json_encode([
            'status' => 'error',
            'message' => "Too many attempts for $section" . '_' . ($limits[$ip]['stage'][$section] + 1)
        ]);
    } else {
        echo json_encode([
            'status' => 'error',
            'message' => 'Error wrong code.'
        ]);
    }
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data_2 = json_decode(file_get_contents('php://input'), true);

    if (empty($_SESSION['csrf_token']) || empty($data_2['csrf_token']) || 
        !hash_equals($_SESSION['csrf_token'], $data_2['csrf_token'])) {
        echo json_encode(['status' => 'error', 'message' => 'Invalid CSRF token.']);
        exit;
    }

    $code_2 = $data_2['code'];

    $ip = $_SERVER['REMOTE_ADDR'];
    $limitFile = __DIR__ . '/../../../rate_limits.json';

    if (!file_exists($limitFile)) {
        file_put_contents($limitFile, json_encode([]));
    }

    $limits = json_decode(file_get_contents($limitFile), true) ?? [];
    if (!isset($limits[$ip])) {
        $limits[$ip] = [
            'attempts' => [],
            'stage' => [],
            'blocked_until' => []
        ];
    }

    $now = time();
    $cooldowns = [60, 300, 600, 900];
    $threshold = 5;
    $section = 'confirm_email';

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] <= $now) {
        $limits[$ip]['attempts'][$section] = [];
        $limits[$ip]['stage'][$section] = 0;
        $limits[$ip]['blocked_until'][$section] = 0;
    }

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] > $now) {
        $stage = $limits[$ip]['stage'][$section] ?? 0;
        echo json_encode([
            'status' => 'error',
            'message' => 'Too many attempts for confirm_email_' . ($stage + 1)
        ]);
        exit;
    }

    if ($storedCode !== $code_2) {
        failAction($limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section);
    }

    try {
        $stmt = $pdo->prepare("INSERT INTO users (username, email, password_hash, verified) VALUES (?, ?, ?, 1)");
        $stmt->execute([$username_2, $email_2, $passwordHash]);
        $userId = $pdo->lastInsertId();
        
        session_regenerate_id(true);
        $_SESSION['user_id'] = $userId;
        $_SESSION['username'] = $username_2;
        $_SESSION['email'] = $email_2;
        $_SESSION['ip'] = $_SERVER['REMOTE_ADDR'];
        $_SESSION['ua'] = $_SERVER['HTTP_USER_AGENT'] ?? '';
        $_SESSION['login_time'] = time();
        $_SESSION['last_activity'] = time();
        $_SESSION['csrf_token'] = bin2hex(random_bytes(32));

        unset($_SESSION['pending_verification']);
        unset($_SESSION['pending_expiry']);

        if (isset($limits[$ip]['attempts'][$section])) {
            $limits[$ip]['attempts'][$section] = [];
            $limits[$ip]['stage'][$section] = 0;
            $limits[$ip]['blocked_until'][$section] = 0;
            file_put_contents($limitFile, json_encode($limits));
        }

        echo json_encode(['status' => 'success', 'message' => 'Email verification successful.']);
        
    } catch (PDOException $e) {
        echo json_encode(['status' => 'error', 'message' => 'Database insertion failed.']);
        exit;
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method.']);
}
?>
