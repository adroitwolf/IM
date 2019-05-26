#ifndef MYUDPSERVER_H
#define MYUDPSERVER_H

#include <QUdpSocket>
#include <QObject>
#include <QThread>
#include "business/msgaction.h"
#include "data/logininfo.h"

/**
 * UDP服务端
 * @brief The MyUDPServer class
 */
class MyUDPServer:public QObject
{
      Q_OBJECT
public:
    MyUDPServer(QObject *parent = 0);
    void startService(quint16 port);
public slots:
    void readData();
    void getUserInfo(const LoginInfo loginInfo);
    void getLogoutInfo(QString qq);
    void sendMessage(const QByteArray data,const QString receiveQQ);
signals:
    void sendMessageToUser(const QByteArray data,const QString receiveQQ);
private:
    QUdpSocket *mUdpSocket;
    QMap<QString,QString> *userList;
};




#endif // MYUDPSERVER_H
