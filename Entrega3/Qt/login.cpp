#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>

#include <QFile>


Login::Login(QWidget *parent) : QWidget(parent),
                                ui(new Ui::Login),
                                manager( new QNetworkAccessManager( this ) ),
                                managerClima (new QNetworkAccessManager( this ))

{
    ui->setupUi(this);


    connect( ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_validar_con_API()));
    connect( ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar_con_API()));
    connect( manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    connect(ui->pbIngresar, SIGNAL(pressed()), this, SLOT(slot_cargar_clima()));

    connect(managerClima, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(slot_mostrar_clima(QNetworkReply*)));



    ui->leUsuario->setFocus();
    QString sUrl = "http://tusrutashoy.com.ar/api/Apiclima.php";
    managerClima ->get( QNetworkRequest( QUrl( sUrl ) ) );

    ventana = new Ventana;
}

Login::~Login()
{
    delete ui;
}
void Login::setClima(QString data)
{
    ui->lClima->setText(data);
}
void Login::slot_cargar_clima(){
    //Armo solicitud para el ws
    QString ClimaApiUrl = "http://krokos.com.ar/api/apiclima.php";
    managerClima->get( QNetworkRequest( QUrl( ClimaApiUrl ) ) );
}

void Login::slot_mostrar_clima( QNetworkReply * reply){
    QByteArray clima = reply->readAll();
    this->setClima( clima);

}

void Login::slot_validar_con_API()  {
    QString sUrl = "https://krokos.com.ar/api/poologin.php?user=";
    sUrl += ui->leUsuario->text();
    sUrl += "&pass=";
    sUrl += ui->leClave->text();

    manager->get( QNetworkRequest( QUrl( sUrl ) ) );
}

void Login::slot_descargaFinalizada( QNetworkReply * reply )  {
    QByteArray ba = reply->readAll();
    qDebug() << ba;


    if ( ba.contains( "exito" ) )  { //el usuario es valido
        ba = ba.replace( "exito", " " );
        this->hide();

        QFile file("./../index.html");
        file.open(QIODevice::ReadOnly | QIODevice::Text);




        ventana->setContenido( file.readAll() );
        ventana->show();

    }else if( ba.contains( ":" ) ){
        qDebug() << ba;
        QMessageBox::critical(this,"Error de validacion", "Ha alcanzado el limite de 3 intentos, puede intentar de vuelta a las " + ba);
    }else{ // usuario o contraseña invalida
        QMessageBox::critical(this,"Error de validacion", "Usuario o contraseña incorrectos");
    }


}




