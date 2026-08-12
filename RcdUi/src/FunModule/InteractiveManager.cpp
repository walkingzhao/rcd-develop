#include "InteractiveManager.h"
#include <QDebug>

InteractiveManager* InteractiveManager::s_pInstance = nullptr;

InteractiveManager::InteractiveManager(QObject *parent) : IController(parent)
{
    m_focusModule = MD_MainMonitor;
    m_focusRelationship.clear();
}

InteractiveManager::~InteractiveManager()
{

}

InteractiveManager *InteractiveManager::GetInstance(QObject *parent)
{
    if(s_pInstance == nullptr) {
        s_pInstance = new InteractiveManager(parent);
    }
    return s_pInstance;
}

void InteractiveManager::getFromAny(ModuleDir moduleDir,int cmd,QVariant data)
{
    moduleDir.clear();
    InteractiveManagerCmdType Cmd = static_cast<InteractiveManagerCmdType>(cmd);//更新当前界面焦点

    switch (Cmd) {
    case IA_KeyPress:{
//        Qt::Key key = static_cast<Qt::Key>(data.toInt());
//        if(key == Qt::Key_PageUp){
//            ModuleDir module;
//            module.append(MD_MainCamera);
//            emit sendToMain(module,CC_KeyPress,data);
//        }        else
        {
            ModuleDir module;
            module.append(m_focusModule);
            emit sendToMain(module,CC_KeyPress,data); //统一命令

        }
        break;
    }
    case IA_SwitchLayout:{
        LayoutType layout = static_cast<LayoutType>(data.toInt());
        if(layout == LT_Monitor){
            System::getInstance()->setCurrentLayoutType(LT_Monitor);
//            System::getInstance()->clearMsgWidgetMap();xuzhkxuzhk
            //更新驾驶状态为监控中
            ModuleDir module;
            module.clear();
            module.append(MD_MainCamera);
            emit sendToMain(module,MC_UpdateState,"");
            m_focusModule = MD_MainMonitor;
        }else if(layout == LT_RemoteControl){
            System::getInstance()->setCurrentLayoutType(LT_RemoteControl);
            m_focusModule = MD_MainCamera;
        }
        break;
    }
    default:{break;}
    }
}


