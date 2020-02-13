/**
 *      @desc:  HTTP服务器类
 *      @author:jiacobi
 *      @date:  2020.2.13
 **/

#pragma once

#include <memory>
#include <mutex>
#include <list>
#include "../net/EventLoop.h"
#include "../net/TcpServer.h"

using namespace net;

class HttpSession;

class HttpServer final
{
public:
    HttpServer() = default;
    ~HttpServer() = default;

    HttpServer(const HttpServer& rhs) = delete;
    HttpServer& operator=(const HttpServer& rhs) = delete;

public:
    bool init(const char* ip, short port, EventLoop* loop);
    void uninit();
    //新连接到来调用或连接断开，所以需要通过conn->connected()来判断，一般只在主loop里面调用
    void onConnected(std::shared_ptr<TcpConnection> conn);
    //连接断开
    void onDisconnected(const std::shared_ptr<TcpConnection>& conn);

private:
    std::unique_ptr<TcpServer>                  m_server;
    std::list<std::shared_ptr<HttpSession>>     m_sessions;
    std::mutex                                  m_sessionMutex;//多线程之间保护m_sessions
};