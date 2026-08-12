#ifndef selfTestCL_H
#define selfTestCL_H

#include "Interface/IController.h"
#include "selfTestModel.h"

class selfTestCL : public IController
{
    Q_OBJECT
public:
    explicit selfTestCL(QObject *parent = nullptr);
    ~selfTestCL() override;
    enum selfTestCL_CmdType {
        selfTestCL_ShowCmd = 0,
        selfTestCL_Update,
        selfTestCL_Enter,
        selfTestCL_Max,
        selfTestCL_HideCmd
    };

    bool isShow();
    void keyPress();

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;
    void setModel(selfTestModel *model);

private:
    selfTestModel *m_pModel;
};

#endif // selfTestCL_H
