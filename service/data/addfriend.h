#ifndef ADDFRIENDS_H
#define ADDFRIENDS_H

#include <QString>


/**
 * function :封装的添加好友信息类
 * @brief The AddFriend class
 */
class AddFriend{
private:
    QString requestQQ;
    QString receiveQQ;
public:
    void setRequestQQ(QString requestQQ){
        this->requestQQ = requestQQ;
    }
    QString getRequestQQ() const{
        return requestQQ;
    }

    void setReceiveQQ(QString receiveQQ){
        this->receiveQQ = receiveQQ;
    }

    QString getReceiveQQ() const{
        return receiveQQ;
    }

};

#endif // ADDFRIENDS_H
