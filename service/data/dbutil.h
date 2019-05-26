#ifndef DBUTIL_H
#define DBUTIL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "data/mysql.h"
#include "data/user.h"
#include "data/hostinfo.h"
#include "data/userinfo.h"
#include "data/message.h"
#include "data/addfriend.h"

/**
 * function: 数据库操作类
 * @brief The DBUtil class
 */
class DBUtil : public QObject
{
    Q_OBJECT
public:
    explicit DBUtil(QObject *parent = 0);

    //初始化数据库 将所有的用户都设置没OFFLINE离线状态
    bool initDatabase();
    //注册用户
    QString registerUser(User user,HostInfo info);

    //登陆用户
    UserInfo loginUser(User user,HostInfo info);

    //搜索用户
    User searchById(QString qq);

    //添加好友
    void addNewFriend(AddFriend addFriend);
    
    //添加好友成功，保存到数据库
    void addNewFriendToDB(AddFriend addFriend);

    //查询自己的好友
    bool searchFriend(QString qq,QString selfQQ);

    //储存离线消息
    void storageMsg(Message msg);

    //离线操作
    void logout(QString qq);
    void release(); //释放主线程数据库防止跨线程网速
private:
    QSqlDatabase creatConnection();
    void closeConnection(QSqlDatabase connection);

};

#endif // DBUTIL_H
