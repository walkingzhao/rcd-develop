/****************************************************************************
** Meta object code from reading C++ file 'devhandle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../GatewayServer/include/devhandle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'devhandle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DevHandle_t {
    QByteArrayData data[50];
    char stringdata0[748];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DevHandle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DevHandle_t qt_meta_stringdata_DevHandle = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DevHandle"
QT_MOC_LITERAL(1, 10, 12), // "Disconnected"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "qintptr"
QT_MOC_LITERAL(4, 32, 10), // "socketDesc"
QT_MOC_LITERAL(5, 43, 10), // "DevReqAuth"
QT_MOC_LITERAL(6, 54, 11), // "std::string"
QT_MOC_LITERAL(7, 66, 4), // "imei"
QT_MOC_LITERAL(8, 71, 4), // "type"
QT_MOC_LITERAL(9, 76, 19), // "ReqControlCmdResult"
QT_MOC_LITERAL(10, 96, 3), // "cmd"
QT_MOC_LITERAL(11, 100, 6), // "result"
QT_MOC_LITERAL(12, 107, 8), // "uint16_t"
QT_MOC_LITERAL(13, 116, 6), // "taskId"
QT_MOC_LITERAL(14, 123, 19), // "VehicleStatusSignal"
QT_MOC_LITERAL(15, 143, 6), // "status"
QT_MOC_LITERAL(16, 150, 20), // "VehicleRawDataSignal"
QT_MOC_LITERAL(17, 171, 7), // "rawData"
QT_MOC_LITERAL(18, 179, 18), // "VehicleDelaySignal"
QT_MOC_LITERAL(19, 198, 8), // "uint32_t"
QT_MOC_LITERAL(20, 207, 7), // "delayUs"
QT_MOC_LITERAL(21, 215, 25), // "VehicleReportHmiMsgSignal"
QT_MOC_LITERAL(22, 241, 3), // "len"
QT_MOC_LITERAL(23, 245, 11), // "QByteArray&"
QT_MOC_LITERAL(24, 257, 4), // "body"
QT_MOC_LITERAL(25, 262, 26), // "VehicleReportGnssMsgSignal"
QT_MOC_LITERAL(26, 289, 29), // "VehicleReportHmiHintMsgSignal"
QT_MOC_LITERAL(27, 319, 18), // "VehicleTaskAuthReq"
QT_MOC_LITERAL(28, 338, 7), // "authkey"
QT_MOC_LITERAL(29, 346, 31), // "VehicleReportTrackLineMsgSignal"
QT_MOC_LITERAL(30, 378, 31), // "VehicleReportRoadTaskInfoSignal"
QT_MOC_LITERAL(31, 410, 31), // "VehicleSendSafeDecelerateSignal"
QT_MOC_LITERAL(32, 442, 7), // "uint8_t"
QT_MOC_LITERAL(33, 450, 6), // "cation"
QT_MOC_LITERAL(34, 457, 34), // "VehicleReportSpeedWarningMsgS..."
QT_MOC_LITERAL(35, 492, 15), // "ReadDataFromDev"
QT_MOC_LITERAL(36, 508, 15), // "DevDisConnected"
QT_MOC_LITERAL(37, 524, 17), // "HeartTimeOutSlots"
QT_MOC_LITERAL(38, 542, 22), // "ControlCmdTimeOutSlots"
QT_MOC_LITERAL(39, 565, 20), // "DelayCmdTimeOutSlots"
QT_MOC_LITERAL(40, 586, 23), // "HandleReqControlCmdSlot"
QT_MOC_LITERAL(41, 610, 3), // "opt"
QT_MOC_LITERAL(42, 614, 26), // "HandleReqSendHmiMsgCmdSlot"
QT_MOC_LITERAL(43, 641, 25), // "HandleReqTrackLineMsgSlot"
QT_MOC_LITERAL(44, 667, 17), // "HandleControlData"
QT_MOC_LITERAL(45, 685, 4), // "data"
QT_MOC_LITERAL(46, 690, 18), // "HandleTaskAuthResp"
QT_MOC_LITERAL(47, 709, 14), // "HandleTaskStop"
QT_MOC_LITERAL(48, 724, 17), // "HandleRemoteEstop"
QT_MOC_LITERAL(49, 742, 5) // "estop"

    },
    "DevHandle\0Disconnected\0\0qintptr\0"
    "socketDesc\0DevReqAuth\0std::string\0"
    "imei\0type\0ReqControlCmdResult\0cmd\0"
    "result\0uint16_t\0taskId\0VehicleStatusSignal\0"
    "status\0VehicleRawDataSignal\0rawData\0"
    "VehicleDelaySignal\0uint32_t\0delayUs\0"
    "VehicleReportHmiMsgSignal\0len\0QByteArray&\0"
    "body\0VehicleReportGnssMsgSignal\0"
    "VehicleReportHmiHintMsgSignal\0"
    "VehicleTaskAuthReq\0authkey\0"
    "VehicleReportTrackLineMsgSignal\0"
    "VehicleReportRoadTaskInfoSignal\0"
    "VehicleSendSafeDecelerateSignal\0uint8_t\0"
    "cation\0VehicleReportSpeedWarningMsgSignal\0"
    "ReadDataFromDev\0DevDisConnected\0"
    "HeartTimeOutSlots\0ControlCmdTimeOutSlots\0"
    "DelayCmdTimeOutSlots\0HandleReqControlCmdSlot\0"
    "opt\0HandleReqSendHmiMsgCmdSlot\0"
    "HandleReqTrackLineMsgSlot\0HandleControlData\0"
    "data\0HandleTaskAuthResp\0HandleTaskStop\0"
    "HandleRemoteEstop\0estop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DevHandle[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  144,    2, 0x06 /* Public */,
       5,    3,  147,    2, 0x06 /* Public */,
       9,    4,  154,    2, 0x06 /* Public */,
      14,    3,  163,    2, 0x06 /* Public */,
      16,    1,  170,    2, 0x06 /* Public */,
      18,    2,  173,    2, 0x06 /* Public */,
      21,    3,  178,    2, 0x06 /* Public */,
      25,    3,  185,    2, 0x06 /* Public */,
      26,    3,  192,    2, 0x06 /* Public */,
      27,    3,  199,    2, 0x06 /* Public */,
      29,    3,  206,    2, 0x06 /* Public */,
      30,    3,  213,    2, 0x06 /* Public */,
      31,    1,  220,    2, 0x06 /* Public */,
      34,    3,  223,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      35,    0,  230,    2, 0x0a /* Public */,
      36,    0,  231,    2, 0x0a /* Public */,
      37,    0,  232,    2, 0x0a /* Public */,
      38,    0,  233,    2, 0x0a /* Public */,
      39,    0,  234,    2, 0x0a /* Public */,
      40,    2,  235,    2, 0x0a /* Public */,
      42,    2,  240,    2, 0x0a /* Public */,
      43,    2,  245,    2, 0x0a /* Public */,
      44,    1,  250,    2, 0x0a /* Public */,
      46,    1,  253,    2, 0x0a /* Public */,
      47,    1,  256,    2, 0x0a /* Public */,
      48,    1,  259,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 6, QMetaType::Int,    4,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int, 0x80000000 | 12,    7,   10,   11,   13,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int,    7,    8,   15,
    QMetaType::Void, QMetaType::QByteArray,   17,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 19,    7,   20,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 23,    7,   22,   24,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 23,    7,   22,   24,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 23,    7,   22,   24,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 6, 0x80000000 | 6,   13,    7,   28,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 23,    7,   22,   24,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 23,    7,   22,   24,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 23,    7,   22,   24,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 32,    7,   41,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QByteArray,    7,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QByteArray,    7,    2,
    QMetaType::Void, QMetaType::QByteArray,   45,
    QMetaType::Void, 0x80000000 | 32,   11,
    QMetaType::Void, QMetaType::UShort,   13,
    QMetaType::Void, 0x80000000 | 32,   49,

       0        // eod
};

void DevHandle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DevHandle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Disconnected((*reinterpret_cast< qintptr(*)>(_a[1]))); break;
        case 1: _t->DevReqAuth((*reinterpret_cast< qintptr(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->ReqControlCmdResult((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< uint16_t(*)>(_a[4]))); break;
        case 3: _t->VehicleStatusSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->VehicleRawDataSignal((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 5: _t->VehicleDelaySignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2]))); break;
        case 6: _t->VehicleReportHmiMsgSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 7: _t->VehicleReportGnssMsgSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 8: _t->VehicleReportHmiHintMsgSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 9: _t->VehicleTaskAuthReq((*reinterpret_cast< const uint16_t(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 10: _t->VehicleReportTrackLineMsgSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 11: _t->VehicleReportRoadTaskInfoSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 12: _t->VehicleSendSafeDecelerateSignal((*reinterpret_cast< const uint8_t(*)>(_a[1]))); break;
        case 13: _t->VehicleReportSpeedWarningMsgSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 14: _t->ReadDataFromDev(); break;
        case 15: _t->DevDisConnected(); break;
        case 16: _t->HeartTimeOutSlots(); break;
        case 17: _t->ControlCmdTimeOutSlots(); break;
        case 18: _t->DelayCmdTimeOutSlots(); break;
        case 19: _t->HandleReqControlCmdSlot((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 20: _t->HandleReqSendHmiMsgCmdSlot((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 21: _t->HandleReqTrackLineMsgSlot((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 22: _t->HandleControlData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 23: _t->HandleTaskAuthResp((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 24: _t->HandleTaskStop((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 25: _t->HandleRemoteEstop((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DevHandle::*)(qintptr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::Disconnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(qintptr , const std::string & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::DevReqAuth)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , int , uint16_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::ReqControlCmdResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleStatusSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleRawDataSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleDelaySignal)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleReportHmiMsgSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleReportGnssMsgSignal)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleReportHmiHintMsgSignal)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const uint16_t , std::string , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleTaskAuthReq)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleReportTrackLineMsgSignal)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleReportRoadTaskInfoSignal)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleSendSafeDecelerateSignal)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (DevHandle::*)(const std::string & , int , QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DevHandle::VehicleReportSpeedWarningMsgSignal)) {
                *result = 13;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DevHandle::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DevHandle.data,
    qt_meta_data_DevHandle,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DevHandle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DevHandle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DevHandle.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DevHandle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void DevHandle::Disconnected(qintptr _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DevHandle::DevReqAuth(qintptr _t1, const std::string & _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DevHandle::ReqControlCmdResult(const std::string & _t1, int _t2, int _t3, uint16_t _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DevHandle::VehicleStatusSignal(const std::string & _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DevHandle::VehicleRawDataSignal(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DevHandle::VehicleDelaySignal(const std::string & _t1, uint32_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DevHandle::VehicleReportHmiMsgSignal(const std::string & _t1, int _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DevHandle::VehicleReportGnssMsgSignal(const std::string & _t1, int _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DevHandle::VehicleReportHmiHintMsgSignal(const std::string & _t1, int _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DevHandle::VehicleTaskAuthReq(const uint16_t _t1, std::string _t2, std::string _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void DevHandle::VehicleReportTrackLineMsgSignal(const std::string & _t1, int _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void DevHandle::VehicleReportRoadTaskInfoSignal(const std::string & _t1, int _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void DevHandle::VehicleSendSafeDecelerateSignal(const uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void DevHandle::VehicleReportSpeedWarningMsgSignal(const std::string & _t1, int _t2, QByteArray & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
