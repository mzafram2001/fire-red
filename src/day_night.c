#include "global.h"
#include "day_night.h"
#include "rtc.h"
#include "overworld.h"
#include "fieldmap.h"
#include "event_object_movement.h"
#include "palette.h"

#define MIN_VAL(a, b) ((a) < (b) ? (a) : (b))

static EWRAM_DATA u8 sLastTimeOfDay = 0xFF;

void ApplyDayNightTint(u16 *palette, u16 count)
{
    u8 timeOfDay;
    s32 r, g, b;
    u16 i;

    // Do not tint inside buildings, gyms, caves, or during Quest Log playback
    if (!IsMapTypeOutdoors(gMapHeader.mapType))
        return;

    timeOfDay = GetTimeOfDay();
    if (timeOfDay == TIME_DAY)
        return; // Normal daytime needs no tint

    for (i = 0; i < count; i++)
    {
        // Skip transparent color (color 0 in each 16-color palette)
        if ((i % 16) == 0)
            continue;

        r = GET_R(palette[i]);
        g = GET_G(palette[i]);
        b = GET_B(palette[i]);

        switch (timeOfDay)
        {
        case TIME_MORNING: // Warm golden morning sunrise
            r = MIN_VAL(31, r + (31 - r) / 8 + 1);
            g = MIN_VAL(31, g + (31 - g) / 10);
            b = (b > 1) ? b - 1 : b;
            break;
        case TIME_SUNSET: // Warm sunset orange / dusk
            r = MIN_VAL(31, r + 4);
            g = (g > 1) ? g - 1 : g;
            b = (b * 3) / 4;
            break;
        case TIME_NIGHT: // Deep blue moonlight
            r = (r * 8) / 16;
            g = (g * 11) / 16;
            b = MIN_VAL(31, (b * 14) / 16 + 2);
            break;
        }

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
        }
    }
}
