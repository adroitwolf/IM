#include "threadmysql.h"

//查询数据库中有没有特定好友
const static QString SEARCH_FRINED_BY_ID =
        "select * from friends where qq = '%1'";

ThreadMysql::ThreadMysql(qint32 socketDescriptor, QObject *parent): QObject(parent)
{
    QString connectionName = (QString)socketDescriptor;
        db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            db.setHostName("127.0.0.1");
            db.setDatabaseName("qq"); // 如果是 SQLite 则为数据库文件名
            db.setUserName("root");   // 如果是 SQLite 不需要
            db.setPassword("123");   // 如果是 SQLite 不需要

            if (!db.open()) {
                    qDebug() << "Connect to MySql error: " << db.lastError().text();

            }
}

bool ThreadMysql::searchFriend(QString qq, QString selfQQ)
{

    QSqlQuery query(db);
    if(!query.exec(SEARCH_FRINED_BY_ID.arg(selfQQ))){
        qDebug()<<"执行失败";
        return false;
    }

    while (query.next()) {
        if(qq == query.value(1).toString()){
            return true;
        }
    }


    return false;
}
