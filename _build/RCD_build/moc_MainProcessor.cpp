/****************************************************************************
** Meta object code from reading C++ file 'MainProcessor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/MainFile/MainProcessor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainProcessor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainProcessor_t {
    QByteArrayData data[12];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainProcessor_t qt_meta_stringdata_MainProcessor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainProcessor"
QT_MOC_LITERAL(1, 14, 8), // "killProc"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "getFromAny"
QT_MOC_LITERAL(4, 35, 9), // "ModuleDir"
QT_MOC_LITERAL(5, 45, 9), // "moduleDir"
QT_MOC_LITERAL(6, 55, 3), // "cmd"
QT_MOC_LITERAL(7, 59, 4), // "data"
QT_MOC_LITERAL(8, 64, 12), // "procFinished"
QT_MOC_LITERAL(9, 77, 8), // "exitCode"
QT_MOC_LITERAL(10, 86, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(11, 107, 10) // "exitStatus"

    },
    "MainProcessor\0killProc\0\0getFromAny\0"
    "ModuleDir\0moduleDir\0cmd\0data\0procFinished\0"
    "exitCode\0QProcess::ExitStatus\0exitStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainProcessor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   30,    2, 0x0a /* Public */,
       8,    2,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int, QMetaType::QVariant,    5,    6,    7,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,

       0        // eod
};

void MainProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->killProc(); break;
        case 1: _t->getFromAny((*reinterpret_cast< ModuleDir(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 2: _t->procFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
            using _t = void (MainProcessor::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainProcessor::killProc)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainProcessor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MainProcessor.data,
    qt_meta_data_MainProcessor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MainProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void MainProcessor::killProc()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
