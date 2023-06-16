<?php
$apiKey = '9411af434f1da79b75ff8f3164fd19f7';
$city = 'cordoba';
$apiUrl = "http://api.openweathermap.org/data/2.5/weather?q=$city&appid=$apiKey&units=metric";
$lang = 'sp';
$response = file_get_contents($apiUrl);
$data = json_decode($response);

if ($data->cod === 200) {
    $temperature = $data->main->temp;
    echo "Cordoba $temperature C";
} else {
    echo "Error al obtener la temperatura actual";
}
?>