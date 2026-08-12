#include "takeoverinfomodel.h"

TakeOverInfoModel::TakeOverInfoModel(QObject *parent) : IModel(parent)
{

}

void TakeOverInfoModel::setAllInfo(QString dest,QString curName,QString orgDest)
{
//    m_destName = dest;
    m_curName = curName;
    m_orgDestName = orgDest;
    emit sendModelUpdate(ModelCmdType::MC_UpdateAll);
}

void TakeOverInfoModel::setTargetInfo(QString dest)
{
    m_destName = dest;
    emit sendModelUpdate(ModelCmdType::MC_UpdateAll);
}
void TakeOverInfoModel::setLoadStatus(uint8_t loadStatus)
{
    m_loadStatus = loadStatus;
    emit sendModelUpdate(ModelCmdType::MC_UpdateAll);
}
