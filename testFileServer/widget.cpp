#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stopService->setEnabled(false);



}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startService_clicked()
{
    //获取端口号
    QString portString = this->ui->port->text();

    bool ok;

    quint16 port = portString.toInt(&ok,10);


    if(!ok){
        QMessageBox::critical(NULL,"错误","端口错误！请输入正确的端口号",QMessageBox::Yes);
        return ;
    }
    server = new MyTcpServer(this);

    server->listen(QHostAddress::Any,port);
    ui->startService->setEnabled(false);
    ui->stopService->setEnabled(true);

}

void Widget::on_stopService_clicked()
{
    ui->startService->setEnabled(true);
    ui->stopService->setEnabled(false);
    server->destroyed();
}
