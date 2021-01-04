/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Interface stats page functions

=================================================================*/

#include "interface_Stash.h"
#include "updateServer.h"
#include "infinityStash.h"
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "common.h"
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
			DWORD stashName:1;
		};
	};
} isDownBtn;

bool displaySharedSetItemNameInGreen = true;
int posXPreviousBtn = -1;
int posYPreviousBtn = -1;
int posWPreviousBtn = 32;
int posHPreviousBtn = 32;
int posXNextBtn = -1;
int posYNextBtn = -1;
int posWNextBtn = 32;
int posHNextBtn = 32;
int posXSharedBtn = -1;
int posYSharedBtn = -1;
int posWSharedBtn = 32;
int posHSharedBtn = 32;
int posXPreviousIndexBtn = -1;
int posYPreviousIndexBtn = -1;
int posWPreviousIndexBtn = 32;
int posHPreviousIndexBtn = 32;
int posXNextIndexBtn = -1;
int posYNextIndexBtn = -1;
int posWNextIndexBtn = 32;
int posHNextIndexBtn = 32;
int posXPutGoldBtn = -1;
int posYPutGoldBtn = -1;
int posWPutGoldBtn = 32;
int posHPutGoldBtn = 32;
int posXTakeGoldBtn = -1;
int posYTakeGoldBtn = -1;
int posWTakeGoldBtn = 32;
int posHTakeGoldBtn = 32;
int posXStashNameField = -1;
int posYStashNameField = -1;
int posWStashNameField = 175;
int posHStashNameField = 20;
int posXStashGoldField = -1;
int posYStashGoldField = -1;
int posWStashGoldField = 152;
int posHStashGoldField = 18;


DWORD PersonalNormalPageColor = WHITE;
DWORD PersonalIndexPageColor = DARK_GREEN;
DWORD PersonalMainIndexPageColor = YELLOW;
DWORD SharedNormalPageColor = GOLD;
DWORD SharedIndexPageColor = ORANGE;
DWORD SharedMainIndexPageColor = RED;


DWORD	getXPreviousBtn()		{return RX(posXPreviousBtn<0? D2GetResolution()?0x80:0xAF : posXPreviousBtn);}
DWORD	getYPreviousBtn()		{return RY(posYPreviousBtn<0 ? 0x40 : posYPreviousBtn);}
DWORD	getXNextBtn()			{return RX(posXNextBtn<0 ? D2GetResolution()?0xA0:0xCF :posXNextBtn);}//?169:SEL_X(0x63, 0x63, 0xCF, 0xA0));}
DWORD	getYNextBtn()			{return RY(posYNextBtn<0 ? 0x40 : posYNextBtn);}
DWORD	getXSharedBtn()			{return RX(posXSharedBtn<0 ? D2GetResolution()?0x10:0x6F :posXSharedBtn);}//17:SEL_X(0xE3, 0xE3, 0x6F, 0x10));}//0xD8
DWORD	getYSharedBtn()			{return RY(posYSharedBtn<0 ? 0x40 : posYSharedBtn);}
DWORD	getXPreviousIndexBtn()	{return RX(posXPreviousIndexBtn<0 ?  D2GetResolution()?0x60:0x8F :posXPreviousIndexBtn);}//73:SEL_X(0x18, 0x60, 0x8F, 0x60));}
DWORD	getYPreviousIndexBtn()	{return RY(posYPreviousIndexBtn<0 ? 0x40 : posYPreviousIndexBtn);}
DWORD	getXNextIndexBtn()		{return RX(posXNextIndexBtn<0? D2GetResolution()?0xC0:0xEF : posXNextIndexBtn);}//217:SEL_X(0x128, 0xC0, 0xEF, 0xC0));}
DWORD	getYNextIndexBtn()		{return RY(posYNextIndexBtn<0 ? 0x40 : posYNextIndexBtn);}
DWORD	getXPutGoldBtn()		{return RX(posXPutGoldBtn<0? 0x1C : posXPutGoldBtn);}
DWORD	getYPutGoldBtn()		{return RY(posYPutGoldBtn<0 ? 0x1A8 : posYPutGoldBtn);}
DWORD	getXTakeGoldBtn()		{return RX(posXTakeGoldBtn<0? 0x105 : posXTakeGoldBtn);}
DWORD	getYTakeGoldBtn()		{return RY(posYTakeGoldBtn<0 ? 0x1A8 : posYTakeGoldBtn);}
DWORD	getXStashNameField()	{return RX(posXStashNameField<0 ? 0x4A : posXStashNameField);}
DWORD	getYStashNameField()	{return RY(posYStashNameField<0 ? 0x19A : posYStashNameField);}
DWORD	getXStashGoldField()	{return RX(posXStashGoldField<0 ? 0x61 : posXStashGoldField);}
DWORD	getYStashGoldField()	{return RY(posYStashGoldField<0 ? 0x1B6 : posYStashGoldField);}

//closeBtn x: D2C=0x113 LOD=0x110(0->0x28)		y: D2C=0x41 LOD=0x40 (-0x23 -> 5)


#define isOnButtonNextStash(x,y) isOnRect(x, y, getXNextBtn(), getYNextBtn(), posWNextBtn, posHNextBtn)
#define isOnButtonPreviousStash(x,y) isOnRect(x, y, getXPreviousBtn(), getYPreviousBtn(), posWPreviousBtn, posHPreviousBtn)
#define isOnButtonToggleSharedStash(x,y) isOnRect(x, y, getXSharedBtn(), getYSharedBtn(), posWSharedBtn, posHSharedBtn)
#define isOnButtonNextIndexStash(x,y) isOnRect(x, y, getXNextIndexBtn(), getYNextIndexBtn(), posWNextIndexBtn, posHNextIndexBtn)
#define isOnButtonPreviousIndexStash(x,y) isOnRect(x, y, getXPreviousIndexBtn(), getYPreviousIndexBtn(), posWPreviousIndexBtn, posHPreviousIndexBtn)
#define isOnButtonPutGold(x,y) isOnRect(x, y, getXPutGoldBtn(), getYPutGoldBtn(), posWPutGoldBtn, posHPutGoldBtn)
#define isOnButtonTakeGold(x,y) isOnRect(x, y, getXTakeGoldBtn(), getYTakeGoldBtn(), posWTakeGoldBtn, posHTakeGoldBtn)
#define isOnStashNameField(x,y) isOnRect(x, y, getXStashNameField(), getYStashNameField(), posWStashNameField, posHStashNameField)
#define isOnStashGoldField(x,y) isOnRect(x, y, getXStashGoldField(), getYStashGoldField(), posWStashGoldField, posHStashGoldField)

void UpdateStashPosition()
{
	//static int isInstalled = false;
	//if (isInstalled) return;

	InventoryBIN* inventory = D2GetInventoryBIN();
	if (inventory->gridY == 15)
	{
		posXPreviousBtn = 127;
		posYPreviousBtn = 500;
		posXNextBtn = 159;
		posYNextBtn = 500;
		posXSharedBtn = 28;
		posYSharedBtn = 21;
		posXPreviousIndexBtn = 95;
		posYPreviousIndexBtn = 500;
		posXNextIndexBtn = 191;
		posYNextIndexBtn = 500;
		posXPutGoldBtn = 28;
		posYPutGoldBtn = 500;
		posXTakeGoldBtn = 259;
		posYTakeGoldBtn = 500;
		//posXStashNameField = -1;
		posYStashNameField = 16;
		//posXStashGoldField = -1;
		posYStashGoldField = 36;
	}
}

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
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();

	D2SetFont(1);

	if (isOnButtonPreviousStash(mx,my)) {
		lpText = getLocalString(STR_STASH_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousBtn()+posWPreviousBtn/2, getYPreviousBtn()-posHPreviousBtn, WHITE, 1);

	} else if (isOnButtonNextStash(mx,my)) {
		lpText = getLocalString(STR_STASH_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextBtn()+posWNextBtn/2, getYNextBtn()-posHNextBtn, WHITE, 1);

	} else if (isOnButtonToggleSharedStash(mx,my)) {
		if (active_sharedStash) {
			lpText = getLocalString(PCPY->showSharedStash ? STR_TOGGLE_TO_PERSONAL : STR_TOGGLE_TO_SHARED);
			D2PrintPopup(lpText, getXSharedBtn()+posWSharedBtn/2, getYSharedBtn()-posHSharedBtn, WHITE, 1);
		} else if (active_SharedStashInMultiPlayer == 1) {
			lpText = getLocalString(STR_TOGGLE_MULTI_DISABLED);
			D2PrintPopup(lpText, getXPreviousIndexBtn()+posWPreviousIndexBtn/2, getYPreviousIndexBtn()-posHPreviousIndexBtn, WHITE, 1);
		}

	} else if (isOnButtonPreviousIndexStash(mx,my)) {
		lpText = getLocalString(STR_STASH_PREVIOUS_INDEX);
		D2PrintPopup(lpText, getXPreviousIndexBtn()+posWPreviousIndexBtn/2, getYPreviousIndexBtn()-posHPreviousIndexBtn, WHITE, 1);

	} else if (isOnButtonNextIndexStash(mx,my))	{
		lpText = getLocalString(STR_STASH_NEXT_INDEX);
		D2PrintPopup(lpText, getXNextIndexBtn()+posWNextIndexBtn/2, getYNextIndexBtn()-posHNextIndexBtn, WHITE, 1);

	} else if (active_sharedGold && isOnButtonPutGold(mx,my))	{
		lpText = getLocalString(STR_PUT_GOLD);
		D2PrintPopup(lpText, getXPutGoldBtn()+posWPutGoldBtn/2, getYPutGoldBtn()-posHPutGoldBtn, WHITE, 1);

	} else if (active_sharedGold && isOnButtonTakeGold(mx,my))	{
		lpText = getLocalString(STR_TAKE_GOLD);
		D2PrintPopup(lpText, getXTakeGoldBtn()+posWTakeGoldBtn/2, getYTakeGoldBtn()-posHTakeGoldBtn, WHITE, 1);
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
	else if (isOnStashNameField(msg->x,msg->y))
		isDownBtn.stashName = 1;
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

	} else if (isOnStashNameField(msg->x,msg->y)) {
		log_msg("push up left Stash Name\n");
		if (isDownBtn.stashName && PCPY->currentStash)
		{
			if (GetKeyState(VK_SHIFT)<0)
			{
				WCHAR text[21];
				getCurrentStashName(text, 21, ptChar);
				D2TogglePage(5,0,0);// Open command window
				_snwprintf(ptInputCommand, 25, L"/rp %s", text);
				InputCommandLen = wcslen(ptInputCommand);
			}
			else if (PCPY->currentStash->isMainIndex)
				updateServer(US_RESET_INDEX);
			else if (PCPY->currentStash->isIndex)
				updateServer(US_SET_MAIN_INDEX);
			else
				updateServer(US_SET_INDEX);
		}

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

	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();
	Unit* ptChar = D2GetClientPlayer();
	WCHAR popupText[0x400];

	if (!PCPY->currentStash)
		D2PrintString(getLocalString(STR_NO_SELECTED_PAGE), x, y, WHITE, bfalse);
	else
	{
		bool isShared = PCPY->currentStash->isShared;
		bool isIndex = PCPY->currentStash->isIndex;
		bool isMainIndex = PCPY->currentStash->isMainIndex;
		DWORD currentId = PCPY->currentStash->id + 1;

		WCHAR text[21];
		getCurrentStashName(text, 21, ptChar);

		// Replace character # by number page.
		int j = 0;
		for (int i=0; text[i]; i++)
		{
			if (text[i] == L'#')
			{
				DWORD val = currentId;
				int nbDigits = 0;
				do
				{
					nbDigits++;
					val /= 10;
				} while(val);
				j += nbDigits;

				val = currentId;
				nbDigits = 0;
				do
				{
					nbDigits++;
					popupText[j - nbDigits] = (WCHAR)(val % 10 + 48);
					val /= 10;
				} while(val);
			}
			else
				popupText[j++] = text[i];
		}
		popupText[j] = NULL;

		// Check text length vs field name length
		int pixelLen = D2GetPixelLen(popupText);
		int len = wcslen(popupText);
		while(len > 0 && pixelLen > posWStashNameField - 5)
		{
			len--;
			popupText[len] = NULL;
			pixelLen = D2GetPixelLen(popupText);
		}

		DWORD color = isShared ? (isMainIndex ? SharedMainIndexPageColor : isIndex ? SharedIndexPageColor : SharedNormalPageColor) : (isMainIndex ? PersonalMainIndexPageColor : isIndex ? PersonalIndexPageColor : PersonalNormalPageColor);
		D2PrintString(popupText, x, y, color, bfalse);

		if (isOnStashNameField(mx, my))
		{
			_snwprintf(popupText, 0x400, getLocalString(STR_PAGE_TYPE_CHANGE), currentId);
			D2PrintPopup(popupText, getXStashNameField() + posWStashNameField/2, getYStashNameField() - posHStashNameField - 2, WHITE, 1);
		}
	}

	//printGoldMaxPopup
	if (isOnStashGoldField(mx, my))
	{
		if (active_sharedGold)
		{
			_snwprintf(popupText, 0x400, L"%s\n%s: %u", maxGoldText, getLocalString(STR_SHARED_GOLD_QUANTITY), PCPY->sharedGold);
			D2PrintPopup(popupText, getXStashGoldField() + posWStashGoldField/2, getYStashGoldField() - posHStashGoldField - 2, WHITE, 1);
		} else
			D2PrintPopup(maxGoldText, getXStashGoldField() + posWStashGoldField/2, getYStashGoldField() - posHStashGoldField - 2, WHITE, 1);
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

FCT_ASM( caller_manageBtnDown_114 )
	PUSH EBX
	CALL manageBtnDown
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0xA]
	MOV DWORD PTR DS:[EDX],1
	POP EDI
	POP ESI
	POP EBX
	MOV ESP,EBP
	POP EBP
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2ClickOnStashButton
}}

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

FCT_ASM( caller_manageBtnUp_114 )
	PUSH EBX
	CALL manageBtnUp
	MOV isDownBtn.all,0
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0x33]
	MOV DWORD PTR DS:[EDX],0
	SUB EDX,8
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,4
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,0x64
	MOV DWORD PTR DS:[EDX],0
	POP EDI
	POP ESI
	POP EBX
	MOV ESP,EBP
	POP EBP
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2ClickOnStashButton
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

FCT_ASM ( initBtnsStates_114 )
	MOV isDownBtn.all,0
	POP ECX
	MOV ESP,EBP
	POP EBP
	RETN
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
	mem_seek R8(D2Client, 39060, 39060, 3F399, B1006, 7DF86, B3656, 99A56, 9DE26, 8F308);
	MEMC_REF4( D2LoadBuySelBtn, printBtns);
	//6FADF398  |. E8 734D0400    CALL D2Client.6FB24110
	//6FB61005  |. E8 A6D3FEFF    CALL D2Client.6FB4E3B0
	//6FB2DF85  |. E8 3642FEFF    CALL D2Client.6FB121C0
	//6FB63655  |. E8 9682FDFF    CALL D2Client.6FB3B8F0
	//6FB49A55  |. E8 96500200    CALL D2Client.6FB6EAF0
	//6FB4DE25  |. E8 76ACF7FF    CALL D2Client.6FAC8AA0
	//0048F307  |. E8 F452FCFF    CALL Game.00454600

	// print page number
	mem_seek R8(D2Client, 3903C, 3903C, 3F375, B0FE3, 7DF63, B3633, 99A33, 9DE03, 8F2E5);
	MEMJ_REF4( D2PrintString, printPageNumber);
	//6FADF374  |. E8 3FCC0800    CALL <JMP.&D2Win.#10117>
	//6FB60FE2  |. E8 99C2F5FF    CALL <JMP.&D2Win.#10020>
	//6FB2DF62  |. E8 19F3F8FF    CALL <JMP.&D2Win.#10064>
	//6FB63632  |. E8 299DF5FF    CALL <JMP.&D2Win.#10001>
	//6FB49A32  |. E8 4739F7FF    CALL <JMP.&D2Win.#10150>
	//6FB4DE02  |. E8 4739F7FF    CALL <JMP.&D2Win.#10076>
	//0048F2E4  |. E8 37300700    CALL Game.00502320                       ; \Game.00502320

	// Manage mouse down (Play sound)
	mem_seek R8(D2Client, 45091, 45091, 4BBA1, B4666, 7FDD6, B54A6, 9B8A6, 9FC76, 925B8);
	MEMC_REF4( version_D2Client >= V111 ? (DWORD)D2ClickOnStashButton : (DWORD)D2isLODGame, version_D2Client >= V114a ? caller_manageBtnDown_114 : version_D2Client >= V111 ? caller_manageBtnDown_111 : caller_manageBtnDown);
	//6FAEBBA0   > E8 DB04FCFF    CALL D2Client.6FAAC080
	//6FB64665   . E8 B61EFFFF    CALL D2Client.6FB56520
	//6FB2FDD5   . E8 E612FFFF    CALL D2Client.6FB210C0
	//6FB654A5   . E8 9611FFFF    CALL D2Client.6FB56640
	//6FB4B8A5   . E8 5614FFFF    CALL D2Client.6FB3CD00
	//6FB4FC75   . E8 960FFFFF    CALL D2Client.6FB40C10
	//004925B7  |. E8 C473FFFF    CALL Game.00489980

	// Manage mouse up
	mem_seek R8(D2Client, 455F9, 455F9, 4C0F9, B57B9, 7FC09, B52D9, 9B6D9, 9FAA9, 89B63);
	MEMC_REF4( version_D2Client >= V111 ? (DWORD)D2ClickOnStashButton : (DWORD)D2isLODGame, version_D2Client >= V114a ? caller_manageBtnUp_114 : version_D2Client >= V111 ? caller_manageBtnUp_111 : caller_manageBtnUp);
	//6FAEC0F8   > E8 83FFFBFF    CALL D2Client.6FAAC080
	//6FB657B8   > E8 630DFFFF    CALL D2Client.6FB56520
	//6FB2FC08   > E8 B314FFFF    CALL D2Client.6FB210C0
	//6FB652D8   > E8 6313FFFF    CALL D2Client.6FB56640
	//6FB4B6D8   > E8 2316FFFF    CALL D2Client.6FB3CD00
	//6FB4FAA8   > E8 6311FFFF    CALL D2Client.6FB40C10
	//00489B62  |> E8 19FEFFFF    CALL Game.00489980

	// init state of button on open stash page
	mem_seek R8(D2Client, 45B3A, 45B3A, 4C63A, A645A, 749DA, A9D9A, 8CC3A, 9441A, 89ED5);
	if (version_D2Client >= V114d)
	{
		memt_byte( 0x8B, 0xE9 );	// CALL initBtnsStates
		MEMT_REF4( 0xCCC35DE5, initBtnsStates_114);
	} else {
		memt_byte( 0x81, 0xE9 );	// CALL initBtnsStates
		MEMT_REF4( 0x000104C4, initBtnsStates);
		memt_byte( 0x00, 0x90 );
	}
	//6FAE5B3A  |> 81C4 04010000  ADD ESP,104
	//6FAE5B3A  |> 81C4 04010000  ADD ESP,104
	//6FAEC63A  |> 81C4 04010000  ADD ESP,104
	//6FB5645A  |> 81C4 04010000  ADD ESP,104
	//6FB249DA  |> 81C4 04010000  ADD ESP,104
	//6FB59D9A  |> 81C4 04010000  ADD ESP,104
	//6FB3CC3A  |> 81C4 04010000  ADD ESP,104
	//6FB4441A  |> 81C4 04010000  ADD ESP,104
	//00489ED5  |> 8BE5           MOV ESP,EBP
	//00489ED7  |. 5D             POP EBP
	//00489ED8  \. C3             RETN
	//00489ED9     CC             INT3

	// init the search of print in green the item set name we have in stash
	mem_seek R8(D2Client, 3F098, 3F098, 45997, A71F4, 71F64, A7314, 8D434, 91A24, 86774);
	MEMJ_REF4( D2InventoryGetFirstItem, initGetNextItemForSet);
	//6FAE5996  |. E8 D5500800    CALL <JMP.&D2Common.#10277>
	//6FB571F3  |. E8 D64EF6FF    CALL <JMP.&D2Common.#10402>
	//6FB21F63  |. E8 96A1F9FF    CALL <JMP.&D2Common.#10535>
	//6FB57313  |. E8 8250F6FF    CALL <JMP.&D2Common.#11151>
	//6FB3D433  |. E8 B8F0F7FF    CALL <JMP.&D2Common.#10460>
	//6FB41A23  |. E8 96A7F7FF    CALL <JMP.&D2Common.#11040>
	//00486773  |. E8 484B1B00    CALL Game.0063B2C0                       ; \Game.0063B2C0

	// Get next item for print in green the item set name we have in stash
	mem_seek R8(D2Client, 3F0FA, 3F0FA, 45A1C, A728B, 71FFB, A73AB, 8D4CB, 91ABB, 86807);
	MEMJ_REF4( D2UnitGetNextItem, getNextItemForSet);
	//6FAE5A1B   E8 4A500800      CALL <JMP.&D2Common.#10304>
	//6FB5728A  |. E8 0B4FF6FF    |CALL <JMP.&D2Common.#10934>
	//6FB21FFA  |. E8 A1A1F9FF    |CALL <JMP.&D2Common.#11140>
	//6FB573AA  |. E8 7550F6FF    |CALL <JMP.&D2Common.#10770>
	//6FB3D4CA  |. E8 99F0F7FF    |CALL <JMP.&D2Common.#10464>
	//6FB41ABA  |. E8 A3A8F7FF    |CALL <JMP.&D2Common.#10879>
	//00486806  |. E8 95771B00    |CALL Game.0063DFA0                      ; \Game.0063DFA0

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/