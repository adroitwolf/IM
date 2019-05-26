#ifndef ADDFRIENDOP_H
#define ADDFRIENDOP_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "Json/userinfo.h"
#include "Json/hostinfo.h"
#include <QFile>

class AddFriendOp:public QObject
{
    Q_OBJECT
public:
    void dealAdd(User user,QString Id,HostInfo info);

    void dealSearch(QString qqId,HostInfo info);

    void setHostInfo(HostInfo info);
private:
    QTcpSocket *tcpSocket;
    QFile file;
    HostInfo info;

signals:

    void noSearch();

    void searchSignal(User user);


};

#endif // ADDFRIENDOP_H
