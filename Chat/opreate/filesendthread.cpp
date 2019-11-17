#include "FileSendThread.h"
#include <QThread>
#include <QDebug>

FileSendThread::FileSendThread(QObject *parent) : QObject(parent)
{
    isstop = false;
}

void FileSendThread::MyTimeout()
{
//    while (isstop == false)
//    {
//        QThread::sleep(1);
//        emit mysignal();

//        //打印子线程号
//        qDebug()<<"sub thread number:"<<QThread::currentThread();//当前线程号打印
//        if(isstop == true)
//        {
//            break;
//        }
//    }


}

void FileSendThread::setflag(bool flag)
{
    isstop = flag;
}
