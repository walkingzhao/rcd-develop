/****************************************************************************
** Meta object code from reading C++ file 'CompleteOperEndWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Widget/CompleteOperEndWgt/CompleteOperEndWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CompleteOperEndWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CompleteOperEndWgt_t {
    QByteArrayData data[9];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CompleteOperEndWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CompleteOperEndWgt_t qt_meta_stringdata_CompleteOperEndWgt = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CompleteOperEndWgt"
QT_MOC_LITERAL(1, 19, 24), // "on_pushButton_ok_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 28), // "on_pushButton_cancel_clicked"
QT_MOC_LITERAL(4, 74, 12), // "onClDataCome"
QT_MOC_LITERAL(5, 87, 3), // "cmd"
QT_MOC_LITERAL(6, 91, 4), // "data"
QT_MOC_LITERAL(7, 96, 13), // "onModelUpdate"
QT_MOC_LITERAL(8, 110, 10) // "statuSlots"

    },
    "CompleteOperEndWgt\0on_pushButton_ok_clicked\0"
    "\0on_pushButton_cancel_clicked\0"
    "onClDataCome\0cmd\0data\0onModelUpdate\0"
    "statuSlots"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CompleteOperEndWgt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    2,   46,    2, 0x0a /* Public */,
       4,    1,   51,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   54,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    5,    6,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void CompleteOperEndWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CompleteOperEndWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_ok_clicked(); break;
        case 1: _t->on_pushButton_cancel_clicked(); break;
        case 2: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 3: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onModelUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->statuSlots(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CompleteOperEndWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<IFunWidget::staticMetaObject>(),
    qt_meta_stringdata_CompleteOperEndWgt.data,
    qt_meta_data_CompleteOperEndWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CompleteOperEndWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CompleteOperEndWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CompleteOperEndWgt.stringdata0))
        return static_cast<void*>(this);
    return IFunWidget::qt_metacast(_clname);
}

int CompleteOperEndWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IFunWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
