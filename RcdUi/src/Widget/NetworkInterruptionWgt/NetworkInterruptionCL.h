#ifndef NetworkInterruptionCL_H
#define NetworkInterruptionCL_H

#include "Interface/IController.h"
#include "NetworkInterruptionModel.h"

class NetworkInterruptionCL : public IController
{
    Q_OBJECT
public:
    explicit NetworkInterruptionCL(QObject *parent = nullptr);
    ~NetworkInterruptionCL() override;
    enum NetworkInterruptionCLCmdType {
        NetworkInterruptionCL_ShowCmd = 0,
        NetworkInterruptionCL_Update,
        NetworkInterruptionCL_Enter,
        NetworkInterruptionCL_Max,
        NetworkInterruptionCL_HideCmd
    };
    bool isShow();
    void keyPress();



    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(NetworkInterruptionModel *model);

private:

    NetworkInterruptionModel *m_pModel;
};

#endif // NetworkInterruptionCL_H
