#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QString>

class ClientInfo{

private:
    QString clientIp;
    qint16  clientPort;
    QString fileOldName;//文件的UUID
    QString fileNewName;//文件的本名

public:
    void setClientIp(QString ip){
        this->clientIp = ip;
    }
    QString getClientIp(){
        return this->clientIp;
    }
    void setClientPort(qint16 port){
        this->clientPort = port;
    }
    qint16 getClientPort(){
        return this->clientPort;
    }
    void setFileOldName(QString oldname){
        this->fileOldName = oldname;
    }
    QString getOldName(){
        return this->fileOldName;
    }
    void setFileNewName(QString newname){
        this->fileNewName = newname;
    }
    QString getNewName(){
        return this->fileNewName;
    }
};

#endif // CLIENTINFO_H
