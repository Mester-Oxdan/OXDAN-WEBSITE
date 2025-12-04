<?php
session_start();
ini_set('session.cookie_secure', 1);
ini_set('session.cookie_httponly', 1);
ini_set('session.use_strict_mode', 1);

$limitFile = __DIR__ . '/../../../rate_limits.json';
if (!file_exists($limitFile)) {
    file_put_contents($limitFile, json_encode([]));
}

$limits = json_decode(file_get_contents($limitFile), true) ?? [];
$ip = $_SERVER['REMOTE_ADDR'];
$now = time();
$cooldowns = [60, 300, 600, 900];
$threshold = 5;
$section = 'promocode';

function failPromo(&$limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section) {
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
        echo json_encode(['status' => 'error', 'message' => "Too many attempts for promocode_" . ($limits[$ip]['stage'][$section] + 1)]);
    } else {
        echo json_encode(['status' => 'error', 'message' => 'Invalid promo code.']);
    }

    exit;
}

if (!empty($limits[$ip]['blocked_until'][$section]) && $limits[$ip]['blocked_until'][$section] > $now) {
    $stage = $limits[$ip]['stage'][$section] ?? 0;
    echo json_encode(['status' => 'error', 'message' => 'Too many attempts for promocode_' . ($stage + 1)]);
    exit;
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $data = json_decode(file_get_contents('php://input'), true);
    $promo = strtolower(trim($data['promo'] ?? ''));

    $promo_groups = [
        'sans-battle' => [
            'variations' => ['sans-battle', 'sansbattle', 'sans_battle'],
            'display_message' => 'https://jcw87.github.io/c2-sans-fight/'
        ],
        'toby-fox' => [
            'variations' => ['toby-fox', 'tobyfox', 'toby_fox'],
            'display_message' => 'Thanks a lot! You are the hero of my childhood.<br>(Big fan) Thanks for <span style="color:red;">Undertale</span> :)'
        ],
        'scott-cawthon' => [
            'variations' => ['scott-cawthon', 'scottcawthon', 'scott_cawthon', 'scott'],
            'display_message' => 'Thanks a lot! You are one more hero of my childhood.<br>(Big fan) Thanks for <span style="color:yellow;">Five Nights at Freddy\'s</span> :)'
        ],
        'oxda8vpdlvlm' => [
            'variations' => ['oxda8vpdlvlm'],
            'display_message' => 'Sorry, this promo-code <span style="color:red;">Expired.</span> <br>Follow us on social media to be updated.'
        ]
    ];

    $valid_promos = [];
    foreach ($promo_groups as $group) {
        foreach ($group['variations'] as $variation) {
            $valid_promos[$variation] = $group['display_message'];
        }
    }

    if (isset($valid_promos[$promo])) {
        unset($limits[$ip]);
        file_put_contents($limitFile, json_encode($limits));
        echo json_encode([
            'status' => 'success', 
            'promo' => $promo, 
            'message' => $valid_promos[$promo]
        ]);
        exit;
    } else {
        failPromo($limits, $ip, $now, $cooldowns, $threshold, $limitFile, $section);
    }
} else {
    echo json_encode(['status' => 'error', 'message' => 'Invalid request method.']);
}
?>
