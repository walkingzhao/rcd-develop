#include "control.h"
#include <QScreen>
#include <QApplication>
control::control(QObject *parent) : QObject(parent)
{
    run();
}
control::~control()
{
    for(auto ch : _listGifWidget) {
        ch->slotRecord(1);
        ch->deleteLater();
    }
}
void control::run()
{
    QList<QScreen *> allScreen =  QGuiApplication::screens();

    for (int i=0;i<allScreen.count();i++) {
        GifWidget *p_GifWidget = new GifWidget(QString("%1").arg(i));
        p_GifWidget->setGeometry(allScreen[i]->geometry());
        p_GifWidget->setGifRect();
        //        p_GifWidget->hide();
        _listGifWidget.push_back(p_GifWidget);
        p_GifWidget->slotRecord(0);
        qDebug()<<allScreen.at(i)->name()<<"-------------------------";

    }
}
