/**
 * @file zmqwrap.hpp
 * @author lujiefeng
 * @brief compile whit -lzmq -lpthread -std=c++17
 * @version 0.1
 * @date 2020-08-20
 * 
 * @copyright Copyright () 2020
 * 
 */

#pragma once

#include "zmqtopic.hpp"
#include <atomic>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <functional>
#include <map>
#include <mutex>
#include <thread>
#include <vector>
#include <zmq.hpp>
#include <zmq_addon.hpp>

#define ZMQ_ADDR_UI "ipc://@UIPub"
#define ZMQ_ADDR_CONTROL "ipc://@ControlPub"
#define ZMQ_ADDR_Gateway "ipc://@GatewayPub"
#define ZMQ_ADDR_CLOUDSERVER "ipc://@CloudServerPub"

#define DISALLOW_COPY_AND_ASSIGN(classname) \
    classname(const classname &) = delete;  \
    classname &operator=(const classname &) = delete;

class ZmqContext
{
public:
    static ZmqContext *Instance()
    {
        static ZmqContext *ptr = nullptr;
        if (ptr == nullptr)
        {
            static std::once_flag flag;
            std::call_once(flag, [&]() { ptr = new ZmqContext(); });
        }
        return ptr;
    }
    zmq::context_t &GetContext()
    {
        return ctx;
    }

    ~ZmqContext() {}

private:
    zmq::context_t ctx;
    ZmqContext() {}
    DISALLOW_COPY_AND_ASSIGN(ZmqContext)
};

#define ZmqContextRef() ZmqContext::Instance()->GetContext()

class ZmqPublisher
{
public:
    ZmqPublisher(const std::string &addr)
    {
        // EADDRINUSE: ipc://@Name still held by a live or recently dead process — retry briefly, then fail with hint.
        constexpr int kMaxAttempts = 12;
        constexpr int kDelayMs = 250;
        for (int attempt = 0; attempt < kMaxAttempts; ++attempt) {
            try {
                pubSocket = zmq::socket_t(ZmqContextRef(), zmq::socket_type::pub);
                pubSocket.bind(addr);
                return;
            } catch (const zmq::error_t &e) {
                const int err = e.num();
                const bool last = (attempt + 1 >= kMaxAttempts);
                if (err != EADDRINUSE || last) {
                    std::fprintf(stderr,
                                 "[ZMQ] bind failed: %s\n"
                                 "  what(): %s  errno=%d\n"
                                 "  If errno=%d (EADDRINUSE / 地址已在使用), another copy of RCD/Gateway/Control still holds this IPC.\n"
                                 "  Try: pkill -9 RCD GatewayServer Control; sleep 1; ./RCD.sh\n",
                                 addr.c_str(), e.what(), err, EADDRINUSE);
                    throw;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(kDelayMs));
            }
        }
    }
    ~ZmqPublisher() {}

    int Publish(const std::string &topic, const void *data, int len)
    {
        std::vector<zmq::const_buffer> pubMsg;
        pubMsg.push_back(zmq::buffer(topic));
        pubMsg.push_back(zmq::const_buffer(data, len));
        auto result = zmq::send_multipart(pubSocket, pubMsg);
        return result.has_value() ? result.value() : 0;
    }

private:
    zmq::socket_t pubSocket;
};

/*
* Topic handle CallBack Func . (std::string &topic,const void * data,int dataLen)
*/
using TopicCbFunc = std::function<void(std::string &, const void *, int)>;

class ZmqSubscriber
{
public:
    ZmqSubscriber()
    {
        subSocket = zmq::socket_t(ZmqContextRef(), zmq::socket_type::sub);
        // 让 recv 周期性返回，保证析构时能 join 成功；否则进程 a.exec() 返回之后 ps 里还能看到，
        // 就是因为接收线程一直阻塞在 zmq_msg_recv 导致主线程 pthread_join 死等。
        subSocket.set(zmq::sockopt::rcvtimeo, 200);
        subSocket.set(zmq::sockopt::linger, 0);
        m_stop.store(false);
        recvMsgThread = std::thread(&ZmqSubscriber::RecvZmqMessage, this);
    }
    ~ZmqSubscriber()
    {
        m_stop.store(true);
        try {
            subSocket.close();
        } catch (...) {
        }
        if (recvMsgThread.joinable()) {
            recvMsgThread.join();
        }
    }

    /*
    * Connect To Publisher. called before Subscribe topic
    * you can connect to multiple publishers
    */
    void ConnectTo(const std::string &addr)
    {
        subSocket.connect(addr);
    }

    void SubscribeAll(TopicCbFunc func)
    {
        subSocket.set(zmq::sockopt::subscribe, "");
        allTopicCbFunc = func;
    }

    void Subscribe(const std::string &topic, TopicCbFunc func)
    {
        subSocket.set(zmq::sockopt::subscribe, topic);
        cbFuncMap.insert_or_assign(topic, std::move(func));
    }

    void UnSubscribeAll()
    {
        for (auto &it : cbFuncMap)
        {
            subSocket.set(zmq::sockopt::unsubscribe, it.first);
        }
        allTopicCbFunc = nullptr;
    }

    void UnSubscribe(const std::string &topic)
    {
        subSocket.set(zmq::sockopt::unsubscribe, topic);
    }

private:
    void RecvZmqMessage()
    {
        while (!m_stop.load())
        {
            try
            {
                std::vector<zmq::message_t> recvMsg;
                auto ret = zmq::recv_multipart(subSocket, std::back_inserter(recvMsg));
                if (!ret.has_value()) {
                    continue;
                }
                if (recvMsg.size() == 2)
                {
                    try
                    {
                        std::string topic = recvMsg.at(0).to_string();
                        TopicCbFunc tmpFunc = allTopicCbFunc != nullptr ? allTopicCbFunc : cbFuncMap.at(topic);
                        tmpFunc(topic, recvMsg.at(1).data(), recvMsg.at(1).size());
                    }
                    catch (...)
                    {
                        // callback / topic dispatch errors should not stop recv thread
                    }
                }
            }
            catch (const zmq::error_t &e)
            {
                const int n = e.num();
                if (n == ETERM || n == ENOTSOCK || n == EINTR || n == EAGAIN) {
                    if (m_stop.load() || n == ETERM || n == ENOTSOCK) {
                        break;
                    }
                }
            }
            catch (...)
            {
            }
        }
    }

private:
    zmq::socket_t subSocket;
    TopicCbFunc allTopicCbFunc;
    std::map<std::string, TopicCbFunc> cbFuncMap;
    std::atomic<bool> m_stop{false};
    std::thread recvMsgThread;
};