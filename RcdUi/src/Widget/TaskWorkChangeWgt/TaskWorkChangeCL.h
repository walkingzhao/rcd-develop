#ifndef TaskWorkChangeCL_H
#define TaskWorkChangeCL_H

#include "Interface/IController.h"
#include "TaskWorkChangeModel.h"

class TaskWorkChangeCL : public IController
{
    Q_OBJECT
public:
    explicit TaskWorkChangeCL(QObject *parent = nullptr);
    ~TaskWorkChangeCL() override;
    enum TaskWorkChangeCLCmdType {
       TaskWorkChangeCL_ShowCmd = 0,
       TaskWorkChangeCL_Max
   };

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(TaskWorkChangeModel *model);

private:

    TaskWorkChangeModel *m_pModel;
};

#endif // TaskWorkChangeCL_H
