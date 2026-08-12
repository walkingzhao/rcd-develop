#ifndef AUDIODECODE_H
#define AUDIODECODE_H
#include <QAudioOutput>
#include <thread>
//仅支持qt5.0以上版本
class AudioDecode
{
public:
    AudioDecode(std::string url, int sampleRate, int sampleSize, int channelCount);
    ~AudioDecode();
    int initAudioDevice(std::string url, int sampleRate, int sampleSize, int channelCount);

    void startPlay();
    void pausePlay();
    void stopPlay();
private:
    void freeAudioDevice();
    QAudioOutput *audioOutput=nullptr;
    QIODevice* audioDevice;
    bool audioDeviceOk;
    int playFlag=1;
    std::string strUrl;
    int periodSize;
    std::thread audioThread;//=nullptr;

    std::string m_url;
    int m_sampleRate;
    int m_sampleSize;
    int m_channelCount;

};

#endif // AUDIODECODE_H
