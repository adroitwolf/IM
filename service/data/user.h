#ifndef USER_H
#define USER_H

#include <QString>

/**
 * function:用户信息类
 * @brief The User class
 */
class User{
private:
    QString qq;
    QString nickname;
    QString pwd;
    QString sign;
    QString sex;
    QString status;
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
    QString getNickName() const{
        return this->nickname;
    }
    void setPwd(QString pwd){
        this->pwd = pwd;
    }
    QString getPwd() const{
        return this->pwd;
    }
    void setSign(QString sign){
        this->sign = sign;
    }
    QString getSign()const{
        return this->sign;
    }
    void setSex(QString sex){
        this->sex = sex;
    }
    QString getSex() const{
        return this->sex;
    }
    void setqq(QString qq){
        this->qq = qq;
    }
    QString getqq()const{
        return this->qq;
    }
};

#endif // USER_H
