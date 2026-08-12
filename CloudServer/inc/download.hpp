/**
 * @file download.hpp
 * @author lujiefeng
 * @brief 
 * @version 0.1
 * @date 2019-10-28
 * 
 * @copyright Copyright () 2019
 * 
 */
#ifndef _DOWNLOAD_H
#define _DOWNLOAD_H
#include <QDebug>
#include <cstdio>
#include <cstring>
#include <curl/curl.h>
#include <string>

//compile with -lcurl
class DownloadFile
{
public:
    DownloadFile()
    {
        fp = nullptr;
        curl_handle = curl_easy_init();
        curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl_handle, CURLOPT_NOSIGNAL, 1);
    }
    ~DownloadFile()
    {
        if (fp)
        {
            fflush(fp);
            fclose(fp);
//            std::system("sync");
        }
        curl_easy_cleanup(curl_handle);
    }
    bool openSaveFile(const char *filename)
    {
        fp = std::fopen(filename, "wb");
        if (!fp)
        {
             qDebug() << "openSaveFile:[" << filename << "] failed: " << std::strerror(errno);
            return false;
        }
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fp);
        qDebug() << "Create downloadFile[" << filename << "] Success:";
        return true;
    }

    bool downloadFromUrl(const char *url, long timeout)
    {
        qDebug() << "start downloadFromUrl:" << url;
        if (timeout > 0)
        {
            curl_easy_setopt(curl_handle, CURLOPT_CONNECTTIMEOUT, timeout);
        }
        if (url == nullptr)
        {
            qDebug() << "download failed : url is null!";
            return false;
        }
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);

        CURLcode res = curl_easy_perform(curl_handle);

        if (res != CURLE_OK)
        {
            qDebug() << "downloadFromUrl error,url:" << url
                        << " error msg:" << curl_easy_strerror(res);
            return false;
        }
        qDebug() << "downloadFile success :" << url;
        return true;
    }

    bool downloadFromUrl(const char *url)
    {
        return downloadFromUrl(url, -1);
    }

private:
    std::FILE *fp;
    CURL *curl_handle;
};

#endif
