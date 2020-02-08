/**
 *      功能：聊天服务器入口函数
 *      作者：jiacobi
 *      日期：2020.2.7
 **/

#include <iostream>
#include <stdlib.h>

//#include "../base/Platform.h"  暂不考虑跨平台
#include "../base/Singleton.h"
#include "../base/ConfigFileReader.h"
#include "../base/AsyncLog.h"
#include "../net/EventLoop.h"
#include "../net/EventLoopThreadPool.h"
#include "../mysqlmgr/MysqlManager.h"


#include "UserManager.h"
#include "ChatServer.h"
#include "MonitorServer.h"
#include "HttpServer.h"

using namespace net;

EventLoop g_mainLoop;

int main(int argc, char* argv[])
{
    CConfigFileReader config("etc/chatserver.conf");

    const char* logbinarypackage = config.getConfigName("logbinarypackage");
    if (logbinarypackage != NULL)
    {
        int logbinarypackageint = atoi(logbinarypackage);
        if (logbinarypackageint != 0)
            Singleton<ChatServer>::Instance().enableLogPackageBinary(true);
        else
            Singleton<ChatServer>::Instance().enableLogPackageBinary(false);
    }
/*   
    std::string logFileFullPath;

    const char* logfilename = config.getConfigName("logfilename");
    logFileFullPath += logfilename;

#ifdef _DEBUG
    CAsyncLog::init();
#else
    CAsyncLog::init(logFileFullPath.c_str());
#endif
    
    //初始化数据库配置
    const char* dbserver = config.getConfigName("dbserver");
    const char* dbuser = config.getConfigName("dbuser");
    const char* dbpassword = config.getConfigName("dbpassword");
    const char* dbname = config.getConfigName("dbname");
    if (!Singleton<CMysqlManager>::Instance().init(dbserver, dbuser, dbpassword, dbname))
    {
        LOGF("Init mysql failed, please check your database config..............");
    }

    if (!Singleton<UserManager>::Instance().init(dbserver, dbuser, dbpassword, dbname))
    {
        LOGF("Init UserManager failed, please check your database config..............");
    }
*/
    const char* listenip = config.getConfigName("listenip");
    short listenport = (short)atol(config.getConfigName("listenport"));
    Singleton<ChatServer>::Instance().init(listenip, listenport, &g_mainLoop);
/*
    const char* monitorlistenip = config.getConfigName("monitorlistenip");
    short monitorlistenport = (short)atol(config.getConfigName("monitorlistenport"));
    const char* monitortoken = config.getConfigName("monitortoken");
    Singleton<MonitorServer>::Instance().init(monitorlistenip, monitorlistenport, &g_mainLoop, monitortoken);

    const char* httplistenip = config.getConfigName("monitorlistenip");
    short httplistenport = (short)atol(config.getConfigName("httplistenport"));
    Singleton<HttpServer>::Instance().init(httplistenip, httplistenport, &g_mainLoop);
*/
    LOGI("chatserver initialization completed, now you can use client to connect it.");

    g_mainLoop.loop();

    LOGI("exit chatserver.");

    return 0;
}