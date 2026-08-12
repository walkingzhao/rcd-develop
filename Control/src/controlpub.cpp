#include "../include/controlpub.h"
#include <qnamespace.h>
#include <QDebug>

#include "fbs/tgmsg_generated.h"
#include "fbs/rcd_generated.h"

ControlPub::ControlPub(QObject *parent) : QObject(parent), pubObj(ZMQ_ADDR_CONTROL)
{
    std::memset(&cacheControlData, 0x00, sizeof(cacheControlData));
    std::memset(&status, 0x00, sizeof(status));
    std::memset(&lightData, 0x00, sizeof(lightData));

    //ControlData发送定时器
    pubDataTimer.setInterval(CONTROLDATA_PUB_TIME_MS);
    connect(&pubDataTimer, SIGNAL(timeout()), this, SLOT(HandlePubDataTimerOut()));
    pubDataTimer.start();

    //ControlLinkStatus发送定时器
    pubStatusTimer.setInterval(LINKSTATUS_PUB_TIME_MS);
    connect(&pubStatusTimer, SIGNAL(timeout()), SLOT(HandlePubStatusTimerOut()));
    pubStatusTimer.start();

    //add self-check timer
    //自检状态发送定时器
    pubSelfCheckTimer.setInterval(1000);
    connect(&pubSelfCheckTimer, SIGNAL(timeout()), SLOT(HandlePubSelfCheckTimerOut()));
    pubSelfCheckTimer.start();
}

void ControlPub::HandleFisonControlRawDataSlot(const QByteArray &data)
{
    MainCtrlMsg ctlData;
    std::memset(&ctlData, 0x00, sizeof(MainCtrlMsg));
    std::memmove(&ctlData, data.data(), data.size());

    Rcd::CtrlRawDataT rawData;
    rawData.clutch = ctlData.clutch;               //离合
    rawData.brake = ctlData.brake;                 //刹车
    rawData.accelerator = ctlData.accelerator;     //油门
    rawData.handbrake = ctlData.handbrake;         //手刹
    rawData.steeringwheel = ctlData.steeringwheel; //方向盘

    flatbuffers::FlatBufferBuilder fbb;
    fbb.Finish(Rcd::CtrlRawData::Pack(fbb, &rawData));

    pubObj.Publish(ZMQ_TOPIC_CONTROL_RAW_DATA, fbb.GetBufferPointer(), fbb.GetSize());
}

void ControlPub::HandleFisonControlDataSlot(const QByteArray &data)
{
    while (controlDataFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;

    std::memmove(&cacheControlData, data.data(), data.size());
    controlDataFlag.clear(std::memory_order::memory_order_release);
}

void ControlPub::HandleFisonControlLightSlot(const QByteArray &data)
{
    while (controlLightFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    std::memmove(&lightData, data.data(), data.size());
    controlLightFlag.clear(std::memory_order::memory_order_release);
}

void ControlPub::HandleFisonStatusSlot(quint8 _status)
{
    while (linkStatusFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    status.wheel = _status;
    linkStatusFlag.clear(std::memory_order::memory_order_release);
}

void ControlPub::HandleFisonButtonSlot(quint32 key)
{
    KeyButton button;
    std::memset(&button, 0x00, sizeof(button));
    button.key = key;
    pubObj.Publish(ZMQ_TOPIC_BUTTON, &button, sizeof(button));
    qDebug() << ZMQ_ADDR_CONTROL << "[send]ControlPub topic:" << ZMQ_TOPIC_BUTTON
             << "softKey:" << static_cast<Qt::Key>(button.key);
}

void ControlPub::HandlePubDataTimerOut()
{
    ControlData tmpControlData;
    std::memset(&tmpControlData, 0x00, sizeof(ControlData));

    while (controlDataFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
//    qDebug() << "get estop " << cacheControlData.eStop;

    std::memmove(&tmpControlData, &cacheControlData, sizeof(cacheControlData));
    controlDataFlag.clear(std::memory_order::memory_order_release);
//    qDebug() << "cp estop " << tmpControlData.eStop;

    ControlLight tmpControlLight;
    std::memset(&tmpControlLight, 0x00, sizeof(ControlLight));
    while (controlLightFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    std::memmove(&tmpControlLight, &lightData, sizeof(tmpControlLight));
    controlLightFlag.clear(std::memory_order::memory_order_release);

    flatbuffers::FlatBufferBuilder fbb;
    TGMsg::MsgFrameT tmpMsgFrame;

    auto now = std::chrono::system_clock::now();
    tmpMsgFrame.timestamps = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    Rcd::VehicleCtrlCmd vehicleCtrl;
    vehicleCtrl.mutate_steeringWheelAngle(tmpControlData.steeringWheelAngle);
    vehicleCtrl.mutate_throttlePedal(tmpControlData.throttlePedal);
    vehicleCtrl.mutate_brakePedal(tmpControlData.brakePedal);
    vehicleCtrl.mutate_hydraulicBrake(tmpControlData.hydraulicBrake);
    vehicleCtrl.mutate_retarderCtrl(tmpControlData.retarderCtrl);
    vehicleCtrl.mutate_exhuastBrake(tmpControlData.exhuastBrake);
    vehicleCtrl.mutate_parkCtrl(tmpControlData.parkCtrl);
    vehicleCtrl.mutate_bucketCtrl(tmpControlData.bucketCtrl);
    vehicleCtrl.mutate_shiftCtrl(tmpControlData.gearShiftCtrl);
    vehicleCtrl.mutate_eStop(!!tmpControlData.eStop);
    vehicleCtrl.mutate_loadingCtrl(!!tmpControlData.loadingCtrl);

    Rcd::LightCtrlCmd lightCtrl;
    lightCtrl.mutate_left(static_cast<LightAction>(tmpControlLight.left));
    lightCtrl.mutate_right(static_cast<LightAction>(tmpControlLight.right));
    lightCtrl.mutate_lowBeam(static_cast<LightAction>(tmpControlLight.lowBeam));
    lightCtrl.mutate_heighBeam(static_cast<LightAction>(tmpControlLight.heighBeam));

    lightCtrl.mutate_rotatingWarningLight(static_cast<LightAction>(tmpControlLight.rotatingWarningLight));
    lightCtrl.mutate_speaker(static_cast<LightAction>(tmpControlLight.speaker));
    lightCtrl.mutate_frontFog(static_cast<LightAction>(tmpControlLight.frontFog));
    lightCtrl.mutate_frontStatus(static_cast<LightAction>(tmpControlLight.frontStatus));

    lightCtrl.mutate_side(static_cast<LightAction>(tmpControlLight.side));
    lightCtrl.mutate_rearPosition(static_cast<LightAction>(tmpControlLight.rearPosition));
    lightCtrl.mutate_emergency(static_cast<LightAction>(tmpControlLight.emergency));
    lightCtrl.mutate_brake(static_cast<LightAction>(tmpControlLight.brake));

    lightCtrl.mutate_back(static_cast<LightAction>(tmpControlLight.back));
    lightCtrl.mutate_rearStatus(static_cast<LightAction>(tmpControlLight.rearStatus));

    Rcd::ControlDataT controlData;
    controlData.vehicleCmd = std::make_unique<Rcd::VehicleCtrlCmd>(vehicleCtrl);
    controlData.lightCmd = std::make_unique<Rcd::LightCtrlCmd>(lightCtrl);

    tmpMsgFrame.msg.Set(std::move(controlData));

    fbb.Clear();
    fbb.FinishSizePrefixed(TGMsg::MsgFrame::Pack(fbb, &tmpMsgFrame));

    pubObj.Publish(ZMQ_TOPIC_CONTROL_DATA, fbb.GetBufferPointer(), fbb.GetSize());
}

void ControlPub::HandlePubStatusTimerOut()
{
    ControlDevLinkStatus tmp;
    std::memset(&tmp, 0x00, sizeof(ControlDevLinkStatus));

    while (linkStatusFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    std::memmove(&tmp, &status, sizeof(ControlDevLinkStatus));
    linkStatusFlag.clear(std::memory_order::memory_order_release);

    qDebug() << "pubilsh status-------------------";
    qDebug() << "status: " << tmp.io << ", " << tmp.wheel << ", " << tmp.vehicle;
    pubObj.Publish(ZMQ_TOPIC_CONTROL_DEVLINKSTATUS, &tmp, sizeof(tmp));
}

void ControlPub::HandlePubSelfCheckTimerOut()
{
    SelfCheckStatus selfCheck;

    ControlData tmpControlData;
    std::memset(&tmpControlData, 0x00, sizeof(ControlData));
    while (controlDataFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    std::memmove(&tmpControlData, &cacheControlData, sizeof(cacheControlData));
    controlDataFlag.clear(std::memory_order::memory_order_release);

    ControlLight tmpControlLight;
    std::memset(&tmpControlLight, 0x00, sizeof(ControlLight));
    while (controlLightFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    std::memmove(&tmpControlLight, &lightData, sizeof(tmpControlLight));
    controlLightFlag.clear(std::memory_order::memory_order_release);

    if (!tmpControlData.exhuastBrake && !tmpControlLight.side && !tmpControlLight.emergency && !tmpControlData.eStop
            && !tmpControlData.bucketCtrl)
    {
        selfCheck.isButtonReset = true;
    }
    else
    {
        selfCheck.isButtonReset = false;
        qDebug() << "self check" << tmpControlData.exhuastBrake << ", " << tmpControlLight.side << ", " << tmpControlLight.emergency
                                << " , " << tmpControlData.eStop << " , " << tmpControlData.bucketCtrl;
    }

    if (tmpControlData.steeringWheelAngle >= 4800 && tmpControlData.steeringWheelAngle <= 5200)
    {
        selfCheck.isCenterSteeringWheel = true;
    }
    else
    {
        selfCheck.isCenterSteeringWheel = false;
        qDebug() << "self check whell:" << tmpControlData.steeringWheelAngle << ", " << static_cast<int>(tmpControlData.steeringWheelAngle);
    }

    if (tmpControlData.throttlePedal == 0)
    {
        selfCheck.isNoPedal = true;
    }
    else
    {
        selfCheck.isNoPedal = false;
    }

    if (tmpControlData.parkCtrl && tmpControlData.loadingCtrl)
    {
        selfCheck.isParking = true;
    }
    else
    {
        selfCheck.isParking = false;
    }

    pubObj.Publish(ZMQ_TOPIC_SELF_CHECK_STATUS, &selfCheck, sizeof(selfCheck));
    qDebug() << "self check-------------";
}

void ControlPub::HandleVehicleStatus(quint8 _status)
{
    qDebug() << "handle get status:" << _status;

    while (linkStatusFlag.test_and_set(std::memory_order::memory_order_acquire))
        ;
    status.vehicle = _status;
    linkStatusFlag.clear(std::memory_order::memory_order_release);
}