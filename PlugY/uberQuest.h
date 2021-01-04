/*=================================================================
	File created by Yohann NICOLAS.

	Uber Quest Management.

=================================================================*/
#pragma once

#include "common.h"

extern bool active_UberQuest;
extern DWORD UberMephistoX;
extern DWORD UberMephistoY;
extern DWORD UberDiabloX;
extern DWORD UberDiabloY;
extern DWORD UberBaalX;
extern DWORD UberBaalY;

extern bool active_UberMinions;
//extern DWORD UberMephistoNbMinions;
//extern DWORD UberMephistoMinions[];
extern int UberMephistoSpawnPercent;
extern DWORD UberMephistoSpawnRadius;

//extern DWORD UberBaalNbMinions;
//extern DWORD UberBaalMinions[];
extern int UberBaalSpawnPercent;
extern DWORD UberBaalSpawnRadius;

//extern DWORD UberDiabloNbMinions;
//extern DWORD UberDiabloMinions[];
extern int UberDiabloSpawnPercent;
extern DWORD UberDiabloSpawnRadius;

extern bool active_UberDiabloRushTweekAI;
extern bool active_UberBaalTeleportTweekAI;
extern bool active_UberBaalChillingArmorTweekAI;
extern int uberBaalChillingArmorTimer;

void Install_UberQuest();
void resetQuestState();

/*================================= END OF FILE =================================*/