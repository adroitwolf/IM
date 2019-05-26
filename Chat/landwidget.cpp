#include "landwidget.h"
#include "ui_landwidget.h"

#pragma execution_character_set("utf-8")

//第一层界面
LandWidget::LandWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LandWidget)
{
    ui->setupUi(this);
    setWindowTitle("OO");
    //初始化类成员
    Regist.hide();
    //设置背景

    QFile qssfile(":/resource/landwidget.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    this->setStyleSheet(qss);

    QPalette pal = this->palette();
    QPixmap pixmap= QPixmap(":/resource/index-bg.jpg").scaled(this->size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(pal);
    //信号处理函数

    //注册界面信号
    connect(&Regist,&RegistWidget::BackLand,
            [=]()
            {
                Regist.hide();
                this->show();
            });
    //登陆界面信号
    connect(&Enter,&EnterWidget::BackLand,
            [=]()
            {
                Enter.hide();
                this->show();
            });

}

LandWidget::~LandWidget()
{
    delete ui;
}



//窗口控件槽函数
void LandWidget::on_pushButton_clicked()
{
    this->hide();
    Regist.show();
}

void LandWidget::on_pushButton_2_clicked()
{
    this->hide();
    Enter.show();
}
