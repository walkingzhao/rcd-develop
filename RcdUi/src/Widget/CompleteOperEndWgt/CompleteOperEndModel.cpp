#include "CompleteOperEndModel.h"
CompleteOperEndModel::CompleteOperEndModel(QObject *parent) : IModel(parent)
{

}

void CompleteOperEndModel::updateSelfState(SelfCheckStatusST selfState)
{
    memcpy(&m_selfState,&selfState,sizeof(selfState));
    emit sendModelUpdate(MC_UpdateSelf);
}

