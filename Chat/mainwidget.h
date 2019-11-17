#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "itemwidget.h"
#include "opreate/EnterOp.h"
#include "Json/userinfo.h"
#include "addfriendwidget.h"
#include "selfinfowidget.h"
#include "opreate/MainOp.h"
#include <QFile>
#include "setwidget.h"
#include <QDateTime>
#include "filesend.h"
#include "Json/filedata.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void dealFriends();//好友列表

    void setUserWidget();//个人信息界面

    void setUserInfo(UserInfo userInfo);


    UserInfo getUserInfo();//获取用户的个人信息

    void addNewList(User user);

    void nowAdd(User user);

    void dealListFrdChoose();

    void changeStatus(QString qq,QString status);

    void dealMessage(Message msg);
    void dealOulineMessage(QList<Message> outlineMessage);//离线消息

    void setSelectFlag(bool flag = false){this->isSelect = flag;}//设置是否有好友选中
    bool getSlectFlag(){return  this->isSelect;}

    void setCurrentRow(int row){this->currentRow = row;}//获取之前选中的行
    int getCurrentRow(){return  this->currentRow;}

    void dealFileSend(QString code);//文件发送
    void dealFileSendFailed();//文件请求失败
    void dealOutlineRequestFileReceive(QList<FileDate>);
    void dealOnlineFileReceive(FileDate fileData);
//    void dealAgreeReceive(QString answerAccount,QString fileName);//对方同意接收文件
//    void dealRefuseReceive(QString answerAccount,QString fileName);//对方拒绝接受文件
//    void dealRequestReceive(QString requestName,QString account);//处理对方的文件发送请求



private slots:


    void on_ButtonAddFriend_clicked();

    void on_ButtonMy_clicked();

    void on_ButtonNewAdd_clicked();

    void on_ButtonMsg_clicked();

    void on_ButtonAgree_clicked();

    void setButton();

    void on_ButtonSet_clicked();

    void on_ButtonSend_clicked();

    void on_ButtonRefuse_clicked();

    void on_ButtonFileSend_clicked();


signals:
    void disconnect();

private:
    Ui::MainWidget *ui;

    EnterOp enterOp;
    UserInfo userInfo;//用户信息
    //User newFriend;//新好友
    HostInfo info;
    MainOp mainOp;
    QFile file;
    AddFriendWidget addWidget;//加好友界面
    SelfInfoWidget infoWidget;//查看用户信息界面
    SetWidget setWidget;//设置界面
    FileSend fileWidget;//文件发送界面
    QDateTime currentTime;//当前时间

    bool isSelect;//是否选择标记
    int currentRow;//当前选择行

};

#endif // MAINWIDGET_H
