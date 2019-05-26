#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>


/**
 * function: 消息存储类
 * @brief The Message class
 */
class Message{
public:
    void setSenderQQ(QString senderQQ){
        this->senderQQ = senderQQ;
    }
    QString getSenderQQ(){
        return senderQQ;
    }
    void setReceviceQQ(QString receviceQQ){
        this->receviceQQ = receviceQQ;
    }

    QString getReceviceQQ(){
        return receviceQQ;
    }
    void setContext(QString context){
        this->context = context;
    }
    QString getContext(){
        return context;
    }

    void setCDate(QString cDate){
        this->cDate = cDate;
    }
    QString getCDate(){
        return cDate;
    }


private:
    QString senderQQ;
    QString receviceQQ;
    QString context;
    QString cDate;
};

#endif // MESSAGE_H
