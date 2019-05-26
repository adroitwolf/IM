#ifndef MAINOP_H
#define MAINOP_H

#include <QWidget>
#include <QTcpSocket>
#include <QObject>
#include "Json/user.h"
#include "Json/hostinfo.h"
#include "opreate/EnterOp.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QUdpSocket>

class MainOp:public QObject
{
     Q_OBJECT
public:
    void dealAgreeAdd(User self,User user,HostInfo info);

    void dealSend(Message msg,HostInfo info);


signals:

private slots:



private:
    QTcpSocket *tcpSocket;//通信套接字
    QUdpSocket *udpSocket;//UDP套接字



};

#endif // MAINOP_H
