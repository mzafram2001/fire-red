#include "global.h"
#include "rtc.h"
#include "main.h"

// GBA S-3511A RTC Registers
#define GPIO_PORT_DATA          (*(volatile u16 *)0x080000C4)
#define GPIO_PORT_DIRECTION     (*(volatile u16 *)0x080000C6)
#define GPIO_PORT_CONTROL       (*(volatile u16 *)0x080000C8)

#define RTC_PIN_SCK             0x01
#define RTC_PIN_SIO             0x02
#define RTC_PIN_CS              0x04

static void RtcDelay(void)
{
    volatile int i;
    for (i = 0; i < 10; i++);
}

static void RtcWriteByte(u8 value)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        u8 bit = (value >> i) & 1;
        GPIO_PORT_DATA = (bit ? RTC_PIN_SIO : 0);
        RtcDelay();
        GPIO_PORT_DATA = (bit ? RTC_PIN_SIO : 0) | RTC_PIN_SCK;
        RtcDelay();
    }
}

static u8 RtcReadByte(void)
{
    u8 value = 0;
    int i;
    for (i = 0; i < 8; i++)
    {
        GPIO_PORT_DATA = 0;
        RtcDelay();
        GPIO_PORT_DATA = RTC_PIN_SCK;
        RtcDelay();
        if (GPIO_PORT_DATA & RTC_PIN_SIO)
            value |= (1 << i);
    }
    return value;
}

static u8 BcdToBin(u8 val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

void RtcInit(void)
{
    GPIO_PORT_CONTROL = 1;
    GPIO_PORT_DIRECTION = RTC_PIN_SCK | RTC_PIN_SIO | RTC_PIN_CS;
    GPIO_PORT_DATA = 0;
}

void RtcGetTime(struct SiiRtcInfo *rtc)
{
    u8 rawData[7];
    int i;

    // Fallback based on play time hours if RTC is disabled or not present
    rtc->year = 26;
    rtc->month = 1;
    rtc->day = 1;
    rtc->dayOfWeek = 0;
    rtc->hour = (gSaveBlock2Ptr != NULL) ? (gSaveBlock2Ptr->playTimeHours % 24) : 12;
    rtc->minute = (gSaveBlock2Ptr != NULL) ? gSaveBlock2Ptr->playTimeMinutes : 0;
    rtc->second = (gSaveBlock2Ptr != NULL) ? gSaveBlock2Ptr->playTimeSeconds : 0;
    rtc->status = 0;

    // Enable GPIO access to RTC
    GPIO_PORT_CONTROL = 1;
    GPIO_PORT_DIRECTION = RTC_PIN_SCK | RTC_PIN_SIO | RTC_PIN_CS;

    // S-3511A Command: Read Date & Time (0x65)
    GPIO_PORT_DATA = RTC_PIN_CS | RTC_PIN_SCK;
    RtcDelay();

    RtcWriteByte(0x65);

    // Switch SIO pin to input
    GPIO_PORT_DIRECTION = RTC_PIN_SCK | RTC_PIN_CS;
    RtcDelay();

    for (i = 0; i < 7; i++)
        rawData[i] = RtcReadByte();

    // End communication: CS Low
    GPIO_PORT_DIRECTION = RTC_PIN_SCK | RTC_PIN_SIO | RTC_PIN_CS;
    GPIO_PORT_DATA = 0;
    RtcDelay();

    // Validate BCD hour (< 24) and minute (< 60)
    if ((rawData[4] & 0x80) == 0 && (rawData[4] & 0x3F) <= 0x23 && (rawData[5] & 0x7F) <= 0x59)
    {
        rtc->year = BcdToBin(rawData[0]);
        rtc->month = BcdToBin(rawData[1] & 0x1F);
        rtc->day = BcdToBin(rawData[2] & 0x3F);
        rtc->dayOfWeek = rawData[3] & 0x07;
        rtc->hour = BcdToBin(rawData[4] & 0x3F);
        rtc->minute = BcdToBin(rawData[5] & 0x7F);
        rtc->second = BcdToBin(rawData[6] & 0x7F);
    }
}

u8 GetTimeOfDay(void)
{
    struct SiiRtcInfo rtc;
    RtcGetTime(&rtc);

    if (rtc.hour >= 5 && rtc.hour < 10)
        return TIME_MORNING; // 05:00 - 09:59 (soft warm sunrise)
    else if (rtc.hour >= 10 && rtc.hour < 17)
        return TIME_DAY;     // 10:00 - 16:59 (standard daylight)
    else if (rtc.hour >= 17 && rtc.hour < 20)
        return TIME_SUNSET;  // 17:00 - 19:59 (golden dusk)
    else
        return TIME_NIGHT;   // 20:00 - 04:59 (deep blue nocturnal)
}
