#ifndef FILESENDTHREAD_H
#define FILESENDTHREAD_H

#include <QObject>
#include <QThread>

class FileSendThread : public QObject
{
    Q_OBJECT
public:
    explicit FileSendThread(QObject *parent = nullptr);

    void MyTimeout();//线程处理函数

    void setflag(bool flag = true);//线程停止flag


signals:

    void mysignal();

public slots:

private:
    bool isstop;
};

#endif // FILESENDTHREAD_H
