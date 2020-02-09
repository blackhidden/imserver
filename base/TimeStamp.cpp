/**
 *      @desc:  时间戳类
 *      @author:jiacobi
 *      @date:  2020.2.8
 **/

#include "TimeStamp.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdio.h>

static_assert(sizeof(TimeStamp) == sizeof(int64_t), "sizeof(TimeStamp) error");

TimeStamp::TimeStamp(int64_t microSecondsSinceEpoch)
: microSecondsSinceEpoch_(microSecondsSinceEpoch)
{
}

string TimeStamp::toString() const
{
    char buf[64] = { 0 };
    int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
    int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
    snprintf(buf, sizeof(buf)-1, "%lld.%06lld", (long long int)seconds, (long long int)microseconds);
    return buf;
}

string TimeStamp::toFormattedString(bool showMicroseconds) const
{
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
	struct tm tm_time;
	struct tm *ptm;
	ptm = localtime(&seconds);
	tm_time = *ptm;

	char buf[32] = { 0 };

	if (showMicroseconds)
	{
		int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
		snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
			tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
			microseconds);
	}
	else
	{
		snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
			tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
	}
	
	return buf;
}

TimeStamp TimeStamp::now()
{
	chrono::time_point<chrono::system_clock, chrono::microseconds> now = chrono::time_point_cast<chrono::microseconds>(
		chrono::system_clock::now());

	int64_t microSeconds = now.time_since_epoch().count();
	TimeStamp time(microSeconds);
	return time;
}

TimeStamp TimeStamp::invalid()
{
	return TimeStamp();
}