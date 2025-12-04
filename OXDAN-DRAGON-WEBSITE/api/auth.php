<?php
session_set_cookie_params([
    'lifetime' => 0,
    'path' => '/',
    'secure' => true,
    'httponly' => true,
    'samesite' => 'Lax'
]);

if (session_status() === PHP_SESSION_NONE) {
    session_start();
    
    if (empty($_SESSION['initialized'])) {
        session_regenerate_id(true);
        $_SESSION['initialized'] = true;
        $_SESSION['created_time'] = time();
    }
} else {
    session_start();
}

function validateSession() {
    if (!isset($_SESSION['user_id']) || 
        !isset($_SESSION['username']) ||
        !isset($_SESSION['login_time']) ||
        !isset($_SESSION['ip']) ||
        !isset($_SESSION['ua'])) {
        return false;
    }
    
    $inactive_limit = 1800;
    if (time() - $_SESSION['login_time'] > $inactive_limit) {
        return false;
    }
    
    $absolute_limit = 28800;
    $created_time = $_SESSION['created_time'] ?? $_SESSION['login_time'];
    if (time() - $created_time > $absolute_limit) {
        return false;
    }
    
    $sessionIp = $_SESSION['ip'];
    $currentIp = $_SERVER['REMOTE_ADDR'];
    if ($sessionIp !== $currentIp) {
        return false;
    }
    
    $sessionUa = $_SESSION['ua'];
    $currentUa = $_SERVER['HTTP_USER_AGENT'] ?? '';
    if ($sessionUa !== $currentUa) {
        return false;
    }
    
    $regeneration_interval = 900;
    $last_regeneration = $_SESSION['last_regeneration'] ?? $_SESSION['login_time'];
    if (time() - $last_regeneration > $regeneration_interval) {
        session_regenerate_id(true);
        $_SESSION['last_regeneration'] = time();
        
        $essential_data = [
            'user_id', 'username', 'email', 'ip', 'ua', 
            'login_time', 'created_time', 'last_activity',
            'oauth_provider', 'csrf_token'
        ];
        
        $preserved_data = [];
        foreach ($essential_data as $key) {
            if (isset($_SESSION[$key])) {
                $preserved_data[$key] = $_SESSION[$key];
            }
        }
        
        session_unset();
        foreach ($preserved_data as $key => $value) {
            $_SESSION[$key] = $value;
        }
    }
    
    $_SESSION['last_activity'] = time();
    
    return true;
}

$current_page = $_SERVER['REQUEST_URI'] ?? '';

$allowed_pages = [
    '/confirm_email',
    '/change_password',
    '/confirm_email_new'
];

$is_verification_page = false;
foreach ($allowed_pages as $page) {
    if (strpos($current_page, $page) !== false) {
        $is_verification_page = true;
        break;
    }
}

if (empty($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

if ($is_verification_page) {
    if (empty($_SESSION['pending_verification'])) {
        header('Location: /register');
        exit();
    }
    
    if ($_SESSION['pending_ip'] !== $_SERVER['REMOTE_ADDR']) {
        unset($_SESSION['pending_verification']);
        unset($_SESSION['pending_expiry']);
        unset($_SESSION['pending_ip']);
        header('Location: /register?security=1');
        exit();
    }
    
    if (isset($_SESSION['pending_expiry']) && time() > $_SESSION['pending_expiry']) {
        unset($_SESSION['pending_verification']);
        unset($_SESSION['pending_expiry']);
        unset($_SESSION['pending_ip']);
        header('Location: /register?expired=1');
        exit();
    }
}

if (!validateSession() && !$is_verification_page) {
    session_unset();
    session_destroy();
    
    setcookie(session_name(), '', [
        'expires' => time() - 3600,
        'path' => '/',
        'secure' => true,
        'httponly' => true,
        'samesite' => 'Lax'
    ]);
    
    header('Location: /login?expired=1');
    exit();
}

if (empty($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

function regenerateSessionAfterPrivilegeChange() {
    $essential_data = [
        'user_id', 'username', 'email', 'ip', 'ua', 
        'login_time', 'created_time', 'last_activity', 'last_regeneration',
        'oauth_provider', 'csrf_token', 'initialized'
    ];
    
    $preserved_data = [];
    foreach ($essential_data as $key) {
        if (isset($_SESSION[$key])) {
            $preserved_data[$key] = $_SESSION[$key];
        }
    }
    
    session_regenerate_id(true);
    
    foreach ($preserved_data as $key => $value) {
        $_SESSION[$key] = $value;
    }
    
    $_SESSION['last_regeneration'] = time();
    $_SESSION['last_activity'] = time();
}

?>
