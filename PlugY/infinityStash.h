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
extern int active_SharedStashInMultiPlayer;
extern bool active_sharedStash;
extern bool active_sharedGold;
extern bool separateHardSoftStash;
extern char* sharedStashFilename;

extern bool displaySharedSetItemNameInGreen;
extern int posXPreviousBtn;
extern int posYPreviousBtn;
extern int posWPreviousBtn;
extern int posHPreviousBtn;
extern int posXNextBtn;
extern int posYNextBtn;
extern int posWNextBtn;
extern int posHNextBtn;
extern int posXSharedBtn;
extern int posYSharedBtn;
extern int posWSharedBtn;
extern int posHSharedBtn;
extern int posXPreviousIndexBtn;
extern int posYPreviousIndexBtn;
extern int posWPreviousIndexBtn;
extern int posHPreviousIndexBtn;
extern int posXNextIndexBtn;
extern int posYNextIndexBtn;
extern int posWNextIndexBtn;
extern int posHNextIndexBtn;
extern int posXPutGoldBtn;
extern int posYPutGoldBtn;
extern int posWPutGoldBtn;
extern int posHPutGoldBtn;
extern int posXTakeGoldBtn;
extern int posYTakeGoldBtn;
extern int posWTakeGoldBtn;
extern int posHTakeGoldBtn;
extern int posXStashNameField;
extern int posYStashNameField;
extern int posWStashNameField;
extern int posHStashNameField;
extern int posXStashGoldField;
extern int posYStashGoldField;
extern int posWStashGoldField;
extern int posHStashGoldField;

extern bool autoRenameStashPage;
extern DWORD PersonalNormalPageColor;
extern DWORD PersonalIndexPageColor;
extern DWORD PersonalMainIndexPageColor;
extern DWORD SharedNormalPageColor;
extern DWORD SharedIndexPageColor;
extern DWORD SharedMainIndexPageColor;

void toggleToSharedStash(Unit* ptChar);
void toggleToSelfStash(Unit* ptChar);
void setCurrentStashIndex(Unit* ptChar, int index);
void selectPreviousStash(Unit* ptChar);
void selectNextStash(Unit* ptChar);
void selectPreviousIndexStash(Unit* ptChar);
void selectNextIndexStash(Unit* ptChar);
void selectPrevious2Stash(Unit* ptChar);
void selectNext2Stash(Unit* ptChar);
void selectPreviousIndex2Stash(Unit* ptChar);
void selectNextIndex2Stash(Unit* ptChar);
void swapStash(Unit* ptChar, DWORD page, bool toggle);
void renameCurrentStash(Unit* ptChar, char* name);
void insertStash(Unit* ptChar);
bool deleteStash(Unit* ptChar, bool isClient);

void updateSelectedStashClient(Unit* ptChar);
void selectStash(Unit* ptChar, Stash* newStash, bool forceUpdate = false);
void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags, bool bOnlyItems);

Stash* addStash(Unit* ptChar, bool isShared, bool autoSetIndex, Stash* ptStash = NULL);
DWORD loadStashList(Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize, bool isShared);
void saveStashList(Unit* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize);

void getCurrentStashName(WCHAR* buffer, DWORD maxSize, Unit* ptChar);
WCHAR* getDefaultStashName(Unit* ptChar);

void Install_MultiPageStash();

/*================================= END OF FILE =================================*/