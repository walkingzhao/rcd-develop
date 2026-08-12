/****************************************************************************
** Meta object code from reading C++ file 'FastStopWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Widget/FastStopWgt/FastStopWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FastStopWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FastStopWgt_t {
    QByteArrayData data[12];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FastStopWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FastStopWgt_t qt_meta_stringdata_FastStopWgt = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FastStopWgt"
QT_MOC_LITERAL(1, 12, 12), // "onClDataCome"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "cmd"
QT_MOC_LITERAL(4, 30, 4), // "data"
QT_MOC_LITERAL(5, 35, 13), // "onModelUpdate"
QT_MOC_LITERAL(6, 49, 9), // "showEvent"
QT_MOC_LITERAL(7, 59, 11), // "QShowEvent*"
QT_MOC_LITERAL(8, 71, 9), // "hideEvent"
QT_MOC_LITERAL(9, 81, 11), // "QHideEvent*"
QT_MOC_LITERAL(10, 93, 24), // "on_pushButton_ok_clicked"
QT_MOC_LITERAL(11, 118, 28) // "on_pushButton_cancel_clicked"

    },
    "FastStopWgt\0onClDataCome\0\0cmd\0data\0"
    "onModelUpdate\0showEvent\0QShowEvent*\0"
    "hideEvent\0QHideEvent*\0on_pushButton_ok_clicked\0"
    "on_pushButton_cancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FastStopWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x0a /* Public */,
       1,    1,   54,    2, 0x2a /* Public | MethodCloned */,
       5,    1,   57,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       8,    1,   63,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x08 /* Private */,
      11,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FastStopWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FastStopWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onModelUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        case 4: _t->hideEvent((*reinterpret_cast< QHideEvent*(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_ok_clicked(); break;
        case 6: _t->on_pushButton_cancel_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FastStopWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<IFunWidget::staticMetaObject>(),
    qt_meta_stringdata_FastStopWgt.data,
    qt_meta_data_FastStopWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FastStopWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FastStopWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FastStopWgt.stringdata0))
        return static_cast<void*>(this);
    return IFunWidget::qt_metacast(_clname);
}

int FastStopWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IFunWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
