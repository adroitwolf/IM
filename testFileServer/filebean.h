#ifndef FILEBEAN_H
#define FILEBEAN_H
#include <QFileInfo>
#include <QDir>
#include <QFile>   //文件
#include <QTimer>//定时器
#include <QDebug>

class FileBean
{
public:
    explicit FileBean(QString fileName,qint64 filesize){
        file.setFileName(fileName);
        this->filesize = filesize;
        this->receivesize = 0;
        bool isopen = file.open(QIODevice::WriteOnly);
        if(isopen == false)
        {
            qDebug() << "只写打开文件失败";
        }
    }



    void recvFile(QByteArray buff){
        qint64 len =  file.write(buff);
        this->receivesize += len;
        qDebug()<<"len:"<<this->receivesize;
        qDebug()<<"size"<<this->filesize;
    }

    bool isRecvOver(){
        return this->filesize == this->receivesize ? true:false;
    }

    void closeFile(){
        this->file.close();
    }

    void functionOver(){
        this->file.close();
    }

private:
    qint64 filesize;
    QFile file;
    qint64 receivesize;
    qint64 sendSize;
};

#endif // FILEBEAN_H
