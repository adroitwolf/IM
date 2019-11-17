#ifndef ENTERWIDGET_H
#define ENTERWIDGET_H

#include <QWidget>
#include "Json/user.h"
#include "Json/hostinfo.h"
#include "opreate/EnterOp.h"
#include "mainwidget.h"
#include <QFile>
#include "Json/message.h"
#include "filesend.h"

namespace Ui {
class EnterWidget;
}

class EnterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnterWidget(QWidget *parent = nullptr);
    ~EnterWidget();

signals:
    void BackLand();//返回初始界面信号
    void EnterSignal();//登陆信号


private slots:

    void on_ButtonBack_clicked();
    void on_ButtonLand_clicked();
    void failedSlot();
    void errorSlot();
    void dealJson(UserInfo userInfo);
    void dealAddNew(User user);
    void loginOut(QString qq,QString status);
    void dealMessage(Message msg);
    void dealOutlineMessage(QList<Message> oulineMessage);
    void dealNowAdd(User user);
    void dealFileSend(QString code);
    void dealFileSendFailed();
    void dealOutlineRequestFileReceive(QList<FileDate>);
    void dealOnlieFileReceive(FileDate fileData);
//    void dealAgreeReceive(QString answerAccount,QString fileName);//对方同意接受文件
//    void dealRefuseReceive(QString answerAccount,QString fileName);//对方拒绝
//    void dealRequestReceive(QString requestName,QString account);//处理文件发送请求函数

private:
    Ui::EnterWidget *ui;

    User user;//登陆用户的信息包
    HostInfo info;//服务端信息
    EnterOp enterOp;//登陆操作对象
    QFile file;//文件对象

    MainWidget mainWidget;


};

#endif // ENTERWIDGET_H
