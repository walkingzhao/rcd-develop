#include "vehicledatamodel.h"

VehicleDataModel::VehicleDataModel(QObject *parent):IModel(parent)
{
    memset(&m_VehicleData,0,sizeof(m_VehicleData));
}

void VehicleDataModel::setVehicleState(vehicleDataST st)
{
    memcpy(&m_VehicleData,&st,sizeof(st));
//    emit sendModelUpdate(MC_UpdateVehicleData);
}
