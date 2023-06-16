<?PHP
$host = "localhost";
$DB_name = "krokos_poo";
$DB_user = "krokos";
$DB_pass = "JUA752MAX423";

$conn = mysqli_connect($host, $DB_user, $DB_pass, $DB_name);

//Consultar sino da error la conexión a la base
if(!$conn) {
    echo "Error: No se pudo conectar a MySQL." . "<br/>";
    echo "Nro de error: " . mysqli_connect_errno() . "<br/>";
    echo "Mensaje de depuración: " . mysqli_connect_error() . "<br/>";
    exit;
}

// Verificar conexión
if (!$conn) {
    die("Conexión fallida: " . mysqli_connect_error());
}
// $timezone = date_default_timezone_get();
// echo "The current server timezone is: " . $timezone; America/New_York
//$today = date("Y-m-d H:i:s");
if ( isset( $_GET[ 'user' ] ) ) {

    // Procese los datos de inicio de sesión
    $username = $_GET["user"];
    $password = $_GET["pass"];
    // ...
    $intentos;
    $ultimo_intento;
    date_default_timezone_set('America/Argentina/Buenos_Aires');


    $sql = "SELECT * FROM USUARIOS WHERE username = '$username'";
    $resultado = mysqli_query($conn, $sql);
    // INGRESO UN NOMBRE CORRECTO PERO NO LA CONTRASENA
        // HAGO UN UPDATE EN CAMPO INTENTOS +1, HAGO UN UPDATE EN ultimo_intento = DATETIME
    // NO HAY USUARIO CORRECTO
    if (mysqli_num_rows($resultado) == 1) { // Existe usuario con ese username
        // Las credenciales son válidas
        // Mostrar los datos del usuario
        $fila = mysqli_fetch_assoc($resultado);
        $ultimo_inicio = $fila["ultimo_intento"];

        $proximo_intento =strtotime($ultimo_inicio);
        $nueva_fecha = date('H:i:s', $proximo_intento + 300);
        //echo $nueva_fecha;
        $ultimo_intento = date("Y-m-d H:i:s");
        if ($fila["intentos"] >= 3){
            // Si la diferencia de minutos entre la fecha actual y el ultimo intento es mayor a 5
            $fecha_actual = new DateTime(); // Fecha actual
            $ultimo_inicio = new DateTime($ultimo_inicio); // Fecha obtenida de la base de datos como objeto DateTime
            $diferencia = $fecha_actual->diff($ultimo_inicio); // Diferencia entre las dos fechas
            $minutos = $diferencia->i; // Obtener los minutos de la diferencia
            //echo $minutos; // Imprimir la diferencia de minutos
            if($minutos < 5){
                echo $nueva_fecha;
                exit;
            } else{
                $cod_usuario = $fila["id_user"];
                if($fila["contrasenia"] == $password){
                    echo "exito";
                    $sql3 = "UPDATE USUARIOS SET intentos = 0, ultimo_intento = '$ultimo_intento' WHERE id_user = '$cod_usuario'";
                    mysqli_query($conn, $sql3);
                }
                else {
                    $intentos = $fila["intentos"] + 1 ;
                    $sql2 = "UPDATE USUARIOS SET intentos = '$intentos', ultimo_intento = '$ultimo_intento' WHERE id_user ='$cod_usuario' ";
                    mysqli_query($conn, $sql2);
                }
            }

        } else{
            $cod_usuario = $fila["id_user"];

            if($fila["contrasenia"] == $password){
                echo "exito";
                $sql3 = "UPDATE USUARIOS SET intentos = 0, ultimo_intento = '$ultimo_intento' WHERE id_user = '$cod_usuario'";
            }
            else {
                $intentos = $fila["intentos"] + 1 ;
                $sql2 = "UPDATE USUARIOS SET intentos = '$intentos', ultimo_intento = '$ultimo_intento' WHERE id_user ='$cod_usuario' ";
                mysqli_query($conn, $sql2);
            }
        }
    } else {

        // Las credenciales no son válidas, muestre un mensaje de error
        echo "Nombre de usuario o contraseña incorrectos";

    }
}

?>