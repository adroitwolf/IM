#ifndef HOSTINFO_H
#define HOSTINFO_H

#include <QString>


/**
 * function : 保存主机信息
 * @brief The HostInfo class
 */
class HostInfo{
private:
    QString ip;
    QString port;
    QString desk;
    QString qq;
public:
    void setIp(QString ip){
        this->ip = ip;
    }
    QString getIp(){
        return ip;
    }
    void setPort(QString port){
        this->port = port;
    }
    QString getPort(){
        return this->port;
    }
    void setDesk(QString desk){
        this->desk = desk;
    }
    QString getDesk(){
        return desk;
    }

};

#endif // HOSTINFO_H
