#include "msgWgt.h"
#include "ui_msgWgt.h"
#include <QDebug>

msgWgt* msgWgt::s_pInstance = nullptr; //初始化静态数据成员
msgWgt::msgWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::msgWgt)
{
    ui->setupUi(this);
    m_pCL = new msgCl();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new msgModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);
}

msgWgt::~msgWgt()
{
    delete ui;
    delete m_pCL;
    delete m_pModel;
}

msgWgt *msgWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new msgWgt();
    }
    return s_pInstance;
}

void msgWgt::initWidget()
{
//    qInfo()<<"msgWgt::initWidget";
    m_pCL->intoAction();
    this->updateWidget();


}

bool msgWgt::isQuit()
{
//    qInfo()<<"msgWgt::isQuit";
    m_pCL->exitAction();
    return true;
}

void msgWgt::updateWidget()
{
//    qInfo() << "msgWgt::updateWidget";
}

void msgWgt::onClDataCome(int cmd, QVariant data)
{
    data.isValid();
    switch (cmd) {
    case 1:
    {
        this->updateWidget();
        break;
    }
    case 2:
    {

        break;
    }

    case 3:
    {

        break;
    }

    default:
        break;
    }
}

void msgWgt::onModelUpdate(int cmd)
{
//    VehicleInfoModel::ModelCmdType tCmd = static_cast<VehicleInfoModel::ModelCmdType>(cmd);
//    switch (tCmd) {
//    case VehicleInfoModel::MC_UpdateAll:
//    {
//        this->updateWidget();
//        break;
//    }
//    case VehicleInfoModel::MC_AddSysInfo:
//    {
//        ui->sysInfo->insertPlainText(m_pModel->m_newInfo + "\r\n");
//        ui->sysInfo->moveCursor(QTextCursor::End);
//        break;
//    }
//    case VehicleInfoModel::MC_Oil://油量
//    {
//        ui->vehicleWgt_2->setValue(m_pModel->_oilvalue);
//        break;
//    }
//    case VehicleInfoModel::MC_Map://地图数据
//    {
//        //        qDebug()<<m_pModel->_gpsDataMap.at(0).toDouble()<<m_pModel->_gpsDataMap.at(1).toDouble()<<
//        //                  m_pModel->_gpsDataMap.at(2).toDouble()<<"LLLLLLLLLLLLLLLLLL";
//        //        ui->vehicleWgt_2->setValue(m_pModel->_oilvalue);
//        //        ui->map_widget->setvalue(m_pModel->_gpsDataMap)
//        break;
//    }
//    default:
//        break;
//    }
}

