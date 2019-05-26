#ifndef REQUEST_H
#define REQUEST_H
#include <QByteArray>
#include <QHostAddress>

#include <QThread>
#include <QObject>
class RequestMsg :public QObject{
    Q_OBJECT
public:
    explicit RequestMsg(QObject *parent = nullptr);
    void setData(QByteArray data){
        this->data = data;
    }
    void setSender(QHostAddress sender){
        this->sender = sender;
    }
    void setSenderPort(quint16 senderPort){
        this->senderPort = senderPort;
    }
private:

};
#endif // REQUEST_H
