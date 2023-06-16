
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QNetworkAccessManager>  // Para ejecutar solicitudes GET, POST, etc
#include <QNetworkRequest>  // Contener la info que ira hacia el server
#include <QNetworkReply>  // Contiene la info que viene desde el server
#include <QUrl>

#include "ventana.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget

{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void setClima( QString data );

private:
    Ui::Login * ui;
    QNetworkAccessManager * manager;
    QNetworkAccessManager * managerClima;


    Ventana * ventana;



private slots:
    void slot_cargar_clima();
    void slot_mostrar_clima( QNetworkReply * reply);
    void slot_validar_con_API();
    void slot_descargaFinalizada( QNetworkReply * reply );
};

#endif // LOGIN_H
