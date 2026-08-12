#ifndef FastStopModel_H
#define FastStopModel_H
#include "Interface/IModel.h"

#include "public/fbsstructure.h"

class FastStopModel : public IModel
{
    Q_OBJECT
public:
    explicit FastStopModel(QObject *parent = nullptr);
    ReportRoadTaskInfoST m_TaskLoadInfo;
};

#endif // FastStopModel_H
