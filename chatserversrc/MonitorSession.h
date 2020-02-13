/**
 *      @desc:  监控会话类
 *      @author:jiacobi
 *      @date:  2020.2.13
 **/

#pragma once

#include "../net/Buffer.h"
#include "../base/TimeStamp.h"
#include "../net/TcpConnection.h"
#include <memory>

using namespace net;

class MonitorSession
{
public:
    MonitorSession(std::shared_ptr<TcpConnection>& conn);
    ~MonitorSession() = default;
    MonitorSession(const MonitorSession& rhs) = delete;
    MonitorSession& operator =(const MonitorSession& rhs) = delete;

public:
    //有数据可读, 会被多个工作loop调用
    void onRead(const std::shared_ptr<TcpConnection>& conn, Buffer* pBuffer, TimeStamp receivTime);

    std::shared_ptr<TcpConnection> getConnectionPtr()
    {
        if (m_tmpConn.expired())
            return NULL;

        return m_tmpConn.lock();
    }

    void showHelp();
    void send(const char* data, size_t length);

private:
    bool process(const std::shared_ptr<TcpConnection>& conn, const std::string& inbuf);
    bool showOnlineUserList(const std::string& token = "");
    bool showSpecifiedUserInfoByID(int32_t userid);

private:
    std::weak_ptr<TcpConnection>       m_tmpConn;
};