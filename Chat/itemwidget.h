#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QList>
#include "Json/user.h"
#include "Json/userinfo.h"

namespace Ui {
class ItemWidget;
}

class ItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidget(QWidget *parent = nullptr);
    ~ItemWidget();
    void setItemWidget(User user);

private:
    Ui::ItemWidget *ui;
};

#endif // ITEMWIDGET_H
