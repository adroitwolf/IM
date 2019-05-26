#include "opreate/RegistOp.h"
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHostInfo>
#include <QDebug>
#include <QObject>
#include <QString>

#pragma execution_character_set("utf-8")

void RegistOp::DealRegist(User *user,HostInfo info)
{
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    QString qqId = "";
    //打包成json格式

    QJsonObject jsonObject;
    jsonObject.insert("actionType","register");//注册命令

    //封装data格式
    //用户名、密码、性别
    QJsonObject userData;
    userData.insert("username",user->getNickName());
    userData.insert("password",user->getPwd());
    userData.insert("sex",user->getSex());
    jsonObject.insert("data",QJsonValue(userData));

     //本机主机名
    QString localHostName = QHostInfo::localHostName();
    jsonObject.insert("desk",localHostName);

    //qDebug()<<"3";

    //主动连接服务器
    tcpSocket->connectToHost(QHostAddress(info.getIp()),info.getPort().toInt());
    //发送注册信息包给服务器
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();

    tcpSocket->write(msg);

    //读取服务器的注册结果
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                QByteArray buf = tcpSocket->readAll();
                QJsonObject json = QJsonDocument::fromJson(buf).object();
                QJsonObject subJson = json.value("data").toObject();
                QString rs = subJson["rs"].toString();
                QString Id = subJson["qqId"].toString();
                if(rs == "success")
                {
                    //qDebug()<<"4";
                    emit RegistOp::isRegist(Id);

                }
                else
                {
                    emit RegistOp::noRegist();
                }
                emit disConnect();
            });
    connect(this,&RegistOp::disConnect,
            [=]()
            {
            //断开连接
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
            });

}



