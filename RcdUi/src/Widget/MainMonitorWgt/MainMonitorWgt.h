#ifndef MainMonitorWgt_H
#define MainMonitorWgt_H

#include "Interface/IFunWidget.h"
#include "MainMonitorCL.h"
#include "MainMonitorModel.h"

#include <QToolButton>

namespace Ui {
class MainMonitorWgt;
}

class TGFrame;
class OpenGLWidget;
class QLabel;

class MainMonitorWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit MainMonitorWgt(QWidget *parent = nullptr);
    ~MainMonitorWgt() override;

    static MainMonitorWgt* GetInstance();
    virtual bool isQuit() override;
    virtual void initWidget() override;
    virtual void updateWidget() override;
    virtual void showEvent(QShowEvent *) override;
    virtual void hideEvent(QHideEvent *) override;

public slots:
    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private slots:
    void on_selfTestBtn();

private:
    Ui::MainMonitorWgt *ui;
    static MainMonitorWgt        *s_pInstance;
    MainMonitorCL                *m_pCL;
    MainMonitorModel             *m_pModel;

    QVector<TGFrame*>            m_frameVector;
    QVector<OpenGLWidget*>       m_playWgtVector;
    QVector<QLabel*>             m_nameVector;

    // self test button
    QToolButton* selfTestBtn = nullptr;
    QMap<ScreenAreaType,QWidget *>   m_pCurrentWgt;
};

#endif // MainMonitorWgt_H
