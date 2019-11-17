#ifndef ACTION_H
#define ACTION_H

#include "data/user.h"
#include "data/hostinfo.h"
#include "data/dbutil.h"
#include "data/message.h"
#include "data/filebean.h"
/**
 * function:处理用户业务
 * @brief The Action class
 */
class Action
{
public:

    Action();
    //注册业务
    QString registerAction(User user,HostInfo info);
   //登陆业务
    
    UserInfo loginUserAction(User user,HostInfo info);

    //搜索好友业务
    User searchById(QString qq);

    //添加好友请求业务
    void addNewFriend(AddFriend addFriend);

    //搜索特定好友
    bool searchFriend(QString friendQQ,QString selfQQ);


    //将好友写入数据库
    void addNewFriendToDB(AddFriend addFriend);

    //存储消息
    void storageMsg(Message msg);

    //离线
    void logout(const QString qq);

    //存储文件信息
    void saveFile(FileBean fileBean);

    //文件发送请求
    QString asksend(QString selfqq,QString qq);
private:
    DBUtil *sql;
};



#endif // ACTION_H
