#include "itemwidget.h"
#include "ui_itemwidget.h"
#include "QPixmap"
#include <QDebug>

#pragma execution_character_set("utf-8")

ItemWidget::ItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget)
{
    ui->setupUi(this);

}


void ItemWidget::setItemWidget(User user)
{
    //设置好友item
    ui->labelName->setText(user.getNickName());
    if(user.getStatus() == "1")
    {
        ui->labelTextStatus->setText("在线");
        QImage img;
        img.load(":/resource/online.png");
        ui->labelStatus->setPixmap(QPixmap::fromImage(img));
    }
    else if(user.getStatus() == "0")
    {
        ui->labelTextStatus->setText("离线");
        QImage img;
        img.load(":/resource/outline.png");
        ui->labelStatus->setPixmap(QPixmap::fromImage(img));
    }
}

ItemWidget::~ItemWidget()
{
    delete ui;
}
