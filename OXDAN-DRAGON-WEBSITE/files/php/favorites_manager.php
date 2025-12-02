<?php
require_once 'database.php';

header('Content-Type: application/json');
session_start();

function generateSecureToken() {
    return bin2hex(random_bytes(32));
}

function checkRateLimit($pdo, $userToken, $action, $limit = 100) {
    $hourAgo = date('Y-m-d H:i:s', strtotime('-1 hour'));
    
    $stmt = $pdo->prepare("
        SELECT COUNT(*) as count 
        FROM user_favorites 
        WHERE token = ? AND created_at > ?
    ");
    $stmt->execute([$userToken, $hourAgo]);
    $result = $stmt->fetch(PDO::FETCH_ASSOC);
    
    return $result['count'] < $limit;
}

function validateProductId($product_id) {
    if (!is_numeric($product_id) || $product_id <= 0) {
        throw new Exception('Invalid product ID');
    }
    return (int)$product_id;
}

function validateUserToken($user_token) {
    if ($user_token && !preg_match('/^[a-f0-9]{64}$/', $user_token)) {
        throw new Exception('Invalid token format');
    }
    return $user_token;
}

$action = $_GET['action'] ?? '';
$input = json_decode(file_get_contents('php://input'), true);
$product_id = $input['product_id'] ?? ($_GET['product_id'] ?? null);
$user_token = $input['user_token'] ?? null;

try {
    if ($product_id) {
        $product_id = validateProductId($product_id);
    }
    if ($user_token) {
        $user_token = validateUserToken($user_token);
    }
    
    if ($user_token && !checkRateLimit($pdo, $user_token, $action)) {
        throw new Exception('Rate limit exceeded');
    }

    switch ($action) {
        case 'toggle':
            if (!$product_id) {
                throw new Exception('Product ID is required');
            }
            
            if (!$user_token) {
                $user_token = generateSecureToken();
                // Validate the newly generated token
                $user_token = validateUserToken($user_token);
            }
            
            $stmt = $pdo->prepare("SELECT id FROM user_favorites WHERE token = ? AND product_id = ?");
            $stmt->execute([$user_token, $product_id]);
            $existing = $stmt->fetch(PDO::FETCH_ASSOC);
            
            if ($existing) {
                $stmt = $pdo->prepare("DELETE FROM user_favorites WHERE token = ? AND product_id = ?");
                $stmt->execute([$user_token, $product_id]);
                $is_favorite = false;
            } else {
                $stmt = $pdo->prepare("INSERT INTO user_favorites (token, product_id) VALUES (?, ?)");
                $stmt->execute([$user_token, $product_id]);
                $is_favorite = true;
            }
            
            echo json_encode([
                'success' => true,
                'favorite' => $is_favorite,
                'user_token' => $user_token
            ]);
            break;
            
        case 'get':
            if (!$product_id) {
                throw new Exception('Product ID is required');
            }
            
            if (!$user_token) {
                echo json_encode(['success' => true, 'favorite' => false]);
                break;
            }
            
            $stmt = $pdo->prepare("SELECT id FROM user_favorites WHERE token = ? AND product_id = ?");
            $stmt->execute([$user_token, $product_id]);
            $is_favorite = $stmt->fetch(PDO::FETCH_ASSOC) !== false;
            
            echo json_encode([
                'success' => true,
                'favorite' => $is_favorite
            ]);
            break;
            
        case 'generate_token':
            $user_token = generateSecureToken();
            $user_token = validateUserToken($user_token);
            
            echo json_encode([
                'success' => true,
                'user_token' => $user_token
            ]);
            break;

        case 'list':
            if (!$user_token) {
                echo json_encode(['success' => true, 'favorites' => []]);
                break;
            }
            
            $stmt = $pdo->prepare("
                SELECT p.* 
                FROM products p 
                INNER JOIN user_favorites uf ON p.number = uf.product_id 
                WHERE uf.token = ?
            ");
            $stmt->execute([$user_token]);
            $favoriteProducts = $stmt->fetchAll(PDO::FETCH_ASSOC);
            
            echo json_encode([
                'success' => true,
                'favorites' => $favoriteProducts
            ]);
            break;
            
        default:
            throw new Exception('Invalid action');
    }
    
} catch (Exception $e) {
    echo json_encode([
        'success' => false,
        'error' => $e->getMessage()
    ]);
}
?>