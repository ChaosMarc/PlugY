/*================================================
  File created by Yohann NICOLAS.
  Add support 1.13d by L'Autour.
  Add support 1.14d by haxifix.

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

#define R8(Z,A,B,C,D,E,F,G,H,I) (offset_##Z + (version_##Z == V114d? 0x##I : (version_##Z == V113d? 0x##H : (version_##Z == V113c? 0x##G : (version_##Z == V112? 0x##F : (version_##Z == V111b? 0x##E : (version_##Z == V111? 0x##D : (version_##Z == V110? 0x##C : (version_##Z == V109d? 0x##B : 0x##A)))))))))
#define V8(Z,A,B,C,D,E,F,G,H,I) (version_##Z == V114d? 0x##I : (version_##Z == V113d? 0x##H : (version_##Z == V113c? 0x##G : (version_##Z == V112? 0x##F : (version_##Z == V111b? 0x##E : (version_##Z == V111? 0x##D : (version_##Z == V110? 0x##C : (version_##Z == V109d? 0x##B : 0x##A))))))))

#define RX(v) (WindowStartX+(v))
#define RY(v) (ResolutionY+NegWindowStartY-(v))

#define D2S(F, I, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;//static D N = (D)(A);
#define D2F(F, I, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;//static D N = (D)(A);
#define E2S(F, A, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;
#define E2F(F, A, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;
#define E2C(F, A, T, N)		extern T* pt##N;
#define F8(X, Z, A,B,C,D,E,F,G,H,I, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;

// Common
typedef CharStatsBIN*(FASTCALL *TD2GetCharStatsBIN) (DWORD charID); extern TD2GetCharStatsBIN D2GetCharStatsBIN;
typedef DWORD(FASTCALL *TD2CompileCubeInput) (CubeInput* cubeinput, char* s, DWORD p1, DWORD p2); extern TD2CompileCubeInput D2CompileCubeInput;
typedef DWORD(FASTCALL *TD2CompileCubeOutput) (CubeOutput* cubeoutput, char* s, DWORD p1, DWORD p2); extern TD2CompileCubeOutput D2CompileCubeOutput;
typedef ItemTypesBIN*(FASTCALL *TD2GetItemTypesBIN) (DWORD itemTypesId); extern TD2GetItemTypesBIN D2GetItemTypesBIN;
typedef ItemStatCostBIN*(FASTCALL *TD2GetItemStatCostBIN) (DWORD id); extern TD2GetItemStatCostBIN D2GetItemStatCostBIN;
typedef void*(FASTCALL *TD2ReadFile)(DWORD unused, char* filename, DWORD* size, const char*, DWORD); extern TD2ReadFile D2ReadFile;
typedef void(STDCALL *TD2LoadSuperuniques) (DWORD mempool); extern TD2LoadSuperuniques D2LoadSuperuniques;

// Client
typedef void*(FASTCALL *TD2LoadImage) (const char* filename, DWORD filetype); extern TD2LoadImage D2LoadImage;
typedef void(FASTCALL *TD2FreeImage) (void* image); extern TD2FreeImage D2FreeImage;
typedef void(FASTCALL *TD2SendMsgToAll) (BYTE* data); extern TD2SendMsgToAll D2SendMsgToAll;
typedef DWORD(STDCALL *TD2GetLastMonsterIDFight) (); extern TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
typedef void(STDCALL *TD2PrintStatsPage) (); extern TD2PrintStatsPage D2PrintStatsPage;
typedef DWORD(FASTCALL *TD2PrintStat) (Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText); extern TD2PrintStat D2PrintStat;
typedef LPWSTR(FASTCALL *TD2SetColorPopup) (LPWSTR popupText, DWORD color); extern TD2SetColorPopup D2SetColorPopup;
typedef DWORD(FASTCALL *TD2PlaySound) (DWORD id, DWORD, DWORD, DWORD, DWORD); extern TD2PlaySound D2PlaySound;
typedef Unit*(FASTCALL *TD2GetCurrentNPC) (); extern TD2GetCurrentNPC D2GetCurrentNPC;
typedef void(FASTCALL *TD2SendToServerXX) (DWORD size, BYTE * data); extern TD2SendToServerXX D2SendToServerXX;
typedef void(FASTCALL *TD2TogglePage) (DWORD a, DWORD b, DWORD c); extern TD2TogglePage D2TogglePage;
typedef void(FASTCALL *TD2ClickOnStashButton) (DWORD x, DWORD y); extern TD2ClickOnStashButton D2ClickOnStashButton;
typedef void*(STDCALL *TD2LoadBuySelBtn) (); extern TD2LoadBuySelBtn D2LoadBuySelBtn;
typedef void(FASTCALL *TD2ReloadGambleScreen) (); extern TD2ReloadGambleScreen D2ReloadGambleScreen;
// Old Client (Only Until 1.10)
typedef DWORD(FASTCALL *TD2isLODGame) (); extern TD2isLODGame D2isLODGame;
typedef BYTE(FASTCALL *TD2GetDifficultyLevel) (); extern TD2GetDifficultyLevel D2GetDifficultyLevel;
typedef DWORD(STDCALL *TD2GetMouseX) (); extern TD2GetMouseX D2GetMouseX;
typedef DWORD(STDCALL *TD2GetMouseY) (); extern TD2GetMouseY D2GetMouseY;
typedef Unit*(STDCALL *TD2GetClientPlayer) (); extern TD2GetClientPlayer D2GetClientPlayer;
typedef void(FASTCALL *TD2CleanStatMouseUp) (); extern TD2CleanStatMouseUp D2CleanStatMouseUp;
typedef void(FASTCALL *TD2SendToServer3) (BYTE type, WORD p); extern TD2SendToServer3 D2SendToServer3;
typedef NetClient*(FASTCALL *TD2GetClient) (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine); extern TD2GetClient D2GetClient;

// Game
typedef void(FASTCALL *TD2AddClient) (DWORD clientID); extern TD2AddClient D2AddClient;
typedef Game*(STDCALL *TD2GetGameByClientID) (DWORD clientID); extern TD2GetGameByClientID D2GetGameByClientID;
typedef void(FASTCALL *TD2BroadcastFunction)(Game* ptGame, void* fct, void* param); extern TD2BroadcastFunction D2BroadcastFunction;
typedef DWORD(FASTCALL *TD2SendPacket) (void* ptNetClient, LPVOID pData, DWORD size); extern TD2SendPacket D2SendPacket;
typedef void(FASTCALL *TD2SetSkillBaseLevelOnClient) (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove); extern TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
typedef DWORD(STDCALL *TD2LinkPortal) (Game* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID); extern TD2LinkPortal D2LinkPortal;
typedef DWORD(FASTCALL *TD2VerifIfNotCarry1) (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem); extern TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
typedef Room*(FASTCALL *TD2TestPositionInRoom) (Room* ptRoom, DWORD x, DWORD y); extern TD2TestPositionInRoom D2TestPositionInRoom;
typedef DWORD(FASTCALL *TD2SpawnMonster) (Game* ptGame, Room* ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2); extern TD2SpawnMonster D2SpawnMonster;
typedef void(STDCALL *TD2Game235C0) (Game* ptGame, Room* ptRoom); extern TD2Game235C0 D2Game235C0;
typedef DWORD(FASTCALL *TD2LoadInventory) (Game* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead); extern TD2LoadInventory D2LoadInventory;
typedef Unit*(FASTCALL *TD2GameGetObject) (Game* ptGame, DWORD type, DWORD itemNum); extern TD2GameGetObject D2GameGetObject;
typedef Unit*(FASTCALL *TD2CreateUnit) (DWORD type, DWORD id, DWORD x, DWORD y, Game* ptGame, Room* ptRoom, DWORD uk1, DWORD uk2, DWORD uk3); extern TD2CreateUnit D2CreateUnit;
typedef void(FASTCALL *TD2OpenPandPortal) (Game* ptGame, Unit* ptChar); extern TD2OpenPandPortal D2OpenPandPortal;
typedef void(FASTCALL *TD2OpenPandFinalPortal) (Game* ptGame, Unit* ptChar); extern TD2OpenPandFinalPortal D2OpenPandFinalPortal;
typedef void(FASTCALL *TD2MephIA) (Game* ptGame, Unit* ptMonster, DWORD*); extern TD2MephIA D2MephIA;
typedef void(FASTCALL *TD2DiabloIA) (Game* ptGame, Unit* ptMonster, DWORD*); extern TD2DiabloIA D2DiabloIA;
typedef void(FASTCALL *TD2BaalIA) (Game* ptGame, Unit* ptMonster, DWORD*); extern TD2BaalIA D2BaalIA;
typedef void(FASTCALL *TD2UberMephIA) (Game* ptGame, Unit* ptMonster, DWORD*); extern TD2UberMephIA D2UberMephIA;
typedef void(FASTCALL *TD2UberDiabloIA) (Game* ptGame, Unit* ptMonster, DWORD*); extern TD2UberDiabloIA D2UberDiabloIA;
typedef void(FASTCALL *TD2UberBaalIA) (Game* ptGame, Unit* ptMonster, DWORD*); extern TD2UberBaalIA D2UberBaalIA;
typedef void(STDCALL *TD2SaveGame) (Game* ptGame); extern TD2SaveGame D2SaveGame;

extern DWORD* ptResolutionY;
extern DWORD* ptResolutionX;
extern DWORD* ptNegWindowStartY;
extern DWORD* ptWindowStartX;
extern NetClient** ptClientTable;
extern DWORD*  ptIsLodGame;
extern BYTE*   ptDifficultyLevel;
extern DWORD*  ptMouseY;
extern DWORD*  ptMouseX;
extern Unit**  ptptClientChar;
extern DWORD*  ptNbStatDesc;
extern DWORD*  ptStatDescTable;

#include "../Commons/D2Funcs.h"
extern DataTables* SgptDataTables;

#undef F8
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

extern TD2AddPlayerStat				V2AddPlayerStat;
extern TD2GetGameByClientID			V2GetGameByClientID;
extern TD2SpawnMonster				V2SpawnMonster;
//extern TD2SetColorPopup			V2SetColorPopup;
extern WORD(*getDescStrPos)	(DWORD statID);
extern void* (STDCALL *compileTxtFile)(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
void setImage(sDrawImageInfo* data, void* image);
void setFrame(sDrawImageInfo* data, DWORD frame);
void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl) { D2FillArea(x, y, x + Width, y + Height, color, transTbl); };

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

void initD2functions();

/*================================= END OF FILE =================================*/