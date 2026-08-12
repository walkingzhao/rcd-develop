#include "FastStopModel.h"

FastStopModel::FastStopModel(QObject *parent) : IModel(parent)
{
    memset(&m_TaskLoadInfo,0,sizeof(m_TaskLoadInfo));
}
