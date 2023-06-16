#include "ventana.h"
#include "ui_ventana.h"
#include "resultadosprod.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "admindb.h"

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana),
    manager( new QNetworkAccessManager( this ) ),
    managerMercadoLibre( new QNetworkAccessManager( this ) ),
    managerUltimaBusqueda( new QNetworkAccessManager( this ) ),
    ventanaResultados(new resultadosprod)
{
    ui->setupUi(this);    
    connect( ui->pbBuscar, SIGNAL(pressed()), this, SLOT(slot_buscarProductosML()));
    connect( ui->leBuscador, SIGNAL(returnPressed()), this, SLOT(slot_buscarProductosML()));
    connect(managerMercadoLibre, SIGNAL(finished(QNetworkReply*)),this, SLOT(slot_productosMLCargados(QNetworkReply*)));
    connect(managerUltimaBusqueda, SIGNAL(finished(QNetworkReply*)),this, SLOT(slot_verificarUltimaBusqueda(QNetworkReply*)));

    ui->lError->setStyleSheet("QLabel { color: red; }");
    ui->lError->hide();
    this->setWindowTitle("Busqueda de productos");

    ui->results->hideProductLines();

}

void Ventana::realizarUltimaBusqueda(){
    //Busqueda en historial de busqueda con usuario
    QString ultBusquedaUrl = "https://krokos.com.ar/api/busqueda.php?action=busqueda&user=" + this->username;
    qDebug()<< "ultBusquedaUrl: " <<ultBusquedaUrl;
    managerUltimaBusqueda->get( QNetworkRequest( QUrl( ultBusquedaUrl ) ) );
}

//almaceno en atributo username, el usuario
void Ventana::setUsername(QString name){
    this->username = name;
    emit realizarUltimaBusqueda();
}
void Ventana::slot_verificarUltimaBusqueda( QNetworkReply * reply){
    QByteArray ba = reply->readAll();

    //Si se tiene registro de la ultima busqueda del usuario
    if(!ba.contains("0 registros")){
    QString productsApiRequest = "https://api.mercadolibre.com/sites/MLA/search?limit=5&q="+ba;
    qDebug()<< "productsApiRequest: " <<productsApiRequest;
    managerMercadoLibre->get( QNetworkRequest( QUrl( productsApiRequest ) ) );
    }
}
void Ventana::slot_buscarProductosML(){
    if(ui->leBuscador->text() == ""){
        ui->lError->show();
        return;
    }else{
        ui->lError->hide();
    }

    qDebug()<< "buscar prod";
    //Guardar en base de datos la ultima busqueda
    QString guardarBusquedaUrl = "https://krokos.com.ar/api/busqueda.php?action=insertar&busqueda="+ui->leBuscador->text()+"&user="+this->username;
    qDebug()<< guardarBusquedaUrl;
    manager->get( QNetworkRequest( QUrl( guardarBusquedaUrl ) ) );

    //Consultar a api de mercado libre
    QString productsApiRequest = "https://api.mercadolibre.com/sites/MLA/search?limit=5&q=";
    productsApiRequest += ui->leBuscador->text();
    managerMercadoLibre->get( QNetworkRequest( QUrl( productsApiRequest ) ) );
}
void Ventana::slot_productosMLCargados( QNetworkReply * reply){
    qDebug()<<"slot de prod";

    // Leo los datos de la respuesta
               QByteArray response = reply->readAll();
               //qDebug()<<response;

               // Parse del JSON
               QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
               QJsonObject jsonObject = jsonResponse.object();

               // Extraigo el array results de la respuesta y lo almaceno en resultsArray
               QJsonArray resultsArray = jsonObject.value("results").toArray();

               if(sizeof (resultsArray) > 1){
                   ui->results->showProductLines();
               }else{
                   ui->results->hideProductLines();
               }

               // Hago un for para leer los 5 productos
                   int cont = 0;
               for (const QJsonValue& resultValue : resultsArray) {

                    QJsonObject resultObject = resultValue.toObject();
                    QString title = resultObject.value("title").toString();
                    QString imageUrl = resultObject.value("thumbnail").toString();
                    float price = resultObject.value("price").toDouble();

                    QString formattedPrice = QString::number(price, 'f', 2);
      /*              qDebug() << "Title:" << title;
                    qDebug() << "Image URL:" << imageUrl;
                    qDebug() << "Price:" << formattedPrice;
                    qDebug() << "---------------------" << cont;
*/
                    switch(cont){
                    case 0:
                    ui->results->setProducto1( title, formattedPrice, imageUrl );
                    break;
                    case 1:
                    ui->results->setProducto2( title, formattedPrice, imageUrl );
                    break;
                    case 2:
                    ui->results->setProducto3( title, formattedPrice, imageUrl );
                    break;
                    case 3:
                    ui->results->setProducto4( title, formattedPrice, imageUrl );
                    break;
                    case 4:
                    ui->results->setProducto5( title, formattedPrice, imageUrl );
                    break;
                    default:
                    break;
                    }

                    cont++;

                }
}


Ventana::~Ventana()
{
    delete ui;
}

