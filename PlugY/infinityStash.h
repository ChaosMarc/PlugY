/*=================================================================
	File created by Yohann NICOLAS.

  infinity Stash gestion

=================================================================*/

#pragma once

#include "common.h"

extern DWORD maxSelfPages;
extern DWORD maxSharedPages;
extern DWORD nbPagesPerIndex;
extern DWORD nbPagesPerIndex2;
extern bool active_multiPageStash;
extern bool active_sharedStash;
extern bool active_sharedGold;
extern bool separateHardSoftStash;
extern char* sharedStashFilename;

extern bool displaySharedSetItemNameInGreen;
extern int posXPreviousBtn,posYPreviousBtn,posXNextBtn,posYNextBtn,posXSharedBtn,posYSharedBtn,posXPreviousIndexBtn,posYPreviousIndexBtn,posXNextIndexBtn,posYNextIndexBtn,posXPutGoldBtn,posYPutGoldBtn,posXTakeGoldBtn,posYTakeGoldBtn;


void toggleToSharedStash(Unit* ptChar);
void toggleToSelfStash(Unit* ptChar);
void selectPreviousStash(Unit* ptChar);
void selectNextStash(Unit* ptChar);
void selectPreviousIndexStash(Unit* ptChar);
void selectNextIndexStash(Unit* ptChar);
void selectPrevious2Stash(Unit* ptChar);
void selectNext2Stash(Unit* ptChar);
void selectPreviousIndex2Stash(Unit* ptChar);
void selectNextIndex2Stash(Unit* ptChar);
void swapStash(Unit* ptChar, DWORD page, bool toggle);

void selectStash(Unit* ptChar, Stash* newStash);
void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags);

Stash* addStash(Unit* ptChar, bool isShared);
DWORD loadStashList(Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize, bool isShared);
void saveStashList(Unit* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize);

void Install_MultiPageStash();

/*================================= END OF FILE =================================*/