/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Updating server.

=================================================================*/

#include "bigStash.h" // active_bigStash_tested
#include "uberQuest.h" //active_UberQuest + resetQuestState()
#include "common.h"
#include <stdio.h>

bool onRealm=false;
bool needToInit=false;
int previouslyOnRealm = -1;

void STDCALL BtnPress()
{
	needToInit = 1;
//	if (active_WorldEvent)
//		initWorldEventVariables();
	if (active_UberQuest)
		resetQuestState();
	d2_assert(active_bigStash_tested && onRealm && (previouslyOnRealm==0), "Need to restart after play an open game with the Big Stash",__FILE__,__LINE__);
	d2_assert(active_bigStash_tested && !onRealm && (previouslyOnRealm>0), "Need to restart after play an closed game with the Big Stash",__FILE__,__LINE__);
	previouslyOnRealm = onRealm;
}

FCT_ASM ( caller_BnetBtnPress )
	CMP active_DisableBattleNet,1
	JE disableBattleNet
	MOV onRealm,1
	PUSH EAX
	CALL BtnPress
	POP EAX
	SUB ESP,0x3FC//400
	JMP DWORD PTR SS:[ESP+0x3FC]
disableBattleNet:
	POP EAX
	RETN
}}

/*
FCT_ASM ( caller_MultiPlayerBtnPress )
	CALL BtnPress
	MOV	EAX,1
	RETN
}}
*/

FCT_ASM ( caller_TCPIPBtnPress111 )
	MOV onRealm,0
	CALL BtnPress
	MOV ESI,0x40
	RETN
}}

FCT_ASM ( caller_TCPIPBtnPress )
	MOV onRealm,0
	CALL BtnPress
	MOV EBP,1
	RETN
}}

FCT_ASM ( caller_SinglePlayerBtnPress )
	MOV onRealm,0
	CALL BtnPress
	MOV EDX,0x400
	RETN
}}


FCT_ASM ( caller_fixClientRemovingBug )
	TEST ECX,ECX
	JE notFound
	CMP DWORD PTR DS:[ECX],EBP
	JE found
next:
	MOV EAX,ECX
	MOV ECX,DWORD PTR DS:[EAX+0x4A8]
	TEST ECX,ECX
	JE notFound
	CMP DWORD PTR DS:[ECX],EBP
	JNZ next
found:
	ADD DWORD PTR SS:[ESP],0xB
	RETN
notFound:
	ADD DWORD PTR SS:[ESP],0x1D
	RETN
}}

void Install_VariableOnRealm()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Launch for set not on realm variable. (VariableonRealm)\n");

	// click on Battle.net button
	mem_seek R7(D2Launch, 8195, 81A5, 9915, 129E5, 18AA5, 17D15, 19295, 11C65);
	memt_byte( 0x81, 0xE8 );	// CALL
	MEMT_REF4( 0x000400EC, caller_BnetBtnPress);
	memt_byte( 0x00, 0x90 );	// NOP
	//6FA529E5   . 81EC 00040000  SUB ESP,400

	// click on Multiplayer button
//	mem_seek R7(D2Launch, D5EC, D5CC, EFFC, 0000, 0000, 0000, 0000);
//	memt_byte( 0xB8, 0xE8 );	// CALL
//	MEMT_REF4( 0x00000001, caller_MultiPlayerBtnPress);
	//6FA1EFFC   . B8 01000000    MOV EAX,1

	// click on TCP/IP button
	mem_seek R7(D2Launch, 87B9, 87C9, 9F99, 11329, 17409, 16659, 17B8E, 1053E);
	if (version_D2Launch == V109b || version_D2Launch == V109d || version_D2Launch == V110)
	{
		memt_byte( 0xBD, 0xE8 );	// CALL
		MEMT_REF4( 0x00000001, caller_TCPIPBtnPress);
	} else {
		memt_byte( 0xBE, 0xE8 );	// CALL
		MEMT_REF4( 0x00000040, caller_TCPIPBtnPress111);
		//6FA51329   . BE 40000000    MOV ESI,40
	}

	// click on SinglePlayer button
	mem_seek R7(D2Launch, D1F6, D1E6, EC16, B726, 117E6, 10A56, 11F36, A906);
	memt_byte( 0xBA, 0xE8 );	// CALL
	MEMT_REF4( 0x00000400, caller_SinglePlayerBtnPress);
	//6FA4B726   . BA 00040000    MOV EDX,400

	if (version_D2Game == V110)
	{
		log_msg("\nPatch D2Game for fixing ptClient removing bug. (VariableonRealm)\n");
		//Bug crash ptClient search fix (for Megalixir Mod).
		mem_seek R7(D2Game, 0000, 0000, 2B97, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0x39 ,0xE8);
		MEMT_REF4( 0x8B0C7429 , caller_fixClientRemovingBug);
		memt_byte( 0xC1 ,0x90);
		//6FC32B97  |> 3929           CMP DWORD PTR DS:[ECX],EBP
		//6FC32B99  |. 74 0C          JE SHORT D2Game.6FC32BA7
		//6FC32B9B  |> 8BC1           MOV EAX,ECX
	}

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/