#include "jsonMethord.h"

jsonMethord* jsonMethord::P_jsonMethord = nullptr;
std::mutex jsonMethord::_mutex ;
jsonMethord::jsonMethord(QObject *parent) : QObject(parent)
{

}
jsonMethord::~jsonMethord()
{
    delInstance();
}
QVariant jsonMethord::readJson(QString jsonPath,const QString &key)
{
    /*解析json文件*/
    QFile file(jsonPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析配置文件json文件错误！")<<parseJsonErr.errorString();
        return QVariant();
    }
    QJsonObject jsonObject = document.object();
    return jsonObject.toVariantMap().value(key);
}
