/**
 *      @desc:  定时器内部类
 *      @author:jiacobi
 *      @date:  2020.2.9
 **/

#pragma once

#include <atomic>
#include <stdint.h>
#include "../base/TimeStamp.h"
#include "../net/Callbacks.h"

namespace net 
{
    class Timer
    {
    public:
        Timer(const TimerCallback& cb, TimeStamp when, int64_t interval, int64_t repeatCount = -1);           
        Timer(TimerCallback&& cb, TimeStamp when, int64_t interval);

        void run();        

        bool isCanceled() const
        {
            return canceled_;
        }

        void cancel(bool off)
        {
            canceled_ = off;
        }

        TimeStamp expiration() const { return expiration_; }
        int64_t getRepeatCount() const { return repeatCount_; }
        int64_t sequence() const { return sequence_; }

        //void restart(TimeStamp now);

        static int64_t numCreated() { return s_numCreated_; }

    private:
        //noncopyable
        Timer(const Timer& rhs) = delete;
        Timer& operator=(const Timer& rhs) = delete;

    private:
        const TimerCallback         callback_;
        TimeStamp                   expiration_;
        const int64_t               interval_;
        int64_t                     repeatCount_;       //重复次数，-1 表示一直重复下去
        const int64_t               sequence_;
        bool                        canceled_;          //是否处于取消状态

        static std::atomic<int64_t> s_numCreated_;
    }
}