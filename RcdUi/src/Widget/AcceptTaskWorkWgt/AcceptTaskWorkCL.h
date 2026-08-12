#ifndef AcceptTaskWorkCL_H
#define AcceptTaskWorkCL_H

#include "Interface/IController.h"
#include "AcceptTaskWorkModel.h"

class AcceptTaskWorkCL : public IController
{
    Q_OBJECT
public:
    explicit AcceptTaskWorkCL(QObject *parent = nullptr);
    ~AcceptTaskWorkCL() override;
    enum AcceptTaskWorkCLCmd
    {
        AcceptTaskWorkCLCmd_Show = 0,
        AcceptTaskWorkCLCmd_Enter,
        AcceptTaskWorkCLCmd_Max
    };

    void keyPress(QString keyStr);
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(AcceptTaskWorkModel *model);

private:

    AcceptTaskWorkModel *m_pModel;
};

#endif // AcceptTaskWorkCL_H
