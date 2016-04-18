/*=================================================================
	File created by Yohann NICOLAS.

	Unassign Stats Point for futher re-assignment.

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"

#include "plugYFiles.h"			// Install_PlugYImagesFiles()
#include "interface_Stats.h"	// Install_InterfaceStats()
#include "updateServer.h"
#include <stdio.h>

bool active_StatsPoints=0;
DWORD keyUsedForUnassignStatPoint=VK_CONTROL;
bool active_StatsShiftClickLimit=1;
DWORD limitValueToShiftClick=5;

void UnassignStr(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Strengh\n");

	int currentStr, removePtsNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);

	currentStr = D2GetPlayerBaseStat( ptChar, STATS_STRENGTH, 0 );
	if (currentStr <= charStats->baseSTR) return;
	removePtsNb = currentStr - charStats->baseSTR >= nb ? nb : currentStr - charStats->baseSTR;
	if (currentStr - removePtsNb < 1) removePtsNb = currentStr - 1;

	log_msg("Start Unassign Strengh (cur %d, base %d, rem %d)\n",currentStr,charStats->baseSTR,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_STRENGTH,	-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignDex(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Dexterity\n");

	int currentDex, removePtsNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	
	currentDex = D2GetPlayerBaseStat( ptChar, STATS_DEXTERITY, 0 );
	if (currentDex <= charStats->baseDEX) return;
	removePtsNb = currentDex - charStats->baseDEX >= nb ? nb : currentDex - charStats->baseDEX;
	if (currentDex - removePtsNb < 1) removePtsNb = currentDex - 1;

	log_msg("Start Unassign Dexterity (cur %d, base %d, rem %d)\n",currentDex,charStats->baseDEX,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_DEXTERITY,	-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignVit(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Vitality\n");

	int currentVit, removePtsNb, removeVitNb, removeStaNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	
	currentVit = D2GetPlayerBaseStat( ptChar, STATS_VITALITY, 0 );
	if (currentVit <= charStats->baseVIT) return;
	removePtsNb = currentVit - charStats->baseVIT >= nb ? nb : currentVit - charStats->baseVIT;
	if (currentVit - removePtsNb < 1) removePtsNb = currentVit - 1;
	removeVitNb = removePtsNb * (charStats->lifePerVitality << 6);
	removeStaNb = removePtsNb * (charStats->staminaPerVitality << 6);
	
	log_msg("Start Unassign Vitality (cur %d, base %d, rem %d)\n",currentVit,charStats->baseVIT,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_VITALITY,	-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_MAXHP,		-removeVitNb ,0 );
	D2AddPlayerStat( ptChar, STATS_MAXSTAMINA,	-removeStaNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignEne(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Energy\n");

	int currentEne, removePtsNb, removeManNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	
	currentEne = D2GetPlayerBaseStat( ptChar, STATS_ENERGY, 0);
	if (currentEne <= charStats->baseENE) return;
	removePtsNb = currentEne - charStats->baseENE >= nb ? nb : currentEne - charStats->baseENE;
	if (currentEne - removePtsNb < 1) removePtsNb = currentEne - 1;
	removeManNb = removePtsNb * (charStats->manaPerMagic << 6);
	
	log_msg("Start Unassign Energy (cur %d, base %d, rem %d)\n",currentEne,charStats->baseENE,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_ENERGY,		-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_MAXMANA,		-removeManNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignStrPoint(Unit* ptChar)
{
	UnassignStr(ptChar, 1);
}

void UnassignStrPoints(Unit* ptChar)
{
	UnassignStr(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}

void UnassignDexPoint(Unit* ptChar)
{
	UnassignDex(ptChar, 1);
}

void UnassignDexPoints(Unit* ptChar)
{
	UnassignDex(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}

void UnassignVitPoint(Unit* ptChar)
{
	UnassignVit(ptChar, 1);
}

void UnassignVitPoints(Unit* ptChar)
{
	UnassignVit(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}

void UnassignEnePoint(Unit* ptChar)
{
	UnassignEne(ptChar, 1);
}

void UnassignEnePoints(Unit* ptChar)
{
	UnassignEne(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}


//////////////////////////////////


void STDCALL printDisabledStatsBtn(WORD statID, sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6)
{
	if ( onRealm || !D2isLODGame())
	{
		D2PrintImage(data,x,y,p4,p5,p6);
		return;
	}
	Unit* ptChar = D2GetClientPlayer();

	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	int minValue=1;
	switch (statID)
	{
		case STATS_STRENGTH: minValue = charStats->baseSTR; break;
		case STATS_DEXTERITY: minValue = charStats->baseDEX; break;
		case STATS_VITALITY: minValue = charStats->baseVIT; break;
		case STATS_ENERGY: minValue = charStats->baseENE; break;
	}
	int statValue = D2GetPlayerBaseStat(ptChar, statID, 0);

	if (isOnRect(D2GetMouseX(),D2GetMouseY(),x+5,y+5,32,32))
	{
		WCHAR text[100];
		if (active_StatsShiftClickLimit)
			swprintf(text, getTranslatedString(STR_STATS_UNASSIGN_WITH_LIMIT),limitValueToShiftClick);
		else
			swprintf(text, getTranslatedString(STR_STATS_UNASSIGN_WITHOUT_LIMIT));
		wcscat(text,L"\n");
		swprintf(text+wcslen(text), getTranslatedString(STR_STATS_BASE_MIN), statValue, minValue);
		D2SetFont(1);
		D2PrintPopup(text, x+18, y-32, WHITE, 1);
	}

	if ( GetKeyState(keyUsedForUnassignStatPoint) >= 0) {
		if ( D2GetPlayerBaseStat(ptChar, 4, 0) <= 0)
			setFrame(data, 2);
	} else {
		setImage(data, unassignStatsBtnImages);
		if (minValue >= statValue)
			setFrame(data, 2);
	}

	D2PrintImage(data,x,y,p4,p5,p6);
}

FCT_ASM ( caller_printUnassignStatsBtn )
	POP EAX
	XOR ECX,ECX
	MOV CX,WORD PTR DS:[ESI+8]
	PUSH ECX
	PUSH EAX
	JMP printDisabledStatsBtn
}}



BYTE currentMsgID=0;

WORD UnassignStats()
{
	if (onRealm || !D2isLODGame()) return 0;
	return GetKeyState(keyUsedForUnassignStatPoint);
}

FCT_ASM ( caller_UnassignStats_9 )
	PUSH EAX
	CALL UnassignStats
	TEST AX,AX
	POP EAX
	JNL NOT_CTRL

	MOV currentMsgID,0x10
	TEST AX,AX
	JNL NOT_SHIFT
	ADD currentMsgID,4
NOT_SHIFT:
	MOV EAX,1
	MOV ESI,EAX
	RETN

NOT_CTRL:
	MOV currentMsgID,0
	TEST AX,AX
	MOV EAX,1
	RETN
}}


FCT_ASM ( caller_UnassignStats )
	PUSH EAX
	CALL UnassignStats
	TEST AX,AX
	POP EAX
	JNL NOT_CTRL

	MOV currentMsgID,0x10
	TEST AX,AX
	JNL NOT_SHIFT
	ADD currentMsgID,4
NOT_SHIFT:
	MOV ESI,1
	ADD DWORD PTR SS:[ESP],0xB
	RETN

NOT_CTRL:
	MOV currentMsgID,0
	TEST AX,AX
	JNL END_UNASSGNSTATS
	ADD DWORD PTR SS:[ESP],0x7
END_UNASSGNSTATS:
	RETN
}}


FCT_ASM ( caller_setValue_111 )
	ADD CL,currentMsgID
	MOV WORD PTR SS:[ESP+0x19],CX
	RETN
}}

FCT_ASM ( caller_setValue )
	ADD DL,currentMsgID
	JMP D2SendToServer3
}}



DWORD STDCALL pushDown (DWORD num)
{
	Unit* ptChar = D2GetClientPlayer();

	if ( !D2isLODGame() || GetKeyState(keyUsedForUnassignStatPoint) >= 0)//GetAsyncKeyState
	{
		if ( D2GetPlayerBaseStat(ptChar, 4, 0) > 0)
			return 1;
	} else {
		CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
		switch (num)
		{
			case 0: if ((DWORD)charStats->baseSTR < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0))
				return 1; break;
			case 1: if ((DWORD)charStats->baseDEX < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0))
				return 1; break;
			case 2: if ((DWORD)charStats->baseVIT < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0))
				return 1; break;
			case 3: if ((DWORD)charStats->baseENE < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0))
				return 1; break;
		}
	}
	return 0;
}

FCT_ASM ( caller_pushDown_111 )
	PUSH EDX
	PUSH EDX
	CALL pushDown
	POP EDX
	TEST EAX,EAX
	JNZ end_pushDown
	SUB DWORD PTR SS:[ESP],0x22
	RETN
end_pushDown:
	MOV EDI,1
	RETN
}}

FCT_ASM ( caller_pushDown )
	PUSH EDX
	PUSH EDX
	CALL pushDown
	POP EDX
	TEST EAX,EAX
	JNZ end_pushDown
	SUB DWORD PTR SS:[ESP],0x22
	RETN
end_pushDown:
	LEA EAX,DWORD PTR DS:[EDX*8]
	RETN
}}


void Install_StatsPoints()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlugYImagesFiles();
//	Install_InterfaceStats();
	Install_UpdateServer();

	log_msg("Patch D2Client for unassign stat points when specified key is press. (StatsPoints)\n");
//if ( version_D2Client < V113 )
{
	// Always print stat button images.
	mem_seek R7(D2Client, 29B12, 29B02, 30073, 82BBA, 8963A, 6B59A, BD1B5);
	memt_byte( 0x8B, 0xEB );	// JMP SHORT D2Client.6FAD0088
	memt_byte( 0x4C, V7(D2Client, 12, 12, 13, 13, 13, 13, 13) );
	memt_byte( 0x24, 0x90 );	// NOP
	memt_byte( V7(D2Client, 20, 20, 14, 1C, 1C, 1C, 1C), 0x90 );			// NOP (V109d:0x20 , V110:0x14
	//6FAD0073     8B4C24 14      MOV ECX,DWORD PTR SS:[ESP+14]
	//6FB32BBA   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB3963A   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB1B59A   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB6D1B5  |> 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]

	//print our buttons
	mem_seek R7(D2Client, 29B9D, 29B8D, 300FD, 82C54, 896D4, 6B637, BD23E);
	MEMJ_REF4( D2PrintImage, caller_printUnassignStatsBtn);
	//6FB32C53   . E8 82A3F8FF    CALL <JMP.&D2gfx.#10047>
	//6FB396D3   . E8 D238F8FF    CALL <JMP.&D2gfx.#10044>
	//6FB1B636   . E8 431AFAFF    CALL <JMP.&D2gfx.#10024>
	//6FB6D23D   . E8 54FEF4FF    CALL <JMP.&D2gfx.#10041>

	// Always manage push down.
	mem_seek R7(D2Client, 2AA7B, 2AA6B, 3134D, 827D9, 89259, 6B1B9, BCDD9);
	memt_byte( 0x74, 0x90 );	// NOP
	memt_byte( 0x4E, 0x90 );	// NOP
	//6FAD134D     74 4E             JE SHORT D2Client.6FAD139D
	//6FB327D9   . 74 4E          JE SHORT D2Client.6FB32829
	//6FB39259   . 74 4E          JE SHORT D2Client.6FB392A9
	//6FB1B1B9   74 4E            JE SHORT D2Client.6FB1B209
	//6FB6CDD9   . 74 4E          JE SHORT D2Client.6FB6CE29

	if ( version_D2Client >= V111 )
	{
		// On Push down.
		mem_seek R7(D2Client, 2AAE6, 2AAD6, 313B8, 82844, 892C4, 6B224, BCE44);
		memt_byte( 0x6B, 0xE8 );
		MEMT_REF4( 0x01BF0ED2, caller_pushDown_111);
		memt_byte( 0x00, 0x6B );	// IMUL EDX,EDX,0E
		memt_byte( 0x00, 0xD2 );
		memt_byte( 0x00, 0x0E );
		//6FB32844   > 6BD2 0E        IMUL EDX,EDX,0E
		//6FB32847   . BF 01000000    MOV EDI,1
		//6FB392C4   > 6BD2 0E        IMUL EDX,EDX,0E
		//6FB392C7   . BF 01000000    MOV EDI,1
		//6FB1B224   6BD2 0E          IMUL EDX,EDX,0E
		//6FB1B227   BF 01000000      MOV EDI,1
		//6FB6CE44   > 6BD2 0E        IMUL EDX,EDX,0E
		//6FB6CE47   . BF 01000000    MOV EDI,1

	} else {
		// On Push down.
		mem_seek R7(D2Client, 2AAE6, 2AAD6, 313B8, 82844, 892C4, 0000, 0000);
		memt_byte( 0x8D, 0xE8 );	// CALL
		MEMT_REF4( 0x0000D504, caller_pushDown);
		memt_byte( 0x00, 0x90 );	// NOP
		memt_byte( 0x00, 0x90 );	// NOP
		//6FAD13B8   8D04D5 00000000  LEA EAX,DWORD PTR DS:[EDX*8]
	}


	if ( version_D2Client >= V110 )
	{
		// Always manage push up.
		mem_seek R7(D2Client, 0000, 0000, 3152E, 83869, 8A2E9, 6C249, BDE49);
		memt_byte( 0x74, 0x90 );	// NOP
		memt_byte( version_D2Client >= V111 ? 0x65 : 0x68, 0x90 );	// NOP
		//6FAD152E     74 68          JE SHORT D2Client.6FAD1598
		//6FB33869   . 74 65          JE SHORT D2Client.6FB338D0
		//6FB3A2E9   . 74 65          JE SHORT D2Client.6FB3A350
		//6FB1C249   74 65            JE SHORT D2Client.6FB1C2B0
		//6FB6DE49   . 74 65          JE SHORT D2Client.6FB6DEB0

		// Unassign stats point when ctrl is push.
		mem_seek R7(D2Client, 0000, 0000, 315D3, 8391B, 8A39B, 6C2FB, BDEFB);
		memt_byte( 0x66, 0xE8 );	// CALL
		MEMT_REF4( 0x077CC085, caller_UnassignStats);
		//6FAD15D3   . 66:85C0        TEST AX,AX
		//6FAD15D6   . 7C 07          JL SHORT D2Client.6FAD15DF
		//6FB3391B   . 66:85C0        TEST AX,AX
		//6FB3391E   . 7C 07          JL SHORT D2Client.6FB33927
		//6FB3A39B   . 66:85C0        TEST AX,AX
		//6FB3A39E   . 7C 07          JL SHORT D2Client.6FB3A3A7
		//6FB1C2FB   . 66:85C0        TEST AX,AX
		//6FB1C2FE   . 7C 07          JL SHORT D2Client.6FB1C307
		//6FB6DEFB   . 66:85C0        TEST AX,AX
		//6FB6DEFE   . 7C 07          JL SHORT D2Client.6FB6DF07
	} else {
		// Always manage push up.
		mem_seek R7(D2Client, 2AC55, 2AC45, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0x0F, 0x90 );	// NOP
		memt_byte( 0x84, 0x90 );	// NOP
		memt_dword( 0x000000AE, 0x90909090 );	// NOP NOP NOP NOP
		//6FACAC45   . 0F84 AE000000  JE D2Client.6FACACF9

		// Unassign stats point when ctrl is push.
		mem_seek R7(D2Client, 2ACD9, 2ACC9, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0xB8, 0xE8 );	// CALL
		MEMT_REF4( 0x00000001, caller_UnassignStats_9);
		//6FACACC9   . B8 01000000    MOV EAX,1
	}

	// Set the id for the calling function.
	mem_seek R7(D2Client, 2AD02, 2ACF2, 31611, 8395E, 8A3DE, 6C33E, BDF3E);
	if ( version_D2Client >= V111 ) {
		memt_byte( 0x66, 0xE8 );	// CALL
		MEMT_REF4( 0x15244C89, caller_setValue_111);
		//6FB3395E   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX
		//6FB3A3DE   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX
		//6FB1C33E   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX              ; |
		//6FB6DF3E   . 66:894C24 15   MOV WORD PTR SS:[ESP+15],CX              ; |
	} else {
		MEMC_REF4( D2SendToServer3, caller_setValue);
		//6FAD1610   . E8 7BC3FDFF    CALL D2Client.6FAAD990
	}
}	log_msg("\n");

	isInstalled = true;
}

/*********************************************************************************/


FCT_ASM ( caller_LimitShift_111 )
	CMP EDI,limitValueToShiftClick
	JL DontTruncTheValue
	MOV EDI,limitValueToShiftClick
DontTruncTheValue:
	JMP DWORD PTR DS:[GetKeyState]
}}

FCT_ASM ( caller_LimitShift )
	CMP ESI,limitValueToShiftClick
	JL DontTruncTheValue
	MOV ESI,limitValueToShiftClick
DontTruncTheValue:
	JMP DWORD PTR DS:[GetKeyState]
}}

void Install_StatsLimitShiftClick()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for limit the assigment of stat points when shift is used. (LimitShift)\n");

	// Limit the assigment of stat points.
	mem_seek R7(D2Client, 2ACD0, 2ACC0, 315CD, 83915, 8A395, 6C2F5, BDEF5);
	memt_byte( 0xFF, 0x90 );	// NOP
	memt_byte( 0x15, 0xE8 );	// CALL
	MEMD_REF4( GetKeyState, version_D2Client >= V111 ? caller_LimitShift_111 : caller_LimitShift);
	//6FAD15CD   . FF15 68E0B66F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
	//6FB33915   . FF15 CCF0B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
	//6FB3A395   . FF15 08F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
	//6FB1C2F5   . FF15 10F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState
	//6FB6DEF5   . FF15 04F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState

	log_msg("\n");

	isInstalled = true;
}


/*================================= END OF FILE =================================*/