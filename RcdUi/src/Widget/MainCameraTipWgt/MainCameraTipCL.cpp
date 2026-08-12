#include "MainCameraTipCL.h"
#include "public/fbsstructure.h"

MainCameraTipCL::MainCameraTipCL(QObject *parent) : IController(parent)
{

}

void MainCameraTipCL::setModel(MainCameraTipModel *model)
{
    m_pModel = model;
}

void MainCameraTipCL::getFromAny(ModuleDir moduleDir, int cmd, QVariant data)
{
    moduleDir.clear();

    switch (cmd) {
    case MainCameraTipWgtCmdType::MainCameraTip_Update:{
        emit pushDataToView(CL_UpdateText,data);
        break;
    }
    case MainCameraTipWgtCmdType::MainCameraTip_Hide:{
        emit pushDataToView(CL_Hide);
        break;
    }

    default:{break;}
    }

}
