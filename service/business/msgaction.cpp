#include "msgaction.h"

#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QHostAddress>


#pragma execution_character_set("utf-8")


MsgAction::MsgAction(QByteArray data,QHostAddress sender,quint16 senderPort,QMap<QString, QString> **userList):
    data(data),sender(sender),senderPort(senderPort),userList(*userList)
{
    this->action = new Action();
}


/**
 * 转发消息服务
 * @brief MsgAction::run
 */
void MsgAction::run()
{
    qDebug()<<tr("用户想说:" )<<" buf= "<<QString(data);
    QJsonObject json = QJsonDocument::fromJson(data).object();
    QString action  =json["actionType"].toString();

    if(action == "sendMessage"){
        qDebug()<<"have message";
        QJsonObject subJson = json.value("data").toObject();
        Message msg;
        msg.setSenderQQ(subJson.value("senderQQ").toString());
        msg.setReceviceQQ(subJson.value("receiveQQ").toString());
        msg.setContext(subJson.value("context").toString());
        msg.setCDate(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        if(userList->contains(msg.getReceviceQQ())){ //说明在线
           // QUdpSocket *udp = new QUdpSocket(this);
//            udp->bind(9999);

            json.insert("actionType","receiveMsg");

            QJsonObject subJson = json.value("data").toObject();

            subJson.insert("sendTime",msg.getCDate());

            json.insert("data",subJson);

            QJsonDocument jsonDocument;
            jsonDocument.setObject(json);

            QByteArray msgData = jsonDocument.toJson();

            emit sendMessage(msgData,msg.getReceviceQQ());

            //udp->writeDatagram(msgData,QHostAddress(userList->value(msg.getReceviceQQ())),9999);
        }else{

            qDebug()<<tr("存储消息");
            this->action->storageMsg(msg);
        }
    }

}
