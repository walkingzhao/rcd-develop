#include "CompleteOperStartModel.h"

CompleteOperStartModel::CompleteOperStartModel(QObject *parent) : IModel(parent)
{
    memset(&m_selfState,0,sizeof(m_selfState));
}

void CompleteOperStartModel::updateState(SelfCheckStatusST st)
{
    memcpy(&m_selfState,&st,sizeof(st));
    emit sendModelUpdate(MC_Update);
}
