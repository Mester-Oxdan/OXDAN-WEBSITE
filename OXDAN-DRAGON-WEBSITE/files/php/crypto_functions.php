<?php

function encrypt($data, $key) {
    $ivLength = openssl_cipher_iv_length('aes-256-cbc');
    $iv = random_bytes($ivLength);
    $encrypted = openssl_encrypt($data, 'aes-256-cbc', $key, 0, $iv);
    
    return base64_encode($encrypted) . '::' . base64_encode($iv);
}

function decrypt($data, $key) {
    try {
        $parts = explode('::', $data);
        if (count($parts) !== 2) return false;
        
        $encrypted_data = base64_decode($parts[0]);
        $iv = base64_decode($parts[1]);
        
        return openssl_decrypt($encrypted_data, 'aes-256-cbc', $key, 0, $iv);
    } catch(Exception $e) {
        return false;
    }
}

function generateEncryptionKey($length = 32) {
    return random_bytes($length);
}

?>
