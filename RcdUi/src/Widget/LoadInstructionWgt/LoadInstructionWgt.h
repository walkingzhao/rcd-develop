#ifndef LOADINSTRUCTIONWGT_H
#define LOADINSTRUCTIONWGT_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "loadinstructioncl.h"
#include "loadinstructionmodel.h"
#include <QTimer>
namespace Ui {
class LoadInstructionWgt;
}
enum  Load_instruction{
    drive_in = 0,//请驶入
    loading,//装载中
    drive_away, //请驶离
    re_dock, //重新停靠
};

class LoadInstructionWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit LoadInstructionWgt(QWidget *parent = nullptr);
    ~LoadInstructionWgt();
    static LoadInstructionWgt *GetInstance();
    void initUi();
    void setLoadValue(Load_instruction flag,bool checked);

public slots:
    void tickTimerOut();
private:
    Ui::LoadInstructionWgt *ui;
    LoadInstructionCL                *m_pCL;//控制类
    LoadInstructionModel             *m_pModel;//模型类
    static LoadInstructionWgt        *s_pInstance;
    QTimer                           tickTimer;
};

#endif // LOADINSTRUCTIONWGT_H
