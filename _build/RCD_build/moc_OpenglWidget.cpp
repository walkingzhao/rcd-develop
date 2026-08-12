/****************************************************************************
** Meta object code from reading C++ file 'OpenglWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RcdUi/src/Component/OpenglWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OpenglWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_OpenGLWidget_t {
    QByteArrayData data[20];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OpenGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OpenGLWidget_t qt_meta_stringdata_OpenGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "OpenGLWidget"
QT_MOC_LITERAL(1, 13, 9), // "sglResize"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 1), // "w"
QT_MOC_LITERAL(4, 26, 1), // "h"
QT_MOC_LITERAL(5, 28, 12), // "signalPixmap"
QT_MOC_LITERAL(6, 41, 3), // "img"
QT_MOC_LITERAL(7, 45, 13), // "syncUpdateYUV"
QT_MOC_LITERAL(8, 59, 12), // "const uchar*"
QT_MOC_LITERAL(9, 72, 6), // "Yplane"
QT_MOC_LITERAL(10, 79, 6), // "Uplane"
QT_MOC_LITERAL(11, 86, 6), // "Vplane"
QT_MOC_LITERAL(12, 93, 5), // "width"
QT_MOC_LITERAL(13, 99, 6), // "height"
QT_MOC_LITERAL(14, 106, 13), // "asyncUpdateUi"
QT_MOC_LITERAL(15, 120, 13), // "syncUpdateRGB"
QT_MOC_LITERAL(16, 134, 8), // "uint8_t*"
QT_MOC_LITERAL(17, 143, 3), // "rgb"
QT_MOC_LITERAL(18, 147, 9), // "reconnect"
QT_MOC_LITERAL(19, 157, 21) // "slot_timer_checkVideo"

    },
    "OpenGLWidget\0sglResize\0\0w\0h\0signalPixmap\0"
    "img\0syncUpdateYUV\0const uchar*\0Yplane\0"
    "Uplane\0Vplane\0width\0height\0asyncUpdateUi\0"
    "syncUpdateRGB\0uint8_t*\0rgb\0reconnect\0"
    "slot_timer_checkVideo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OpenGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    5,   57,    2, 0x0a /* Public */,
      14,    0,   68,    2, 0x0a /* Public */,
      15,    3,   69,    2, 0x0a /* Public */,
      18,    0,   76,    2, 0x0a /* Public */,
      19,    0,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QPixmap,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8, 0x80000000 | 8, QMetaType::UInt, QMetaType::UInt,    9,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::UInt, QMetaType::UInt,   17,   12,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void OpenGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OpenGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglResize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalPixmap((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 2: _t->syncUpdateYUV((*reinterpret_cast< const uchar*(*)>(_a[1])),(*reinterpret_cast< const uchar*(*)>(_a[2])),(*reinterpret_cast< const uchar*(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4])),(*reinterpret_cast< uint(*)>(_a[5]))); break;
        case 3: _t->asyncUpdateUi(); break;
        case 4: _t->syncUpdateRGB((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 5: _t->reconnect(); break;
        case 6: _t->slot_timer_checkVideo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OpenGLWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::sglResize)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OpenGLWidget::*)(QPixmap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&OpenGLWidget::signalPixmap)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject OpenGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_OpenGLWidget.data,
    qt_meta_data_OpenGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *OpenGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OpenGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_OpenGLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int OpenGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void OpenGLWidget::sglResize(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OpenGLWidget::signalPixmap(QPixmap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
