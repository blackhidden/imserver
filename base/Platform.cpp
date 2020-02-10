/**
 *      @desc:  平台相关头文件
 *      @author:jiacobi
 *      @date:  2020.2.10
 **/

#include "Platform.h"

#ifdef WIN32

NetworkInitializer::NetworkInitializer()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    ::WSAStartup(wVersionRequested, &wsaData);   
}

NetworkInitializer::~NetworkInitializer()
{
    ::WSACleanup();
}

#endif