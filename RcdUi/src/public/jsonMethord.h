#ifndef JSONMETHORD_H
#define JSONMETHORD_H

#include <QObject>
#include <mutex>
#include <QFile>
#include <QJsonArray>
#include <QMap>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
class jsonMethord : public QObject
{
    Q_OBJECT
private:
    explicit jsonMethord(QObject *parent = nullptr);
    jsonMethord & operator=(const jsonMethord & ) = delete;
    jsonMethord(const jsonMethord &) = delete;
    ~jsonMethord();
public:
    static jsonMethord* getInstance(){
        if (P_jsonMethord == nullptr)
        {
            std::lock_guard<std::mutex> lgd(_mutex);
            if (P_jsonMethord == nullptr)
            {
                P_jsonMethord = new jsonMethord;
            }
        }
        return P_jsonMethord;
    }
    static void delInstance()
    {
        std::lock_guard<std::mutex> lgd(_mutex);
        if (P_jsonMethord)
        {
            delete P_jsonMethord;
            P_jsonMethord = nullptr;
        }
    }
    QVariant readJson(QString jsonPath,const QString &key);
signals:

private:
    static jsonMethord * P_jsonMethord;
    static std::mutex _mutex;
};

#endif // JSONMETHORD_H
