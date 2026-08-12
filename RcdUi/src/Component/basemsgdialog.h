#ifndef BASEMSGDIALOG_H
#define BASEMSGDIALOG_H

#include <QDialog>
#include <QPainter>
namespace Ui {
class baseMsgDialog;
}

class baseMsgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit baseMsgDialog(QWidget *parent = nullptr);
    ~baseMsgDialog();
protected:
    void paintEvent(QPaintEvent *);
    void drawTip(QPainter &painter);
private:
    Ui::baseMsgDialog *ui;
     QString        m_titleStr;
};

#endif // BASEMSGDIALOG_H
