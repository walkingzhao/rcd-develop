#ifndef STREAMTHREAD_H
#define STREAMTHREAD_H

#include <QObject>
#include <QMutex>
#include <QPixmap>
#include <memory>
#ifdef HIK_INTERFACE
extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/pixfmt.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}
class FfmpegRegister
{
public:
    explicit FfmpegRegister();
    ~FfmpegRegister();
};
#endif
class StreamThread : public QObject
{
    Q_OBJECT
public:
    explicit StreamThread(QObject *parent = nullptr);
    ~StreamThread();

    void stopThread();
#ifdef HIK_INTERFACE
    bool openStream();
#endif
    void setParameter(QString &url,QMetaObject::Connection &connection,int w = 0,int h = 0);
    void startThread();  //执行后线程结束会自动释放内存

    static int Video_Callback(void* opaque, void*frame, int*size, long long stamp, int picfmt, int width, int height, int index);
    static void msgCallback(int what, int arg1, int arg2, void *extra, void *player_str);
    void syncUpdateRGB(uint8_t* rgb,
                       uint width,uint height);
    void syncUpdateYUV(uint8_t* y,uint8_t*u,uint8_t *v, uint width, uint height);


signals:
    void sglFinished();
    void sglAsyncUpdateUi(QPixmap img);
    void sglAsyncUpdateUi();
    /// Notifies the UI of the negotiated source frame rate so presentation can be paced to match.
    void sglVideoInfo(double fps);
    void sglSyncUpdateYUV(const uchar *Yplane,
                          const uchar *Uplane,
                          const uchar *Vplane,
                          uint width,uint height);
    void sglSyncUpdateRGB(uint8_t* rgb,
                          uint width,uint height);

public slots:
    void doWork();
    void outputResize(int w,int h);


private:
#ifdef HIK_INTERFACE
    std::unique_ptr<AVPacket,void(*)(void*)>            m_pPacket;
    std::unique_ptr<SwsContext,void(*)(SwsContext*)>    m_pImgConvertCtx;
    std::unique_ptr<uint8_t,void(*)(void*)>             m_pOutBuffer;

    AVFrame                 *m_pFrame;
    AVFrame                 *m_pFrameIMG;
    AVFormatContext         *m_pFormatCtx;
    AVCodecContext          *m_pCodecCtx;
    AVCodec                 *m_pCodec;
    int                     m_videoIndex;
#endif
    QString                 m_url;
    QSize                   m_outSize;
    QMetaObject::Connection m_connection;
    void                    *player = nullptr;
    QThread                 *thread=nullptr;

    static QMutex           s_mutex;
    static QMutex           m_videoMutex;
    static QMutex           m_msgMutex;
    static QMutex           m_doWorkMutex;
    static int cameraNum;
#ifdef HIK_INTERFACE
    // 进程内一次性初始化 FFmpeg 网络模块(avformat_network_init)。
    // 缺了它 rtmp://、rtsp:// 等网络流会打不开，而本地文件/VLC 不受影响。
    static FfmpegRegister   s_ffmpeg;
#endif
};

#endif // STREAMTHREAD_H
