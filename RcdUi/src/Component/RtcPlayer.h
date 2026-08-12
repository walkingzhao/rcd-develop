#ifndef RTCPLAYER_H
#define RTCPLAYER_H

#include <QObject>
#include <QByteArray>
#include <QMutex>
#include <QString>

#include <atomic>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <vector>

class QAudioOutput;
class QIODevice;

namespace rtc {
class PeerConnection;
class Track;
}

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/pixfmt.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

class RtcPlayer
{
public:
    using FrameCallback = std::function<void(const uchar *y,
                                             const uchar *u,
                                             const uchar *v,
                                             uint width,
                                             uint height)>;
    using VideoInfoCallback = std::function<void(double fps)>;
    using ErrorCallback = std::function<void(const QString &message)>;

    RtcPlayer();
    ~RtcPlayer();

    void setFrameCallback(FrameCallback callback);
    void setVideoInfoCallback(VideoInfoCallback callback);
    void setErrorCallback(ErrorCallback callback);

    void setAudioEnabled(bool enabled);
    bool start(const QString &url);
    void stop();
    bool isRunning() const;

private:
    struct SrsPlayRequest {
        QString api;
        QString streamUrl;
    };

    bool parseSrsPlayUrl(const QString &url, SrsPlayRequest &request) const;
    bool postOfferToSrs(const SrsPlayRequest &request, const QString &offerSdp, QString &answerSdp);
    QString browserizeOfferSdp(const QString &sdp) const;

    bool initDecoder();
    void releaseDecoder();
    void decodeAnnexB(const uint8_t *data, int size);
    void emitDecodedFrame(AVFrame *frame);
    bool applyAnswerVideoParams(const QString &answerSdp);
    void cacheParameterSetNal(const uint8_t *nal, size_t size);
    void prependCachedParameterSets(std::vector<uint8_t> &accessUnit) const;

    bool initAudioPlayer();
    bool ensureAudioPlayerReady();
    void releaseAudioPlayer();
    void handleVideoRtpPacket(const uint8_t *data, size_t size);
    void enqueueVideoRtpPacket(const uint8_t *data, size_t size);
    void processVideoRtpPacketInOrder(const uint8_t *data, size_t size);
    void onVideoPacketLoss(uint16_t lastSeq, uint16_t currentSeq, uint16_t diff);
    void requestVideoKeyframe();
    void handleAudioRtpPacket(const uint8_t *data, size_t size);
    void decodeOpusPayload(const uint8_t *payload, size_t size);
    int rtpPayloadOffset(const uint8_t *data, size_t size) const;
    void handleH264Payload(const uint8_t *payload, size_t size,
                           uint32_t timestamp, bool marker);
    void beginVideoAccessUnit(uint32_t timestamp);
    void appendNalToAccessUnit(const uint8_t *nal, size_t size);
    void finishVideoAccessUnit();

    void reportError(const QString &message);

private:
    std::atomic<bool> m_running{false};
    bool m_audioEnabled = true;
    bool m_audioPlayerReady = false;
    bool m_audioPlaybackStarted = false;
    std::shared_ptr<rtc::PeerConnection> m_peerConnection;
    std::shared_ptr<rtc::Track> m_localAudioTrack;
    std::shared_ptr<rtc::Track> m_localVideoTrack;
    std::shared_ptr<rtc::Track> m_remoteVideoTrack;
    std::shared_ptr<rtc::Track> m_remoteAudioTrack;

    FrameCallback m_frameCallback;
    VideoInfoCallback m_videoInfoCallback;
    ErrorCallback m_errorCallback;

    QMutex m_decodeMutex;
    std::vector<uint8_t> m_fuBuffer;
    bool m_fuStarted = false;
    bool m_hasLastRtpSeq = false;
    bool m_waitingForKeyframe = true;
    uint16_t m_lastRtpSeq = 0;
    // 短重排序缓冲：把乱序包排好再解，减少误判 sequence gap 导致花屏
    std::map<uint16_t, std::vector<uint8_t>> m_videoReorder;
    static constexpr size_t kVideoReorderMax = 8;
    std::vector<uint8_t> m_cachedSps;
    std::vector<uint8_t> m_cachedPps;
    bool m_paramSetsInjected = false;
    std::vector<uint8_t> m_videoAccessUnit;
    uint32_t m_videoAccessUnitTimestamp = 0;
    bool m_hasVideoAccessUnitTimestamp = false;
    bool m_videoAccessUnitHasIdr = false;

    AVCodecContext *m_codecCtx = nullptr;
    AVFrame *m_frame = nullptr;
    AVFrame *m_yuvFrame = nullptr;
    AVPacket *m_packet = nullptr;
    SwsContext *m_sws = nullptr;
    uint8_t *m_yuvBuffer = nullptr;
    int m_yuvBufferSize = 0;
    int m_yuvWidth = 0;
    int m_yuvHeight = 0;

    QMutex m_audioMutex;
    AVCodecContext *m_audioCodecCtx = nullptr;
    AVFrame *m_audioFrame = nullptr;
    AVPacket *m_audioPacket = nullptr;
    SwrContext *m_swr = nullptr;
    QAudioOutput *m_audioOutput = nullptr;
    QIODevice *m_audioDevice = nullptr;
    int m_audioOutSampleRate = 48000;
    int m_audioOutChannels = 2;
    QByteArray m_audioPendingPcm;
    static constexpr int kAudioOutputBufferMs = 500;
    static constexpr int kAudioPendingMaxMs = 400;
    static constexpr int kAudioPrebufferMs = 80;
    std::atomic<uint64_t> m_audioRtpCount{0};
    std::atomic<uint64_t> m_audioDecodeOk{0};
    std::atomic<uint64_t> m_audioPcmBytes{0};
    std::atomic<uint64_t> m_audioDropBytes{0};
};

#endif // RTCPLAYER_H
