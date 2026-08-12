#include "NotSatisfiedWithTakeoverModel.h"

NotSatisfiedWithTakeoverModel::NotSatisfiedWithTakeoverModel(QObject *parent) : IModel(parent)
{
    memset(&m_vehicleData,0,sizeof(m_vehicleData));
}

void NotSatisfiedWithTakeoverModel::setVehicleState(vehicleDataST st)
{
    memcpy(&m_vehicleData,&st,sizeof(st));
    emit sendModelUpdate(MC_Update);
}

