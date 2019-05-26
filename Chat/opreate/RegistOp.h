#ifndef REGISTOP_H
#define REGISTOP_H

#include <QWidget>
#include <QTcpSocket>
#include <QObject>
#include "Json/user.h"
#include "Json/hostinfo.h"

class RegistOp:public QObject
{
     Q_OBJECT
public:



    void DealRegist(User *user,HostInfo info);//注册处理函数

signals:
    void isRegist(QString Id);//注册成功信号
    void noRegist();//注册失败信号
    void disConnect();//断开TCP连接信号

private:



};

#endif // REGISTOP_H
