#include "global.h"
#include "gflib.h"
#include "strings.h"
#include "task.h"
#include "field_message_box.h"
#include "script.h"
#include "event_data.h"
#include "fldeff.h"
#include "party_menu.h"
#include "field_poison.h"
#include "constants/battle.h"

EWRAM_DATA static u8 sPoisonSurvivedPartyMask = 0;

#define tState   data[0]
#define tPartyId data[1]

static void Task_TryFieldPoisonWhiteOut(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    switch (tState)
    {
    case 0:
        for (; tPartyId < PARTY_SIZE; tPartyId++)
        {
            if (sPoisonSurvivedPartyMask & (1 << tPartyId))
            {
                struct Pokemon *pokemon = &gPlayerParty[tPartyId];
                sPoisonSurvivedPartyMask &= ~(1 << tPartyId);
                GetMonData(pokemon, MON_DATA_NICKNAME, gStringVar1);
                StringGet_Nickname(gStringVar1);
                ShowFieldMessage(gText_PkmnPoisonSurvived);
                tState++;
                return;
            }
        }
        sPoisonSurvivedPartyMask = 0;
        tState = 2;
        break;
    case 1:
        if (IsFieldMessageBoxHidden())
            tState--;
        break;
    case 2:
        gSpecialVar_Result = FALSE; // Pokemon never faint from field poison (Gen 4+ survival)
        ScriptContext_Enable();
        DestroyTask(taskId);
        break;
    }
}

void TryFieldPoisonWhiteOut(void)
{
    CreateTask(Task_TryFieldPoisonWhiteOut, 80);
    ScriptContext_Stop();
}

s32 DoPoisonFieldEffect(void)
{
    int i;
    u32 hp;
    
    struct Pokemon *pokemon = gPlayerParty;
    u32 numPoisoned = 0;
    u32 numSurvived = 0;
    sPoisonSurvivedPartyMask = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(pokemon, MON_DATA_SANITY_HAS_SPECIES) && GetAilmentFromStatus(GetMonData(pokemon, MON_DATA_STATUS)) == AILMENT_PSN)
        {
            hp = GetMonData(pokemon, MON_DATA_HP);
            if (hp > 1)
            {
                hp--;
                SetMonData(pokemon, MON_DATA_HP, &hp);
                numPoisoned++;
            }
            else if (hp == 1)
            {
                u32 status = STATUS1_NONE;
                SetMonData(pokemon, MON_DATA_STATUS, &status);
                sPoisonSurvivedPartyMask |= (1 << i);
                numSurvived++;
            }
        }
        pokemon++;
    }
    if (numSurvived || numPoisoned)
        FldEffPoison_Start();
    if (numSurvived)
        return FLDPSN_FNT;
    if (numPoisoned)
        return FLDPSN_PSN;
    return FLDPSN_NONE;
}
