/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Interface functions

=================================================================*/

#include "statsPoints.h"
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>

static struct
{
	union{
		DWORD all;
		struct{
			DWORD previousPage:1;
			DWORD nextPage:1;
		};
	};
} isDownBtn;

#define	getXPreviousPageBtn()		RX(0x19)//0x70
#define	getLPreviousPageBtn()		32
#define	getYPreviousPageBtn()		RY(0x40)
#define	getHPreviousPageBtn()		32
#define isOnPreviousPageBtn(x,y)	isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())

#define	getXNextPageBtn()		RX(D2GetResolution()?0x43:0x8A)
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(D2GetResolution()?0x40:0x70)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())



void STDCALL printStatsPageBtns()
{
	if (!active_newInterfaces || !D2isLODGame() ) return;

	LPWSTR lpText;
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();

	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));

	if (printBackgroundOnMainPage && D2GetResolution())
	{
		setImage(&data, statsBackgroundImages);
		setFrame(&data, 1);
		D2PrintImage(&data, getXPreviousPageBtn()-7, getYPreviousPageBtn()+8, -1, 5, 0);
	}

	setImage(&data, D2LoadBuySelBtn());
	if (D2GetResolution())
	{
		setFrame(&data, 12 + isDownBtn.previousPage);
		D2PrintImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);
	}
	setFrame(&data, 14 + isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	D2SetFont(1);
	if (D2GetResolution() && isOnPreviousPageBtn(mx,my))	//print popup "previous page"
	{
		lpText = getLocalString(STR_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousPageBtn()+getLPreviousPageBtn()/2, getYPreviousPageBtn()-getHPreviousPageBtn(), WHITE, 1);
	}
	else if ( isOnNextPageBtn(mx,my))
	{
		lpText = getLocalString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn()+getLNextPageBtn()/2, getYNextPageBtn()-getHNextPageBtn(), WHITE, 1);
	}
}

Unit* STDCALL statsPageMouseDown(sWinMessage* msg)
{
	Unit* ptChar = D2GetClientPlayer();

	if (!active_newInterfaces || !D2isLODGame() ) return ptChar;

	if (D2GetResolution() && isOnPreviousPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button previous page\n");
		isDownBtn.previousPage = 1;
		D2PlaySound(4,0,0,0,0);
		freeMessage(msg);
		return NULL;
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
		freeMessage(msg);
		return NULL;
	}
	return ptChar;
}


Unit* STDCALL statsPageMouseUp(sWinMessage* msg)
{
	Unit* ptChar = D2GetClientPlayer();

	if (!active_newInterfaces || !D2isLODGame() ) return ptChar;

	if (D2GetResolution() && isOnPreviousPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button previous page\n");
		if (isDownBtn.previousPage)
		{
			GoPreviousStatPage();
			log_msg("previous page press\n");
			isDownBtn.all=0;
			freeMessage(msg);
			return NULL;
		}
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button next page\n");
		if (isDownBtn.nextPage)
		{
			GoNextStatPage();
			log_msg("next page press\n");
			isDownBtn.all=0;
			freeMessage(msg);
			return NULL;
		}
	}

	isDownBtn.all=0;
	return ptChar;
}

FCT_ASM ( caller_printStatsPageBtns_111 )
	CALL printStatsPageBtns
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x370
	RETN
}}


FCT_ASM ( caller_printStatsPageBtns )
	CALL printStatsPageBtns
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x3B0
	RETN
}}

FCT_ASM ( caller_printStatsPageBtns_9 )
	CALL printStatsPageBtns
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x374
	RETN
}}



FCT_ASM ( caller_statsPageMouseDown_111 )
	PUSH DWORD PTR SS:[ESP+0x20]
	CALL statsPageMouseDown
	TEST EAX,EAX
	JE fin_statsPageMouseDown
	RETN
fin_statsPageMouseDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_statsPageMouseDown )
	PUSH DWORD PTR SS:[ESP+0x18]
	CALL statsPageMouseDown
	TEST EAX,EAX
	JE fin_statsPageMouseDown
	RETN
fin_statsPageMouseDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_statsPageMouseUp )
	PUSH EBP
	CALL statsPageMouseUp
	TEST EAX,EAX
	JE fin_statsPageMouseUp
	RETN
fin_statsPageMouseUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,8
	RETN 4
}}

FCT_ASM ( caller_statsPageMouseUp_9 )
	PUSH EBP
	CALL statsPageMouseUp
	TEST EAX,EAX
	JE fin_statsPageMouseUp
	RETN
fin_statsPageMouseUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	POP ECX
	RETN 4
}}


void Install_InterfaceStats()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	Install_PlugYImagesFiles();

	log_msg("Patch D2Client for stats interface. (InterfaceStats)\n");

	// Print new buttons images
	mem_seek R7(D2Client, 2A7BE, 2A7AE, 30F86, 83636, 8A0B6, 6C016, BDC16, C03B6);
	memt_byte( 0x5F, 0xE9 );	// JMP
	MEMT_REF4( 0x815B5D5E, version_D2Client >= V111 ? caller_printStatsPageBtns_111: version_D2Client == V110 ? caller_printStatsPageBtns : caller_printStatsPageBtns_9);
	//6FAD0F86   . 5F                   POP EDI
	//6FAD0F87   . 5E                   POP ESI
	//6FAD0F88   . 5D                   POP EBP
	//6FAD0F89   . 5B                   POP EBX
	//6FAD0F8A   . 81C4 B0030000        ADD ESP,3B0
	//6FAD0F90   . C3                   RETN
	//6FB33636   . 5F             POP EDI
	//6FB33637   . 5E             POP ESI
	//6FB33638   . 5D             POP EBP
	//6FB33639   . 5B             POP EBX
	//6FB3363A   . 81C4 70030000  ADD ESP,370
	//6FB33640   . C3             RETN
	//6FB3A0B6   . 5F             POP EDI
	//6FB3A0B7   . 5E             POP ESI
	//6FB3A0B8   . 5D             POP EBP
	//6FB3A0B9   . 5B             POP EBX
	//6FB3A0BA   . 81C4 70030000  ADD ESP,370
	//6FB3A0C0   . C3             RETN
	//6FB1C016   . 5F             POP EDI
	//6FB1C017   . 5E             POP ESI
	//6FB1C018   . 5D             POP EBP
	//6FB1C019   . 5B             POP EBX
	//6FB1C01A   . 81C4 70030000  ADD ESP,370
	//6FB1C020   . C3             RETN
	//6FB6DC16  |. 5F             POP EDI
	//6FB6DC17  |. 5E             POP ESI
	//6FB6DC18  |. 5D             POP EBP
	//6FB6DC19  |. 5B             POP EBX
	//6FB6DC1A  |. 81C4 70030000  ADD ESP,370
	//6FB6DC20  \. C3             RETN
	//6FB703B6  |. 5F             POP EDI
	//6FB703B7  |. 5E             POP ESI
	//6FB703B8  |. 5D             POP EBP
	//6FB703B9  |. 5B             POP EBX
	//6FB703BA  |. 81C4 70030000  ADD ESP,370
	//6FB703Ñ0  \. C3             RETN

	if ( version_D2Client >= V111 )
	{
		// Manage mouse down (Play sound)
		mem_seek R7(D2Client, 2AA6D, 2AA5D, 3133D, 827C8, 89248, 6B1A8, BCDC8, BF568);
		memt_byte( 0xA1, 0xE8 );
		MEMT_REF4( ptptClientChar, caller_statsPageMouseDown);
		//6FB327C8   . A1 F0C4BC6F    MOV EAX,DWORD PTR DS:[6FBCC4F0]
		//6FB39248   . A1 E0C1BC6F    MOV EAX,DWORD PTR DS:[6FBCC1E0]
		//6FB1B1A8   . A1 D0C3BC6F    MOV EAX,DWORD PTR DS:[6FBCC3D0]
		//6FB6CDC8   . A1 FCBBBC6F    MOV EAX,DWORD PTR DS:[6FBCBBFC]
		//6FB6F568   . A1 50D0BC6F    MOV EAX,DWORD PTR DS:[6FBCD050]

		// Manage mouse up
		mem_seek R7(D2Client, 2AC43, 2AC33, 3151A, 83853, 8A2D3, 6C233, BDE33, C05D3);
		memt_byte( 0xA1, 0xE8 );
		MEMT_REF4( ptptClientChar, caller_statsPageMouseUp);
		//6FB33853   . A1 F0C4BC6F    MOV EAX,DWORD PTR DS:[6FBCC4F0]
		//6FB3A2D3   . A1 E0C1BC6F    MOV EAX,DWORD PTR DS:[6FBCC1E0]
		//6FB1C233   . A1 D0C3BC6F    MOV EAX,DWORD PTR DS:[6FBCC3D0]
		//6FB6DE33   . A1 FCBBBC6F    MOV EAX,DWORD PTR DS:[6FBCBBFC]
		//6FB705D3   . A1 50D0BC6F    MOV EAX,DWORD PTR DS:[6FBCD050]
	} else {
		// Manage mouse down (Play sound)
		mem_seek R7(D2Client, 2AA6D, 2AA5D, 3133D, 827C8, 89248, 6B1A8, 0000, 0000);
		MEMC_REF4( D2GetClientPlayer, caller_statsPageMouseDown);
		//6FAD133C   . E8 8F700500    CALL D2Client.6FB283D0

		// Manage mouse up
		mem_seek R7(D2Client, 2AC43, 2AC33, 3151A, 83853, 8A2D3, 6C233, 0000, 0000);
		MEMC_REF4( D2GetClientPlayer, version_D2Client == V110 ? caller_statsPageMouseUp : caller_statsPageMouseUp_9);//0x00056EB2
		//6FAD1519   . E8 B26E0500    CALL D2Client.6FB283D0
	}

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/