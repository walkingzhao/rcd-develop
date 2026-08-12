#ifndef MSGWGT_H
#define MSGWGT_H

#include <QWidget>
#include "Interface/IFunWidget.h"
#include "msgCl.h"
#include "msgModel.h"
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
namespace Ui {
class msgWgt;
}

class msgWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit msgWgt(QWidget *parent = nullptr);
    ~msgWgt();

    static msgWgt* GetInstance();
    virtual bool isQuit() override;
    virtual void initWidget() override;
    virtual void updateWidget() override;

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;
private:
    Ui::msgWgt *ui;
    static msgWgt        *s_pInstance;
    msgCl                *m_pCL;
    msgModel             *m_pModel;
};

#endif // MSGWGT_H
