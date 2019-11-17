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
//#include <QTimer>
#include <QFile>
#include <windows.h>


class MainOp:public QObject
{
     Q_OBJECT
public:
    void dealAgreeAdd(User self,User user,HostInfo info);

    void dealSend(Message msg,HostInfo info);

//    void dealSendFile(QString filepath,HostInfo info);//发送文件


signals:

private slots:


private:
    QTcpSocket *tcpSocket;//通信套接字
    QUdpSocket *udpSocket;//UDP套接字

//    QFile file; //文件对象
//    QString filename;//文件名
//    qint64 filesize;//文件大小
//    qint64 sendsize;//发送大小

//    QTimer timer;//定时器
};

#endif // MAINOP_H
