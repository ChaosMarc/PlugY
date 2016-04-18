/*=================================================================
	File created by Yohann NICOLAS.

	Updating server.

=================================================================*/

#include "common.h"
#include "updateServer.h"
#include "error.h"
#include "d2functions.h"

#include "statsPoints.h"
#include "skillsPoints.h"
#include "infinityStash.h"
#include "commands.h"


int STDCALL handleServerUpdate(Unit* ptChar, WORD param)
{
	log_msg("Received custom message: %X\n", param);
	switch(param & 0xFF)
	{
		case US_UNASSIGN_STR_POINT :	UnassignStrPoint( ptChar ); return 1;
		case US_UNASSIGN_ENE_POINT :	UnassignEnePoint( ptChar ); return 1;
		case US_UNASSIGN_DEX_POINT :	UnassignDexPoint( ptChar ); return 1;
		case US_UNASSIGN_VIT_POINT :	UnassignVitPoint( ptChar ); return 1;
		case US_UNASSIGN_STR_POINTS :	UnassignStrPoints( ptChar ); return 1;
		case US_UNASSIGN_ENE_POINTS :	UnassignEnePoints( ptChar ); return 1;
		case US_UNASSIGN_DEX_POINTS :	UnassignDexPoints( ptChar ); return 1;
		case US_UNASSIGN_VIT_POINTS :	UnassignVitPoints( ptChar ); return 1;
		case US_UNASSIGN_SKILLS :		UnassignAllSkillsPoints( ptChar ); return 1;
		case US_SELECT_PREVIOUS :		selectPreviousStash( ptChar ); return 1;
		case US_SELECT_NEXT :			selectNextStash( ptChar ); return 1;
		case US_SELECT_SELF :			if (active_sharedStash) toggleToSelfStash( ptChar ); return 1;
		case US_SELECT_SHARED :			if (active_sharedStash) toggleToSharedStash( ptChar ); return 1;
		case US_SELECT_PREVIOUS_INDEX :	selectPreviousIndexStash( ptChar ); return 1;
		case US_SELECT_NEXT_INDEX :		selectNextIndexStash( ptChar ); return 1;

		case US_SELECT_PREVIOUS2 :		selectPrevious2Stash( ptChar ); return 1;
		case US_SELECT_NEXT2 :			selectNext2Stash( ptChar ); return 1;
		case US_SELECT_PREVIOUS_INDEX2:	selectPreviousIndex2Stash( ptChar ); return 1;
		case US_SELECT_NEXT_INDEX2 :	selectNextIndex2Stash( ptChar ); return 1;

		case US_STARTSAVE :				savePlayers( ptChar ); return 1;

		case US_MAXGOLD :				maxGold(ptChar); return 1;
		case US_PUTGOLD :				putGold(ptChar, 0); return 1;
		case US_TAKEGOLD :				takeGold(ptChar, 0); return 1;
		default : return 0;
	}
}

FCT_ASM( caller_handleServerUpdate)
	PUSH EAX
	PUSH EBX
	CALL handleServerUpdate
	TEST EAX,EAX
	JNZ END_RCM
	MOV EAX,ESI
	AND EAX,0xFF
	SHR ESI,8
	MOV EDI,EAX
	RETN
END_RCM:
	ADD ESP,4
	POP EDI
	POP ESI
	XOR EAX,EAX
	POP EBX
	RETN 8
}}


FCT_ASM( caller_handleServerUpdate_9)
	XOR EDX,EDX
	MOV DX,WORD PTR DS:[EAX+1]
	PUSH ECX
	PUSH EDX
	PUSH EDX
	PUSH ECX
	CALL handleServerUpdate
	POP EDX
	POP ECX
	TEST EAX,EAX
	JNZ END_RCM
	RETN
END_RCM:
	POP EAX
	XOR EAX,EAX
	RETN 8
}}


void Install_UpdateServer()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Game for received button click message. (UpdateServer)\n");

	// manage button click message from Client.
	mem_seek R7(D2Game, 4A702, 4AAC2, 56EA2, 54AE3, 2C773, 975C3, CC983);
	if (version_D2Game >= V111) {
		memt_byte( 0xC1, 0x57 );	// PUSH EDI
		memt_byte( 0xEE, 0xE8 );	// CALL caller_handleServerUpdate
		MEMT_REF4( 0xF88B5708, caller_handleServerUpdate);
		//01FD4AE3   . C1EE 08        SHR ESI,8
		//01FD4AE6   . 57             PUSH EDI
		//01FD4AE7   . 8BF8           MOV EDI,EAX
		//01F9C773   . C1EE 08        SHR ESI,8
		//01F9C776   . 57             PUSH EDI
		//01F9C777   . 8BF8           MOV EDI,EAX
		//6FCB75C3   . C1EE 08        SHR ESI,8
		//6FCB75C6   . 57             PUSH EDI
		//6FCB75C7   . 8BF8           MOV EDI,EAX
		//6FCEC983   . C1EE 08        SHR ESI,8
		//6FCEC986   . 57             PUSH EDI
		//6FCEC987   . 8BF8           MOV EDI,EAX
	} else if (version_D2Game == V110) {
		memt_byte( 0xC1, 0xE8 );	// CALL caller_handleServerUpdate
		MEMT_REF4( 0xF88B08EE, caller_handleServerUpdate);
		//6FC86EA2   . C1EE 08        SHR ESI,8
		//6FC86EA5   . 8BF8           MOV EDI,EAX
	} else {
		memt_byte( 0x33, 0xE8 );	// CALL caller_handleServerUpdate
		MEMT_REF4( 0x508B66D2, caller_handleServerUpdate_9);
		memt_byte( 0x01, 0x90 );	// NOP
		//6FC7A702   . 33D2           XOR EDX,EDX
		//6FC7A704   . 66:8B50 01     MOV DX,WORD PTR DS:[EAX+1]
	}

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/