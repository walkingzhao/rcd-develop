#include "MainMonitorModel.h"
#include <QSettings>
#include <QtDebug>
#include "public/jsonMethord.h"
#include "System.h"
#include <QApplication>
MainMonitorModel::MainMonitorModel(QObject *parent) : IModel(parent),
    m_showVehicle(6,QLatin1String("")),
    m_select(-1),
    m_pageIndex(0),
    m_maxPage(1)
{

    VehicleInfo vehicle;
    QVariant data = jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","Vehicle");
    if(data.toList().isEmpty()){
        return;
    }
    QMap<QString, QVariant> ::Iterator it;
    QMap<QString, QVariant> map = data.toList().at(0).toMap();
    for(it=map.begin();it!=map.end();it++){
        vehicle.url = it.value().toList().at(0).toMap().value("Forward").toString();
        vehicle.name = it.value().toList().at(0).toMap().value("Name").toString();
        m_vehicleList.append(it.key());
        m_vehicleMap[it.key()] = vehicle;
    }
    System::getInstance()->setCurrentImeiList(m_vehicleList);//imeilist



}

bool MainMonitorModel::addVehicle(VehicleInfo &vehicle)
{
    bool ret = false;
    auto iter = m_vehicleMap.find(vehicle.imei);
    if(iter == m_vehicleMap.end()){
        m_vehicleList.append(vehicle.imei);
        ret = true;
    }
    m_vehicleMap[vehicle.imei] = vehicle;
    return ret;
}

bool MainMonitorModel::removeVehicle(QString &imei)
{
    m_vehicleList.removeOne(imei);
    m_vehicleMap.remove(imei);
    return true;
}

