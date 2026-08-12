#include "TipsPopupModel.h"

TipsPopupModel::TipsPopupModel(QObject *parent) : IModel(parent)
{

}

void TipsPopupModel::setState(VehicleStatus &st)
{
//    std::memmove(&m_vehicleState,&st,sizeof(st));
//    emit sendModelUpdate(MC_Update);
}

void TipsPopupModel::updateContent(popContent &content)
{
    std::memmove(&m_content,&content,sizeof(content));
    emit sendModelUpdate(TP_Update_content);
}
