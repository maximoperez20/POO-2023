#include "resultadosprod.h"
#include "ui_resultadosprod.h"

resultadosprod::resultadosprod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resultadosprod)
{
    ui->setupUi(this);
}

resultadosprod::~resultadosprod()
{
    delete ui;
}
//Muestro linea horizontal inferior de todos los widget producto
void resultadosprod::showProductLines()
{
    ui->producto1->showLine();
    ui->producto2->showLine();
    ui->producto3->showLine();
    ui->producto4->showLine();
    ui->producto5->showLine();
}
//Oculto linea horizontal inferior de todos los widget producto
void resultadosprod::hideProductLines()
{
    ui->producto1->hideLine();
    ui->producto2->hideLine();
    ui->producto3->hideLine();
    ui->producto4->hideLine();
    ui->producto5->hideLine();
}
//Seteo la informacion a el producto 1
void resultadosprod::setProducto1(QString nombre, QString precio, QUrl url)
{
    ui->producto1->setNombre( nombre );
    ui->producto1->setPrecio( precio );
    ui->producto1->setUrlImagen( url );
}
//Seteo la informacion a el producto 2
void resultadosprod::setProducto2(QString nombre, QString precio, QUrl url)
{
    ui->producto2->setNombre( nombre );
    ui->producto2->setPrecio( precio );
    ui->producto2->setUrlImagen( url );
}
//Seteo la informacion a el producto 3
void resultadosprod::setProducto3(QString nombre, QString precio, QUrl url)
{
    ui->producto3->setNombre( nombre );
    ui->producto3->setPrecio( precio );
    ui->producto3->setUrlImagen( url );
}
//Seteo la informacion a el producto 4
void resultadosprod::setProducto4(QString nombre, QString precio, QUrl url)
{
    ui->producto4->setNombre( nombre );
    ui->producto4->setPrecio( precio );
    ui->producto4->setUrlImagen( url );
}
//Seteo la informacion a el producto 5
void resultadosprod::setProducto5(QString nombre, QString precio, QUrl url)
{
    ui->producto5->setNombre( nombre );
    ui->producto5->setPrecio( precio );
    ui->producto5->setUrlImagen( url );
}
