#include "infocl.h"

InfoCL::InfoCL(QObject *parent) : IController(parent)
{

}

InfoCL::~InfoCL()
{

}

void InfoCL::setModel(InfoModel *model)
{
    m_pModel = model;
}

void InfoCL::getFromAny(ModuleDir moduleDir, int cmd, QVariant data)
{

    moduleDir.clear();
    InfoWgtCmdType Cmd = static_cast<InfoWgtCmdType>(cmd);

    qDebug()<<"InfoCL::getFromAny Cmd:"<<Cmd;

    switch (Cmd) {
    case InfoWgtCmdType::IF_InsertMsg:{
        m_pModel->insertMsg(data.toString());
        break;
    }

    default:{break;}
    }
}
