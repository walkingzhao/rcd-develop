#include "hikvisioncamera.h"
#include "HttpUtil.h"
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "public/jsonMethord.h"
#include <QApplication>
HikvisionCamera* HikvisionCamera::handle = nullptr;
QMutex HikvisionCamera::handleMutex;
QMutex HikvisionCamera::getCameraMutex;
HikvisionCamera::HikvisionCamera()
{
    m_CameraList = QByteArray();


    QVariant cameraServerMap= jsonMethord::getInstance()
            ->readJson(QApplication::applicationDirPath()+"/rcdconfig.json","CameraServer");
    if(cameraServerMap.toList().isEmpty())
    {
        qDebug()<<"rcdconfig.json can't find camera key";
        return;
    }
    artemisIp   = cameraServerMap.toList()[0].toMap().value("artemisIp").toString().toStdString();
    appKey      = cameraServerMap.toList()[0].toMap().value("appKey").toString().toStdString();
    appSecret   = cameraServerMap.toList()[0].toMap().value("appSecret").toString().toStdString();


//    artemisIp = "https://192.168.30.150:443";
//    appKey = "26476177";
//    appSecret = "FqmfU4WIMLQxU1bpvQLF";
    cameraListEnd ="/artemis/api/resource/v1/cameras";
    cameraUrlEnd ="/artemis/api/video/v2/cameras/previewURLs";
    cameraListSzBody = "{\"pageNo\":1,\"pageSize\":1000}";
    /*
{
  "pageNo": 1,
  "pageSize": 100
}
     */
    getCameraList();
}

HikvisionCamera *HikvisionCamera::instance()
{
    if(handle == nullptr) {
        QMutexLocker locker(&handleMutex);
        if(handle == nullptr) {
            handle = new HikvisionCamera();
        }
    }
    return handle;
}

void HikvisionCamera::getCameraList()
{
    QMutexLocker locker(&getCameraMutex);
    if(!isEmptyCameraList())return;
    int dataLen = 0;
    QByteArray ret=QByteArray();
    char* data = httpUtil::HTTPUTIL_Post((artemisIp+cameraListEnd).c_str(),
                               cameraListSzBody.c_str(),
                               appKey.c_str(), appSecret.c_str(), 2000, &dataLen);
    if (NULL == data)
    {
        qDebug() << "getCameraList fail, status is " << httpUtil::HTTPUTIL_GetLastStatus();
    }
    else
    {
        qDebug()<<"getCameraList:"<<data;
        m_CameraList = QByteArray(data);
        httpUtil::HTTPUTIL_Free(data);
    }
}

bool HikvisionCamera::isEmptyCameraList()
{
    return m_CameraList.isEmpty();
}

QString HikvisionCamera::getCameraUrl(QString name)
{
    if(isEmptyCameraList())
    {
        getCameraList();
        if(isEmptyCameraList())
            return "";
    }
    //1.获取cameraIndexCode
    /*
    {
      "code": "0",
      "msg": "success",
      "data": {
        "total": 6,
        "pageNo": 1,
        "pageSize": 1000,
        "list": [
          {
            "altitude": null,
            "cameraIndexCode": "9d8c311b2e2542c3a74333bba829387e",
            "cameraName": "左侧",
            "cameraType": 0,
            "cameraTypeName": "枪机",
            "capabilitySet": "event_gps,event_vss,io,vss,record,ptz,remote_vss,maintenance,event_device,status",
            "capabilitySetName": "GPS事件能力,视频事件能力,IO能力,视频能力,录像能力,云台能力,视频设备远程获取能力,设备维护能力,设备事件能力,状态能力",
            "intelligentSet": null,
            "intelligentSetName": null,
            "channelNo": "1",
            "channelType": "analog",
            "channelTypeName": "模拟通道",
            "createTime": "2021-11-11T16:04:09.081+08:00",
            "encodeDevIndexCode": "0991f0efec834e98a73d26390b0678a1",
            "encodeDevResourceType": null,
            "encodeDevResourceTypeName": null,
            "gbIndexCode": null,
            "installLocation": null,
            "keyBoardCode": null,
            "latitude": null,
            "longitude": null,
            "pixel": null,
            "ptz": null,
            "ptzName": null,
            "ptzController": null,
            "ptzControllerName": null,
            "recordLocation": null,
            "recordLocationName": null,
            "regionIndexCode": "root000000",
            "status": null,
            "statusName": null,
            "transType": 0,
            "transTypeName": "UDP",
            "treatyType": null,
            "treatyTypeName": null,
            "viewshed": null,
            "updateTime": "2021-11-11T16:07:59.807+08:00"
          },
          {
            "altitude": null,
            "cameraIndexCode": "847fbdd9af2b41f69e9416393de067e3",
            "cameraName": "右侧",
            "cameraType": 0,
            "cameraTypeName": "枪机",
            "capabilitySet": "event_gps,event_vss,io,vss,record,ptz,remote_vss,maintenance,event_device,status",
            "capabilitySetName": "GPS事件能力,视频事件能力,IO能力,视频能力,录像能力,云台能力,视频设备远程获取能力,设备维护能力,设备事件能力,状态能力",
            "intelligentSet": null,
            "intelligentSetName": null,
            "channelNo": "1",
            "channelType": "analog",
            "channelTypeName": "模拟通道",
            "createTime": "2021-11-11T16:05:28.913+08:00",
            "encodeDevIndexCode": "4f6cb73a841a4f37ab9e9f096004435e",
            "encodeDevResourceType": null,
            "encodeDevResourceTypeName": null,
            "gbIndexCode": null,
            "installLocation": null,
            "keyBoardCode": null,
            "latitude": null,
            "longitude": null,
            "pixel": null,
            "ptzName": null,
            "ptzController": null,
            "ptzControllerName": null,
            "recordLocation": null,
            "recordLocationName": null,
            "regionIndexCode": "root000000",
            "status": null,
            "statusName": null,
            "transType": 0,
            "transTypeName": "UDP",
            "treatyType": null,
            "treatyTypeName": null,
            "viewshed": null,
            "updateTime": "2021-11-11T16:07:59.744+08:00"
          }
        ]
      }
    }
    */
    QString l_cameraIndex="";
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(m_CameraList.toStdString().c_str(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        if (doucment.isObject()) { // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 data
                QJsonValue value = object.value("data");  // 获取指定 data 对应的 value
                QJsonValue msgValue = object.value("msg");

                if((!msgValue.isString())||(msgValue.toString() != "success"))
                    return "";

                if (value.isObject()) {  // 判断 value 是否为json object
                    QJsonObject dataobject = value.toObject();  // 转化为对象
                    if(dataobject.contains("list"))
                    {
                        QJsonValue listvalue = dataobject.value("list");  // 获取指定 key 对应的 value
                        if(listvalue.isArray())
                        {
                            QJsonArray array = listvalue.toArray();
                            int nSize = array.size();
                            for(int i = 0;i < nSize; i++)
                            {
                                QJsonValue cameraValue = array.at(i);
                                if(cameraValue.isObject())
                                {
                                    QJsonObject cameraObject = cameraValue.toObject();
                                    if(cameraObject.contains("cameraName")&&cameraObject.contains("cameraIndexCode"))
                                    {
                                        QJsonValue cameraNameValue = cameraObject.value("cameraName");
                                        QJsonValue cameraIndexCode = cameraObject.value("cameraIndexCode");
                                        if(cameraIndexCode.isString()&&cameraNameValue.isString())
                                        {
                                            QString nameStr = cameraNameValue.toString();
                                            QString cameraIndexCodeStr = cameraIndexCode.toString();
                                            if(nameStr==name)
                                            {
//                                                qDebug()<<"get cameraIndexCode:"<<nameStr<<cameraIndexCodeStr;
                                                l_cameraIndex = cameraIndexCodeStr;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(l_cameraIndex == "")
        return "";
    //2.拼装json post字串
    QJsonObject json;
    json.insert("cameraIndexCode", l_cameraIndex.toStdString().c_str());
    json.insert("streamType",0);
    json.insert("protocol", "rtsp");
    json.insert("streamform","rtp");
    json.insert("expand", "transcode=1&resolution=720P");
    QJsonDocument document;
    document.setObject(json);
    QByteArray array = document.toJson(QJsonDocument::Compact);

    //发送json请求url
    QByteArray l_urlJson;
    int dataLen = 0;
    char* data = httpUtil::HTTPUTIL_Post((artemisIp+cameraUrlEnd).c_str(),
                               array.data(),
                               appKey.c_str(), appSecret.c_str(), 2000, &dataLen);
    if (NULL == data)
    {
        qDebug() << "getCameraUrl fail, status is " << httpUtil::HTTPUTIL_GetLastStatus();
        return "";
    }
    else
    {
        l_urlJson = QByteArray(data);
        httpUtil::HTTPUTIL_Free(data);
    }

    //3.解析返回json字串
    /*
    {
      "code": "0",
      "msg": "success",
      "data": {
        "url": "rtsp://192.168.30.150:554/openUrl/zQ9JDJm"
      }
    }
    */
    doucment = QJsonDocument::fromJson(l_urlJson.toStdString().c_str(), &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        if (doucment.isObject()) { // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("data")) {  // 包含指定的 data
                QJsonValue dataValue = object.value("data");  // 获取指定 data 对应的 value
                QJsonValue msgValue = object.value("msg");

                if((!msgValue.isString())||(msgValue.toString() != "success"))
                    return "";

                if (dataValue.isObject()) {  // 判断 value 是否为json object
                    QJsonObject dataobject = dataValue.toObject();  // 转化为对象
                    if(dataobject.contains("url"))
                    {
                        QJsonValue urlvalue = dataobject.value("url");  // 获取指定 key 对应的 value
                        if(urlvalue.isString())
                        {
                            return urlvalue.toString();
                        }
                    }
                }
            }
        }
    }
    return "";
}
