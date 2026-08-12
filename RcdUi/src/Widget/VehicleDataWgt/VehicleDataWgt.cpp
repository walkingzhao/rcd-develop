#include "VehicleDataWgt.h"
#include "ui_VehicleDataWgt.h"
#include "public/jsonMethord.h"

VehicleDataWgt  *VehicleDataWgt::s_pInstance=nullptr;
VehicleDataWgt::VehicleDataWgt(QWidget *parent) :
    IFunWidget(parent),
    m_vehicle_type(VehicleType_Unknown),
    ui(new Ui::VehicleDataWgt)
{
    ui->setupUi(this);
    m_pCL = new VehicleDataCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new VehicleDataModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

    m_updateTimer = new QTimer;
    m_updateTimer->setInterval(500);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateUI()));
    m_updateTimer->start();

    // layout //////////////////////////

    ui->Title->setFrameType(TGFrame::InfoFrameRightPage2No10);
    ui->Title->setTitleString(QString::fromUtf8("车辆数据"));

    QHBoxLayout *pHLayout = new QHBoxLayout();
    pHLayout->addStretch(1);
    pHLayout->addWidget(ui->frame_info,9);
    pHLayout->addStretch(1);
    pHLayout->addWidget(ui->frame_dash_board,6);
    pHLayout->addStretch(1);

    QVBoxLayout* pVLayout = new QVBoxLayout(ui->Title);
    pVLayout->addStretch(2);
    pVLayout->addLayout(pHLayout,10);
    pVLayout->addStretch(1);

    pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(ui->Title);
    setLayout(pVLayout);

    ////////////////////////////
    // 发动机油压
    float tmp_start,tmp_end,tmp_min,tmp_max;
    QVariant data_engineOilPressure = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                        "/rcdconfig.json","EngineOilPressure");
    if(data_engineOilPressure.toList().isEmpty()) return;
    tmp_start = data_engineOilPressure.toList()[0].toMap().value("Start").toFloat();
    tmp_min = data_engineOilPressure.toList()[0].toMap().value("Min").toFloat();
    tmp_max = data_engineOilPressure.toList()[0].toMap().value("Max").toFloat();
    tmp_end = data_engineOilPressure.toList()[0].toMap().value("End").toFloat();
    ui->widget_oil_pressure->setParameter(RingDialPro::EngineOilPressure_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
    ui->widget_oil_pressure->setValue(tmp_start);

    // 发动机油量
    QVariant data_fuelLevel= jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                           "/rcdconfig.json","FuelLevel");
    if(data_fuelLevel.toList().isEmpty()) return;
    tmp_start = data_fuelLevel.toList()[0].toMap().value("Start").toFloat();
    tmp_min = data_fuelLevel.toList()[0].toMap().value("Min").toFloat();
    tmp_max = data_fuelLevel.toList()[0].toMap().value("Max").toFloat();
    tmp_end = data_fuelLevel.toList()[0].toMap().value("End").toFloat();
    ui->widget_oil_volume->setParameter(RingDialPro::FuelLevel_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
    ui->widget_oil_volume->setValue(tmp_start);

    // 冷却液温度
    QVariant data_engineCoolantTemperature = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                   "/rcdconfig.json","EngineCoolantTemperature");
    if(data_engineCoolantTemperature.toList().isEmpty()) return;
    tmp_start = data_engineCoolantTemperature.toList()[0].toMap().value("Start").toFloat();
    tmp_min = data_engineCoolantTemperature.toList()[0].toMap().value("Min").toFloat();
    tmp_max = data_engineCoolantTemperature.toList()[0].toMap().value("Max").toFloat();
    tmp_end = data_engineCoolantTemperature.toList()[0].toMap().value("End").toFloat();
    ui->widget_Coolant_temperature->setParameter(RingDialPro::EngineCoolantTemperature_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
    ui->widget_Coolant_temperature->setValue(tmp_start);

    // 冷却液液位
    QVariant data_coolantLevel = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                   "/rcdconfig.json","CoolantLevel");
    if(data_coolantLevel.toList().isEmpty()) return;
    tmp_start = data_coolantLevel.toList()[0].toMap().value("Start").toFloat();
    tmp_min = data_coolantLevel.toList()[0].toMap().value("Min").toFloat();
    tmp_max = data_coolantLevel.toList()[0].toMap().value("Max").toFloat();
    tmp_end = data_coolantLevel.toList()[0].toMap().value("End").toFloat();
    ui->widget_coolant_level->setParameter(RingDialPro::CoolantLevel_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
    ui->widget_coolant_level->setValue(tmp_start);
}

VehicleDataWgt::~VehicleDataWgt()
{
    delete ui;
}

VehicleDataWgt *VehicleDataWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new VehicleDataWgt();
    }
    return s_pInstance;
}
void VehicleDataWgt::updateUI()
{
    ui->widget_oil_pressure->setValue(m_pModel->m_VehicleData.bodys.engineOilPressure);
    ui->widget_oil_volume->setValue(m_pModel->m_VehicleData.bodys.fuelLevel);
    ui->widget_Coolant_temperature->setValue(m_pModel->m_VehicleData.bodys.engineCoolantTemperature);
    ui->widget_coolant_level->setValue(m_pModel->m_VehicleData.bodys.coolantLevel);

#if 0
    static bool init_flag = true;
    VehicleType vehicle_type = (VehicleType)m_pModel->m_VehicleData.bodys.vehicleType;
    if (m_vehicle_type != vehicle_type)
    {
        m_vehicle_type = vehicle_type;
        init_flag = true;
    }

    switch (m_vehicle_type)
    {
    case VehicleType_Electric:
    {
        if (init_flag)
        {
            init_flag = false;

            float tmp_start,tmp_end,tmp_min,tmp_max;
            // 电池电量
            QVariant data_batteryCapacity = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                                "/rcdconfig.json","EngineOilPressure");
            if(data_batteryCapacity.toList().isEmpty()) return;
            tmp_start = data_batteryCapacity.toList()[0].toMap().value("Start").toFloat();
            tmp_min = data_batteryCapacity.toList()[0].toMap().value("Min").toFloat();
            tmp_max = data_batteryCapacity.toList()[0].toMap().value("Max").toFloat();
            tmp_end = data_batteryCapacity.toList()[0].toMap().value("End").toFloat();
            ui->widget_battery_voltage->setParameter(RingDialPro::BatteryLevel_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
            ui->widget_battery_voltage->setValue(tmp_start);

            // 电芯温度
            QVariant data_cellTemperature= jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                                "/rcdconfig.json","FuelLevel");
            if(data_cellTemperature.toList().isEmpty()) return;
            tmp_start = data_cellTemperature.toList()[0].toMap().value("Start").toFloat();
            tmp_min = data_cellTemperature.toList()[0].toMap().value("Min").toFloat();
            tmp_max = data_cellTemperature.toList()[0].toMap().value("Max").toFloat();
            tmp_end = data_cellTemperature.toList()[0].toMap().value("End").toFloat();
            ui->widget_Coolant_temperature->setParameter(RingDialPro::CellTemperature_omter, tmp_start, tmp_end, tmp_min, tmp_max);
            ui->widget_Coolant_temperature->setValue(tmp_start);
        }
        else
        {
            ui->widget_battery_voltage->setValue(m_pModel->m_VehicleData.bodys.batteryLevel);
            ui->widget_Coolant_temperature->setValue(m_pModel->m_VehicleData.bodys.cellTemperature);
        }
        break;
    }
    case VehicleType_Diesel:
    {
        if (init_flag)
        {
            init_flag = false;
            
            float tmp_start,tmp_end,tmp_min,tmp_max;
            // 发动机冷却液温度
            QVariant data_engineCoolantTemperature = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                                        "/rcdconfig.json","EngineOilPressure");
            if(data_engineCoolantTemperature.toList().isEmpty()) return;
            tmp_start = data_engineCoolantTemperature.toList()[0].toMap().value("Start").toFloat();
            tmp_min = data_engineCoolantTemperature.toList()[0].toMap().value("Min").toFloat();
            tmp_max = data_engineCoolantTemperature.toList()[0].toMap().value("Max").toFloat();
            tmp_end = data_engineCoolantTemperature.toList()[0].toMap().value("End").toFloat();
            ui->widget_battery_voltage->setParameter(RingDialPro::EngineOilPressure_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
            ui->widget_battery_voltage->setValue(tmp_start);

            // 排气口温度
            QVariant data_exhaustPortTemperature = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                        "/rcdconfig.json","FuelLevel");
            if(data_exhaustPortTemperature.toList().isEmpty()) return;
            tmp_start = data_exhaustPortTemperature.toList()[0].toMap().value("Start").toFloat();
            tmp_min = data_exhaustPortTemperature.toList()[0].toMap().value("Min").toFloat();
            tmp_max = data_exhaustPortTemperature.toList()[0].toMap().value("Max").toFloat();
            tmp_end = data_exhaustPortTemperature.toList()[0].toMap().value("End").toFloat();
            ui->widget_Coolant_temperature->setParameter(RingDialPro::FuelLevel_ometer, tmp_start, tmp_end, tmp_min, tmp_max);
            ui->widget_Coolant_temperature->setValue(tmp_start);
        }
        else
        {
            ui->widget_battery_voltage->setValue(/*m_pModel->m_VehicleData.bodys.engineCoolantTemperature*/29);
            ui->widget_Coolant_temperature->setValue(/*m_pModel->m_VehicleData.bodys.exhaustPortEmperature*/90);
        }
        break;
    }

    case VehicleType_Dust:
    {
        if (init_flag)
        {
            init_flag = false;
            
            float tmp_start,tmp_end,tmp_min,tmp_max;
            // 温度
            QVariant data_temperature = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                                        "/rcdconfig.json","temperature");
            if(data_temperature.toList().isEmpty()) return;
            tmp_start = data_temperature.toList()[0].toMap().value("Start").toFloat();
            tmp_min = data_temperature.toList()[0].toMap().value("Min").toFloat();
            tmp_max = data_temperature.toList()[0].toMap().value("Max").toFloat();
            tmp_end = data_temperature.toList()[0].toMap().value("End").toFloat();
            ui->widget_battery_voltage->setParameter(RingDialPro::Temperature_omter, tmp_start, tmp_end, tmp_min, tmp_max);
            ui->widget_battery_voltage->setValue(tmp_start);

            // 水箱水位
            QVariant data_waterTankLevel = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+ \
                                                                        "/rcdconfig.json","waterTankLevel");
            if(data_waterTankLevel.toList().isEmpty()) return;
            tmp_start = data_waterTankLevel.toList()[0].toMap().value("Start").toFloat();
            tmp_min = data_waterTankLevel.toList()[0].toMap().value("Min").toFloat();
            tmp_max = data_waterTankLevel.toList()[0].toMap().value("Max").toFloat();
            tmp_end = data_waterTankLevel.toList()[0].toMap().value("End").toFloat();
            ui->widget_Coolant_temperature->setParameter(RingDialPro::WaterTankLevel_omter, tmp_start, tmp_end, tmp_min, tmp_max);
            ui->widget_Coolant_temperature->setValue(tmp_start);
        }
        else
        {
            ui->widget_battery_voltage->setValue(m_pModel->m_VehicleData.bodys.temperature);
            ui->widget_Coolant_temperature->setValue(m_pModel->m_VehicleData.bodys.waterTankLevel);
        }
        break;
    }   
    default:
        break;
    }
#endif

    //双闪 左转 右转
    static bool emergencyFlash_flag = false;
    static bool left_flag = false;
    static bool right_flag = false;
    if(m_pModel->m_VehicleData.lights.emergencyFlash == 0)
    {
        emergencyFlash_flag = false;
        if(m_pModel->m_VehicleData.lights.left == 0)
        {
            left_flag = false;
            ui->forwardLeft->setPixmap(QPixmap(":/resource/icon/forwardLeft-black.png"));
        }
        else
        {
            if (!left_flag)
            {
                left_flag = true;
                ui->forwardLeft->setPixmap(QPixmap(":/resource/icon/forwardLeft-highlight.png"));
            }
            else
            {
                left_flag = false;
                ui->forwardLeft->setPixmap(QPixmap(":/resource/icon/forwardLeft-black.png"));
            }
        }

        if(m_pModel->m_VehicleData.lights.right == 0)
        {
            right_flag = false;
            ui->forwardRight->setPixmap(QPixmap(":/resource/icon/forwardRight-black.png"));
        }
        else
        {
            if (!right_flag)
            {
                right_flag = true;
                ui->forwardRight->setPixmap(QPixmap(":/resource/icon/forwardRight-highlight.png"));
            }
            else
            {
                right_flag = false;
                ui->forwardRight->setPixmap(QPixmap(":/resource/icon/forwardRight-black.png"));
            }
        }
    }
    else
    {
        right_flag = false;
        left_flag = false;
        if (!emergencyFlash_flag)
        {
            emergencyFlash_flag = true;
            ui->forwardLeft->setPixmap(QPixmap(":/resource/icon/forwardLeft-highlight.png"));
            ui->forwardRight->setPixmap(QPixmap(":/resource/icon/forwardRight-highlight.png"));
        }
        else
        {
            emergencyFlash_flag = false;
            ui->forwardLeft->setPixmap(QPixmap(":/resource/icon/forwardLeft-black.png"));
            ui->forwardRight->setPixmap(QPixmap(":/resource/icon/forwardRight-black.png"));
        }
    }

    //近光灯
    if(m_pModel->m_VehicleData.lights.lowBeam==0)
    {
        ui->lowBeam->setPixmap(QPixmap(":/resource/icon/lowBeam-black.png"));
    }else //if(m_pModel->m_VehicleData.lowBeam==1)
    {
        ui->lowBeam->setPixmap(QPixmap(":/resource/icon/lowBeam-highlight.png"));
    }
    //远光灯
    if(m_pModel->m_VehicleData.lights.highBeam==0)
    {
        ui->highBeam->setPixmap(QPixmap(":/resource/icon/highBeam-black.png"));
    }else //if(m_pModel->m_VehicleData.highBeam==1)
    {
        ui->highBeam->setPixmap(QPixmap(":/resource/icon/highBeam-highlight.png"));
    }
    //示廓灯
    if(m_pModel->m_VehicleData.lights.positoinLamp==0)
    {
        ui->emergencyFlash->setPixmap(QPixmap(":/resource/icon/emergencyFlash-black.png"));
    }else //if(m_pModel->m_VehicleData.positoinLamp==1)
    {
        ui->emergencyFlash->setPixmap(QPixmap(":/resource/icon/emergencyFlash-highlight.png"));
    }

    //侧灯
    if(m_pModel->m_VehicleData.lights.sideLamp==0)
    {
        ui->sideLamp->setPixmap(QPixmap(":/resource/icon/sideLamp-black.png"));
    }else //if(m_pModel->m_VehicleData.forwardRight==1)
    {
        ui->sideLamp->setPixmap(QPixmap(":/resource/icon/sideLamp-highlight.png"));
    }

    //排气制动
    if(m_pModel->m_VehicleData.bodys.exhaustBrake==0)
    {
        ui->exhaustBrake->setPixmap(QPixmap(":/resource/icon/exhaustBrake-black.png"));
    }else //if(m_pModel->m_VehicleData.exhaustBrake==1)
    {
        ui->exhaustBrake->setPixmap(QPixmap(":/resource/icon/exhaustBrake-highlight.png"));
    }

    //胎压异常告警灯
    if(m_pModel->m_VehicleData.bodys.tirePressureWarning==0)
    {
        ui->tirePressureWarning->setPixmap(QPixmap(":/resource/icon/tirePressureWarning-black.png"));
    }else //if(m_pModel->m_VehicleData.tirePressureWarning==1)
    {
        ui->tirePressureWarning->setPixmap(QPixmap(":/resource/icon/tirePressureWarning-highlight.png"));
    }
    
    //车斗状态0x00/0x01/0x02/0x03/0x04/0x05 下止点/上止点/下降/上升/中间/保持
    if((m_pModel->m_VehicleData.bodys.bucketCtrl==0x02) || (m_pModel->m_VehicleData.bodys.bucketCtrl==0x03) ||
       (m_pModel->m_VehicleData.bodys.bucketCtrl==0x04) || (m_pModel->m_VehicleData.bodys.bucketCtrl==0x05))//下降/上升,不能覆盖举升后保持
    {//中间状态闪烁
        static bool lightOn=true;
        if(lightOn)
        {
            ui->bucketCtrl->setPixmap(QPixmap(":/resource/icon/bucketCtrlMid-highlight.png"));
        }
        else
        {
            ui->bucketCtrl->setPixmap(QPixmap(":/resource/icon/bucketCtrlMid.png"));
        }
        lightOn = !lightOn;
    }else if(m_pModel->m_VehicleData.bodys.bucketCtrl==1)
    {//上止点
        ui->bucketCtrl->setPixmap(QPixmap(":/resource/icon/bucketCtrlUp-highlight.png"));
    }else if(m_pModel->m_VehicleData.bodys.bucketCtrl==0)
    {//下止点
        ui->bucketCtrl->setPixmap(QPixmap(":/resource/icon/bucketCtrlDown-highlight.png"));
    }

    ui->bucketCtrl->setPixmap(QPixmap(":/resource/icon/bucketCtrl-black.png"));
}
