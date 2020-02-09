/**
 *      @desc:  聊天服务器类
 *      @author:jiacobi
 *      @date:  2020.2.9
 **/

#pragma once

#include <memory>
#include <list>
#include <map>
#include <mutex>
#include <atomic>
#include "../net/TcpServer.h"
#include "../net/EventLoop.h"
#include "ChatSession.h"

