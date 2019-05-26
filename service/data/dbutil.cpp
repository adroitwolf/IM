#include "dbutil.h"

#include <QDebug>
#include <QDateTime>




//所有人设置为离线
static const QString UPDATE_STATUS_IN_LOGIN_SQL =
        "update login set Lstatus = 0";

static const QString UPDATE_STATUS_IN_FRIENDS_SQL =
        "update friends set fstatus = 0";

static const QString UPDATE_LOGIN_STATUS_SQL =
        "update login set Lstatus = 0 where Lqq = '%1'";

//注册账号
static const QString INSERT_USER_IN_USER_SQL =
        "insert into user(pwd,sign,nickname,sex) values('%1','%2','%3','%4')";

static const QString INSERT_LOGIN_SQL =
        "insert into login(Lip,Lport,Ldate,Lstatus,Lqq,Ldesk) values('%1','%2','%3','%4','%5','%6')";

//"SELECT LAST_INSERT_ID()";
static const QString GET_USER_ID_IN_USER_SQL =
        "select max(qq) from user";

//登陆账号
static const QString GET_USER_INFO_SQL =
        "select * from user where qq = '%1' ";

static const QString GET_USER_STATUS_SQL =
        "select * from login where Lqq = '%1'";

static const QString UPDATE_LOGIN_SQL = 
        "update login set Lip = '%1',Lport = '%2' , Ldate = '%3',Ldesk = '%4',Lstatus = '%5' where Lqq = '%6'";

static const QString GET_FRIEND_LIST_SQL =
        "select * from friends where qq = '%1'";

static const QString GET_MESSAGE_SQL =
        "select * from chatinfo where receiveqq = '%1'";

static const QString UPDATE_FRIEND_STATUS_SQL =
        "update friends set fstatus = '%1' where fqq = '%2'";

static const QString FIND_ADD_FRIEND_SQL =
        "select * from addfriends where receviceQQ = '%1'";

static const QString CONSUMER_ADD_FRIEND_INFO_SQL =
        "delete from addfriends where receviceQQ = '%1'";

static const QString DELETE_MESSAGE_SQL =
        "delete from chatinfo where receiveqq = '%1'";


//搜索好友
static const QString SEARCH_BY_ID_SQL =
        "select * from user where qq = '%1'";

//查询数据库中有没有特定好友
const static QString SEARCH_FRINED_BY_ID =
        "select * from friends where qq = '%1'";


//添加好友数据库的请求
const static QString ADD_FRIEND_SQL =
        "insert into addfriends(requestQQ,receviceQQ) values('%1','%2')";

//添加好友同意，添加到好优酷
const static QString ADD_FRIEND_TO_DB_SQL =
        "insert into friends (fqq,qq,fstatus,FNickName) values('%1','%2','%3','%4')";

//储存离线消息
const static QString ADD_MSG_SQL =
        "insert into chatinfo (context,sendqq,receiveqq,cdate) values('%1','%2','%3','%4')";

DBUtil::DBUtil(QObject *parent) : QObject(parent)
{

}


/**
 * function: 初始化数据库 将所有用户的状态status设置为OFFLINE
 * @brief DBUtil::initDatabase
 * @return
 */
bool DBUtil::initDatabase()
{

      QSqlDatabase sql =  creatConnection();
      QSqlQuery query(sql);
      if(query.exec(UPDATE_STATUS_IN_LOGIN_SQL)){
          qDebug()<<"初始化成功！";
      }else{
          qDebug()<<"初始化失败！";
      }
      if(!query.exec(UPDATE_STATUS_IN_FRIENDS_SQL)){
          qDebug()<<"failed";
      }

      if (!query.isActive())
      {
          return false;
      }
      sql.commit();
      closeConnection(sql);

      return true;
}

/**
 * function:获取连接
 * @brief DBUtil::creatConnection
 * @return
 */
QSqlDatabase DBUtil::creatConnection()
{
    return ConnectionPool::openConnection();

}

/**
 * function: 关闭连接
 * @brief DBUtil::closeConnection
 * @param connection
 */
void DBUtil::closeConnection(QSqlDatabase connection)
{
    ConnectionPool::closeConnection(connection);
}

void DBUtil::release()
{
    ConnectionPool::release();
}


/**
 * function:创建账号
 * @brief DBUtil::registerUser
 * @param user
 * @return
 * //TODO : 这里应该加上事务 还有锁 保证线程安全
 */
QString DBUtil::registerUser(User user,HostInfo info)
{
    QString qqId = NULL;

    QSqlDatabase sql = creatConnection();

    QString test = INSERT_USER_IN_USER_SQL.arg(user.getPwd())
            .arg(user.getSign())
            .arg(user.getNickName())
            .arg(user.getSex());
    qDebug()<<test;

    QSqlQuery query(sql);
//    query.prepare(INSERT_USER_IN_USER_SQL);
//    query.bindValue(0,user.getPwd());
//    query.bindValue(1,user.getSign());
//    query.bindValue(2,user.getNickName());
//    query.bindValue(3,user.getSex());

    if(!query.exec(INSERT_USER_IN_USER_SQL.arg(user.getPwd())
                  .arg(user.getSign())
                  .arg(user.getNickName())
                  .arg(user.getSex()))){
        return NULL;
    }

    sql.commit();

    qDebug()<<1;

    query.exec(GET_USER_ID_IN_USER_SQL);
    while (query.next()) {
        qqId = query.value(0).toString();
    }

//    query.prepare(INSERT_LOGIN_SQL);
//    query.bindValue(0,info.ip);
//    query.bindValue(1,info.port);
//    query.bindValue(2,QDate::currentDate().toString("yyyy-MM-dd hh:mm:ss"));
//    query.bindValue(3,0);
//    query.bindValue(4,qqId);

    qDebug()<<INSERT_LOGIN_SQL.arg(info.getIp())
              .arg(info.getPort())
              .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
              .arg(0)
              .arg(qqId)
              .arg(info.getDesk());

    if(!query.exec(INSERT_LOGIN_SQL.arg(info.getIp())
                   .arg(info.getPort())
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(0)
            .arg(qqId)
            .arg(info.getDesk()))){
        return NULL;
    }

    sql.commit();
    closeConnection(sql);

    return qqId;

}


/**
 * function : 登陆用户业务
 * @brief DBUtil::loginUser
 * @param user
 * @return
 */
UserInfo DBUtil::loginUser(User user,HostInfo info)
{

    UserInfo userInfo;
    User mUser;
    QSqlDatabase sql = creatConnection();
    QSqlQuery query(sql);
//    query.prepare(LOGIN_SQL);
//    query.addBindValue(user.getqq());
    if(!query.exec(GET_USER_INFO_SQL.arg(user.getqq()))){
        qDebug()<<"登陆失败!";
    }
    while (query.next()) {
        if(query.value(1).toString() == user.getPwd()){ //验证密码
            mUser.setqq(query.value(0).toString());
            mUser.setPwd(query.value(1).toString());
            mUser.setSign(query.value(2).toString());
            mUser.setNickName(query.value(3).toString());
            mUser.setSex(query.value(4).toString());
        }
    }
    if(mUser.getqq().isEmpty()){ //说明账号密码错误
        userInfo.setInfo("failed");
        return userInfo;
    }


    if(!query.exec(GET_USER_STATUS_SQL.arg(mUser.getqq()))){
        qDebug()<<"查询失败";
    }

    while (query.next()) {
        if(query.value(4).toInt() == 1){ //说明上线
            userInfo.setInfo("error");
            return userInfo;
        }
    }


    userInfo.setUser(mUser);
    //到这里说明用户已经输入正确了
    //更新数据库登录时间
    if(!query.exec(UPDATE_LOGIN_SQL.arg(info.getIp())
                   .arg(info.getPort())
                   .arg(QDateTime::currentDateTime().toString())
                   .arg(info.getDesk())
                   .arg(1)
                   .arg(mUser.getqq()))){
        qDebug()<<"数据库更新Login表失败！";
    }

    //同时更新friend表中自己的在线情况
    if(!query.exec(UPDATE_FRIEND_STATUS_SQL.arg(1)
                   .arg(mUser.getqq()))){
        qDebug()<<"failed";
    }

    //获取好友列表
    if(!query.exec(GET_FRIEND_LIST_SQL.arg(mUser.getqq()))){
        qDebug()<<"获取好友列表失败";
    }
    QList<User> friends;

    while (query.next()) {
        User friendInfo;
        friendInfo.setqq(query.value(1).toString());
        friendInfo.setStatus(query.value(3).toString());
        friendInfo.setNickName(query.value(4).toString());
        friends.append(friendInfo);
    }

    userInfo.setFriends(friends);

    //获取离线的时候的信息

    QList<Message> msgs;

    if(!query.exec(GET_MESSAGE_SQL.arg(mUser.getqq()))){
        qDebug()<<"获取离线信息失败";
    }



    while (query.next()) {
        Message msg;
        msg.setContext(query.value(1).toString());
        msg.setSenderQQ(query.value(2).toString());

        msg.setCDate(query.value(4).toString());
        msgs.append(msg);
    }

    userInfo.setMessage(msgs);

    if(msgs.size() >0){ //如果有消息
        if(!query.exec(DELETE_MESSAGE_SQL.arg(mUser.getqq()))){
            qDebug()<<QString("删除好友信息失败");
        }
    }

    QList<User> addRequest;

    if(!query.exec(FIND_ADD_FRIEND_SQL.arg(mUser.getqq()))){
        qDebug()<<QString("用户登陆DAO  --> 获取添加请求失败");
    }
    while (query.next()) {
        User user;
        user.setqq(query.value(1).toString());

        QSqlQuery query2(sql);
        if(!query2.exec(SEARCH_BY_ID_SQL.arg(user.getqq()))){
            qDebug()<<QString("用户登陆DAO");
        }
        while(query2.next()){
            user.setNickName(query2.value(3).toString());
            user.setSex(query2.value(4).toString());
            user.setSign(query2.value(2).toString());
        }



        if(!query2.exec(CONSUMER_ADD_FRIEND_INFO_SQL.arg(mUser.getqq()))){
            qDebug()<<QString("用户登陆DAO");
        }
        addRequest.append(user);
    }


    userInfo.setInfo("success");

    userInfo.setAddRequest(addRequest);



    closeConnection(sql);
    return userInfo;
}

/**
 * function: 查询好友
 * @brief DBUtil::searchById
 * @param qq
 * @return
 */
User DBUtil::searchById(QString qq)
{
    QSqlDatabase sql = creatConnection();


    QSqlQuery query(sql);
    qDebug()<<SEARCH_BY_ID_SQL.arg(qq);
    if(!query.exec(SEARCH_BY_ID_SQL.arg(qq))){
        qDebug()<<QString("用户登陆DAO -->好友搜索失败");
    }

    User user;

    while(query.next()){
        user.setqq(query.value(0).toString());
        user.setNickName(query.value(3).toString());
        user.setSign(query.value(2).toString());
        user.setSex(query.value(4).toString());
    }

    closeConnection(sql);

    return user;
}




/**
 * function:查询自己好友库中有没有特定好友
 * @brief DBUtil::searchFriend
 * @param qq
 * @param selfQQ
 * @return
 */
bool DBUtil::searchFriend(QString qq, QString selfQQ)
{
     QSqlDatabase sql = creatConnection();
     QSqlQuery query(sql);
     if(!query.exec(SEARCH_FRINED_BY_ID.arg(selfQQ))){
         qDebug()<<"执行失败";
         return false;
     }

     while (query.next()) {
         if(qq == query.value(1).toString()){
             closeConnection(sql);
             return true;
         }
     }

     closeConnection(sql);


     return false;

}

/**
 * function: 存储离线消息
 * @brief DBUtil::storageMsg
 * @param msg
 */
void DBUtil::storageMsg(Message msg)
{
    QSqlDatabase sql = creatConnection();

    QSqlQuery query(sql);

    if(!query.exec(ADD_MSG_SQL.arg(msg.getContext())
                   .arg(msg.getSenderQQ())
                   .arg(msg.getReceviceQQ())
                   .arg(msg.getCDate()))){
        qDebug()<<QString("存储离线消息失败");
    }


    closeConnection(sql);
}

/**
 * function: 离线操作
 * @brief DBUtil::logout
 * @param qq
 */
void DBUtil::logout(QString qq)
{
    QSqlDatabase sql = creatConnection();

    QSqlQuery query(sql);



    if(!query.exec(UPDATE_FRIEND_STATUS_SQL.arg(0)
                   .arg(qq))){
        qDebug()<<QString("用户离线数据操作失败1");
    }
    if(!query.exec(UPDATE_LOGIN_STATUS_SQL.arg(qq))){
            qDebug()<<QString("用户离线数据操作失败2");
    }
    closeConnection(sql);
}


/**
 * 将添加好友请求发送到数据库
 * @brief DBUtil::addNewFriend
 * @param addFriend
 */
void DBUtil::addNewFriend(AddFriend addFriend)
{
    QSqlDatabase sql = creatConnection();

    QSqlQuery query(sql);


    if(!query.exec(ADD_FRIEND_SQL.arg(addFriend.getRequestQQ())
                   .arg(addFriend.getReceiveQQ()))){
        qDebug()<<QString("添加好友请求失败");
    }

    closeConnection(sql);

}


/**
 * function : 添加好友成功，保存到数据库
 * @brief DBUtil::addNewFriendToDB
 * @param addFriend
 */
void DBUtil::addNewFriendToDB(AddFriend addFriend)
{
       QSqlDatabase sql = creatConnection();
       QSqlQuery query(sql);

       User recevice;


       if(!query.exec(SEARCH_BY_ID_SQL.arg(addFriend.getReceiveQQ()))){
       }
       while (query.next()) {
           recevice.setNickName(query.value(3).toString());
           recevice.setStatus("1");
       }

       if(!query.exec(ADD_FRIEND_TO_DB_SQL.arg(addFriend.getReceiveQQ())
                      .arg(addFriend.getRequestQQ())
                      .arg(recevice.getStatus())
                      .arg(recevice.getNickName()))){
           qDebug()<<QString("DAO-- 好友");
       }

       User request;
       if(!query.exec(SEARCH_BY_ID_SQL.arg(addFriend.getRequestQQ()))){

       }

       while (query.next()) {
           request.setNickName(query.value(3).toString());
           request.setStatus("0");
       }
       if(!query.exec(ADD_FRIEND_TO_DB_SQL.arg(addFriend.getRequestQQ())
                      .arg(addFriend.getReceiveQQ())
                      .arg(request.getStatus())
                      .arg(request.getNickName()))){
           qDebug()<<QString("DAO-->好友");
       }

       closeConnection(sql);
}








