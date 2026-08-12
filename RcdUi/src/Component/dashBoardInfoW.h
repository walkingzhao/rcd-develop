#ifndef DASHBOARDINFOW_H
#define DASHBOARDINFOW_H

#include <QWidget>

namespace Ui {
class dashBoardInfoW;
}

class dashBoardInfoW : public QWidget
{
    Q_OBJECT

public:
    explicit dashBoardInfoW(QWidget *parent = nullptr);
    ~dashBoardInfoW();

private:
    Ui::dashBoardInfoW *ui;
};

#endif // DASHBOARDINFOW_H
