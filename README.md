# 基于qt c++的一个即时通讯软件
-----
## 项目说明
这个软件是我大二学期的一个c++课设，ui方面是仿照着pc端的wechat,由于本人不太喜欢c++的语法，所以这个软件更新的速度会很慢。

## 项目功能

**账号方面**

* 账号注册
* 账号登陆

**好友方面**

* 添加好友
* 查询好友
* 请求好友通知

**消息方面**

* 离线消息通知
* 在线消息

## 技术选型

开发语言： c++
基础框架: MVC
核心技术：多线程QTcpSocket +多线程QUdpSocket + 数据库连接池
数据库： mysql

## 重要说明

服务器这边我打算采用的是mvc架构，但是在最后的时候测试bug的时候发现数据库这边不允许主线程和子线程同时访问，考虑到子线程访问次数比较少，所以直接新建了一个类去让子线程直接访问数据库，打破了mvc模式，以后应该会改的。。。大概。。

## 数据库连接

数据库只有服务端有连接，分别在mysql.cpp和threadmysql.cpp中有连接信息，并没有单独出丑来做一个资源文件，耦合度很高。
