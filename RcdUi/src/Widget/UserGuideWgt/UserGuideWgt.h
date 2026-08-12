#ifndef UserGuideWgt_H
#define UserGuideWgt_H

#include "Interface/IFunWidget.h"
#include "UserGuideCL.h"
#include "UserGuideModel.h"

namespace Ui {
class UserGuideWgt;
}

class Dashboard;
class AnalogClock;

class UserGuideWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit UserGuideWgt(QWidget *parent = nullptr);
    ~UserGuideWgt() override;

    static UserGuideWgt* GetInstance();
    virtual bool isQuit() override;
    virtual void initWidget() override;
    virtual void updateWidget() override;

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::UserGuideWgt *ui;
    static UserGuideWgt        *s_pInstance;
    UserGuideCL                *m_pCL;
    UserGuideModel             *m_pModel;
//    Dashboard                    *m_pDashboard;
    AnalogClock                  *m_pAnalogClock;
};

#endif // UserGuideWgt_H
