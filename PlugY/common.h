/*==============================================
	File created by Yohann NICOLAS.

  this file implements some common and useful
  function related to some Diablo II mechanisms.

/*============================================*/

#pragma once

#include <windows.h>
#include "../Commons/d2Constants.h"
#include "../Commons/d2BinFile.h"
#include "../Commons/d2Struct.h"
#include "../Commons/d2StringTblStruct.h"
#include "../Commons/D2UnitStruct.h"
#include "../Commons/updatingConst.h"

#include "customData.h"
#include "modifMemory.h"
#include "parameters.h"
#include "globalVariable.h"

//#ifdef MSVC 
#define FASTCALL __fastcall 
//#else 
//#define FASTCALL __msfastcall 
//#endif 
#define STDCALL		__stdcall
#define FCT_ASM(N) __declspec(naked) void N() {__asm{
#define RANDOM(V) ((int)(rand()/(RAND_MAX+1.0)*(V)))
//#define RANDOM(V) (rand()%(V))

// Convertion to 1.09
struct s_shifting {
	DWORD ptInventory;
	DWORD ptSpecificData;
	DWORD ptPYPlayerData;
	DWORD ptGame;
	DWORD ptClientGame;
	DWORD ptSkills;
	DWORD ptImage;
	DWORD ptFrame;
};
extern s_shifting shifting;

//#define PY(C) (*(PYPlayerData**)((BYTE*)(ptChar)+shifting.ptPYPlayerData))
#define PCPlayerData (*(PlayerData**)((DWORD)(ptChar)+shifting.ptSpecificData)) //->ptPlayerData
#define PCGame (*(Game**)((DWORD)(ptChar)+shifting.ptGame)) //->ptGame
#define PClientGame (*(Game**)((DWORD)(ptClient)+shifting.ptClientGame)) //ptClient->ptGame
#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
//#define PIItemData (*(ItemData**)((DWORD)(ptItem)+shifting.ptSpecificData)) //->ptItemData
//#define PCPY (*(PYPlayerData**)((DWORD)(ptChar)+shifting.ptPYPlayerData)) //->ptPYPlayerData
#define PCPY ((PYPlayerData*)((DWORD)PCPlayerData+shifting.ptPYPlayerData)) //->ptPYPlayerData
#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills

#define R7(Z,A,B,C,D,E,F,G) (offset_##Z + (version_##Z == V113? 0x##G : (version_##Z == V112? 0x##F : (version_##Z == V111b? 0x##E : (version_##Z == V111? 0x##D : (version_##Z == V110? 0x##C : (version_##Z == V109d? 0x##B : 0x##A)))))))
#define V7(Z,A,B,C,D,E,F,G) (version_##Z == V113? 0x##G : (version_##Z == V112? 0x##F : (version_##Z == V111b? 0x##E : (version_##Z == V111? 0x##D : (version_##Z == V110? 0x##C : (version_##Z == V109d? 0x##B : 0x##A))))))


// Convert 4 char code in a DWORD code
#define BIN(A,B,C,D) ((DWORD)A) + (((DWORD)B) << 8) + (((DWORD)C) << 16) + (((DWORD)D) << 24)


#define RX(v) (WindowStartX+(v))
#define RY(v) (ResolutionY+NegWindowStartY-(v))


enum eFileVersion
{
	V109b=0,
	V109d,
	V110,
	V111,
	V111b,
	V112,
	V113
};

extern int version_SmackW32;
extern int version_D2Common;
extern int version_ijl11;
extern int version_D2Gdi;
extern int version_D2Win;
extern int version_D2sound;
extern int version_D2MCPCLI;
extern int version_D2Launch;
extern int version_D2gfx;
extern int version_D2Client;
extern int version_D2Net;
extern int version_D2Lang;
extern int version_D2Game;
extern int version_D2CMP;
extern int version_Bnclient;
extern int version_Fog;
extern int version_Storm;


// Address in memory of external DLL
extern DWORD offset_SmackW32;
extern DWORD offset_D2Common;
extern DWORD offset_ijl11;
extern DWORD offset_D2Gdi;
extern DWORD offset_D2Win;
extern DWORD offset_D2sound;
extern DWORD offset_D2MCPCLI;
extern DWORD offset_D2Launch;
extern DWORD offset_D2gfx;
extern DWORD offset_D2Client;
extern DWORD offset_D2Net;
extern DWORD offset_D2Lang;
extern DWORD offset_D2Game;
extern DWORD offset_D2CMP;
extern DWORD offset_Bnclient;
extern DWORD offset_Fog;
extern DWORD offset_Storm;

extern const char* S_CloneBattles;
extern const char* S_DarkAlliance;

LPWSTR getTranslatedString(int stringID);
enum eStringList
{
	STR_STATS_UNASSIGN_WITH_LIMIT=0,
	STR_STATS_UNASSIGN_WITHOUT_LIMIT,
	STR_STATS_BASE_MIN,
	STR_SKILLS_UNASSIGN,
	STR_STASH_PREVIOUS_PAGE,
	STR_STASH_NEXT_PAGE,
	STR_TOGGLE_TO_PERSONAL,
	STR_TOGGLE_TO_SHARED,
	STR_STASH_PREVIOUS_INDEX,
	STR_STASH_NEXT_INDEX,
	STR_PERSONAL_PAGE_NUMBER,
	STR_SHARED_PAGE_NUMBER,
	STR_NO_SELECTED_PAGE,
	STR_PUT_GOLD,
	STR_TAKE_GOLD,
	STR_SHARED_GOLD_QUANTITY,
	STR_PREVIOUS_PAGE,
	STR_NEXT_PAGE
};

bool isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h);
void freeMessage(sWinMessage* msg);
LPWSTR getTypeUString (WORD id, LPWSTR lpText, DWORD size);
char* getTypeAString (WORD id, char* lpText, DWORD size);

/*================================= END OF FILE =================================*/