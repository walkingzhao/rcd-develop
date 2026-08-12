#ifndef BUTTONFORM_H
#define BUTTONFORM_H

#include <QWidget>

namespace Ui {
class buttonForm;
}

class buttonForm : public QWidget
{
    Q_OBJECT

public:
    explicit buttonForm(QWidget *parent = nullptr);
    ~buttonForm();
    virtual void paintEvent(QPaintEvent *) override;
    void drawTip(QPainter &painter);
private:
    Ui::buttonForm *ui;
    QString        m_titleStr;
};

#endif // BUTTONFORM_H
