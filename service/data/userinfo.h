#ifndef USERINFO_H
#define USERINFO_H

#include "data/user.h"
#include "data/message.h"
#include "data/filebean.h"
#include <QList>


/**
 * function:用户类的详细信息
 * @brief The UserInfo class
 */
class UserInfo
{
private:
    User user; //用户个人信息
    QList<User> friends; //用户好友
    QList<Message> msg; //用户离线时候的消息
    QList<User> addRequest; //用户离线时候的添加好友请求
    QList<FileBean> fileBeans; //用户传文件
    QString info;
public:

    void setInfo(QString info){
        this->info = info;
    }

    QString getInfo() const{
        return info;
    }

    void setAddRequest(QList<User> addRequest){
        this->addRequest = addRequest;
    }

    QList<User> getAddRequest() const{
        return addRequest;
    }

    void setUser(User user){
        this->user = user;
    }
    User getUser() const{
        return user;
    }
    void setFriends(QList<User> friends){
        this->friends = friends;
    }

    QList<User> getFriends()const {
        return friends;
    }

    void setMessage(QList<Message> msg){
        this->msg = msg;
    }

    const QList<Message> getMessage() const{
        return msg;
    }

    void setFileBeans(QList<FileBean> fileBeans){
        this->fileBeans = fileBeans;
    }

    QList<FileBean> getFileBeans() const{
        return this->fileBeans;
    }

};

#endif // USERINFO_H
