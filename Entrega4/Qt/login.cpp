#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//Usuario encontrado en db local
bool usuarioEncontrado = false;
Login::Login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Login),
                                manager( new QNetworkAccessManager( this ) ),
                                managerClima (new QNetworkAccessManager( this )),
                                managerparaimagen(new QNetworkAccessManager(this)),
                                managerMercadoLibre( new QNetworkAccessManager( this ) ),
                                imagenCargada(false),
                                adminDB( new AdminDB ),
                                ventana(new Ventana())



{
    ui->setupUi(this);

    //Conexion a la base de datos
    if (adminDB->conectar( "C:/Users/Maximo/Desktop/POO/DB-Local/poodb" ) )
         qDebug() << "Exito al conectar con la base de datos";
     else
         qDebug() << "ERROR al conectar con la base de datos";

    //Imagen de fondo
    connect(managerparaimagen, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargadeimagenFinalizada(QNetworkReply*)));
    managerparaimagen->get(QNetworkRequest(QUrl("https://t3.ftcdn.net/jpg/03/55/60/70/360_F_355607062_zYMS8jaz4SfoykpWz5oViRVKL32IabTP.jpg")));

    //Validar Creendenciales
    connect( ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validar_con_API()));
    connect( ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar_con_API()));
    connect( manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    //Mostrar Clima Actual en Cordoba

    connect(managerClima, SIGNAL(finished(QNetworkReply*)),this, SLOT(slot_mostrar_clima(QNetworkReply*)));

    QString ClimaApiUrl = "http://krokos.com.ar/api/apiclima.php";
    managerClima->get( QNetworkRequest( QUrl( ClimaApiUrl ) ) );

    //Funcionalidad recordar contrasena
    connect(ui->leUsuario, SIGNAL(editingFinished()), this, SLOT(slot_finalizoEscribirUsuario()));

    ui->leUsuario->setFocus();

}

Login::~Login()
{
    delete ui;
}

//Pintar el bg
void Login::paintEvent(QPaintEvent* Event)
{
    if (imagenCargada) {
        QPainter painter(this);
        painter.drawImage(0, 0, imagenBackground.scaled(this->width(), this->height()));
    }
}

//Finalizo la descarga de la imagen de bg
void Login::slot_descargadeimagenFinalizada(QNetworkReply* reply)
{
    imagenBackground = QImage::fromData(reply->readAll());
    imagenCargada = true;
    this->repaint();
    this->show();
}

//Una vez que la api del clima devolvio la informacion, cambio el texto al label lClima
void Login::slot_mostrar_clima( QNetworkReply * reply){
    QByteArray clima = reply->readAll();
    ui->lClima->setText(clima);

}

//Validacion de creedenciales ingresadas por el usuario
void Login::slot_validar_con_API()  {
    QString sUrl = "https://krokos.com.ar/api/poologin.php?user=";
    sUrl += ui->leUsuario->text();
    sUrl += "&pass=";
    sUrl += ui->leClave->text();

    manager->get( QNetworkRequest( QUrl( sUrl ) ) );
}
//Cuando el usuario finaliza de escribir sobre lineEdit usuario
void Login::slot_finalizoEscribirUsuario(){

    QString enteredUsername = ui->leUsuario->text();
    ventana->setUsername(enteredUsername);
    if ( adminDB->getDB().isOpen() )  {
         QSqlQuery * query = new QSqlQuery( adminDB->getDB() );

         query->exec( "SELECT clave FROM usuarios WHERE usuario='" + enteredUsername + "'" );
         //Mientras tengamos registros encontrados
         while ( query->next() )  {
             //Cambio el contenido de leClave, por la clave registrada en la base de datos
             QString claveRegistradaEnBase = query->value(0).toString();
             ui->leClave->setText(claveRegistradaEnBase);
             usuarioEncontrado = true;
         }


     }
}

//Cuando el servicio de validacion de creedenciales responda
void Login::slot_descargaFinalizada( QNetworkReply * reply )  {
    QString usuarioIngresado = ui->leUsuario->text();
    QString claveIngresada = ui->leClave->text();

    QByteArray ba = reply->readAll();
    qDebug() << ba;

    if ( ba.contains( "exito" ) )  { //el usuario es valido
        ba = ba.replace( "exito", " " );

        //Recordar Usuario y Contrasena

        if(ui->chRecordar->isChecked()){
            if ( adminDB->getDB().isOpen() )  {
             QSqlQuery * query = new QSqlQuery( adminDB->getDB() );

             query->exec( "SELECT clave FROM usuarios WHERE usuario='" + usuarioIngresado + "'" );
             //Si no hay registro de este usuario, insertaremos la clave
             if(!query->next()){
                 qDebug() << "Ningun usuario pa";
                 QSqlQuery * queryInsert = new QSqlQuery( adminDB->getDB() );
                 queryInsert->exec( "INSERT INTO usuarios (usuario, clave) values ('" + usuarioIngresado + "' , '" + claveIngresada + "' )" );
             }
             //Si tenemos algun registro de este usuario actualizaremos su clave en la tabla
             else  {
                 qDebug() << "Encontre un usuario";
                 //Actualizo la clave guardada en la base de datos, por la nueva que fue ingresada
                 QSqlQuery * actualizarClaveQuery = new QSqlQuery( adminDB->getDB() );
                 actualizarClaveQuery->exec( "UPDATE usuarios SET clave = '"+ claveIngresada +"' WHERE usuario='" + usuarioIngresado + "'" );
             }


         }
        }

        this->hide();
        ventana->show();

    }else if( ba.contains( ":" ) ){
        qDebug() << ba;
        QMessageBox::critical(this,"Error de validacion", "Ha alcanzado el limite de 3 intentos, puede intentar de vuelta a las " + ba);
    }else{ // usuario o contraseña invalida
        QMessageBox::critical(this,"Error de validacion", "Usuario o contraseña incorrectos");
    }
}




