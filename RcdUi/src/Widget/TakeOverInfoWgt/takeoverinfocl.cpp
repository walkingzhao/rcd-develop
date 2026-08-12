#include "takeoverinfocl.h"
#include "public/fbsstructure.h"
#include <QDebug>
TakeOverInfoCL::TakeOverInfoCL(QObject *parent) : IController(parent)
{

}

void TakeOverInfoCL::setModel(TakeOverInfoModel *model)
{
    m_pModel = model;
}

void TakeOverInfoCL::getFromAny(ModuleDir moduleDir, int cmd, QVariant data)
{
    moduleDir.clear();
    switch (cmd) {
    case TakeOverInfoWgtCmdType::TakeOver_UpdateTask:{
        cabinTakeoverTaskApplyST st=data.value<cabinTakeoverTaskApplyST>();
        m_pModel->setAllInfo(st.dispatchTask.targetName,
                             st.truckName,
                             st.dispatchTask.targetName);
        break;
    }
    case TakeOverInfoWgtCmdType::TakeOver_UpdateDispatchTask:{
        m_pModel->setTargetInfo(data.toString());
        break;
    }
    case TakeOverInfoWgtCmdType::TakeOver_UpdateLoadStatus:{

        ReportRoadTaskInfoST st=data.value<ReportRoadTaskInfoST>();
        m_pModel->setLoadStatus(st.loadStatus);
        break;
    }

    default:{break;}
    }
}
