/****************************************************************************
** Meta object code from reading C++ file 'IController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Interface/IController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IController_t {
    QByteArrayData data[10];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IController_t qt_meta_stringdata_IController = {
    {
QT_MOC_LITERAL(0, 0, 11), // "IController"
QT_MOC_LITERAL(1, 12, 14), // "pushDataToView"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "cmd"
QT_MOC_LITERAL(4, 32, 4), // "data"
QT_MOC_LITERAL(5, 37, 10), // "sendToMain"
QT_MOC_LITERAL(6, 48, 9), // "ModuleDir"
QT_MOC_LITERAL(7, 58, 9), // "moduleDir"
QT_MOC_LITERAL(8, 68, 8), // "nameList"
QT_MOC_LITERAL(9, 77, 6) // "subcmd"

    },
    "IController\0pushDataToView\0\0cmd\0data\0"
    "sendToMain\0ModuleDir\0moduleDir\0nameList\0"
    "subcmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       1,    1,   44,    2, 0x26 /* Public | MethodCloned */,
       5,    3,   47,    2, 0x06 /* Public */,
       5,    2,   54,    2, 0x26 /* Public | MethodCloned */,
       5,    5,   59,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QVariant,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::QVariant,    7,    3,    4,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    7,    3,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QStringList, QMetaType::Int, QMetaType::Int, QMetaType::QVariant,    7,    8,    3,    9,    4,

       0        // eod
};

void IController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pushDataToView((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        case 1: _t->pushDataToView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendToMain((*reinterpret_cast< ModuleDir(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 3: _t->sendToMain((*reinterpret_cast< ModuleDir(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->sendToMain((*reinterpret_cast< ModuleDir(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QVariant(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ModuleDir >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ModuleDir >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ModuleDir >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IController::*)(int , QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IController::pushDataToView)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IController::*)(ModuleDir , int , QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IController::sendToMain)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IController::*)(ModuleDir , QStringList , int , int , QVariant );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IController::sendToMain)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IController.data,
    qt_meta_data_IController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void IController::pushDataToView(int _t1, QVariant _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void IController::sendToMain(ModuleDir _t1, int _t2, QVariant _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void IController::sendToMain(ModuleDir _t1, QStringList _t2, int _t3, int _t4, QVariant _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
