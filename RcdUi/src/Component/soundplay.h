#ifndef SOUNDPLAY_H
#define SOUNDPLAY_H
#include <QQueue>
#include <QMutex>
#include <QTimer>
#include <QTextToSpeech>
#include <QMediaPlayer>
/*
语音报警分为5个优先级：一级故障>异常信息>二级故障>三级故障>提示信息。其中前4个优先级来自128bit 主控报警信息
原则如下：
1.      同一时刻，只报优先级最高的语音
2.      某时刻，只有4个提示信息，那么这4个提示信息要挨个报。其他优先级语音信息同理。
3.      假如第2种情况下，报第一个语音的过程中，来了1个一级故障(假如只来一次)，则抹掉3个提示信息，报完一次一级故障的语音后，语音播报结束
4.      语音播报周期5s~8s
 */
class SoundPlay : public QObject
{

#define MAX_SOUND_LEVEL 5
#define SOUND_LEVEL_1           0
#define SOUND_LEVEL_ABNORMAL    1
#define SOUND_LEVEL_2           2
#define SOUND_LEVEL_3           3
#define SOUND_LEVEL_TIP         4

    Q_OBJECT
public:

    static SoundPlay *instance();
    void addSound(int,QString);//优先级，语音文件
public slots:
    void playSound();//从soundStore中挑出要播放的文件，并播放
private:
    SoundPlay(QObject *parent=nullptr);
    QQueue<QString> soundStore[MAX_SOUND_LEVEL];
    static SoundPlay *handle;
    static QMutex soundPlayMutex;
    QTimer *soundPlayTimer;

    int count=0;
private:
    bool inQueue(QQueue<QString> q,QString str);
//    QTextToSpeech *tts;
    QMediaPlayer * player;
};

#endif // SOUNDPLAY_H
