#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "gifwidget.h"
#include <QtDebug>
class control : public QObject
{
    Q_OBJECT
public:
    explicit control(QObject *parent = nullptr);
    ~control();
    void run();
signals:

private:
    QList<GifWidget*> _listGifWidget ;
};

#endif // CONTROL_H
