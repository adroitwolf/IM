#ifndef USERINFO_H
#define USERINFO_H

#include "data/user.h"
#include "data/message.h"
#include <QList>


/**
 * function:用户类的详细信息
 * @brief The UserInfo class
 */
class UserInfo
{
private:
    User user;
    QList<User> friends;
    QList<Message> msg;
public:
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


};

#endif // USERINFO_H
