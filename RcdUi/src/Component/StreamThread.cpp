#include "StreamThread.h"
#include <QThread>
#include <QDebug>
#ifdef HIK_INTERFACE
#include "RtcPlayer.h"
#else
#include "iLivePlayer.h"
#endif

#define USEOPENGL  true
#ifdef HIK_INTERFACE
FfmpegRegister::FfmpegRegister()
{
    //av_register_all();          //注册全部功能
    avformat_network_init();    //初始化FFmpeg网络模块
    av_log_set_level(AV_LOG_ERROR);
}

FfmpegRegister::~FfmpegRegister()
{
    avformat_network_deinit();
}
FfmpegRegister StreamThread::s_ffmpeg;
#endif
QMutex         StreamThread::s_mutex;
QMutex         StreamThread::m_videoMutex;
QMutex         StreamThread::m_msgMutex;
QMutex         StreamThread::m_doWorkMutex;
int            StreamThread::cameraNum;
StreamThread::StreamThread(QObject *parent) : QObject(parent),
#ifdef HIK_INTERFACE
    m_pPacket(NULL,free),
    m_pImgConvertCtx(NULL,sws_freeContext),
    m_pOutBuffer(NULL,av_free),
    m_pFrame(NULL),
    m_pFrameIMG(NULL),
    m_pFormatCtx(NULL),
    m_pCodecCtx(NULL),
#endif
    m_outSize(0,0)
{
    m_url.clear();
}

StreamThread::~StreamThread()
{
#ifdef HIK_INTERFACE
    if(m_pFrame != NULL){
        av_frame_free(&m_pFrame);
    }
    if(m_pFrameIMG != NULL){
        av_frame_free(&m_pFrameIMG);
    }
    if(m_pCodecCtx != NULL){
        avcodec_free_context(&m_pCodecCtx);
    }
    if(m_pFormatCtx != NULL){
        avformat_free_context(m_pFormatCtx);
    }
#else
    if(player!=nullptr)
    {
        outputResize(0,0);
    }
#endif
}

void StreamThread::stopThread()
{
    cameraNum = 0;
    emit sglFinished();
}

void StreamThread::startThread()
{
    thread = new QThread();
    connect(thread, SIGNAL(started()), this, SLOT(doWork()));
    connect(this, SIGNAL(sglFinished()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    this->moveToThread(thread);
    thread->start();
}

void StreamThread::setParameter(QString &url,QMetaObject::Connection &connection,int w,int h)
{
    m_url = url;
    m_outSize.setWidth(w);
    m_outSize.setHeight(h);
    m_connection = connection;
}

#ifdef HIK_INTERFACE
void StreamThread::outputResize(int w,int h)
{
    m_outSize.setWidth(w);
    m_outSize.setHeight(h);
    if(m_outSize.isNull()){
        this->disconnect(m_connection);
    }
}
#else
void StreamThread::outputResize(int w,int h)
{
    m_outSize.setWidth(w);
    m_outSize.setHeight(h);
    if(m_outSize.isNull()){
        this->disconnect(m_connection);

        if(player == nullptr){
            qDebug() << "[player] the video player has stopped!";
            return;
        }
        iLive_Player_stop(player);
        iLive_Player_shutdown(player, NULL);
        iLive_Player_dec_ref(player);
        player = nullptr;
        stopThread();
    }
}
#endif


void StreamThread::syncUpdateRGB(uint8_t* rgb, uint width, uint height)
{
    emit sglSyncUpdateRGB(rgb,width, height);
    emit sglAsyncUpdateUi();
}
int StreamThread::Video_Callback(void* opaque, void *frame, int*size, long long stamp, int picfmt, int width, int height, int index) {
//    QMutexLocker locker(&m_videoMutex);
//    return 0;
    StreamThread *p=(StreamThread *)opaque;
    p->syncUpdateRGB((uint8_t*)frame,width,height);
    return 0;
}

void StreamThread::msgCallback(int what, int arg1, int arg2, void *extra, void *player_str) {
//    QMutexLocker locker(&m_msgMutex);
    switch (what) {
        case 402:
            qDebug()<<"FFP_MSG_VIDEO_RENDERING_START";
            break;
        case 403:
            qDebug()<<"FFP_MSG_AUDIO_RENDERING_START";
            break;
        default:
            break;
    }
}

#ifndef HIK_INTERFACE
void StreamThread::doWork()
{
    QMutexLocker locker(&m_doWorkMutex);

    if(m_url.isEmpty()){
        qWarning("Missing parameter. \n");
    }else
    {
        // 清流(非 HIK_INTERFACE)编译：统一走第三方 iLive 播放器。
        // RTC / RTMP 的按 URL 选择只在 HIK_INTERFACE 编译分支里做。
        QByteArray urlByte = m_url.toLatin1();
        bool pzsp = strncmp(urlByte.data(), "pzsp://", 7) == 0;
        player = iLive_Player_create((void*)pzsp, NULL);
        qDebug()<<"player addr:"<<player<<urlByte.data();
        iLive_Player_set_data_source(player, NULL, urlByte.data());
        iLive_Player_prepare_async(player);
        iLive_Player_set_hwnd(player, NULL);
        this->setObjectName("摄像机="+QString::number(cameraNum++));


        int64_t arg[5];
        arg[0] = (uint64_t)this;

        arg[1] = (int64_t)StreamThread::Video_Callback;
        arg[2] = 4; /* 0: NV12, 3: BGRA, 4: RGB24 */
    #if 0
        arg[3] = 1; /* split frame ? */
        arg[4] = 4; /* split num */
    #else
        arg[3] = 0; /* split frame ? */
        arg[4] = 0; /* split num */
    #endif
        iLive_Player_set_player_op(player, NULL, ILIVE_PLAYER_OP_ID_SET_VIDEO_CALLBACK_EI, 5, (void*)arg, 0, NULL);
        arg[0] = (int64_t)StreamThread::msgCallback;
        iLive_Player_set_player_op(player, NULL, PIMEDIAPLAYER_OP_ID_SET_MSG_CALLBACK, 1, (void *)arg, 0, NULL);
        iLive_Player_start(player);
    }

}

#else
bool StreamThread::openStream()
{
    if(m_url.isEmpty()){
        qWarning("Missing parameter. \n");
        return false;
    }

    int ret = 0;
    //添加命令参数
    AVDictionary *options = NULL;
    const QString lowerUrl = m_url.toLower();
    const bool isRtsp = lowerUrl.startsWith("rtsp://");
    if (isRtsp) {
        // stimeout 是 rtsp/tcp 专用的 socket 超时参数(微秒)
        av_dict_set(&options, "stimeout", "2000000", 0);
        av_dict_set(&options, "rtsp_transport", "tcp", 0);
        av_dict_set(&options, "max_delay", "50", 0);
    } else {
        // rtmp/http-flv 不认 stimeout，用 rw_timeout(读写超时,微秒)；
        // 限制探测大小/时长，避免 find_stream_info 长时间阻塞。
        av_dict_set(&options, "rw_timeout", "2000000", 0);
    }
    m_pFormatCtx = avformat_alloc_context();
    if (!isRtsp) {
        m_pFormatCtx->probesize = 32768;
        m_pFormatCtx->max_analyze_duration = AV_TIME_BASE / 10;
    }
    ret = avformat_open_input(&m_pFormatCtx, m_url.toUtf8().data(), NULL, &options);
    av_dict_free(&options);

    if (ret != 0) {
        return false;
    }
    QMutexLocker lk(&s_mutex);
    if (avformat_find_stream_info(m_pFormatCtx, NULL) < 0) {
        qWarning("Could't find stream infomation.\n");
        return false;
    }

//    fprintf(stderr,"--------------- File Information ----------------\n");
    //打印输入或输出的详细信息
    av_dump_format(m_pFormatCtx, 0, m_url.toUtf8().data(), 0);
//    fprintf(stderr,"-------------------------------------------------\n");

    m_videoIndex = -1;

    //循环查找视频中包含的流信息，仅找视频类型的流
    for (uint i = 0; i < m_pFormatCtx->nb_streams; i++) {
        if (m_pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            m_videoIndex = i;
        }
    }
    if (m_videoIndex == -1) {
        qWarning("Didn't find a video stream.\n");
        return false;
    }

    //查找解码器
    m_pCodec = avcodec_find_decoder(m_pFormatCtx->streams[m_videoIndex]->codecpar->codec_id);
    m_pCodecCtx = avcodec_alloc_context3(m_pCodec);
    if (m_pCodec == NULL || m_pCodecCtx == NULL) {
        qWarning("Codec not found.\n");
        return false;
    }
    if(avcodec_parameters_to_context(m_pCodecCtx, m_pFormatCtx->streams[m_videoIndex]->codecpar) < 0){
        qWarning("Error initializing the decoder context.\n");
    }

    //    m_pCodecCtx->bit_rate =0;   //初始化为0
    //    m_pCodecCtx->time_base.num=1;  //一秒钟25帧
    //    m_pCodecCtx->time_base.den=25;
    //    m_pCodecCtx->frame_number=1;  //每包一个视频帧

    //打开解码器
    ret = avcodec_open2(m_pCodecCtx, m_pCodec, NULL);
    lk.unlock();
    if (ret < 0) {
        qWarning("Could not open codec.\n");
        return false;
    }
    if(m_pCodecCtx->width < 50 || m_pCodecCtx->height < 50){
        qWarning() << "error video width :" << m_pCodecCtx->width << "video height :" << m_pCodecCtx->height;
        return false;
    }

    m_pFrame = av_frame_alloc();
    m_pFrameIMG = av_frame_alloc();

#if USEOPENGL
    int size = av_image_get_buffer_size(AV_PIX_FMT_YUVJ420P, m_pCodecCtx->width,m_pCodecCtx->height,1);
#else
    int size = av_image_get_buffer_size(AV_PIX_FMT_RGB32, m_pCodecCtx->width,m_pCodecCtx->height,1);
#endif

    m_pOutBuffer = std::unique_ptr<uint8_t,void(*)(void*)>{
        static_cast<uint8_t*>(av_malloc(size)),av_free
    };

#if USEOPENGL
    av_image_fill_arrays(m_pFrameIMG->data, m_pFrameIMG->linesize, m_pOutBuffer.get(),
                         AV_PIX_FMT_YUVJ420P, m_pCodecCtx->width, m_pCodecCtx->height, 1);
#else
    av_image_fill_arrays(m_pFrameIMG->data, m_pFrameIMG->linesize, m_pOutBuffer.get(),
                         AV_PIX_FMT_RGB32, m_pCodecCtx->width, m_pCodecCtx->height, 1);
#endif

    m_pPacket = std::unique_ptr<AVPacket,void(*)(void*)>{
        static_cast<AVPacket*>(malloc(sizeof(AVPacket))),free
    };
    memset(m_pPacket.get(),0,sizeof(AVPacket));
    av_init_packet(m_pPacket.get());

#if USEOPENGL
    m_pImgConvertCtx = std::unique_ptr<SwsContext,void(*)(SwsContext*)>{
        sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height,
                       m_pCodecCtx->pix_fmt, m_pCodecCtx->width, m_pCodecCtx->height,
                       AV_PIX_FMT_YUVJ420P, SWS_BICUBIC, NULL, NULL, NULL),
                sws_freeContext
    };
#else
    m_pImgConvertCtx = std::unique_ptr<SwsContext,void(*)(SwsContext*)>{
        sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height,
                       m_pCodecCtx->pix_fmt, m_pCodecCtx->width, m_pCodecCtx->height,
                       AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL),
                sws_freeContext
    };
#endif

    return true;
}
void StreamThread::doWork()
{
    const QString lowerUrl = m_url.toLower();
    const bool useRtc = lowerUrl.startsWith("webrtc://") ||
        lowerUrl.contains("/rtc/v1/play") ||
        ((lowerUrl.startsWith("http://") || lowerUrl.startsWith("https://")) &&
         lowerUrl.contains("app=") && lowerUrl.contains("stream="));
    if (useRtc) {
        RtcPlayer rtcPlayer;
        rtcPlayer.setAudioEnabled(m_url.contains(QStringLiteral("inner_cam"), Qt::CaseInsensitive));
        rtcPlayer.setVideoInfoCallback([this](double fps) {
            emit sglVideoInfo(fps);
        });
        rtcPlayer.setFrameCallback([this](const uchar *y, const uchar *u, const uchar *v, uint width, uint height) {
            emit sglSyncUpdateYUV(y, u, v, width, height);
            emit sglAsyncUpdateUi();
        });
        rtcPlayer.setErrorCallback([](const QString &message) {
            qWarning() << "[rtc]" << message;
        });
        if (rtcPlayer.start(m_url)) {
            while (!m_outSize.isNull() && rtcPlayer.isRunning()) {
                QThread::msleep(20);
            }
        }
        rtcPlayer.stop();
        emit sglFinished();
        return;
    }

    if(openStream()) {

        int ret = -1;

        // 读取帧
        while (av_read_frame(m_pFormatCtx, m_pPacket.get()) >= 0) {

            if (m_pPacket->stream_index != m_videoIndex) {
                av_packet_unref(m_pPacket.get());
                continue;
            }

            // 发送包解码
            ret = avcodec_send_packet(m_pCodecCtx,m_pPacket.get());
            av_packet_unref(m_pPacket.get());
            if (ret != 0) {
                continue;
            }

            // 一个 packet 不一定立刻产出 frame；EAGAIN 是正常状态，不能当成解码失败。
            while ((ret = avcodec_receive_frame(m_pCodecCtx,m_pFrame)) == 0) {
                if(!m_outSize.isNull()) {
                    sws_scale(m_pImgConvertCtx.get(),
                              (const uint8_t* const*)m_pFrame->data, m_pFrame->linesize,
                              0, m_pCodecCtx->height,
                              m_pFrameIMG->data, m_pFrameIMG->linesize);
                    //返回解码图像
#if USEOPENGL
                    emit sglSyncUpdateYUV(m_pFrameIMG->data[0],m_pFrameIMG->data[1],m_pFrameIMG->data[2],
                            m_pCodecCtx->width, m_pCodecCtx->height);
                    emit sglAsyncUpdateUi();

#else
                    QImage tmpImg(static_cast<uchar*>(m_pOutBuffer.get()),m_pCodecCtx->width,m_pCodecCtx->height,QImage::Format_RGB32);
                    emit sglAsyncUpdateUi(QPixmap::fromImage(tmpImg.scaled(m_outSize,Qt::KeepAspectRatio)));  //发送信号
#endif

                }else{
                    break;
                }
            }
            if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
                qWarning("decode error.\n");
                break;
            }
        }
        QMutexLocker lk(&s_mutex);
        avcodec_close(m_pCodecCtx);
        avformat_close_input(&m_pFormatCtx);
    }
    emit sglFinished();
}
#endif
