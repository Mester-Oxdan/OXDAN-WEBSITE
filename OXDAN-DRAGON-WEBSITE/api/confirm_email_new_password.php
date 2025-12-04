<?php

session_start();

ini_set('session.cookie_secure', 1);
ini_set('session.cookie_httponly', 1);
ini_set('session.use_strict_mode', 1);

header('Content-Type: application/json');

$pdo = new PDO('sqlite:' . __DIR__ . '/../../app.db');
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$pdo->exec("PRAGMA foreign_keys = ON");

$RATE_FILE = __DIR__ . '/../../../rate_limits.json';
$SECTION = 'confirm_email_new_password';
$COOLDOWNS = [60, 300, 600, 900];
$THRESHOLD = 5;

function failAction(&$limits, $ip, $now, $cooldowns, $threshold, $rateFile, $section) {
    if (!isset($limits[$ip]['attempts'][$section]) || !is_array($limits[$ip]['attempts'][$section])) {
        $limits[$ip]['attempts'][$section] = [];
    }

    $limits[$ip]['attempts'][$section] = array_filter(
        $limits[$ip]['attempts'][$section],
        fn($t) => $t > $now - 3600
    );
    $limits[$ip]['attempts'][$section][] = $now;

    if (count($limits[$ip]['attempts'][$section]) >= $threshold) {
        $limits[$ip]['stage'][$section] = min(($limits[$ip]['stage'][$section] ?? 0) + 1, count($cooldowns) - 1);
        $limits[$ip]['blocked_until'][$section] = $now + $cooldowns[$limits[$ip]['stage'][$section]];
        $limits[$ip]['attempts'][$section] = [];
    }

    file_put_contents($rateFile, json_encode($limits));

    if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] > $now) {
        echo json_encode([
            'status' => 'error',
            'message' => "Too many attempts for {$section}_" . ($limits[$ip]['stage'][$section] + 1)
        ]);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Wrong code.']);
    }
    exit;
}

$ip = $_SERVER['REMOTE_ADDR'];
if (!file_exists($RATE_FILE)) {
    file_put_contents($RATE_FILE, json_encode([]));
}
$limits = json_decode(file_get_contents($RATE_FILE), true) ?? [];
if (!isset($limits[$ip])) {
    $limits[$ip] = ['attempts' => [], 'stage' => [], 'blocked_until' => []];
}

$now = time();

if (!empty($limits[$ip]['blocked_until'][$SECTION]) && $limits[$ip]['blocked_until'][$SECTION] <= $now) {
    $limits[$ip]['attempts'][$SECTION] = [];
    $limits[$ip]['stage'][$SECTION] = 0;
    $limits[$ip]['blocked_until'][$SECTION] = 0;
}

if (!empty($limits[$ip]['blocked_until'][$SECTION]) && $limits[$ip]['blocked_until'][$SECTION] > $now) {
    $stage = $limits[$ip]['stage'][$SECTION] ?? 0;
    echo json_encode([
        'status' => 'error',
        'message' => 'Too many attempts for ' . $SECTION . '_' . ($stage + 1)
    ]);
    exit;
}

try {
    $data = json_decode(file_get_contents('php://input'), true);
    
    if (!$data) {
        throw new Exception('No data received');
    }

    if (empty($_SESSION['csrf_token']) || empty($data['csrf_token']) || 
        !hash_equals($_SESSION['csrf_token'], $data['csrf_token'])) {
        throw new Exception('Invalid CSRF token.');
    }
    
    $code = $data['code'] ?? '';

    $code = trim($code);
    $code = preg_replace('/[^a-zA-Z0-9]/', '', $code);
    
    if (strlen($code) !== 6) {
        throw new Exception('Invalid code format.');
    }
    
    if (!isset($_SESSION['password_reset'])) {
        throw new Exception('Reset session expired. Please start over.');
    }
    
    $resetData = $_SESSION['password_reset'];
    $email = $resetData['email'];
    
    if (time() > $resetData['expiry']) {
        unset($_SESSION['password_reset']);
        throw new Exception('Reset session expired. Please start over.');
    }

    if (empty($code)) {
        throw new Exception('Code required');
    }

    $stmt = $pdo->prepare("SELECT verification_code FROM users WHERE email=?");
    $stmt->execute([$email]);
    $stored_code = $stmt->fetchColumn();

    if (!$stored_code) {
        throw new Exception('No verification code found. Please request a new one.');
    }

    if ($stored_code !== $code) {
        failAction($limits, $ip, $now, $COOLDOWNS, $THRESHOLD, $RATE_FILE, $SECTION);
    }

    $stmt = $pdo->prepare("UPDATE users SET verification_code = NULL WHERE email=?");
    $stmt->execute([$email]);

    $_SESSION['pending_verification'] = [
        'username' => $resetData['username'],
        'email' => $email,
        'created_at' => time()
    ];

    $_SESSION['verified_password_reset'] = [
        'email' => $email,
        'username' => $resetData['username'],
        'verified_at' => time(),
        'expiry' => time() + 3600,
        'csrf_token' => bin2hex(random_bytes(32))
    ];
    $_SESSION['pending_ip'] = $_SERVER['REMOTE_ADDR'];
    $_SESSION['pending_expiry'] = time() + 3600;
    
    unset($_SESSION['password_reset']);

    $limits[$ip]['attempts'][$SECTION] = [];
    $limits[$ip]['stage'][$SECTION] = 0;
    $limits[$ip]['blocked_until'][$SECTION] = 0;
    file_put_contents($RATE_FILE, json_encode($limits));

    echo json_encode(['status' => 'success', 'message' => 'Code verified successfully.']);
    
} catch (Exception $e) {
    echo json_encode(['status' => 'error', 'message' => $e->getMessage()]);
}
?>
