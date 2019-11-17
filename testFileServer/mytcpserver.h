#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "mytcpsocket.h"
#include "fileinfo.h"
#include "filebean.h"

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include <QTcpSocket>
#include <QByteArray>
#include <QFile>   //文件
#include <QTimer>//定时器
#include <QFileInfo>
#include <QDir>

class MyTcpServer: public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer(QObject *parent = 0,int numConnections = 10000);


protected:
    void incomingConnection(qintptr handle);


signals:
    void recvComplete(qint32 socketDescriptor);
    void ACKFiles(qint32 socketDescriptor);
    void dealDownLoad(qint32 socketDescriptor,QString fileName);
public slots:
    void receiveDataSlot(const qint32 socketDescriptor,const QByteArray buff);
    void disconnectSlot(qint32 socketDescriptor);
private:
    QThread *thread;
    QMap<qint32, QTcpSocket *> *clients;
    QMap<qint32,FileInfo> *fileInfos;
    QMap<qint32,FileBean *> *fileBeans;
};

#endif // MYTCPSERVER_H
