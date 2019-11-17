#include "MainOp.h"
#include <QHostAddress>
#include <QFileInfo>

void MainOp::dealAgreeAdd(User self,User user,HostInfo info)
{
    tcpSocket = new QTcpSocket(this);
    QJsonObject jsonObject;
        jsonObject.insert("actionType","addNewFeedBack");//加好友反馈命令

        //封装data格式
        //用户名、密码
        QJsonObject userData;
        userData.insert("requestQQ",user.getAccount());
        userData.insert("receiveQQ",self.getAccount());
        userData.insert("result","success");
        jsonObject.insert("data",QJsonValue(userData));
        //连接服务器
        tcpSocket->connectToHost(QHostAddress(info.getIp()),info.getPort().toInt());
        //发送登陆信息包给服务器
        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray msg = jsonDocument.toJson();
        tcpSocket->write(msg);
        qDebug()<<QString(msg);

}

void MainOp::dealSend(Message msg, HostInfo info)
{
    udpSocket = new QUdpSocket(this);
    QJsonObject jsonObject;
        jsonObject.insert("actionType","sendMessage");//加好友反馈命令
        //封装data格式
        //用户名、密码
        QJsonObject userData;
        userData.insert("senderQQ",msg.getSenderQQ());
        userData.insert("receiveQQ",msg.getReceviceQQ());
        userData.insert("datetime",msg.getCDate());
        userData.insert("context",msg.getContext());
        jsonObject.insert("data",QJsonValue(userData));

        //发送登陆信息包给服务器
        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray msg2 = jsonDocument.toJson();
        udpSocket->writeDatagram(msg2,QHostAddress(info.getIp()),info.getPort().toInt());
        qDebug()<<QString(msg2);
}

//void MainOp::dealSendFile(QString filepath,HostInfo info)
//{

//}
