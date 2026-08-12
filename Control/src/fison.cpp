#include "fison.h"

#include <QDateTime>
#include <QDebug>
#include <qnamespace.h>
#include <QtGlobal>
#include <cstring>
#include <functional>

namespace {

constexpr quint8 kProtocolVersion = 0x0C;
constexpr quint8 kReadRequestType = 0x00;
constexpr int kHeaderSize = 4;
constexpr int kPacketSize = 14;
constexpr qint16 kSteeringMin = -450;
constexpr qint16 kSteeringMax = 450;

constexpr quint8 kByte4A1TakeoverBit = 3;
constexpr quint8 kByte4ReverseBit = 1;
constexpr quint8 kByte4DriveBit = 2;
constexpr quint8 kByte6EmergencyStopBit = 5;
constexpr quint8 kByte7HornBit = 1;
constexpr quint8 kByte7WidthLightBit = 2;
constexpr quint8 kByte7LowBeamBit = 3;
constexpr quint8 kByte7HighBeamBit = 4;
constexpr quint8 kByte7FogLightBit = 5;
constexpr quint8 kByte7LeftTurnBit = 6;
constexpr quint8 kByte7RightTurnBit = 7;
constexpr quint8 kByte8WiperINTBit = 0;
constexpr quint8 kByte8WiperLOBit = 1;
constexpr quint8 kByte8WiperHIBit = 2;

inline quint8 U8(char value)
{
    return static_cast<quint8>(static_cast<unsigned char>(value));
}

inline bool TestBit(quint8 value, quint8 bit)
{
    return ((value >> bit) & 0x01U) != 0;
}

inline quint8 ToLight(bool enabled)
{
    return enabled ? 0x01 : 0x00;
}

inline quint16 ReadLittleEndianU16(const QByteArray &packet, int offset)
{
    return (static_cast<quint16>(U8(packet[offset + 1])) << 8)
         | static_cast<quint16>(U8(packet[offset]));
}

} // namespace

fison::fison(QObject *parent)
    : QObject(parent)
{
    subObj.ConnectTo(ZMQ_ADDR_Gateway);
    subObj.Subscribe(ZMQ_TOPIC_VEHICLE_STATUS,
                     std::bind(&fison::HandleZmqVehicleStatus,
                               this,
                               std::placeholders::_1,
                               std::placeholders::_2,
                               std::placeholders::_3));

    connect(&socket, &QTcpSocket::connected, this, &fison::HandleSocketConnected);
    connect(&socket, &QTcpSocket::disconnected, this, &fison::HandleSocketDisconnected);
    connect(&socket, &QTcpSocket::readyRead, this, &fison::HandleSocketReadyRead);
    connect(&socket,
        QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
        this,
        &fison::HandleSocketError);

    pollTimer.setInterval(pollIntervalMs);
    connect(&pollTimer, &QTimer::timeout, this, &fison::HandlePollTimerSlot);

    reconnectTimer.setInterval(reconnectIntervalMs);
    connect(&reconnectTimer, &QTimer::timeout, this, &fison::HandleReconnectTimerSlot);
}

void fison::StartRun()
{
    reconnectTimer.start();
    ConnectToCabin();
}

void fison::ConnectToCabin()
{
    if (socket.state() == QAbstractSocket::ConnectedState
            || socket.state() == QAbstractSocket::ConnectingState) {
        return;
    }

    recvBuffer.clear();
    socket.abort();
    socket.connectToHost(tcpHost, tcpPort);
    qDebug() << "connecting fison cabin tcp:" << tcpHost << tcpPort;
}

void fison::ResetConnectionState(quint8 status)
{
    recvBuffer.clear();
    hasValidData = false;
    pollCountWithoutData = 0;
    emit EmitStatus(status);
}

void fison::HandleSocketConnected()
{
    ResetConnectionState(DEV_LINKSTATUS_CONNECTED_NO_DATA);
    // 舱端通常需要周期读请求才会回包；不能等收到首包后再启动 poll。
    pollTimer.start();
    SendReadRequest();
    qDebug() << "fison cabin connected, polling every" << pollIntervalMs << "ms";
}

void fison::HandleSocketDisconnected()
{
    pollTimer.stop();
    ResetConnectionState(DEV_LINKSTATUS_DISCONNECTED);
    qWarning() << "fison cabin disconnected";
}

void fison::HandleSocketError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qWarning() << "fison cabin socket error:" << socket.errorString();
}

void fison::HandlePollTimerSlot()
{
    if (socket.state() == QAbstractSocket::ConnectedState) {
        SendReadRequest();
        if (!hasValidData) {
            ++pollCountWithoutData;
            if (pollCountWithoutData % 100 == 0) {
                qWarning() << "fison cabin still no data after" << pollCountWithoutData
                           << "polls, host:" << tcpHost << "port:" << tcpPort
                           << "- check cabin TCP service / IP / port";
            }
        }
    }
}

void fison::HandleReconnectTimerSlot()
{
    if (socket.state() == QAbstractSocket::UnconnectedState) {
        ConnectToCabin();
    }
}

void fison::SendReadRequest()
{
    if (socket.state() != QAbstractSocket::ConnectedState) {
        return;
    }
    QByteArray request(kHeaderSize, 0x00);
    request[0] = static_cast<char>(kProtocolVersion);
    request[1] = static_cast<char>(kReadRequestType);
    request[2] = static_cast<char>(pollMessageId++);
    request[3] = static_cast<char>(kHeaderSize);
    const qint64 written = socket.write(request);
    socket.flush();
    if (written != kHeaderSize) {
        qWarning() << "fison cabin write read request failed, written:" << written;
    }
}

void fison::HandleSocketReadyRead()
{
    const QByteArray chunk = socket.readAll();
    if (chunk.isEmpty()) {
        return;
    }
    qDebug() << "fison cabin recv bytes:" << chunk.size() << "hex:" << chunk.toHex(' ');
    recvBuffer.append(chunk);
    ParsePackets();
}

void fison::ParsePackets()
{
    while (recvBuffer.size() >= kHeaderSize) {
        const int packetLength = U8(recvBuffer[3]);
        if (packetLength < kHeaderSize || packetLength > 64) {
            recvBuffer.remove(0, 1);
            continue;
        }

        if (recvBuffer.size() < packetLength) {
            return;
        }

        const QByteArray packet = recvBuffer.left(packetLength);
        recvBuffer.remove(0, packetLength);
        HandlePacket(packet);
    }
}

bool fison::HandlePacket(const QByteArray &packet)
{
    if (packet.size() < kPacketSize) {
        qWarning() << "fison cabin packet too short:" << packet.toHex(' ');
        return false;
    }

    if (U8(packet[0]) != kProtocolVersion) {
        qWarning() << "fison cabin invalid version:" << packet.toHex(' ');
        return false;
    }

    if (!hasValidData) {
        hasValidData = true;
        emit EmitStatus(DEV_LINKSTATUS_CONNECTED_DATA);
        pollTimer.start();
    }

    PublishControlData(packet);
    return true;
}

void fison::PublishControlRawData(qint16 steering, quint8 throttle, quint8 brake)
{
    MainCtrlMsg rawData;
    std::memset(&rawData, 0x00, sizeof(rawData));
    rawData.clutch = brake;
    rawData.brake = brake;
    rawData.accelerator = throttle;
    rawData.steeringwheel = steering;
    emit EmitControlRawData(QByteArray(reinterpret_cast<const char *>(&rawData), sizeof(rawData)));
}

void fison::PublishControlData(const QByteArray &packet)
{
    const quint8 byte4 = U8(packet[4]);
    const quint8 byte6 = U8(packet[6]);
    const quint8 byte7 = U8(packet[7]);
    const quint8 byte8 = U8(packet[8]);
    const qint16 steering = ReadLittleEndianU16(packet, 9);
    const quint8 throttle = U8(packet[11]);
    const quint8 brake = U8(packet[12]);
    const quint8 fault = U8(packet[13]);

    const bool a1TakeoverPressed = TestBit(byte4, kByte4A1TakeoverBit);
    // Match the old zhongzhi behavior: trigger takeover once when the button is released.
    if (!a1TakeoverPressed && lastA1TakeoverPressed) {
        const qint64 nowMs = QDateTime::currentMSecsSinceEpoch();
        if (nowMs - lastA1TakeoverEmitMs > 300) {
            lastA1TakeoverEmitMs = nowMs;
            emit EmitButton(Qt::Key_PageUp);
            qDebug() << "fison A1 takeover button released, emit PageUp";
        }
    }
    lastA1TakeoverPressed = a1TakeoverPressed;

    ControlData controlData;
    std::memset(&controlData, 0x00, sizeof(controlData));
    controlData.steeringWheelAngle = static_cast<quint16>(
        qBound(0, qRound(((static_cast<double>(steering) - kSteeringMin)
                          / (kSteeringMax - kSteeringMin)) * 10000.0), 10000));
    controlData.throttlePedal = static_cast<quint16>(throttle) * 100;
    controlData.brakePedal = static_cast<quint16>(brake) * 100;
    controlData.hydraulicBrake = controlData.brakePedal;
    controlData.eStop = TestBit(byte6, kByte6EmergencyStopBit) ? 1 : 0;

    if (TestBit(byte4, kByte4DriveBit)) {
        controlData.gearShiftCtrl = GEARSHIFT_CTRL_D;
    } else if (TestBit(byte4, kByte4ReverseBit)) {
        controlData.gearShiftCtrl = GEARSHIFT_CTRL_R;
    } else {
        controlData.gearShiftCtrl = GEARSHIFT_CTRL_N;
    }

    ControlLight lightData;
    std::memset(&lightData, 0x00, sizeof(lightData));
    lightData.speaker = ToLight(TestBit(byte7, kByte7HornBit));
    lightData.side = ToLight(TestBit(byte7, kByte7WidthLightBit));
    lightData.rearPosition = lightData.side;
    lightData.lowBeam = ToLight(TestBit(byte7, kByte7LowBeamBit));
    lightData.heighBeam = ToLight(TestBit(byte7, kByte7HighBeamBit));
    lightData.frontFog = ToLight(TestBit(byte7, kByte7FogLightBit));
    lightData.left = ToLight(TestBit(byte7, kByte7LeftTurnBit));
    lightData.right = ToLight(TestBit(byte7, kByte7RightTurnBit));
    lightData.emergency = ToLight(lightData.left && lightData.right);

    emit EmitControlData(QByteArray(reinterpret_cast<const char *>(&controlData), sizeof(controlData)));
    emit EmitControlLight(QByteArray(reinterpret_cast<const char *>(&lightData), sizeof(lightData)));
    PublishControlRawData(steering, throttle, brake);

    qDebug()
        << "========================================"
        << "\n[斐视驾驶舱 实时数据]"
        << "\n  方向盘角度: " << steering << "°"
        << "\n  油门踏板: " << throttle << "%"
        << "\n  制动踏板: " << brake << "%"
        << "\n  当前档位: " << (TestBit(byte4, kByte4DriveBit) ? "D" :
                           TestBit(byte4, kByte4ReverseBit) ? "R" : "N")
        << "\n  A1接管按键: " << (a1TakeoverPressed ? "按下" : "松开")
        << "\n  急停状态: " << (TestBit(byte6, kByte6EmergencyStopBit) ? "触发" : "正常")
        << "\n  左转向灯: " << (TestBit(byte7, kByte7LeftTurnBit) ? "ON" : "OFF")
        << "\n  右转向灯: " << (TestBit(byte7, kByte7RightTurnBit) ? "ON" : "OFF")
        << "\n  双闪警示: " << ((TestBit(byte7, kByte7LeftTurnBit) && TestBit(byte7, kByte7RightTurnBit)) ? "ON" : "OFF")
        << "\n  雨刮状态: " << [&]() {
        if (TestBit(byte8, kByte8WiperHIBit)) return "高速(HI)";
        if (TestBit(byte8, kByte8WiperLOBit)) return "低速(LO)";
        if (TestBit(byte8, kByte8WiperINTBit)) return "间歇(INT)";
            return "关闭";
            }()
        << "\n  喇叭鸣笛: " << (TestBit(byte7, kByte7HornBit) ? "ON" : "OFF")
        << "\n  近光灯: " << (TestBit(byte7, kByte7LowBeamBit) ? "ON" : "OFF")
        << "\n  远光灯: " << (TestBit(byte7, kByte7HighBeamBit) ? "ON" : "OFF")
        << "\n  示宽灯: " << (TestBit(byte7, kByte7WidthLightBit) ? "ON" : "OFF")
        << "\n  雾灯: " << (TestBit(byte7, kByte7FogLightBit) ? "ON" : "OFF")
        << "\n  按键面板故障: " << (TestBit(fault, 0) ? "正常" : "故障/掉线")
        << "\n  方向盘组件故障: " << (TestBit(fault, 1) ? "正常" : "故障/掉线")
        << "\n  电机故障: " << (TestBit(fault, 2) ? "正常" : "故障/掉线")
        << "\n  设备状态: " << ((fault & 0x07U) == 0x07U ? "全部正常" : "存在故障")
        << "\n========================================\n";
}

void fison::HandleZmqVehicleStatus(std::string &topic, const void *data, int len)
{
    Q_UNUSED(topic);
    if (data == nullptr || len < static_cast<int>(sizeof(VehicleStatus))) {
        return;
    }

    const auto *vehicleStatus = reinterpret_cast<const VehicleStatus *>(data);
    emit EmitVehicleStatus(vehicleStatus->status);
}
