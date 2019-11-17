#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "mytcpserver.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void dealDownLoad();
    void sendFile();

private slots:
    void on_startService_clicked();

    void on_stopService_clicked();

private:
    Ui::Widget *ui;
    MyTcpServer *server;

};

#endif // WIDGET_H
