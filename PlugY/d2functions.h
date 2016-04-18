/*================================================
	File created by Yohann NICOLAS.

    This file implements some common and useful
    function related to some Diablo II mechanisms.

================================================*/

#pragma once

#include "common.h"

#define D2S(F, I, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;//static D N = (D)(A);
#define D2F(F, I, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;//static D N = (D)(A);
#define E2S(F, A, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;
#define E2F(F, A, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;
#define E2C(F, A, T, N)		extern T* pt##N;
#define F7(X, Z, A,B,C,D,E,F,G, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define A7(X, Z, A,B,C,D,E,F,G, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define C7(Z, A,B,C,D,E,F,G, T, N)       extern T* pt##N;

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