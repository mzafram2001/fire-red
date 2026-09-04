#ifndef GUARD_RTC_H
#define GUARD_RTC_H

#include "global.h"

struct SiiRtcInfo
{
    u8 year;
    u8 month;
    u8 day;
    u8 dayOfWeek;
    u8 hour;
    u8 minute;
    u8 second;
    u8 status;
};

#define TIME_MORNING  0
#define TIME_DAY      1
#define TIME_SUNSET   2
#define TIME_NIGHT    3

void RtcInit(void);
void RtcGetTime(struct SiiRtcInfo *rtc);
u8 GetTimeOfDay(void);

#endif // GUARD_RTC_H
