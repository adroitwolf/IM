#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QFile>   //文件
#include <QTimer>//定时器
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileInfo>
#include <windows.h>
class MyTcpSocket: public QTcpSocket
{
    Q_OBJECT
public:
    MyTcpSocket( qint32 socketDescriptor,QObject *parent = 0);
    void sendFile();
signals:
    void receiveData(qint32 socketDescriptor,const QByteArray buff);
    void socketDisconnect( qint32 socketDescriptor);
public slots:
    void ACKFiles(qint32 socketDescriptor);
    void dealDownload(qint32 socketDescriptor,QString filename);
    void dealSendFile();
private:
    qintptr socketID;
    QFile file;
    QTimer *timer;//定时器
    qint64 sendsize;//发送大小
    QString filename;//文件名
    qint64 filesize;//文件大小
};

#endif // MYTCPSOCKET_H
