#ifndef MSGMODEL_H
#define MSGMODEL_H
#include <QMap>
#include <QVector>
#include "Interface/IModel.h"

class msgModel : public IModel
{
    Q_OBJECT
public:
    explicit msgModel(QObject *parent = nullptr);

};
#endif // MSGMODEL_H
