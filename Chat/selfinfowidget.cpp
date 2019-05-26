#include "selfinfowidget.h"
#include "ui_selfinfowidget.h"
#include <QDebug>

#pragma execution_character_set("utf-8")

SelfInfoWidget::SelfInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfInfoWidget)
{
    ui->setupUi(this);
    setWindowTitle("我的信息");
}

SelfInfoWidget::~SelfInfoWidget()
{
    delete ui;
}

void SelfInfoWidget::setUser(User user)
{
    ui->labelId->setText(user.getAccount());
    ui->labelNick->setText(user.getNickName());
    ui->labelSex->setText(user.getSex());
    ui->labelSign->setText(user.getSign());
}
