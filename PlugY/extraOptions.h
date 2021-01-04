/*=================================================================
	File created by Yohann NICOLAS.
	Add DoNotCloseNihlathakPortal by haxifix.

	More little options.

=================================================================*/
#pragma once

#include "common.h"

extern bool active_DisplayItemLevel;
extern DWORD nbPlayersCommandByDefault;
extern DWORD nbPlayersCommand;
extern bool active_alwaysRegenMapInSP;
extern bool active_RunLODs;
extern int active_AlwaysDisplayLifeMana;
extern bool active_EnabledTXTFilesWithMSExcel;
extern bool active_DisplayBaseStatsValue;
extern bool active_LadderRunewords;
extern bool active_EnabledCowPortalWhenCowKingWasKill;
extern bool active_DoNotCloseNihlathakPortal;
extern bool active_MoveCainNearHarrogathWaypoint;
extern bool active_RemoveExperienceDiminushingReturn;

void Install_DisplayItemLevel();
void Install_SendPlayersCommand();
void Install_AlwaysRegenMapInSP();
void Install_RunLODs();
void Install_AlwaysDisplayLifeMana();
void Install_EnabledTXTFilesWithMSExcel();
void Install_DisplayBaseStatsValue();
void Install_LadderRunewords();
void Install_EnabledCowPortalWhenCowKingWasKill();
void Install_DoNotCloseNihlathakPortal();
void Install_MoveCainNearHarrogathWaypoint();
void Install_RemoveExperienceDiminushingReturn();

/*================================= END OF FILE =================================*/