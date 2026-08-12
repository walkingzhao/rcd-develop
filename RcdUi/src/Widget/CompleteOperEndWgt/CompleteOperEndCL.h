#ifndef CompleteOperEndCL_H
#define CompleteOperEndCL_H

#include "Interface/IController.h"
#include "CompleteOperEndModel.h"

class CompleteOperEndCL : public IController
{
    Q_OBJECT
public:
    explicit CompleteOperEndCL(QObject *parent = nullptr);
    ~CompleteOperEndCL() override;
    enum CompleteOperEndCLCmdType {
        CompleteOperEndCL_ShowCmd = 0,
        CompleteOperEndCL_Update,
        CompleteOperEndCL_Enter,
        CompleteOperEndCL_Max
    };

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(CompleteOperEndModel *model);
    void keyPress();
    bool isShow();

private:

    CompleteOperEndModel *m_pModel;
};

#endif // CompleteOperEndCL_H
