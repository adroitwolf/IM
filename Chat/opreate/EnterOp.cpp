#include "opreate/EnterOp.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QHostAddress>
#include <QVariantMap>
#include <QJsonArray>
#include "mainwidget.h"
#include <QDebug>


#pragma execution_character_set("utf-8")

void EnterOp::dealEnter(User user,HostInfo info)
{
    //初始化通信套接字
    tcpSocket = new QTcpSocket(this);
    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","login");//登陆命令

    //封装data格式
    //用户名、密码
    QJsonObject userData;
    userData.insert("qq",user.getAccount());
    userData.insert("password",user.getPwd());
    jsonObject.insert("data",QJsonValue(userData));
    //连接服务器
    tcpSocket->connectToHost(QHostAddress(info.getIp()),info.getPort().toInt());
    //发送登陆信息包给服务器
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();
    tcpSocket->write(msg);
    //读取服务器的登陆结果
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                QByteArray buf = tcpSocket->readAll();
                qDebug()<<QString(buf);

                QJsonObject json = QJsonDocument::fromJson(buf).object();
                if(json["actionType"].toString() == "login")
                {
                    QJsonObject subJson = json.value("data").toObject();//subJson-->data

                    QString rs = subJson["rs"].toString();
                    if(rs == "success")
                    {
                        UserInfo userInfo;
                        //打包获取的信息入个人信息类
                        QJsonObject subJsonSelf = subJson.value("self").toObject();
                        QList<Message> messageList;
                        User self;
                        self.setNickName(subJsonSelf["username"].toString());
                        self.setAccount(subJsonSelf["qq"].toString());
                        self.setSign(subJsonSelf["sign"].toString());
                        self.setSex(subJsonSelf["sex"].toString());
                        self.setStatus(subJsonSelf["status"].toString());
                        userInfo.setUser(self);

                        QJsonArray friendsJson = subJson.value("friends").toArray();
                        QJsonArray requestJson = subJson.value("addRequests").toArray();
                        QJsonArray messageJson = subJson.value("messages").toArray();

                        if(friendsJson.empty() == 0)
                        {
                            QList<User> friends;
                            for (int i = 0; i < friendsJson.size(); ++i)
                            {                                
                                QJsonObject friendLJson = friendsJson.at(i).toObject();
                                User friendL;
                                friendL.setAccount(friendLJson["qq"].toString());
                                friendL.setNickName(friendLJson["username"].toString());
                                friendL.setStatus(friendLJson["status"].toString());
                                friends.append(friendL);
                                userInfo.setFriends(friends);
                            }
                        }

                        if(requestJson.empty() == 0)
                        {
                            QList<User> addRequest;
                            for (int i = 0; i < requestJson.size(); ++i) {
                                QJsonObject requestLJson = requestJson.at(i).toObject();
                                User requestL;
                                requestL.setAccount(requestLJson["requestQQ"].toString());
                                requestL.setNickName(requestLJson["requestUsername"].toString());
                                requestL.setSex(requestLJson["requestSex"].toString());
                                requestL.setSign(requestLJson["requestSign"].toString());
                                requestL.setStatus(requestLJson["requestStatus"].toString());
                                addRequest.append(requestL);
                                userInfo.setAddRequest(addRequest);
                            }
                        }

                        if(messageJson.empty() == 0)
                        {

                            for (int i = 0;i<messageJson.size();i++) {
                                QJsonObject messageLJson = messageJson.at(i).toObject();
                                Message messageL;
                                messageL.setContext(messageLJson["context"].toString());
                                messageL.setCDate(messageLJson["CDate"].toString());
                                messageL.setSenderQQ(messageLJson["senderQQ"].toString());
                                messageL.setReceviceQQ(userInfo.getUser().getAccount());
                                messageList.append(messageL);
                            }

                        }
                        emit EnterOp::isEntered(userInfo);//发送带有个人信息的信号
                        emit EnterOp::outlineMessage(messageList);
                    }
                    else if(rs == "failed")
                    {
                        emit EnterOp::noEntered();
                    }
                    else
                    {
                        emit EnterOp::errorEntered();
                    }
                }
                else if(json["actionType"].toString() == "addNewFeedBack")//自己请求已经被同意
                {
                    QJsonObject subJson = json.value("data").toObject();
                    User newFriend;
                    newFriend.setAccount(subJson["friendQQ"].toString());
                    newFriend.setNickName(subJson["friendUsername"].toString());
                    newFriend.setSex(subJson["friendSex"].toString());
                    newFriend.setSign(subJson["friendSign"].toString());
                    newFriend.setStatus(subJson["friendStatus"].toString());
                    emit isAddNew(newFriend);
                }
                else if(json["actionType"].toString() == "adviceLoginOrLogout")
                {
                    QJsonObject subJson = json.value("data").toObject();
                    QString status = subJson["status"].toString();
                    QString qq = subJson["qq"].toString();
                    emit loginAndLogout(qq,status);
                }
                else if(json["actionType"].toString() == "receiveMsg")
                {
                    QJsonObject subJson = json.value("data").toObject();
                    Message msg;
                    msg.setSenderQQ(subJson["senderQQ"].toString());
                    msg.setCDate(subJson["datetime"].toString());
                    msg.setReceviceQQ(subJson["receiveQQ"].toString());
                    msg.setContext(subJson["context"].toString());
                    emit messageSignal(msg);
                }
                else if(json["actionType"].toString() == "addnew")
                {
                    QJsonObject subJson = json.value("data").toObject();
                    User newFriend;
                    newFriend.setAccount(subJson["reQuestqq"].toString());
                    newFriend.setNickName(subJson["requestUsername"].toString());
                    newFriend.setSex(subJson["requestSex"].toString());
                    newFriend.setSign(subJson["requestSign"].toString());
                    newFriend.setStatus(subJson["requestStatus"].toString());
                    emit nowAddNew(newFriend);
                }


            });
    connect(this,&EnterOp::disConnect,
            [=]()
            {
            //断开连接
            tcpSocket->disconnectFromHost();
            tcpSocket->close();
            });
}
