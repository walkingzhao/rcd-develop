/****************************************************************************
** Meta object code from reading C++ file 'gatewayserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../GatewayServer/include/gatewayserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gatewayserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GateWayServer_t {
    QByteArrayData data[48];
    char stringdata0[735];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GateWayServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GateWayServer_t qt_meta_stringdata_GateWayServer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GateWayServer"
QT_MOC_LITERAL(1, 14, 23), // "EmitReqControlCmdSignal"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 11), // "std::string"
QT_MOC_LITERAL(4, 51, 4), // "imei"
QT_MOC_LITERAL(5, 56, 7), // "uint8_t"
QT_MOC_LITERAL(6, 64, 3), // "opt"
QT_MOC_LITERAL(7, 68, 26), // "EmitReqSendHmiMsgCmdSignal"
QT_MOC_LITERAL(8, 95, 4), // "data"
QT_MOC_LITERAL(9, 100, 15), // "EmitControlData"
QT_MOC_LITERAL(10, 116, 14), // "EmitTaskCancel"
QT_MOC_LITERAL(11, 131, 12), // "EmitTaskStop"
QT_MOC_LITERAL(12, 144, 6), // "taskId"
QT_MOC_LITERAL(13, 151, 16), // "EmitTaskAuthResp"
QT_MOC_LITERAL(14, 168, 6), // "result"
QT_MOC_LITERAL(15, 175, 25), // "EmitReqTrackLineMsgSignal"
QT_MOC_LITERAL(16, 201, 15), // "EmitRemoteEstop"
QT_MOC_LITERAL(17, 217, 5), // "estop"
QT_MOC_LITERAL(18, 223, 16), // "HandleNewConnect"
QT_MOC_LITERAL(19, 240, 21), // "HandleDevDisConnected"
QT_MOC_LITERAL(20, 262, 7), // "qintptr"
QT_MOC_LITERAL(21, 270, 10), // "socketDesc"
QT_MOC_LITERAL(22, 281, 16), // "HandleDevReqAuth"
QT_MOC_LITERAL(23, 298, 4), // "type"
QT_MOC_LITERAL(24, 303, 25), // "HandleReqControlCmdResult"
QT_MOC_LITERAL(25, 329, 3), // "cmd"
QT_MOC_LITERAL(26, 333, 8), // "uint16_t"
QT_MOC_LITERAL(27, 342, 19), // "HandleVehicleStatus"
QT_MOC_LITERAL(28, 362, 6), // "status"
QT_MOC_LITERAL(29, 369, 20), // "HandleVehicleRawData"
QT_MOC_LITERAL(30, 390, 7), // "rawData"
QT_MOC_LITERAL(31, 398, 18), // "HandleVehicleDelay"
QT_MOC_LITERAL(32, 417, 8), // "uint32_t"
QT_MOC_LITERAL(33, 426, 7), // "delayUs"
QT_MOC_LITERAL(34, 434, 25), // "HandleVehicleReportHmiMsg"
QT_MOC_LITERAL(35, 460, 3), // "len"
QT_MOC_LITERAL(36, 464, 11), // "QByteArray&"
QT_MOC_LITERAL(37, 476, 4), // "body"
QT_MOC_LITERAL(38, 481, 26), // "HandleVehicleReportGnssMsg"
QT_MOC_LITERAL(39, 508, 29), // "HandleVehicleReportHmiHintMsg"
QT_MOC_LITERAL(40, 538, 24), // "HandleVehicleTaskAuthReq"
QT_MOC_LITERAL(41, 563, 7), // "authkey"
QT_MOC_LITERAL(42, 571, 31), // "HandleVehicleReportTrackLineMsg"
QT_MOC_LITERAL(43, 603, 31), // "HandleVehicleReportRoadTaskInfo"
QT_MOC_LITERAL(44, 635, 31), // "HandleVehicleSendSafeDecelerate"
QT_MOC_LITERAL(45, 667, 6), // "action"
QT_MOC_LITERAL(46, 674, 34), // "HandleVehicleReportSpeedWarni..."
QT_MOC_LITERAL(47, 709, 25) // "handleCheckConnectTimeOut"

    },
    "GateWayServer\0EmitReqControlCmdSignal\0"
    "\0std::string\0imei\0uint8_t\0opt\0"
    "EmitReqSendHmiMsgCmdSignal\0data\0"
    "EmitControlData\0EmitTaskCancel\0"
    "EmitTaskStop\0taskId\0EmitTaskAuthResp\0"
    "result\0EmitReqTrackLineMsgSignal\0"
    "EmitRemoteEstop\0estop\0HandleNewConnect\0"
    "HandleDevDisConnected\0qintptr\0socketDesc\0"
    "HandleDevReqAuth\0type\0HandleReqControlCmdResult\0"
    "cmd\0uint16_t\0HandleVehicleStatus\0"
    "status\0HandleVehicleRawData\0rawData\0"
    "HandleVehicleDelay\0uint32_t\0delayUs\0"
    "HandleVehicleReportHmiMsg\0len\0QByteArray&\0"
    "body\0HandleVehicleReportGnssMsg\0"
    "HandleVehicleReportHmiHintMsg\0"
    "HandleVehicleTaskAuthReq\0authkey\0"
    "HandleVehicleReportTrackLineMsg\0"
    "HandleVehicleReportRoadTaskInfo\0"
    "HandleVehicleSendSafeDecelerate\0action\0"
    "HandleVehicleReportSpeedWarningMsg\0"
    "handleCheckConnectTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GateWayServer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  134,    2, 0x06 /* Public */,
       7,    2,  139,    2, 0x06 /* Public */,
       9,    1,  144,    2, 0x06 /* Public */,
      10,    1,  147,    2, 0x06 /* Public */,
      11,    1,  150,    2, 0x06 /* Public */,
      13,    1,  153,    2, 0x06 /* Public */,
      15,    2,  156,    2, 0x06 /* Public */,
      16,    1,  161,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  164,    2, 0x0a /* Public */,
      19,    1,  165,    2, 0x0a /* Public */,
      22,    3,  168,    2, 0x0a /* Public */,
      24,    4,  175,    2, 0x0a /* Public */,
      27,    3,  184,    2, 0x0a /* Public */,
      29,    1,  191,    2, 0x0a /* Public */,
      31,    2,  194,    2, 0x0a /* Public */,
      34,    3,  199,    2, 0x0a /* Public */,
      38,    3,  206,    2, 0x0a /* Public */,
      39,    3,  213,    2, 0x0a /* Public */,
      40,    3,  220,    2, 0x0a /* Public */,
      42,    3,  227,    2, 0x0a /* Public */,
      43,    3,  234,    2, 0x0a /* Public */,
      44,    1,  241,    2, 0x0a /* Public */,
      46,    3,  244,    2, 0x0a /* Public */,
      47,    0,  251,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QByteArray,    4,    8,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, QMetaType::UShort,   12,
    QMetaType::Void, 0x80000000 | 5,   14,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QByteArray,    4,    8,
    QMetaType::Void, 0x80000000 | 5,   17,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 3, QMetaType::Int,   21,    4,   23,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int, 0x80000000 | 26,    4,   25,   14,   12,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    4,   23,   28,
    QMetaType::Void, QMetaType::QByteArray,   30,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 32,    4,   33,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 36,    4,   35,   37,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 36,    4,   35,   37,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 36,    4,   35,   37,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 3, 0x80000000 | 3,   12,    4,   41,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 36,    4,   35,   37,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 36,    4,   35,   37,
    QMetaType::Void, 0x80000000 | 5,   45,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 36,    4,   35,   37,
    QMetaType::Void,

       0        // eod
};

void GateWayServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GateWayServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->EmitReqControlCmdSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 1: _t->EmitReqSendHmiMsgCmdSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 2: _t->EmitControlData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->EmitTaskCancel((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->EmitTaskStop((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 5: _t->EmitTaskAuthResp((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 6: _t->EmitReqTrackLineMsgSignal((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 7: _t->EmitRemoteEstop((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 8: _t->HandleNewConnect(); break;
        case 9: _t->HandleDevDisConnected((*reinterpret_cast< qintptr(*)>(_a[1]))); break;
        case 10: _t->HandleDevReqAuth((*reinterpret_cast< qintptr(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->HandleReqControlCmdResult((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< uint16_t(*)>(_a[4]))); break;
        case 12: _t->HandleVehicleStatus((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->HandleVehicleRawData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 14: _t->HandleVehicleDelay((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< uint32_t(*)>(_a[2]))); break;
        case 15: _t->HandleVehicleReportHmiMsg((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 16: _t->HandleVehicleReportGnssMsg((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 17: _t->HandleVehicleReportHmiHintMsg((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 18: _t->HandleVehicleTaskAuthReq((*reinterpret_cast< const uint16_t(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 19: _t->HandleVehicleReportTrackLineMsg((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 20: _t->HandleVehicleReportRoadTaskInfo((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 21: _t->HandleVehicleSendSafeDecelerate((*reinterpret_cast< const uint8_t(*)>(_a[1]))); break;
        case 22: _t->HandleVehicleReportSpeedWarningMsg((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 23: _t->handleCheckConnectTimeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GateWayServer::*)(const std::string & , uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitReqControlCmdSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(const std::string & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitReqSendHmiMsgCmdSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitControlData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitTaskCancel)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitTaskStop)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitTaskAuthResp)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(const std::string & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitReqTrackLineMsgSignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GateWayServer::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GateWayServer::EmitRemoteEstop)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GateWayServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GateWayServer.data,
    qt_meta_data_GateWayServer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GateWayServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GateWayServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GateWayServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GateWayServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void GateWayServer::EmitReqControlCmdSignal(const std::string & _t1, uint8_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GateWayServer::EmitReqSendHmiMsgCmdSignal(const std::string & _t1, const QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GateWayServer::EmitControlData(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GateWayServer::EmitTaskCancel(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GateWayServer::EmitTaskStop(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GateWayServer::EmitTaskAuthResp(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GateWayServer::EmitReqTrackLineMsgSignal(const std::string & _t1, const QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void GateWayServer::EmitRemoteEstop(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
