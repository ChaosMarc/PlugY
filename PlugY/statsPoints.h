/*=================================================================
	File created by Yohann NICOLAS.

	Unassign Stats Point for futher re-assignment.

=================================================================*/

#pragma once

#include <windows.h>

extern bool active_StatsPoints;
extern DWORD keyUsedForUnassignStatPoint;
extern bool active_StatsShiftClickLimit;
extern DWORD limitValueToShiftClick;

void UnassignStrPoint(Unit* ptChar);
void UnassignStrPoints(Unit* ptChar);
void UnassignDexPoint(Unit* ptChar);
void UnassignDexPoints(Unit* ptChar);
void UnassignVitPoint(Unit* ptChar);
void UnassignVitPoints(Unit* ptChar);
void UnassignEnePoint(Unit* ptChar);
void UnassignEnePoints(Unit* ptChar);

void Install_StatsLimitShiftClick();
void Install_StatsPoints();

/*================================= END OF FILE =================================*/