#ifndef RESULTADOSPROD_H
#define RESULTADOSPROD_H

#include <QWidget>

namespace Ui {
class resultadosprod;
}

class resultadosprod : public QWidget
{
    Q_OBJECT

public:
    explicit resultadosprod(QWidget *parent = nullptr);
    ~resultadosprod();
    void showProductLines();
    void hideProductLines();
    void setProducto1(QString nombre, QString precio, QUrl url);
    void setProducto2(QString nombre, QString precio, QUrl url);
    void setProducto3(QString nombre, QString precio, QUrl url);
    void setProducto4(QString nombre, QString precio, QUrl url);
    void setProducto5(QString nombre, QString precio, QUrl url);

private:
    Ui::resultadosprod *ui;
};

#endif // RESULTADOSPROD_H
