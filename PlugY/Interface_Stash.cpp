/*=================================================================
	File created by Yohann NICOLAS.

	Interface stats page functions

=================================================================*/

#include "common.h"
#include "error.h"
#include "interface_Stash.h"
#include "d2functions.h"
#include "updateServer.h"
#include "infinityStash.h"
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include <stdio.h>

static struct
{
	union{
		DWORD all;
		struct{
			DWORD previous:1;
			DWORD next:1;
			DWORD toggleToSharedStash:1;
			DWORD previousIndex:1;
			DWORD nextIndex:1;
			DWORD putGold:1;
			DWORD takeGold:1;
		};
	};
} isDownBtn;

bool displaySharedSetItemNameInGreen = true;
int posXPreviousBtn=-1;
int posYPreviousBtn=-1;
int posXNextBtn=-1;
int posYNextBtn=-1;
int posXSharedBtn=-1;
int posYSharedBtn=-1;
int posXPreviousIndexBtn=-1;
int posYPreviousIndexBtn=-1;
int posXNextIndexBtn=-1;
int posYNextIndexBtn=-1;
int posXPutGoldBtn=-1;
int posYPutGoldBtn=-1;
int posXTakeGoldBtn=-1;
int posYTakeGoldBtn=-1;

DWORD	getXPreviousBtn()		{return RX(posXPreviousBtn<0? D2GetResolution()?0x80:0xAF : posXPreviousBtn);}
#define	getLPreviousBtn()		32
DWORD	getYPreviousBtn()		{return RY(posYPreviousBtn<0 ? 0x40 : posYPreviousBtn);}
#define	getHPreviousBtn()		32

DWORD	getXNextBtn()			{return RX(posXNextBtn<0 ? D2GetResolution()?0xA0:0xCF :posXNextBtn);}//?169:SEL_X(0x63, 0x63, 0xCF, 0xA0));}
#define	getLNextBtn()			32
DWORD	getYNextBtn()			{return RY(posYNextBtn<0 ? 0x40 : posYNextBtn);}
#define	getHNextBtn()			32

DWORD	getXSharedBtn()			{return RX(posXSharedBtn<0 ? D2GetResolution()?0x10:0x6F :posXSharedBtn);}//17:SEL_X(0xE3, 0xE3, 0x6F, 0x10));}//0xD8
#define	getLSharedBtn()			32
DWORD	getYSharedBtn()			{return RY(posYSharedBtn<0 ? 0x40 : posYSharedBtn);}
#define	getHSharedBtn()			32

DWORD	getXPreviousIndexBtn()	{return RX(posXPreviousIndexBtn<0 ?  D2GetResolution()?0x60:0x8F :posXPreviousIndexBtn);}//73:SEL_X(0x18, 0x60, 0x8F, 0x60));}
#define	getLPreviousIndexBtn()	32
DWORD	getYPreviousIndexBtn()	{return RY(posYPreviousIndexBtn<0 ? 0x40 : posYPreviousIndexBtn);}
#define	getHPreviousIndexBtn()	32

DWORD	getXNextIndexBtn()		{return RX(posXNextIndexBtn<0? D2GetResolution()?0xC0:0xEF : posXNextIndexBtn);}//217:SEL_X(0x128, 0xC0, 0xEF, 0xC0));}
#define	getLNextIndexBtn()		32
DWORD	getYNextIndexBtn()		{return RY(posYNextIndexBtn<0 ? 0x40 : posYNextIndexBtn);}
#define	getHNextIndexBtn()		32

DWORD	getXPutGoldBtn()		{return RX(posXPutGoldBtn<0? 0x1C : posXPutGoldBtn);}
#define	getLPutGoldBtn()		32
DWORD	getYPutGoldBtn()		{return RY(posYPutGoldBtn<0 ? 0x1A8 : posYPutGoldBtn);}
#define	getHPutGoldBtn()		32

DWORD	getXTakeGoldBtn()		{return RX(posXTakeGoldBtn<0? 0x105 : posXTakeGoldBtn);}
#define	getLTakeGoldBtn()		32
DWORD	getYTakeGoldBtn()		{return RY(posYTakeGoldBtn<0 ? 0x1A8 : posYTakeGoldBtn);}
#define	getHTakeGoldBtn()		32

//closeBtn x: D2C=0x113 LOD=0x110(0->0x28)		y: D2C=0x41 LOD=0x40 (-0x23 -> 5)


#define isOnButtonNextStash(x,y) isOnRect(x, y, getXNextBtn(), getYNextBtn(), getLNextBtn(), getHNextBtn())
#define isOnButtonPreviousStash(x,y) isOnRect(x, y, getXPreviousBtn(), getYPreviousBtn(), getLPreviousBtn(), getHPreviousBtn())
#define isOnButtonToggleSharedStash(x,y) isOnRect(x, y, getXSharedBtn(), getYSharedBtn(), getLSharedBtn(), getHSharedBtn())
#define isOnButtonNextIndexStash(x,y) isOnRect(x, y, getXNextIndexBtn(), getYNextIndexBtn(), getLNextIndexBtn(), getHNextIndexBtn())
#define isOnButtonPreviousIndexStash(x,y) isOnRect(x, y, getXPreviousIndexBtn(), getYPreviousIndexBtn(), getLPreviousIndexBtn(), getHPreviousIndexBtn())
#define isOnButtonPutGold(x,y) isOnRect(x, y, getXPutGoldBtn(), getYPutGoldBtn(), getLPutGoldBtn(), getHPutGoldBtn())
#define isOnButtonTakeGold(x,y) isOnRect(x, y, getXTakeGoldBtn(), getYTakeGoldBtn(), getLTakeGoldBtn(), getHTakeGoldBtn())



void* STDCALL printBtns()
{
	if (onRealm || !D2isLODGame()) return D2LoadBuySelBtn();

	Unit* ptChar = D2GetClientPlayer();

	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));
	setImage(&data, stashBtnsImages);

	setFrame(&data, 0 + isDownBtn.previous);
	D2PrintImage(&data, getXPreviousBtn(), getYPreviousBtn(), -1, 5, 0);

	setFrame(&data, 2 + isDownBtn.next);
	D2PrintImage(&data, getXNextBtn(), getYNextBtn(), -1, 5, 0);

	if (active_sharedStash)
	{
		setFrame(&data, 4 + isDownBtn.toggleToSharedStash + (PCPY->showSharedStash?2:0) );
		D2PrintImage(&data, getXSharedBtn(), getYSharedBtn(), -1, 5, 0);
	}

	setFrame(&data, 8 + isDownBtn.previousIndex);
	D2PrintImage(&data, getXPreviousIndexBtn(), getYPreviousIndexBtn(), -1, 5, 0);

	setFrame(&data, 10 + isDownBtn.nextIndex);
	D2PrintImage(&data, getXNextIndexBtn(), getYNextIndexBtn(), -1, 5, 0);

	if (active_sharedGold)
	{
		setImage(&data, sharedGoldBtnsImages);
		setFrame(&data, 0 + isDownBtn.putGold);
		D2PrintImage(&data, getXPutGoldBtn(), getYPutGoldBtn(), -1, 5, 0);

		setFrame(&data, 2 + isDownBtn.takeGold);
		D2PrintImage(&data, getXTakeGoldBtn(), getYTakeGoldBtn(), -1, 5, 0);
	}


	LPWSTR lpText;
	WCHAR text[100];
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();

	D2SetFont(1);

	if (isOnButtonPreviousStash(mx,my)) {
		lpText = getTranslatedString(STR_STASH_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousBtn()+getLPreviousBtn()/2, getYPreviousBtn()-getHPreviousBtn(), WHITE, 1);

	} else if (isOnButtonNextStash(mx,my)) {
		lpText = getTranslatedString(STR_STASH_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextBtn()+getLNextBtn()/2, getYNextBtn()-getHNextBtn(), WHITE, 1);

	} else if (active_sharedStash && isOnButtonToggleSharedStash(mx,my)) {
		lpText = getTranslatedString(PCPY->showSharedStash ? STR_TOGGLE_TO_PERSONAL : STR_TOGGLE_TO_SHARED);
		D2PrintPopup(lpText, getXSharedBtn()+getLSharedBtn()/2, getYSharedBtn()-getHSharedBtn(), WHITE, 1);

	} else if (isOnButtonPreviousIndexStash(mx,my)) {
		swprintf(text, getTranslatedString(STR_STASH_PREVIOUS_INDEX) ,nbPagesPerIndex,nbPagesPerIndex2);
		D2PrintPopup(text, getXPreviousIndexBtn()+getLPreviousIndexBtn()/2, getYPreviousIndexBtn()-getHPreviousIndexBtn(), 0, 0);

	} else if (isOnButtonNextIndexStash(mx,my))	{
		swprintf(text, getTranslatedString(STR_STASH_NEXT_INDEX) ,nbPagesPerIndex,nbPagesPerIndex2);
		D2PrintPopup(text, getXNextIndexBtn()+getLNextIndexBtn()/2, getYNextIndexBtn()-getHNextIndexBtn(), WHITE, 1);

	} else if (active_sharedGold && isOnButtonPutGold(mx,my))	{
		lpText = getTranslatedString(STR_PUT_GOLD);
		D2PrintPopup(lpText, getXPutGoldBtn()+getLPutGoldBtn()/2, getYPutGoldBtn()-getHPutGoldBtn(), WHITE, 1);

	} else if (active_sharedGold && isOnButtonTakeGold(mx,my))	{
		lpText = getTranslatedString(STR_TAKE_GOLD);
		D2PrintPopup(lpText, getXTakeGoldBtn()+getLTakeGoldBtn()/2, getYTakeGoldBtn()-getHTakeGoldBtn(), WHITE, 1);
	}

	return D2LoadBuySelBtn();
}


DWORD STDCALL manageBtnDown(sWinMessage* msg)
{
	if (onRealm || !D2isLODGame()) return 0;

	if (isOnButtonPreviousStash(msg->x,msg->y))
		isDownBtn.previous = 1;
	else if (isOnButtonNextStash(msg->x,msg->y))
		isDownBtn.next = 1;
	else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x,msg->y))
		isDownBtn.toggleToSharedStash = 1;
	else if (isOnButtonPreviousIndexStash(msg->x,msg->y))
		isDownBtn.previousIndex = 1;
	else if (isOnButtonNextIndexStash(msg->x,msg->y))
		isDownBtn.nextIndex = 1;
	else if (active_sharedGold && isOnButtonPutGold(msg->x,msg->y))
		isDownBtn.putGold = 1;
	else if (active_sharedGold && isOnButtonTakeGold(msg->x,msg->y))
		isDownBtn.takeGold = 1;
	else return 0;

	D2PlaySound(4,0,0,0,0);
	freeMessage(msg);
	return 1;
}

	
DWORD STDCALL manageBtnUp(sWinMessage* msg)
{
	if (onRealm || !D2isLODGame()) return 0;

	Unit* ptChar = D2GetClientPlayer();

	if (isOnButtonPreviousStash(msg->x,msg->y)) {
		log_msg("push up left button previous\n");
		if (isDownBtn.previous)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_PREVIOUS2);
			else
				updateServer(US_SELECT_PREVIOUS);

	} else if (isOnButtonNextStash(msg->x,msg->y)) {
		log_msg("push up left button next\n");
		if (isDownBtn.next)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_NEXT2);
			else
				updateServer(US_SELECT_NEXT);

	} else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x,msg->y)) {
		log_msg("push up left button shared\n");
		if (isDownBtn.toggleToSharedStash)
			if (PCPY->showSharedStash)
				updateServer(US_SELECT_SELF);
			 else
				updateServer(US_SELECT_SHARED);

	} else if (isOnButtonPreviousIndexStash(msg->x,msg->y)) {
		log_msg("select left button previous index\n");
		if (isDownBtn.previousIndex)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_PREVIOUS_INDEX2);
			else
				updateServer(US_SELECT_PREVIOUS_INDEX);

	} else if (isOnButtonNextIndexStash(msg->x,msg->y)) {
		log_msg("push up left button next index\n");
		if (isDownBtn.nextIndex)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_NEXT_INDEX2);
			else
				updateServer(US_SELECT_NEXT_INDEX);

	} else if (active_sharedGold && isOnButtonPutGold(msg->x,msg->y)) {
		log_msg("push up left put gold\n");
		if (isDownBtn.putGold)
			updateServer(US_PUTGOLD);

	} else if (active_sharedGold && isOnButtonTakeGold(msg->x,msg->y)) {
		log_msg("push up left take gold\n");
		if (isDownBtn.takeGold)
			updateServer(US_TAKEGOLD);

	} else return 0;

	return 1;
}

void FASTCALL printPageNumber(LPWSTR maxGoldText, DWORD x, DWORD y, DWORD color, DWORD bfalse)
{
	if (onRealm || !D2isLODGame() )
	{
		D2PrintString(maxGoldText,x,y,color,bfalse);
		return;
	}

	Unit* ptChar = D2GetClientPlayer();
	WCHAR popupText[100];

	if (PCPY->currentStash)
	{
		bool isShared = PCPY->currentStash->isShared;
		DWORD currentId = PCPY->currentStash->id;

		if (PCPY->currentStash->name && PCPY->currentStash->name[0])
			mbstowcs(popupText,PCPY->currentStash->name,50);//strlen(PCPY->currentStash->name)+1
		else swprintf(popupText, getTranslatedString( isShared ? STR_SHARED_PAGE_NUMBER : STR_PERSONAL_PAGE_NUMBER), currentId+1);
		D2PrintString(popupText,x,y, isShared?RED:WHITE ,bfalse);
	} else {
		swprintf(popupText, getTranslatedString(STR_NO_SELECTED_PAGE));
		D2PrintString(popupText,x,y, WHITE ,bfalse);
	}

	//printGoldMaxPopup
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();
	if ((RX(0x5E) < mx) && (mx < RX(0xF8)) && (RY(0x1C8) < my) && (my < RY(0x1B6)) )
	{
		if (active_sharedGold)
		{
			swprintf(popupText, L"%s\n", maxGoldText);
			swprintf(popupText+wcslen(popupText), getTranslatedString(STR_SHARED_GOLD_QUANTITY), PCPY->sharedGold);
			DWORD x = D2GetPixelLen(maxGoldText);
			DWORD x2 = D2GetPixelLen(popupText) - x;
			D2PrintPopup(popupText, RX(0xA8-max(x,x2)/2), RY(0x1CA), WHITE, 0);
		} else 
			D2PrintPopup(maxGoldText, RX(0xA8), RY(0x1CA), WHITE, 1);
	}
}


static Stash* curStash=NULL;
static DWORD currentSawStash=0;
Unit* STDCALL getNextItemForSet(Unit* ptItem)
{
	Unit* item = ptItem?D2UnitGetNextItem(ptItem):NULL;
	if (item) return item;

	if (!curStash)
	{
		Unit* ptChar = D2GetClientPlayer();
		switch (currentSawStash)
		{
		case 0: curStash = PCPY->selfStash;
				currentSawStash = displaySharedSetItemNameInGreen ? 1 : 2;
				break;
		case 1: curStash = PCPY->sharedStash;
				currentSawStash = 2;
				break;
		default:return NULL;
		}
	} else {
		curStash = curStash->nextStash;
	}
	if (curStash)
	{
		item = curStash->ptListItem;
		if (item) return item;
	}
	return getNextItemForSet(item);
}

Unit* STDCALL initGetNextItemForSet(Inventory* ptInventory)
{
	Unit* ptChar = D2GetClientPlayer();
	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPY) return NULL;

	curStash = NULL;
	currentSawStash = 0;
	Unit* item = D2InventoryGetFirstItem(ptInventory);
	if (item) return item;
	return getNextItemForSet(item);
}


FCT_ASM( caller_manageBtnDown_111 )
	PUSH EBP
	CALL manageBtnDown
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0x10]
	MOV DWORD PTR DS:[EDX],1
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2ClickOnStashButton
}}

FCT_ASM( caller_manageBtnDown )
	PUSH EDI
	CALL manageBtnDown
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0xF3]
	MOV DWORD PTR DS:[EDX],1
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2isLODGame
}}

FCT_ASM( caller_manageBtnUp_111 )
	PUSH EBX
	CALL manageBtnUp
	MOV isDownBtn.all,0
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0x1A]
	MOV DWORD PTR DS:[EDX],0
	SUB EDX,8
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,4
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,0x68
	MOV DWORD PTR DS:[EDX],0
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	POP ECX
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2ClickOnStashButton
}}

FCT_ASM( caller_manageBtnUp )
	PUSH EBP
	CALL manageBtnUp
	MOV isDownBtn.all,0
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0xEA]
	MOV DWORD PTR DS:[EDX],0
	SUB EDX,8
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,4
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,0x68
	MOV DWORD PTR DS:[EDX],0
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2isLODGame
}}


FCT_ASM ( initBtnsStates )
	MOV isDownBtn.all,0
	ADD ESP,0x104
	RETN
}}


void Install_InterfaceStash()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();
	Install_PlugYImagesFiles();

	log_msg("Patch D2Client for stash interface. (InterfaceStash)\n");

	// Print button images
	mem_seek R7(D2Client, 39060, 39060, 3F399, B1006, 7DF86, B3656, 99A56);
	MEMC_REF4( D2LoadBuySelBtn, printBtns);
	//6FADF398  |. E8 734D0400    CALL D2Client.6FB24110
	//6FB61005  |. E8 A6D3FEFF    CALL D2Client.6FB4E3B0
	//6FB2DF85  |. E8 3642FEFF    CALL D2Client.6FB121C0
	//6FB63655  |. E8 9682FDFF    CALL D2Client.6FB3B8F0
	//6FB49A55  |. E8 96500200    CALL D2Client.6FB6EAF0

	// print page number
	mem_seek R7(D2Client, 3903C, 3903C, 3F375, B0FE3, 7DF63, B3633, 99A33);
	MEMJ_REF4( D2PrintString, printPageNumber);
	//6FADF374  |. E8 3FCC0800    CALL <JMP.&D2Win.#10117>
	//6FB60FE2  |. E8 99C2F5FF    CALL <JMP.&D2Win.#10020>
	//6FB2DF62  |. E8 19F3F8FF    CALL <JMP.&D2Win.#10064>
	//6FB63632  |. E8 299DF5FF    CALL <JMP.&D2Win.#10001>
	//6FB49A32  |. E8 4739F7FF    CALL <JMP.&D2Win.#10150>

	// Manage mouse down (Play sound)
	mem_seek R7(D2Client, 45091, 45091, 4BBA1, B4666, 7FDD6, B54A6, 9B8A6);
	MEMC_REF4( version_D2Client >= V111 ? (DWORD)D2ClickOnStashButton : (DWORD)D2isLODGame, version_D2Client >= V111 ? caller_manageBtnDown_111 : caller_manageBtnDown);
	//6FAEBBA0   > E8 DB04FCFF    CALL D2Client.6FAAC080
	//6FB64665   . E8 B61EFFFF    CALL D2Client.6FB56520
	//6FB2FDD5   . E8 E612FFFF    CALL D2Client.6FB210C0
	//6FB654A5   . E8 9611FFFF    CALL D2Client.6FB56640
	//6FB4B8A5   . E8 5614FFFF    CALL D2Client.6FB3CD00

	// Manage mouse up
	mem_seek R7(D2Client, 455F9, 455F9, 4C0F9, B57B9, 7FC09, B52D9, 9B6D9);
	MEMC_REF4( version_D2Client >= V111 ? (DWORD)D2ClickOnStashButton : (DWORD)D2isLODGame, version_D2Client >= V111 ? caller_manageBtnUp_111 : caller_manageBtnUp);
	//6FAEC0F8   > E8 83FFFBFF    CALL D2Client.6FAAC080
	//6FB657B8   > E8 630DFFFF    CALL D2Client.6FB56520
	//6FB2FC08   > E8 B314FFFF    CALL D2Client.6FB210C0
	//6FB652D8   > E8 6313FFFF    CALL D2Client.6FB56640
	//6FB4B6D8   > E8 2316FFFF    CALL D2Client.6FB3CD00

	// init state of button on open stash page
	mem_seek R7(D2Client, 45B3A, 45B3A, 4C63A, A645A, 749DA, A9D9A, 8CC3A);
	memt_byte( 0x81, 0xE9 );	// CALL initBtnsStates
	MEMT_REF4( 0x000104C4, initBtnsStates);
	memt_byte( 0x00, 0x90 );
	//6FAE5B3A  |> 81C4 04010000  ADD ESP,104
	//6FAE5B3A  |> 81C4 04010000  ADD ESP,104
	//6FAEC63A  |> 81C4 04010000  ADD ESP,104
	//6FB5645A  |> 81C4 04010000  ADD ESP,104
	//6FB249DA  |> 81C4 04010000  ADD ESP,104
	//6FB59D9A  |> 81C4 04010000  ADD ESP,104
	//6FB3CC3A  |> 81C4 04010000  ADD ESP,104

	// init the search of print in green the item set name we have in stash
	mem_seek R7(D2Client, 3F098, 3F098, 45997, A71F4, 71F64, A7314, 8D434);
	MEMJ_REF4( D2InventoryGetFirstItem, initGetNextItemForSet);
	//6FAE5996  |. E8 D5500800    CALL <JMP.&D2Common.#10277>
	//6FB571F3  |. E8 D64EF6FF    CALL <JMP.&D2Common.#10402>
	//6FB21F63  |. E8 96A1F9FF    CALL <JMP.&D2Common.#10535>
	//6FB57313  |. E8 8250F6FF    CALL <JMP.&D2Common.#11151>
	//6FB3D433  |. E8 B8F0F7FF    CALL <JMP.&D2Common.#10460>

	// Get next item for print in green the item set name we have in stash
	mem_seek R7(D2Client, 3F0FA, 3F0FA, 45A1C, A728B, 71FFB, A73AB, 8D4CB);
	MEMJ_REF4( D2UnitGetNextItem, getNextItemForSet);
	//6FAE5A1B   E8 4A500800      CALL <JMP.&D2Common.#10304>
	//6FB5728A  |. E8 0B4FF6FF    |CALL <JMP.&D2Common.#10934>
	//6FB21FFA  |. E8 A1A1F9FF    |CALL <JMP.&D2Common.#11140>
	//6FB573AA  |. E8 7550F6FF    |CALL <JMP.&D2Common.#10770>
	//6FB3D4CA  |. E8 99F0F7FF    |CALL <JMP.&D2Common.#10464>

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/