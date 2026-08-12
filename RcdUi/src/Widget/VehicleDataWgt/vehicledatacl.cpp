#include "vehicledatacl.h"

VehicleDataCL::VehicleDataCL(QObject *parent):IController(parent)
{

}

void VehicleDataCL::setModel(VehicleDataModel *model)
{
    m_pModel = model;
}

void VehicleDataCL::getFromAny(ModuleDir moduleDir, int cmd, QVariant data)
{

    moduleDir.clear();
    switch (cmd) {
    case VD_UpdateVehicleData:{
        vehicleDataST st=data.value<vehicleDataST>();
        m_pModel->setVehicleState(st);

//        qDebug()<<"VehicleDataCL VD_UpdateVehicleData:"
//             <<st.speed<<(int)st.gear<<(int)st.mode<<(int)st.handBrake
//            <<"近光灯:"<<(int)st.lowBeam<<"双闪:"<<st.emergencyFlash
//           <<"排气制动"<<st.exhaustBrake;
        break;
    }

    default:{break;}
    }
}
