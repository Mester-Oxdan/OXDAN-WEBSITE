<?php
session_start();

if (!isset($_GET['file'])) {
    http_response_code(400);
    die('No file specified.');
}

$allowed_files = [
    'installer' => 'Oxdan-Dragon-Console-C-3-2025-Setup.zip',
    'files' => 'Oxdan-Dragon-Console-C-3-2025-Files.zip'
];

$file_key = $_GET['file'];

if (!array_key_exists($file_key, $allowed_files)) {
    http_response_code(400);
    die('Invalid file selection.');
}

$filename = $allowed_files[$file_key];
$filepath = __DIR__ . '/path_to_zip_files/' . $filename;

$real_base = realpath(__DIR__ . '/path_to_zip_files/');
$real_path = realpath($filepath);

if ($real_path === false || strpos($real_path, $real_base) !== 0) {
    http_response_code(403);
    die('Access denied.');
}

if (!file_exists($filepath)) {
    http_response_code(404);
    die('File not found.');
}

$limitFile = __DIR__ . '/../../../rate_limits.json';
if (!file_exists($limitFile)) file_put_contents($limitFile, json_encode([]));
$limits = json_decode(file_get_contents($limitFile), true) ?? [];

$ip = $_SERVER['REMOTE_ADDR'];
$now = time();
$section = 'download';

if (!isset($limits[$ip])) {
    $limits[$ip] = ['last_download' => 0, 'count' => 0];
}

if ($limits[$ip]['count'] >= 5 && ($now - $limits[$ip]['last_download']) < 3600) {
    http_response_code(429);
    die('Download limit exceeded. Please try again later.');
}

$limits[$ip]['count']++;
$limits[$ip]['last_download'] = $now;
file_put_contents($limitFile, json_encode($limits));

while (ob_get_level()) {
    ob_end_clean();
}

header('Content-Description: File Transfer');
header('Content-Type: application/zip');
header('Content-Disposition: attachment; filename="' . $filename . '"');
header('Expires: 0');
header('Cache-Control: must-revalidate');
header('Pragma: public');
header('Content-Length: ' . filesize($filepath));
header('X-Content-Type-Options: nosniff');

$fp = fopen($filepath, 'rb');
if ($fp) {
    while (!feof($fp)) {
        echo fread($fp, 1024 * 8);
        flush();
    }
    fclose($fp);
}
exit;
?>