/*=================================================================
	File created by Yohann NICOLAS.

	More little options.

=================================================================*/

#ifndef __EXTRAOPTIONS_H__INCLUDED
#define __EXTRAOPTIONS_H__INCLUDED

extern int active_Windowed;
extern int active_LockMouseCursor;
extern int active_DisplayItemLevel;
extern DWORD nbPlayersCommandByDefault;
extern int active_alwaysRegenMapInSP;
extern int active_RunLODs;
extern int active_AlwaysDisplayLifeMana;
extern int active_EnabledTXTFilesWithMSExcel;
extern int active_DisplayBaseStatsValue;
extern int active_LadderRunewords;
extern int active_EnabledCowPortalWhenCowKingWasKill;

extern int active_RemoveBorder;
extern int active_WindowOnTop;
extern int active_Maximized;
extern int active_SetWindowPos;
extern int windowedX;
extern int windowedY;
extern int windowedWidth;
extern int windowedHeight;
extern int active_LockMouseOnStartup;

void Install_DisplayItemLevel();
void Install_SendPlayersCommand();
void Install_AlwaysRegenMapInSP();
void Install_RunLODs();
void Install_AlwaysDisplayLifeMana();
void Install_EnabledTXTFilesWithMSExcel();
void Install_DisplayBaseStatsValue();
void Install_LadderRunewords();
void Install_EnabledCowPortalWhenCowKingWasKill();

void SetWindowedOptions();
void lockMouseCursor();
#endif