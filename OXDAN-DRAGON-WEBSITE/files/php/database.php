<?php
$pdo = new PDO('sqlite:' . __DIR__ . '/../../../app.db');
$pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$pdo->exec("PRAGMA foreign_keys = ON");

$tables = [
    'users' => "
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            email TEXT UNIQUE NOT NULL,
            password_hash TEXT,
            verified INTEGER DEFAULT 0,
            verification_code TEXT,
            oauth_provider TEXT,
            oauth_id TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    ",
    
    'faq' => "
        CREATE TABLE IF NOT EXISTS faq (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            question TEXT NOT NULL,
            answer TEXT NOT NULL,
            tags TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    ",
    
    'comments' => "
        CREATE TABLE IF NOT EXISTS comments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL,
            comment TEXT NOT NULL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    ",
    
    'feedbacks' => "
        CREATE TABLE IF NOT EXISTS feedbacks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            rating INTEGER NOT NULL,
            user_ip TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    ",
    
    'products' => "
        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            category TEXT NOT NULL,
            folder TEXT NOT NULL,
            image TEXT NOT NULL,
            price TEXT NOT NULL,
            number INTEGER UNIQUE NOT NULL,
            url TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    ",
    
    'user_favorites' => "
        CREATE TABLE IF NOT EXISTS user_favorites (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            token VARCHAR(64) NOT NULL,
            product_id INTEGER NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            UNIQUE (token, product_id)
        );
    "
];

foreach ($tables as $tableName => $createSQL) {
    $pdo->exec($createSQL);
}

$indexes = [
    'idx_users_email' => 'CREATE INDEX IF NOT EXISTS idx_users_email ON users(email)',
    'idx_users_oauth' => 'CREATE INDEX IF NOT EXISTS idx_users_oauth ON users(oauth_provider, oauth_id)',
    'idx_faq_tags' => 'CREATE INDEX IF NOT EXISTS idx_faq_tags ON faq(tags)',
    'idx_comments_timestamp' => 'CREATE INDEX IF NOT EXISTS idx_comments_timestamp ON comments(timestamp)',
    'idx_feedbacks_ip' => 'CREATE INDEX IF NOT EXISTS idx_feedbacks_ip ON feedbacks(user_ip)',
    'idx_products_category' => 'CREATE INDEX IF NOT EXISTS idx_products_category ON products(category)',
    'idx_products_number' => 'CREATE INDEX IF NOT EXISTS idx_products_number ON products(number)',
    'idx_user_favorites_token' => 'CREATE INDEX IF NOT EXISTS idx_user_favorites_token ON user_favorites(token)',
    'idx_user_favorites_product' => 'CREATE INDEX IF NOT EXISTS idx_user_favorites_product ON user_favorites(product_id)'
];

foreach ($indexes as $indexName => $createIndexSQL) {
    $pdo->exec($createIndexSQL);
}

$stmt = $pdo->query("PRAGMA table_info(products)");
$columns = $stmt->fetchAll(PDO::FETCH_ASSOC);

$favoritesColumnExists = false;
foreach ($columns as $column) {
    if ($column['name'] === 'favorites') {
        $favoritesColumnExists = true;
        break;
    }
}
?>