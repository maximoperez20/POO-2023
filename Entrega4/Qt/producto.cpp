#include "producto.h"
#include "ui_producto.h"

Producto::Producto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Producto),
    managerImagen( new QNetworkAccessManager( this ) )
{
    ui->setupUi(this);
    connect( managerImagen, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(slot_descargaImagenFinalizada(QNetworkReply*)));
}

Producto::~Producto()
{
    delete ui;
}
//Cambio el texto de lNombre por el titulo del producto
void Producto::setNombre(QString nombre)
{
    ui->lNombre->setText( nombre );
}
//Cambio el texto de lPrecio por el precio del producto
void Producto::setPrecio(QString precio)
{
ui->lPrecio->setText( "$ " +precio );
}

//Descargo imagen del producto a partir de la url que viene de la response
void Producto::setUrlImagen(QUrl url)
{
managerImagen->get((QNetworkRequest(QUrl(url))));

}

void Producto::showLine()
{
    ui->line->show();
}
void Producto::hideLine()
{
    ui->line->hide();
}
//Cuando finaliza la descarga de la imagen del producto
void Producto::slot_descargaImagenFinalizada(QNetworkReply* reply){
    QByteArray imageData = reply->readAll();

               // Create a QPixmap from the image data
               QPixmap pixmap;
               pixmap.loadFromData(imageData);

               // Set the pixmap as the label's pixmap
               ui->lImagen->setPixmap(pixmap.scaled(ui->lImagen->size(), Qt::KeepAspectRatio));

}
