#ifndef MainCameraTipModel_H
#define MainCameraTipModel_H
#include "Interface/IModel.h"

#include "public/fbsstructure.h"

class MainCameraTipModel : public IModel
{
    Q_OBJECT
public:
    explicit MainCameraTipModel(QObject *parent = nullptr);
    ReportRoadTaskInfoST m_TaskLoadInfo;
};

#endif // MainCameraTipModel_H
