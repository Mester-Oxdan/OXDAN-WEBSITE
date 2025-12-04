<?php
include __DIR__ . '/database.php';

$file = __DIR__ . '/questions.txt';
$questions = file($file, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

$stmt = $pdo->prepare("INSERT INTO faq (question, answer, tags) VALUES (?, ?, ?)");

foreach ($questions as $line) {
    $parts = explode('||', $line);
    if (count($parts) === 3) {
        [$question, $answer, $tags] = $parts;
        $stmt->execute([trim($question), trim($answer), trim($tags)]);
    }
}

echo "✅ FAQ data imported successfully.\n";
