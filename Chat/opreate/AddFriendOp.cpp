#include "opreate/AddFriendOp.h"
#include <QHostAddress>

#pragma execution_character_set("utf-8")

void AddFriendOp::dealAdd(User user, QString Id,HostInfo info)
{
    tcpSocket = new QTcpSocket(this);
    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","addnew");//登陆命令

    //封装data
    //用户名、密码
    QJsonObject userData;
    userData.insert("userQqId",Id);
    userData.insert("selfQqId",user.getAccount());
    qDebug()<<user.getAccount();
    jsonObject.insert("data",QJsonValue(userData));

    //连接服务器
    tcpSocket->connectToHost(QHostAddress(info.getIp()),info.getPort().toInt());
    //发送注册信息包给服务器
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();
    tcpSocket->write(msg);
    qDebug()<<QString(msg);
}

void AddFriendOp::dealSearch(QString qqId,HostInfo info)
{
    tcpSocket = new QTcpSocket(this);
    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","search");//搜索命令

    //封装data
    //id号
    QJsonObject userData;
    userData.insert("qq",qqId);
    jsonObject.insert("data",QJsonValue(userData));

    //连接服务器
    tcpSocket->connectToHost(QHostAddress(info.getIp()),info.getPort().toInt());
    //发送注册信息包给服务器
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();
    tcpSocket->write(msg);
    //接收反馈的搜索信息
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                QByteArray buf = tcpSocket->readAll();
                qDebug()<<QString(buf);

                QJsonObject json = QJsonDocument::fromJson(buf).object();
                if(json["actionType"].toString() == "search")
                {
                    QJsonObject subJson = json.value("data").toObject();//subJson-->data

                    QString rs = subJson["rs"].toString();
                    if(rs == "success")
                    {
                        User user;
                        user.setNickName(subJson["username"].toString());
                        user.setAccount(subJson["qq"].toString());
                        user.setSex(subJson["sex"].toString());
                        user.setSign(subJson["sign"].toString());
                        emit searchSignal(user);
                        qDebug()<<"search over";
                    }
                    else
                    {
                        emit noSearch();
                    }
                }
            });
}
