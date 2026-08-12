#ifndef CloudWebWgt_H
#define CloudWebWgt_H

#include <QResizeEvent>
#include "Interface/IFunWidget.h"
#include "CloudWebCL.h"
#include "CloudWebModel.h"
#include <QTimer>
namespace Ui {
class CloudWebWgt;
}

class WebEngine;

class CloudWebWgt : public IFunWidget
{
    Q_OBJECT

public:
    explicit CloudWebWgt(QWidget *parent = nullptr);
    ~CloudWebWgt() override;

    static CloudWebWgt* GetInstance();
    virtual bool isQuit() override;
    virtual void initWidget() override;
    virtual void updateWidget() override;
    void setFrameType(int small);

protected:

    virtual void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

public slots:

    virtual void onClDataCome(int cmd, QVariant data = INT_INVALID) override;
    virtual void onModelUpdate(int cmd) override;

private slots:
    void slotUpdateMap();
    void slotLoadFinished(bool ret);

private:
    Ui::CloudWebWgt *ui;
    static CloudWebWgt        *s_pInstance;
    CloudWebCL                *m_pCL;
    CloudWebModel             *m_pModel;
    WebEngine                 *m_pWeb;
    int smallMapType;//0大地图 1小地图
    int _mapId = 0;
    QTimer _timerSwitchMap;
    bool loadMapResult = false;
};

#endif // CloudWebWgt_H
