#include "audiodecode.h"
#include <QDebug>
#include <QString>
#include <QDateTime>
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
#include "libavfilter/avfilter.h"
#include "libavutil/avutil.h"

#ifdef __cplusplus
};
#endif // __cplusplus
#define MAX_AUDIO_FRAME_SIZE    (19200)
AudioDecode::AudioDecode(std::string url, int sampleRate, int sampleSize, int channelCount)
{
    m_url=url;
    m_sampleRate=sampleRate;
    m_sampleSize=sampleSize;
    m_channelCount=channelCount;
    audioThread = std::thread([&](){
                while(1)
                {
//                    qDebug()<<sampleRate<<sampleSize<<channelCount;
                    if(0 != initAudioDevice(m_url, m_sampleRate, m_sampleSize, m_channelCount))
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                        continue;
                    }
                    startPlay();
                    freeAudioDevice();
                    if(playFlag==2)
                    {
//                        qDebug()<<"音频线程结束";
                        break;
                    }
                }
            });
    audioThread.detach();
}

AudioDecode::~AudioDecode()
{
    freeAudioDevice();
//    qDebug()<<"销毁playFlag:"<<playFlag;
//    if(audioThread != nullptr)
//        delete audioThread;
}

int AudioDecode::initAudioDevice(std::string url, int sampleRate, int sampleSize, int channelCount)
{
    qDebug()<<"初始化音频设备"<<QString(m_url.c_str())<<m_sampleRate<<m_sampleSize<<m_channelCount;
    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setSampleRate(m_sampleRate);
    format.setSampleSize(m_sampleSize);
    format.setChannelCount(m_channelCount);
    format.setSampleType(QAudioFormat::SignedInt);
    strUrl = m_url;

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    audioDeviceOk = info.isFormatSupported(format);
    if (audioDeviceOk) {
        audioOutput = new QAudioOutput(format);
        audioDevice = audioOutput->start();
        periodSize = audioOutput->periodSize();
        if (periodSize <= 0)
        {
            return -1;
        }
    } else {
        qDebug() << "Raw audio format not supported by backend, cannot play audio.";
        return -1;
    }
    return 0;
}

void AudioDecode::startPlay()
{
    playFlag = 1;

    //设备不正常则不解码
    if (!audioDeviceOk) {
        return;
    }

    //解码音频流
//    std::string strUrl="rtsp://admin:123456@192.168.23.210/live/stream0";
//    strUrl = "rtsp://admin:itage123@192.168.23.232:554/0";
    AVDictionary *opts = NULL;
    av_dict_set(&opts, "buffer_size", "102400", 0);
    av_dict_set(&opts, "max_delay", "6000", 0);
    av_dict_set(&opts, "stimeout", "2000000", 0);
    av_dict_set(&opts, "rtsp_transport", "udp", 0);

    AVFormatContext* ifmtCtx = NULL;

    int out_buffer_size;
    AVFrame* pFrame_Resample = av_frame_alloc();

    AVFrame* frame = av_frame_alloc();
    AVCodecContext* pACodecCtx = NULL;
    struct SwrContext *pSwrCtx = NULL;
    int ret;
    do
    {
        if (ret = avformat_open_input(&ifmtCtx, strUrl.c_str(), 0, &opts) < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "Could not open input stream file '%s'\n", strUrl.c_str());
            break;
        }
        ret = avformat_find_stream_info(ifmtCtx, NULL);
        if (ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "avformat_find_stream_info fail!\n");
            break;
        }
        int nAStreamIndex = -1;
        nAStreamIndex = av_find_best_stream(ifmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0);
        av_dump_format(ifmtCtx, 0 ,strUrl.c_str(), 0);
        pACodecCtx = ifmtCtx->streams[nAStreamIndex]->codec;
        AVCodec* pCodec = avcodec_find_decoder(pACodecCtx->codec_id);
        if (avcodec_open2(pACodecCtx, pCodec, NULL) < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "Error open codec!\n");
            break;
        }
        uint8_t* out_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE);
        uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;
        enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
        enum AVSampleFormat in_sample_fmt = pACodecCtx->sample_fmt;
        int in_sample_rate = pACodecCtx->sample_rate;
        int out_sample_rate = 44100;
        int in_channels = pACodecCtx->channels;
        int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
        int in_channel_layout = av_get_default_channel_layout(pACodecCtx->channels);
        pSwrCtx = swr_alloc();
        pSwrCtx = swr_alloc_set_opts(NULL, out_channel_layout, out_sample_fmt, out_sample_rate,
                                     in_channel_layout, in_sample_fmt, in_sample_rate, 0, NULL);
        ret = swr_init(pSwrCtx);
        if (ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "swr init fail!\n");
            break;
        }
        AVPacket pkt;
        av_init_packet(&pkt);
        while (1)
        {
            ret = av_read_frame(ifmtCtx, &pkt);
            if (ret < 0)
            {
                break;
            }
            if (pkt.stream_index != nAStreamIndex)
            {
                av_packet_unref(&pkt);
                continue;
            }
            ret = avcodec_send_packet(pACodecCtx, &pkt);
            if (ret < 0)
            {
                av_packet_unref(&pkt);
                av_log(NULL, AV_LOG_ERROR, "Error sending a packet!\n");
            }
            else
            {
                while (ret >= 0)
                {
                    ret = avcodec_receive_frame(pACodecCtx, frame);
                    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                    {
                        ret = -1;
                        break;
                    }
                    else if (ret < 0)
                    {
                        av_log(NULL, AV_LOG_ERROR, "Error dufing decoding!\n");
                        ret = -1;
                        break;
                    }
                    if (pFrame_Resample->nb_samples != frame->nb_samples)
                    {
                        pFrame_Resample->pts = frame->pts;
                        //double second = frame->pts * av_q2d(rt);
                        pFrame_Resample->nb_samples = av_rescale_rnd(swr_get_delay(pSwrCtx, out_sample_rate) + frame->nb_samples,
                                                                     out_sample_rate, in_sample_rate, AV_ROUND_UP);
                        av_samples_fill_arrays(pFrame_Resample->data, pFrame_Resample->linesize, out_buffer, out_channels,
                                               pFrame_Resample->nb_samples, out_sample_fmt, 0);
                    }
                    int len = swr_convert(pSwrCtx, pFrame_Resample->data, pFrame_Resample->nb_samples, (const uint8_t**)frame->data, frame->nb_samples);
                    out_buffer_size = len * out_channels * av_get_bytes_per_sample(out_sample_fmt);
                    char *buf = (char *)out_buffer;
                    int len2 = out_buffer_size;
                    while (1)
                    {
                        if(playFlag==2)
                        {
//                            ret=1;
//                            break;
                            return;
                        }
                        if (len2 <= 0)
                        {
                            break;
                        }
                        if (len2 <= periodSize)
                        {
                            if(playFlag==1)
                                audioDevice->write(buf, len2);
                            len2 -= len2;
                        }
                        else
                        {
                            if(playFlag==1)
                                audioDevice->write(buf, periodSize);
                            len2 -= periodSize;
                            buf += periodSize;
                        }
                    }
                }
            }
            av_packet_unref(&pkt);
//            break;
        }
        av_frame_free(&frame);
    } while (0);

    if (pACodecCtx != NULL)
    {
        avcodec_close(pACodecCtx);
    }
    if (ifmtCtx != NULL)
    {
        avformat_close_input(&ifmtCtx);
    }
    if (pFrame_Resample != NULL)
    {
        av_frame_free(&pFrame_Resample);
    }
    if (pSwrCtx != NULL)
    {
        swr_free(&pSwrCtx);
    }

}

void AudioDecode::pausePlay()
{
    playFlag = 0;
}

void AudioDecode::stopPlay()
{
    playFlag = 2;
}

void AudioDecode::freeAudioDevice()
{
    if(audioOutput!=nullptr)
    {
        audioOutput->stop();
//        audioOutput->deleteLater();
        delete audioOutput;
        audioOutput=nullptr;
    }
}
