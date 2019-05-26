#include "business/mytcpserver.h"


#include <QDebug>
#include <QThread>

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>


#pragma execution_character_set("utf-8")

/**
 * function :启动TCP服务
 * @brief MyTcpServer::MyTcpServer
 * @param parent
 * @param numConnections
 */
MyTcpServer::MyTcpServer(QObject *parent,int numConnections) : QTcpServer(parent)
{
    clients = new QMap< qint32, QTcpSocket *> ();
    user = new QMap<qint32,QString>();
    userCopy = new QMap<QString,quint32>();



    action = new Action();

    qRegisterMetaType<User>("User");
    qRegisterMetaType<QMap<qint32,QString>>("QMap<qint32,QString>");

    qRegisterMetaType<UserInfo>("UserInfo");
}

void MyTcpServer::incomingConnection( qint32 socketDescriptor)
{
    qDebug()<<tr("有新的连接 :-socketDescriptor-")<<socketDescriptor;



    MyTcpSocket *tcptemp = new MyTcpSocket(socketDescriptor,&user,&userCopy);


    QThread *thread = new QThread(tcptemp);




    //收到客户端发送的信息
    connect(tcptemp,&MyTcpSocket::receiveData,this,&MyTcpServer::receiveDataSlot);

    //客户端断开链接
    connect(tcptemp,&MyTcpSocket::socketDisconnect,this,&MyTcpServer::disconnectSlot);



    //客户端断开链接 关闭线程
    connect(tcptemp,&MyTcpSocket::disconnected,thread,&QThread::quit);
    //向socket发送信息

    // 发送注册信息
    connect(this,&MyTcpServer::sendRegisterData,tcptemp,&MyTcpSocket::sendRegisterData);

    //发送登陆信息
    connect(this,&MyTcpServer::sendLoginData,tcptemp,&MyTcpSocket::sendLoginData);

    //发送查询信息
    connect(this,&MyTcpServer::sendSearchData,tcptemp,&MyTcpSocket::sendSearchData);

    //用户登陆
    connect(tcptemp,&MyTcpSocket::moveUserToMap,this,&MyTcpServer::moveUserToMapSolt);

    //通知用户加好友
    connect(this,&MyTcpServer::sendAddnew,tcptemp,&MyTcpSocket::sendAddnew);

    //用户上线下通知
    connect(this,&MyTcpServer::adviceLoginOrLogout,tcptemp,&MyTcpSocket::sendAdviceLoginOrLogOut);


    //告诉用户添加好友成功
    connect(this,&MyTcpServer::addFriendSuccess,tcptemp,&MyTcpSocket::addFriendSuccess);


    //发送消息
    connect(this,&MyTcpServer::sendMessageToUser,tcptemp,&MyTcpSocket::sendMessageToUser);

    tcptemp->moveToThread(thread);

    thread->start();

    clients->insert(socketDescriptor,tcptemp);

    qDebug()<<tr("目前客户端数量：")<<clients->size();
}


/**
 * function: 解析数据包
 * @brief MyTcpServer::receiveDataSlot
 * @param socketDescriptor
 * @param buf
 */
void MyTcpServer::receiveDataSlot(const qint32 socketDescriptor,const HostInfo &info)
{
    //根据数据actionType 类型判断客服端行为
    //{\"actionType\":\"login\",\"data\":{\"name\":\"小明\",\"pwd\":\"123456\"}}


    qDebug()<<tr("客户端说:" )<<" buf= "<<QString(info.getData());
    QJsonObject json = QJsonDocument::fromJson(info.getData()).object();
    QString action  =json["actionType"].toString();
    
    HostInfo hostInfo;
    hostInfo.setDesk(json["desk"].toString());
    hostInfo.setIp(info.getIp());
    hostInfo.setPort(info.getPort());



    //登陆行为
    if(action == "register"){

        QJsonObject subJson = json.value("data").toObject();

        //封装user数据
        User user;

        user.setNickName(subJson["username"].toString());

        user.setPwd(subJson["password"].toString());

        user.setSex(subJson["sex"].toString());

        QString sign = subJson["sign"].toString().isEmpty() ? "这个人很懒，什么也没有留下.":subJson["sign"].toString();
        user.setSign(sign);



        QString qqId = this->action->registerAction(user,hostInfo);

        //传送信号
        emit sendRegisterData(socketDescriptor,qqId);

    }else if(action == "login"){ //登陆业务
        QJsonObject subJson = json.value("data").toObject();

        //封装user数据
        User user;
        user.setqq(subJson["qq"].toString());
        user.setPwd(subJson["password"].toString());
        UserInfo userInfo = this->action->loginUserAction(user,hostInfo);

        LoginInfo loginInfo;

        loginInfo.setIp(hostInfo.getIp());
        loginInfo.setQQ(userInfo.getUser().getqq());

        emit adviceUdpLoginInfo(loginInfo);

        emit sendLoginData(socketDescriptor,userInfo);
    }else if(action == "search"){ //搜索好友by ID
        QJsonObject subJson = json.value("data").toObject();

        QString qqId = subJson["qq"].toString();

        User user = this->action->searchById(qqId);


        emit sendSearchData(socketDescriptor,user);



    }else if(action == "addnew"){
        QJsonObject subJson = json.value("data").toObject();
        QString userQQ = subJson["userQqId"].toString();
        QString selfQQ = subJson["selfQqId"].toString();
        if(userCopy->contains(userQQ)){ //说明此时那个人没有下线

            User user = this->action->searchById(selfQQ);
            emit sendAddnew(socketDescriptor,user);
        }else{  //将发送请求发送到数据库
            AddFriend addFriend;
            addFriend.setReceiveQQ(userQQ);
            addFriend.setRequestQQ(selfQQ);

            this->action->addNewFriend(addFriend);
        }
    }else if(action == "addNewFeedBack"){
        QJsonObject subJson = json.value("data").toObject();
        AddFriend addFriend;
        addFriend.setRequestQQ(subJson.value("requestQQ").toString());
        addFriend.setReceiveQQ(subJson.value("receiveQQ").toString());
        this->action->addNewFriendToDB(addFriend);

        if(userCopy->contains(addFriend.getRequestQQ())){
            User friendL = this->action->searchById(addFriend.getReceiveQQ());
            emit addFriendSuccess(socketDescriptor,friendL);  //告诉请求者添加好友成功
        }

    }



    // 发送结果


}


/**
 * function:tcp下线操作
 * @brief MyTcpServer::disconnectSlot
 * @param socketDescriptor
 */
void MyTcpServer::disconnectSlot( qint32 socketDescriptor)
{
    if(user->contains(socketDescriptor)){
        qDebug()<<user->value(socketDescriptor)<<"已经下线";
        this->action->logout(user->value(socketDescriptor));

        QString qq = user->value(socketDescriptor);
        user->remove(socketDescriptor);
        userCopy->remove(qq);
        emit adviceLoginOrLogout(socketDescriptor,qq,false);
        emit  adviceUdpLogoutInfo(qq);
        emit displayAccount(false);


    }

    int i = clients->remove(socketDescriptor);

    qDebug()<<tr("删除客户端   i=")<<i;


}


/**
 * function:将用户线程转移到新得Map集合中
 * @brief MyTcpServer::moveUserToMapSolt
 * @param socketDescriptor
 * @param qq
 */
void MyTcpServer::moveUserToMapSolt(qint32 socketDescriptor, QString qq)
{
//    QTcpSocket * tcpConn = clients->value(socketDescriptor);

    user->insert(socketDescriptor,qq);
    userCopy->insert(qq,socketDescriptor);

    emit adviceLoginOrLogout(socketDescriptor,qq,true);

    qDebug()<<qq<<"已上线"<<socketDescriptor;





    emit displayAccount(true);

}

/**
 * funciton: 发送给好友消息
 * @brief MyTcpServer::sendMessage
 * @param data
 * @param receiveQQ
 */
void MyTcpServer::sendMessage(const QByteArray data, const QString receiveQQ)
{
    qDebug()<<"yes";
    emit sendMessageToUser(this->userCopy->value(receiveQQ),data);
}

