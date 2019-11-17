#include "FileSendThread.h"
#include <QThread>
#include <QDebug>
File::MyThread(QObject *parent) : QObject(parent)
{

    isstop = false;
}

void MyThread::MyTimeout()
{
    while (isstop == false)
    {
        QThread::sleep(1);
        emit mysignal();

        //打印子线程号
        qDebug()<<"sub thread number:"<<QThread::currentThread();//当前线程号打印
        if(isstop == true)
        {
            break;
        }
    }
}

void MyThread::setflag(bool flag)
{
    isstop = flag;
}
