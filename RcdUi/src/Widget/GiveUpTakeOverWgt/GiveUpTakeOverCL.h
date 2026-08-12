#ifndef GiveUpTakeOverCL_H
#define GiveUpTakeOverCL_H

#include "Interface/IController.h"
#include "GiveUpTakeOverModel.h"

class GiveUpTakeOverCL : public IController
{
    Q_OBJECT
public:
    explicit GiveUpTakeOverCL(QObject *parent = nullptr);
    ~GiveUpTakeOverCL() override;
    enum AcceptTaskWorkCLCmd
    {
        GiveUpTakeOverCLCmd_Show = 0,
        GiveUpTakeOverCLCmd_Enter,
        GiveUpTakeOverCLCmd_Max
    };

    void keyPress(QString keyStr);
    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void getButton(int numb);
    void setModel(GiveUpTakeOverModel *model);

private:

    GiveUpTakeOverModel *m_pModel;
};

#endif // GiveUpTakeOverCL_H
