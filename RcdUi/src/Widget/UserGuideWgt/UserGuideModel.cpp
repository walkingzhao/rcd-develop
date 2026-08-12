#include "UserGuideModel.h"

UserGuideModel::UserGuideModel(QObject *parent) : IModel(parent)
{
    m_url = "https://www.baidu.com";
}

void UserGuideModel::setUrl(QString &url)
{
    m_url = url;
    emit sendModelUpdate(MC_LoadUrl);
}
