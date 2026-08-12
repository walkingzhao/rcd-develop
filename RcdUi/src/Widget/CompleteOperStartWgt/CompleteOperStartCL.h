#ifndef CompleteOperStartCL_H
#define CompleteOperStartCL_H

#include "Interface/IController.h"
#include "CompleteOperStartModel.h"

class CompleteOperStartCL : public IController
{
    Q_OBJECT
public:
    explicit CompleteOperStartCL(QObject *parent = nullptr);
    ~CompleteOperStartCL() override;
    enum CompleteOperStartCLCmdType {
       CompleteOperStartCL_Show = 0,
       CompleteOperStartCL_Enter,
       CompleteOperStartCL_Max
    };

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;
    void keyPress();

    void setModel(CompleteOperStartModel *model);
    bool isShow();
//    void setTimerStatus(bool checked);

private:

    CompleteOperStartModel *m_pModel;
};

#endif // CompleteOperStartCL_H
