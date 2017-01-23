/*=================================================================
	File created by Yohann NICOLAS.

	New Interfaces functions

=================================================================*/
#pragma once

#include "common.h"

#define MILIEU(X,L,N) (X + ((N<L)? (L-N)/2 : 0))
#define isOnStatsPage(x,y)		((x<400) && (y<553))

extern DWORD bDontPrintBorder;

void GoNextStatPage();
void GoPreviousStatPage();
void GoStatPage(int page);
int GetCurrentPage();

extern bool active_newInterfaces;
extern bool selectMainPageOnOpenning;
extern bool printBackgroundOnMainPage;

void Install_NewInterfaces();

/*================================= END OF FILE =================================*/