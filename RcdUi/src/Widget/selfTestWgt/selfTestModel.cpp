#include "selfTestModel.h"

selfTestModel::selfTestModel(QObject *parent) : IModel(parent)
{

}

void selfTestModel::setState(VehicleStatus &st)
{
}

void selfTestModel::updateContent(SelfTest_ControlData_St &content)
{
    std::memmove(&m_content,&content,sizeof(content));
    emit sendModelUpdate(Self_Update_content);
}

void selfTestModel::updateWheelValue(SelfTest_CtrlRawData_St &wheelData)
{
    memcpy(&m_wheelData,&wheelData,sizeof(wheelData));
    emit sendModelUpdate(Self_Update_wheel_content);
}

void selfTestModel::updateEmptyStatus()
{
    emit sendModelUpdate(Self_Update_empty_content);
}

void selfTestModel::updateTakeoverStatus()
{
    emit sendModelUpdate(Self_Update_takeover_content);
}

void selfTestModel::updateBlindStatus()
{
    emit sendModelUpdate(Self_Update_blind_content);
}
