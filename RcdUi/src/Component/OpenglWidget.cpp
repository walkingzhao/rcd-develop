#include "OpenglWidget.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <cstring>
#include <QDateTime>

#include "TGFrame.h"

#ifdef HIK_INTERFACE
#include "Component/hikvisioncamera.h"
#endif

#define  VERTEXIN       0
#define  TEXTUREIN      1

OpenGLWidget::OpenGLWidget(QWidget *parent):
    QOpenGLWidget(parent),
    m_isPlay(false),
    m_isWaitingReconn(false),
    m_pYData(nullptr,free),
    m_pUData(nullptr,free),
    m_pVData(nullptr,free),
    m_pRGBData(nullptr,free)
{
    m_pFrame = new TGFrame(this);
    m_pFrame->move(0,0);

    _label = new QLabel;
    _layoutGrid = new QGridLayout;
    _label->clear();
    _label->setStyleSheet("background-color:black; color:white;");
    _label->setScaledContents(true);
    _layoutGrid->addWidget(_label);
    _layoutGrid->setMargin(0);
    this->setLayout(_layoutGrid);

   timer_checkVideo = new QTimer(this);
   connect(timer_checkVideo, SIGNAL(timeout()), this, SLOT(slot_timer_checkVideo()));
   timer_checkVideo->start(2000);
   nowTime = QTime::currentTime();

}
void OpenGLWidget::slot_timer_checkVideo()
{    
    int elapsed = nowTime.msecsTo(QTime::currentTime());
    if((elapsed>2000)&&(m_isPlay))//2s没有收到数据，提示无视频，请连接
    {
        setDisconnectTip();
    }
}
void OpenGLWidget::setDisconnectTip()
{
    QFont font("Microsoft YaHei",18);
    _label->setPixmap(QPixmap());
    _label->setText("无视频数据\n等待连接...");
    _label->setFont(font);
    _label->setAlignment(Qt::AlignCenter);
    _label->setStyleSheet("background-color:black; color:white;");
    _label->show();

}

OpenGLWidget::~OpenGLWidget()
{
    this->makeCurrent();
    m_vertexTexture.destroy();
    if(m_pTextureY!=nullptr)
        m_pTextureY->destroy();
    if(m_pTextureU!=nullptr)
        m_pTextureU->destroy();
    if(m_pTextureV!=nullptr)
        m_pTextureV->destroy();

    this->doneCurrent();

    if(m_pTextureY!=nullptr)delete m_pTextureY;
    if(m_pTextureU!=nullptr)delete m_pTextureU;
    if(m_pTextureV!=nullptr)delete m_pTextureV;
    if(_label!=nullptr)delete _label;
//    if(timer_checkVideo->isActive())
//        timer_checkVideo->stop();
//    delete timer_checkVideo;
    // qDebug()<<"updatexzk OpenGLDestory!";

}
#ifdef HIK_INTERFACE
void OpenGLWidget::startPlay(QString &name)
{
    if(m_isPlay&&(m_cameraName == name)){
//        qDebug() << "m_isPlay :" << m_isPlay << "m_playUrl == url";
        return;
    }
    stopPlay();
    m_cameraName = name;
    if (name.contains("://")) {
        m_playUrl = name;
    } else {
        m_playUrl = HikvisionCamera::instance()->getCameraUrl(name);
    }
    qDebug()<<name<<"url:"<<m_playUrl;

    if(m_playUrl.isEmpty()){
        return;
    }
    m_isPlay = true;
    StreamThread *pStreaming = new StreamThread();
    QMetaObject::Connection conn(connect(pStreaming, SIGNAL(sglFinished()), this, SLOT(reconnect())));
    connect(pStreaming, SIGNAL(sglSyncUpdateYUV(const uchar*,const uchar*,const uchar*,uint,uint)),
            this,SLOT(syncUpdateYUV(const uchar*,const uchar*,const uchar*,uint,uint)),Qt::DirectConnection);
    connect(pStreaming, SIGNAL(sglAsyncUpdateUi()), this, SLOT(asyncUpdateUi()),Qt::QueuedConnection);
    connect(this, SIGNAL(sglResize(int,int)), pStreaming, SLOT(outputResize(int,int)),Qt::DirectConnection);
    pStreaming->setParameter(m_playUrl,conn,this->width(),this->height());
    pStreaming->startThread();
    _label->hide();
}
#else
void OpenGLWidget::startPlay(QString &url)
{
//    qDebug()<<"updatexzk 开始播放"<<m_cameraName;
    if(m_isPlay && m_playUrl == url){
        qDebug() << "m_isPlay :" << m_isPlay << "m_playUrl == url"<<(m_playUrl == url);
        return;
    }
    stopPlay();
    m_playUrl = url;

    if(url.isEmpty()){
        return;
    }

    m_isPlay = true;
    pStreaming = new StreamThread();
    QMetaObject::Connection conn(connect(pStreaming, SIGNAL(sglFinished()), this, SLOT(reconnect())));

    connect(pStreaming, SIGNAL(sglSyncUpdateRGB(uint8_t*,uint,uint)),
            this,SLOT(syncUpdateRGB(uint8_t*,uint,uint)),Qt::DirectConnection);//must directconnection

    connect(pStreaming, SIGNAL(sglAsyncUpdateUi()), this, SLOT(asyncUpdateUi()),Qt::QueuedConnection);
    connect(this, SIGNAL(sglResize(int,int)), pStreaming, SLOT(outputResize(int,int)),Qt::DirectConnection);
    pStreaming->setParameter(url,conn,this->width(),this->height());
    pStreaming->startThread();
    _label->hide();

    isVideoComingFlag = false;
    setDisconnectTip();
    nowTime=QTime::currentTime();
    qDebug()<<"updatexzk 开始播放:"<<url;
    delayTestStart=true;
}
#endif
void OpenGLWidget::stopPlay()
{
//    if(timer_checkVideo->isActive())
//        timer_checkVideo->stop();

//    qDebug()<<"updatexzk 停止播放:"<<m_cameraName;
    if(m_isPlay){
        m_isPlay = false;
        m_isWaitingReconn = false;
        emit sglResize(0,0); //发送窗口大小为0信号，播放停止。
        this->update();
        QApplication::sync();
        _label->clear();
        _label->hide();
    }
}

void OpenGLWidget::syncUpdateYUV(const uchar *Yplane,
                                 const uchar *Uplane,
                                 const uchar *Vplane,
                                 uint width,uint height)
{
    isVideoComingFlag = true;

    if(m_width != width || m_height != height ){
        m_width = width;
        m_height = height;
        m_pYData = std::unique_ptr<GLubyte,void(*)(void*)>{
            static_cast<GLubyte*>(malloc(sizeof(GLubyte)*m_width*m_height)),free
        };

        m_pUData = std::unique_ptr<GLubyte,void(*)(void*)>{
            static_cast<GLubyte*>(malloc(sizeof(GLubyte)*m_width*m_height/4)),free
        };

        m_pVData = std::unique_ptr<GLubyte,void(*)(void*)>{
            static_cast<GLubyte*>(malloc(sizeof(GLubyte)*m_width*m_height/4)),free
        };
    }
    nowTime = QTime::currentTime();
    _label->hide();
    std::memcpy(m_pYData.get(),Yplane,m_width*m_height);
    std::memcpy(m_pUData.get(),Uplane,m_width*m_height/4);
    std::memcpy(m_pVData.get(),Vplane,m_width*m_height/4);
}
#ifdef HIK_INTERFACE
void OpenGLWidget::reconnect()
{
    qDebug() << m_cameraName << "OpenGLWidget::reconnect()";
    m_isWaitingReconn = true;
    QTimer::singleShot(2000,Qt::VeryCoarseTimer,this,[this](){
        if(this->m_isWaitingReconn){
            this->m_isWaitingReconn = false;
            this->stopPlay();
            this->startPlay(m_cameraName);
        }
    });
}
#else
void OpenGLWidget::reconnect()
{
    return;
}
#endif
void OpenGLWidget::setShadowType(int type)
{
    m_pFrame->setFrameType(static_cast<TGFrame::TGFrameType>(type));
}

void OpenGLWidget::asyncUpdateUi()
{
    this->update();
}

void OpenGLWidget::syncUpdateRGB(uint8_t *rgb, uint width, uint height)
{
    if(delayTestStart==true)
    {
        qDebug()<<"updatexzk 收到第一帧数据"<<m_cameraName;
        delayTestStart=false;
    }
    if(m_width != width || m_height != height ){
        m_width = width;
        m_height = height;
        m_pRGBData = std::unique_ptr<GLubyte,void(*)(void*)>{
            static_cast<GLubyte*>(malloc(sizeof(GLubyte)*m_width*m_height*3)),free
        };
    }
    nowTime = QTime::currentTime();
    _label->hide();
    unsigned long l=m_width*m_height;
    std::memcpy(m_pRGBData.get(),rgb,l*3);
}


void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    initCoordinate();
    initShader();
    initTexture();

    glClearColor(0,0,0,0);
}

void OpenGLWidget::paintGL()
{
    if(m_isPlay && m_width != 0){
        copyTexture();
        updateRender();
    }else{
        glClearColor(0,0,0,0);
    }
}

void OpenGLWidget::resizeGL(int w,int h)
{
    m_pFrame->resize(w,h);
    if(m_isPlay)
    {
        emit sglResize(w,h);
    }
}

void OpenGLWidget::initCoordinate()
{
    static const GLfloat coordinates[]{
        //顶点坐标
        -1.0f,-1.0f,
        -1.0f,+1.0f,
        +1.0f,+1.0f,
        +1.0f,-1.0f,
        //纹理坐标
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
    };

    m_vertexTexture.create();
    m_vertexTexture.bind();
    m_vertexTexture.allocate(coordinates,sizeof(coordinates));
}

void OpenGLWidget::initShader()
{
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex,this);
    const char *vsrc =
            "attribute vec4 vertexIn;    \
            attribute vec2 textureIn;   \
    varying vec2 textureOut;    \
    void main(void)             \
    {                           \
        gl_Position = vertexIn; \
        textureOut = textureIn; \
    }";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment,this);
#ifndef HIK_INTERFACE
    const char *fsrc = " \
    varying vec2 textureOut; \
    uniform sampler2D tex_rgb; \
    void main(void) \
    { \
        gl_FragColor = texture2D(tex_rgb, textureOut); \
    }";
#else
    const char *fsrc = "varying vec2 textureOut; \
            uniform sampler2D tex_y; \
    uniform sampler2D tex_u; \
    uniform sampler2D tex_v; \
    void main(void) \
    { \
        vec3 yuv; \
        vec3 rgb; \
        yuv.x = texture2D(tex_y, textureOut).r; \
        yuv.y = texture2D(tex_u, textureOut).r - 0.5; \
        yuv.z = texture2D(tex_v, textureOut).r - 0.5; \
        rgb = mat3( 1,       1,         1, \
                    0,       -0.39465,  2.03211, \
                    1.13983, -0.58060,  0) * yuv; \
        gl_FragColor = vec4(rgb, 1); \
    }";
#endif
    fshader->compileSourceCode(fsrc);

    QOpenGLShaderProgram *pShaderProgram = new QOpenGLShaderProgram(this);
    pShaderProgram->addShader(vshader);
    pShaderProgram->addShader(fshader);
    pShaderProgram->bindAttributeLocation("vertexIn",VERTEXIN);
    pShaderProgram->bindAttributeLocation("textureIn",TEXTUREIN);
    pShaderProgram->link();
    pShaderProgram->bind();
    pShaderProgram->enableAttributeArray(VERTEXIN);
    pShaderProgram->enableAttributeArray(TEXTUREIN);
    pShaderProgram->setAttributeBuffer(VERTEXIN,GL_FLOAT,0,2,2*sizeof(GLfloat));
    pShaderProgram->setAttributeBuffer(TEXTUREIN,GL_FLOAT,8*sizeof(GLfloat),2,2*sizeof(GLfloat));

#ifdef HIK_INTERFACE
    m_pTextureUniformY = pShaderProgram->uniformLocation("tex_y");
    m_pTextureUniformU = pShaderProgram->uniformLocation("tex_u");
    m_pTextureUniformV = pShaderProgram->uniformLocation("tex_v");
#else
    m_pTextureUniformRGB = pShaderProgram->uniformLocation("tex_rgb");
#endif
}
#ifdef HIK_INTERFACE
void OpenGLWidget::initTexture()
{
    m_pTextureY = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_pTextureU = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_pTextureV = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_pTextureY->create();
    m_pTextureU->create();
    m_pTextureV->create();

    glBindTexture(GL_TEXTURE_2D,m_pTextureY->textureId()); //绑定y分量纹理对象id到激活的纹理单元
    //设置纹理参数
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D,m_pTextureU->textureId()); //绑定U分量纹理对象id到激活的纹理单元
    //设置纹理参数
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D,m_pTextureV->textureId()); //绑定V分量纹理对象id到激活的纹理单元
    //设置纹理参数
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
void OpenGLWidget::copyTexture()
{
    glActiveTexture(GL_TEXTURE0);  //激活纹理单元GL_TEXTURE0
    glBindTexture(GL_TEXTURE_2D,m_pTextureY->textureId()); //绑定y分量纹理对象id到激活的纹理单元
    //拷贝Y分量纹理数据到纹理单元
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,m_width,m_height,0,GL_RED,GL_UNSIGNED_BYTE,m_pYData.get());
    //指定y纹理要使用新值
    glUniform1i(m_pTextureUniformY, 0);

    glActiveTexture(GL_TEXTURE1); //激活纹理单元GL_TEXTURE1
    glBindTexture(GL_TEXTURE_2D,m_pTextureU->textureId()); //绑定U分量纹理对象id到激活的纹理单元
    //拷贝U分量纹理数据到纹理单元
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,m_width >> 1, m_height >> 1,0,GL_RED,GL_UNSIGNED_BYTE,m_pUData.get());
    //指定u纹理要使用新值
    glUniform1i(m_pTextureUniformU, 1);


    glActiveTexture(GL_TEXTURE2); //激活纹理单元GL_TEXTURE2
    glBindTexture(GL_TEXTURE_2D,m_pTextureV->textureId());//绑定V分量纹理对象id到激活的纹理单元
    //拷贝V分量纹理数据到纹理单元
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width >> 1, m_height >> 1, 0, GL_RED, GL_UNSIGNED_BYTE, m_pVData.get());
    //指定v纹理要使用新值
    glUniform1i(m_pTextureUniformV, 2);
}
#else
void OpenGLWidget::initTexture()
{

    m_pTextureRGB = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_pTextureRGB->create();

    glBindTexture(GL_TEXTURE_2D,m_pTextureRGB->textureId()); //绑定R分量纹理对象id到激活的纹理单元
    //设置纹理参数
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
void OpenGLWidget::copyTexture()
{
    glActiveTexture(GL_TEXTURE0);  //激活纹理单元GL_TEXTURE0
    glBindTexture(GL_TEXTURE_2D,m_pTextureRGB->textureId()); //绑定R分量纹理对象id到激活的纹理单元
    //拷贝R分量纹理数据到纹理单元
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,m_pRGBData.get());
    //指定R纹理要使用新值
    glUniform1i(m_pTextureUniformRGB, 0);
}
#endif
void OpenGLWidget::updateRender()
{
    //使用顶点数组方式绘制图形
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void OpenGLWidget::hideLabel()
{
    _label->hide();
}
void OpenGLWidget::showLabel(QString src)
{
    if(src!="")
    {
        QImage image;
        image.load(src);
        _label->setPixmap(QPixmap::fromImage(image));
    }
    _label->show();
}

void OpenGLWidget::setLabel(QString src)
{
    QImage image;
    image.load(src);
    _label->setPixmap(QPixmap::fromImage(image));
}
