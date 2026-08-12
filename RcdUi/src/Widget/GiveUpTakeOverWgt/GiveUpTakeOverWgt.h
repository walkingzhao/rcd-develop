#ifndef GiveUpTakeOverWgt_H
#define GiveUpTakeOverWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "GiveUpTakeOverCL.h"
#include "GiveUpTakeOverModel.h"
namespace Ui {
class GiveUpTakeOverWgt;
}

class GiveUpTakeOverWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit GiveUpTakeOverWgt(QWidget *parent = nullptr);
    ~GiveUpTakeOverWgt();
    static GiveUpTakeOverWgt *GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

protected:
    void paintEvent(QPaintEvent *event);

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();

private:
    Ui::GiveUpTakeOverWgt *ui;
    static GiveUpTakeOverWgt        *s_pInstance;
    GiveUpTakeOverCL                *m_pCL;
    GiveUpTakeOverModel             *m_pModel;
};

#endif // GiveUpTakeOverWgt_H
