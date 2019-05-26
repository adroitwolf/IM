#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "business/mytcpserver.h"
#include "business/myudpserver.h"
#include "data/dbutil.h"

#include <QWidget>
#include <QThread>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void setLog(QString log,bool status);

private slots:
    void on_startService_clicked();
    void on_stopService_clicked();
    void display_account(bool);


private:
    Ui::MainWidget *ui;
    MyTcpServer *myServer;
    MyUDPServer *udpServer;
};

#endif // MAINWIDGET_H
