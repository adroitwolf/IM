#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T14:41:36
#
#-------------------------------------------------

QT       += core gui network
RC_ICONS += OO.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        landwidget.cpp \
    mainwidget.cpp \
    registwidget.cpp \
    enterwidget.cpp \
    opreate/RegistOp.cpp \
    itemwidget.cpp \
    opreate/EnterOp.cpp \
    itemwidget.cpp \
    opreate/MainOp.cpp \
    addfriendwidget.cpp \
    opreate/AddFriendOp.cpp \
    selfinfowidget.cpp \
    setwidget.cpp

HEADERS += \
        landwidget.h \
    mainwidget.h \
    registwidget.h \
    enterwidget.h \
    opreate/RegistOp.h \
    Json/datainfo.h \
    Json/user.h \
    Json/hostinfo.h \
    itemwidget.h \
    opreate/EnterOp.h \
    itemwidget.h \
    opreate/MainOp.h \
    Json/userinfo.h \
    addfriendwidget.h \
    opreate/AddFriendOp.h \
    selfinfowidget.h \
    setwidget.h \
    Json/message.h \
    Json/userwithmsg.h

FORMS += \
        landwidget.ui \
    mainwidget.ui \
    registwidget.ui \
    enterwidget.ui \
    itemwidget.ui \
    itemwidget.ui \
    addfriendwidget.ui \
    selfinfowidget.ui \
    setwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc \
    resource.qrc

DISTFILES +=
