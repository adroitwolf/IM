#ifndef ADDFRIENDWIDGET_H
#define ADDFRIENDWIDGET_H

#include <QWidget>
#include "Json/user.h"
#include "Json/hostinfo.h"
#include "opreate/AddFriendOp.h"
#include <QFile>

namespace Ui {
class AddFriendWidget;
}

class AddFriendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddFriendWidget(QWidget *parent = nullptr);
    ~AddFriendWidget();

    void getUserInfo(User user);
    void setUserInfo(UserInfo serInfo);

private slots:
    void on_ButtonBack_clicked();

    void on_ButtonOK_clicked();


    void on_ButtonSure_clicked();

    void on_ButtonSearch_clicked();

    void searchSlot(User user);
    void noSearchSlot();

    void on_ButtonBack2_clicked();

signals:
    void addBack();

private:
    Ui::AddFriendWidget *ui;

    User user;//用户的信息
    HostInfo info;//服务器信息

    UserInfo userInfo;

    AddFriendOp addOp;//加好友操作

    QFile file;
};

#endif // ADDFRIENDWIDGET_H
