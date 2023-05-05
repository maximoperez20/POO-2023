<?PHP
$host = "localhost";
$DB_name = "krokos_poo";
$DB_user = "krokos";
$DB_pass = "JUA752MAX423";

$conn = mysqli_connect($host, $DB_user, $DB_pass, $DB_name);

//Consultar sino da error la conexión a la base
if(!$conn) {
    echo "Error: No se pudo conectar a MySQL." . NEWLINE;
    echo "Nro de error: " . mysqli_connect_errno() . NEWLINE;
    echo "Mensaje de depuración: " . mysqli_connect_error() . NEWLINE;
    exit;
}

// Verificar conexión
if (!$conn) {
    die("Conexión fallida: " . mysqli_connect_error());
}
//echo "Conexión exitosa";
if ( isset( $_GET[ 'user' ] ) ) {

    // Procese los datos de inicio de sesión
    $username = $_GET["user"];
    $password = $_GET["pass"];
    // ...

    $sql = "SELECT * FROM USUARIOS WHERE username = '$username' AND contrasenia = '$password'";
    $resultado = mysqli_query($conn, $sql);

    if (mysqli_num_rows($resultado) == 1) {
        // Las credenciales son válidas
        // Mostrar los datos del usuario
        $fila = mysqli_fetch_assoc($resultado);
        echo "Nombre: " . $fila["nombre"] . "<br>";
        echo "Apellido: " . $fila["apellido"] . "<br>";
        echo "Correo electrónico: " . $fila["email"] . "<br>";
    } else {
        // Las credenciales no son válidas, muestre un mensaje de error
        echo "Nombre de usuario o contraseña incorrectos";
    }
}

?>