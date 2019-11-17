/****************************************************************************
** Meta object code from reading C++ file 'registwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Chat/registwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RegistWidget_t {
    QByteArrayData data[8];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RegistWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RegistWidget_t qt_meta_stringdata_RegistWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RegistWidget"
QT_MOC_LITERAL(1, 13, 8), // "BackLand"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 21), // "on_ButtonBack_clicked"
QT_MOC_LITERAL(4, 45, 23), // "on_ButtonRegist_clicked"
QT_MOC_LITERAL(5, 69, 12), // "isRegistSlot"
QT_MOC_LITERAL(6, 82, 4), // "qqId"
QT_MOC_LITERAL(7, 87, 21) // "on_ButtonSure_clicked"

    },
    "RegistWidget\0BackLand\0\0on_ButtonBack_clicked\0"
    "on_ButtonRegist_clicked\0isRegistSlot\0"
    "qqId\0on_ButtonSure_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RegistWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void RegistWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RegistWidget *_t = static_cast<RegistWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BackLand(); break;
        case 1: _t->on_ButtonBack_clicked(); break;
        case 2: _t->on_ButtonRegist_clicked(); break;
        case 3: _t->isRegistSlot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_ButtonSure_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RegistWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RegistWidget::BackLand)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RegistWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_RegistWidget.data,
    qt_meta_data_RegistWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RegistWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegistWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RegistWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RegistWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void RegistWidget::BackLand()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
