#include "enterwidget.h"
#include "ui_enterwidget.h"
#include "Json/user.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#pragma execution_character_set("utf-8")

//登陆界面
EnterWidget::EnterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterWidget)
{
    ui->setupUi(this);
    setWindowTitle("登陆");




    //设置背景

    QFile qssfile(":/resource/enterwidget.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    this->setStyleSheet(qss);
    //设置背景
    QPalette pal = this->palette();
    QPixmap pixmap= QPixmap(":/resource/login-bg.jpg").scaled(this->size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(pal);

    //初始化LineEdit
    ui->lineEditPswd->setEchoMode(QLineEdit::Password);
    //初始化info
    QString IpString;
    file.setFileName(":/resource/Ip.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        IpString = QString(line);
    }
    info.setIp(IpString);
    info.setPort("9999");
}

EnterWidget::~EnterWidget()
{
    delete ui;
}

void EnterWidget::on_ButtonBack_clicked()
{
    ui->lineEditId->clear();
    ui->lineEditPswd->clear();
    emit BackLand();
}


void EnterWidget::on_ButtonLand_clicked()
{

    //获取输入的信息
    QString qqId = ui->lineEditId->text();
    QString pswd = ui->lineEditPswd->text();

    if(qqId.isEmpty()||pswd.isEmpty())//错误判断
    {
        QMessageBox::information(this,"ERROR","有空余信息");
        ui->ButtonLand->setEnabled(true);
    }
    else
    {
        //设置传入函数的数据包
        user.setAccount(qqId);
        user.setPwd(pswd);

        //登陆操作
        //登陆后一直开启监听
        enterOp.dealEnter(user,info);

        connect(&enterOp,&EnterOp::isEntered,this,&EnterWidget::dealJson,Qt::UniqueConnection);
        connect(&enterOp,&EnterOp::noEntered,this,&EnterWidget::failedSlot,Qt::UniqueConnection);
        connect(&enterOp,&EnterOp::errorEntered,this,&EnterWidget::errorSlot,Qt::UniqueConnection);
        connect(&enterOp,&EnterOp::isAddNew,this,&EnterWidget::dealAddNew);
        connect(&enterOp,&EnterOp::loginAndLogout,this,&EnterWidget::loginOut);
        connect(&enterOp,&EnterOp::messageSignal,this,&EnterWidget::dealMessage);
        connect(&enterOp,&EnterOp::outlineMessage,this,&EnterWidget::dealOutlineMessage);
        connect(&enterOp,&EnterOp::nowAddNew,this,&EnterWidget::dealNowAdd);
    }

}

void EnterWidget::failedSlot()
{
    QMessageBox::information(this,"错误","账号或密码错误");
    ui->ButtonLand->setEnabled(true);
}
void EnterWidget::errorSlot()
{
    QMessageBox::information(this,"重复登陆","您的账号目前已在线");
}
void EnterWidget::dealJson(UserInfo userInfo)
{   
    ui->ButtonLand->setEnabled(false);
    //好友列表
    mainWidget.setUserInfo(userInfo);//传入用户数据
    this->hide();
    mainWidget.dealFriends();
    mainWidget.show();

}

void EnterWidget::dealAddNew(User user)
{
    qDebug()<<"is received signal";
    //mainWidget.setNewFriend(user);
    mainWidget.addNewList(user);
}

void EnterWidget::loginOut(QString qq,QString status)
{
    mainWidget.changeStatus(qq,status);
}

void EnterWidget::dealMessage(Message msg)
{
    mainWidget.dealMessage(msg);
}

void EnterWidget::dealOutlineMessage(QList<Message> outlineMessage)
{
    mainWidget.dealOulineMessage(outlineMessage);
}

void EnterWidget::dealNowAdd(User user)
{
    mainWidget.nowAdd(user);
}
