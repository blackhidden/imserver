/**
 *      @desc:  定时器标识符
 *      @author:jiacobi
 *      @date:  2020.2.9
 **/

#pragma once

namespace net
{
    class Timer;

    class TimerId
    {
    public:
        TimerId() : timer_(NULL), sequence_(0) {}
        TimerId(Timer *timer, int64_t seq) : timer_(timer), sequence_(seq) {}

        Timer* getTimer() { return timer_; }

        friend class TimerQueue;

    private:
        Timer*  timer_;
        int64_t sequence_;

    }
}