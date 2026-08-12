#include "RtcPlayer.h"

#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QEventLoop>
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QThread>
#include <QUrl>
#include <QUrlQuery>
#include <QWaitCondition>
#include <QDebug>
#include <QStringList>

#include <QByteArray>
#include <cstring>
#include <iterator>
#include <variant>

#ifdef USE_LIBDATACHANNEL_RTC
#include <rtc/rtc.hpp>
#endif

namespace {
constexpr uint8_t kStartCode[] = {0x00, 0x00, 0x00, 0x01};

struct OfferState {
    QMutex mutex;
    QWaitCondition ready;
    QString sdp;
    QStringList candidates;
    bool received = false;
    bool gatheringComplete = false;
    bool closed = false;
};

static uint16_t readBe16(const uint8_t *p)
{
    return static_cast<uint16_t>((static_cast<uint16_t>(p[0]) << 8) | p[1]);
}

static uint32_t readBe32(const uint8_t *p)
{
    return (static_cast<uint32_t>(p[0]) << 24) |
           (static_cast<uint32_t>(p[1]) << 16) |
           (static_cast<uint32_t>(p[2]) << 8) |
           static_cast<uint32_t>(p[3]);
}

static bool isIdrNal(uint8_t nalHeader)
{
    return (nalHeader & 0x1F) == 5;
}

static bool isParameterSetNal(uint8_t nalHeader)
{
    const uint8_t nalType = nalHeader & 0x1F;
    return nalType == 7 || nalType == 8;
}
}

RtcPlayer::RtcPlayer()
{
}

RtcPlayer::~RtcPlayer()
{
    stop();
}

void RtcPlayer::setFrameCallback(FrameCallback callback)
{
    m_frameCallback = std::move(callback);
}

void RtcPlayer::setVideoInfoCallback(VideoInfoCallback callback)
{
    m_videoInfoCallback = std::move(callback);
}

void RtcPlayer::setErrorCallback(ErrorCallback callback)
{
    m_errorCallback = std::move(callback);
}

void RtcPlayer::setAudioEnabled(bool enabled)
{
    m_audioEnabled = enabled;
}

bool RtcPlayer::start(const QString &url)
{
#ifndef USE_LIBDATACHANNEL_RTC
    Q_UNUSED(url)
    reportError("USE_LIBDATACHANNEL_RTC is not enabled; libdatachannel is not linked.");
    return false;
#else
    if (m_running.exchange(true)) {
        return true;
    }

    SrsPlayRequest request;
    if (!parseSrsPlayUrl(url, request)) {
        m_running.store(false);
        reportError("unsupported rtc url: " + url);
        return false;
    }

    if (!initDecoder()) {
        m_running.store(false);
        reportError("failed to initialize H264 decoder");
        return false;
    }
    rtc::Configuration config;
    config.iceServers.emplace_back("stun:stun.l.google.com:19302");
    m_peerConnection = std::make_shared<rtc::PeerConnection>(config);

    auto offerState = std::make_shared<OfferState>();

    m_peerConnection->onStateChange([this, offerState](rtc::PeerConnection::State state) {
        qDebug() << "[rtc] peer state:" << static_cast<int>(state);
        if (state == rtc::PeerConnection::State::Disconnected ||
            state == rtc::PeerConnection::State::Failed ||
            state == rtc::PeerConnection::State::Closed) {
            m_running.store(false);
            QMutexLocker locker(&offerState->mutex);
            offerState->closed = true;
            offerState->ready.wakeAll();
        }
    });

    m_peerConnection->onGatheringStateChange([offerState](rtc::PeerConnection::GatheringState state) {
        qDebug() << "[rtc] gathering state:" << static_cast<int>(state);
        if (state == rtc::PeerConnection::GatheringState::Complete) {
            QMutexLocker locker(&offerState->mutex);
            offerState->gatheringComplete = true;
            offerState->ready.wakeAll();
        }
    });

    m_peerConnection->onLocalCandidate([](rtc::Candidate candidate) {
        const QString line = QString::fromStdString(candidate.candidate());
        if (line.isEmpty()) {
            return;
        }
        qDebug() << "[rtc] local candidate:" << line;
    });

    auto handleVideoTrack = [this](const std::shared_ptr<rtc::Track> &track) {
        if (!track) {
            return;
        }
        track->onMessage([this](std::variant<rtc::binary, rtc::string> message) {
            if (!m_running.load()) {
                return;
            }
            const auto *binary = std::get_if<rtc::binary>(&message);
            if (!binary) {
                return;
            }
            handleVideoRtpPacket(reinterpret_cast<const uint8_t *>(binary->data()), binary->size());
        });
    };

    auto handleAudioTrack = [this](const std::shared_ptr<rtc::Track> &track) {
        if (!track) {
            return;
        }
        track->onMessage([this](std::variant<rtc::binary, rtc::string> message) {
            if (!m_running.load()) {
                return;
            }
            const auto *binary = std::get_if<rtc::binary>(&message);
            if (!binary) {
                return;
            }
            handleAudioRtpPacket(reinterpret_cast<const uint8_t *>(binary->data()), binary->size());
        });
    };

    m_peerConnection->onTrack([this](std::shared_ptr<rtc::Track> track) {
        const QString type = track ? QString::fromStdString(track->description().type()) : QString();
        qDebug() << "[rtc] remote track opened type=" << type;
        // RTP 只从本地 recvonly track 的 onMessage 收，避免 local+remote 双订阅导致乱序/重复。
        if (type == "video") {
            m_remoteVideoTrack = track;
            return;
        }
        if (type == "audio") {
            m_remoteAudioTrack = track;
            qWarning() << "[rtc] remote audio track signaled (Opus)";
            return;
        }
    });

    // Use browser-style numeric mids ("0"/"1") instead of libdatachannel's default
    // "audio"/"video". Older/stricter SRS (4.0) rejects non-numeric mids with HTTP 400,
    // while Chrome (which SRS is validated against) always uses numeric mids. Setting the
    // mid at track creation keeps libdatachannel internally consistent (BUNDLE group, the
    // RTP mid header extension, and answer<->offer matching all follow this value).
    if (m_audioEnabled) {
        rtc::Description::Audio audio("0", rtc::Description::Direction::RecvOnly);
        audio.addOpusCodec(111);
        m_localAudioTrack = m_peerConnection->addTrack(audio);
        handleAudioTrack(m_localAudioTrack);
    }

    rtc::Description::Video media(m_audioEnabled ? "1" : "0", rtc::Description::Direction::RecvOnly);
    media.addH264Codec(109);
    m_localVideoTrack = m_peerConnection->addTrack(media);
    handleVideoTrack(m_localVideoTrack);

    m_peerConnection->onLocalDescription([this, offerState](rtc::Description description) {
        const QString sdp = QString::fromStdString(std::string(description));
        QMutexLocker locker(&offerState->mutex);
        offerState->sdp = browserizeOfferSdp(sdp);
        offerState->received = true;
        offerState->ready.wakeAll();
    });

    m_peerConnection->setLocalDescription();

    {
        QElapsedTimer timer;
        timer.start();
        QMutexLocker locker(&offerState->mutex);
        while (!offerState->received &&
               !offerState->closed &&
               timer.elapsed() < 10000) {
            offerState->ready.wait(&offerState->mutex,
                                   static_cast<unsigned long>(10000 - timer.elapsed()));
        }
    }

    if (!offerState->received || !m_running.load()) {
        stop();
        reportError("timed out waiting for local WebRTC offer");
        return false;
    }

    QString answerSdp;
    QString finalOffer;
    {
        QMutexLocker locker(&offerState->mutex);
        finalOffer = offerState->sdp;
    }

    if (!postOfferToSrs(request, finalOffer, answerSdp)) {
        stop();
        reportError("SRS /rtc/v1/play negotiation failed");
        return false;
    }

    applyAnswerVideoParams(answerSdp);

    try {
        m_peerConnection->setRemoteDescription(rtc::Description(answerSdp.toStdString(), "answer"));
    } catch (const std::exception &e) {
        stop();
        reportError(QString("failed to apply remote answer: %1").arg(e.what()));
        return false;
    }

    if (m_videoInfoCallback) {
        m_videoInfoCallback(30.0);
    }
    qDebug() << "[rtc] negotiation complete, receiving RTP";
    return true;
#endif
}

void RtcPlayer::stop()
{
    if (!m_running.exchange(false)) {
        return;
    }
    m_remoteAudioTrack.reset();
    m_remoteVideoTrack.reset();
    m_localVideoTrack.reset();
    m_localAudioTrack.reset();
    m_peerConnection.reset();
    releaseAudioPlayer();
    releaseDecoder();
    m_audioRtpCount.store(0);
    m_audioDecodeOk.store(0);
    m_audioPcmBytes.store(0);
    m_audioDropBytes.store(0);
}

bool RtcPlayer::isRunning() const
{
    return m_running.load();
}

bool RtcPlayer::parseSrsPlayUrl(const QString &url, SrsPlayRequest &request) const
{
    const QUrl parsed(url);
    const QString scheme = parsed.scheme().toLower();
    const QUrlQuery query(parsed);

    if (scheme == "webrtc") {
        if (parsed.host().isEmpty() || parsed.path().isEmpty()) {
            return false;
        }
        const QString explicitApi = query.queryItemValue("api");
        if (!explicitApi.isEmpty()) {
            request.api = explicitApi;
        } else {
            const int apiPort = parsed.port(1985);
            request.api = QString("http://%1:%2/rtc/v1/play/").arg(parsed.host()).arg(apiPort);
        }
        // Match the browser page: streamurl is webrtc://host/app/stream, not the HTTP API URL.
        request.streamUrl = QString("webrtc://%1%2").arg(parsed.host(), parsed.path());
        return true;
    }

    if (scheme == "http" || scheme == "https") {
        QString app = query.queryItemValue("app");
        QString stream = query.queryItemValue("stream");
        if (app.isEmpty() || stream.isEmpty()) {
            const QStringList parts = parsed.path().split('/', Qt::SkipEmptyParts);
            // Accept http://host/live/front_cam as shorthand for the browser inputs.
            if (parts.size() >= 2 && parts.value(0) != "rtc") {
                app = parts.value(0);
                stream = parts.value(1);
            }
        }
        if (parsed.host().isEmpty() || app.isEmpty() || stream.isEmpty()) {
            return false;
        }
        const int apiPort = parsed.port(scheme == "https" ? 443 : 80);
        if (parsed.path().contains("/rtc/v1/play")) {
            request.api = QString("%1://%2:%3/rtc/v1/play/")
                              .arg(scheme)
                              .arg(parsed.host())
                              .arg(apiPort);
        } else {
            request.api = QString("%1://%2:%3/rtc/v1/play/")
                              .arg(scheme)
                              .arg(parsed.host())
                              .arg(apiPort);
        }
        request.streamUrl = QString("webrtc://%1/%2/%3").arg(parsed.host(), app, stream);
        return true;
    }

    return false;
}

bool RtcPlayer::postOfferToSrs(const SrsPlayRequest &request, const QString &offerSdp, QString &answerSdp)
{
    QNetworkAccessManager manager;
    QNetworkRequest httpRequest((QUrl(request.api)));
    httpRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject body;
    body.insert("api", request.api);
    body.insert("streamurl", request.streamUrl);
    body.insert("sdp", offerSdp);

    QNetworkReply *reply = manager.post(httpRequest, QJsonDocument(body).toJson(QJsonDocument::Compact));
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    const auto guard = std::unique_ptr<QNetworkReply, void(*)(QNetworkReply*)>{
        reply, [](QNetworkReply *r) { if (r) r->deleteLater(); }
    };

    if (reply->error() != QNetworkReply::NoError) {
        reportError("SRS play HTTP error: " + reply->errorString());
        return false;
    }

    const QByteArray payload = reply->readAll();
    const QJsonDocument doc = QJsonDocument::fromJson(payload);
    if (!doc.isObject()) {
        reportError("SRS play response is not JSON: " + QString::fromUtf8(payload.left(200)));
        return false;
    }

    const QJsonObject obj = doc.object();
    if (obj.value("code").toInt(-1) != 0) {
        reportError("SRS play rejected offer: " + QString::fromUtf8(payload.left(500)));
        return false;
    }

    answerSdp = obj.value("sdp").toString();
    if (answerSdp.isEmpty()) {
        answerSdp = obj.value("data").toObject().value("sdp").toString();
    }
    return !answerSdp.isEmpty();
}

QString RtcPlayer::browserizeOfferSdp(const QString &sdp) const
{
    QStringList out;
    const QStringList lines = sdp.split(QRegularExpression("[\r\n]+"), Qt::SkipEmptyParts);
    bool inAudio = false;
    bool inVideo = false;
    bool addedExtmaps = false;
    bool addedFeedback = false;

    const QStringList audioExtmaps = {
        "a=extmap:1 urn:ietf:params:rtp-hdrext:ssrc-audio-level",
        "a=extmap:2 http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time",
        "a=extmap:4 urn:ietf:params:rtp-hdrext:sdes:mid",
    };
    const QStringList videoExtmaps = {
        "a=extmap:14 urn:ietf:params:rtp-hdrext:toffset",
        "a=extmap:2 http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time",
        "a=extmap:13 urn:3gpp:video-orientation",
        "a=extmap:5 http://www.webrtc.org/experiments/rtp-hdrext/playout-delay",
        "a=extmap:6 http://www.webrtc.org/experiments/rtp-hdrext/video-content-type",
        "a=extmap:7 http://www.webrtc.org/experiments/rtp-hdrext/video-timing",
        "a=extmap:8 http://www.webrtc.org/experiments/rtp-hdrext/color-space",
        "a=extmap:4 urn:ietf:params:rtp-hdrext:sdes:mid",
    };
    const QStringList feedback = {
        "a=rtcp-fb:109 goog-remb",
        "a=rtcp-fb:109 ccm fir",
        "a=rtcp-fb:109 nack",
        "a=rtcp-fb:109 nack pli",
    };

    const bool hasExtmapAllowMixed = lines.contains("a=extmap-allow-mixed");
    for (const QString &line : lines) {
        // libdatachannel emits a lip-sync group "a=group:LS ..." that Chrome never sends
        // and that stricter SRS builds (4.0) reject. Drop it so the offer looks browser-like.
        if (line.startsWith("a=group:LS")) {
            continue;
        }

        if (line.startsWith("a=group:BUNDLE") && !hasExtmapAllowMixed) {
            out << line << "a=extmap-allow-mixed";
            continue;
        }

        if (line.startsWith("m=")) {
            inAudio = line.startsWith("m=audio ");
            inVideo = line.startsWith("m=video ");
            addedExtmaps = false;
            addedFeedback = false;
        }

        if (inAudio && line.startsWith("a=mid:") && !addedExtmaps) {
            out << line;
            out << audioExtmaps;
            addedExtmaps = true;
            continue;
        }

        if (inVideo && line.startsWith("a=mid:") && !addedExtmaps) {
            out << line;
            out << videoExtmaps;
            addedExtmaps = true;
            continue;
        }

        if (inVideo && line.startsWith("a=rtcp-fb:109")) {
            continue;
        }

        if (inVideo && line.startsWith("a=fmtp:109")) {
            out << feedback;
            out << "a=fmtp:109 level-asymmetry-allowed=1;packetization-mode=1;profile-level-id=42e01f";
            addedFeedback = true;
            continue;
        }

        out << line;
    }

    if (addedExtmaps || addedFeedback) {
        qDebug() << "[rtc] adjusted offer SDP for SRS/Chrome-like H264 feedback";
    }
    return out.join("\r\n") + "\r\n";
}

bool RtcPlayer::initDecoder()
{
    const AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec) {
        return false;
    }

    m_codecCtx = avcodec_alloc_context3(codec);
    if (!m_codecCtx) {
        return false;
    }
    m_codecCtx->flags |= AV_CODEC_FLAG_LOW_DELAY;
    m_codecCtx->flags2 |= AV_CODEC_FLAG2_FAST;
    // zerolatency/x264 常将一帧编码成多个 slice。原先强制单线程会让
    // 1080p mp4 软件解码明显落后于浏览器硬解；slice 并行不增加帧级缓存延迟。
    m_codecCtx->thread_count = 4;
    m_codecCtx->thread_type = FF_THREAD_SLICE;

    if (avcodec_open2(m_codecCtx, codec, nullptr) < 0) {
        releaseDecoder();
        return false;
    }

    m_frame = av_frame_alloc();
    m_yuvFrame = av_frame_alloc();
    m_packet = av_packet_alloc();
    if (!m_frame || !m_yuvFrame || !m_packet) {
        releaseDecoder();
        return false;
    }
    return true;
}

void RtcPlayer::releaseDecoder()
{
    QMutexLocker locker(&m_decodeMutex);
    if (m_packet) {
        av_packet_free(&m_packet);
    }
    if (m_frame) {
        av_frame_free(&m_frame);
    }
    if (m_yuvFrame) {
        av_frame_free(&m_yuvFrame);
    }
    if (m_codecCtx) {
        avcodec_free_context(&m_codecCtx);
    }
    if (m_sws) {
        sws_freeContext(m_sws);
        m_sws = nullptr;
    }
    if (m_yuvBuffer) {
        av_free(m_yuvBuffer);
        m_yuvBuffer = nullptr;
    }
    m_yuvBufferSize = 0;
    m_yuvWidth = 0;
    m_yuvHeight = 0;
    m_fuBuffer.clear();
    m_fuStarted = false;
    m_hasLastRtpSeq = false;
    m_waitingForKeyframe = true;
    m_lastRtpSeq = 0;
    m_videoReorder.clear();
    m_cachedSps.clear();
    m_cachedPps.clear();
    m_paramSetsInjected = false;
    m_videoAccessUnit.clear();
    m_videoAccessUnitTimestamp = 0;
    m_hasVideoAccessUnitTimestamp = false;
    m_videoAccessUnitHasIdr = false;
}

void RtcPlayer::handleVideoRtpPacket(const uint8_t *data, size_t size)
{
    QMutexLocker locker(&m_decodeMutex);
    if (!data || size < 12) {
        return;
    }
    // 不再按 PT 过滤：Answer 里的 H264 PT 可能不是 109，误过滤会导致系统性丢包花屏。
    enqueueVideoRtpPacket(data, size);
}

void RtcPlayer::enqueueVideoRtpPacket(const uint8_t *data, size_t size)
{
    const uint16_t sequence = readBe16(data + 2);

    if (!m_hasLastRtpSeq) {
        processVideoRtpPacketInOrder(data, size);
        return;
    }

    const uint16_t expected = static_cast<uint16_t>(m_lastRtpSeq + 1);
    if (sequence == expected) {
        processVideoRtpPacketInOrder(data, size);
        // 只冲刷连续包，避免把有缺口的数据突发交给解码器。
        while (true) {
            const uint16_t next = static_cast<uint16_t>(m_lastRtpSeq + 1);
            auto it = m_videoReorder.find(next);
            if (it == m_videoReorder.end()) {
                break;
            }
            std::vector<uint8_t> pkt = std::move(it->second);
            m_videoReorder.erase(it);
            processVideoRtpPacketInOrder(pkt.data(), pkt.size());
        }
        return;
    }

    const uint16_t forward = static_cast<uint16_t>(sequence - m_lastRtpSeq);
    if (forward == 0 || forward > 0x8000) {
        // 重复或过时乱序包
        return;
    }

    // 未来包：先缓存，等中间包；缓冲过大则判定丢包并追赶
    m_videoReorder[sequence] = std::vector<uint8_t>(data, data + size);
    if (m_videoReorder.size() <= kVideoReorderMax && forward <= kVideoReorderMax) {
        return;
    }

    // 中间包迟迟不来：选相对当前序号最近的缓存包追赶。
    // 不能直接使用 map.begin()，因为 RTP 序号在 65535 后会回绕。
    auto it = m_videoReorder.begin();
    for (auto candidate = m_videoReorder.begin();
         candidate != m_videoReorder.end(); ++candidate) {
        const uint16_t candidateDistance =
            static_cast<uint16_t>(candidate->first - m_lastRtpSeq);
        const uint16_t bestDistance =
            static_cast<uint16_t>(it->first - m_lastRtpSeq);
        if (candidateDistance < bestDistance) {
            it = candidate;
        }
    }

    const uint16_t nextAvailable = it->first;
    const uint16_t lostDiff = static_cast<uint16_t>(nextAvailable - m_lastRtpSeq);
    onVideoPacketLoss(m_lastRtpSeq, nextAvailable, lostDiff);

    // 丢包只报告一次；从最近可用包继续，后续仍只处理连续序号。
    m_lastRtpSeq = static_cast<uint16_t>(nextAvailable - 1);
    std::vector<uint8_t> packet = std::move(it->second);
    m_videoReorder.erase(it);
    processVideoRtpPacketInOrder(packet.data(), packet.size());

    while (true) {
        const uint16_t next = static_cast<uint16_t>(m_lastRtpSeq + 1);
        auto contiguous = m_videoReorder.find(next);
        if (contiguous == m_videoReorder.end()) {
            break;
        }
        std::vector<uint8_t> contiguousPacket = std::move(contiguous->second);
        m_videoReorder.erase(contiguous);
        processVideoRtpPacketInOrder(contiguousPacket.data(), contiguousPacket.size());
    }
}

void RtcPlayer::onVideoPacketLoss(uint16_t lastSeq, uint16_t currentSeq, uint16_t diff)
{
    qWarning() << "[rtc] RTP sequence gap, wait keyframe. last="
               << lastSeq << "current=" << currentSeq << "diff=" << diff;
    m_fuBuffer.clear();
    m_fuStarted = false;
    m_videoAccessUnit.clear();
    m_hasVideoAccessUnitTimestamp = false;
    m_videoAccessUnitHasIdr = false;
    m_waitingForKeyframe = true;
    if (m_codecCtx) {
        avcodec_flush_buffers(m_codecCtx);
    }
    requestVideoKeyframe();
}

void RtcPlayer::requestVideoKeyframe()
{
    // 可选：若链接的 libdatachannel 支持 Track::requestKeyframe()（发 PLI），
    // 可在此调用以加速丢包后恢复。当前以“等下一个 IDR + flush decoder”为主。
}

void RtcPlayer::processVideoRtpPacketInOrder(const uint8_t *data, size_t size)
{
    if (!data || size < 12) {
        return;
    }

    const uint16_t sequence = readBe16(data + 2);
    if (m_hasLastRtpSeq) {
        const uint16_t diff = static_cast<uint16_t>(sequence - m_lastRtpSeq);
        if (diff == 0 || diff > 0x8000) {
            return;
        }
        if (diff != 1) {
            onVideoPacketLoss(m_lastRtpSeq, sequence, diff);
        }
    }
    m_lastRtpSeq = sequence;
    m_hasLastRtpSeq = true;

    const int payloadOffset = rtpPayloadOffset(data, size);
    if (payloadOffset < 0 || static_cast<size_t>(payloadOffset) >= size) {
        return;
    }
    const uint32_t timestamp = readBe32(data + 4);
    const bool marker = (data[1] & 0x80) != 0;
    handleH264Payload(data + payloadOffset,
                      size - static_cast<size_t>(payloadOffset),
                      timestamp, marker);
}

bool RtcPlayer::initAudioPlayer()
{
    const AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_OPUS);
    if (!codec) {
        return false;
    }
    m_audioCodecCtx = avcodec_alloc_context3(codec);
    if (!m_audioCodecCtx) {
        return false;
    }
    m_audioCodecCtx->sample_rate = 48000;
    m_audioCodecCtx->channels = 2;
    m_audioCodecCtx->channel_layout = AV_CH_LAYOUT_STEREO;
    if (avcodec_open2(m_audioCodecCtx, codec, nullptr) < 0) {
        releaseAudioPlayer();
        return false;
    }
    m_audioFrame = av_frame_alloc();
    m_audioPacket = av_packet_alloc();
    if (!m_audioFrame || !m_audioPacket) {
        releaseAudioPlayer();
        return false;
    }

    QAudioFormat format;
    format.setSampleRate(m_audioOutSampleRate);
    format.setChannelCount(m_audioOutChannels);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    // Prefer analog/PCH speakers; avoid null and HDMI (HDMI often has no speakers).
    auto deviceScore = [](const QAudioDeviceInfo& d) -> int {
        const QString n = d.deviceName().toLower();
        if (n.isEmpty() || n.contains(QStringLiteral("null")) || n.contains(QStringLiteral("dummy"))) {
            return -100;
        }
        if (n.contains(QStringLiteral("hdmi"))) {
            return 1; // last resort only
        }
        int score = 10;
        if (n == QStringLiteral("pulse") || n.contains(QStringLiteral("pulseaudio"))) {
            score += 80;
        }
        if (n.contains(QStringLiteral("analog"))) score += 50;
        if (n.contains(QStringLiteral("pch")) || n.contains(QStringLiteral("hda intel"))) score += 30;
        if (n.contains(QStringLiteral("hw_0_0")) || n.contains(QStringLiteral("hw:0,0"))) score += 40;
        if (n.contains(QStringLiteral("speaker")) || n.contains(QStringLiteral("headphone"))) score += 20;
        return score;
    };

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();
    int bestScore = deviceScore(info);
    const QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    qWarning() << "[rtc] audio devices available=" << devices.size()
                << "default=" << info.deviceName() << "score=" << bestScore;
    for (const QAudioDeviceInfo& d : devices) {
        const int score = deviceScore(d);
        qWarning() << "[rtc]   out device:" << d.deviceName() << "score=" << score;
        if (score > bestScore) {
            bestScore = score;
            info = d;
        }
    }
    if (bestScore < 0) {
        qWarning() << "[rtc] no real audio output device; PCM will be silent.";
    } else if (info.deviceName().toLower().contains(QStringLiteral("hdmi"))) {
        qWarning() << "[rtc] only HDMI output found; speakers may be silent. "
                      "Set Pulse default to analog (hw:0,0).";
    }

    if (!info.isFormatSupported(format)) {
        format = info.nearestFormat(format);
        m_audioOutSampleRate = format.sampleRate();
        m_audioOutChannels = format.channelCount();
    }
    m_audioOutput = new QAudioOutput(info, format);
    m_audioOutput->setVolume(1.0);
  // ~500ms 硬件缓冲，弱网下吸收抖动
    m_audioOutput->setBufferSize(
        m_audioOutSampleRate * m_audioOutChannels * 2 * kAudioOutputBufferMs / 1000);
    m_audioDevice = m_audioOutput->start();
    if (!m_audioDevice) {
        qWarning() << "[rtc] QAudioOutput::start failed device=" << info.deviceName();
        return false;
    }
    qWarning() << "[rtc] audio player ready device=" << info.deviceName()
               << "rate=" << m_audioOutSampleRate
               << "ch=" << m_audioOutChannels;
    return true;
}

bool RtcPlayer::ensureAudioPlayerReady()
{
    if (m_audioPlayerReady) {
        return m_audioCodecCtx != nullptr;
    }
    if (!m_audioEnabled) {
        return false;
    }
    m_audioPlayerReady = initAudioPlayer();
    if (!m_audioPlayerReady) {
        qWarning() << "[rtc] audio player init failed, continue video-only";
    }
    return m_audioPlayerReady;
}

void RtcPlayer::releaseAudioPlayer()
{
    QMutexLocker locker(&m_audioMutex);
    m_audioPendingPcm.clear();
    m_audioPlaybackStarted = false;
    m_audioPlayerReady = false;
    if (m_audioOutput) {
        m_audioOutput->stop();
        delete m_audioOutput;
        m_audioOutput = nullptr;
        m_audioDevice = nullptr;
    }
    if (m_swr) {
        swr_free(&m_swr);
        m_swr = nullptr;
    }
    if (m_audioPacket) {
        av_packet_free(&m_audioPacket);
    }
    if (m_audioFrame) {
        av_frame_free(&m_audioFrame);
    }
    if (m_audioCodecCtx) {
        avcodec_free_context(&m_audioCodecCtx);
    }
}

void RtcPlayer::handleAudioRtpPacket(const uint8_t *data, size_t size)
{
    if (!data || size < 12 || !ensureAudioPlayerReady() || !m_audioCodecCtx) {
        return;
    }
    const int payloadOffset = rtpPayloadOffset(data, size);
    if (payloadOffset < 0 || static_cast<size_t>(payloadOffset) >= size) {
        return;
    }

    const uint64_t rtpCount = ++m_audioRtpCount;
    if (rtpCount == 1) {
        qWarning() << "[rtc] first Opus RTP received, size=" << size;
    } else if (rtpCount % 200 == 0) {
        qWarning() << "[rtc] audio stats rtp=" << rtpCount
                   << "decode_ok=" << m_audioDecodeOk.load()
                   << "pcm_bytes=" << m_audioPcmBytes.load()
                   << "drop_bytes=" << m_audioDropBytes.load();
    }

    decodeOpusPayload(data + payloadOffset, size - static_cast<size_t>(payloadOffset));
}

void RtcPlayer::decodeOpusPayload(const uint8_t *payload, size_t size)
{
    QMutexLocker locker(&m_audioMutex);
    if (!m_audioCodecCtx || !m_audioPacket || !m_audioFrame || !payload || size == 0) {
        return;
    }

    m_audioPacket->data = const_cast<uint8_t *>(payload);
    m_audioPacket->size = static_cast<int>(size);
    if (avcodec_send_packet(m_audioCodecCtx, m_audioPacket) < 0) {
        return;
    }

    while (avcodec_receive_frame(m_audioCodecCtx, m_audioFrame) == 0) {
        ++m_audioDecodeOk;
        if (!m_audioDevice) {
            continue;
        }

        const int srcChannels = m_audioFrame->channels > 0 ? m_audioFrame->channels : 2;
        const uint64_t srcLayout = m_audioFrame->channel_layout
                                       ? m_audioFrame->channel_layout
                                       : av_get_default_channel_layout(srcChannels);
        const int srcRate = m_audioFrame->sample_rate > 0 ? m_audioFrame->sample_rate : 48000;

        if (!m_swr) {
            m_swr = swr_alloc_set_opts(
                nullptr,
                av_get_default_channel_layout(m_audioOutChannels),
                AV_SAMPLE_FMT_S16,
                m_audioOutSampleRate,
                srcLayout,
                static_cast<AVSampleFormat>(m_audioFrame->format),
                srcRate,
                0,
                nullptr);
            if (!m_swr || swr_init(m_swr) < 0) {
                if (m_swr) {
                    swr_free(&m_swr);
                }
                continue;
            }
        }

        const int outSamples = swr_get_out_samples(m_swr, m_audioFrame->nb_samples);
        if (outSamples <= 0) {
            continue;
        }
        QByteArray pcm;
        pcm.resize(outSamples * m_audioOutChannels * static_cast<int>(sizeof(int16_t)));
        uint8_t *outPlanes[1] = { reinterpret_cast<uint8_t *>(pcm.data()) };
        const int converted = swr_convert(
            m_swr,
            outPlanes,
            outSamples,
            (const uint8_t **)m_audioFrame->data,
            m_audioFrame->nb_samples);
        if (converted <= 0) {
            continue;
        }
        const int bytes = converted * m_audioOutChannels * static_cast<int>(sizeof(int16_t));
        m_audioPendingPcm.append(pcm.constData(), bytes);

        const int bytesPerMs = m_audioOutSampleRate * m_audioOutChannels * 2 / 1000;
        if (!m_audioPlaybackStarted) {
            if (m_audioPendingPcm.size() < bytesPerMs * kAudioPrebufferMs) {
                continue;
            }
            m_audioPlaybackStarted = true;
        }

        const int pendingMaxBytes = bytesPerMs * kAudioPendingMaxMs;
        if (m_audioPendingPcm.size() > pendingMaxBytes) {
            const int drop = m_audioPendingPcm.size() - pendingMaxBytes;
            m_audioPendingPcm.remove(0, drop);
            m_audioDropBytes += static_cast<uint64_t>(drop);
        }

        while (!m_audioPendingPcm.isEmpty() && m_audioDevice) {
            const int free = m_audioOutput ? m_audioOutput->bytesFree() : m_audioPendingPcm.size();
            if (free <= 0) {
                break;
            }
            const int toWrite = qMin(m_audioPendingPcm.size(), free);
            const qint64 written = m_audioDevice->write(m_audioPendingPcm.constData(), toWrite);
            if (written <= 0) {
                break;
            }
            m_audioPendingPcm.remove(0, static_cast<int>(written));
            m_audioPcmBytes += static_cast<uint64_t>(written);
        }
    }
}

int RtcPlayer::rtpPayloadOffset(const uint8_t *data, size_t size) const
{
    if (!data || size < 12) {
        return -1;
    }
    const uint8_t version = data[0] >> 6;
    if (version != 2) {
        return -1;
    }

    const bool hasExtension = (data[0] & 0x10) != 0;
    const int csrcCount = data[0] & 0x0F;
    size_t offset = 12 + static_cast<size_t>(csrcCount) * 4;
    if (offset > size) {
        return -1;
    }

    if (hasExtension) {
        if (offset + 4 > size) {
            return -1;
        }
        const uint16_t extensionWords = readBe16(data + offset + 2);
        offset += 4 + static_cast<size_t>(extensionWords) * 4;
        if (offset > size) {
            return -1;
        }
    }
    return static_cast<int>(offset);
}

void RtcPlayer::handleH264Payload(const uint8_t *payload, size_t size,
                                  uint32_t timestamp, bool marker)
{
    if (!payload || size < 1) {
        return;
    }

    beginVideoAccessUnit(timestamp);

    const uint8_t nalType = payload[0] & 0x1F;
    if (nalType >= 1 && nalType <= 23) {
        if (isParameterSetNal(payload[0])) {
            cacheParameterSetNal(payload, size);
        }
        if (isIdrNal(payload[0])) {
            m_videoAccessUnitHasIdr = true;
        }
        appendNalToAccessUnit(payload, size);
        if (marker) {
            finishVideoAccessUnit();
        }
        return;
    }

    if (nalType == 24) { // STAP-A
        size_t offset = 1;
        while (offset + 2 <= size) {
            const uint16_t nalSize = readBe16(payload + offset);
            offset += 2;
            if (nalSize == 0 || offset + nalSize > size) {
                break;
            }
            const uint8_t stapNalType = payload[offset] & 0x1F;
            if (stapNalType == 7 || stapNalType == 8) {
                cacheParameterSetNal(payload + offset, nalSize);
            }
            if (stapNalType == 5) {
                m_videoAccessUnitHasIdr = true;
            }
            appendNalToAccessUnit(payload + offset, nalSize);
            offset += nalSize;
        }
        if (marker) {
            finishVideoAccessUnit();
        }
        return;
    }

    if (nalType == 28) { // FU-A
        if (size < 3) {
            return;
        }
        const uint8_t fuIndicator = payload[0];
        const uint8_t fuHeader = payload[1];
        const bool start = (fuHeader & 0x80) != 0;
        const bool end = (fuHeader & 0x40) != 0;
        const uint8_t reconstructedNal = (fuIndicator & 0xE0) | (fuHeader & 0x1F);

        if (start) {
            m_fuBuffer.clear();
            m_fuBuffer.push_back(reconstructedNal);
            m_fuBuffer.insert(m_fuBuffer.end(), payload + 2, payload + size);
            m_fuStarted = true;
        } else if (m_fuStarted) {
            m_fuBuffer.insert(m_fuBuffer.end(), payload + 2, payload + size);
        }

        if (end && m_fuStarted) {
            if (isIdrNal(m_fuBuffer[0])) {
                m_videoAccessUnitHasIdr = true;
            }
            appendNalToAccessUnit(m_fuBuffer.data(), m_fuBuffer.size());
            m_fuBuffer.clear();
            m_fuStarted = false;
        }
        if (marker) {
            // marker 应位于该帧最后一个 FU 包；分片不完整时整帧丢弃。
            if (m_fuStarted) {
                m_fuBuffer.clear();
                m_fuStarted = false;
                m_videoAccessUnit.clear();
                m_videoAccessUnitHasIdr = false;
            }
            finishVideoAccessUnit();
        }
    }
}

void RtcPlayer::beginVideoAccessUnit(uint32_t timestamp)
{
    if (!m_hasVideoAccessUnitTimestamp) {
        m_videoAccessUnitTimestamp = timestamp;
        m_hasVideoAccessUnitTimestamp = true;
        return;
    }

    if (timestamp != m_videoAccessUnitTimestamp) {
        // 上一帧没有 marker，不能把两个时间戳的 slice 混在一起。
        m_videoAccessUnit.clear();
        m_fuBuffer.clear();
        m_fuStarted = false;
        m_videoAccessUnitHasIdr = false;
        m_videoAccessUnitTimestamp = timestamp;
    }
}

void RtcPlayer::appendNalToAccessUnit(const uint8_t *nal, size_t size)
{
    if (!nal || size == 0) {
        return;
    }
    m_videoAccessUnit.insert(m_videoAccessUnit.end(),
                             std::begin(kStartCode), std::end(kStartCode));
    m_videoAccessUnit.insert(m_videoAccessUnit.end(), nal, nal + size);
}

void RtcPlayer::finishVideoAccessUnit()
{
    if (m_videoAccessUnit.empty()) {
        m_hasVideoAccessUnitTimestamp = false;
        m_videoAccessUnitHasIdr = false;
        return;
    }

    if (m_waitingForKeyframe && !m_videoAccessUnitHasIdr) {
        m_videoAccessUnit.clear();
        m_hasVideoAccessUnitTimestamp = false;
        return;
    }

    if (m_videoAccessUnitHasIdr) {
        std::vector<uint8_t> complete;
        prependCachedParameterSets(complete);
        complete.insert(complete.end(),
                        m_videoAccessUnit.begin(), m_videoAccessUnit.end());
        decodeAnnexB(complete.data(), static_cast<int>(complete.size()));
        m_waitingForKeyframe = false;
    } else {
        decodeAnnexB(m_videoAccessUnit.data(),
                     static_cast<int>(m_videoAccessUnit.size()));
    }

    m_videoAccessUnit.clear();
    m_hasVideoAccessUnitTimestamp = false;
    m_videoAccessUnitHasIdr = false;
}

void RtcPlayer::cacheParameterSetNal(const uint8_t *nal, size_t size)
{
    if (!nal || size < 1) {
        return;
    }
    const uint8_t nalType = nal[0] & 0x1F;
    std::vector<uint8_t> copy(nal, nal + size);
    if (nalType == 7) {
        m_cachedSps = std::move(copy);
    } else if (nalType == 8) {
        m_cachedPps = std::move(copy);
    }
}

void RtcPlayer::prependCachedParameterSets(std::vector<uint8_t> &accessUnit) const
{
    if (!m_cachedSps.empty()) {
        accessUnit.insert(accessUnit.end(), std::begin(kStartCode), std::end(kStartCode));
        accessUnit.insert(accessUnit.end(), m_cachedSps.begin(), m_cachedSps.end());
    }
    if (!m_cachedPps.empty()) {
        accessUnit.insert(accessUnit.end(), std::begin(kStartCode), std::end(kStartCode));
        accessUnit.insert(accessUnit.end(), m_cachedPps.begin(), m_cachedPps.end());
    }
}

bool RtcPlayer::applyAnswerVideoParams(const QString &answerSdp)
{
    // 浏览器会用 fmtp 里的 sprop-parameter-sets；舱端以前忽略，ffmpeg/mp4 经 SRS 时常只靠这个才有 SPS/PPS。
    const QRegularExpression re(QStringLiteral("a=fmtp:(\\d+)\\s+([^\\r\\n]+)"));
    auto it = re.globalMatch(answerSdp);
    QString sprop;
    while (it.hasNext()) {
        const QRegularExpressionMatch m = it.next();
        const QString fmtp = m.captured(2);
        const int idx = fmtp.indexOf(QStringLiteral("sprop-parameter-sets="));
        if (idx < 0) {
            continue;
        }
        sprop = fmtp.mid(idx + int(QStringLiteral("sprop-parameter-sets=").size()));
        const int semi = sprop.indexOf(';');
        if (semi >= 0) {
            sprop = sprop.left(semi);
        }
        break;
    }
    if (sprop.isEmpty()) {
        qWarning() << "[rtc] answer has no sprop-parameter-sets";
        return false;
    }

    const QStringList parts = sprop.split(',', Qt::SkipEmptyParts);
    for (const QString &part : parts) {
        const QByteArray nal = QByteArray::fromBase64(part.toLatin1());
        if (nal.isEmpty()) {
            continue;
        }
        cacheParameterSetNal(reinterpret_cast<const uint8_t *>(nal.constData()),
                             static_cast<size_t>(nal.size()));
    }

    if (m_cachedSps.empty() || m_cachedPps.empty()) {
        qWarning() << "[rtc] failed to parse sprop SPS/PPS";
        return false;
    }

    // 立即喂给解码器（open 之后改 extradata 不一定生效）
    {
        std::vector<uint8_t> boot;
        prependCachedParameterSets(boot);
        if (!boot.empty()) {
            decodeAnnexB(boot.data(), static_cast<int>(boot.size()));
            m_paramSetsInjected = true;
        }
    }

    qWarning() << "[rtc] loaded SPS/PPS from answer sprop, sps=" << m_cachedSps.size()
               << "pps=" << m_cachedPps.size();
    return true;
}

void RtcPlayer::decodeAnnexB(const uint8_t *data, int size)
{
    if (!m_codecCtx || !m_packet || !data || size <= 0) {
        return;
    }

    av_packet_unref(m_packet);
    if (av_new_packet(m_packet, size) < 0) {
        return;
    }
    std::memcpy(m_packet->data, data, static_cast<size_t>(size));

    int ret = avcodec_send_packet(m_codecCtx, m_packet);
    av_packet_unref(m_packet);
    if (ret < 0 && ret != AVERROR(EAGAIN)) {
        return;
    }

    while ((ret = avcodec_receive_frame(m_codecCtx, m_frame)) == 0) {
        emitDecodedFrame(m_frame);
        av_frame_unref(m_frame);
    }
}

void RtcPlayer::emitDecodedFrame(AVFrame *frame)
{
    if (!frame || !m_frameCallback) {
        return;
    }

    if (frame->width <= 0 || frame->height <= 0) {
        return;
    }

    // OpenGL 侧按 width*height 紧凑拷贝；这里必须输出 packed YUV420，避免 linesize>width 花屏。
    const int width = frame->width & ~1;
    const int height = frame->height & ~1;
    if (width <= 0 || height <= 0) {
        return;
    }

    if (m_yuvWidth != width || m_yuvHeight != height) {
        if (m_sws) {
            sws_freeContext(m_sws);
            m_sws = nullptr;
        }
        if (m_yuvBuffer) {
            av_free(m_yuvBuffer);
            m_yuvBuffer = nullptr;
        }

        m_yuvWidth = width;
        m_yuvHeight = height;
        m_yuvBufferSize = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, m_yuvWidth, m_yuvHeight, 1);
        m_yuvBuffer = static_cast<uint8_t *>(av_malloc(static_cast<size_t>(m_yuvBufferSize)));
        if (!m_yuvBuffer) {
            return;
        }
        av_image_fill_arrays(m_yuvFrame->data, m_yuvFrame->linesize, m_yuvBuffer,
                             AV_PIX_FMT_YUV420P, m_yuvWidth, m_yuvHeight, 1);

        m_sws = sws_getContext(frame->width, frame->height, static_cast<AVPixelFormat>(frame->format),
                               m_yuvWidth, m_yuvHeight, AV_PIX_FMT_YUV420P,
                               SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
        if (!m_sws) {
            return;
        }
    }

    sws_scale(m_sws,
              frame->data, frame->linesize,
              0, frame->height,
              m_yuvFrame->data, m_yuvFrame->linesize);

    // av_image_fill_arrays(..., align=1) 已保证三个 plane 紧凑排列。
    // DirectConnection 会在本函数返回前复制到 OpenGLWidget，无需每帧再分配和复制一份。
    m_frameCallback(m_yuvFrame->data[0],
                    m_yuvFrame->data[1],
                    m_yuvFrame->data[2],
                    static_cast<uint>(m_yuvWidth), static_cast<uint>(m_yuvHeight));
}

void RtcPlayer::reportError(const QString &message)
{
    qWarning() << "[rtc]" << message;
    if (m_errorCallback) {
        m_errorCallback(message);
    }
}
