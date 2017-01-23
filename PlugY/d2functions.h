/*================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

    This file implements some common and useful
    function related to some Diablo II mechanisms.

================================================*/
#pragma once

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

//#ifdef MSVC
#define FASTCALL __fastcall 
//#else
//#define FASTCALL __msfastcall 
//#endif
#define STDCALL		__stdcall
#define FCT_ASM(N) __declspec(naked) void N() {__asm{
#define RANDOM(V) ((int)(rand()/(RAND_MAX+1.0)*(V)))
//#define RANDOM(V) (rand()%(V))

//#define PY(C) (*(PYPlayerData**)((BYTE*)(ptChar)+shifting.ptPYPlayerData))
#define PCPlayerData (*(PlayerData**)((DWORD)(ptChar)+shifting.ptSpecificData)) //->ptPlayerData
#define PCGame (*(Game**)((DWORD)(ptChar)+shifting.ptGame)) //->ptGame
#define PClientGame (*(Game**)((DWORD)(ptClient)+shifting.ptClientGame)) //ptClient->ptGame
#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
//#define PIItemData (*(ItemData**)((DWORD)(ptItem)+shifting.ptSpecificData)) //->ptItemData
//#define PCPY (*(PYPlayerData**)((DWORD)(ptChar)+shifting.ptPYPlayerData)) //->ptPYPlayerData
#define PCPY ((PYPlayerData*)((DWORD)PCPlayerData+shifting.ptPYPlayerData)) //->ptPYPlayerData
#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills

#define R7(Z,A,B,C,D,E,F,G,H) (offset_##Z + (version_##Z == V113d? 0x##H : (version_##Z == V113c? 0x##G : (version_##Z == V112? 0x##F : (version_##Z == V111b? 0x##E : (version_##Z == V111? 0x##D : (version_##Z == V110? 0x##C : (version_##Z == V109d? 0x##B : 0x##A))))))))
#define V7(Z,A,B,C,D,E,F,G,H) (version_##Z == V113d? 0x##H : (version_##Z == V113c? 0x##G : (version_##Z == V112? 0x##F : (version_##Z == V111b? 0x##E : (version_##Z == V111? 0x##D : (version_##Z == V110? 0x##C : (version_##Z == V109d? 0x##B : 0x##A)))))))

#define RX(v) (WindowStartX+(v))
#define RY(v) (ResolutionY+NegWindowStartY-(v))



#define D2S(F, I, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;//static D N = (D)(A);
#define D2F(F, I, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;//static D N = (D)(A);
#define E2S(F, A, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;
#define E2F(F, A, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;
#define E2C(F, A, T, N)		extern T* pt##N;
#define F7(X, Z, A,B,C,D,E,F,G,H, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define A7(X, Z, A,B,C,D,E,F,G,H, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define C7(Z, A,B,C,D,E,F,G,H, T, N)       extern T* pt##N;

#include "../Commons/D2Funcs.h"
extern DataTables* SgptDataTables;
//ONLY UNTIL 1.10 :
//E2F(D2Client,0,	DWORD,		D2isLODGame, ());
//E2F(D2Client,0,	BYTE,		D2GetDifficultyLevel, ());
//E2S(D2Client,0,	DWORD,		D2GetMouseX, ());
//E2S(D2Client,0,	DWORD,		D2GetMouseY, ());
//E2S(D2Client,0,	Unit*,		D2GetClientPlayer, ());
//E2F(D2Client,0,	void,		D2SendToServer3, (BYTE type, WORD p));
////E2F(D2Client,0,	void,		D2SendToServer7, (BYTE type, WORD p1, WORD p2, WORD p3));
////E2F(D2Client,0,	void,		D2SendToServer5, (BYTE type, DWORD p));
////E2F(D2Client,0,	void,		D2SendToServer9, (BYTE type, DWORD p1, DWORD p2));
////E2F(D2Client,0,	void,		D2SendToServer13,(BYTE type, DWORD p1, DWORD p2, DWORD p3));
//E2F(D2Game,0,	NetClient*,	D2GetClient, (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine));
//E2F(D2Client,0,	void,		D2CleanStatMouseUp, ());


#undef F7
#undef A7
#undef C7
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

extern TD2AddPlayerStat				V2AddPlayerStat;
extern TD2GetGameByClientID			V2GetGameByClientID;
extern TD2SpawnMonster				V2SpawnMonster;
//extern TD2SetColorPopup			V2SetColorPopup;
extern WORD (*getDescStrPos)	(DWORD statID);
extern void* (STDCALL *compileTxtFile)(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
void setImage(sDrawImageInfo* data, void* image);
void setFrame(sDrawImageInfo* data, DWORD frame);
void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl){D2FillArea(x,y,x+Width,y+Height,color,transTbl);};

//#define SgptDataTables (*ptSgptDataTables)
#define ResolutionY (*ptResolutionY)
#define ResolutionX (*ptResolutionX)
#define NegWindowStartY (*ptNegWindowStartY)
#define WindowStartX (*ptWindowStartX)
#define GameTypeMode (*ptGameTypeMode)
#define ClientTable (*ptClientTable)

#define IsLodGame (*ptIsLodGame)
#define DifficultyLevel (*ptDifficultyLevel)
#define MouseY (*ptMouseY)
#define MouseX (*ptMouseX)
#define ptClientChar (*ptptClientChar)
//#define CurrentNPCNum (*ptCurrentNPCNum)

bool initD2functions();

/*================================= END OF FILE =================================*/