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
    QDateTime currentTime;

    bool isSelect;
    int currentRow;

};

#endif // MAINWIDGET_H
