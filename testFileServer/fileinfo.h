#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>


class FileInfo
{
public:
    QString getFileName(){
        return this->fileName;
    }

    int getFileSize(){
        return fileSize;
    }

    void setFileSize(int fileSize){
        this->fileSize = fileSize;
    }
    void setFileName(QString fileName){
        this->fileName = fileName;
    }

private:
    QString fileName;
    int fileSize;
};

#endif // FILEINFO_H
