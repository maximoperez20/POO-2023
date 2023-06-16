#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

namespace Ui {
class Producto;
}

class Producto : public QWidget
{
    Q_OBJECT

public:
    explicit Producto(QWidget *parent = nullptr);
    ~Producto();

    void setNombre( QString nombre );
    void setPrecio( QString precio );
    void setUrlImagen( QUrl url );
    void showLine();
    void hideLine();

private:
    Ui::Producto *ui;
    QImage imagenProducto;
    QNetworkAccessManager * managerImagen;

private slots:
    void slot_descargaImagenFinalizada(QNetworkReply* reply);
};

#endif // PRODUCTO_H
