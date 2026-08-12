#include "loadinstructioncl.h"
#include "public/fbsstructure.h"

LoadInstructionCL::LoadInstructionCL(QObject *parent) : IController(parent)
{

}

void LoadInstructionCL::setModel(LoadInstructionModel *model)
{
    m_pModel = model;
}

void LoadInstructionCL::getFromAny(ModuleDir moduleDir, int cmd, QVariant data)
{
    moduleDir.clear();

    switch (cmd) {
    case LoadInstructionWgtCmdType::LoadInstruction_Update:{
        qDebug()<<"test report road ";
        m_pModel->m_TaskLoadInfo = data.value<ReportRoadTaskInfoST>();
        qDebug()<<"test report road end";
        break;
    }

    default:{break;}
    }

}
