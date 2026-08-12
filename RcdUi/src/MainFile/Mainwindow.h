#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>

class LeftWgt1;
class MidWgt;
class RightWgt1;
class LeftWgt;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void switchLayout(int layoutType);
    void addShowWidget(int type ,QWidget *pWgt);
    void showAll();

private:
    Ui::MainWindow *ui;
    LeftWgt1         *m_pLeftWgt=nullptr;
    LeftWgt          *m_pLeftWgt_Monitor = nullptr;
    MidWgt          *m_pMidWgt=nullptr;
    RightWgt1        *m_pRightWgt=nullptr;
};

#endif // MAINWINDOW_H
