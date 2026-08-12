#include "soundplay.h"
SoundPlay *SoundPlay::handle=nullptr;
QMutex SoundPlay::soundPlayMutex;
SoundPlay *SoundPlay::instance()
{
    if(handle == nullptr) {
        QMutexLocker locker(&soundPlayMutex);
        if(handle == nullptr) {
            handle = new SoundPlay();
        }
    }
    return handle;
}

void SoundPlay::addSound(int level, QString str)
{
    for(int i=0;i<level;i++)
    {
        if(!soundStore[i].isEmpty())//存在优先级更高的语音
            return;
    }
    if(!inQueue(soundStore[level],str))//语音不在队列里面
        soundStore[level].push_back(str);
    for(int i=level+1;i<MAX_SOUND_LEVEL;i++)//清除低优先级语音
        soundStore[i].clear();
}

void SoundPlay::playSound()
{
    if(count>0)
    {
        count--;
        return;
    }
    int i;
    for(i=0;i<MAX_SOUND_LEVEL;i++)
    {
        if(!soundStore[i].isEmpty())//有待报警的语音
            break;
    }

    //向网关发送语音报警报文
    if(i != MAX_SOUND_LEVEL)
    {
//        tts->say(soundStore[i].head());

        player->setMedia(QUrl(soundStore[i].head()));
        player->play();

        soundStore[i].pop_front();
        count=50;
    }
}

SoundPlay::SoundPlay(QObject *parent) : QObject(parent)
{
//    tts = new QTextToSpeech(this);
    player = new QMediaPlayer;
    for(int i = 0;i<MAX_SOUND_LEVEL;i++)
        soundStore[i].clear();
    soundPlayTimer = new QTimer;
    soundPlayTimer->setInterval(100);
    connect(soundPlayTimer,SIGNAL(timeout()),this,SLOT(playSound()));
    soundPlayTimer->start();//6s报一次
    count=0;


}

bool SoundPlay::inQueue(QQueue<QString> q, QString str)
{
    for(auto &it:q)
    {
        if(it==str)
            return true;
    }
    return false;
}


