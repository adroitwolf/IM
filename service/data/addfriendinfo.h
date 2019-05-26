#ifndef ADDFRIENDINFO_H
#define ADDFRIENDINFO_H

#include <QString>

/**
 * function: 添加好友的信息类
 * @brief The AddFriendInfo class
 */
class AddFriendInfo{
private:
    QString requestQQ;
    QString receviceQQ;
public:
    void setRequestQQ(QString requestQQ){
        this->requestQQ = requestQQ;
    }
    QString getRequestQQ() const{
        return requestQQ;
    }
    void setReceviceQQ(QString receviceQQ){
        this->receviceQQ = receviceQQ;
    }

    QString getReceviceQQ() const{
        return receviceQQ;
    }
};

#endif // ADDFRIENDINFO_H
