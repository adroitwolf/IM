#ifndef HOSTINFO_H
#define HOSTINFO_H

#include <QString>


/**
 * function : 保存主机信息
 * @brief The HostInfo class
 */
class HostInfo{
public:
    QString getIp() const{
        return ip;
    }
    void setIp(QString ip){
        this->ip = ip;
    }
    QString getPort() const{
        return port;
    }
    void setPort(QString port){
        this->port = port;
    }
    QString getDesk() const{
        return desk;
    }
    void setDesk(QString desk){
        this->desk = desk;
    }
    QByteArray getData()const{
        return data;
    }

    void setData(QByteArray data){
        this->data = data;
    }


private:
    QString ip;
    QString port;
    QString desk;
    QByteArray data;

};

#endif // HOSTINFO_H
