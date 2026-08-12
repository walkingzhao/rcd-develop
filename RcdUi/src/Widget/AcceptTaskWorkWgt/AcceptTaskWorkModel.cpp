#include "AcceptTaskWorkModel.h"

AcceptTaskWorkModel::AcceptTaskWorkModel(QObject *parent) : IModel(parent)
{
    m_dest.clear();
    m_taskId=0;
}

void AcceptTaskWorkModel::setDest(QString &dest,unsigned short &taskId)
{
    m_dest = dest;
    m_taskId = taskId;
    emit sendModelUpdate(MC_destStr);
}
