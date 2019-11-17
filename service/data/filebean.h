#ifndef FILEBEAN_H
#define FILEBEAN_H

#include <QString>


/**
 * function: 文件传输的bean
 * @brief The FileBean class
 */
class FileBean
{
public:
    QString getSender() const{
        return this->sender;
    }

    QString getRecver() const{
        return this->recver;
    }

    void setSender(QString sender){
        this->sender  =  sender;
    }
    void setRecver(QString recver){
        this->recver = recver;
    }

    QString getFileName() const{
        return this->fileName;
    }

    QString getUUID() const{
        return this->uuid;
    }

    void setFileName(QString fileName){
        this->fileName = fileName;
    }

    void setUUID(QString uuid){
        this->uuid = uuid;
    }

    int getSize() const{
        return this->size;
    }
    QString getFileTime() const{
        return this->fileTime;
    }
    void setSize(int size){
        this->size = size;
    }

    void setFileTime(QString fileTime){
        this->fileTime = fileTime;
    }
private:
    QString sender;
    QString recver;
    QString fileName;
    QString uuid;
    int size;
    QString fileTime;
};

#endif // FILEBEAN_H
