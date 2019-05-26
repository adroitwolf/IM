#include "addfriendwidget.h"
#include "ui_addfriendwidget.h"
#include <QMessageBox>

#pragma execution_character_set("utf-8")

AddFriendWidget::AddFriendWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriendWidget)
{
    ui->setupUi(this);
    setWindowTitle("添加好友");

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

AddFriendWidget::~AddFriendWidget()
{
    delete ui;
}

void AddFriendWidget::on_ButtonBack_clicked()
{
    ui->lineEditId->clear();
    this->hide();
    emit addBack();
}


void AddFriendWidget::getUserInfo(User user)
{
    this->user = user;
}

void AddFriendWidget::on_ButtonOK_clicked()
{
    ui->lineEditId->clear();
    ui->page_4->hide();
    ui->page->hide();
    ui->page_3->show();
    this->hide();
    emit addBack();
}



void AddFriendWidget::on_ButtonSure_clicked()//确认添加按钮
{
    int flag = 1;
    for(int i = 0;i<this->userInfo.getFriends().size();i++)
    {
        if(ui->lineEditId->text() == this->userInfo.getFriends()[i].getAccount())
        {
            flag = 0;//重复
        }
    }
    if(flag == 1)
    {
        //发送请求信息
        QString idString = ui->lineEditId->text();
        addOp.dealAdd(user,idString,info);
        ui->page->hide();
        ui->page_4->show();
    }
    else
    {
        QMessageBox::information(this,"出错了啊！","你已经添加过此用户啦，求求你别加啦！");
    }
}

void AddFriendWidget::on_ButtonSearch_clicked()
{

    addOp.dealSearch(ui->lineEditId->text(),this->info);

    connect(&addOp,&AddFriendOp::searchSignal,this,&AddFriendWidget::searchSlot);


}

void AddFriendWidget::searchSlot(User user)
{
    ui->labelId->setText(user.getAccount());
    ui->labelNick->setText(user.getNickName());
    ui->labelSex->setText(user.getSex());
    ui->labelsign->setText(user.getSign());
    ui->page->show();
    ui->page_3->hide();
    ui->page_4->hide();
}

void AddFriendWidget::on_ButtonBack2_clicked()
{
    ui->page->hide();
    ui->page_3->show();
}

void AddFriendWidget::setUserInfo(UserInfo userInfo)
{
    this->userInfo = userInfo;
}
