#ifndef HIKVISIONCAMERA_H
#define HIKVISIONCAMERA_H
#include <string>
#include <QByteArray>
#include <QMutex>
class HikvisionCamera
{
public:
    HikvisionCamera();
    static HikvisionCamera *instance();
    void getCameraList();
    bool isEmptyCameraList();
    QString getCameraUrl(QString name);

private:
    std::string artemisIp;              // 平台的ip地址（必填
    std::string appKey;                 // 密钥的appKey（必填）
    std::string appSecret;              // 密钥的appSecret（必填）
    std::string cameraListEnd;
    std::string cameraListSzBody;
    std::string cameraUrlEnd;
    std::string cameraUrlSzBody;
    std::string cameraUrl;
    QByteArray  m_CameraList;
    static HikvisionCamera *handle;
    static QMutex handleMutex;
    static QMutex getCameraMutex;
};

#endif // HIKVISIONCAMERA_H
