#include "infomodel.h"

InfoModel::InfoModel(QObject *parent) : IModel(parent)
{

}
void InfoModel::insertMsg(QString msg)
{
    newMsg = msg;
    emit sendModelUpdate(InfoModel::MC_InsertMsg);
}
