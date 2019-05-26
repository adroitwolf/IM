#include "action.h"


/**
 * function:处理用户业务
 * @brief Action::registerAction
 * @param user
 * @param info
 * @return
 */
Action::Action()
{
    this->sql = new DBUtil();
}

QString Action::registerAction(User user, HostInfo info)
{
    return sql->registerUser(user,info);
}

/**
 * function : 处理登陆业务
 * @brief Action::loginUserAction
 * @param user
 * @param info
 * @return
 */
UserInfo Action::loginUserAction(User user, HostInfo info)
{
    return sql->loginUser(user,info);
}

/**
 * function: 处理搜索业务
 * @brief Action::searchById
 * @param qq
 * @return
 */
User Action::searchById(QString qq)
{
    return sql->searchById(qq);
}


/**
 * function: 将好友添加请求保存到临时数据库
 * @brief Action::addNewFriend
 * @param addFriend
 */
void Action::addNewFriend(AddFriend addFriend)
{
    sql->addNewFriend(addFriend);
}


/**
 * function:查询自己是否有特定好友
 * @brief Action::searchFriend
 * @param friendQQ
 * @param selfQQ
 * @return
 */
bool Action::searchFriend(QString friendQQ, QString selfQQ)
{

    return sql->searchFriend(friendQQ,selfQQ);
}


/**
 * function:添加好友成功，保存到数据库
 * @brief Action::addNewFriendToDB
 * @param addFriend
 */
void Action::addNewFriendToDB(AddFriend addFriend)
{
    sql->addNewFriendToDB(addFriend);
}

/**
 * function: 存储离线消息
 * @brief Action::storageMsg
 * @param msg
 */
void Action::storageMsg(Message msg)
{
    sql->storageMsg(msg);
}


/**
 * 离线操作
 * @brief Action::logout
 * @param qq
 */
void Action::logout(const QString qq)
{
    sql->logout(qq);
}
