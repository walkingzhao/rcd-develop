/****************************************************************************
** Meta object code from reading C++ file 'MainCameraWgt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Widget/MainCameraWgt/MainCameraWgt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainCameraWgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainCameraWgt_t {
    QByteArrayData data[8];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainCameraWgt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainCameraWgt_t qt_meta_stringdata_MainCameraWgt = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainCameraWgt"
QT_MOC_LITERAL(1, 14, 12), // "onClDataCome"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "cmd"
QT_MOC_LITERAL(4, 32, 4), // "data"
QT_MOC_LITERAL(5, 37, 13), // "onModelUpdate"
QT_MOC_LITERAL(6, 51, 13), // "slotTimerTest"
QT_MOC_LITERAL(7, 65, 13) // "get_net_usage"

    },
    "MainCameraWgt\0onClDataCome\0\0cmd\0data\0"
    "onModelUpdate\0slotTimerTest\0get_net_usage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainCameraWgt[] = {

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
       1,    2,   39,    2, 0x0a /* Public */,
       1,    1,   44,    2, 0x2a /* Public | MethodCloned */,
       5,    1,   47,    2, 0x0a /* Public */,
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Bool,

       0        // eod
};

void MainCameraWgt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainCameraWgt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->onClDataCome((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onModelUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotTimerTest(); break;
        case 4: { bool _r = _t->get_net_usage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainCameraWgt::staticMetaObject = { {
    QMetaObject::SuperData::link<IFunWidget::staticMetaObject>(),
    qt_meta_stringdata_MainCameraWgt.data,
    qt_meta_data_MainCameraWgt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainCameraWgt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainCameraWgt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainCameraWgt.stringdata0))
        return static_cast<void*>(this);
    return IFunWidget::qt_metacast(_clname);
}

int MainCameraWgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
