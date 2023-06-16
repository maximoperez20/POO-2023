<?php

$host = "localhost";
$DB_name = "krokos_poo";
$DB_user = "krokos";
$DB_pass = "JUA752MAX423";

$conn = mysqli_connect($host, $DB_user, $DB_pass, $DB_name);

//Consultar sino da error la conexión a la base
if (!$conn) {
    echo "Error: No se pudo conectar a MySQL." . "<br/>";
    echo "Nro de error: " . mysqli_connect_errno() . "<br/>";
    echo "Mensaje de depuración: " . mysqli_connect_error() . "<br/>";
    exit;
}

// Verificar conexión
if (!$conn) {
    die("Conexión fallida: " . mysqli_connect_error());
}

$action = $_GET['action'];
$user = $_GET['user'];
$busquedaTexto = $_GET['busqueda'];

if (isset($_GET['user'])) {
    if ($action == "busqueda") {
        $sql = "SELECT ultima_busqueda FROM BUSQUEDAS WHERE usuario = '$user' ";
        $resultado = mysqli_query($conn, $sql);

        if (mysqli_num_rows($resultado) >= 1) { // Existe usuario con ese username
            // Las credenciales son válidas
            // Mostrar los datos del usuario
            $registro = mysqli_fetch_assoc($resultado);
            echo $registro['ultima_busqueda'];
        } else {
            echo "0 registros";
        }
    }
}
if (isset($_GET['user']) && isset($_GET['busqueda'])) {

    if ($action == "insertar") {
        $sql = "SELECT ultima_busqueda FROM BUSQUEDAS WHERE usuario = '$user'";
        $resultado = mysqli_query($conn, $sql);

        if (mysqli_num_rows($resultado) >=1) { // Existe usuario con ese username
            $sqlActualizar = "UPDATE BUSQUEDAS SET usuario = '$user', ultima_busqueda= '$busquedaTexto' WHERE usuario='$user'";
            mysqli_query($conn, $sqlActualizar);
            echo $sqlActualizar;
        } else {
            $sqlInsertar = "INSERT INTO BUSQUEDAS (usuario, ultima_busqueda) VALUES ('$user', '$busquedaTexto')";
            mysqli_query($conn, $sqlInsertar);
            echo $sqlInsertar;
        }
    }
}
