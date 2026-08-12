#ifndef OpenGLWidget_H
#define OpenGLWidget_H
//#define USE_YUV
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTime>
#include "StreamThread.h"

/************车道线***谭创****/
#include <QGL>
#include <QGLFormat>
#include <QSurfaceFormat>
#include  <qmath.h>
#include <vector>
#include <QPoint>
#include <QLabel>
#include <QGridLayout>
/************车道线***谭创****/
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QTimer)

class TGFrame;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent =0);
    ~OpenGLWidget();

    void     startPlay(QString &url);
    void     stopPlay();
    void     setShadowType(int);
    void     hideLabel();//隐藏图片
    void     showLabel(QString str=""); // 显示图片
    void     setLabel(QString src);     // 显示图片
    /*******************车道线*****************谭创******/

    /********************************车道线*******************/
public slots:
    void syncUpdateYUV(const uchar *Yplane,
                           const uchar *Uplane,
                           const uchar *Vplane,
                           uint width,uint height);
    void asyncUpdateUi();
    //    void asyncUpdateUi(QPixmap img);
    void syncUpdateRGB(uint8_t* rgb,
                       uint width,uint height);
    void reconnect();

signals:

    void sglResize(int w,int h);
    void signalPixmap(QPixmap img);

protected:

    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w,int h) Q_DECL_OVERRIDE;
private:

    void initCoordinate();
    void initShader();
    void initTexture();
    void copyTexture();
    void updateRender();
    void setDisconnectTip();

private:
    StreamThread *pStreaming = nullptr;

    TGFrame*       m_pFrame;
    QString        m_playUrl;
    QString        m_cameraName;
    bool           m_isWaitingReconn;
    QOpenGLBuffer m_vertexTexture;

    GLuint m_pTextureUniformY;
    GLuint m_pTextureUniformU;
    GLuint m_pTextureUniformV; //Shader程序接口
    GLuint m_pTextureUniformRGB;

    QOpenGLTexture *m_pTextureY = nullptr;
    QOpenGLTexture *m_pTextureU = nullptr;
    QOpenGLTexture *m_pTextureV = nullptr;
    QOpenGLTexture *m_pTextureRGB= nullptr;

    GLuint m_width = 0;
    GLuint m_height = 0;

    std::unique_ptr<GLubyte,void(*)(void*)> m_pYData;
    std::unique_ptr<GLubyte,void(*)(void*)> m_pUData;
    std::unique_ptr<GLubyte,void(*)(void*)> m_pVData;
    std::unique_ptr<GLubyte,void(*)(void*)> m_pRGBData;
    QLabel *_label = nullptr;
    QGridLayout *_layoutGrid = nullptr;

    QTimer* timer_checkVideo = nullptr;
    bool isVideoComingFlag = false;
    bool delayTestStart=false;
    QTime nowTime;
public:
    bool           m_isPlay ;

private slots:
    void slot_timer_checkVideo();
};

#endif // OpenGLWidget_H
