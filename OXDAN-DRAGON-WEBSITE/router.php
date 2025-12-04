<?php
// router.php - Clean organized routes

$uri = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);

// Serve static files directly
if (file_exists(__DIR__ . $uri) && !is_dir(__DIR__ . $uri)) {
    return false;
}

$routes = [
    // Main
    '/' => 'index.html',
    '/start' => 'index.html',
    
    // Pages
    '/login' => 'pages/login.php',
    '/register' => 'pages/register.php',
    '/faq' => 'pages/faq.html',
    '/lists' => 'pages/lists.html',
    '/about' => 'pages/about.html',
    '/terms' => 'pages/terms.html',
    '/privacy' => 'pages/privacy.html',
    '/sitemap' => 'pages/sitemap.html',
    
    // Auth (email verification, password reset)
    '/confirm_email' => 'files/confirm_email_start.php',
    '/change_password' => 'files/change_password_start.php',
    '/confirm_email_new' => 'files/confirm_email_new_password_start.php',
    
    // Shop (legacy support)
    '/3d_printing_shop' => 'files/3d_printing_shop_start.html',
    '/promo_codes' => 'files/promo_codes_start.html',
];

$uri_clean = rtrim($uri, '/') ?: '/';

if (array_key_exists($uri_clean, $routes)) {
    include __DIR__ . '/' . $routes[$uri_clean];
} else {
    http_response_code(404);
    echo "404 Not Found: " . htmlspecialchars($uri);
}
