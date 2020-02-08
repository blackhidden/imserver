/**
 *      功能：时间类
 *      作者：jiacobi
 *      日期：2020.2.8
 **/

#pragma once

#include <stdint.h>
#include <algorithm>
#include <string>

using namespace std;

class TimeStamp 
{
public:
    TimeStamp() : microSecondsSinceEpoch_(0) {}

    explicit TimeStamp(int64_t microSecondsSinceEpoch_);

    TimeStamp& operator+=(TimeStamp lhs) {
        this->microSecondsSinceEpoch_ += lhs.microSecondsSinceEpoch_;
        return *this;
    }
    TimeStamp& operator+=(int64_t lhs) {
        this->microSecondsSinceEpoch_ += lhs;
        return *this;
    }

    TimeStamp& operator-=(TimeStamp lhs) {
        this->microSecondsSinceEpoch_ -= lhs.microSecondsSinceEpoch_;
        return *this;
    }
    TimeStamp& operator-=(int64_t lhs) {
        this->microSecondsSinceEpoch_ -= lhs;
        return *this;
    }

    void swap(TimeStamp& that) {
        std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
    }

    string toString() const;
    string toFormattedString(bool showMicroseconds = true) const;
    bool valid() const { return microSecondsSinceEpoch_ > 0; };

    int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
    time_t secondsSinceEpoch() const {
        return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    }

    static TimeStamp now();
    static TimeStamp invalid();
    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t microSecondsSinceEpoch_;
};

inline bool operator<(TimeStamp lhs, TimeStamp rhs) 
{
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator>(TimeStamp lhs, TimeStamp rhs) 
{
    return rhs < lhs;
}

inline bool operator<=(TimeStamp lhs, TimeStamp rhs) 
{
    return !(lhs > rhs);
}

inline bool operator>=(TimeStamp lhs, TimeStamp rhs) 
{
    return !(lhs < rhs);
}

inline bool operator==(TimeStamp lhs, TimeStamp rhs) 
{
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline bool operator!=(TimeStamp lhs, TimeStamp rhs) 
{
    return !(lhs == rhs);
}

inline double timeDifference(TimeStamp high, TimeStamp low) 
{
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return static_cast<double>(diff) / TimeStamp::kMicroSecondsPerSecond;
}

inline TimeStamp addTime(TimeStamp timeStamp, int64_t microseconds) 
{
    return TimeStamp(timeStamp.microSecondsSinceEpoch() + microseconds);
}