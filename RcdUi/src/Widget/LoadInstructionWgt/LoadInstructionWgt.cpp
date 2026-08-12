#include "LoadInstructionWgt.h"
#include "ui_LoadInstructionWgt.h"

LoadInstructionWgt* LoadInstructionWgt::s_pInstance = nullptr; //初始化静态数据成员
LoadInstructionWgt::LoadInstructionWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::LoadInstructionWgt)
{
    ui->setupUi(this);
    // 创建控制层
    m_pCL = new LoadInstructionCL(this);
    m_pCL->doInit();
    this->setCL(m_pCL);
    // 创建数据层
    m_pModel = new LoadInstructionModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);
    initUi();

    ui->Title->setFrameType(TGFrame::InfoFrameRightPage2No6);
    ui->Title->setTitleString(QString::fromUtf8("装载指令"));


    QHBoxLayout *pHLayout = new QHBoxLayout();
    pHLayout->addStretch(2);
    pHLayout->addWidget(ui->frame_drive,10);
    pHLayout->addStretch(2);
    pHLayout->addWidget(ui->frame_re_dock,5);
    pHLayout->addStretch(2);

    QVBoxLayout* pVLayout = new QVBoxLayout(ui->Title);
    pVLayout->addStretch(2);
    pVLayout->addLayout(pHLayout,10);
    pVLayout->addStretch(1);





    pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(ui->Title);
    setLayout(pVLayout);


    connect(&tickTimer,SIGNAL(timeout()),this ,SLOT(tickTimerOut()));
    tickTimer.start(200);

}

LoadInstructionWgt::~LoadInstructionWgt()
{
    delete ui;
}

void LoadInstructionWgt::tickTimerOut()
{
    //关闭所有显示
    setLoadValue(Load_instruction::re_dock,false);
    setLoadValue(Load_instruction::drive_in,false);
    setLoadValue(Load_instruction::loading,false);
    setLoadValue(Load_instruction::drive_away,false);

    //闪烁显示提示图标
    static bool flag=true;
    if(m_pModel->m_TaskLoadInfo.workStatus==0x04)//驶入停靠
    {
        // --> BEGIN modify by ZJZ, 2022/3/24
#if 0
        if(m_pModel->m_TaskLoadInfo.operType==0x07)
        {
        }else
        {
            setLoadValue(Load_instruction::drive_in,flag);
        }
#endif
        setLoadValue(Load_instruction::drive_in,flag);
        // <-- END
    }else if(m_pModel->m_TaskLoadInfo.workStatus==0x06)//装载中
    {
        setLoadValue(Load_instruction::loading,flag);
    }else if((m_pModel->m_TaskLoadInfo.workStatus==0x07)//装载完成
        ||(m_pModel->m_TaskLoadInfo.workStatus==0x09))//卸载完成，请驶离
    {
        setLoadValue(Load_instruction::drive_away,flag);
    }else if(m_pModel->m_TaskLoadInfo.workStatus==0x0d)
    {
        // --> BEGIN deleted by ZJZ, 2022/3/24
#if 0
        if(m_pModel->m_TaskLoadInfo.operType==0x07)//重新停靠
        {
            setLoadValue(Load_instruction::re_dock,flag);
        }
#endif
        // <-- END
    }
    // --> BEGIN added by ZJZ, 2022/3/24
    else if(m_pModel->m_TaskLoadInfo.workStatus==0x0e)
    {
        setLoadValue(Load_instruction::re_dock,flag);
    }
    // <-- END
    flag=!flag;

    this->update();
}

LoadInstructionWgt *LoadInstructionWgt::GetInstance()
{
    if(s_pInstance == nullptr) {
        s_pInstance = new LoadInstructionWgt();
    }
    return s_pInstance;
}
void LoadInstructionWgt::initUi()
{
    ui->label_drive_in->setPixmap(QPixmap(":/resource/icon/drive_in_black.png"));
    ui->label_loading->setPixmap(QPixmap(":/resource/icon/loading_black.png"));


    ui->label_drive_away->setPixmap(QPixmap(":/resource/icon/drive_away_black.png"));
    ui->label_re_dock->setPixmap(QPixmap(":/resource/icon/re_dock_black.png"));
}
void LoadInstructionWgt::setLoadValue(Load_instruction flag,bool checked)
{
    switch (flag) {
    case Load_instruction::drive_in:{
        ui->label_drive_in->setPixmap(QPixmap(QString(":/resource/icon/drive_in_%1.png")
                                              .arg(checked ? "highlight":"black")));
    }
        break;
    case Load_instruction::loading:{
        ui->label_loading->setPixmap(QPixmap(QString(":/resource/icon/loading_%1.png")
                                             .arg(checked ? "highlight":"black")));
    }
        break;
    case Load_instruction::drive_away:{
        ui->label_drive_away->setPixmap(QPixmap(QString(":/resource/icon/drive_away_%1.png")
                                                .arg(checked ? "highlight":"black")));
    }
        break;
    case Load_instruction::re_dock:{
        ui->label_re_dock->setPixmap(QPixmap(QString(":/resource/icon/re_dock_%1.png")
                                             .arg(checked ? "highlight":"black")));
    }
        break;
    default:
        break;
    }
}
