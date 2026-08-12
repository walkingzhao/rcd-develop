#include <QCoreApplication>
#include "control.h"
#include <QtDebug>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    control app;
    return a.exec();
    app.deleteLater();
}
