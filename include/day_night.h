#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

#include "global.h"

u8 GetTimeOfDay(void);
void ApplyDayNightTint(u16 *palette, u16 count);
void CheckDayNightChange(void);

#endif // GUARD_DAY_NIGHT_H
