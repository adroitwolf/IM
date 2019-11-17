#ifndef ENTEROP_H
#define ENTEROP_H

#include <QWidget>
#include <QTcpSocket>
#include <QObject>
#include "Json/user.h"
#include "Json/hostinfo.h"
#include "Json/userinfo.h"
#include "Json/userinfo.h"
#include "Json/message.h"
#include "Json/filedata.h"

class EnterOp:public QObject
{
     Q_OBJECT
public:

    void dealEnter(User user,HostInfo info);//处理登陆函数




signals:
    void isEntered(UserInfo userInfo);//登陆成功
    void noEntered();//登陆失败
    void errorEntered();//登陆错误（重复登陆）
    void disConnect();//断开连接
    void isAddNew(User user);//添加好友成功
    void nowAddNew(User user);
    void loginAndLogout(QString qq,QString status);//上下线通知
    void messageSignal(Message msg);
    void outlineMessage(QList<Message>);
    void dealFileSend(QString code);
    void dealOutlineRequestFileReceive(QList<FileDate>);//离线文件
    void dealFileSendFailed();
    void dealOnlineFileReceive(FileDate fileData);
//    void agreeReceive(QString answerAccount,QString fileName);//同意接收文件
//    void refuseReceive(QString answerAccount,QString fileName);//拒绝文件接收
//    void requestReceive(QString requestName,QString request);//请求文件接收

private:
    QTcpSocket *tcpSocket;//通信套接字



};

#endif // ENTEROP_H
