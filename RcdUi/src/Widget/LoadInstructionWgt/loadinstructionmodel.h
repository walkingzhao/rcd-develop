#ifndef LOADINSTRUCTIONMODEL_H
#define LOADINSTRUCTIONMODEL_H
#include "Interface/IModel.h"

#include "public/fbsstructure.h"

class LoadInstructionModel : public IModel
{
    Q_OBJECT
public:
    explicit LoadInstructionModel(QObject *parent = nullptr);
    ReportRoadTaskInfoST m_TaskLoadInfo;
};

#endif // LOADINSTRUCTIONMODEL_H
