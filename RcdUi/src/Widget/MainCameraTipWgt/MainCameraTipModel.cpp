#include "MainCameraTipModel.h"

MainCameraTipModel::MainCameraTipModel(QObject *parent) : IModel(parent)
{
    memset(&m_TaskLoadInfo,0,sizeof(m_TaskLoadInfo));
}
