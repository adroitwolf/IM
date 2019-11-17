#ifndef FILEDATA_H
#define FILEDATA_H

#include <QString>


/**
 * @brief The FileDate class 文件信息
 */
class FileDate{
private:
    QString fileName;
    QString senderQQ;
    QString fileSize;
    QString UUID;
    QString fileTime;
public:
    void setFileName(QString filename){
        this->fileName = filename;
    }
    QString getFileName(){
        return fileName;
    }
    void setSenderQQ(QString senderQQ){
        this->senderQQ = senderQQ;
    }
    QString getSenderQQ(){
        return this->senderQQ;
    }
    void setFileSize(QString filesize){
        this->fileSize = filesize;
    }
    QString getFileSize(){
        return this->fileSize;
    }
    void setUUID(QString uuid){
        this->UUID = uuid;
    }
    QString getUUID(){
        return this->UUID;
    }
    void setFileTime(QString filetime){
        this->fileTime = filetime;
    }
    QString getFileTime(){
        return this->fileTime;
    }
};


#endif // FILEDATA_H
