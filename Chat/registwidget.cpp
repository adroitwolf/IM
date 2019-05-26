#include "registwidget.h"
#include "ui_registwidget.h"
#include "opreate/RegistOp.h"
#include "QMessageBox"
#include "Json/hostinfo.h"
#include <QHostAddress>
#include <QTextCodec>
#pragma execution_character_set("utf-8")

RegistWidget::RegistWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistWidget)
{
    ui->setupUi(this);
    setWindowTitle("注册");

    QFile qssfile(":/resource/registwidget.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    this->setStyleSheet(qss);
    //设置背景
    QPalette pal = this->palette();
    QPixmap pixmap= QPixmap(":/resource/register-bg.jpg").scaled(this->size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(pal);
    //设置LineEdit状态
    ui->lineEditPswd->setEchoMode(QLineEdit::Password);
    ui->lineEditSure->setEchoMode(QLineEdit::Password);

    //初始化栈Widget
    ui->page->show();
    ui->page_2->hide();

    //初始化user
    user = new User;
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

RegistWidget::~RegistWidget()
{
    delete ui;
    delete user;
}

void RegistWidget::on_ButtonBack_clicked()
{
    ui->lineEditUser->clear();
    ui->lineEditPswd->clear();
    ui->lineEditSure->clear();
    emit BackLand();
}

void RegistWidget::on_ButtonRegist_clicked()//注册信息
{

    QString UserString = ui->lineEditUser->text();
    QString PswdString = ui->lineEditPswd->text();
    QString SureString = ui->lineEditSure->text();
    QString SexString = ui->comboBoxSex->currentText();

    //错误判断
    if(PswdString != SureString)
    {
        QMessageBox::information(this,"ERROR","密码与确认密码不相同");
    }
    else if(UserString.isEmpty()||PswdString.isEmpty()||SureString.isEmpty())
    {
        QMessageBox::information(this,"ERROR","请不要有空余信息");
    }
    else
    {

        RegistOp *registOp = new RegistOp();
        //发送注册信息到服务器

        user->setNickName(UserString);
        user->setPwd(PswdString);
        user->setSex(SexString);
        registOp->DealRegist(user,this->info);

        connect(registOp,&RegistOp::isRegist,this,&RegistWidget::isRegistSlot);


        connect(registOp,&RegistOp::noRegist,
                [=]()
                {
                    QMessageBox::information(this,"注册失败","注册失败!");
                    emit BackLand();
                });
    }

}

void RegistWidget::isRegistSlot(QString qq)
{
    this->qqId = qq;
    ui->page->hide();
    ui->page_2->show();
    QString str = "注册成功，您的账号为："+qqId;
    ui->labelqqId->setText(str);

}

void RegistWidget::on_ButtonSure_clicked()
{
    ui->labelqqId->clear();
    emit BackLand();
}
