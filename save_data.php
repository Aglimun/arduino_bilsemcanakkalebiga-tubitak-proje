<?php
// CORS Başlıkları: HTML dosyası farklı bir kaynaktan (seri port) çalışacağı için zorunludur.
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST, GET, OPTIONS");
header("Access-Control-Allow-Headers: Content-Type");
header('Content-Type: application/json');

// Sadece POST isteği kabul et
if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    http_response_code(405); // Method Not Allowed
    echo json_encode(["message" => "Sadece POST metodu kabul edilir."]);
    exit();
}

// Gelen JSON verisini al
$json_data = file_get_contents("php://input");
$new_data_point = json_decode($json_data, true);

// Veri doğrulama
if (empty($new_data_point) || !isset($new_data_point['sic']) || !isset($new_data_point['time'])) {
    http_response_code(400); // Bad Request
    echo json_encode(["message" => "Geçersiz veri formatı."]);
    exit();
}

$file = 'data.json';

// Mevcut veriyi oku (dosya yoksa boş dizi ile başla)
if (file_exists($file)) {
    $current_data = json_decode(file_get_contents($file), true);
    if ($current_data === null) {
        $current_data = [];
    }
} else {
    $current_data = [];
}

// Yeni veriyi diziye ekle
$current_data[] = $new_data_point;

// Güvenli depolama limitini ayarla (örneğin 5000 kayıt)
$max_records = 5000;
if (count($current_data) > $max_records) {
    // En eski kayıtları sil (En son 5000 kaydı tut)
    $current_data = array_slice($current_data, -$max_records);
}

// Veriyi JSON formatına dönüştür ve dosyaya yaz
if (file_put_contents($file, json_encode($current_data)) === false) {
    http_response_code(500);
    echo json_encode(["message" => "Dosyaya yazma hatası. data.json dosyasının yazma iznini kontrol edin (CHMOD 666)." ]);
    exit();
}

http_response_code(200);
echo json_encode(["message" => "Veri başarıyla kaydedildi.", "count" => count($current_data)]);

?>