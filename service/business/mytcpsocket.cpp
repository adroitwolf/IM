#include "business/mytcpsocket.h"


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QHostAddress>
#include <QMetaType>

#pragma execution_character_set("utf-8")

MyTcpSocket::MyTcpSocket( qint32 socketDescriptor,QMap<qint32,QString> **user,QMap<QString,quint32> **userCopy,QObject *parent) :
    QTcpSocket(parent),socketID(socketDescriptor),userCopy(*userCopy)
{
    this->setSocketDescriptor(socketDescriptor);
    this->user = *user;
//    this->action = new Action();
    this->action = new ThreadMysql(socketDescriptor,this);
    connect(this,&MyTcpSocket::readyRead,[=](){
        HostInfo host;
        qRegisterMetaType<HostInfo>("HostInfo");

        host.setData(this->readAll());
        host.setIp(this->peerAddress().toString());
        host.setPort(QString::number(this->peerPort()));
        emit receiveData(socketDescriptor,host);
    }); //阅读消息
    connect(this,&MyTcpSocket::disconnected,[=](){
       emit socketDisconnect(socketDescriptor);
    }); // 断开连接
     

}

/**
 * function:注册用户模块返回给客户端数据
 * @brief MyTcpSocket::sendRegisterData
 * @param socketDescriptor
 * @param rs
 */
void MyTcpSocket::sendRegisterData(qint32 socketDescriptor,QString qqId)
{
    if(socketID == socketDescriptor){
        //打包成json格式
       QJsonObject jsonObject;
       jsonObject.insert("actionType","register");

       //封装data格式
       QJsonObject data;
       data.insert("rs",qqId.isEmpty() ?"failed": "success");
       data.insert("qqId",qqId);

        jsonObject.insert("data",QJsonValue(data));



       QJsonDocument jsonDocument;
       jsonDocument.setObject(jsonObject);

       QByteArray msg = jsonDocument.toJson();

        write(msg);
    }
}

/**
 * function:登陆用户模块返回给客户端数据
 * @brief MyTcpSocket::sendLoginData
 * @param socketDescriptor
 * @param info
 */
void MyTcpSocket::sendLoginData(qint32 socketDescriptor, const UserInfo info)
{

    if(socketID == socketDescriptor){
        //打包json格式
        QJsonObject jsonObject;
        jsonObject.insert("actionType","login");

        //封装data格式
        QJsonObject data;
        data.insert("rs",info.getInfo());

        if(!info.getUser().getNickName().isEmpty()){

            //给服务器发通知 让其他人知道他上线

            emit moveUserToMap(socketDescriptor,info.getUser().getqq());

            QJsonObject self;
            self.insert("qq",info.getUser().getqq());
            self.insert("username",info.getUser().getNickName());
            qDebug()<<info.getUser().getSign();
            self.insert("sign",info.getUser().getSign());
            self.insert("status",1); //1-在线 0-离线
            self.insert("sex",info.getUser().getSex());

            data.insert("self",QJsonValue(self));



            if(!info.getFriends().isEmpty()){ //判断是否有好友
                QJsonArray friends;
                foreach(User selfFriend,info.getFriends()){
                    QJsonObject friend1;
                    friend1.insert("qq",selfFriend.getqq());
                    friend1.insert("status",selfFriend.getStatus());
                    friend1.insert("username",selfFriend.getNickName());

                    friends.append(friend1);
                }
               data.insert("friends",friends);
            }




            if(!info.getMessage().isEmpty()){ //判断是否有离线消息
                QJsonArray messages;
                foreach(Message msg,info.getMessage()){
                    QJsonObject msg1;
                    msg1.insert("context",msg.getContext());
                    msg1.insert("senderQQ",msg.getSenderQQ());
                    msg1.insert("CDate",msg.getCDate());

                    messages.append(msg1);
                }
                data.insert("messages",messages);
            }

            if(!info.getAddRequest().isEmpty()){ //判断离线是否有好友请求
                QJsonArray addRequests;
                foreach(User user,info.getAddRequest()){
                    QJsonObject addRequest;
                    addRequest.insert("requestQQ",user.getqq());
                    addRequest.insert("requestUsername",user.getNickName());
                    addRequest.insert("requestSex",user.getSex());
                    addRequest.insert("requestSign",user.getSign());
                    addRequest.insert("requestStatus",this->userCopy->contains(user.getqq())?"1":"0");
                    addRequests.append(addRequest);
                }
                data.insert("addRequests",addRequests);

            }
        }


       jsonObject.insert("data",data);

        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);

        QByteArray msg = jsonDocument.toJson();

        qDebug()<<QString(msg);

         write(msg);

    }


}



/**
 * function: 发送给客户端查询消息
 * @brief MyTcpSocket::sendSearchData
 * @param socketDescriptor
 * @param user
 */
void MyTcpSocket::sendSearchData(qint32 socketDescriptor, const User user)
{
    if(socketID == socketDescriptor){
        //打包成json格式
       QJsonObject jsonObject;
       jsonObject.insert("actionType","search");

       //封装data格式
       QJsonObject data;
       data.insert("rs",user.getNickName().isEmpty() ?"failed": "success");

       data.insert("qq",user.getqq());
       data.insert("username",user.getNickName());
       data.insert("sign",user.getSign());
       data.insert("sex",user.getSex());

        jsonObject.insert("data",data);



       QJsonDocument jsonDocument;
       jsonDocument.setObject(jsonObject);

       QByteArray msg = jsonDocument.toJson(QJsonDocument::Compact);
        qDebug()<<QString(msg);
        write(msg);
    }
}



/**
 * function: 通知其他人上线
 * @brief MyTcpSocket::sendAdviceLogin
 * @param socketDescriptor
 * @param qq
 */
void MyTcpSocket::sendAdviceLoginOrLogOut(qint32 socketDescriptor,const QString qq ,const bool status)
{


    if((socketDescriptor!= socketID) && (this->user->contains(socketID))){


        QString selfQQ = this->user->value(socketID);
        //查询自己好友有没有这个人



        if(action->searchFriend(qq,selfQQ)){
            QJsonObject jsonObject;
            jsonObject.insert("actionType","adviceLoginOrLogout");
            //封装data格式
            QJsonObject data;
            data.insert("qq",qq);
            data.insert("status",status?"1":"0");
            jsonObject.insert("data",QJsonValue(data));

           QJsonDocument jsonDocument;
           jsonDocument.setObject(jsonObject);

           QByteArray msg = jsonDocument.toJson();
           qDebug()<<QString(msg);
            write(msg);
        }
    }
}



/**
 * function: 给用户发添加好友通知
 * @brief MyTcpSocket::sendAddnew
 * @param socketDescriptor
 * @param qq
 */
void MyTcpSocket::sendAddnew(quint32 socketDescriptor, const User user)
{
    if(socketID == socketDescriptor){
        //打包成json格式
       QJsonObject jsonObject;
       jsonObject.insert("actionType","addnew");

       //封装data格式
       QJsonObject data;

        data.insert("reQuestqq",user.getqq());
        data.insert("requestUsername",user.getNickName());
        data.insert("requestSex",user.getSex());
        data.insert("requestSign",user.getSign());
        data.insert("requestStatus","1");
        jsonObject.insert("data",data);



       QJsonDocument jsonDocument;
       jsonDocument.setObject(jsonObject);

       QByteArray msg = jsonDocument.toJson(QJsonDocument::Compact);
        qDebug()<<QString(msg);
        write(msg);
    }
}

/**
 * function:  告诉用户添加好友成功
 * @brief MyTcpSocket::addFriendSuccess
 * @param socketDescriptor
 * @param friendL
 */
void MyTcpSocket::addFriendSuccess(qint32 socketDescriptor, const User friendL)
{
    if(socketID == socketDescriptor){
        //打包成json格式
       QJsonObject jsonObject;
       jsonObject.insert("actionType","addNewFeedBack");

       //封装data格式
       QJsonObject data;

        data.insert("friendQQ",friendL.getqq());
        data.insert("friendUsername",friendL.getNickName());
        data.insert("friendSex",friendL.getSex());
        data.insert("friendSign",friendL.getSign());
        data.insert("friendStatus",this->userCopy->contains(friendL.getqq())?"1":"0");

        jsonObject.insert("data",data);



       QJsonDocument jsonDocument;
       jsonDocument.setObject(jsonObject);

       QByteArray msg = jsonDocument.toJson(QJsonDocument::Compact);
        qDebug()<<QString(msg);
        write(msg);
    }
}

/**
 * function: 给好友发信息
 * @brief MyTcpSocket::sendMessageToUser
 * @param socketDescriptor
 * @param data
 */
void MyTcpSocket::sendMessageToUser(qint32 socketDescriptor, const QByteArray data)
{
    if(socketID == socketDescriptor){
        qDebug()<<QString(data);
        write(data);
    }
}
