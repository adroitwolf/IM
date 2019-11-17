#include "mytcpserver.h"

#include <QDebug>
#include <QThread>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#pragma execution_character_set("utf-8")
MyTcpServer::MyTcpServer(QObject *parent,int numConnections) : QTcpServer(parent){
    clients = new QMap< qint32, QTcpSocket *> ();
    fileInfos = new QMap<qint32,FileInfo>();
    fileBeans = new QMap<qint32,FileBean*>();
}



void MyTcpServer::incomingConnection(qintptr handle)
{
     qDebug()<<tr("有新的连接 :-socketDescriptor-")<<handle;

     MyTcpSocket *tcptemp = new MyTcpSocket(handle);


     QThread *thread = new QThread(tcptemp);


     //收到客户端发送的信息
     connect(tcptemp,&MyTcpSocket::receiveData,this,&MyTcpServer::receiveDataSlot);

     //允许客户端发送文件
     connect(this,&MyTcpServer::ACKFiles,tcptemp,&MyTcpSocket::ACKFiles);

     connect(this,&MyTcpServer::recvComplete,this,&MyTcpServer::disconnectSlot);


     connect(this,&MyTcpServer::dealDownLoad,tcptemp,&MyTcpSocket::dealDownload);
     //客户端断开链接
     connect(tcptemp,&MyTcpSocket::socketDisconnect,this,&MyTcpServer::disconnectSlot);

     //客户端断开链接 关闭线程
     connect(tcptemp,&MyTcpSocket::disconnected,thread,&QThread::quit);
     //向socket发送信息

     tcptemp->moveToThread(thread);

     thread->start();

     clients->insert(handle,tcptemp);

     qDebug()<<tr("目前客户端数量：")<<clients->size();

}

void MyTcpServer::receiveDataSlot(const qint32 socketDescriptor, const QByteArray buff)
{

     qDebug()<<"客户端说:"<<QString(buff);
    if(!fileInfos->contains(socketDescriptor)){ //说明此时发送的是json文件
        QJsonObject json = QJsonDocument::fromJson(buff).object();
        QString action = json["actionType"].toString();

        if(action == "fileSendReq"){ //请求上传文件

            QJsonObject subJson = json.value("data").toObject();
            FileInfo fileinfo;
            fileinfo.setFileName(subJson["fileName"].toString());

            fileinfo.setFileSize(subJson["fileSize"].toInt());
            FileBean *fileBean = new FileBean(fileinfo.getFileName(),fileinfo.getFileSize());
            fileBeans->insert(socketDescriptor,fileBean);
            fileInfos->insert(socketDescriptor,fileinfo);
            emit ACKFiles(socketDescriptor);
        }else if(action == "downLoad"){ //这里是客户端请求下载文件
            qDebug()<<"有人要下载";
            QJsonObject subJson = json.value("data").toObject();
            emit dealDownLoad(socketDescriptor,subJson["UUID"].toString());
        }


    }else{ //说明此事发送的是文件
        qDebug()<<"此时发送文件";
        FileInfo fileInfo = fileInfos->value(socketDescriptor);

        FileBean *fileBean = fileBeans->value(socketDescriptor);
        fileBean->recvFile(buff);
        if(fileBean->isRecvOver()){
            qDebug()<<"发送完毕";
            fileBean->functionOver();
            emit recvComplete(socketDescriptor);
        }




    }
}



/**
 * function:tcp下线操作
 * @brief MyTcpServer::disconnectSlot
 * @param socketDescriptor
 */
void MyTcpServer::disconnectSlot( qint32 socketDescriptor)
{

    if(fileBeans->contains(socketDescriptor)){
        FileBean *fileBean = fileBeans->value(socketDescriptor);
        if(!fileBean->isRecvOver()){
            fileBean->closeFile();
        }
        fileBeans->remove(socketDescriptor);
    }

    if(fileInfos->contains(socketDescriptor)){
        fileInfos->remove(socketDescriptor);
    }

    int i = clients->remove(socketDescriptor);

    qDebug()<<tr("删除客户端   i=")<<i;


}

