#ifndef SELFINFOWIDGET_H
#define SELFINFOWIDGET_H

#include <QWidget>
#include "Json/userinfo.h"

namespace Ui {
class SelfInfoWidget;
}

class SelfInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelfInfoWidget(QWidget *parent = nullptr);
    ~SelfInfoWidget();
    void setUser(User user);

private:
    Ui::SelfInfoWidget *ui;

    User user;
};

#endif // SELFINFOWIDGET_H
