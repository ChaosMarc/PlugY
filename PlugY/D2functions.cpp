/*================================================
  File created by Yohann NICOLAS.
  Add support 1.13d by L'Autour.
  Add support 1.14d by haxifix.

  This file implements some common and useful
  function related to some Diablo II mechanisms.

================================================*/

#include "common.h"

s_shifting shifting;

#define D2S(F, I, R, N, P)	T##N N;
#define D2F(F, I, R, N, P)	T##N N;
#define E2S(F, A, R, N, P)	T##N N;
#define E2F(F, A, R, N, P)	T##N N;
#define E2C(F, A, T, N)		T* pt##N;
#define F8(X, Z, A,B,C,D,E,F,G,H,I, R, N, P) T##N N;

// Common
TD2GetCharStatsBIN D2GetCharStatsBIN;
TD2CompileCubeInput D2CompileCubeInput;
TD2CompileCubeOutput D2CompileCubeOutput;
TD2GetItemTypesBIN D2GetItemTypesBIN;
TD2GetItemStatCostBIN D2GetItemStatCostBIN;
TD2ReadFile D2ReadFile;
TD2LoadSuperuniques D2LoadSuperuniques;

// Client
TD2LoadImage D2LoadImage;
TD2FreeImage D2FreeImage;
TD2SendMsgToAll D2SendMsgToAll;
TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
TD2PrintStatsPage D2PrintStatsPage;
TD2PrintStat D2PrintStat;
TD2SetColorPopup D2SetColorPopup;
TD2PlaySound D2PlaySound;
TD2GetCurrentNPC D2GetCurrentNPC;
TD2SendToServerXX D2SendToServerXX;
TD2TogglePage D2TogglePage;
TD2ClickOnStashButton D2ClickOnStashButton;
TD2LoadBuySelBtn D2LoadBuySelBtn;
TD2ReloadGambleScreen D2ReloadGambleScreen;
// Old Client (Only Until 1.10)
TD2isLODGame D2isLODGame;
TD2GetDifficultyLevel D2GetDifficultyLevel;
TD2GetMouseX D2GetMouseX;
TD2GetMouseY D2GetMouseY;
TD2GetClientPlayer D2GetClientPlayer;
TD2CleanStatMouseUp D2CleanStatMouseUp;
TD2SendToServer3 D2SendToServer3;
TD2GetClient D2GetClient;

// Game
TD2AddClient D2AddClient;
TD2GetGameByClientID D2GetGameByClientID;
TD2BroadcastFunction D2BroadcastFunction;
TD2SendPacket D2SendPacket;
TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
TD2LinkPortal D2LinkPortal;
TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
TD2TestPositionInRoom D2TestPositionInRoom;
TD2SpawnMonster D2SpawnMonster;
TD2Game235C0 D2Game235C0;
TD2LoadInventory D2LoadInventory;
TD2GameGetObject D2GameGetObject;
TD2CreateUnit D2CreateUnit;
TD2OpenPandPortal D2OpenPandPortal;
TD2OpenPandFinalPortal D2OpenPandFinalPortal;
TD2MephIA D2MephIA;
TD2DiabloIA D2DiabloIA;
TD2BaalIA D2BaalIA;
TD2UberMephIA D2UberMephIA;
TD2UberDiabloIA D2UberDiabloIA;
TD2UberBaalIA D2UberBaalIA;
TD2SaveGame D2SaveGame;

DWORD* ptResolutionY;
DWORD* ptResolutionX;
DWORD* ptNegWindowStartY;
DWORD* ptWindowStartX;
NetClient** ptClientTable;
DWORD*  ptIsLodGame;
BYTE*   ptDifficultyLevel;
DWORD*  ptMouseY;
DWORD*  ptMouseX;
Unit**  ptptClientChar;
DWORD* ptStatDescTable;
DWORD* ptNbStatDesc;

#include "../Commons/D2Funcs.h"
DataTables* SgptDataTables;
//E2F(D2Client,0,	DWORD,		D2isLODGame, ());//6FAAC080
//E2F(D2Client,0,	BYTE,		D2GetDifficultyLevel, ());//6FAAC090
//E2S(D2Client,0,	DWORD,		D2GetMouseX, ());//6FB57BC0
//E2S(D2Client,0,	DWORD,		D2GetMouseY, ());//6FB57BD0
//E2S(D2Client,0,	Unit*,		D2GetClientPlayer, ());//6FB283D0
//E2F(D2Client,0,	void,		D2SendToServer3, (BYTE type, WORD p));//6FAAD990
////E2F(D2Client,0,	void,		D2SendToServer7, (BYTE type, WORD p1, WORD p2, WORD p3));//6FAAD9E0
////E2F(D2Client,0,	void,		D2SendToServer5, (BYTE type, DWORD p));//6FAADA20
////E2F(D2Client,0,	void,		D2SendToServer9, (BYTE type, DWORD p1, DWORD p2));//6FAADA40
////E2F(D2Client,0,	void,		D2SendToServer13,(BYTE type, DWORD p1, DWORD p2, DWORD p3));//6FAADA70
//E2F(D2Game,0,	NetClient*,	D2GetClient, (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine));//6FCBC2E0
//E2F(D2Client,0,	void,		D2CleanStatMouseUp, ());//6FAABF60
#undef F8
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

#define D2S(F, I, R, N, P)	typedef R (STDCALL  *T##N) P; T##N N;
D2S(D2Common, 10581, CharStatsBIN*, D2Common10581, (DWORD charID));//ONLY in 1.09
D2S(D2Common, 10598, ItemStatCostBIN*, D2Common10598, (DWORD itemStatCostID));//ONLY in 1.09
D2S(D2Common, 10673, ItemTypesBIN*, D2Common10673, (DWORD itemTypesID));//ONLY in 1.09
#undef D2S

//TD2SetPlayerStat			 V2SetPlayerStat;
TD2AddPlayerStat			 V2AddPlayerStat;
TD2GetPlayerStat			 V2GetPlayerStat;
//TD2GetPlayerStat20			 V2GetPlayerStat20;
TD2GetPlayerBaseStat		 V2GetPlayerBaseStat;
TD2SetSkillBaseLevel		 V2SetSkillBaseLevel;
TD2SetSkillBaseLevelOnClient V2SetSkillBaseLevelOnClient;
TD2PrintStat				 V2PrintStat;
TD2CompileCubeInput			 V2CompileCubeInput;
TD2CompileCubeOutput		 V2CompileCubeOutput;
TD2BroadcastFunction		 V2BroadcastFunction;
TD2GetGameByClientID		 V2GetGameByClientID;
TD2SpawnMonster				 V2SpawnMonster;
TD2VerifIfNotCarry1			 V2VerifIfNotCarry1;
TD2GameGetObject			 V2GameGetObject;
TD2TestPositionInRoom		 V2TestPositionInRoom;
TD2GetItemTypesBIN			 V2GetItemTypesBIN;
TD2CompileTxtFile			 compileTxtFile;
WORD(*getDescStrPos) (DWORD statID);
//void (*setImage) (sDrawImageInfo* data, void* image);
//void (*setFrame) (sDrawImageInfo* data, DWORD frame);
TD2SendMsgToAll				 V2SendMsgToAll;
TD2SetColorPopup			 V2SetColorPopup;
TD2LoadImage				 V2LoadImage;
TD2PlaySound				 V2PlaySound;
TD2SendToServer				 V2SendToServer;
TD2GetCharStatsBIN			 V2GetCharStatsBIN;
TD2GetItemStatCostBIN		 V2GetItemStatCostBIN;
TD2SendPacket				 V2SendPacket;
TD2LoadInventory			 V2LoadInventory;
TD2SaveGame					 V2SaveGame;
TD2LinkPortal					 V2LinkPortal;
TD2Game235C0					 V2Game235C0;

//DWORD* ptNbStatDesc
//DWORD* ptStatDescTable;
//TD2OpenNPCMenu				 V2OpenNPCMenu;

DWORD getStatDescIDFrom(DWORD statID)//FOR 1.09
  {
  DWORD* desc = ptStatDescTable;
  DWORD curDesc = 0;
  while (curDesc < *ptNbStatDesc)
    {
    if (*desc == statID)
      return curDesc;
    desc += 4;
    curDesc++;
    }
  return curDesc;
  }

//FCT_ASM ( D2SetPlayerStat_9 )//(Unit* ptChar, DWORD statID, DWORD amount, DWORD index)
//	PUSH DWORD PTR SS:[ESP+0xC]
//	PUSH DWORD PTR SS:[ESP+0xC]
//	PUSH DWORD PTR SS:[ESP+0xC]
//	CALL V2SetPlayerStat
//	RETN 0x10
//}}

FCT_ASM(D2AddPlayerStat_9)//(Unit* ptChar, DWORD statID, DWORD amount, DWORD index)
PUSH DWORD PTR SS : [ESP + 0xC]
PUSH DWORD PTR SS : [ESP + 0xC]
PUSH DWORD PTR SS : [ESP + 0xC]
CALL V2AddPlayerStat
RETN 0x10
}}

FCT_ASM(D2GetPlayerStat_9)//(Unit* ptChar, DWORD statID, DWORD index)
PUSH DWORD PTR SS : [ESP + 0x8]
PUSH DWORD PTR SS : [ESP + 0x8]
CALL V2GetPlayerStat
RETN 0x0C
}}

//FCT_ASM ( D2GetPlayerStat20_9 )//(Unit* ptChar, DWORD statID, DWORD index)
//	PUSH DWORD PTR SS:[ESP+0x8]
//	PUSH DWORD PTR SS:[ESP+0x8]
//	CALL V2GetPlayerStat20
//	RETN 0x0C
//}}

FCT_ASM(D2GetPlayerBaseStat_9)//(Unit* ptChar, DWORD statID, DWORD index)
PUSH DWORD PTR SS : [ESP + 0x8]
PUSH DWORD PTR SS : [ESP + 0x8]
CALL V2GetPlayerBaseStat
RETN 0x0C
}}

FCT_ASM(D2SetSkillBaseLevel_9)//(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
CALL V2SetSkillBaseLevel
RETN 0x18
}}

FCT_ASM(D2SetSkillBaseLevelOnClient_9)//(void* ptClient, Unit* ptChar, DWORD skillID, DWORD newValue, DWORD zero)
POP EAX
MOV ECX, EDX
POP EDX
PUSH EAX
JMP V2SetSkillBaseLevelOnClient
}}

FCT_ASM(D2GetCharStatsBIN_9)
PUSH ECX
CALL D2Common10581
RETN
}}

FCT_ASM(D2GetItemStatCostBIN_9)
PUSH ECX
CALL D2Common10598
RETN
}}

FCT_ASM(D2GetItemTypesBIN_9)
PUSH ECX
CALL D2Common10673
RETN
}}


DWORD FASTCALL D2PrintStat_9(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText)
  {
  DWORD curDesc = getStatDescIDFrom(statID);
  if (curDesc < *ptNbStatDesc)
    return V2PrintStat(ptItem, (Stats*)curDesc, statValue, 0, 0, lpText);
  return 0;
  }


void setImage(sDrawImageInfo* data, void* image) { ((void**)data)[shifting.ptImage / 4] = image; }//0x4 0x8 0x3C
void setFrame(sDrawImageInfo* data, DWORD frame) { ((DWORD*)data)[shifting.ptFrame / 4] = frame; }//0x8 0x44 0x40

//void setImage_111(sDrawImageInfo* data, void* image){data->image=image;}//0x8 0x44
//void setImage_1XX(sDrawImageInfo* data, void* image){((void**)data)[1]=image;}//0x4 0x8
//void setFrame_111(sDrawImageInfo* data, DWORD frame){data->frame=frame;}
//void setFrame_1XX(sDrawImageInfo* data, DWORD frame){((DWORD*)data)[2]=frame;}


WORD getDescStrPos_9(DWORD statID)
  {
  DWORD* desc = &ptStatDescTable[getStatDescIDFrom(statID) * 4];
  return (WORD)*(desc + 2);
  }
WORD getDescStrPos_10(DWORD statID)
  {
  ItemStatCostBIN* itemStatCost = D2GetItemStatCostBIN(statID);
  return itemStatCost->descstrpos;
  }


const char* S_compileTxtFile = "compileTxtFile";
const char* S_errorReadTxtFile = "pbData";
__declspec(naked) void* STDCALL compileTxtFile_9(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
  {
  _asm {
    SUB ESP, 0x210
    //	MOV EAX,DWORD PTR DS:[1BEA28C]
    PUSH EBX
    PUSH EBP
    PUSH ESI
    PUSH EDI
    MOV ESI, DWORD PTR SS : [ESP + 0x228]
    MOV DWORD PTR SS : [ESP + 0x10], 0

    MOV EDI, wsprintf
    PUSH ESI
    LEA EAX, DWORD PTR SS : [ESP + 0x20]
    PUSH EAX
    CALL EDI
    ADD ESP, 8

    LEA EDX, DWORD PTR SS : [ESP + 0x10]
    PUSH 0
    PUSH S_compileTxtFile
    PUSH EDX
    MOV ECX, DWORD PTR SS : [ESP + 0x230]
    LEA EDX, DWORD PTR SS : [ESP + 0x28]
    CALL D2ReadFile
    TEST EAX, EAX
    JNZ continue_compileTxtFile
    PUSH 0
    PUSH S_compileTxtFile
    PUSH S_errorReadTxtFile
    CALL D2FogAssertOld
    PUSH - 1
    CALL exit
    continue_compileTxtFile :
    MOV ECX, D2CompileTxtFile
      ADD ECX, 0x305
      JMP ECX
    }
  }

__declspec(naked) void* STDCALL compileTxtFile_10(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
  {
  _asm {
    SUB ESP, 0x210
    //	MOV EAX,DWORD PTR DS:[1BEA28C]
    PUSH EBX
    PUSH EBP
    MOV EBP, DWORD PTR SS : [ESP + 0x220]
    PUSH ESI
    PUSH EDI
    MOV DWORD PTR SS : [ESP + 0x10], 0

    MOV EBX, wsprintf
    PUSH EBP
    LEA EAX, DWORD PTR SS : [ESP + 0x20]
    PUSH EAX
    CALL EBX
    ADD ESP, 8

    LEA EDX, DWORD PTR SS : [ESP + 0x10]
    PUSH 0
    PUSH S_compileTxtFile
    PUSH EDX
    MOV ECX, DWORD PTR SS : [ESP + 0x230]
    LEA EDX, DWORD PTR SS : [ESP + 0x28]
    CALL D2ReadFile
    TEST EAX, EAX
    JNZ continue_compileTxtFile
    PUSH 0
    PUSH S_compileTxtFile
    PUSH S_errorReadTxtFile
    CALL D2FogAssertOld
    PUSH - 1
    CALL exit
    continue_compileTxtFile :
    MOV ECX, D2CompileTxtFile
      ADD ECX, 0x2ED
      JMP ECX
    }
  }

__declspec(naked) void* STDCALL compileTxtFile_114(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength) {
  _asm {
    SUB ESP, 0x20C
    //	MOV EAX,DWORD PTR DS:[6FDF1464]
    PUSH EBX
    PUSH EBP
    PUSH ESI
    PUSH EDI
    MOV DWORD PTR SS : [ESP + 0x10], 0
    MOV EBX, DWORD PTR SS : [ESP + 0x224]

    PUSH EBX
    LEA EAX, DWORD PTR SS : [ESP + 0x1A]
    PUSH EAX
    CALL DWORD PTR SS : [wsprintf]
    MOV EDX, DWORD PTR SS : [ESP + 0x228]
    ADD ESP, 8
    LEA EDX, DWORD PTR SS : [ESP + 0xE]
    PUSH EDX
    PUSH EAX
    LEA EDX, DWORD PTR SS : [ESP + 0x20]
    CALL D2ReadFile
    TEST EAX, EAX
    JNZ continue_compileTxtFile
    PUSH __LINE__
    CALL D2GetInstructionPointer
    PUSH EAX
    PUSH S_errorReadTxtFile
    CALL D2FogAssert
    ADD ESP, 0xC
    PUSH - 1
    CALL exit
    continue_compileTxtFile :
    MOV ECX, D2CompileTxtFile
      ADD ECX, 0x1EC
      JMP ECX
    }
  }

__declspec(naked) void* STDCALL compileTxtFile_111(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
  {
  _asm {
    SUB ESP, 0x20C
    //	MOV EAX,DWORD PTR DS:[6FDF1464]
    PUSH EBX
    PUSH EBP
    PUSH ESI
    PUSH EDI
    MOV DWORD PTR SS : [ESP + 0x10], 0
    MOV EBX, DWORD PTR SS : [ESP + 0x224]

    PUSH EBX
    LEA EAX, DWORD PTR SS : [ESP + 0x1C]
    PUSH EAX
    CALL DWORD PTR SS : [wsprintf]
    MOV EDX, DWORD PTR SS : [ESP + 0x228]
    ADD ESP, 8
    LEA EDX, DWORD PTR SS : [ESP + 0x10]
    PUSH EDX
    PUSH EAX
    LEA EAX, DWORD PTR SS : [ESP + 0x20]
    CALL D2ReadFile
    TEST EAX, EAX
    JNZ continue_compileTxtFile
    PUSH __LINE__
    CALL D2GetInstructionPointer
    PUSH EAX
    PUSH S_errorReadTxtFile
    CALL D2FogAssert
    ADD ESP, 0xC
    PUSH - 1
    CALL exit
    continue_compileTxtFile :
    MOV ECX, D2CompileTxtFile
      ADD ECX, 0x1EC
      JMP ECX
    }
  }


DWORD FASTCALL	D2isLODGame_111() { return IsLodGame; }
BYTE  FASTCALL	D2GetDifficultyLevel_111() { return DifficultyLevel; }
DWORD STDCALL	D2GetMouseX_111() { return MouseX; }
DWORD STDCALL	D2GetMouseY_111() { return MouseY; }
Unit* STDCALL	D2GetClientPlayer_111() { return ptClientChar; }

DWORD *StatMouse1, *StatMouse2, *StatMouse3, *StatMouse4;
void FASTCALL D2CleanStatMouseUp_111() { *StatMouse1 = *StatMouse2 = *StatMouse3 = *StatMouse4 = 0; }

FCT_ASM(D2CleanStatMouseUp_114)
MOV DWORD PTR DS : [StatMouse1], 0
MOV DWORD PTR DS : [StatMouse2], 0
MOV DWORD PTR DS : [StatMouse3], 0
MOV DWORD PTR DS : [StatMouse4], 0
RETN
}}

Unit* STDCALL	D2GetRealItem_111(Unit* ptItem) { return ptItem; }
/* 1.11 : sizememory : 0x104 (LoadBuySell)
6FADA7F0  |. A1 48BDBC6F    MOV EAX,DWORD PTR DS:[6FBCBD48]
6FADA7F5  |. 3BC3           CMP EAX,EBX
6FADA7F7  |. 75 27          JNZ SHORT D2Client.6FADA820
6FADA7F9  |. 68 C407B86F    PUSH D2Client.6FB807C4                   ; /<%s> = "DATA\GLOBAL"
6FADA7FE  |. 8D4424 6C      LEA EAX,DWORD PTR SS:[ESP+6C]            ; |
6FADA802  |. 68 483BB86F    PUSH D2Client.6FB83B48                   ; |Format = "%s\ui\panel\buysellbtn"
6FADA807  |. 50             PUSH EAX                                 ; |s
6FADA808  |. FF15 FCF0B76F  CALL DWORD PTR DS:[<&USER32.wsprintfA>]  ; \wsprintfA
6FADA80E  |. 83C4 0C        ADD ESP,0C
6FADA811  |. 53             PUSH EBX                                 ; /Arg1
6FADA812  |. 8D4424 6C      LEA EAX,DWORD PTR SS:[ESP+6C]            ; |
6FADA816  |. E8 E5B40400    CALL D2Client.6FB25D00                   ; \D2Client.6FB25D00
6FADA81B  |. A3 48BDBC6F    MOV DWORD PTR DS:[6FBCBD48],EAX
*/


FCT_ASM(D2SendMsgToAll_111)
PUSH ESI
MOV ESI, ECX
CALL V2SendMsgToAll
POP ESI
RETN
}}

FCT_ASM(D2SetColorPopup_111)
PUSH EDI
PUSH EDX
MOV EDI, ECX
CALL V2SetColorPopup
POP EDI
RETN
}}

FCT_ASM(D2LoadImage_111)
PUSH EDX
MOV EAX, ECX
CALL V2LoadImage
RETN
}}

FCT_ASM(D2LoadImage_114)
PUSH EDX
MOV EAX, ECX
CALL V2LoadImage
POP EDX
RETN
}}

const char* D2FreeImage_FILE = __FILE__;
FCT_ASM(D2FreeImage_111)
PUSH ESI
MOV ESI, ECX
PUSH ESI
CALL D2CMP10014
TEST ESI, ESI
JE END_D2Free
PUSH 0
PUSH __LINE__
MOV EDX, D2FreeImage_FILE;  ASCII "C:\projects\D2\head\Diablo2\Source\D2Client\CORE\ARCHIVE.CPP"
MOV ECX, ESI
CALL D2FogMemDeAlloc
END_D2Free :
POP ESI
RETN
}}


FCT_ASM(D2PlaySound_111)
PUSH EBX
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH EDX
MOV EBX, ECX
CALL V2PlaySound
POP EBX
RETN 0xC
}}

FCT_ASM(D2GetClient_111)
PUSH ECX
CALL D2GetPlayerData
MOV EAX, DWORD PTR DS : [EAX + 0x9C]
RETN 4
}}

FCT_ASM(D2SetSkillBaseLevelOnClient_114)
PUSH EBX
PUSH EDX
PUSH ESI
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH DWORD PTR SS : [ESP + 0x14]
MOV EBX, DWORD PTR SS : [ESP + 0x14]
MOV EAX, ECX
MOV ESI, EDX
CALL V2SetSkillBaseLevelOnClient
POP ESI
POP EBX
RETN 0xC
}}

FCT_ASM(D2SetSkillBaseLevelOnClient_111)
PUSH EBX
PUSH ESI
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH DWORD PTR SS : [ESP + 0x14]
MOV EBX, DWORD PTR SS : [ESP + 0x14]
MOV EAX, ECX
MOV ESI, EDX
CALL V2SetSkillBaseLevelOnClient
POP ESI
POP EBX
RETN 0xC
}}

FCT_ASM(D2GetCharStatsBIN_111)
MOV EAX, ECX
JMP V2GetCharStatsBIN
}}

FCT_ASM(D2GetItemStatCostBIN_111)
MOV EAX, ECX
JMP V2GetItemStatCostBIN
}}

FCT_ASM(D2SendToServer3_114)
PUSH EDI
PUSH ESI
PUSH EBX
PUSH ECX
MOV BYTE PTR SS : [ESP], CL
MOV WORD PTR SS : [ESP + 1], DX
MOV EDI, 3
LEA ECX, DWORD PTR SS : [ESP]
PUSH ECX
CALL D2SendToServerXX
POP ECX
POP EBX
POP ESI
POP EDI
RETN
}}

FCT_ASM(D2SendToServer3_111)
PUSH EBX
PUSH ECX
MOV BYTE PTR SS : [ESP], CL
MOV WORD PTR SS : [ESP + 1], DX
MOV EBX, 3
LEA EDX, DWORD PTR SS : [ESP]
PUSH EDX
CALL D2SendToServerXX
POP ECX
POP EBX
RETN
}}

FCT_ASM(D2PrintStat_114)
PUSH ESI
PUSH EBX
PUSH ECX
MOV ESI, DWORD PTR SS : [ESP + 0x1C]
PUSH DWORD PTR SS : [ESP + 0x18]
PUSH DWORD PTR SS : [ESP + 0x18]
PUSH DWORD PTR SS : [ESP + 0x18]
PUSH EDX
PUSH ECX
CALL V2PrintStat
POP ECX
POP EBX
POP ESI
RETN 0x10
}}

FCT_ASM(D2PrintStat_111)
PUSH ESI
MOV ESI, DWORD PTR SS : [ESP + 0x14]
MOV EAX, DWORD PTR SS : [ESP + 0x08]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH EDX
PUSH ECX
CALL V2PrintStat
POP ESI
RETN 0x10
}}

FCT_ASM(D2SendPacket_114)
PUSH EDI
PUSH DWORD PTR SS : [ESP + 8]
PUSH EDX
MOV EDI, ECX
CALL V2SendPacket
POP EDI
RETN 0x4
}}

FCT_ASM(D2SendPacket_111)
POP EAX
PUSH EDX
PUSH EAX
MOV EAX, ECX
JMP V2SendPacket
}}

FCT_ASM(D2LoadInventory_111)
MOV EAX, DWORD PTR SS : [ESP + 4]
MOV DWORD PTR SS : [ESP + 4], EDX
JMP V2LoadInventory
}}

FCT_ASM(D2CompileCubeInput_111)
PUSH EBX
MOV EBX, ECX
MOV EAX, EDX
CALL V2CompileCubeInput
POP EBX
RETN 8
}}

FCT_ASM(D2CompileCubeInput_114)
PUSH ECX
MOV EAX, EDX
CALL V2CompileCubeInput
RETN 8
}}

FCT_ASM(D2CompileCubeOutput_111)
PUSH EBX
MOV EBX, ECX
PUSH EDX
CALL V2CompileCubeOutput
POP EBX
RETN 8
}}

FCT_ASM(D2BroadcastFunction_111)
PUSH EDI
PUSH EBX
MOV EAX, ECX
MOV EDI, EDX
MOV EBX, DWORD PTR SS : [ESP + 0xC]
CALL V2BroadcastFunction
POP EBX
POP EDI
RETN 4
}}

FCT_ASM(D2SpawnMonster_111)
PUSH DWORD PTR SS : [ESP + 0x18]
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH ECX
MOV ECX, DWORD PTR SS : [ESP + 0x18]
MOV EAX, DWORD PTR SS : [ESP + 0x28]
CALL V2SpawnMonster
RETN 0x18
}}

FCT_ASM(D2SpawnMonster_111b)
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH EDX
PUSH ECX
MOV EAX, DWORD PTR SS : [ESP + 0x18]
MOV EDX, DWORD PTR SS : [ESP + 0x2C]
MOV ECX, DWORD PTR SS : [ESP + 0x28]//superuniqueID
CALL V2SpawnMonster
RETN 0x18
}}

FCT_ASM(D2SpawnMonster_114)
PUSH ECX
MOV EBX, DWORD PTR SS : [ESP + 0x18]
MOV ECX, DWORD PTR SS : [ESP + 0x14]
MOV DWORD PTR SS : [ESP + 0x18], ECX
MOV ECX, DWORD PTR SS : [ESP + 0x10]
MOV DWORD PTR SS : [ESP + 0x14], ECX
MOV ECX, DWORD PTR SS : [ESP + 0xC]
MOV DWORD PTR SS : [ESP + 0x10], ECX
MOV ECX, DWORD PTR SS : [ESP + 0x8]
MOV DWORD PTR SS : [ESP + 0xC], ECX
MOV DWORD PTR SS : [ESP + 0x8], EDX
POP ECX
JMP V2SpawnMonster
}}

FCT_ASM(D2VerifIfNotCarry1_111)
PUSH EBX
PUSH ECX
MOV EBX, EDX
MOV EAX, DWORD PTR SS : [ESP + 0xC]
CALL V2VerifIfNotCarry1
POP EBX
RETN 4
}}

FCT_ASM(D2GameGetObject_111)
MOV EAX, EDX
MOV EDX, DWORD PTR SS : [ESP + 4]
CALL V2GameGetObject
RETN 4
}}


FCT_ASM(D2TestPositionInRoom_111)
PUSH EDI
PUSH EBX
MOV EDI, DWORD PTR SS : [ESP + 0xC]
MOV EAX, ECX
MOV EBX, EDX
CALL V2TestPositionInRoom
POP EBX
POP EDI
RETN 4
}}

FCT_ASM(D2GetItemTypesBIN_111)
MOV EAX, ECX
JMP V2GetItemTypesBIN
}}

//FCT_ASM ( D2OpenNPCMenu_111)
//	MOV ESI,ECX
//	JMP V2OpenNPCMenu
//}}
FCT_ASM(D2SendToServer_1XX)
PUSH DWORD PTR SS : [ESP + 0x4]
PUSH DWORD PTR SS : [ESP + 0x10]
PUSH 0
CALL V2SendToServer
RETN 0xC
}}

FCT_ASM(D2GetGameByClientID_114)
MOV ECX, DWORD PTR SS : [ESP + 0x4]
JMP V2GetGameByClientID
}}

FCT_ASM(D2GetGameByClientID_1XX)
POP EAX
POP ECX
PUSH EAX
JMP V2GetGameByClientID
}}

FCT_ASM(D2SaveGame_1XX)
POP EAX
POP ECX
PUSH EAX
JMP V2SaveGame
}}

FCT_ASM(D2SetColorPopup_114)
PUSH EDI
PUSH EDX
MOV EDI, ECX
CALL V2SetColorPopup
POP EDI
RETN
}}

FCT_ASM(D2LinkPortal_114)
PUSH ECX
MOV ECX, DWORD PTR SS : [ESP + 0x8]
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH DWORD PTR SS : [ESP + 0x14]
PUSH DWORD PTR SS : [ESP + 0x14]
CALL V2LinkPortal
POP ECX
RETN 0x10
}}

FCT_ASM(D2Game235C0_114)
PUSH ECX
PUSH EDX
MOV ECX, DWORD PTR SS : [ESP + 0xC]
MOV EDX, DWORD PTR SS : [ESP + 0x10]
POP EDX
POP ECX
RETN 0x8
}}

#define SETFCTADDR(F, I, N) setFctAddr((DWORD*)&N, (HMODULE)offset_##F, (LPCSTR)I)
void setFctAddr(DWORD* addr, HMODULE module, LPCSTR index)
  {
  if (index)
    {
    *addr = (DWORD)GetProcAddress(module, index);
    if (!*addr)
      {
      log_msg("Bad index fct %d for %08X\n", index, module);
      }
    }
  else
    *addr = NULL;
  }

void intCommonFunctions()
  {
  switch ((eGameVersion)version_D2Common)
    {
    case V114d:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x833E0);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x268600);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x5AB20);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x155C90);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x5C4F0);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x117079);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x2552E0);
      break;
    case V113d:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x17B0);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x5B0E0);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x5AB20);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x1160);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x17E0);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0xB5E0);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x80C40);
      break;
    case V113c:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x12D0);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x1C020);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x1BA60);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x1300);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x17A0);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x9900);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x59870);
      break;
    case V112:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x1220);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x116C0);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x11100);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x1140);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x1540);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x9900);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x7D2A0);
      break;
    case V111b:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x1800);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x1A100);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x19B40);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x1380);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x12F0);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x98D0);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x32AA0);
      break;
    case V111:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x15D0);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x5D7D0);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x5D210);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x11F0);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x13F0);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x96E0);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x71EB0);
      break;
    case V110:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x82C80);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x12410);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x12910);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x2B1A0);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x642B0);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x84268);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x29FA0);
      break;
    case V109d:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x000000);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x000000);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x000000);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x000000);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x000000);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x739B4);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x1F510);
      break;
    default:
      D2GetCharStatsBIN = (TD2GetCharStatsBIN)(offset_D2Common + 0x000000);
      D2CompileCubeInput = (TD2CompileCubeInput)(offset_D2Common + 0x000000);
      D2CompileCubeOutput = (TD2CompileCubeOutput)(offset_D2Common + 0x000000);
      D2GetItemTypesBIN = (TD2GetItemTypesBIN)(offset_D2Common + 0x000000);
      D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)(offset_D2Common + 0x000000);
      D2ReadFile = (TD2ReadFile)(offset_D2Common + 0x738A4);
      D2LoadSuperuniques = (TD2LoadSuperuniques)(offset_D2Common + 0x1F500);
      break;
    }
  }

// Client Functions
void initClientFunctions()
  {
  switch ((eGameVersion)version_D2Client)
    {
    case V114d:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0x788B0);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x000000);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0x787B0);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0xA7D00);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0xE4D80);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x521C0);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0xB9A00);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x790D0);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x78350);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x55F20);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x89980);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x54600);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x7DC60);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0x000000);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0x000000);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0x000000);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x000000);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0x000000);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0x000000);

      ptResolutionY = (DWORD*)(offset_D2Client + 0x311470);
      ptResolutionX = (DWORD*)(offset_D2Client + 0x31146C);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x3A285C);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x3A2858);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x3A04F4);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x000000);
      ptMouseY = (DWORD*)(offset_D2Client + 0x3A6AAC);
      ptMouseX = (DWORD*)(offset_D2Client + 0x3A6AB0);
      ptptClientChar = (Unit**)(offset_D2Client + 0x3A5E74);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V113d:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0xA9480);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x000000);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0xB6890);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0xBF640);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x2CE40);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x18820);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0x26270);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x790D0);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0xB61F0);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x1C190);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x90C10);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x18AA0);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x7DC60);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0x000000);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0x000000);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0x000000);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x000000);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0x000000);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0x000000);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xF7038);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xF7034);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x11D358);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x11D354);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x1087B4);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x000000);
      ptMouseY = (DWORD*)(offset_D2Client + 0x11C94C);
      ptMouseX = (DWORD*)(offset_D2Client + 0x11C950);
      ptptClientChar = (Unit**)(offset_D2Client + 0x11D050);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V113c:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0x2B420);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x000000);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0x147A0);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0xBCEA0);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x54E10);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0xBF5F0);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0x88A70);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x46150);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x143E0);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0xC2790);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x8CD00);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0xBEAF0);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x4ABE0);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0x000000);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0x000000);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0x000000);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x000000);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0x000000);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0x000000);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xDBC4C);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xDBC48);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x11B9A4);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x11B9A0);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x119854);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x000000);
      ptMouseY = (DWORD*)(offset_D2Client + 0x11B824);
      ptMouseX = (DWORD*)(offset_D2Client + 0x11B828);
      ptptClientChar = (Unit**)(offset_D2Client + 0x11BBFC);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V112:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0xBEF70);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x000000);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0x79670);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0x6B280);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x88EA0);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x8B7A0);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0x31FA0);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x18450);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x791A0);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x8EF00);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0xA6640);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x8B8F0);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x1CC00);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0x000000);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0x000000);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0x000000);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x000000);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0x000000);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0x000000);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xDC6E4);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xDC6E0);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x11BD2C);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x11BD28);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x10330C);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x11BFF4);
      ptMouseY = (DWORD*)(offset_D2Client + 0x101634);
      ptMouseX = (DWORD*)(offset_D2Client + 0x101638);
      ptptClientChar = (Unit**)(offset_D2Client + 0x11C3D0);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V111b:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0xA9070);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x000000);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0x5E4E0);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0x89320);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x21250);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x62070);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0x54210);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x571C0);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x5DE40);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x65690);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x710C0);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x621C0);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x5BA90);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0x000000);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0x000000);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0x000000);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x000000);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0x000000);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0x000000);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xF4FC8);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xF4FC4);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x11BEFC);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x11BEF8);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x11A2F4);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x11C2A8);
      ptMouseY = (DWORD*)(offset_D2Client + 0x11B414);
      ptMouseX = (DWORD*)(offset_D2Client + 0x11B418);
      ptptClientChar = (Unit**)(offset_D2Client + 0x11C1E0);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V111:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0x75D00);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x000000);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0x73620);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0x828A0);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0xB8CB0);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x9EEB0);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0x3ACC0);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x000000);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x73260);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0xA1F30);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0xA6520);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x9E3B0);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x8E480);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0x000000);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0x000000);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0x000000);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x000000);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0x000000);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0x000000);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xF5C60);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xF5C5C);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x11BD28);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x11BD24);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0xFB3F4);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x11BFB8);
      ptMouseY = (DWORD*)(offset_D2Client + 0x10A40C);
      ptMouseX = (DWORD*)(offset_D2Client + 0x10A410);
      ptptClientChar = (Unit**)(offset_D2Client + 0x11C4F0);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V110:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0x1000);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x1140);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0xDB50);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x15A80);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0x2FD60);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x521C0);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x80430);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0xB5820);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x000000);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x000000);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x83260);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x000000);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x84110);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x000000);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0xC080);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0xC090);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0xB7BC0);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0xB7BD0);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x883D0);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0xBF60);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0xD990);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xD40F0);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xD40F4);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x11A74C);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x11A748);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x000000);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x10795C);
      ptMouseY = (DWORD*)(offset_D2Client + 0x000000);
      ptMouseX = (DWORD*)(offset_D2Client + 0x000000);
      ptptClientChar = (Unit**)(offset_D2Client + 0x000000);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0x000000);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0x000000);
      break;
    case V109d:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0x1000);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x1150);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0xD630);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0x297F0);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x4BB20);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x84DE0);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0xB36E0);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x000000);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x000000);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x87CC0);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x000000);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x88B30);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x000000);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0xB9F0);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0xB59F0);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0xB5A00);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x8CFC0);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0xB910);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0xD200);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xD40E0);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xD40E4);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x124958);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x124954);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x000000);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x000000);
      ptMouseY = (DWORD*)(offset_D2Client + 0x000000);
      ptMouseX = (DWORD*)(offset_D2Client + 0x000000);
      ptptClientChar = (Unit**)(offset_D2Client + 0x000000);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0xDA828);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0xD9EA8);
      break;
    default:
      D2LoadImage = (TD2LoadImage)(offset_D2Client + 0x1000);
      D2FreeImage = (TD2FreeImage)(offset_D2Client + 0x1150);
      D2SendMsgToAll = (TD2SendMsgToAll)(offset_D2Client + 0xD640);
      D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)(offset_D2Client + 0x000000);
      D2PrintStatsPage = (TD2PrintStatsPage)(offset_D2Client + 0x29800);
      D2PrintStat = (TD2PrintStat)(offset_D2Client + 0x4BB20);
      D2SetColorPopup = (TD2SetColorPopup)(offset_D2Client + 0x85A60);
      D2PlaySound = (TD2PlaySound)(offset_D2Client + 0xB4360);
      D2GetCurrentNPC = (TD2GetCurrentNPC)(offset_D2Client + 0x000000);
      D2SendToServerXX = (TD2SendToServerXX)(offset_D2Client + 0x000000);
      D2TogglePage = (TD2TogglePage)(offset_D2Client + 0x88940);
      D2ClickOnStashButton = (TD2ClickOnStashButton)(offset_D2Client + 0x000000);
      D2LoadBuySelBtn = (TD2LoadBuySelBtn)(offset_D2Client + 0x897B0);
      D2ReloadGambleScreen = (TD2ReloadGambleScreen)(offset_D2Client + 0x000000);

      D2isLODGame = (TD2isLODGame)(offset_D2Client + 0xBA00);
      D2GetDifficultyLevel = (TD2GetDifficultyLevel)(offset_D2Client + 0x000000);
      D2GetMouseX = (TD2GetMouseX)(offset_D2Client + 0xB6670);
      D2GetMouseY = (TD2GetMouseY)(offset_D2Client + 0xB6680);
      D2GetClientPlayer = (TD2GetClientPlayer)(offset_D2Client + 0x8DC40);
      D2CleanStatMouseUp = (TD2CleanStatMouseUp)(offset_D2Client + 0xB920);
      D2SendToServer3 = (TD2SendToServer3)(offset_D2Client + 0xD210);

      ptResolutionY = (DWORD*)(offset_D2Client + 0xD50E8);
      ptResolutionX = (DWORD*)(offset_D2Client + 0xD50EC);
      ptNegWindowStartY = (DWORD*)(offset_D2Client + 0x125AD8);
      ptWindowStartX = (DWORD*)(offset_D2Client + 0x125AD4);
      ptIsLodGame = (DWORD*)(offset_D2Client + 0x000000);
      ptDifficultyLevel = (BYTE*)(offset_D2Client + 0x000000);
      ptMouseY = (DWORD*)(offset_D2Client + 0x000000);
      ptMouseX = (DWORD*)(offset_D2Client + 0x000000);
      ptptClientChar = (Unit**)(offset_D2Client + 0x000000);
      ptNbStatDesc = (DWORD*)(offset_D2Client + 0xDB918);
      ptStatDescTable = (DWORD*)(offset_D2Client + 0xDAF98);
    }
  }

void initGameFunctions()
  {
  switch ((eGameVersion)version_D2Game)
    {
    case V114d:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0x12C550);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0x12FEE0);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0x12DED0);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0x13B280);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0x13C4A0);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x16CF40);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x15CA40);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x63740);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x1A09E0);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x142B40);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x1335E0);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x152F60);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x155230);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x194270);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x194280);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x1E9170);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x1F78B0);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0x1FCFE0);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x1F81C0);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x1E9DF0);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0x1FD200);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0x12CA10);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x000000);
      ptClientTable = (NetClient**)(offset_D2Game + 0x4842A8);
      break;
    case V113d:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0xE5070);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0xBC700);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0xBB510);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0xDB780);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0xDD4F0);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x15F40);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0xB2F70);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x1340);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0xCDE20);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x59980);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x3A4C0);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x6DC40);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x6FE10);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x941E0);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x941D0);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x31920);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x4EAD0);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0xC8850);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x49480);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x2C3F0);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0xC6EC0);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0xBE660);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x000000);
      ptClientTable = (NetClient**)(offset_D2Game + 0x1105E0);
      break;
    case V113c:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0x49930);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0x2AAE0);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0x29820);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0x8A3E0);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0x8D5F0);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0xA22E0);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0xD2070);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x1280);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x24950);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x200E0);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x54810);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0xE03A0);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0xE1D90);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x70180);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x70170);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0xA9610);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x85B60);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0xB8610);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x7B4E0);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0xA39D0);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0xB6C80);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0x2C830);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x000000);
      ptClientTable = (NetClient**)(offset_D2Game + 0x1107B8);
      break;
    case V112:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0xEB060);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0xA6360);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0xA5080);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0x7D220);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0x802E0);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0xAE930);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x11FF0);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x11F0);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x40B90);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0xD410);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x44950);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x93650);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x94E70);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0xD1AA0);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0xD1A90);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0xDBE90);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0xCD0F0);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0xB3B90);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0xC2A90);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0xD6250);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0xB2210);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0xA8090);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x000000);
      ptClientTable = (NetClient**)(offset_D2Game + 0x1105E0);
      break;
    case V111b:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0xE8210);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0xE49A0);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0xE36D0);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0xA0D50);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0xA3F20);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x109F0);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x43E60);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x1DF0);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0xEC7E0);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x235C0);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x25D50);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0xBEF80);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0xC09E0);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x34920);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x34910);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x85AA0);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0xD7BD0);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0x2BC80);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0xD2D70);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x7FE60);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0x2A300);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0xE66D0);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x000000);
      ptClientTable = (NetClient**)(offset_D2Game + 0x1115E0);
      break;
    case V111:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0xE3DA0);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0xE0520);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0xDF250);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0x41420);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0x44D00);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x27230);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x38D90);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x1090);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x4ABE0);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0xD6D10);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0xB9D70);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x97620);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x99760);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x9B480);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x9B470);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x84730);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x75980);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0xEAB20);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x70320);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x7F200);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0xE92B0);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0xE2390);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x000000);
      ptClientTable = (NetClient**)(offset_D2Game + 0x111718);
      break;
    case V110:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0x6C60);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0x94E0);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0xB0E0);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0xC710);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0xDB50);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x000000);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x128F0);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x22070);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x3F220);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x000000);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x5B8A0);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x8BB00);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x000000);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x000000);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x000000);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x000000);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x000000);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0x000000);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x000000);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x000000);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0x000000);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0x89C0);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x8C2E0);
      ptClientTable = (NetClient**)(offset_D2Game + 0x113FB8);
      break;
    case V109d:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0x000000);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0x000000);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0x000000);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0xC650);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0xD920);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x000000);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x000000);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x000000);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x000000);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x000000);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x4F500);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x7BFD0);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x000000);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x000000);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x000000);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x000000);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x000000);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0x000000);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x000000);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x000000);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0x000000);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0x000000);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x7C7B0);
      ptClientTable = (NetClient**)(offset_D2Game + 0xF2918);
      break;
    default:
      D2AddClient = (TD2AddClient)(offset_D2Game + 0x000000);
      D2GetGameByClientID = (TD2GetGameByClientID)(offset_D2Game + 0x000000);
      D2BroadcastFunction = (TD2BroadcastFunction)(offset_D2Game + 0x000000);
      D2SendPacket = (TD2SendPacket)(offset_D2Game + 0xC380);
      D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)(offset_D2Game + 0xD650);
      D2LinkPortal = (TD2LinkPortal)(offset_D2Game + 0x000000);
      D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)(offset_D2Game + 0x000000);
      D2TestPositionInRoom = (TD2TestPositionInRoom)(offset_D2Game + 0x000000);
      D2SpawnMonster = (TD2SpawnMonster)(offset_D2Game + 0x000000);
      D2Game235C0 = (TD2Game235C0)(offset_D2Game + 0x000000);
      D2LoadInventory = (TD2LoadInventory)(offset_D2Game + 0x4F100);
      D2GameGetObject = (TD2GameGetObject)(offset_D2Game + 0x7BAE0);
      D2CreateUnit = (TD2CreateUnit)(offset_D2Game + 0x000000);
      D2OpenPandPortal = (TD2OpenPandPortal)(offset_D2Game + 0x000000);
      D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)(offset_D2Game + 0x000000);
      D2MephIA = (TD2MephIA)(offset_D2Game + 0x000000);
      D2DiabloIA = (TD2DiabloIA)(offset_D2Game + 0x000000);
      D2BaalIA = (TD2BaalIA)(offset_D2Game + 0x000000);
      D2UberMephIA = (TD2UberMephIA)(offset_D2Game + 0x000000);
      D2UberDiabloIA = (TD2UberDiabloIA)(offset_D2Game + 0x000000);
      D2UberBaalIA = (TD2UberBaalIA)(offset_D2Game + 0x000000);
      D2SaveGame = (TD2SaveGame)(offset_D2Game + 0x000000);
      D2GetClient = (TD2GetClient)(offset_D2Game + 0x7C2C0);
      ptClientTable = (NetClient**)(offset_D2Game + 0xF2A80);
    }
  }

void initD2functions()
  {
#define D2S(F, I, R, N, P)	SETFCTADDR(F, I, N);
#define D2F(F, I, R, N, P)	SETFCTADDR(F, I, N);
#define E2S(F, A, R, N, P)	N = (T##N)(offset_##F + 0x##A);
#define E2F(F, A, R, N, P)	N = (T##N)(offset_##F + 0x##A);
#define E2C(F, A, T, N)		pt##N = (T*)(offset_##F + 0x##A);
#define F8(X, Z, A,B,C,D,E,F,G,H,I, R, N, P) if (version_##Z == V114d) { E2S(Z, I, 0, N, 0) } else { setFctAddr((DWORD*)&N, (HMODULE)offset_##Z, (LPCSTR)(version_##Z == V113d? H : (version_##Z == V113c? G : (version_##Z == V112? F : (version_##Z == V111b? E : (version_##Z == V111? D : (version_##Z == V110? C : (version_##Z == V109d? B : A)))))))); }

  intCommonFunctions();
  initClientFunctions();
  initGameFunctions();

#include "../Commons/D2Funcs.h"
                            //D2FogMemAlloc = (TD2FogMemAlloc)(offset_D2Game + 0xB380);
                            //E2S(D2Game, B380, 0, D2FogMemAlloc, 0)
                            //return;
  SgptDataTables = *(DataTables**)R8(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C, A33F0, 344304);
  if (version_D2Common < V110)
    {
    D2S(D2Common, 10581, CharStatsBIN*, D2Common10581, (DWORD charID));//ONLY in 1.09
    D2S(D2Common, 10598, ItemStatCostBIN*, D2Common10598, (DWORD itemStatCostID));//ONLY in 1.09
    D2S(D2Common, 10673, ItemTypesBIN*, D2Common10673, (DWORD itemTypesID));//ONLY in 1.09
    }
#undef F8
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

  //////////////// MISC FCT ////////////////
  //setImage = version_D2Common >= V111 ? setImage_111 : setImage_1XX;
  //setFrame = version_D2Common >= V111 ? setFrame_111 : setFrame_1XX;
  getDescStrPos = version_D2Common >= V110 ? getDescStrPos_10 : getDescStrPos_9;
  compileTxtFile = version_D2Common == V114d ? compileTxtFile_114 : version_D2Common >= V111 ? compileTxtFile_111 : version_D2Common == V110 ? compileTxtFile_10 : compileTxtFile_9;


  //////////////// SELECT RIGHT ADDR FUNCTION ////////////////
//#define V3(V,T,F,A,B,C,D)\
//	if (version_##F == V109b) V = (T) (offset_##F + 0x##A);\
//	else if (version_##F == V109d) V = (T) (offset_##F + 0x##B);\
//	else if (version_##F == V110) V = (T) (offset_##F + 0x##C);\
//	else if (version_##F == V111) V = (T) (offset_##F + 0x##D)

  //if (version_D2Common != V111b)
  //{
    //SETFCTADDR( D2Common,	10332, D2GetLevelID);
    //SETFCTADDR( D2Common,	10623, D2GetDropRoom);
    //SETFCTADDR( D2Common,	10461, D2InvRemoveItem);
    //SETFCTADDR( D2Common,	10855, D2CanPutItemInInv);
    //SETFCTADDR( D2Common,	10880, D2InvAddItem);
    //SETFCTADDR( D2Common,	10402, D2InventoryGetFirstItem);
    //SETFCTADDR( D2Common,	10934, D2UnitGetNextItem);
    //SETFCTADDR( D2Common,	11095, D2GetRealItem);
    //SETFCTADDR( D2Common,	11080, D2GetPosition);
    //SETFCTADDR( D2Common,	10455, D2GetMaxGoldBank);
    //SETFCTADDR( D2Common,	10172, D2GetRoom);
    //SETFCTADDR( D2Common,	10218, D2InitPlayerData);
    //SETFCTADDR( D2Common,	10914, D2FreePlayerData);
    //SETFCTADDR( D2Common,	10562, D2GetPlayerData);
    //SETFCTADDR( D2Common,	10343, D2GetMaxGold);
    //SETFCTADDR( D2Common,	10500, D2GetGemsBIN);
    //SETFCTADDR( D2Common,	10109, D2AddPlayerStat);
    //SETFCTADDR( D2Common,	11092, D2GetPlayerStat);
    //SETFCTADDR( D2Common,	10733, D2GetPlayerBaseStat);
    //SETFCTADDR( D2Common,	10653, D2CompileTxtFile);
    //SETFCTADDR( D2Common,	10573, D2GetItemsBIN);
    //SETFCTADDR( D2Common,	10687, D2GetNbRunesBIN);
    //SETFCTADDR( D2Common,	10775, D2GetRunesBIN);
    //SETFCTADDR( D2Common,	10450, D2GetSuperUniqueBIN);
    //SETFCTADDR( D2Common,	10927, D2GetItemQuality);
    //SETFCTADDR( D2Common,	10911, D2TestFlags);
    //SETFCTADDR( D2Common,	10898, D2GetItemLevel);
    //SETFCTADDR( D2Common,	10820, D2ItemGetPage);
    //SETFCTADDR( D2Common,	10485, D2ItemSetPage);
    //SETFCTADDR( D2Common,	11017, D2CheckItemType);
    //SETFCTADDR( D2Common,	10692, D2GetUniqueID);
    //SETFCTADDR( D2Common,	10816, D2GetNbSocket);
    //SETFCTADDR( D2Common,	10880, D2isEtheral);
    //SETFCTADDR( D2Common,	10956, D2SaveItem);
    //SETFCTADDR( D2Common,	10950, D2IncSkillBaseLevel);
    //SETFCTADDR( D2Common,	10700, D2GetSkillLevel);
    //SETFCTADDR( D2Common,	10027, D2Common10027);
    //SETFCTADDR( D2Common,	10099, D2SetSkillBaseLevel);
    //SETFCTADDR( D2Common,	10746, D2GetCubeMainBIN);
    //SETFCTADDR( D2Common,	10639, D2GetNbCubeMainBIN);
    //SETFCTADDR( D2Common,	10254, D2GetSkillCost);
    //SETFCTADDR( D2Common,	10471, D2GetObjectFlags);
    //SETFCTADDR( D2Common,	10572, D2SetObjectFlags);
    //SETFCTADDR( D2Common,	10188, D2Common11084);
    //SETFCTADDR( D2Common,	10440, D2Common10572);
    //SETFCTADDR( D2Common,	10655, D2GetDifficultyLevelsBIN);
    //SETFCTADDR( D2Game,		10039, D2SetNbPlayers);
    //SETFCTADDR( D2Win,		10061, D2PrintLineOnTextBox);
    //SETFCTADDR( D2Win,		10020, D2PrintString);
    //SETFCTADDR( D2Win,		10034, D2GetPixelLen);
    //SETFCTADDR( D2Win,		10141, D2SetFont);
    //SETFCTADDR( D2Win,		10118, D2PrintPopup);
    //SETFCTADDR( D2Win,		10147, D2CreateTextBox);
    //SETFCTADDR( D2Lang,		10009, D2GetLang);
    //SETFCTADDR( D2Lang,		10005, D2GetStringFromIndex);
    //SETFCTADDR( D2gfx,		10000, D2GetResolution);
    //SETFCTADDR( D2gfx,		10047, D2PrintImage);
    //SETFCTADDR( D2gfx,		10028, D2FillArea);
    //SETFCTADDR( D2Net,		10035, D2SendToServer);
    ////SETFCTADDR( D2Net,		10018, D2SendToClient);//SAME IN BOTH VERSION
    //SETFCTADDR( D2CMP,		10021, D2CMP10014);
    //if (version_D2Common != V111)
    //{
      //setImage = setImage_1XX;
      //setFrame = setFrame_1XX;
      //SETFCTADDR( D2Common,	10057, D2GetLevelID);
      //SETFCTADDR( D2Common,	10138, D2GetDropRoom);
      //SETFCTADDR( D2Common,	10243, D2InvRemoveItem);
      //SETFCTADDR( D2Common,	10246, D2CanPutItemInInv);
      //SETFCTADDR( D2Common,	10249, D2InvAddItem);
      //SETFCTADDR( D2Common,	10277, D2InventoryGetFirstItem);
      //SETFCTADDR( D2Common,	10304, D2UnitGetNextItem);
      //SETFCTADDR( D2Common,	10305, D2GetRealItem);
      //SETFCTADDR( D2Common,	10332, D2GetPosition);
      //SETFCTADDR( D2Common,	10339, D2GetMaxGoldBank);
      //SETFCTADDR( D2Common,	10342, D2GetRoom);
      //SETFCTADDR( D2Common,	10420, D2InitPlayerData);
      //SETFCTADDR( D2Common,	10421, D2FreePlayerData);
      //SETFCTADDR( D2Common,	10424, D2GetPlayerData);
      //SETFCTADDR( D2Common,	10439, D2GetMaxGold);
      //SETFCTADDR( D2Common,	10616, D2GetGemsBIN);
      //SETFCTADDR( D2Common,	10518, D2AddPlayerStat);
      //SETFCTADDR( D2Common,	10519, D2GetPlayerStat);
      //SETFCTADDR( D2Common,	10521, D2GetPlayerBaseStat);
      //SETFCTADDR( D2Common,	10578, D2CompileTxtFile);
      //SETFCTADDR( D2Common,	10600, D2GetItemsBIN);
      //SETFCTADDR( D2Common,	10619, D2GetNbRunesBIN);
      //SETFCTADDR( D2Common,	10620, D2GetRunesBIN);
      //SETFCTADDR( D2Common,	10668, D2GetSuperUniqueBIN);
      //SETFCTADDR( D2Common,	10695, D2GetItemQuality);
      //SETFCTADDR( D2Common,	10707, D2TestFlags);
      //SETFCTADDR( D2Common,	10717, D2GetItemLevel);
      //SETFCTADDR( D2Common,	10719, D2ItemGetPage);
      //SETFCTADDR( D2Common,	10720, D2ItemSetPage);
      //SETFCTADDR( D2Common,	10731, D2CheckItemType);
      //SETFCTADDR( D2Common,	10732, D2GetUniqueID);
      //SETFCTADDR( D2Common,	10816, D2GetNbSocket);
      //SETFCTADDR( D2Common,	11163, D2isEtheral);
      //SETFCTADDR( D2Common,	10881, D2SaveItem);
      //SETFCTADDR( D2Common,	10952, D2IncSkillBaseLevel);
      //SETFCTADDR( D2Common,	10968, D2GetSkillLevel);
      //SETFCTADDR( D2Common,	10940, D2Common10027);
      //SETFCTADDR( D2Common,	10953, D2SetSkillBaseLevel);
      //SETFCTADDR( D2Common,	11232, D2GetCubeMainBIN);
      //SETFCTADDR( D2Common,	11233, D2GetNbCubeMainBIN);
      //SETFCTADDR( D2Common,	11276, D2GetSkillCost);
      //SETFCTADDR( D2Common,	10655, D2GetDifficultyLevelsBIN);
      //SETFCTADDR( D2Game,		10059, D2SetNbPlayers);
      //SETFCTADDR( D2Win,		10046, D2PrintLineOnTextBox);
      //SETFCTADDR( D2Win,		10117, D2PrintString);
      //SETFCTADDR( D2Win,		10121, D2GetPixelLen);
      //SETFCTADDR( D2Win,		10127, D2SetFont);
      //SETFCTADDR( D2Win,		10129, D2PrintPopup);
      //SETFCTADDR( D2Win,		10017, D2CreateTextBox);
      //SETFCTADDR( D2Lang,		10007, D2GetLang);
      //SETFCTADDR( D2Lang,		10004, D2GetStringFromIndex);
      //SETFCTADDR( D2gfx,		10005, D2GetResolution);
      //SETFCTADDR( D2gfx,		10072, D2PrintImage);
      //SETFCTADDR( D2gfx,		10055, D2FillArea);
      //SETFCTADDR( D2Net,		10005, D2SendToServer); //(DWORD zero, void* data, DWORD size)
      //SETFCTADDR( D2Net,		10006, D2SendToClient);
      //SETFCTADDR( Fog,		10023, D2FogAssertOld);
      //SETFCTADDR( D2CMP,		10032, D2CMP10014);
    //}
  //}

  //V3(ptResolutionY,		DWORD*,					D2Client,	D50E8,	D40E0,	D40F0,	F5C60);
  //V3(ptResolutionX,		DWORD*,					D2Client,	D50EC,	D40E4,	D40F4,	F5C5C);
  //V3(ptNegWindowStartY,	DWORD*,					D2Client,	125AD8,	124958,	11A74C,	11BD28);
  //V3(ptWindowStartX,		DWORD*,					D2Client,	125AD4,	124954,	11A748,	11BD24);
  //V3(ptGameTypeMode,		DWORD*,					D2Launch,	55818,	56088,	2CD5C,	0000);
  //V3(ptClientTable,		NetClient**,			D2Game,		F2A80,	F2918,	113FB8,	111718);
  //V3(ptIsLodGame,			DWORD*,					D2Client,	0000,	0000,	0000,	FB3F4);
  //V3(ptDifficultyLevel,	BYTE*,					D2Client,	0000,	0000,	10795C,	11BFB8);
  //V3(ptMouseY,			DWORD*,					D2Client,	0000,	0000,	0000,	10A40C);
  //V3(ptMouseX,			DWORD*,					D2Client,	0000,	0000,	0000,	10A410);
  //V3(ptptClientChar,		Unit**,					D2Client,	0000,	0000,	0000,	11C4F0);
  //V3(ptNbStatDesc,			DWORD*,					D2Client,	DB918,	DA828,	0000,	0000);
  //V3(ptStatDescTable,		DWORD*,					D2Client,	DAF98,	D9EA8,	0000,	0000);

  //V3(D2LoadImage,			TD2LoadImage,			D2Client,	1000,	1000,	1000,	75D00);
  //V3(D2FreeImage,			TD2FreeImage,			D2Client,	1150,	1150,	1140,	0000);
  //V3(D2CleanStatMouseUp,	TD2CleanStatMouseUp,	D2Client,	B920,	B910,	BF60,	0000);
  //V3(D2isLODGame,			TD2isLODGame,			D2Client,	BA00,	B9F0,	C080,	0000);
  //V3(D2GetDifficultyLevel,TD2GetDifficultyLevel,	D2Client,	000,	000,	C090,	0000);//1.09 should be BA10 (b) BA00 (d)
  //V3(D2SendToServer3,		TD2SendToServer3,		D2Client,	D210,	D200,	D990,	0000);
  //V3(D2SendToServer7,		TD2SendToServer7,		D2Client,	000,	000,	D9E0,	0000);
  //V3(D2SendToServer5,		TD2SendToServer5,		D2Client,	000,	000,	DA20,	0000);
  //V3(D2SendToServer9,		TD2SendToServer9,		D2Client,	000,	000,	DA40,	0000);
  //V3(D2SendToServer13,	TD2SendToServer13,		D2Client,	000,	000,	DA70,	0000);
  //V3(D2SendMsgToAll,		TD2SendMsgToAll,		D2Client,	D640,	D630,	DB50,	73620);
  //V3(D2PrintStatsPage,	TD2PrintStatsPage,		D2Client,	29800,	297F0,	2FD60,	828A0);
  //V3(D2SetColorPopup,		TD2SetColorPopup,		D2Client,	85A60,	84DE0,	80430,	9EEB0);
  //V3(D2SendToServerXX,	TD2SendToServerXX,		D2Client,	000,	000,	000,	73260);
  //V3(D2TogglePage,		TD2TogglePage,			D2Client,	88940,	87CC0,	83260,	A1F30);
  //V3(D2LoadBuySelBtn,		TD2LoadBuySelBtn,		D2Client,	897B0,	88B30,	84110,	9E3B0);
  //V3(D2GetClientPlayer,	TD2GetClientPlayer,		D2Client,	8DC40,	8CFC0,	883D0,	0000);
  //V3(D2PlaySound,			TD2PlaySound,			D2Client,	B4360,	B36E0,	B5820,	3ACC0);
  //V3(D2GetMouseX,			TD2GetMouseX,			D2Client,	B6670,	B59F0,	B7BC0,	0000);
  //V3(D2GetMouseY,			TD2GetMouseY,			D2Client,	B6680,	B5A00,	B7BD0,	0000);
//	//V3(D2FillRect,			TD2FillRect,			D2Client,	B9970,	B8CF0,	BB0F0,	0000);

  //V3(D2PrintStat,			TD2PrintStat,			D2Client,	4BB20,	4BB20,	521C0,	B8CB0);

  //V3(D2AddClient,			TD2AddClient,			D2Game,		000,	000,	6C60,	E3DA0);
  //V3(D2SendPacket,		TD2SendPacket,			D2Game,		C380,	C650,	C710,	41420);
  //V3(D2GetGameByClientID,	TD2GetGameByClientID,	D2Game,		000,	000,	94E0,	E0520);
  //V3(D2BroadcastFunction,	TD2BroadcastFunction,	D2Game,		000,	000,	B0E0,	DF250);
  //V3(D2SetSkillBaseLevelOnClient,	TD2SetSkillBaseLevelOnClient,D2Game,	D650,	D920,	DB50,	44D00);
  //V3(D2VerifIfNotCarry1,	TD2VerifIfNotCarry1,	D2Game,		000,	000,	128F0,	38D90);
  //V3(D2TestPositionInRoom,TD2TestPositionInRoom,	D2Game,		000,	000,	22070,	01090);
  //V3(D2LoadInventory,		TD2LoadInventory,		D2Game,		4F100,	4F500,	5B8A0,	B9D70);
  //V3(D2GameGetObject,		TD2GameGetObject,		D2Game,		7BAE0,	7BFD0,	8BB00,	97620);
  //V3(D2GetClient,			TD2GetClient,			D2Game,		7C2C0,	7C7B0,	8C2E0,	000);
  //V3(D2GetOwnerMonster,	TD2GetOwnerMonster,		D2Game,		000,	000,	9F320,	501C0);
  //V3(D2ReadFile,			TD2ReadFile,			D2Common,	738A4,	739B4,  84268, 96E0);//1.11
  //V3(D2CompileCubeInput,	TD2CompileCubeInput,	D2Common,	000,	000,	12410,	5D7D0);
  //V3(D2CompileCubeOutput,	TD2CompileCubeOutput,	D2Common,	000,	000,	12910,	5D210);
  //V3(D2GetCharStatsBIN,	TD2GetCharStatsBIN,		D2Common,	000,	000,	82C80,	015D0);
  //V3(D2LoadSuperuniques,	TD2LoadSuperuniques,	D2Common,	1F500,	1F510,	29FA0,	71EB0);
  //V3(D2GetItemStatCostBIN,TD2GetItemStatCostBIN,	D2Common,	000,	000,	642B0,	13F0);
  //V3(D2GetItemTypesBIN,	TD2GetItemTypesBIN,		D2Common,	000,	000,	2B1A0,	11F0);
  //V3(D2SpawnMonster,		TD2SpawnMonster,		D2Game,		000,	000,	3F220,	4ABE0);
  //V3(D2ReloadGambleScreen,TD2ReloadGambleScreen,	D2Game,		000,	000,	000,	8E480);
  //V3(D2SaveGame,			TD2SaveGame,			D2Game,		000,	000,	89C0,	E2390);
  //V3(D2ClickOnStashButton,TD2ClickOnStashButton,	D2Client,	000,	000,	000,	A6520);
  //V3(D2CreateUnit,		TD2CreateUnit,			D2Game,		000,	000,	000,	99760);
  //V3(D2LinkPortal,		TD2LinkPortal,			D2Game,		000,	000,	000,	27230);
  //V3(D2Game235C0,			TD2Game235C0,			D2Game,		000,	000,	000,	D6D10);
  //V3(D2OpenPandPortal,	TD2OpenPandPortal,		D2Game,		000,	000,	000,	9B480);
  //V3(D2OpenPandFinalPortal,TD2OpenPandFinalPortal,D2Game,		000,	000,	000,	9B470);
  //V3(D2MephIA,			TD2MephIA,				D2Game,		000,	000,	000,	84730);
  //V3(D2DiabloIA,			TD2DiabloIA,			D2Game,		000,	000,	000,	75980);
  //V3(D2BaalIA,			TD2BaalIA,				D2Game,		000,	000,	000,	EAB20);
  //V3(D2UberMephIA,		TD2UberMephIA,			D2Game,		000,	000,	000,	70320);
  //V3(D2UberDiabloIA,		TD2UberDiabloIA,		D2Game,		000,	000,	000,	7F200);
  //V3(D2UberBaalIA,		TD2UberBaalIA,			D2Game,		000,	000,	000,	E92B0);

//#undef V3

  //V2SetPlayerStat = D2SetPlayerStat;
  V2AddPlayerStat = D2AddPlayerStat;
  V2GetPlayerStat = D2GetPlayerStat;
  //V2GetPlayerStat20 = D2GetPlayerStat20;
  V2GetPlayerBaseStat = D2GetPlayerBaseStat;
  V2SetSkillBaseLevel = D2SetSkillBaseLevel;
  V2SetSkillBaseLevelOnClient = D2SetSkillBaseLevelOnClient;
  V2PrintStat = D2PrintStat;
  V2SendMsgToAll = D2SendMsgToAll;
  V2SetColorPopup = D2SetColorPopup;
  V2LoadImage = D2LoadImage;
  V2PlaySound = D2PlaySound;
  V2GetCharStatsBIN = D2GetCharStatsBIN;
  V2GetItemStatCostBIN = D2GetItemStatCostBIN;
  V2SendToServer = D2SendToServer;
  V2SendPacket = D2SendPacket;
  V2LoadInventory = D2LoadInventory;
  V2CompileCubeInput = D2CompileCubeInput;
  V2CompileCubeOutput = D2CompileCubeOutput;
  V2BroadcastFunction = D2BroadcastFunction;
  V2GetGameByClientID = D2GetGameByClientID;
  V2SpawnMonster = D2SpawnMonster;
  V2VerifIfNotCarry1 = D2VerifIfNotCarry1;
  V2GameGetObject = D2GameGetObject;
  V2TestPositionInRoom = D2TestPositionInRoom;
  V2GetItemTypesBIN = D2GetItemTypesBIN;
  V2SaveGame = D2SaveGame;
  V2LinkPortal = D2LinkPortal;
  V2Game235C0 = D2Game235C0;
  //V2OpenNPCMenu = D2OpenNPCMenu;
  //////////////// REDIRECT ON CUSTOM FUNCTIONS ////////////////

  if (version_D2Client == V114d) {
    D2GetClientPlayer = D2GetClientPlayer_111;
    D2GetClient = (TD2GetClient)D2GetClient_111;
    D2LoadImage = (TD2LoadImage)D2LoadImage_114;
    D2FreeImage = (TD2FreeImage)D2FreeImage_111;
    D2isLODGame = D2isLODGame_111;
    D2GetMouseX = D2GetMouseX_111;
    D2GetMouseY = D2GetMouseY_111;
    D2SendToServer3 = (TD2SendToServer3)D2SendToServer3_114;
    D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)D2SetSkillBaseLevelOnClient_114;
    D2SendPacket = (TD2SendPacket)D2SendPacket_114;
    D2GetGameByClientID = (TD2GetGameByClientID)D2GetGameByClientID_1XX;
    D2SpawnMonster = (TD2SpawnMonster)D2SpawnMonster_114;
    D2CompileCubeInput = (TD2CompileCubeInput)D2CompileCubeInput_114;
    D2CleanStatMouseUp = (TD2CleanStatMouseUp)D2CleanStatMouseUp_114;
    D2LinkPortal = (TD2LinkPortal)D2LinkPortal_114;
    D2Game235C0 = (TD2Game235C0)D2Game235C0_114;
    D2PrintStat = (TD2PrintStat)D2PrintStat_114;
    D2SaveGame = (TD2SaveGame)D2SaveGame_1XX;
    D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)D2VerifIfNotCarry1_111;

    StatMouse1 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C004, 11C2F4, 11C040, 11C3DC, 11D224, A0650);
    StatMouse2 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C008, 11C2F8, 11C044, 11C3E0, 11D228, A0654);
    StatMouse3 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C020, 11C310, 11C05C, 11C3F8, 11D240, A0658);
    StatMouse4 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C024, 11C314, 11C060, 11C3FC, 11D244, A065C);
    }
  else if (version_D2Client >= V111) {
    D2SendMsgToAll = (TD2SendMsgToAll)D2SendMsgToAll_111;
    D2SetColorPopup = (TD2SetColorPopup)D2SetColorPopup_111;
    D2LoadImage = (TD2LoadImage)D2LoadImage_111;
    D2FreeImage = (TD2FreeImage)D2FreeImage_111;
    D2PlaySound = (TD2PlaySound)D2PlaySound_111;
    D2GetClient = (TD2GetClient)D2GetClient_111;
    D2SendToServer3 = (TD2SendToServer3)D2SendToServer3_111;
    D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)D2SetSkillBaseLevelOnClient_111;
    D2GetCharStatsBIN = (TD2GetCharStatsBIN)D2GetCharStatsBIN_111;
    D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)D2GetItemStatCostBIN_111;
    D2PrintStat = (TD2PrintStat)D2PrintStat_111;
    D2SendPacket = (TD2SendPacket)D2SendPacket_111;
    D2LoadInventory = (TD2LoadInventory)D2LoadInventory_111;
    D2CompileCubeInput = (TD2CompileCubeInput)D2CompileCubeInput_111;
    D2CompileCubeOutput = (TD2CompileCubeOutput)D2CompileCubeOutput_111;
    D2BroadcastFunction = (TD2BroadcastFunction)D2BroadcastFunction_111;
    D2SpawnMonster = version_D2Game >= V111b ? (TD2SpawnMonster)D2SpawnMonster_111b : (TD2SpawnMonster)D2SpawnMonster_111;
    D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)D2VerifIfNotCarry1_111;
    D2GameGetObject = (TD2GameGetObject)D2GameGetObject_111;
    D2GetItemTypesBIN = (TD2GetItemTypesBIN)D2GetItemTypesBIN_111;
    D2TestPositionInRoom = (TD2TestPositionInRoom)D2TestPositionInRoom_111;
    //D2OpenNPCMenu = (TD2OpenNPCMenu) D2OpenNPCMenu_111;
    D2isLODGame = D2isLODGame_111;
    D2GetDifficultyLevel = D2GetDifficultyLevel_111;
    D2GetMouseX = D2GetMouseX_111;
    D2GetMouseY = D2GetMouseY_111;
    D2GetClientPlayer = D2GetClientPlayer_111;
    D2GetRealItem = D2GetRealItem_111;
    D2CleanStatMouseUp = D2CleanStatMouseUp_111;
    StatMouse1 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C004, 11C2F4, 11C040, 11C3DC, 11D224, A0650);
    StatMouse2 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C008, 11C2F8, 11C044, 11C3E0, 11D228, A0654);
    StatMouse3 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C020, 11C310, 11C05C, 11C3F8, 11D240, A0658);
    StatMouse4 = (DWORD*)R8(D2Client, 0000, 0000, 0000, 11C024, 11C314, 11C060, 11C3FC, 11D244, A065C);
    }
  else {
    D2SendToServer = (TD2SendToServer)D2SendToServer_1XX;
    D2GetGameByClientID = (TD2GetGameByClientID)D2GetGameByClientID_1XX;
    D2SaveGame = (TD2SaveGame)D2SaveGame_1XX;
    }

  if (version_D2Common <= V109d)
    {
    //D2SetPlayerStat =				(TD2SetPlayerStat) D2SetPlayerStat_9;
    D2AddPlayerStat = (TD2AddPlayerStat)D2AddPlayerStat_9;
    D2GetPlayerStat = (TD2GetPlayerStat)D2GetPlayerStat_9;
    //D2GetPlayerStat20 =				(TD2GetPlayerStat20) D2GetPlayerStat20_9;
    D2GetPlayerBaseStat = (TD2GetPlayerBaseStat)D2GetPlayerBaseStat_9;
    D2SetSkillBaseLevel = (TD2SetSkillBaseLevel)D2SetSkillBaseLevel_9;
    D2GetCharStatsBIN = (TD2GetCharStatsBIN)D2GetCharStatsBIN_9;
    D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)D2GetItemStatCostBIN_9;
    D2GetItemTypesBIN = (TD2GetItemTypesBIN)D2GetItemTypesBIN_9;
    }

  if (version_D2Client <= V109d)
    D2PrintStat = (TD2PrintStat)D2PrintStat_9;

  if (version_D2Game <= V109d)
    D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)D2SetSkillBaseLevelOnClient_9;


  //////////////// STRUCTURE MANAGEMENT ////////////////

//	shifting.ptPYPlayerData = V7(D2Common,118,118,F4,F4,F4,F4,F4);
  shifting.ptPYPlayerData = *(DWORD*)((DWORD)D2InitPlayerData + V8(D2Common, 5D, 5D, 5D, 49, 49, 49, 49, 49, 48));
  shifting.ptSpecificData = V8(D2Common, 70, 70, 14, 14, 14, 14, 14, 14, 14);
  shifting.ptGame = V8(D2Common, A4, A4, 80, 80, 80, 80, 80, 80, 80);
  shifting.ptClientGame = V8(D2Common, 170, 194, 1A8, 1A8, 1A8, 1A8, 1A8, 1A8, 1A8);
  shifting.ptInventory = V8(D2Common, 84, 84, 60, 60, 60, 60, 60, 60, 60);
  shifting.ptSkills = V8(D2Common, CC, CC, A8, A8, A8, A8, A8, A8, A8);
  shifting.ptImage = V8(D2Common, 04, 04, 04, 08, 08, 3C, 34, 34, 34);
  shifting.ptFrame = V8(D2Common, 08, 08, 08, 44, 44, 40, 00, 00, 00);
  }

/*================================= END OF FILE =================================*/