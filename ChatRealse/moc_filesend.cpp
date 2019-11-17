/****************************************************************************
** Meta object code from reading C++ file 'filesend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Chat/filesend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filesend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileSend_t {
    QByteArrayData data[10];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileSend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileSend_t qt_meta_stringdata_FileSend = {
    {
QT_MOC_LITERAL(0, 0, 8), // "FileSend"
QT_MOC_LITERAL(1, 9, 8), // "sendOver"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 12), // "agreeReceive"
QT_MOC_LITERAL(4, 32, 13), // "refuseReceive"
QT_MOC_LITERAL(5, 46, 14), // "requestReceive"
QT_MOC_LITERAL(6, 61, 16), // "fileSizeOverLoad"
QT_MOC_LITERAL(7, 78, 11), // "receivedBuf"
QT_MOC_LITERAL(8, 90, 3), // "buf"
QT_MOC_LITERAL(9, 94, 11) // "fileReceive"

    },
    "FileSend\0sendOver\0\0agreeReceive\0"
    "refuseReceive\0requestReceive\0"
    "fileSizeOverLoad\0receivedBuf\0buf\0"
    "fileReceive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileSend[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,
       6,    0,   53,    2, 0x06 /* Public */,
       7,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    8,

       0        // eod
};

void FileSend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileSend *_t = static_cast<FileSend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendOver(); break;
        case 1: _t->agreeReceive(); break;
        case 2: _t->refuseReceive(); break;
        case 3: _t->requestReceive(); break;
        case 4: _t->fileSizeOverLoad(); break;
        case 5: _t->receivedBuf((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->fileReceive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileSend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSend::sendOver)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileSend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSend::agreeReceive)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileSend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSend::refuseReceive)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FileSend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSend::requestReceive)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FileSend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSend::fileSizeOverLoad)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FileSend::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSend::receivedBuf)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileSend::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_FileSend.data,
    qt_meta_data_FileSend,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileSend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileSend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileSend.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FileSend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void FileSend::sendOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FileSend::agreeReceive()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FileSend::refuseReceive()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FileSend::requestReceive()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void FileSend::fileSizeOverLoad()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void FileSend::receivedBuf(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
