#ifndef TAKEOVERINFOWGT_H
#define TAKEOVERINFOWGT_H

#include <QWidget>
#include "takeoverinfocl.h"
#include "takeoverinfomodel.h"
#include "Interface/IFunWidget.h"
namespace Ui {
class TakeOverInfoWgt;
}
enum Car_num{
    no_load=0,//空载
    half_load,//半载
    full_load,//满载
    unkonwn   //未知
};

class TakeOverInfoWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit TakeOverInfoWgt(QWidget *parent = nullptr);
    ~TakeOverInfoWgt();
    static TakeOverInfoWgt *GetInstance();
public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::TakeOverInfoWgt *ui;
    TakeOverInfoCL                *m_pCL;//控制类
    TakeOverInfoModel             *m_pModel;//模型类
    static TakeOverInfoWgt        *s_pInstance;
};

#endif // TAKEOVERINFOWGT_H
