/****************************************************************************
** Meta object code from reading C++ file 'controlpub.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Control/include/controlpub.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpub.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlPub_t {
    QByteArrayData data[14];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlPub_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlPub_t qt_meta_stringdata_ControlPub = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ControlPub"
QT_MOC_LITERAL(1, 11, 29), // "HandleFisonControlRawDataSlot"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 4), // "data"
QT_MOC_LITERAL(4, 47, 26), // "HandleFisonControlDataSlot"
QT_MOC_LITERAL(5, 74, 21), // "HandleFisonStatusSlot"
QT_MOC_LITERAL(6, 96, 7), // "_status"
QT_MOC_LITERAL(7, 104, 21), // "HandleFisonButtonSlot"
QT_MOC_LITERAL(8, 126, 3), // "key"
QT_MOC_LITERAL(9, 130, 27), // "HandleFisonControlLightSlot"
QT_MOC_LITERAL(10, 158, 19), // "HandleVehicleStatus"
QT_MOC_LITERAL(11, 178, 21), // "HandlePubDataTimerOut"
QT_MOC_LITERAL(12, 200, 23), // "HandlePubStatusTimerOut"
QT_MOC_LITERAL(13, 224, 26) // "HandlePubSelfCheckTimerOut"

    },
    "ControlPub\0HandleFisonControlRawDataSlot\0"
    "\0data\0HandleFisonControlDataSlot\0"
    "HandleFisonStatusSlot\0_status\0"
    "HandleFisonButtonSlot\0key\0"
    "HandleFisonControlLightSlot\0"
    "HandleVehicleStatus\0HandlePubDataTimerOut\0"
    "HandlePubStatusTimerOut\0"
    "HandlePubSelfCheckTimerOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlPub[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    1,   62,    2, 0x0a /* Public */,
       5,    1,   65,    2, 0x0a /* Public */,
       7,    1,   68,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    0,   78,    2, 0x08 /* Private */,
      13,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::UChar,    6,
    QMetaType::Void, QMetaType::UInt,    8,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::UChar,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ControlPub::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControlPub *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->HandleFisonControlRawDataSlot((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->HandleFisonControlDataSlot((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->HandleFisonStatusSlot((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->HandleFisonButtonSlot((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 4: _t->HandleFisonControlLightSlot((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 5: _t->HandleVehicleStatus((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->HandlePubDataTimerOut(); break;
        case 7: _t->HandlePubStatusTimerOut(); break;
        case 8: _t->HandlePubSelfCheckTimerOut(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControlPub::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ControlPub.data,
    qt_meta_data_ControlPub,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControlPub::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlPub::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPub.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ControlPub::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
