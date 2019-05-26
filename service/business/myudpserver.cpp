#include "myudpserver.h"
#pragma execution_character_set("utf-8")

/**
 * function:监听端口
 * @brief MyUDPServer::startService
 */
void MyUDPServer::startService(quint16 port)
{
    this->mUdpSocket = new QUdpSocket(this);
    int error =this->mUdpSocket->bind(QHostAddress::Any,port);
    qDebug()<<error;
    QObject::connect(mUdpSocket,SIGNAL(readyRead()),this,SLOT(readData()));

}


MyUDPServer::MyUDPServer(QObject *parent):QObject(parent)
{
    this->userList = new QMap<QString,QString>();
}


/**
 * function: 多线程读取数据
 * @brief MyUDPServer::readData
 */
void MyUDPServer::readData()
{
    while(this->mUdpSocket->hasPendingDatagrams()){
        //获取数据
        QByteArray array;
        QHostAddress address;
        quint16 port;
        //array.resize(this->mUdpSocket->bytesAvailable());//根据可读数据来设置空间大小
        array.resize(this->mUdpSocket->pendingDatagramSize());

        this->mUdpSocket->readDatagram(array.data(),array.size(),&address,&port); //读取数据

        //创建线程
        MsgAction *msgAction = new MsgAction(array,address,port,&userList);
        QThread *thread = new QThread(msgAction);

        QObject::connect(msgAction,&MsgAction::sendMessage,this,&MyUDPServer::sendMessage);

        //需要封装

        qDebug()<<QThread::currentThread();
        //移动到线程中
        msgAction->moveToThread(thread);

        thread->start();
        msgAction->run();



    }



}

/**
 * function:获得用户上线消息
 * @brief MyUDPServer::getLoginInfo
 * @param loginInfo
 */
void MyUDPServer::getUserInfo(const LoginInfo loginInfo)
{

    this->userList->insert(loginInfo.getQQ(),loginInfo.getIp());

}

/**
 * function :某人已经下线
 * @brief MyUDPServer::getLogoutInfo
 * @param qq
 */
void MyUDPServer::getLogoutInfo(QString qq)
{
    this->userList->remove(qq);
}


/**
 * function: 给用户转发消息
 * @brief MyUDPServer::sendMessage
 * @param data
 * @param receiveQQ
 */
void MyUDPServer::sendMessage(const QByteArray data, const QString receiveQQ)
{
    emit sendMessageToUser(data,receiveQQ);
}
