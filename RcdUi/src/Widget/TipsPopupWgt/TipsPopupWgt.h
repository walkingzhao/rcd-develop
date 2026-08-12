#ifndef TipsPopupWgt_H
#define TipsPopupWgt_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "TipsPopupCL.h"
#include "TipsPopupModel.h"
#include <QTimer>

namespace Ui {
class TipsPopupWgt;
}

class TipsPopupWgt : public IFunWidget
{
    Q_OBJECT
public:
    explicit TipsPopupWgt(QWidget *parent = nullptr);
    ~TipsPopupWgt();
    static TipsPopupWgt* GetInstance();
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

private:
    void updateContent();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();
    void statuSlots();

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private:
    Ui::TipsPopupWgt *ui;
    static TipsPopupWgt        *s_pInstance;
    TipsPopupCL                *m_pCL;
    TipsPopupModel             *m_pModel;
};

#endif // TipsPopupWgt_H
