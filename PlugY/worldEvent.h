/*=================================================================
	File created by Yohann NICOLAS.

	World Event Management.

=================================================================*/

#pragma once

extern bool active_WorldEvent;
extern DWORD showSOJSoldCounterInAllDiff;
extern char* itemsToSell;
extern DWORD worldEventmonsterID;
extern DWORD valueOfOwnSOJSold;
extern DWORD valueInitSOJSoldMin;
extern DWORD valueInitSOJSoldDelta;
extern DWORD triggerAtSolJSoldMin;
extern DWORD triggerAtSolJSoldDelta;
extern bool active_AutomaticSell;
extern DWORD timeBeforeAutoSellMin;
extern DWORD timeBeforeAutoSellDelta;

void initWorldEventVariables();

void Install_WorldEvent();

/*================================= END OF FILE =================================*/