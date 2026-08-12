#include "TaskWorkChangeModel.h"

TaskWorkChangeModel::TaskWorkChangeModel(QObject *parent) : IModel(parent)
{
    m_url = "https://www.baidu.com";
}

void TaskWorkChangeModel::setUrl(QString &url)
{
    m_url = url;
    emit sendModelUpdate(MC_LoadUrl);
}
