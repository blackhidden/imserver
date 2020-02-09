/**
 *      @desc:  事件循环类
 *      @author:jiacobi
 *      @date:  2020.2.8
 **/

#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "../base/TimeStamp.h"
#include "../base/Platform.h"
#include "Callbacks.h"
#include "Sockets.h"
#include "TimerId.h"
#include "TimerQueue.h"

namespace net 
{
    class EventLoop;
    class Channel;
    class Poller;
    class CTimerHeap;

    class EventLoop
    {
    public:


    private:


    private:


    };
}