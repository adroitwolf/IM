/****************************************************************************
** Meta object code from reading C++ file 'myudpserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../service/business/myudpserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myudpserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyUDPServer_t {
    QByteArrayData data[12];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyUDPServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyUDPServer_t qt_meta_stringdata_MyUDPServer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MyUDPServer"
QT_MOC_LITERAL(1, 12, 17), // "sendMessageToUser"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 4), // "data"
QT_MOC_LITERAL(4, 36, 9), // "receiveQQ"
QT_MOC_LITERAL(5, 46, 8), // "readData"
QT_MOC_LITERAL(6, 55, 11), // "getUserInfo"
QT_MOC_LITERAL(7, 67, 9), // "LoginInfo"
QT_MOC_LITERAL(8, 77, 9), // "loginInfo"
QT_MOC_LITERAL(9, 87, 13), // "getLogoutInfo"
QT_MOC_LITERAL(10, 101, 2), // "qq"
QT_MOC_LITERAL(11, 104, 11) // "sendMessage"

    },
    "MyUDPServer\0sendMessageToUser\0\0data\0"
    "receiveQQ\0readData\0getUserInfo\0LoginInfo\0"
    "loginInfo\0getLogoutInfo\0qq\0sendMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyUDPServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   44,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       9,    1,   48,    2, 0x0a /* Public */,
      11,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    3,    4,

       0        // eod
};

void MyUDPServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyUDPServer *_t = static_cast<MyUDPServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessageToUser((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->readData(); break;
        case 2: _t->getUserInfo((*reinterpret_cast< const LoginInfo(*)>(_a[1]))); break;
        case 3: _t->getLogoutInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendMessage((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MyUDPServer::*_t)(const QByteArray , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyUDPServer::sendMessageToUser)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MyUDPServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyUDPServer.data,
      qt_meta_data_MyUDPServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyUDPServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyUDPServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyUDPServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyUDPServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MyUDPServer::sendMessageToUser(const QByteArray _t1, const QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
