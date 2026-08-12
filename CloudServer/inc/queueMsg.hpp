/**
 * @file queueMsg.h
 * @author lujiefeng
 * @brief
 * @version 0.1
 * @date 2019-06-14
 *
 * @copyright Copyright () 2019
 *
 */
#ifndef _QUEUEMSG_H
#define _QUEUEMSG_H

#include <condition_variable>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <queue>

typedef enum {
    PeriodicPlatformMsgType = 0,
    BusinessPlatformMsgType = 1
}QueueMsgType;

typedef struct
{
    QueueMsgType msgType;
    uint16_t msgDataLen;
    uint8_t msgData[4096];
} QueueMsgST;

class QueueMsg
{
private:
    std::queue<QueueMsgST> msgQueue;
    std::mutex cvLock;
    std::condition_variable cv;

public:
    bool pushMsgToQueue(const uint8_t *msgData, uint16_t msgDataLen, QueueMsgType msgtype = BusinessPlatformMsgType)
    {
        QueueMsgST tempMsg;
        tempMsg.msgType = msgtype;
        tempMsg.msgDataLen = msgDataLen;
        std::memmove(tempMsg.msgData, msgData, msgDataLen);
        cvLock.lock();
        msgQueue.push(tempMsg);
        cvLock.unlock();
        cv.notify_all();
        return true;
    }

    bool pushMsgToQueue(QueueMsgST &tempMsg) {
        cvLock.lock();
        msgQueue.push(tempMsg);
        cvLock.unlock();
        cv.notify_all();
        return true;
    }

    bool popMsgFromQueue(QueueMsgST &ret)
    {
        std::unique_lock<std::mutex> lk(cvLock);
        cv.wait(lk, [this] { return !msgQueue.empty(); });
        ret = msgQueue.front();
        msgQueue.pop();
        lk.unlock();
        return true;
    }
};

#endif
