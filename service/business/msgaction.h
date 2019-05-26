#ifndef MSGACTION_H
#define MSGACTION_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>

#include "data/message.h"
#include "business/action.h"

/**
 * function: 处理聊天业务
 * @brief The MsgAction class
 */
class MsgAction:public QObject
{
    Q_OBJECT
public:
    MsgAction(QByteArray data,QHostAddress sender,quint16 senderPort,QMap<QString,QString> **userList);
    void run();
signals:
    void sendMessage(const QByteArray data,const QString receiveQQ);
private:
    QByteArray data;
    QHostAddress sender;
    quint16 senderPort;
    QMap<QString,QString> *userList;
    Action *action;
};

#endif // MSGACTION_H
