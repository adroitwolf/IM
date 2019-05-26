#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "business/action.h"
#include "business/mytcpsocket.h"
#include "data/datainfo.h"
#include "data/user.h"
#include "data/hostinfo.h"
#include "data/addfriend.h"
#include "data/logininfo.h"


#include <QObject>
#include <QTcpServer>
#include <QMap>
#include <QTcpSocket>
#include <QByteArray>



/**
 * function: Tcp线程类
 * @brief The MyTcpServer class
 */
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0,int numConnections = 10000);

signals:
    void readData(); //解析数据包
    void displayAccount(const bool);
    void sendRegisterData(qint32 socketDescriptor,const QString rs); //发送注册后数据
    void sendLoginData(qint32 socketDescriptor,const UserInfo info);

    void sendSearchData(qint32 socketDescriptor,const User user);
    void someoneLogin(QString qq); //通知其他人该用户上线
    void adviceLoginOrLogout(qint32 socketDescriptor,const QString qq,const bool status);

    void adviceUdpLoginInfo(const LoginInfo loginInfo);
    void adviceUdpLogoutInfo(const QString qq);

    void sendAddnew(qint32 socketDescriptor,const User user);

    void addFriendSuccess(qint32 socketDescriptor,const User friendL);

    void sendMessageToUser(qint32 socketDescriptor,const QByteArray data);


public slots:
    void receiveDataSlot(const qint32 socketDescriptor,const HostInfo &info);
    void disconnectSlot(qint32 socketDescriptor);
    void moveUserToMapSolt(qint32 socketDescriptor,QString qq);
    void sendMessage(const QByteArray data,const QString receiveQQ);


protected:
    void incomingConnection(qintptr handle);
private:
    QMap<qint32, QTcpSocket *> *clients;
    QMap<qint32,QString> *user;  //管理在线线程
    QMap<QString,quint32> *userCopy; //根据qq查询tcp线程
    QThread *thread;
    Action *action;
};

#endif // MYTCPSERVER_H
