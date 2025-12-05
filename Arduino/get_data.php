<?php
// CORS Başlıkları
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");
header('Content-Type: application/json');

$file = 'data.json';
$limit = isset($_GET['limit']) ? (int)$_GET['limit'] : 20;

if (file_exists($file)) {
    $data = json_decode(file_get_contents($file), true);
    
    if ($data === null) {
        $data = [];
    }
    
    // Sadece en son N kaydı çek
    $startIndex = max(0, count($data) - $limit);
    $recentData = array_slice($data, $startIndex);
    
    http_response_code(200);
    echo json_encode($recentData);
    
} else {
    // Dosya yoksa boş dizi döndür
    http_response_code(200);
    echo json_encode([]);
}
?>