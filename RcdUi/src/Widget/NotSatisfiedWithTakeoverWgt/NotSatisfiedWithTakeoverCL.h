#ifndef NotSatisfiedWithTakeoverCL_H
#define NotSatisfiedWithTakeoverCL_H

#include "Interface/IController.h"
#include "NotSatisfiedWithTakeoverModel.h"

class NotSatisfiedWithTakeoverCL : public IController
{
    Q_OBJECT
public:
    explicit NotSatisfiedWithTakeoverCL(QObject *parent = nullptr);
    ~NotSatisfiedWithTakeoverCL() override;
    enum NotSatisfiedWithTakeoverCLCmdType {
       NotSatisfiedWithTakeoverCL_Show = 0,
        NotSatisfiedWithTakeoverCL_Enter,
       NotSatisfiedWithTakeoverCL_Max
    };

    void keyPress(QString keyStr);

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(NotSatisfiedWithTakeoverModel *model);
    bool isShow();

private:

    NotSatisfiedWithTakeoverModel *m_pModel;

};

#endif // NotSatisfiedWithTakeoverCL_H
