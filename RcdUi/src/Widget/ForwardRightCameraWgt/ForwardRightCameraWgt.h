#ifndef ForwardRightCameraWgt_H
#define ForwardRightCameraWgt_H

#include "Interface/IFunWidget.h"
#include "ForwardRightCameraCL.h"
#include "Component/audiodecode.h"

namespace Ui {
class ForwardRightCameraWgt;
}

class TitleWgt;

class ForwardRightCameraWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit ForwardRightCameraWgt(QWidget *parent = nullptr);
    ~ForwardRightCameraWgt() override;

    static ForwardRightCameraWgt* GetInstance();
    virtual bool isQuit() override;
    virtual void initWidget() override;
    virtual void updateWidget() override;
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;

private:
    Ui::ForwardRightCameraWgt *ui;
    static ForwardRightCameraWgt        *s_pInstance;
    ForwardRightCameraCL                *m_pCL;

    TitleWgt                     *m_pTitleWgt;
    QString                      vehicleName;

    AudioDecode *audioDecode=nullptr;

};

#endif // ForwardRightCameraWgt_H
