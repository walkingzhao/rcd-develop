#ifndef BTNFORM_H
#define BTNFORM_H

#include <QPushButton>
class btnForm : public QPushButton
{
public:
    btnForm();
    void setTexts( QString str){
        this->setText(str);
    }
protected:

    virtual void paintEvent(QPaintEvent *) override;
    void drawTip(QPainter &painter);

private:
    QString        m_titleStr;
};

#endif // BTNFORM_H
