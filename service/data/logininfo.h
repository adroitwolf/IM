#ifndef LOGININFO_H
#define LOGININFO_H


#include <QString>


/**
 * QQ上线用来消息收发管理的bean类
 * @brief The LoginInfo class
 */
class LoginInfo{
private:
    QString ip;
    QString qq;
public:
    void setIp(QString ip){
        this->ip = ip;
    }

    QString getIp() const{
        return  this->ip;
    }

    void setQQ(QString qq){
        this->qq = qq;
    }

    QString getQQ() const{
        return  qq;
    }
};

#endif // LOGININFO_H
