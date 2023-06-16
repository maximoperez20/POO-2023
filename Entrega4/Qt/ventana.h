#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QNetworkAccessManager>  // Para ejecutar solicitudes GET, POST, etc
#include <QNetworkRequest>  // Contener la info que ira hacia el server
#include <QNetworkReply>  // Contiene la info que viene desde el server
#include <QUrl>
#include <QPainter>

#include "resultadosprod.h"

namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();
    void setUsername(QString name);


private:
    QNetworkAccessManager * manager;
    QNetworkAccessManager * managerMercadoLibre;
    QNetworkAccessManager * managerUltimaBusqueda;
    Ui::Ventana *ui;
    resultadosprod * ventanaResultados;
    QString username;

private slots:
    void slot_productosMLCargados( QNetworkReply * reply);
    void slot_verificarUltimaBusqueda( QNetworkReply * reply);
    void slot_buscarProductosML();
    void realizarUltimaBusqueda();

};

#endif // VENTANA_H
