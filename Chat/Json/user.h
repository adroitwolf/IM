#ifndef USER_H
#define USER_H

#include <QString>
#include "Json/message.h"
#include <QList>

/**
 * function:用户信息类
 * @brief The User class
 */
class User{
private:
    QString account;
    QString nickname;
    QString pwd;
    QString sign;
    QString sex;
    QString status;

    QList<Message> message;
public:
    void setStatus(QString status){
        this->status = status;
    }
    QString getStatus()const{
        return this->status;
    }
    void setNickName(QString nickname){
        this->nickname = nickname;
    }
    QString getNickName(){
        return this->nickname;
    }
    void setPwd(QString pwd){
        this->pwd = pwd;
    }
    QString getPwd(){
        return this->pwd;
    }
    void setSign(QString sign){
        this->sign = sign;
    }
    QString getSign(){
        return this->sign;
    }
    void setSex(QString sex){
        this->sex = sex;
    }
    QString getSex(){
        return this->sex;
    }
    void setAccount(QString account){
        this->account = account;
    }
    QString getAccount(){
        return this->account;
    }
    void setMessage(QList<Message> message){
        this->message = message;
    }
    QList<Message> getMessage(){
        return  this->message;
    }


};

#endif // USER_H
