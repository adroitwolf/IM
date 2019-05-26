#-------------------------------------------------
#
# Project created by QtCreator 2019-03-14T21:51:44
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = service
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
QT += sql


SOURCES +=\
    main.cpp\
    view/mainwidget.cpp \
    business/mytcpserver.cpp \
    business/mytcpsocket.cpp \
    data/dbutil.cpp \
    data/mysql.cpp \
    business/action.cpp \
    business/myudpserver.cpp \
    business/msgaction.cpp \
    data/threadmysql.cpp

HEADERS  +=\
    view/mainwidget.h \
    business/mytcpserver.h \
    business/mytcpsocket.h \
    data/dbutil.h \
    data/datainfo.h \
    data/user.h \
    data/mysql.h \
    data/hostinfo.h \
    business/action.h \
    business/myudpserver.h \
    business/msgaction.h \
    data/userinfo.h \
    data/message.h \
    data/addfriendinfo.h \
    data/addfriend.h \
    data/logininfo.h \
    data/threadmysql.h

FORMS    += mainwidget.ui


