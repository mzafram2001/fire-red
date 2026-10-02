EventScript_RepelWoreOff::
	lockall
	special TrySetupAutoRepel
	goto_if_eq VAR_RESULT, FALSE, EventScript_RepelWoreOffNormal
	msgbox Text_RepelWoreOffAskReuse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_RepelWoreOffEnd
	special UseAutoRepel
	msgbox Text_UsedRepel, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

EventScript_RepelWoreOffNormal::
	msgbox Text_RepelWoreOff, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

EventScript_RepelWoreOffEnd::
	closemessage
	releaseall
	end

Text_RepelWoreOff::
	.string "REPEL's effect wore off…$"

Text_RepelWoreOffAskReuse::
	.string "The {STR_VAR_1}'s effect wore off…\n"
	.string "Would you like to use another?$"

Text_UsedRepel::
	.string "{PLAYER} used the\n"
	.string "{STR_VAR_1}.$"
