/*================================================
	File created by Yohann NICOLAS.

    This file implements some common and useful
    function related to some Diablo II mechanisms.

================================================*/

#include "common.h"
#include "d2functions.h"
#include "error.h"


#define D2S(F, I, R, N, P)	T##N N;
#define D2F(F, I, R, N, P)	T##N N;
#define E2S(F, A, R, N, P)	T##N N;
#define E2F(F, A, R, N, P)	T##N N;
#define E2C(F, A, T, N)		T* pt##N;
#define F7(X, Z, A,B,C,D,E,F,G, R, N, P) T##N N;
#define A7(X, Z, A,B,C,D,E,F,G, R, N, P) T##N N;
#define C7(Z, A,B,C,D,E,F,G, T, N)       T* pt##N;

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
#undef F7
#undef A7
#undef C7
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

#define D2S(F, I, R, N, P)	typedef R (STDCALL  *T##N) P; T##N N;
D2S(D2Common,10581,	CharStatsBIN*,		D2Common10581, (DWORD charID));//ONLY in 1.09
D2S(D2Common,10598,	ItemStatCostBIN*,	D2Common10598, (DWORD itemStatCostID));//ONLY in 1.09
D2S(D2Common,10673,	ItemTypesBIN*,		D2Common10673, (DWORD itemTypesID));//ONLY in 1.09
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
WORD (*getDescStrPos) (DWORD statID);
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

//DWORD* ptNbStatDesc
//DWORD* ptStatDescTable;
//TD2OpenNPCMenu				 V2OpenNPCMenu;

DWORD getStatDescIDFrom (DWORD statID)//FOR 1.09
{
	DWORD* desc = ptStatDescTable;
	DWORD curDesc = 0;
	while (curDesc < *ptNbStatDesc)
	{
		if (*desc == statID)
			return curDesc;
		desc+=4;
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

FCT_ASM ( D2AddPlayerStat_9 )//(Unit* ptChar, DWORD statID, DWORD amount, DWORD index)
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	CALL V2AddPlayerStat
	RETN 0x10
}}

FCT_ASM ( D2GetPlayerStat_9 )//(Unit* ptChar, DWORD statID, DWORD index)
	PUSH DWORD PTR SS:[ESP+0x8]
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL V2GetPlayerStat
	RETN 0x0C
}}

//FCT_ASM ( D2GetPlayerStat20_9 )//(Unit* ptChar, DWORD statID, DWORD index)
//	PUSH DWORD PTR SS:[ESP+0x8]
//	PUSH DWORD PTR SS:[ESP+0x8]
//	CALL V2GetPlayerStat20
//	RETN 0x0C
//}}

FCT_ASM ( D2GetPlayerBaseStat_9 )//(Unit* ptChar, DWORD statID, DWORD index)
	PUSH DWORD PTR SS:[ESP+0x8]
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL V2GetPlayerBaseStat
	RETN 0x0C
}}

FCT_ASM ( D2SetSkillBaseLevel_9 )//(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	CALL V2SetSkillBaseLevel
	RETN 0x18
}}

FCT_ASM ( D2SetSkillBaseLevelOnClient_9 )//(void* ptClient, Unit* ptChar, DWORD skillID, DWORD newValue, DWORD zero)
	POP EAX
	MOV ECX,EDX
	POP EDX
	PUSH EAX
	JMP V2SetSkillBaseLevelOnClient
}}

FCT_ASM ( D2GetCharStatsBIN_9 )
	PUSH ECX
	CALL D2Common10581
	RETN
}}

FCT_ASM ( D2GetItemStatCostBIN_9 )
	PUSH ECX
	CALL D2Common10598
	RETN
}}

FCT_ASM ( D2GetItemTypesBIN_9 )
	PUSH ECX
	CALL D2Common10673
	RETN
}}


DWORD FASTCALL D2PrintStat_9 (Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText)
{
	DWORD curDesc = getStatDescIDFrom(statID);
	if (curDesc < *ptNbStatDesc)
		return V2PrintStat(ptItem, (Stats*)curDesc, statValue, 0, 0, lpText);
	return 0;
}


void setImage(sDrawImageInfo* data, void* image){((void**)data)[shifting.ptImage/4]=image;}//0x4 0x8 0x3C
void setFrame(sDrawImageInfo* data, DWORD frame){((DWORD*)data)[shifting.ptFrame/4]=frame;}//0x8 0x44 0x40

//void setImage_111(sDrawImageInfo* data, void* image){data->image=image;}//0x8 0x44
//void setImage_1XX(sDrawImageInfo* data, void* image){((void**)data)[1]=image;}//0x4 0x8
//void setFrame_111(sDrawImageInfo* data, DWORD frame){data->frame=frame;}
//void setFrame_1XX(sDrawImageInfo* data, DWORD frame){((DWORD*)data)[2]=frame;}


WORD getDescStrPos_9 (DWORD statID)
{
	DWORD* desc = &ptStatDescTable[getStatDescIDFrom(statID)*4];
	return (WORD)*(desc+2);
}
WORD getDescStrPos_10 (DWORD statID)
{
	ItemStatCostBIN* itemStatCost = D2GetItemStatCostBIN(statID);
	return itemStatCost->descstrpos;
}


const char* S_compileTxtFile = "compileTxtFile";
const char* S_errorReadTxtFile = "pbData";
__declspec(naked) void* STDCALL compileTxtFile_9(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{_asm{
	SUB ESP,0x210
//	MOV EAX,DWORD PTR DS:[1BEA28C]
	PUSH EBX
	PUSH EBP
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[ESP+0x228]
	MOV DWORD PTR SS:[ESP+0x10],0

	MOV EDI,wsprintf
	PUSH ESI
	LEA EAX,DWORD PTR SS:[ESP+0x20]
	PUSH EAX
	CALL EDI
	ADD ESP,8

	LEA EDX,DWORD PTR SS:[ESP+0x10]
	PUSH 0
	PUSH S_compileTxtFile
	PUSH EDX
	MOV ECX,DWORD PTR SS:[ESP+0x230]
	LEA EDX,DWORD PTR SS:[ESP+0x28]
	CALL D2ReadFile
	TEST EAX,EAX
	JNZ continue_compileTxtFile
	PUSH 0
	PUSH S_compileTxtFile
	PUSH S_errorReadTxtFile
	CALL D2FogAssertOld
	PUSH -1
	CALL exit
continue_compileTxtFile:
	MOV ECX,D2CompileTxtFile
	ADD ECX,0x305
	JMP ECX
}}

__declspec(naked) void* STDCALL compileTxtFile_10(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{_asm{
	SUB ESP,0x210
//	MOV EAX,DWORD PTR DS:[1BEA28C]
	PUSH EBX
	PUSH EBP
	MOV EBP,DWORD PTR SS:[ESP+0x220]
	PUSH ESI
	PUSH EDI
	MOV DWORD PTR SS:[ESP+0x10],0

	MOV EBX,wsprintf
	PUSH EBP
	LEA EAX,DWORD PTR SS:[ESP+0x20]
	PUSH EAX
	CALL EBX
	ADD ESP,8

	LEA EDX,DWORD PTR SS:[ESP+0x10]
	PUSH 0
	PUSH S_compileTxtFile
	PUSH EDX
	MOV ECX,DWORD PTR SS:[ESP+0x230]
	LEA EDX,DWORD PTR SS:[ESP+0x28]
	CALL D2ReadFile
	TEST EAX,EAX
	JNZ continue_compileTxtFile
	PUSH 0
	PUSH S_compileTxtFile
	PUSH S_errorReadTxtFile
	CALL D2FogAssertOld
	PUSH -1
	CALL exit
continue_compileTxtFile:
	MOV ECX,D2CompileTxtFile
	ADD ECX,0x2ED
	JMP ECX
}}

__declspec(naked) void* STDCALL compileTxtFile_111(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{_asm{
	SUB ESP,0x20C
//	MOV EAX,DWORD PTR DS:[6FDF1464]
	PUSH EBX
	PUSH EBP
	PUSH ESI
	PUSH EDI
	MOV DWORD PTR SS:[ESP+0x10],0
	MOV EBX,DWORD PTR SS:[ESP+0x224]

	PUSH EBX
	LEA EAX,DWORD PTR SS:[ESP+0x1C]
	PUSH EAX
	CALL DWORD PTR SS:[wsprintf]
	MOV EDX,DWORD PTR SS:[ESP+0x228]
	ADD ESP,8
	LEA EDX,DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	PUSH EAX
	LEA EAX,DWORD PTR SS:[ESP+0x20]
	CALL D2ReadFile
	TEST EAX,EAX
	JNZ continue_compileTxtFile
	PUSH __LINE__
	CALL D2GetInstructionPointer
	PUSH EAX
	PUSH S_errorReadTxtFile
	CALL D2FogAssert
	ADD ESP,0xC
	PUSH -1
	CALL exit
continue_compileTxtFile:
	MOV ECX,D2CompileTxtFile
	ADD ECX,0x1EC
	JMP ECX
}}


DWORD FASTCALL	D2isLODGame_111(){return IsLodGame;}
BYTE  FASTCALL	D2GetDifficultyLevel_111(){return DifficultyLevel;}
DWORD STDCALL	D2GetMouseX_111(){return MouseX;}
DWORD STDCALL	D2GetMouseY_111(){return MouseY;}
Unit* STDCALL	D2GetClientPlayer_111(){return ptClientChar;}

DWORD *StatMouse1, *StatMouse2, *StatMouse3, *StatMouse4;
void FASTCALL D2CleanStatMouseUp_111(){*StatMouse1=*StatMouse2=*StatMouse3=*StatMouse4=0;}

Unit* STDCALL	D2GetRealItem_111(Unit* ptItem){return ptItem;}
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


FCT_ASM ( D2SendMsgToAll_111 )
	PUSH ESI
	MOV ESI,ECX
	CALL V2SendMsgToAll
	POP ESI
	RETN
}}

FCT_ASM ( D2SetColorPopup_111 )
	PUSH EDI
	PUSH EDX
	MOV EDI,ECX
	CALL V2SetColorPopup
	POP EDI
	RETN
}}

FCT_ASM ( D2LoadImage_111 )
	PUSH EDX
	MOV EAX,ECX
	CALL V2LoadImage
	RETN
}}

const char* D2FreeImage_FILE = __FILE__;
FCT_ASM ( D2FreeImage_111 )
	PUSH ESI
	MOV ESI,ECX
	PUSH ESI
	CALL D2CMP10014
	TEST ESI,ESI
	JE END_D2Free
	PUSH 0
	PUSH __LINE__
	MOV EDX,D2FreeImage_FILE                ;  ASCII "C:\projects\D2\head\Diablo2\Source\D2Client\CORE\ARCHIVE.CPP"
	MOV ECX,ESI
	CALL D2FogMemDeAlloc
END_D2Free:
	POP ESI
	RETN
}}


FCT_ASM ( D2PlaySound_111 )
	PUSH EBX
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	MOV EBX,ECX
	CALL V2PlaySound
	POP EBX
	RETN 0xC
}}

FCT_ASM ( D2GetClient_111 )
	PUSH ECX
	CALL D2GetPlayerData
	MOV EAX,DWORD PTR DS:[EAX+0x9C]
	RETN 4
}}


FCT_ASM ( D2SetSkillBaseLevelOnClient_111 )
	PUSH EBX
	PUSH ESI
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH DWORD PTR SS:[ESP+0x14]
	MOV EBX, DWORD PTR SS:[ESP+0x14]
	MOV EAX,ECX
	MOV ESI,EDX
	CALL V2SetSkillBaseLevelOnClient
	POP ESI
	POP EBX
	RETN 0xC
}}

FCT_ASM ( D2GetCharStatsBIN_111 )
	MOV EAX,ECX
	JMP V2GetCharStatsBIN
}}

FCT_ASM ( D2GetItemStatCostBIN_111 )
	MOV EAX,ECX
	JMP V2GetItemStatCostBIN
}}

FCT_ASM ( D2SendToServer3_111 )
	PUSH EBX
	PUSH ECX
	MOV BYTE PTR SS:[ESP],CL
	MOV WORD PTR SS:[ESP+1],DX
	MOV EBX,3
	LEA EDX,DWORD PTR SS:[ESP]
	PUSH EDX
	CALL D2SendToServerXX
	POP ECX
	POP EBX
	RETN
}}

FCT_ASM ( D2PrintStat_111 )
	PUSH ESI
	MOV ESI,DWORD PTR SS:[ESP+0x14]
	MOV EAX,DWORD PTR SS:[ESP+0x08]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	PUSH ECX
	CALL V2PrintStat
	POP ESI
	RETN 0x10
}}

FCT_ASM ( D2SendPacket_111 )
	POP EAX
	PUSH EDX
	PUSH EAX
	MOV EAX,ECX
	JMP V2SendPacket
}}

FCT_ASM ( D2LoadInventory_111 )
	MOV EAX,DWORD PTR SS:[ESP+4]
	MOV DWORD PTR SS:[ESP+4],EDX
	JMP V2LoadInventory
}}

FCT_ASM ( D2CompileCubeInput_111 )
	PUSH EBX
	MOV EBX,ECX
	MOV EAX,EDX
	CALL V2CompileCubeInput
	POP EBX
	RETN 8
}}

FCT_ASM ( D2CompileCubeOutput_111 )
	PUSH EBX
	MOV EBX,ECX
	PUSH EDX
	CALL V2CompileCubeOutput
	POP EBX
	RETN 8
}}

FCT_ASM ( D2BroadcastFunction_111 )
	PUSH EDI
	PUSH EBX
	MOV EAX,ECX
	MOV EDI,EDX
	MOV EBX,DWORD PTR SS:[ESP+0xC]
	CALL V2BroadcastFunction
	POP EBX
	POP EDI
	RETN 4
}}

FCT_ASM ( D2SpawnMonster_111 )
	PUSH DWORD PTR SS:[ESP+0x18]
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH ECX
	MOV ECX,DWORD PTR SS:[ESP+0x18]
	MOV EAX,DWORD PTR SS:[ESP+0x28]
	CALL V2SpawnMonster
	RETN 0x18
}}

FCT_ASM ( D2SpawnMonster_111b )
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	PUSH ECX
	MOV EAX,DWORD PTR SS:[ESP+0x18]
	MOV EDX,DWORD PTR SS:[ESP+0x2C]
	MOV ECX,DWORD PTR SS:[ESP+0x28]//superuniqueID
	CALL V2SpawnMonster
	RETN 0x18
}}

FCT_ASM ( D2VerifIfNotCarry1_111 )
	PUSH EBX
	PUSH ECX
	MOV EBX,EDX
	MOV EAX,DWORD PTR SS:[ESP+0xC]
	CALL V2VerifIfNotCarry1
	POP EBX
	RETN 4
}}

FCT_ASM ( D2GameGetObject_111 )
	MOV EAX,EDX
	MOV EDX,DWORD PTR SS:[ESP+4]
	CALL V2GameGetObject
	RETN 4
}}


FCT_ASM ( D2TestPositionInRoom_111 )
	PUSH EDI
	PUSH EBX
	MOV EDI,DWORD PTR SS:[ESP+0xC]
	MOV EAX,ECX
	MOV EBX,EDX
	CALL V2TestPositionInRoom
	POP EBX
	POP EDI
	RETN 4
}}

FCT_ASM ( D2GetItemTypesBIN_111)
	MOV EAX,ECX
	JMP V2GetItemTypesBIN
}}

//FCT_ASM ( D2OpenNPCMenu_111)
//	MOV ESI,ECX
//	JMP V2OpenNPCMenu
//}}
FCT_ASM ( D2SendToServer_1XX )
	PUSH DWORD PTR SS:[ESP+0x4]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH 0
	CALL V2SendToServer
	RETN 0xC
}}


FCT_ASM ( D2GetGameByClientID_1XX )
	POP EAX
	POP ECX
	PUSH EAX
	JMP V2GetGameByClientID
}}

FCT_ASM ( D2SaveGame_1XX )
	POP EAX
	POP ECX
	PUSH EAX
	JMP V2SaveGame
}}

#define SETFCTADDR(F, I, N) setFctAddr((DWORD*)&N, (HMODULE)offset_##F, (LPCSTR)I)
void setFctAddr(DWORD* addr, HMODULE module, LPCSTR index)
{
	if (index)
	{
		*addr = (DWORD)GetProcAddress(module,index);
		if (!*addr)
		{
			log_msg("Bad index fct %d for %08X\n",index,module);
		}
	} else
		*addr = NULL;
}

bool initD2functions()
{
//	#define D2S(F, I, R, N, P)	N = (F##I)GetProcAddress((HMODULE)offset_##F, (LPCSTR)I);
//	#define D2F(F, I, R, N, P)	N = (F##I)GetProcAddress((HMODULE)offset_##F, (LPCSTR)I);
	#define D2S(F, I, R, N, P)	SETFCTADDR(F, I, N);
	#define D2F(F, I, R, N, P)	SETFCTADDR(F, I, N);
	#define E2S(F, A, R, N, P)	N = (T##N)(offset_##F + 0x##A);
	#define E2F(F, A, R, N, P)	N = (T##N)(offset_##F + 0x##A);
	#define E2C(F, A, T, N)		pt##N = (T*)(offset_##F + 0x##A);
	#define F7(X, Z, A,B,C,D,E,F,G, R, N, P) setFctAddr((DWORD*)&N, (HMODULE)offset_##Z, (LPCSTR)((version_##Z == V113? G : (version_##Z == V112? F : version_##Z == V111b? E : (version_##Z == V111? D : (version_##Z == V110? C : (version_##Z == V109d? B : A)))))));
	#define A7(X, Z, A,B,C,D,E,F,G, R, N, P) N = (T##N)R7(Z,A,B,C,D,E,F,G);
	#define C7(Z, A,B,C,D,E,F,G, T, N)       pt##N = (T*)R7(Z,A,B,C,D,E,F,G);

	#include "../Commons/D2Funcs.h"
	SgptDataTables = *(DataTables**) R7(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C);
	if (version_D2Common < V110)
	{
		D2S(D2Common,10581,	CharStatsBIN*,		D2Common10581, (DWORD charID));//ONLY in 1.09
		D2S(D2Common,10598,	ItemStatCostBIN*,	D2Common10598, (DWORD itemStatCostID));//ONLY in 1.09
		D2S(D2Common,10673,	ItemTypesBIN*,		D2Common10673, (DWORD itemTypesID));//ONLY in 1.09
	}
	#undef F7
	#undef A7
	#undef C7
	#undef D2S
	#undef D2F
	#undef E2S
	#undef E2F
	#undef E2C


	//////////////// MISC FCT ////////////////
	//setImage = version_D2Common >= V111 ? setImage_111 : setImage_1XX;
	//setFrame = version_D2Common >= V111 ? setFrame_111 : setFrame_1XX;
	getDescStrPos = version_D2Common >= V110  ? getDescStrPos_10 : getDescStrPos_9;
	compileTxtFile = version_D2Common >= V111 ? compileTxtFile_111 : version_D2Common == V110 ? compileTxtFile_10 : compileTxtFile_9;


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
	//V2OpenNPCMenu = D2OpenNPCMenu;
	//////////////// REDIRECT ON CUSTOM FUNCTIONS ////////////////

	if ( version_D2Client >= V111 )
	{
		D2SendMsgToAll = (TD2SendMsgToAll) D2SendMsgToAll_111;
		D2SetColorPopup = (TD2SetColorPopup) D2SetColorPopup_111;
		D2LoadImage = (TD2LoadImage) D2LoadImage_111;
		D2FreeImage = (TD2FreeImage) D2FreeImage_111;
		D2PlaySound = (TD2PlaySound) D2PlaySound_111;
		D2GetClient = (TD2GetClient) D2GetClient_111;
		D2SendToServer3 = (TD2SendToServer3) D2SendToServer3_111;
		D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient) D2SetSkillBaseLevelOnClient_111;
		D2GetCharStatsBIN = (TD2GetCharStatsBIN) D2GetCharStatsBIN_111;
		D2GetItemStatCostBIN = (TD2GetItemStatCostBIN) D2GetItemStatCostBIN_111;
		D2PrintStat = (TD2PrintStat) D2PrintStat_111;
		D2SendPacket = (TD2SendPacket) D2SendPacket_111;
		D2LoadInventory = (TD2LoadInventory) D2LoadInventory_111;
		D2CompileCubeInput = (TD2CompileCubeInput) D2CompileCubeInput_111;
		D2CompileCubeOutput = (TD2CompileCubeOutput) D2CompileCubeOutput_111;
		D2BroadcastFunction = (TD2BroadcastFunction) D2BroadcastFunction_111;
		D2SpawnMonster = version_D2Game >= V111b ? (TD2SpawnMonster)D2SpawnMonster_111b : (TD2SpawnMonster)D2SpawnMonster_111;
		D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1) D2VerifIfNotCarry1_111;
		D2GameGetObject = (TD2GameGetObject) D2GameGetObject_111;
		D2GetItemTypesBIN = (TD2GetItemTypesBIN) D2GetItemTypesBIN_111;
		D2TestPositionInRoom = (TD2TestPositionInRoom) D2TestPositionInRoom_111;
		//D2OpenNPCMenu = (TD2OpenNPCMenu) D2OpenNPCMenu_111;
		D2isLODGame = D2isLODGame_111;
		D2GetDifficultyLevel = D2GetDifficultyLevel_111;
		D2GetMouseX = D2GetMouseX_111;
		D2GetMouseY = D2GetMouseY_111;
		D2GetClientPlayer = D2GetClientPlayer_111;
		D2GetRealItem = D2GetRealItem_111;
		D2CleanStatMouseUp = D2CleanStatMouseUp_111;
		StatMouse1 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C004, 11C2F4, 11C040, 11C3DC);
		StatMouse2 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C008, 11C2F8, 11C044, 11C3E0);
		StatMouse3 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C020, 11C310, 11C05C, 11C3F8);
		StatMouse4 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C024, 11C314, 11C060, 11C3FC);
	} else {
		D2SendToServer = (TD2SendToServer) D2SendToServer_1XX;
		D2GetGameByClientID = (TD2GetGameByClientID) D2GetGameByClientID_1XX;
		D2SaveGame = (TD2SaveGame) D2SaveGame_1XX;
	}

	if ( version_D2Common <= V109d )
	{
		//D2SetPlayerStat =				(TD2SetPlayerStat) D2SetPlayerStat_9;
		D2AddPlayerStat =				(TD2AddPlayerStat) D2AddPlayerStat_9;
		D2GetPlayerStat =				(TD2GetPlayerStat) D2GetPlayerStat_9;
		//D2GetPlayerStat20 =				(TD2GetPlayerStat20) D2GetPlayerStat20_9;
		D2GetPlayerBaseStat =			(TD2GetPlayerBaseStat) D2GetPlayerBaseStat_9;
		D2SetSkillBaseLevel =			(TD2SetSkillBaseLevel) D2SetSkillBaseLevel_9;
		D2GetCharStatsBIN =				(TD2GetCharStatsBIN) D2GetCharStatsBIN_9;
		D2GetItemStatCostBIN =			(TD2GetItemStatCostBIN) D2GetItemStatCostBIN_9;
		D2GetItemTypesBIN =				(TD2GetItemTypesBIN) D2GetItemTypesBIN_9;
	}

	if ( version_D2Client <= V109d )
		D2PrintStat =					(TD2PrintStat) D2PrintStat_9;

	if ( version_D2Game <= V109d )
		D2SetSkillBaseLevelOnClient =	(TD2SetSkillBaseLevelOnClient) D2SetSkillBaseLevelOnClient_9;


	//////////////// STRUCTURE MANAGEMENT ////////////////

//	shifting.ptPYPlayerData = V7(D2Common,118,118,F4,F4,F4,F4,F4);
	shifting.ptPYPlayerData = *(DWORD*)((DWORD)D2InitPlayerData + V7(D2Common,5D,5D,5D,49,49,49,49));
	shifting.ptSpecificData = V7(D2Common,70,70,14,14,14,14,14);
	shifting.ptGame = V7(D2Common,A4,A4,80,80,80,80,80);
	shifting.ptClientGame = V7(D2Common,170,194,1A8,1A8,1A8,1A8,1A8);
	shifting.ptInventory = V7(D2Common,84,84,60,60,60,60,60);
	shifting.ptSkills = V7(D2Common,CC,CC,A8,A8,A8,A8,A8);
	shifting.ptImage = V7(D2Common,04,04,04,08,08,3C,34);
	shifting.ptFrame = V7(D2Common,08,08,08,44,44,40,00);
	return true;
}

/*================================= END OF FILE =================================*/