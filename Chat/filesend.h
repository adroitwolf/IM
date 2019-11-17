#ifndef FILESEND_H
#define FILESEND_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>   //文件
#include <QTimer>//定时器
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QJsonObject>
#include "Json/hostinfo.h"
#include "Json/userinfo.h"
#include "Json/filedata.h"

namespace Ui {
class FileSend;
}

class FileSend : public QWidget
{
    Q_OBJECT

public:
    explicit FileSend(QWidget *parent = nullptr);
    ~FileSend();

    void setFilePath(QString path){
        this->filePath = path;
    }

    void requestSend();//文件传输随机码请求

    void setUserInfo(User info){this->currentFrdInfo = info;}

    void setHostInfo(HostInfo info){this->hInfo = info;}

    void setSelfInfo(User info){this->selfInfo = info;}

    void dealSend(QString code);//处理发文件函数

//    void dealRefuse();

    void sendFile();//文件发送过程函数

    void agreeReceiveRequest(FileDate fileData);//同意对方请求

    void refuseReceiveRequest(FileDate fileData);//拒绝对方请求

signals:
    void sendOver();

    void agreeReceive();

    void refuseReceive();


    void requestReceive();

    void fileSizeOverLoad();

    void receivedBuf(QByteArray buf);

private slots:

    void fileReceive(QByteArray buf);

private:
    qint32 receiveSize;
    Ui::FileSend *ui;

    QTcpSocket *tcpSocket;//通信套接字
    QTcpSocket *fileTcpSocket;//文件传输套接字
    QTcpSocket *receiveTcpSocket;//文件接收套接字

    User currentFrdInfo;//用户信息
    HostInfo hInfo;//服务器信息
    User selfInfo;//自己的信息
    QFile recvFile;
    QString filePath; //文件地址
    QFile file; //文件对象
    QFile *receiveFile;//接收文件对象
    QString filename;//文件名
    QString receiveFileName;//接收文件名
    qint64 receiveFileSize;//接收文件大小
    qint64 filesize;//文件大小
    qint64 sendsize;//发送大小
    QString senderName;//发送者昵称
    bool isHead;//文件头判断

    QString oldName;//旧文件名
    QString newName;//新文件名
    QString UUID;//随机码

    QTimer timer;//定时器
};

#endif // FILESEND_H
