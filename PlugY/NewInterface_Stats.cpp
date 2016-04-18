/*=================================================================
	File created by Yohann NICOLAS.

	Interface functions

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "updateServer.h"	// Install_UpdateServer()
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "statsPoints.h"
#include "newInterfaces.h"
#include <stdio.h>


#define	getXCloseBtn()			360
#define	getLCloseBtn()			32
#define	getYCloseBtn()			(ResolutionY - 60)
#define	getHCloseBtn()			32
#define isOnCloseBtn(x,y) isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), getLCloseBtn(), getHCloseBtn())

#define	getXPreviousPageBtn()		RX(0x19)//0x70
#define	getLPreviousPageBtn()		32
#define	getYPreviousPageBtn()		RY(0x40)
#define	getHPreviousPageBtn()		32
#define isOnPreviousPageBtn(x,y)	isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())

#define	getXNextPageBtn()		RX(D2GetResolution()?0x43:0x8A)
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(D2GetResolution()?0x40:0x70)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())

/*
#define	getXNextPageBtn()		120
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		(ResolutionY - 60)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())
*/


#define	getLAssignBtn()			32
#define	getHAssignBtn()			32

#define	getXAssSTRBtn()			0x7D+35
#define	getYAssSTRBtn()			0x6A
#define isOnAssSTRBtn(x,y) isOnRect(x, y, getXAssSTRBtn(), getYAssSTRBtn(), getLAssignBtn(), getHAssignBtn())

#define	getXAssDEXBtn()			0x7D+35
#define	getYAssDEXBtn()			0xA8
#define isOnAssDEXBtn(x,y) isOnRect(x, y, getXAssDEXBtn(), getYAssDEXBtn(), getLAssignBtn(), getHAssignBtn())

#define	getXAssVITBtn()			0x7D+35
#define	getYAssVITBtn()			0xFE
#define isOnAssVITBtn(x,y) isOnRect(x, y, getXAssVITBtn(), getYAssVITBtn(), getLAssignBtn(), getHAssignBtn())

#define	getXAssENEBtn()			0x7D+35
#define	getYAssENEBtn()			0x13C
#define isOnAssENEBtn(x,y) isOnRect(x, y, getXAssENEBtn(), getYAssENEBtn(), getLAssignBtn(), getHAssignBtn())


#define	getLUnassignBtn()		32
#define	getHUnassignBtn()		32

#define	getXUnaSTRBtn()			0x7D
#define	getYUnaSTRBtn()			getYAssSTRBtn()
#define isOnUnaSTRBtn(x,y) isOnRect(x, y, getXUnaSTRBtn(), getYUnaSTRBtn(), getLUnassignBtn(), getHUnassignBtn())

#define	getXUnaDEXBtn()			0x7D
#define	getYUnaDEXBtn()			getYAssDEXBtn()
#define isOnUnaDEXBtn(x,y) isOnRect(x, y, getXUnaDEXBtn(), getYUnaDEXBtn(), getLUnassignBtn(), getHUnassignBtn())

#define	getXUnaVITBtn()			0x7D
#define	getYUnaVITBtn()			getYAssVITBtn()
#define isOnUnaVITBtn(x,y) isOnRect(x, y, getXUnaVITBtn(), getYUnaVITBtn(), getLUnassignBtn(), getHUnassignBtn())

#define	getXUnaENEBtn()			0x7D
#define	getYUnaENEBtn()			getYAssENEBtn()
#define isOnUnaENEBtn(x,y) isOnRect(x, y, getXUnaENEBtn(), getYUnaENEBtn(), getLUnassignBtn(), getHUnassignBtn())



void** ptD2RemainingStatsPointsBoxImages = (void**)0x6FBB5E50;
#define D2RemainingStatsPointsBoxImages (*ptD2RemainingStatsPointsBoxImages)

void** ptD2AssignStatsPointsBoxImages = (void**)0x6FBB5BB8;
#define D2AssignStatsPointsBoxImages (*ptD2AssignStatsPointsBoxImages)

void** ptD2AssignStatsPointsBtnImages = (void**)0x6FBB5BB4;
#define D2AssignStatsPointsBtnImages (*ptD2AssignStatsPointsBtnImages)



static struct
{
	union{
		DWORD all;
		struct{
			DWORD close:1;
			DWORD AssSTR:1;
			DWORD AssDEX:1;
			DWORD AssVIT:1;
			DWORD AssENE:1;
			DWORD UnaSTR:1;
			DWORD UnaDEX:1;
			DWORD UnaVIT:1;
			DWORD UnaENE:1;
			DWORD previousPage:1;
			DWORD nextPage:1;
		};
	};
} isDownBtn;


void print2Lines(WORD id, LPWSTR lpText, DWORD x, DWORD l, DWORD y)
{
	wcsncpy(lpText, D2GetStringFromIndex(id), 0x63);
	lpText[0x64]= L'\0';
	
	LPWSTR lptmp = lpText;
	while (*lptmp)
	{
		if (*lptmp==L'\n')
		{
			*lptmp = L'\0';
			if (*(++lptmp))
			{
				DWORD nbPixel = D2GetPixelLen(lpText);
				D2PrintString(lpText, MILIEU(x,l,nbPixel), y-4, WHITE, 0);
				nbPixel = D2GetPixelLen(lptmp);
				D2PrintString(lptmp, MILIEU(x,l,nbPixel), y+4, WHITE, 0);
				return;
			}
			break;
		}
		lptmp++;
	}
	DWORD nbPixel = D2GetPixelLen(lpText);
	D2PrintString(lpText, MILIEU(x,l,nbPixel), y, WHITE, 0);
}


#define BUFSIZE 0x80
void STDCALL printNewStatsPage()
{
	if (!D2isLODGame() || !D2GetResolution()) return D2PrintStatsPage();
	
	WCHAR text[BUFSIZE];
	LPWSTR lpText;
	DWORD nbPixel;
	DWORD curValue,baseValue,color;
	DWORD x1,y1,reset=0;
	bDontPrintBorder = true;

	int curRes,maxRes;

	Unit* ptChar = D2GetClientPlayer();

	d2_assert(!ptChar, "Printing stats page : no character selected",__FILE__,__LINE__);
	d2_assert(ptChar->nUnitType != UNIT_PLAYER, "Printing stats page : bad unit type",__FILE__,__LINE__);

	//Init data for print image
	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));

	//print background
/*	setImage(&data, newStatsInterfaceImages);
	setFrame(&data, 0);
	D2PrintImage(&data, 0,	256, -1, 5, 0);
	setFrame(&data, 1);
	D2PrintImage(&data, 256,256, -1, 5, 0);
	setFrame(&data, 2);
	D2PrintImage(&data, 0,	512, -1, 5, 0);
	setFrame(&data, 3);
	D2PrintImage(&data, 256,512, -1, 5, 0);
	setFrame(&data, 4);
	D2PrintImage(&data, 0,	552, -1, 5, 0);
	setFrame(&data, 5);
	D2PrintImage(&data, 256,552, -1, 5, 0);
*/
	fillRect(0,0,400,552,0,5);

	//print button close
	setImage(&data, D2LoadBuySelBtn());
	setFrame(&data, 10 + isDownBtn.close);
	D2PrintImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);

	//print previous page button
	setFrame(&data, 12 + isDownBtn.previousPage);
	D2PrintImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);

	//print next page button
	setFrame(&data, 14 + isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	DifficultyLevelsBIN* difficultyLevels = D2GetDifficultyLevelsBIN (D2GetDifficultyLevel());

	//print fixed text
	D2SetFont(6);
	print2Lines(0xFD9, text, 0x0B,	0x29,	0x2C); //level					//0x34-0xB
	print2Lines(0xFDA, text, 0x41,	0x73,	0x2C); //Experience				//0xB4-0x41
	print2Lines(0xFDB, text, 0xC1,	0x73,	0x2C); //Next Level				//0x134-0xC1
	print2Lines(0xFDC, text, 0x0A,	0x3F,	0x61); //Strengh				//0x49-0xA
	print2Lines(0xFDE, text, 0x0A,	0x3F,	0xA0); //Dexterity				//0x49-0xA
	print2Lines(0xFE0, text, 0xAE,	0x5E,	0xCF); //Defence				//0x10C-0xAE
	print2Lines(0xFE2, text, 0x0A,	0x3F,	0xF5); //Vitality				//0x49-0xA
	print2Lines(0xFE3, text, 0xAE,	0x36,	0xF5); //Stamina				//0xE4-0xAE
	print2Lines(0xFE4, text, 0xAE,	0x36,	0x10D);//Life					//0xE4-0xAE
	print2Lines(0xFE5, text, 0x0A,	0x3F,	0x133);//Energy					//0x49-0xA
	print2Lines(0xFE6, text, 0xAE,	0x36,	0x133);//Mana					//0xE4-0xAE
	print2Lines(0xFE7, text, 0xBE,	0x4E,	0x15A);//Fire.Resistance		//0x10C-0xBE
	print2Lines(0xFE8, text, 0xBE,	0x4E,	0x172);//Cold.Resistance		//0x10C-0xBE
	print2Lines(0xFE9, text, 0xBE,	0x4E,	0x18B);//Lightning.Resistance	//0x10C-0xBE
	print2Lines(0xFEA, text, 0xBE,	0x4E,	0x1A3);//Poison.Resistance		//0x10C-0xBE

	// print class
	D2SetFont(1);
	lpText = charStats->nameU;
	nbPixel = D2GetPixelLen(lpText);
	D2PrintString(lpText, MILIEU(0xC1,0x76,nbPixel), 0x19, WHITE, 0);

	// print name
	char* string = PCPlayerData->name;
	int usize = strlen(string);
	if (usize>9)
		D2SetFont(usize < 12?0:6);
	mbstowcs(text,string,BUFSIZE);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0xD,0x94,nbPixel), 0x19, WHITE, 0);

	D2SetFont(1);

	// print level value
	curValue = D2GetPlayerStat(ptChar, STATS_LEVEL, 0);
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_LEVEL, 0);
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;
	swprintf(text,L"%ld",curValue);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0xD,0x29,nbPixel), 0x3B, color, 0);//ESI,EBX,EDI

if (version_D2Client <= V110)
{
	//print Experience
	curValue = D2GetPlayerStat(ptChar, STATS_EXPERIENCE, 0);
	D2PrintBigNumber(text, curValue, BUFSIZE);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x43,0x72,nbPixel), 0x3B, WHITE, 0);

	//print next level
	DWORD plvl = D2GetPlayerBaseStat(ptChar, STATS_LEVEL, 0);
	if (plvl < D2GetMaxLevel(ptChar->nPlayerClass))
		curValue = D2GetNextLevelXP(ptChar->nPlayerClass, plvl);
	else
		curValue = D2GetPlayerStat(ptChar, STATS_NEXTEXP, 0);
	D2PrintBigNumber(text,curValue,BUFSIZE);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0xC3,0x72,nbPixel), 0x3B, WHITE, 0);

	//print strength
	curValue = D2GetPlayerStat(ptChar, STATS_STRENGTH, 0);
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0);
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;
	swprintf(text,L"%ld",curValue);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x4D,0x24,nbPixel), 0x63, color, 0);//ESI,EBX,EDI

	//print dexterity
	curValue = D2GetPlayerStat(ptChar, STATS_DEXTERITY, 0);
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0);
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;
	swprintf(text,L"%ld",curValue);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x4D,0x24,nbPixel), 0xA1, color, 0);//ESI,EBX,EDI

	//print vitality
	curValue = D2GetPlayerStat(ptChar, STATS_VITALITY, 0);
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0);
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;
	swprintf(text,L"%ld",curValue);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x4D,0x24,nbPixel), 0xF7, color, 0);//ESI,EBX,EDI

	//print energy
	curValue = D2GetPlayerStat(ptChar, STATS_ENERGY, 0);
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0);
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color=0;
	swprintf(text,L"%ld",curValue);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x4D,0x24,nbPixel), 0x134, color, 0);//ESI,EBX,EDI


	//print max stamina
	curValue = D2GetPlayerStat(ptChar, STATS_MAXSTAMINA, 0) / 256;
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_MAXSTAMINA, 0) / 256;
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;
	swprintf(text,L"%ld",curValue);

	if (curValue > 999) reset=1;
	D2GetPixelRect(text,&x1,&y1);
	if (0x24<x1) reset = 1;
	if (reset) D2SetFont(0);

	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0xE8,0x24,nbPixel), 0xF6, color, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}


	//print stamina
	curValue = D2GetPlayerStat(ptChar, STATS_STAMINA, 0) / 256;
	swprintf(text,L"%ld",curValue);

	if (curValue > 999) reset=1;
	D2GetPixelRect(text,&x1,&y1);
	if (0x24<x1) reset = 1;
	if (reset) D2SetFont(0);

	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x24,nbPixel), 0xF6, WHITE, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}

	//print max Hit Point
	curValue = D2GetPlayerStat(ptChar, STATS_MAXHP, 0) / 256;
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_MAXHP, 0) / 256;
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;

	swprintf(text,L"%ld",curValue);

	if (curValue > 999) reset=1;
	D2GetPixelRect(text,&x1,&y1);
	if (0x24<x1) reset = 1;
	if (reset) D2SetFont(0);

	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0xE8,0x24,nbPixel), 0x10E, color, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}



	//print Hit Point
	curValue = D2GetPlayerStat(ptChar, STATS_HP, 0) / 256;
	if ((ptChar->CurrentAnim != 0x11) && !curValue) curValue=1;

	swprintf(text,L"%ld",curValue);

	if (curValue > 999) reset=1;
	D2GetPixelRect(text,&x1,&y1);
	if (0x24<x1) reset = 1;
	if (reset) D2SetFont(0);

	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x24,nbPixel), 0x10E, WHITE, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}


	//print max mana
	curValue = D2GetPlayerStat(ptChar, STATS_MAXMANA, 0) / 256;
	baseValue = D2GetPlayerBaseStat(ptChar, STATS_MAXMANA, 0) / 256;
	if (curValue != baseValue) color = curValue < baseValue ? RED : BLUE;
	else color = WHITE;

	swprintf(text,L"%ld",curValue);

	if (curValue > 999) reset=1;
	D2GetPixelRect(text,&x1,&y1);
	if (0x24<x1) reset = 1;
	if (reset) D2SetFont(0);

	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0xE8,0x24,nbPixel), 0x134, color, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}


	//print mana
	curValue = D2GetPlayerStat(ptChar, STATS_MANA, 0) / 256;
	swprintf(text,L"%ld",curValue);

	if (curValue > 999) reset=1;
	D2GetPixelRect(text,&x1,&y1);
	if (0x24<x1) reset = 1;
	if (reset) D2SetFont(0);

	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x24,nbPixel), 0x134, WHITE, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}


	// print defence
	curValue = D2GetDefence(ptChar);
	color = D2haveDefenceBonus(ptChar) ? BLUE : WHITE;
	if (PCInventory && D2Common10273(PCInventory,0) && D2isInState(ptChar,0x65))
		color = BLUE;
	if (D2haveDefenceMalus(ptChar)) color = RED;

	if ( D2GetLang() == LNG_JPN)
	{
		D2GetPixelRect(text,&x1,&y1);
		if ((0x24<x1) || (curValue > 999))
			{reset = 1; D2SetFont(0);}
	}

	swprintf(text,L"%ld",curValue);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x23,nbPixel), 0xD1, color, 0);//ESI,EBX,EDI
	if (reset) {D2SetFont(1); reset=0;}


	//print fire resistance
	curRes = D2GetPlayerStat(ptChar, STATS_FIRERESIST, 0) + difficultyLevels->resistPenalty;
	color = D2haveFireResBonus(ptChar) ? BLUE : WHITE;
	if (D2haveFireResMalus(ptChar)) color = RED;
	maxRes = 75 + D2GetPlayerStat(ptChar, STATS_MAXFIRERESIST, 0);
	if (maxRes>95) maxRes = 95;
	if (curRes < -100) curRes=-100;
	if (curRes > maxRes) curRes = maxRes;
	if ((curRes == maxRes) && (color != BLUE)) color = GOLD;
	else if (curRes < 0) color = RED;

	swprintf(text,L"%ld",curRes);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x23,nbPixel), 0x15C, color, 0);//ESI,EBX,EDI

	//print lightning resistance
	curRes = D2GetPlayerStat(ptChar, STATS_LIGHTRESIST, 0) + difficultyLevels->resistPenalty;
	color = D2haveLightResBonus(ptChar) ? BLUE : WHITE;
	if (D2haveLightResMalus(ptChar)) color = RED;
	maxRes = 75 + D2GetPlayerStat(ptChar, STATS_MAXLIGHTRESIST, 0);
	if (maxRes>95) maxRes = 95;
	if (curRes < -100) curRes=-100;
	if (curRes > maxRes) curRes = maxRes;
	if ((curRes == maxRes) && (color != BLUE)) color = GOLD;
	else if (curRes < 0) color = RED;

	swprintf(text,L"%ld",curRes);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x23,nbPixel), 0x174, color, 0);//ESI,EBX,EDI

	//print cold resistance
	curRes = D2GetPlayerStat(ptChar, STATS_COLDRESIST, 0) + difficultyLevels->resistPenalty;
	color = D2haveColdResBonus(ptChar) ? BLUE : WHITE;
	if (D2haveColdResMalus(ptChar)) color = RED;
	maxRes = 75 + D2GetPlayerStat(ptChar, STATS_MAXCOLDRESIST, 0);
	if (maxRes>95) maxRes = 95;
	if (curRes < -100) curRes=-100;
	if (curRes > maxRes) curRes = maxRes;
	if ((curRes == maxRes) && (color != BLUE)) color = GOLD;
	else if (curRes < 0) color = RED;

	swprintf(text,L"%ld",curRes);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x23,nbPixel), 0x18C, color, 0);//ESI,EBX,EDI

	//print poison resistance
	curRes = D2GetPlayerStat(ptChar, STATS_POISONRESIST, 0) + difficultyLevels->resistPenalty;
	color = D2havePoisonResBonus(ptChar) ? BLUE : WHITE;
	if (D2havePoisonResMalus(ptChar)) color = RED;
	maxRes = 75 + D2GetPlayerStat(ptChar, STATS_MAXPOISONRESIST, 0);
	if (maxRes>95) maxRes = 95;
	if (curRes < -100) curRes=-100;
	if (curRes > maxRes) curRes = maxRes;
	if ((curRes == maxRes) && (color != BLUE)) color = GOLD;
	else if (curRes < 0) color = RED;

	swprintf(text,L"%ld",curRes);
	nbPixel = D2GetPixelLen(text);
	D2PrintString(text, MILIEU(0x111,0x23,nbPixel), 0x1A4, color, 0);//ESI,EBX,EDI


//////////////////// STAT POINTS REMAINING MANAGEMENT ////////////////////
	//print Assign box of btns : Str,Dex,Ene,Vit
	setImage(&data, D2AssignStatsPointsBoxImages);
	setFrame(&data, 0);
	D2PrintImage(&data, getXAssSTRBtn()-3, getYAssSTRBtn()+4, -1, 5, 0);
	D2PrintImage(&data, getXAssDEXBtn()-3, getYAssDEXBtn()+4, -1, 5, 0);
	D2PrintImage(&data, getXAssENEBtn()-3, getYAssENEBtn()+4, -1, 5, 0);
	D2PrintImage(&data, getXAssVITBtn()-3, getYAssVITBtn()+4, -1, 5, 0);

	DWORD nbStatPointsRemaining = D2GetPlayerBaseStat(ptChar, 4, 0);
	if (nbStatPointsRemaining)
	{
		//print stat point remaining box image
		setImage(&data, D2RemainingStatsPointsBoxImages);
		setFrame(&data, 0);
		D2PrintImage(&data, 3, 0x16C, -1, 5, 0);

		//print "Stat Points Remaining"
		D2SetFont(6);
		lpText = D2GetStringFromIndex(0xFEB);
		nbPixel = D2GetPixelLen(lpText);
		D2PrintString(lpText, MILIEU(11,78,nbPixel), 0x163, RED, 0);//163
		lpText = D2GetStringFromIndex(0xFEC);
		nbPixel = D2GetPixelLen(lpText);
		D2PrintString(lpText, MILIEU(11,78,nbPixel), 0x16B, RED, 0);

		//print Stat Points Remaining number
		D2SetFont(1);
		swprintf(text, L"%i", nbStatPointsRemaining);
		nbPixel = D2GetPixelLen(text);
		D2PrintString(text, MILIEU(92,36,nbPixel), 0x168, WHITE, 0);

		setImage(&data, D2AssignStatsPointsBtnImages);
		setFrame(&data, isDownBtn.AssSTR);
		D2PrintImage(&data, getXAssSTRBtn(), getYAssSTRBtn(), -1, 5, 0);
		setFrame(&data, isDownBtn.AssDEX);
		D2PrintImage(&data, getXAssDEXBtn(), getYAssDEXBtn(), -1, 5, 0);
		setFrame(&data, isDownBtn.AssVIT);
		D2PrintImage(&data, getXAssVITBtn(), getYAssVITBtn(), -1, 5, 0);
		setFrame(&data, isDownBtn.AssENE);
		D2PrintImage(&data, getXAssENEBtn(), getYAssENEBtn(), -1, 5, 0);
	} else {
		setImage(&data, D2AssignStatsPointsBtnImages);
		setFrame(&data, 2);
		D2PrintImage(&data, getXAssSTRBtn(), getYAssSTRBtn(), -1, 5, 0);
		D2PrintImage(&data, getXAssDEXBtn(), getYAssDEXBtn(), -1, 5, 0);
		D2PrintImage(&data, getXAssVITBtn(), getYAssVITBtn(), -1, 5, 0);
		D2PrintImage(&data, getXAssENEBtn(), getYAssENEBtn(), -1, 5, 0);
	}
	
	if (active_StatsPoints && !onRealm)
	{
		setImage(&data, D2AssignStatsPointsBoxImages);
		setFrame(&data, 0);
		D2PrintImage(&data, getXUnaSTRBtn()-3, getYUnaSTRBtn()+4, -1, 5, 0);
		D2PrintImage(&data, getXUnaDEXBtn()-3, getYUnaDEXBtn()+4, -1, 5, 0);
		D2PrintImage(&data, getXUnaENEBtn()-3, getYUnaENEBtn()+4, -1, 5, 0);
		D2PrintImage(&data, getXUnaVITBtn()-3, getYUnaVITBtn()+4, -1, 5, 0);

		setImage(&data, unassignStatsBtnImages);
		if ((int)charStats->baseSTR < D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0))
			setFrame(&data, isDownBtn.UnaSTR);
		else data.frame = 2;
		D2PrintImage(&data, getXUnaSTRBtn(), getYUnaSTRBtn(), -1, 5, 0);

		if ((int)charStats->baseDEX < D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0))
			setFrame(&data, isDownBtn.UnaDEX);
		else setFrame(&data, 2);
		D2PrintImage(&data, getXUnaDEXBtn(), getYUnaDEXBtn(), -1, 5, 0);

		if ((int)charStats->baseVIT < D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0))
			setFrame(&data, isDownBtn.UnaVIT);
		else setFrame(&data, 2);
		D2PrintImage(&data, getXUnaVITBtn(), getYUnaVITBtn(), -1, 5, 0);

		if ((int)charStats->baseENE < D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0))
			setFrame(&data, isDownBtn.UnaENE);
		else setFrame(&data, 2);
		D2PrintImage(&data, getXUnaENEBtn(), getYUnaENEBtn(), -1, 5, 0);
	}
}

//////////////////// POPUP PRINTING ////////////////////
	//set MouseX & MouseY
	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();


	if (isOnCloseBtn(x,y))			// print popup "close"
	{
		//lpText = D2GetStringFromIndex(0x1030);
		//nbPixel = D2GetPixelLen(lpText);
		//D2PrintPopup(lpText, getXCloseBtn()+getLCloseBtn()/2-nbPixel/2, getYCloseBtn()-getHCloseBtn(), WHITE, 0);
		D2PrintPopup(D2GetStringFromIndex(0x1030), getXCloseBtn()+getLCloseBtn()/2, getYCloseBtn()-getHCloseBtn(), WHITE, 1);
	}
	else if (isOnPreviousPageBtn(x,y))	//print popup "previous page"
	{
		lpText = getTranslatedString(STR_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousPageBtn()+getLPreviousPageBtn()/2, getYPreviousPageBtn()-getHPreviousPageBtn(), WHITE, 1);
	}
	else if (isOnNextPageBtn(x,y))	//print popup "next page"
	{
		lpText = getTranslatedString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn()+getLNextPageBtn()/2, getYNextPageBtn()-getHNextPageBtn(), WHITE, 1);
	}
	else if (isOnRect(x, y, 0xAD, 0x137, 0x15, 0x13))
	{
if ( version_D2Client <= V110 )
{
		DWORD avgChanceMonsterWillHitYou=53;//TODO
		if (avgChanceMonsterWillHitYou<5) 		avgChanceMonsterWillHitYou = 5;
		else if (avgChanceMonsterWillHitYou>95) avgChanceMonsterWillHitYou = 95;
		
		int chanceToBlock = D2GetChanceToBlock(ptChar, D2isLODGame());
		if (chanceToBlock <= 0)
		{
			//......TODO
			chanceToBlock=0;
		}

		int monsterID = D2GetLastMonsterIDFight();
		MonStatsBIN* monStats = SgptDataTables->monStats + monsterID;
		d2_assert((monsterID<0) || (monsterID >= (int)SgptDataTables->nbMonStats) || !monStats, "ptStats", __FILE__, __LINE__);
		LPWSTR monsterStr = D2GetStringFromIndex(monStats->monsterNameID);
		if (chanceToBlock)
			swprintf(text,D2GetStringFromIndex(0x2779),chanceToBlock,avgChanceMonsterWillHitYou,monsterStr,avgChanceMonsterWillHitYou);
		else
			swprintf(text,D2GetStringFromIndex(0x2778),monsterStr,avgChanceMonsterWillHitYou);
		//D2swprintf(0x80
		D2PrintTextPopup(text,0x8B,0xA5,*(BYTE*)0x6FBB1A50,2,WHITE);
}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

DWORD STDCALL mouseNewStatsPageLeftDown(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x,msg->y)) return 1;

	Unit* ptChar = D2GetClientPlayer();

	if (isOnCloseBtn(msg->x,msg->y))
	{
		log_msg("push down left button close\n");
		isDownBtn.close = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnPreviousPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button previous page\n");
		isDownBtn.previousPage = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (D2GetPlayerBaseStat(ptChar, 4, 0))
	{
		if (isOnAssSTRBtn(msg->x,msg->y))
		{
			log_msg("push down left button assign strengh\n");
			isDownBtn.AssSTR = 1;
			D2PlaySound(5,0,0,0,0);
		}
		else if (isOnAssDEXBtn(msg->x,msg->y))
		{
			log_msg("push down left button assign dexterity\n");
			isDownBtn.AssDEX = 1;
			D2PlaySound(5,0,0,0,0);
		}
		else if (isOnAssVITBtn(msg->x,msg->y))
		{
			log_msg("push down left button assign vitality\n");
			isDownBtn.AssVIT = 1;
			D2PlaySound(5,0,0,0,0);
		}
		else if (isOnAssENEBtn(msg->x,msg->y))
		{
			log_msg("push down left button assign energy\n");
			isDownBtn.AssENE = 1;
			D2PlaySound(5,0,0,0,0);
		}
	}
	if (active_StatsPoints && !onRealm)
	{
		CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
		if (isOnUnaSTRBtn(msg->x,msg->y) && ((int)charStats->baseSTR < D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0)))
		{
			log_msg("push down left button unassign strengh\n");
			isDownBtn.UnaSTR = 1;
			D2PlaySound(5,0,0,0,0);
		}
		else if (isOnUnaDEXBtn(msg->x,msg->y) && ((int)charStats->baseDEX < D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0)))
		{
			log_msg("push down left button unassign dexterity\n");
			isDownBtn.UnaDEX = 1;
			D2PlaySound(5,0,0,0,0);
		}
		else if (isOnUnaVITBtn(msg->x,msg->y) && ((int)charStats->baseVIT < D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0)))
		{
			log_msg("push down left button unassign vitality\n");
			isDownBtn.UnaVIT = 1;
			D2PlaySound(5,0,0,0,0);
		}
		else if (isOnUnaENEBtn(msg->x,msg->y) && ((int)charStats->baseENE < D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0)))
		{
			log_msg("push down left button unassign energy\n");
			isDownBtn.UnaENE = 1;
			D2PlaySound(5,0,0,0,0);
		}
	}

	freeMessage(msg);
	return 0;
}


void sendAssignStats(DWORD code, DWORD nbStatPointsRemaining)
{
	DWORD nbPoints = GetKeyState(VK_SHIFT)<0? nbStatPointsRemaining : 1;
	if (active_StatsShiftClickLimit && (nbPoints>limitValueToShiftClick)) 
		 nbPoints = limitValueToShiftClick;
	while ( nbPoints>0 )
	{
		DWORD nbTemp = nbPoints > 0x20 ? 0x20 : nbPoints;
		D2SendToServer3(0x3A, (WORD)(code + (nbTemp-1)*256));
		nbPoints -= nbTemp;
	}
}

DWORD STDCALL mouseNewStatsPageLeftUp(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

	if (!isOnStatsPage(msg->x,msg->y)) return 1;

	Unit* ptChar = D2GetClientPlayer();
	DWORD nbStatPointsRemaining = D2GetPlayerBaseStat(ptChar, 4, 0);

	if (isOnCloseBtn(msg->x,msg->y))
	{
		log_msg("push up left button close\n");
		if (isDownBtn.close)
			D2TogglePage(2,1,0);
	}
	else if (isOnPreviousPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button previous page\n");
		if (isDownBtn.previousPage)
		{
			GoStatPage(GetCurrentPage()-1);
			log_msg("previous page press\n");
		}
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button next page\n");
		if (isDownBtn.nextPage)
		{
			GoNextStatPage();
			log_msg("next page press\n");
		}
	}
	else if (nbStatPointsRemaining)
	{		
		if (isOnAssSTRBtn(msg->x,msg->y))
		{
			log_msg("push up left button assign strengh\n");
			if (isDownBtn.AssSTR)
				sendAssignStats(0,nbStatPointsRemaining);
		}
		else if (isOnAssDEXBtn(msg->x,msg->y))
		{
			log_msg("push up left button assign dexterity\n");
			if (isDownBtn.AssDEX)
				sendAssignStats(2,nbStatPointsRemaining);
		}
		else if (isOnAssVITBtn(msg->x,msg->y))
		{
			log_msg("push up left button assign vitality\n");
			if (isDownBtn.AssVIT)
				sendAssignStats(3,nbStatPointsRemaining);
		}
		else if (isOnAssENEBtn(msg->x,msg->y))
		{
			log_msg("push up left button assign energy\n");
			if (isDownBtn.AssENE)
				sendAssignStats(1,nbStatPointsRemaining);
		}
	}
	if (active_StatsPoints && !onRealm)
	{
		CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
		if (isOnUnaSTRBtn(msg->x,msg->y) && ((int)charStats->baseSTR < D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0)))
		{
			log_msg("push up left button unassign strengh\n");
			if (isDownBtn.UnaSTR)
				if (GetKeyState(VK_SHIFT)<0)
					updateServer(US_UNASSIGN_STR_POINTS);
				else
					updateServer(US_UNASSIGN_STR_POINT);
		}
		else if (isOnUnaDEXBtn(msg->x,msg->y) && ((int)charStats->baseDEX < D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0)))
		{
			log_msg("push up left button unassign dexterity\n");
			if (isDownBtn.UnaDEX)
				if (GetKeyState(VK_SHIFT)<0)
					updateServer(US_UNASSIGN_DEX_POINTS);
				else
					updateServer(US_UNASSIGN_DEX_POINT);
		}
		else if (isOnUnaVITBtn(msg->x,msg->y) && ((int)charStats->baseVIT < D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0)))
		{
			log_msg("push up left button unassign vitality\n");
			if (isDownBtn.UnaVIT)
				if (GetKeyState(VK_SHIFT)<0)
					updateServer(US_UNASSIGN_VIT_POINTS);
				else
					updateServer(US_UNASSIGN_VIT_POINT);
		}
		else if (isOnUnaENEBtn(msg->x,msg->y) && ((int)charStats->baseENE < D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0)))
		{
			log_msg("push up left button unassign energy\n");
			if (isDownBtn.UnaENE)
				if (GetKeyState(VK_SHIFT)<0)
					updateServer(US_UNASSIGN_ENE_POINTS);
				else
					updateServer(US_UNASSIGN_ENE_POINT);
		}
	}

	D2CleanStatMouseUp();
	freeMessage(msg);
	isDownBtn.all=0;
	return 0;
}


/*================================= END OF FILE =================================*/