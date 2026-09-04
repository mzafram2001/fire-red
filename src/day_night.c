#include "global.h"
#include "day_night.h"
#include "rtc.h"
#include "overworld.h"
#include "fieldmap.h"
#include "event_object_movement.h"
#include "palette.h"

static EWRAM_DATA u8 sLastTimeOfDay = 0xFF;

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

void ApplyDayNightTint(u16 *palette, u16 count)
{
    u8 timeOfDay;
    s32 r, g, b;
    u16 i;
    u16 rScale, gScale, bScale;

    // Do not tint inside buildings, gyms, caves, or during Quest Log playback
    if (!IsMapTypeOutdoors(gMapHeader.mapType))
        return;

    timeOfDay = GetTimeOfDay();
    if (timeOfDay == TIME_DAY)
        return; // Normal daytime needs no tint

    switch (timeOfDay)
    {
    case TIME_MORNING: // Warm golden sunrise (05:00 - 09:59)
        rScale = 256;
        gScale = 236;
        bScale = 200;
        break;
    case TIME_SUNSET: // Rich orange dusk (17:00 - 19:59)
        rScale = 256;
        gScale = 180;
        bScale = 140;
        break;
    case TIME_NIGHT: // Cool deep blue nocturnal moonlight (20:00 - 04:59)
    default:
        rScale = 120;
        gScale = 145;
        bScale = 225;
        break;
    }

    for (i = 0; i < count; i++)
    {
        r = GET_R(palette[i]);
        g = GET_G(palette[i]);
        b = GET_B(palette[i]);

        r = (r * rScale) >> 8;
        g = (g * gScale) >> 8;
        b = (b * bScale) >> 8;

        if (r > 31) r = 31;
        if (g > 31) g = 31;
        if (b > 31) b = 31;

        palette[i] = RGB2(r, g, b);
    }
}

void CheckDayNightChange(void)
{
    u8 currentTimeOfDay = GetTimeOfDay();

    if (sLastTimeOfDay == 0xFF)
    {
        sLastTimeOfDay = currentTimeOfDay;
        return;
    }

    if (currentTimeOfDay != sLastTimeOfDay)
    {
        sLastTimeOfDay = currentTimeOfDay;
        if (IsMapTypeOutdoors(gMapHeader.mapType))
        {
            // Reload tileset palettes with the updated lighting
            LoadMapTilesetPalettes(gMapHeader.mapLayout);
            // Reload all active object event (player and NPC) palettes
            ReloadObjectEventPalettes();
        }
    }
}
