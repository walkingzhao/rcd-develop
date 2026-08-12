#ifndef BASEFORM_H
#define BASEFORM_H

#include <QWidget>

namespace Ui {
class baseForm;
}

class baseForm : public QWidget
{
    Q_OBJECT

public:
    explicit baseForm(QWidget *parent = nullptr);
    ~baseForm();
    virtual void paintEvent(QPaintEvent *) override;
    void drawTip(QPainter &painter);
    void setPenColor(QColor color);
private:
    Ui::baseForm *ui;
    QString        m_titleStr;
    QColor       m_penColor;
};

#endif // BASEFORM_H
