#ifndef THREADMYSQL_H
#define THREADMYSQL_H

#include <QObject>

#include <QtSql>
#include <QQueue>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include<QDebug>
#include<QSettings>//配置文件

class ThreadMysql : public QObject
{
    Q_OBJECT
public:
    explicit ThreadMysql(qint32 socketDescriptor,QObject *parent = nullptr);
    //查询自己的好友
    bool searchFriend(QString qq,QString selfQQ);
signals:

public slots:

private:
    QSqlDatabase db;
};

#endif // THREADMYSQL_H
