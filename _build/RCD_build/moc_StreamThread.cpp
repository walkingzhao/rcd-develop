/****************************************************************************
** Meta object code from reading C++ file 'StreamThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Component/StreamThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StreamThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StreamThread_t {
    QByteArrayData data[21];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StreamThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StreamThread_t qt_meta_stringdata_StreamThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StreamThread"
QT_MOC_LITERAL(1, 13, 11), // "sglFinished"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "sglAsyncUpdateUi"
QT_MOC_LITERAL(4, 43, 3), // "img"
QT_MOC_LITERAL(5, 47, 12), // "sglVideoInfo"
QT_MOC_LITERAL(6, 60, 3), // "fps"
QT_MOC_LITERAL(7, 64, 16), // "sglSyncUpdateYUV"
QT_MOC_LITERAL(8, 81, 12), // "const uchar*"
QT_MOC_LITERAL(9, 94, 6), // "Yplane"
QT_MOC_LITERAL(10, 101, 6), // "Uplane"
QT_MOC_LITERAL(11, 108, 6), // "Vplane"
QT_MOC_LITERAL(12, 115, 5), // "width"
QT_MOC_LITERAL(13, 121, 6), // "height"
QT_MOC_LITERAL(14, 128, 16), // "sglSyncUpdateRGB"
QT_MOC_LITERAL(15, 145, 8), // "uint8_t*"
QT_MOC_LITERAL(16, 154, 3), // "rgb"
QT_MOC_LITERAL(17, 158, 6), // "doWork"
QT_MOC_LITERAL(18, 165, 12), // "outputResize"
QT_MOC_LITERAL(19, 178, 1), // "w"
QT_MOC_LITERAL(20, 180, 1) // "h"

    },
    "StreamThread\0sglFinished\0\0sglAsyncUpdateUi\0"
    "img\0sglVideoInfo\0fps\0sglSyncUpdateYUV\0"
    "const uchar*\0Yplane\0Uplane\0Vplane\0"
    "width\0height\0sglSyncUpdateRGB\0uint8_t*\0"
    "rgb\0doWork\0outputResize\0w\0h"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StreamThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       3,    0,   58,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       7,    5,   62,    2, 0x06 /* Public */,
      14,    3,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,   80,    2, 0x0a /* Public */,
      18,    2,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPixmap,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    6,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 8, QMetaType::UInt, QMetaType::UInt,    9,   10,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::UInt, QMetaType::UInt,   16,   12,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   19,   20,

       0        // eod
};

void StreamThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StreamThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglFinished(); break;
        case 1: _t->sglAsyncUpdateUi((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->sglAsyncUpdateUi(); break;
        case 3: _t->sglVideoInfo((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->sglSyncUpdateYUV((*reinterpret_cast< const uchar*(*)>(_a[1])),(*reinterpret_cast< const uchar*(*)>(_a[2])),(*reinterpret_cast< const uchar*(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5]))); break;
        case 5: _t->sglSyncUpdateRGB((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 6: _t->doWork(); break;
        case 7: _t->outputResize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StreamThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamThread::sglFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StreamThread::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamThread::sglAsyncUpdateUi)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StreamThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamThread::sglAsyncUpdateUi)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (StreamThread::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamThread::sglVideoInfo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (StreamThread::*)(const uchar * , const uchar * , const uchar * , uint , uint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamThread::sglSyncUpdateYUV)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (StreamThread::*)(uint8_t * , uint , uint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&StreamThread::sglSyncUpdateRGB)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StreamThread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_StreamThread.data,
    qt_meta_data_StreamThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StreamThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StreamThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StreamThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StreamThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void StreamThread::sglFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void StreamThread::sglAsyncUpdateUi(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StreamThread::sglAsyncUpdateUi()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void StreamThread::sglVideoInfo(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void StreamThread::sglSyncUpdateYUV(const uchar * _t1, const uchar * _t2, const uchar * _t3, uint _t4, uint _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void StreamThread::sglSyncUpdateRGB(uint8_t * _t1, uint _t2, uint _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
