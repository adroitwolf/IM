#include "mytcpsocket.h"

#pragma execution_character_set("utf-8")
MyTcpSocket::MyTcpSocket(qint32 socketDescriptor, QObject *parent):
    QTcpSocket(parent),socketID(socketDescriptor)
{
    this->setSocketDescriptor(socketDescriptor);


    connect(this,&MyTcpSocket::readyRead,[=](){ //diyici
        QByteArray buf = this->readAll();
        emit receiveData(socketDescriptor,buf);
    }); //阅读消息
    connect(this,&MyTcpSocket::disconnected,[=](){
       emit socketDisconnect(socketDescriptor);
    }); // 断开连接


}

void MyTcpSocket::sendFile()
{
    qDebug()<<"进入sendFile方法";
    sendsize = 0;
    qint64 len = 0;
    do
    {
        Sleep(100);
        //每次发送数据的大小参数设置
        char buf[1024*100] = {0};

        len = 0;
        //读数据
        len = file.read(buf,sizeof (buf));
        //发送数据
        qDebug()<<"len:"<<len;
        qDebug()<<"sendsize:"<<sendsize;
        qDebug()<<"filesize:"<<filesize;
        write(buf,len);
        //发送的数据要累加
        sendsize += len;
    }while(len > 0);

    //判断文件是否发送成功
    if(sendsize == filesize)
    {

        file.close();

        //与客户端断开
        emit socketDisconnect(this->socketID);
    }
}

void MyTcpSocket::ACKFiles(qint32 socketDescriptor)
{
    if(socketID == socketDescriptor){
        QString contain = "ACK";
        write(contain.toUtf8());
    }
}

void MyTcpSocket::dealDownload(qint32 socketDescriptor, QString filename)
{
    if(socketID == socketDescriptor){
        timer = new QTimer(this);
        connect(timer,&QTimer::timeout,
                [=](){
            //关闭定时器
            timer->stop();
            qDebug()<<"开始进入sendFile方法";
            //发送文件
            sendFile();
        });
        qDebug()<<filename;
        QFileInfo info(filename);
        this->filename = info.fileName();
        this->filesize = info.size();
        this->sendsize = 0;
        this->file.setFileName(filename);
        bool isopen = file.open(QIODevice::ReadOnly);
        if(isopen == false)
        {
            qDebug() << "只读打开文件失败";
        }
        else
        {
            timer->start(20);//防止TCP粘包
        }
    }
}

void MyTcpSocket::dealSendFile()
{
    //关闭定时器
    timer->stop();

    //发送文件
    sendFile();
}
