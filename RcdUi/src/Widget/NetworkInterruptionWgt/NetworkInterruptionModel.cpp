#include "NetworkInterruptionModel.h"

NetworkInterruptionModel::NetworkInterruptionModel(QObject *parent) : IModel(parent)
{

}

void NetworkInterruptionModel::setState(VehicleStatus &st)
{
    std::memmove(&m_vehicleState,&st,sizeof(st));
    emit sendModelUpdate(MC_Update);
}

void NetworkInterruptionModel::updateSelfState(SelfCheckStatusST &selfState)
{
    std::memmove(&m_selfState,&selfState,sizeof(selfState));
    emit sendModelUpdate(MC_UpdateSelf);
}
