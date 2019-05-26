#ifndef LANDWIDGET_H
#define LANDWIDGET_H

#include <QWidget>

#include "registwidget.h"
#include "enterwidget.h"

namespace Ui {
class LandWidget;
}

class LandWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LandWidget(QWidget *parent = nullptr);
    ~LandWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LandWidget *ui;

    //注册界面
    RegistWidget Regist;
    //登陆界面
    EnterWidget Enter;
};

#endif // LANDWIDGET_H
