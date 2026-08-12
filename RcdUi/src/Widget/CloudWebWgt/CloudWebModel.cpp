#include "CloudWebModel.h"
#include <QSettings>
#include "public/jsonMethord.h"
#include <QApplication>
CloudWebModel::CloudWebModel(QObject *parent) : IModel(parent)
{
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Url");
    if(!data.toList().isEmpty()){
        m_url = data.toList().at(0).toMap()["MapUrl"].toString();
    }
}

void CloudWebModel::setUrl(QString &url)
{
    m_url = url;
    emit sendModelUpdate(MC_LoadUrl);
}
void CloudWebModel::setCurrentMode(QString &data)
{
    _mapMode = data;
    emit sendModelUpdate(MC_SwitchMap);
}
