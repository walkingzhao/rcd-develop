#ifndef TipsPopupCL_H
#define TipsPopupCL_H

#include "Interface/IController.h"
#include "TipsPopupModel.h"

class TipsPopupCL : public IController
{
    Q_OBJECT
public:
    explicit TipsPopupCL(QObject *parent = nullptr);
    ~TipsPopupCL() override;
    enum TipsPopupLCmdType {
        TipsPopupCL_ShowCmd,
        TipsPopupCL_Update,
        TipsPopupCL_Enter,
        TipsPopupCL_Max,
        TipsPopupCL_HideCmd
    };

    bool isShow();
    void keyPress();

    void doInit() override;
    void doUnInit() override;
    bool intoAction() override;
    bool exitAction() override;
    void getFromAny(ModuleDir moduleDir,int cmd,QVariant data ) override;

    void setModel(TipsPopupModel *model);

private:
    TipsPopupModel *m_pModel;
};

#endif // TipsPopupCL_H
