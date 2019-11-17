/****************************************************************************
** Meta object code from reading C++ file 'mytcpsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../service/business/mytcpsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mytcpsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyTcpSocket_t {
    QByteArrayData data[28];
    char stringdata0[303];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyTcpSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyTcpSocket_t qt_meta_stringdata_MyTcpSocket = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyTcpSocket"
QT_MOC_LITERAL(1, 12, 11), // "receiveData"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "socketDescriptor"
QT_MOC_LITERAL(4, 42, 8), // "HostInfo"
QT_MOC_LITERAL(5, 51, 4), // "info"
QT_MOC_LITERAL(6, 56, 16), // "socketDisconnect"
QT_MOC_LITERAL(7, 73, 13), // "moveUserToMap"
QT_MOC_LITERAL(8, 87, 2), // "qq"
QT_MOC_LITERAL(9, 90, 16), // "sendRegisterData"
QT_MOC_LITERAL(10, 107, 2), // "rs"
QT_MOC_LITERAL(11, 110, 13), // "sendLoginData"
QT_MOC_LITERAL(12, 124, 8), // "UserInfo"
QT_MOC_LITERAL(13, 133, 14), // "sendSearchData"
QT_MOC_LITERAL(14, 148, 4), // "User"
QT_MOC_LITERAL(15, 153, 4), // "user"
QT_MOC_LITERAL(16, 158, 23), // "sendAdviceLoginOrLogOut"
QT_MOC_LITERAL(17, 182, 6), // "status"
QT_MOC_LITERAL(18, 189, 10), // "sendAddnew"
QT_MOC_LITERAL(19, 200, 16), // "addFriendSuccess"
QT_MOC_LITERAL(20, 217, 7), // "friendL"
QT_MOC_LITERAL(21, 225, 17), // "sendMessageToUser"
QT_MOC_LITERAL(22, 243, 4), // "data"
QT_MOC_LITERAL(23, 248, 17), // "answerFileRequest"
QT_MOC_LITERAL(24, 266, 6), // "result"
QT_MOC_LITERAL(25, 273, 11), // "fileReceive"
QT_MOC_LITERAL(26, 285, 8), // "FileBean"
QT_MOC_LITERAL(27, 294, 8) // "fileBean"

    },
    "MyTcpSocket\0receiveData\0\0socketDescriptor\0"
    "HostInfo\0info\0socketDisconnect\0"
    "moveUserToMap\0qq\0sendRegisterData\0rs\0"
    "sendLoginData\0UserInfo\0sendSearchData\0"
    "User\0user\0sendAdviceLoginOrLogOut\0"
    "status\0sendAddnew\0addFriendSuccess\0"
    "friendL\0sendMessageToUser\0data\0"
    "answerFileRequest\0result\0fileReceive\0"
    "FileBean\0fileBean"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyTcpSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       6,    1,   79,    2, 0x06 /* Public */,
       7,    2,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   87,    2, 0x0a /* Public */,
      11,    2,   92,    2, 0x0a /* Public */,
      13,    2,   97,    2, 0x0a /* Public */,
      16,    3,  102,    2, 0x0a /* Public */,
      18,    2,  109,    2, 0x0a /* Public */,
      19,    2,  114,    2, 0x0a /* Public */,
      21,    2,  119,    2, 0x0a /* Public */,
      23,    2,  124,    2, 0x0a /* Public */,
      25,    2,  129,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,    3,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Bool,    3,    8,   17,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 14,    3,   15,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,    3,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::QByteArray,    3,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 26,    3,   27,

       0        // eod
};

void MyTcpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyTcpSocket *_t = static_cast<MyTcpSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const HostInfo(*)>(_a[2]))); break;
        case 1: _t->socketDisconnect((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->moveUserToMap((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->sendRegisterData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->sendLoginData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const UserInfo(*)>(_a[2]))); break;
        case 5: _t->sendSearchData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const User(*)>(_a[2]))); break;
        case 6: _t->sendAdviceLoginOrLogOut((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3]))); break;
        case 7: _t->sendAddnew((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< const User(*)>(_a[2]))); break;
        case 8: _t->addFriendSuccess((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const User(*)>(_a[2]))); break;
        case 9: _t->sendMessageToUser((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 10: _t->answerFileRequest((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 11: _t->fileReceive((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< const FileBean(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MyTcpSocket::*_t)(qint32 , const HostInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpSocket::receiveData)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyTcpSocket::*_t)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpSocket::socketDisconnect)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MyTcpSocket::*_t)(qint32 , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyTcpSocket::moveUserToMap)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject MyTcpSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_MyTcpSocket.data,
      qt_meta_data_MyTcpSocket,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyTcpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyTcpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyTcpSocket.stringdata0))
        return static_cast<void*>(this);
    return QTcpSocket::qt_metacast(_clname);
}

int MyTcpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MyTcpSocket::receiveData(qint32 _t1, const HostInfo & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyTcpSocket::socketDisconnect(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyTcpSocket::moveUserToMap(qint32 _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
