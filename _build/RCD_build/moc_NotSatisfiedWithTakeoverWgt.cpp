/****************************************************************************
** Meta object code from reading C++ file 'NotSatisfiedWithTakeoverWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Widget/NotSatisfiedWithTakeoverWgt/NotSatisfiedWithTakeoverWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NotSatisfiedWithTakeoverWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NotSatisfiedWithTakeoverWgt_t {
    QByteArrayData data[8];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NotSatisfiedWithTakeoverWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NotSatisfiedWithTakeoverWgt_t qt_meta_stringdata_NotSatisfiedWithTakeoverWgt = {
    {
QT_MOC_LITERAL(0, 0, 27), // "NotSatisfiedWithTakeoverWgt"
QT_MOC_LITERAL(1, 28, 31), // "on_pushButton_task_over_clicked"
QT_MOC_LITERAL(2, 60, 0), // ""
QT_MOC_LITERAL(3, 61, 12), // "onClDataCome"
QT_MOC_LITERAL(4, 74, 3), // "cmd"
QT_MOC_LITERAL(5, 78, 4), // "data"
QT_MOC_LITERAL(6, 83, 13), // "onModelUpdate"
QT_MOC_LITERAL(7, 97, 10) // "statuSlots"

    },
    "NotSatisfiedWithTakeoverWgt\0"
    "on_pushButton_task_over_clicked\0\0"
    "onClDataCome\0cmd\0data\0onModelUpdate\0"
    "statuSlots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotSatisfiedWithTakeoverWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    2,   40,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x2a /* Public | MethodCloned */,
       6,    1,   48,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    4,    5,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void NotSatisfiedWithTakeoverWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NotSatisfiedWithTakeoverWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_task_over_clicked(); break;
        case 1: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 2: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onModelUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->statuSlots(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NotSatisfiedWithTakeoverWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<IFunWidget::staticMetaObject>(),
    qt_meta_stringdata_NotSatisfiedWithTakeoverWgt.data,
    qt_meta_data_NotSatisfiedWithTakeoverWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NotSatisfiedWithTakeoverWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotSatisfiedWithTakeoverWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NotSatisfiedWithTakeoverWgt.stringdata0))
        return static_cast<void*>(this);
    return IFunWidget::qt_metacast(_clname);
}

int NotSatisfiedWithTakeoverWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IFunWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
