/*=================================================================
	File created by Yohann NICOLAS.

	More little options.

=================================================================*/
#pragma once

#include "common.h"

extern int active_DisplayItemLevel;
extern DWORD nbPlayersCommandByDefault;
extern DWORD nbPlayersCommand;
extern int active_alwaysRegenMapInSP;
extern int active_RunLODs;
extern int active_AlwaysDisplayLifeMana;
extern int active_EnabledTXTFilesWithMSExcel;
extern int active_DisplayBaseStatsValue;
extern int active_LadderRunewords;
extern int active_EnabledCowPortalWhenCowKingWasKill;

void Install_DisplayItemLevel();
void Install_SendPlayersCommand();
void Install_AlwaysRegenMapInSP();
void Install_RunLODs();
void Install_AlwaysDisplayLifeMana();
void Install_EnabledTXTFilesWithMSExcel();
void Install_DisplayBaseStatsValue();
void Install_LadderRunewords();
void Install_EnabledCowPortalWhenCowKingWasKill();

/*================================= END OF FILE =================================*/