#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>
#include <Json/user.h>
#include <QFile>
#include <Json/hostinfo.h>

namespace Ui {
class RegistWidget;
}

class RegistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistWidget(QWidget *parent = nullptr);
    ~RegistWidget();

signals:
    void BackLand();

private slots:
    void on_ButtonBack_clicked();

    void on_ButtonRegist_clicked();

    void isRegistSlot(QString qqId);

    void on_ButtonSure_clicked();

private:
    Ui::RegistWidget *ui;

//    QTcpSocket *tcpSocket;//通信套接字
    User *user;//用户信息包
    HostInfo info;
    QString qqId;
    QFile file;//文件对象
};

#endif // REGISTWIDGET_H

