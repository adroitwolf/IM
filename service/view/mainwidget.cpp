#include "view/mainwidget.h"
#include "ui_mainwidget.h"
#include "data/dbutil.h"

#include <QDebug>
#include <QHostAddress>
#include <QDataStream>
#include <QByteArray>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMapIterator>
#include <QVariant>
#include <QMessageBox>
#include <QDateTime>
#include <QThread>

#pragma execution_character_set("utf-8")

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{



    ui->setupUi(this);
    ui->stopService->setEnabled(false);
    this->ui->status->setStyleSheet("color:black");
    this->ui->status->setText("未开启服务");

}

MainWidget::~MainWidget()
{
    delete ui;

}

/**
 * function: 设置日志
 * @brief MainWidget::setLog
 * @param log 打印日志
 * @param status true 绿色字体/false 红色字体
 */
void MainWidget::setLog(QString log,bool status)
{
    QString LStatus = status ? "green" : "red";
    this->ui->logshow->appendHtml("<br/>----------------------<br/>");
    this->ui->logshow->appendHtml("<span>"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+"</span>");
    this->ui->logshow->appendHtml("<span style='color:"+ LStatus+"'>"+log +"</span>");
    this->ui->logshow->appendHtml("<br/>");



}

/**
 * function :开启服务
 * @brief MainWidget::on_startService_clicked
 */
void MainWidget::on_startService_clicked()
{
    //获取端口号
    QString portString = this->ui->port->text();

    bool ok;

    quint16 port = portString.toInt(&ok,10);


    if(!ok){
        QMessageBox::critical(NULL,"错误","端口错误！请输入正确的端口号",QMessageBox::Yes);
        return ;
    }

    // 启动TCP
    myServer = new MyTcpServer(this);

    myServer->listen(QHostAddress::Any,port);
    connect(myServer,SIGNAL(displayAccount(bool)),this,SLOT(display_account(bool)));
    //启动UDP
    udpServer = new MyUDPServer(this);
    udpServer->startService(port);


    //这里给udp上线人的信息
    connect(myServer,&MyTcpServer::adviceUdpLoginInfo,udpServer,&MyUDPServer::getUserInfo);
    connect(myServer,&MyTcpServer::adviceUdpLogoutInfo,udpServer,&MyUDPServer::getLogoutInfo);
    connect(udpServer,&MyUDPServer::sendMessageToUser,myServer,&MyTcpServer::sendMessage);

    ui->startService->setEnabled(false);
    ui->stopService->setEnabled(true);

    //初始化数据库

    DBUtil *db = new DBUtil();
    bool rs = db->initDatabase();
    db->release(); //释放数据库
    this->ui->status->setStyleSheet("color:green");
    this->ui->status->setText("已开启服务");


    //开启服务提示
    setLog("服务开启成功！",true);
}

/**
 * function:停止服务
 * @brief MainWidget::on_stopService_clicked
 */
void MainWidget::on_stopService_clicked()
{
    ui->startService->setEnabled(true);
    ui->stopService->setEnabled(false);
    myServer->destroyed();
    udpServer->destroyed();
    this->ui->status->setStyleSheet("color:black");
    this->ui->status->setText("未开启服务");
    //关闭服务提示
    setLog("服务已关闭！",false);

}

/**
 * function:有新增用户
 * @brief MainWidget::insertAccount
 */
void MainWidget::display_account(bool rs)
{

    int courrent_account = this->ui->onlineUserNum->intValue();
    courrent_account = rs ? courrent_account+1 : courrent_account-1;

    this->ui->onlineUserNum->display(courrent_account);
}





