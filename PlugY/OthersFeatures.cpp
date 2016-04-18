/*=================================================================
	File created by Yohann NICOLAS.

	Others features.

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"

bool active_othersFeatures = false;


/*
	// Remove protect on the save file .d2s
	mem_seek( offset_D2Game + 0x77080);//6FC8DD5E-6FAA0000
	memt_byte( 0x74, 0xEB );	// JMP SHORT D2Game.6FC8DD6D
	//6FC8DD5E     74 0D          JE SHORT D2Game.6FC8DD6D
*/

/*
void Install_ChangeResolution()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2gfx for . (ChangeResolution)\n");

	// execute if it's our packet else continue
	mem_seek( offset_D2Client + 0x23ED);//6FAA23EC-6FAA0000
	memt_dword( 0x280, 0x400 );
	//6FAA23EC   B8 80020000      MOV EAX,280                              ; Case 0 of switch 6FAA23C2
	mem_seek( offset_D2Client + 0x23F7);//6FAA23F1-6FAA0000
	memt_dword( 0x1E0, 0x300 );
	//6FAA23F1   C705 F040B76F E0>MOV DWORD PTR DS:[6FB740F0],1E0

	// change resolution
	mem_seek R7(D2gfx, 4B91, 4B91, 4B61, 0000, 0000, 0000, 0000);
	memt_dword( 0x280, 0x400 );
	//6FA74B5D   > C74424 14 8002>MOV DWORD PTR SS:[ESP+14],280            ;  Case 0 of switch 6FA74B45
	mem_seek R7(D2gfx, 4B96, 4B96, 4B66, 0000, 0000, 0000, 0000);
	memt_dword( 0x1E0, 0x300 );
	//6FA74B65   . B8 E0010000    MOV EAX,1E0

	// refresh size
	mem_seek( offset_D2Gdi + 0x118F);//6F831189-6F830000
	memt_dword( 0x280, 0x400 );
	//6F831189  |> C705 7CC0836F >MOV DWORD PTR DS:[6F83C07C],280
	mem_seek( offset_D2Gdi + 0x1199);//6F831193-6F830000
	memt_dword( 0x1E0, 0x300 );
	//6F831193  |. C705 8CC4836F >MOV DWORD PTR DS:[6F83C48C],1E0

	log_msg("\n");

	isInstalled = true;
}

///////////////////////////////////////////////////////////////////////////////////////////

DWORD SetDisabledStat(Unit* ptItem, Stats* ptStats, DWORD disabled)
{
	if (!ptItem || !ptStats)
		return 0;
	if (disabled)
	{
		if (!ptStats->isDisabled)
		{
			D2PreUpdateDisabledStat(ptStats);
			ptStats->isDisabled = 1;
			D2UpdateDisabledStat(ptItem->ptStats,ptStats,1);
			return 1;
		}
	} else if (ptStats->isDisabled)
		{
			D2PreUpdateDisabledStat(ptStats);
			ptStats->isDisabled = 0;
			D2UpdateDisabledStat(ptItem->ptStats,ptStats,1);
		}
	return 0;
}

void STDCALL Test2Fct (Unit* ptChar, Unit* ptItem)
{
	SetDisabledStat(ptItem, ptItem->ptStats->ptStatsList, 0);//(DWORD)(rand()/(RAND_MAX+1.0)*2));
}

FCT_ASM ( caller_Test2 )
	PUSH EDI	//ptItem
	PUSH ESI	//ptChar
	CALL Test2Fct
	POP ECX
	PUSH EBX
	MOV EAX,DWORD PTR DS:[ESI]
	XOR EBX,EBX
	JMP ECX
}}

void Install_Test2()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2Game. (Test)\n");

	// Test
	mem_seek( offset_D2Game + 0x1253C);//6FC4253C-6FC30000
	memt_byte( 0x8B, 0xE8 );	// CALL caller_BnetBtnPress
	MEMT_REF4( 0xDB335306, caller_Test2);
	//6FC4253C  |> 8B06           MOV EAX,DWORD PTR DS:[ESI]
	//6FC4253E  |. 53             PUSH EBX
	//6FC4253F  |. 33DB           XOR EBX,EBX
	isInstalled = true;
}*/
///////////////////////////////////////////////////////////////////////////////////////////////


void Install_OthersFeatures()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch. (OthersFeatures)\n");

//	Install_ChangeResolution();
//	Install_Test();

	isInstalled = true;
}

/*================================= END OF FILE =================================*/