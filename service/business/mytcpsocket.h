#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include "data/hostinfo.h"
#include "data/userinfo.h"
#include "business/action.h"
#include "data/threadmysql.h"

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket( qint32 socketDescriptor,QMap<qint32,QString> **user,QMap<QString,quint32> **userCopy,QObject *parent = 0);

signals:
    void receiveData(qint32 socketDescriptor,const HostInfo &info);

    void socketDisconnect( qint32 socketDescriptor);
    void moveUserToMap(qint32 socketDescriptor,const QString qq);

public slots:
    void sendRegisterData(qint32 socketDescriptor,QString rs);
    void sendLoginData(qint32 socketDescriptor,const UserInfo info);
    void sendSearchData(qint32 socketDescriptor,const User user);
    void sendAdviceLoginOrLogOut(qint32 socketDescriptor,const QString qq,const bool status);
    void sendAddnew(quint32 socketDescriptor,const User user);
    void addFriendSuccess(qint32 socketDescriptor,const User friendL);
    void sendMessageToUser(qint32 socketDescriptor,const QByteArray data);
protected:
private:
    qintptr socketID;
    QMap<qint32,QString> *user;
//    Action *action;
    QMap<QString,quint32> *userCopy;
    ThreadMysql *action;
};

#endif // MYTCPSOCKET_H
