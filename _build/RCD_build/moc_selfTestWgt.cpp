/****************************************************************************
** Meta object code from reading C++ file 'selfTestWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Widget/selfTestWgt/selfTestWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selfTestWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_selfTestWgt_t {
    QByteArrayData data[7];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_selfTestWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_selfTestWgt_t qt_meta_stringdata_selfTestWgt = {
    {
QT_MOC_LITERAL(0, 0, 11), // "selfTestWgt"
QT_MOC_LITERAL(1, 12, 10), // "statuSlots"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 12), // "onClDataCome"
QT_MOC_LITERAL(4, 37, 3), // "cmd"
QT_MOC_LITERAL(5, 41, 4), // "data"
QT_MOC_LITERAL(6, 46, 13) // "onModelUpdate"

    },
    "selfTestWgt\0statuSlots\0\0onClDataCome\0"
    "cmd\0data\0onModelUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_selfTestWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    2,   35,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x2a /* Public | MethodCloned */,
       6,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    4,    5,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void selfTestWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<selfTestWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->statuSlots(); break;
        case 1: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 2: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onModelUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject selfTestWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<IFunWidget::staticMetaObject>(),
    qt_meta_stringdata_selfTestWgt.data,
    qt_meta_data_selfTestWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *selfTestWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *selfTestWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_selfTestWgt.stringdata0))
        return static_cast<void*>(this);
    return IFunWidget::qt_metacast(_clname);
}

int selfTestWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IFunWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
