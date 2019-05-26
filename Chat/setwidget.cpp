#include "setwidget.h"
#include "ui_setwidget.h"
#include <QMessageBox>

#include <QDebug>
#pragma execution_character_set("utf-8")

SetWidget::SetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWidget)
{
    ui->setupUi(this);
    setWindowTitle("设置");
}

SetWidget::~SetWidget()
{
    delete ui;
}



void SetWidget::on_ButtonExit_clicked()
{
    if(QMessageBox::question(this,"question","是否退出?",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes) == QMessageBox::Yes){
        QApplication *app;
        app->exit(0);
    }
//    emit exitSignal();
    qDebug()<<"rs";

}
