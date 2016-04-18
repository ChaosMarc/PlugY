/*=================================================================
	File created by Yohann NICOLAS.

	Interface functions

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "globalVariable.h"
#include "updateServer.h"	// Install_UpdateServer()
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "interface_Stats.h"// Install_InterfaceStats()
#include "newInterfaces.h"
#include "newInterface_Stats.h"
#include "newInterface_StatsPageTwo.h"
#include "newInterface_Runewords.h"
#include <stdio.h>

bool active_newInterfaces=false;
bool selectMainPageOnOpenning=true;
bool printBackgroundOnMainPage=true;

DWORD bDontPrintBorder=false;

int selectedPage=0;
int lastPage=0;
int extraHiddenPage=0;

void GoNextStatPage()
{
	selectedPage++;
	if ( selectedPage > lastPage)
		selectedPage = 0;
}

void GoPreviousStatPage()
{
	selectedPage--;
	if ( selectedPage < 0 )
		selectedPage = lastPage;
}

void GoStatPage(int page)
{
	if ( (page >= 0) && (page <= lastPage + (D2GetResolution()? extraHiddenPage : 0)) )
		selectedPage = page;
}

int GetCurrentPage()
{
	return selectedPage;
}


void STDCALL printCustomPage()
{
	if(onRealm) {D2PrintStatsPage();return;}
	if ( (selectedPage > 0) && (selectedPage<=lastPage) )
		printNewStatsPageTwo(selectedPage);
	else if (selectedPage == lastPage+1)
		printRunewordsPage();
	else if (selectedPage == lastPage+2)
		printNewStatsPage();
	else
		D2PrintStatsPage();
}

DWORD STDCALL mouseCustomPageLeftDown(sWinMessage* msg)
{
	if(onRealm) return -1;
	if ( (selectedPage > 0) && (selectedPage<=lastPage) )
		return mouseNewStatsPageTwoLeftDown(msg);
	else if (selectedPage == lastPage+1)
		return mouseRunewordsPageLeftDown(msg);
	else if (selectedPage == lastPage+2)
		return mouseNewStatsPageLeftDown(msg);
	else
		return -1;
}

DWORD STDCALL mouseCustomPageLeftUp(sWinMessage* msg)
{
	if(onRealm) return -1;
	if ( (selectedPage > 0) && (selectedPage <= lastPage) )
		return mouseNewStatsPageTwoLeftUp(msg);
	else if (selectedPage == lastPage+1)
		return mouseRunewordsPageLeftUp(msg);
	else if (selectedPage == lastPage+2)
		return mouseNewStatsPageLeftUp(msg);
	else
		return -1;
}

FCT_ASM ( caller_DontPrintBorder_111 )
	MOV ECX,bDontPrintBorder
	TEST ECX,ECX
	JE printBorder
	MOV bDontPrintBorder,0
	ADD DWORD PTR SS:[ESP],0xBC
	RETN
printBorder:
	MOV ECX,0x12
	RETN
}}

FCT_ASM ( caller_DontPrintBorder )
	MOV ECX,bDontPrintBorder
	TEST ECX,ECX
	JE printBorder
	MOV bDontPrintBorder,0
	ADD DWORD PTR SS:[ESP],0xB6
	RETN
printBorder:
	MOV ECX,0x12
	RETN
}}


FCT_ASM ( caller_mouseCustomPageLeftDown_111 )
	PUSH EAX
	PUSH ESI
	CALL mouseCustomPageLeftDown
	TEST EAX,EAX
	POP EAX
	JE end_mouseNewPageLDown
	JG continue_mouseNewPageLDown
	LEA ECX,DWORD PTR DS:[EAX+0x80]
	RETN
continue_mouseNewPageLDown:
	POP EAX
	ADD EAX,0x143
	PUSH EDI
	JMP EAX
	RETN
end_mouseNewPageLDown:
	ADD ESP,4
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_mouseCustomPageLeftDown )
	PUSH EAX
	PUSH EDI
	CALL mouseCustomPageLeftDown
	TEST EAX,EAX
	POP EAX
	JE end_mouseNewPageLDown
	JG continue_mouseNewPageLDown
	LEA ECX,DWORD PTR DS:[EAX+0x80]
	RETN
continue_mouseNewPageLDown:
	ADD DWORD PTR SS:[ESP],0x152
	RETN
end_mouseNewPageLDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_mouseCustomPageLeftDown_9 )
	PUSH EAX
	PUSH EDI
	CALL mouseCustomPageLeftDown
	TEST EAX,EAX
	POP EAX
	JE end_mouseNewPageLDown
	JG continue_mouseNewPageLDown
	LEA ECX,DWORD PTR DS:[EAX+0x80]
	RETN
continue_mouseNewPageLDown:
	ADD DWORD PTR SS:[ESP],0x149
	RETN
end_mouseNewPageLDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}



FCT_ASM ( caller_mouseCustomPageLeftUp_111 )
	PUSH EBP
	CALL mouseCustomPageLeftUp
	TEST EAX,EAX
	JE end_mouseNewPageLUp
	JG continue_mouseNewPageLUp
	MOV EAX,DWORD PTR DS:[ptWindowStartX]
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
continue_mouseNewPageLUp:
	ADD DWORD PTR SS:[ESP],0x2C4
	RETN
end_mouseNewPageLUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,8
	RETN 4
}}


FCT_ASM ( caller_mouseCustomPageLeftUp )
	PUSH EBP
	CALL mouseCustomPageLeftUp
	TEST EAX,EAX
	JE end_mouseNewPageLUp
	JG continue_mouseNewPageLUp
	MOV EAX,DWORD PTR DS:[ptWindowStartX]
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
continue_mouseNewPageLUp:
	ADD DWORD PTR SS:[ESP],0x1AE
	RETN
end_mouseNewPageLUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,8
	RETN 4
}}


FCT_ASM ( caller_mouseCustomPageLeftUp_9 )
	PUSH EBP
	CALL mouseCustomPageLeftUp
	TEST EAX,EAX
	JE end_mouseNewPageLUp
	JG continue_mouseNewPageLUp
	MOV EAX,DWORD PTR DS:[ptWindowStartX]
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
continue_mouseNewPageLUp:
	ADD DWORD PTR SS:[ESP],0x16A
	RETN
end_mouseNewPageLUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	POP ECX
	RETN 4
}}






FCT_ASM ( caller_resetSelectedPageByToolBar )
	MOV selectedPage,0
	CMP EAX,0x26
	JNZ noJump
	ADD DWORD PTR SS:[ESP],0x1F
noJump:
	RETN
}}

FCT_ASM ( caller_resetSelectedPageByKey )
	MOV selectedPage,0
	POP EAX
	PUSH EBP
	XOR EBP,EBP
	CMP EDX,EBP
	JMP EAX
}}


FCT_ASM ( caller_resetSelectedPage )
	TEST EAX,EAX
	SETE DL
	JNZ END_resetSelectedPage
	CMP ESI,2
	JNZ END_resetSelectedPage
	MOV selectedPage,0
END_resetSelectedPage:
	RETN
}}

void Install_NewInterfaces()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();
	Install_PlugYImagesFiles();
	Install_PlugYTxtFiles();
	Install_InterfaceStats();

	log_msg("Patch D2Client for new custom page interface. (NewInterfaces)\n");
	if ( version_D2Client >= V110 )
		extraHiddenPage=1;

	if (selectMainPageOnOpenning)
	{
		if ( version_D2Client >= V111 )
		{
			//Reset selectedPage variable on opening stats page
			mem_seek R7(D2Client, 0000, 0000, 0000, 4B79E, 8F73E, 55E0E, 65F5E);
			memt_byte( 0x83, 0xE8 );	// CALL caller_resetSelectedPage
			MEMT_REF4( 0x1F7426F8, caller_resetSelectedPageByToolBar);
			//6FAFB79E   > 83F8 26        CMP EAX,26
			//6FAFB7A1   . 74 1F          JE SHORT D2Client.6FAFB7C2
			//6FB3F73E   > 83F8 26        CMP EAX,26
			//6FB3F741   . 74 1F          JE SHORT D2Client.6FB3F762
			//6FB05E0E   > 83F8 26        CMP EAX,26
			//6FB05E11   . 74 1F          JE SHORT D2Client.6FB05E32
			//6FB15F5E   > 83F8 26        CMP EAX,26
			//6FB15F61   . 74 1F          JE SHORT D2Client.6FB15F82

			mem_seek R7(D2Client, 0000, 0000, 0000, 1E55A, 6A8FA, A31DA, 3C5EA);
			memt_byte( 0x55, 0xE8 );	// CALL caller_resetSelectedPage
			MEMT_REF4( 0xD53BED33, caller_resetSelectedPageByKey);
			//6FACE55A   . 55             PUSH EBP
			//6FACE55B   . 33ED           XOR EBP,EBP
			//6FACE55D   . 3BD5           CMP EDX,EBP
			//6FB1A8FA   . 55             PUSH EBP
			//6FB1A8FB   . 33ED           XOR EBP,EBP
			//6FB1A8FD   . 3BD5           CMP EDX,EBP
			//6FB531DA   . 55             PUSH EBP
			//6FB531DB   . 33ED           XOR EBP,EBP
			//6FB531DD   . 3BD5           CMP EDX,EBP
			//6FAEC5EA   . 55             PUSH EBP
			//6FAEC5EB   . 33ED           XOR EBP,EBP
			//6FAEC5ED   . 3BD5           CMP EDX,EBP


			//For Toggle fct : (not used for open the stat page)
	//		mem_seek R7(D2Client, 88B58, 87ED8, 83478, A1FBE, 6571E, 8EF8E, 0000);//((DWORD)D2TogglePage+0x218);
	//		memt_byte( 0x3B, 0xE8 );
	//		MEMT_REF4( 0x393974C5, caller_resetSelectedPage_111);
	//		memt_byte( 0x28, 0x90 );	// NOP
			//6FB51FBE  |. 3BC5           CMP EAX,EBP                              ;  Case 2 of switch 6FB51FB8
			//6FB51FC0  |. 74 39          JE SHORT D2Client.6FB51FFB
			//6FB51FC2  |. 3928           CMP DWORD PTR DS:[EAX],EBP
			//6FB1571E  |. 3BC5           CMP EAX,EBP                              ;  Case 2 of switch 6FB15718
			//6FB15720  |. 74 39          JE SHORT D2Client.6FB1575B
			//6FB15722  |. 3928           CMP DWORD PTR DS:[EAX],EBP
			//6FB3EF8E  |. 3BC5           CMP EAX,EBP                              ;  Case 2 of switch 6FB3EF88
			//6FB3EF90  |. 74 39          JE SHORT D2Client.6FB3EFCB
			//6FB3EF92  |. 3928           CMP DWORD PTR DS:[EAX],EBP
		} else {
			//Reset selectedPage variable on opening stats page
			mem_seek R7(D2Client, 88B58, 87ED8, 83478, A1FBE, 6571E, 8EF8E, 0000);//((DWORD)D2TogglePage+0x218);
			memt_byte( 0x85, 0xE8 );	// CALL caller_resetSelectedPage
			MEMT_REF4( 0xC2940FC0, caller_resetSelectedPage);
			//6FB23478  |. 85C0           TEST EAX,EAX
			//6FB2347A  |. 0F94C2         SETE DL
			//FOR 1.11
		}
	}

	// Print custom page
	mem_seek R7(D2Client, 87697, 86A17, 81FAB, A3759, 66B59, 902B9, C3B49);
	MEMC_REF4( D2PrintStatsPage, printCustomPage);
	//6FB21FAA   . E8 B1DDFAFF    CALL D2Client.6FACFD60
	//6FB53758   . E8 43F1FDFF    CALL D2Client.6FB328A0
	//6FB16B58  |. E8 C3270200    CALL D2Client.6FB39320
	//6FB402B8  |. E8 C3AFFDFF    CALL D2Client.6FB1B280
	//6FB73B48  |. E8 5393FFFF    CALL D2Client.6FB6CEA0

	// Don't print Border
	mem_seek R7(D2Client, 58EF6, 58EF6, 5F4C6, 2D366, B5A46, 82166, 271C6);
	memt_byte( 0xB9, 0xE8 );	// CALL caller_DontPrintBorder
	MEMT_REF4( 0x00000012, version_D2Client >= V111 ? caller_DontPrintBorder_111 : caller_DontPrintBorder);
	//6FAFF4C6   > B9 12000000    MOV ECX,12
	//6FADD366  |. B9 12000000    MOV ECX,12
	//6FB65A46  |. B9 12000000    MOV ECX,12
	//6FB32166  |. B9 12000000    MOV ECX,12
	//6FAD71C6  |. B9 12000000    MOV ECX,12

	// Manage mouse down (Play sound)
	mem_seek R7(D2Client, 2A9DC, 2A9CC, 312A5, 82736, 891B6, 6B116, BCD36);
	memt_byte( 0x8D, 0xE8 );	// CALL
	MEMT_REF4( 0x00008088, version_D2Client >= V111 ? caller_mouseCustomPageLeftDown_111 : version_D2Client == V110 ? caller_mouseCustomPageLeftDown : caller_mouseCustomPageLeftDown_9);
	memt_byte( 0x00, 0x90 );	// NOP
	//6FAD12A5   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
	//6FB32736   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
	//6FB391B6   . 8D88 80000000     LEA ECX,DWORD PTR DS:[EAX+80]
	//6FB1B116   . 8D88 80000000  LEA ECX,DWORD PTR DS:[EAX+80]
	//6FB6CD36   . 8D88 80000000  LEA ECX,DWORD PTR DS:[EAX+80]

	// Manage mouse up
	mem_seek R7(D2Client, 2ABBB, 2ABAB, 3148D, 836D9, 8A159, 6C0B9, BDCB9);
	memt_byte( 0xA1, 0xE8 );	// CALL caller_mouseCustomPageLeftUp
	MEMT_REF4( ptWindowStartX, version_D2Client >= V111 ? caller_mouseCustomPageLeftUp_111 : version_D2Client == V110 ? caller_mouseCustomPageLeftUp : caller_mouseCustomPageLeftUp_9);
	//6FAD148D   . A1 48A7BB6F       MOV EAX,DWORD PTR DS:[6FBBA748]
	//6FB336D9   . A1 24BDBC6F       MOV EAX,DWORD PTR DS:[6FBCBD24]
	//6FB3A159   . A1 F8BEBC6F       MOV EAX,DWORD PTR DS:[6FBCBEF8]
	//6FB1C0B9   . A1 28BDBC6F    MOV EAX,DWORD PTR DS:[6FBCBD28]
	//6FB6DCB9   . A1 A0B9BC6F    MOV EAX,DWORD PTR DS:[6FBCB9A0]


	// open page : 6FB23515  |> 892CB5 A8A6BB6>MOV DWORD PTR DS:[ESI*4+6FBBA6A8],EBP
	//6FB2347D  |. 8914B5 A8A6BB6F   MOV DWORD PTR DS:[ESI*4+6FBBA6A8],EDX

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/