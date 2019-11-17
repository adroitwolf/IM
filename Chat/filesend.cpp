#include "filesend.h"
#include "ui_filesend.h"
#include <QHostAddress>
#include <QJsonDocument>
#include <QDateTime>
#include <windows.h>

#pragma execution_character_set("utf-8")

FileSend::FileSend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSend)
{
    ui->setupUi(this);


    isHead = true;
    tcpSocket = new QTcpSocket(this);
    fileTcpSocket = new QTcpSocket(this);
    receiveTcpSocket = new QTcpSocket(this);

    connect(&timer,&QTimer::timeout,
            [=]()
    {
        //关闭定时器
        timer.stop();
        qDebug()<<"123";
        //发送文件
        sendFile();
    });
    connect(this,&FileSend::receivedBuf,this,&FileSend::fileReceive);

}

FileSend::~FileSend()
{
    delete ui;

}

/**
 * @brief FileSend::requestSend 向服务器发送请求
 * 文件上传的第一步
 */
void FileSend::requestSend()
{
    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","asksend");//请求发文件命令

    //封装data
    //请求者号
    QJsonObject userData;
    userData.insert("senderAccount",this->selfInfo.getAccount());
    userData.insert("receiverAccount",this->currentFrdInfo.getAccount());
    jsonObject.insert("data",QJsonValue(userData));
    //连接服务器
    tcpSocket->abort();
    tcpSocket->connectToHost(QHostAddress(hInfo.getIp()),hInfo.getPort().toInt());
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();
    tcpSocket->write(msg);
    qDebug()<<QString(msg);
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}

/**
 * @brief FileSend::dealSend 接收到服务器的随机码，开始文件传输
 * @param code 随机码
 * 文件上传的第二步
 */
void FileSend::dealSend(QString code)
{
    this->UUID = code;
    //    fileTcpSocket->abort();
    fileTcpSocket->connectToHost(QHostAddress(hInfo.getIp()),8848);
    this->show();//界面弹出
    ui->labelInfo->setText("sending file");
    filename.clear();
    filesize = 0;
    //获取文件信息
    QFileInfo info(this->filePath);
    filename = info.fileName();//名字
    filesize = info.size();//大小
    //指定文件的名字
    file.setFileName(this->filePath);
    /*修改文件名*/
    //获取文件类型
    QString type = file.fileName().section(".",1,1);
    //拼接文件名
    this->newName = QDir::toNativeSeparators(QString(info.absolutePath()+"/"+code));
    //替换文件名
    this->oldName = QDir::toNativeSeparators(file.fileName());
    qDebug()<<"file rename";
    qDebug()<<file.rename(oldName,newName);

    file.setFileName(newName);//修改文件指定位置
    sendsize = 0;//发送文件大小初始化

    //发送文件头
    qDebug()<<"sending head";

    //向服务器发送文件传输完毕请求

    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","fileSendReq");//文件基本信息

    //封装data
    QJsonObject userData;
    userData.insert("fileSize",this->filesize);
    userData.insert("fileName",this->UUID);
    jsonObject.insert("data",QJsonValue(userData));

    //连接服务器
    //    fileTcpSocket->abort();
    fileTcpSocket->connectToHost(QHostAddress(hInfo.getIp()),8848);
    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();
    fileTcpSocket->write(msg);

    connect(fileTcpSocket,&QTcpSocket::readyRead,[=](){
        QByteArray buf = fileTcpSocket->readAll();
//        qDebug()<<QString(buf);

        if(QString(buf) == "ACK")
        {

            //只读打开文件
            //打开文件
            bool isopen = file.open(QIODevice::ReadOnly);
            if(isopen == false)
            {
                qDebug() << "只读打开文件失败";
            }
            /*发送文件操作*/
            timer.start(20);
        }
    });
}

/**
 * @brief FileSend::sendFile 发送文件操作函数
 */

void FileSend::sendFile()
{
    //连接服务器
    qint64 len = 0;
    ui->progressBarSend->setRange(0,this->filesize);
    do
    {
        Sleep(20);
        //每次发送数据的大小参数设置
        char buf[1024*4] = {0};
        len = 0;
        qDebug()<<"-------";
        //读数据
        len = file.read(buf,sizeof (buf));
        qDebug()<<"len:"<<len;
        //发送数据
        fileTcpSocket->write(buf,len);
        //        fileTcpSocket->write(buf,len);
        //发送的数据要累加
        sendsize += len;
        ui->progressBarSend->setValue(sendsize);
    }while(len > 0);

    qDebug()<<"send:"<<sendsize;

    qDebug()<<"fileL:"<<this->filesize;
    //判断文件是否发送成功
    if(sendsize == this->filesize)
    {
        //向服务器发送文件传输完毕请求

        //打包数据包
        QJsonObject jsonObject;
        jsonObject.insert("actionType","upLoadSuccess");//请求发文件命令

        //封装data
        //请求者号
        QJsonObject userData;
        userData.insert("senderAccount",this->selfInfo.getAccount());
        userData.insert("receiverAccount",this->currentFrdInfo.getAccount());
        userData.insert("fileName",this->filename);
        userData.insert("fileTime",QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
        userData.insert("fileSize",this->filesize);
        userData.insert("UUID",this->UUID);
        jsonObject.insert("data",QJsonValue(userData));
        //连接服务器
        tcpSocket->abort();
        tcpSocket->connectToHost(QHostAddress(hInfo.getIp()),hInfo.getPort().toInt());
        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray msg = jsonDocument.toJson();
        tcpSocket->write(msg);

        file.close();

        //与客户端断开
        tcpSocket->disconnectFromHost();
        tcpSocket->close();


        ui->labelInfo->setText("传输完成");
        ui->progressBarSend->setValue(0);
        fileTcpSocket->disconnectFromHost();
        fileTcpSocket->close();
        emit FileSend::sendOver();
        this->hide();//界面关闭
    }
    file.rename(newName,oldName);//将本地文件名改回原来的名字
}

void FileSend::agreeReceiveRequest(FileDate fileData)
{

    recvFile.setFileName(fileData.getFileName());
    bool isopen = recvFile.open(QIODevice::WriteOnly);
    if(isopen == false)
    {
        qDebug()<<"receive error";
    }
    receiveSize = 0;
    connect(receiveTcpSocket,&QTcpSocket::readyRead,
            [=]()
    {
        QByteArray buf = receiveTcpSocket->readAll();

        emit receivedBuf(buf);
    });

    //初始化hInfo
    QString IpString;
    QFile ipFile;
    ipFile.setFileName(":/resource/Ip.txt");
    if(!ipFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!ipFile.atEnd()) {
        QByteArray line = ipFile.readLine();
        IpString = QString(line);
    }
    hInfo.setIp(IpString);
    ipFile.close();

    //同意接收文件
    qDebug()<<"enter agreeReceiveFile";

    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","downLoad");//请求发文件命令

    //封装data
    QJsonObject userData;
    userData.insert("fileName",fileData.getFileName());
    userData.insert("UUID",fileData.getUUID());
    jsonObject.insert("data",QJsonValue(userData));


    QJsonDocument jsonDocument;
    jsonDocument.setObject(jsonObject);
    QByteArray msg = jsonDocument.toJson();
    qDebug()<<QString(msg);

    //连接服务器
    //    receiveTcpSocket->abort();
    receiveTcpSocket->connectToHost(QHostAddress(hInfo.getIp()),8848);

    qDebug()<<"info:"<<hInfo.getIp();

    receiveTcpSocket->write(msg);
    receiveFileName = fileData.getFileName();
    receiveFileSize = fileData.getFileSize().toLongLong();
    this->UUID = fileData.getUUID();
    //设置UI

    ui->progressBarSend->setMaximum(receiveFileSize);
    ui->progressBarSend->setValue(0);
    file.setFileName(receiveFileName);

}

void FileSend::refuseReceiveRequest(FileDate fileData)
{
    //拒绝接收文件
    //打包数据包
    QJsonObject jsonObject;
    jsonObject.insert("actionType","refuseReceive");//请求发文件命令

    //封装data
    QJsonObject userData;
    userData.insert("fileName",fileData.getUUID());
    jsonObject.insert("data",QJsonValue(userData));
    //连接服务器
    fileTcpSocket->abort();
    qDebug()<<hInfo.getIp();
    fileTcpSocket->connectToHost(QHostAddress(hInfo.getIp()),8848);
    if (fileTcpSocket->waitForConnected(1000)) {
        QJsonDocument jsonDocument;
        jsonDocument.setObject(jsonObject);
        QByteArray msg = jsonDocument.toJson();
        fileTcpSocket->write(msg);
        fileTcpSocket->disconnectFromHost();
        fileTcpSocket->close();
    }else{
        qDebug()<<"connect failed";
    }

}

void FileSend::fileReceive(QByteArray buf)
{
//    qDebug()<<"buf:   "<<buf;
    qDebug()<<"enter receiving";
    qint64 len = recvFile.write(buf);
    receiveSize += len;
    qDebug()<<"\n\n\n\nreceiveSize:"<<receiveSize;
    qDebug()<<"fileSize:"<<receiveFileSize;

    qDebug()<<"------------------------\n\n\n\n";
    this->show();
    ui->progressBarSend->setValue(receiveSize);
    if(receiveSize == receiveFileSize)
    {
        ui->labelInfo->setText("receive successful");

        receiveTcpSocket->disconnectFromHost();
        receiveTcpSocket->close();
        recvFile.close();
    }
}
