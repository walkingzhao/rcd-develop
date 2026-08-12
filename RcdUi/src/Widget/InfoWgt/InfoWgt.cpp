#include "InfoWgt.h"
#include "ui_InfoWgt.h"
#include <QDebug>
#include <iostream>

#include "public/jsonMethord.h"
#include "Protocol/warnning.h"

InfoWgt::InfoWgt(QWidget *parent) :
    IFunWidget(parent),
    ui(new Ui::InfoWgt){
    ui->setupUi(this);
    m_pCL = new InfoCL();
    m_pCL->doInit();
    this->setCL(m_pCL);

    m_pModel = new InfoModel();
    this->setModel(m_pModel);
    m_pCL->setModel(m_pModel);

//    _testTimer = new QTimer;
//    connect(_testTimer, SIGNAL(timeout()),this, SLOT(testData()));
//    _testTimer->start(3000);

    //layout
    ui->Title->setFrameType(TGFrame::InfoFrameRightPage2No9);
    ui->Title->setTitleString(QString::fromUtf8("接管信息"));

    leftWidget = left_widget();
    rightWidget = right_widget();

    pHLayout = new QHBoxLayout();
    pHLayout->addStretch(1);
    pHLayout->addWidget(leftWidget,15);
    pHLayout->addSpacing(2);
    pHLayout->addWidget(rightWidget,15);
    pHLayout->addStretch(1);

    pVLayout = new QVBoxLayout(ui->Title);
    pVLayout->addStretch(2);
    pVLayout->addLayout(pHLayout,10);
    pVLayout->addStretch(1);

//    pVLayout = new QVBoxLayout(this);
//    pVLayout->addWidget(ui->Title);
    setLayout(pVLayout);
}

InfoWgt::~InfoWgt(){
    delete ui;
}

QWidget* InfoWgt::left_widget() {
    QLabel* title = new QLabel(" 特殊故障显示", this);
    title->setStyleSheet("color:white; font:18px 'Source Han Sans CN';");

    QHBoxLayout* hlayout[6];
    for(int i=0;i<6;++i){
        faultIcon[i] = new QLabel(this);
        faultIcon[i]->resize(14,14);

        faultText[i] = new QLabel(this);
        faultText[i]->setStyleSheet("color:rgb(230, 230, 230); font:14px 'Source Han Sans CN';");

        hlayout[i] = new QHBoxLayout();
        hlayout[i]->addSpacing(4);
        hlayout[i]->addWidget(faultIcon[i]);
        hlayout[i]->addSpacing(2);
        hlayout[i]->addWidget(faultText[i]);
        hlayout[i]->addStretch();
    }

    QWidget* widget = new QWidget(this);
    widget->setStyleSheet("background-color: rgb(32, 74, 135); border-radius:10px;");

    QVBoxLayout* pleft = new QVBoxLayout();
    pleft->addSpacing(3);
    pleft->addWidget(title);
    pleft->setSpacing(5);
    for(int i=0;i<6;++i){
        pleft->addLayout(hlayout[i]);
    }
    pleft->addStretch();
    widget->setLayout(pleft);
    return  widget;
}

QWidget* InfoWgt::right_widget(){
    rightWidgetTitle = new QLabel(" 其他故障显示", this);
    rightWidgetTitle->setStyleSheet("color:white; font:18px 'Source Han Sans CN';");

    ui->messageBrowser->setStyleSheet("color:rgb(230, 230, 230); font:14px 'Source Han Sans CN';");

    QWidget* widget = new QWidget(this);
    widget->setStyleSheet("background-color: rgb(32, 74, 135); border-radius:10px;");

    QVBoxLayout* pright = new QVBoxLayout();
    pright->addWidget(rightWidgetTitle);
    pright->setSpacing(0);
    pright->addWidget(ui->messageBrowser);
    widget->setLayout(pright);
    return  widget;
}

void InfoWgt::read_fault_data(){
    QVariant data = jsonMethord::getInstance()->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","fault");
    if(data.toList().isEmpty()) return;

    int iFaultArray[6] = {0};
    for(int i=0; i<6; ++i){
        QString str = QString("V%1").arg(i+1);
        iFaultArray[i] = data.toList()[0].toMap().value(str).toInt();
        if(warningMap.find(iFaultArray[i]) == warningMap.end()){
            QImage img(":/resource/icon/general_info.png");
            faultIcon[i]->setPixmap(QPixmap::fromImage(img));

            str = QString("error number: %1").arg(iFaultArray[i]);
            faultText[i]->setText(str);
            led_status[i] = -1;
        }else{
            QImage img(":/resource/icon/green_info.png");
            faultIcon[i]->setPixmap(QPixmap::fromImage(img));

            str = warningMap.find(iFaultArray[i]).value().first.data();
            faultText[i]->setText(str);
            led_status[i] = 0;
        }
    }    

    blinkFaultTimer = new QTimer(this);
    connect(blinkFaultTimer, SIGNAL(timeout()), this, SLOT(on_blinkFaultTimer()));
    blinkFaultTimer->start(500);
}

void InfoWgt::on_blinkFaultTimer(){
    for(int i=0; i<6; ++i) {
        if(led_status[i] == 1){
            numTick[i]++;
            numTick[i]%=2;
            if(numTick[i] == 0){
                QImage img(":/resource/icon/green_info.png");
                faultIcon[i]->setPixmap(QPixmap::fromImage(img));
            }else{
                QImage img(":/resource/icon/red_info.png");
                faultIcon[i]->setPixmap(QPixmap::fromImage(img));
            }
        }else if(led_status[i] == 0){
            QImage img(":/resource/icon/green_info.png");
            faultIcon[i]->setPixmap(QPixmap::fromImage(img));
        }
    }
}

void InfoWgt::insertMessage(const QString &message){
    QString showStr = "";
    if(this->messageType == 0){//故障信息
//        qDebug() << "type=fault";
//        cout << "type=0" << endl;
        //fault come
        QString msg_fault_come = message;
        msg_fault_come = msg_fault_come.section(']', 1, 1);
        if(msg_fault_come != ""){
            for(int i=0; i<6; ++i){
                if(faultText[i]->text()==msg_fault_come && led_status[i]==0){
                    led_status[i] = 1;
                    return;
                }
            }
            showStr = QString("<img src=\"%1\"width=\"14\" height=\"14\"/> ").arg(":/resource/icon/general_info.png");
            ui->messageBrowser->append(showStr + message);
        }

        //fault leave
        QString msg_fault_leave = "";
        if("已消除" == message.right(3)){
            msg_fault_leave = message;
            //msg_fault_clear = msg_fault_clear.section("  ", 1, 1);
            msg_fault_leave.remove(QRegExp("\\s"));
            msg_fault_leave.remove(0, 8);
            msg_fault_leave.chop(3);
            for(int i=0; i<6; ++i){
                if(faultText[i]->text() == msg_fault_leave){
                    led_status[i] = 0;
                    return;
                }
            }
        }
    }else if(this->messageType==1){//系统信息
//        qDebug() << "type=system";
//        cout << "type=1" << endl;
        showStr=QString("<img src=\"%1\"width=\"14\" height=\"14\"/>").arg(":/resource/icon/blue_info.png");
        ui->messageBrowser->append(showStr + message);
    }
}

void InfoWgt::setType(int messageType){
    this->messageType = messageType;
    if(messageType==0){//故障信息
        ui->Title->setTitleString(QString::fromUtf8("故障信息"));

        //read local fault message
        for(int i=0; i<6; ++i) {
            numTick[i] = 0;
            led_status[i] = -1;
        }
        read_fault_data();
    }else if(messageType==1){//系统信息
        ui->Title->setTitleString(QString::fromUtf8("系统信息"));
        leftWidget->hide();
        rightWidgetTitle->hide();
    }
}

void InfoWgt::testData(){
    insertMessage("hello baby");
}

void InfoWgt::onClDataCome(int cmd, QVariant data){
    data.isValid();
    switch (cmd) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
}

void InfoWgt::onModelUpdate(int cmd){
    InfoModel::ModelCmdType tCmd = static_cast<InfoModel::ModelCmdType>(cmd);
    switch (tCmd) {
    case InfoModel::MC_InsertMsg:
        insertMessage(m_pModel->newMsg);
        break;
    default:
        break;
    }
}
