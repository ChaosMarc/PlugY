/*=================================================================
	File created by Yohann NICOLAS.

	More little options.

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include <stdio.h>

int active_Windowed = true;
int active_DisplayItemLevel = false;
DWORD nbPlayersCommandByDefault = 0;
int active_alwaysRegenMapInSP = false;
int active_RunLODs = false;
int active_AlwaysDisplayLifeMana = false;
int active_EnabledTXTFilesWithMSExcel = false;
int active_DisplayBaseStatsValue = false;
int active_LadderRunewords = false;
int active_EnabledCowPortalWhenCowKingWasKill = false;

/****************************************************************************************************/

int setWindowedOptionsDone = false;
int active_RemoveBorder = true;
int active_WindowOnTop = true;
int active_Maximized = true;
int active_SetWindowPos = true;
int windowedX = 240;
int windowedY = 0;
int windowedWidth = 1440;
int windowedHeight = 1080;
int active_LockMouseOnStartup = true;

void lockMouseCursor(int width, int height)
{
	RECT clientRect;
	RECT rect;
	HWND hwnd = GetActiveWindow();
	GetClientRect(hwnd, &clientRect);
	GetWindowRect(hwnd, &rect);
	int shiftX = (rect.right - rect.left - clientRect.right) / 2;
	int shiftY = rect.bottom - rect.top - clientRect.bottom - shiftX;
	log_msg("Windows size : %i, %i, %i, %i\n", rect.left, rect.top, rect.right, rect.bottom);
	rect.left += shiftX;
	rect.right = rect.left + width;
	rect.top += shiftY;
	rect.bottom = rect.top + height;
	//no resize : 560, 231, 1360, 831
	//resized : 240, 0, 1040, 600
	log_msg("Lock Mouse Cursor : %i, %i, %i, %i\n", rect.left, rect.top, rect.right, rect.bottom);
	ClipCursor(&rect);
}

void lockMouseCursor() { lockMouseCursor(ResolutionX, ResolutionY); }

void SetWindowedOptions()
{
	if (setWindowedOptionsDone)
		return;
	HWND hwnd = GetActiveWindow();
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	if (active_RemoveBorder)
	{
		LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
		SetWindowLong(hwnd, GWL_STYLE, lStyle);
		SetWindowPos(hwnd, NULL, 0, 0, clientRect.right, clientRect.bottom, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	if (active_Maximized && !active_SetWindowPos)
	{
		RECT screen;
		GetWindowRect(GetDesktopWindow(), &screen);
		log_msg("Screen size : %i, %i, %i, %i\n", screen.left, screen.top, screen.right, screen.bottom);
		int w = screen.bottom * clientRect.right / clientRect.bottom;
		int h = w * clientRect.bottom / clientRect.right;
		if (screen.right < w)
		{
			h = screen.right * clientRect.bottom / clientRect.right;
			w = h * clientRect.right / clientRect.bottom;
		}
		windowedX = (screen.right - w) / 2;
		windowedY = (screen.bottom - h) / 2;
		windowedWidth = w;
		windowedHeight = h;
	}

	if (active_SetWindowPos || active_Maximized)
	{
		if (active_WindowOnTop)
			SetWindowPos(hwnd, HWND_TOPMOST, windowedX, windowedY, windowedWidth, windowedHeight, SWP_FRAMECHANGED);
		else
			SetWindowPos(hwnd, NULL, windowedX, windowedY, windowedWidth, windowedHeight, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
	} else if (active_WindowOnTop)
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, clientRect.right, clientRect.bottom, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

	if (active_LockMouseOnStartup)
		lockMouseCursor(clientRect.right, clientRect.bottom);

	setWindowedOptionsDone = true;
}

/****************************************************************************************************/

void STDCALL displayItemlevel(LPWSTR popup, Unit* ptItem)
{
	if (onRealm && (selectModParam==MOD_NO)) return;
	WCHAR text[0x50];
	swprintf(text, L"Item Level: %u\n", D2GetItemLevel(ptItem));
	D2SetColorPopup(text,WHITE);
	wcscat(popup,text);
}

FCT_ASM ( caller_displayItemlevel_113 )
	PUSH ECX
	PUSH EAX
	PUSH EAX
	LEA EAX,DWORD PTR SS:[ESP+0x1E70]
	PUSH EAX
	CALL displayItemlevel
	POP EAX
	POP ECX
	POP EDX
	PUSH 0x100
	JMP EDX
}}

FCT_ASM ( caller_displayItemlevel_111 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1E74]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevelSet_111 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1958]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}


FCT_ASM ( caller_displayItemlevel )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x5018]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevelSet )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1220]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevel_9 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x501C]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevelSet_9 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1224]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}


void Install_DisplayItemLevel()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for display item popup. (DisplayPopup)\n");

	// print the text in the final buffer
	mem_seek R7(D2Client,	3D47C,	3D47C,	438A1, ADD0A, 789DA, AE0AA, 941C0);
	memt_byte( 0x68 , 0xE8);
	MEMT_REF4( 0x100, version_D2Client >= V113 ? caller_displayItemlevel_113 : version_D2Client >= V111 ? caller_displayItemlevel_111 : version_D2Client == V110 ? caller_displayItemlevel : caller_displayItemlevel_9);
	//6FAE38A1   . 68 00010000        PUSH 100
	//6FB5DD0A  |. 68 00010000        PUSH 100
	//6FB289DA  |. 68 00010000	      PUSH 100
	//6FB5E0AA  |. 68 00010000    PUSH 100
	//6FB441C0  |. 68 00010000    PUSH 100

	// print the text in the final buffer (for set items)
	mem_seek R7(D2Client,	3C452,	3C452,	427BE, AC773, 77773, ACEB3, 92FE3);
	memt_byte( 0x68 , 0xE8);
	MEMT_REF4( 0x100, version_D2Client >= V111  ? caller_displayItemlevelSet_111 : version_D2Client == V110 ? caller_displayItemlevelSet : caller_displayItemlevelSet_9);
	//6FAE27BE   . 68 00010000        PUSH 100
	//6FB5C773  |. 68 00010000        PUSH 100
	//6FB27773  |. 68 00010000        PUSH 100
	//6FB5CEB3  |. 68 00010000    PUSH 100
	//6FB42FE3  |. 68 00010000    PUSH 100

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

char* msgNBPlayersString = "players %u";
DWORD* infoEnabledSendPlayersCommand;
void SendPlayersCommand()
{
	#pragma pack(1)
	struct {
		BYTE displayType;//0x15 main msg;  0x14: char popup
		BYTE un;
		BYTE zero;
		char string[0xFF];
		char null;
	} data;
	#pragma pack()

	if (!needToInit || onRealm) return;
	needToInit=0;

	DWORD info = *infoEnabledSendPlayersCommand;
	if ((info != 0) && (info != 1) && (info != 6) && (info != 8)) return;

	D2SetNbPlayers(nbPlayersCommandByDefault);

	memset(&data,0,sizeof(data));
	data.displayType=0x15;
	data.un=1;
	data.zero=0;//*(BYTE*)(offset_D2Client+0x112CFC); in 1.10
	data.null=NULL;
	sprintf(data.string, msgNBPlayersString, nbPlayersCommandByDefault);
	D2SendMsgToAll((BYTE*)&data);
}

FCT_ASM ( caller_SendPlayersCommand )
	CALL SendPlayersCommand
	JMP D2GetResolution
}}

void Install_SendPlayersCommand()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for init default nb /players. (SendPlayersCommand)\n");

	infoEnabledSendPlayersCommand = (DWORD*)R7(D2Client, 111D60, 110BC0, 107960, 11BFBC, 11C2AC, 11BFF8, 11C394);
	if ( version_D2Client >= V110 )
		msgNBPlayersString = (char*)R7(D2Client, 0000, 0000, D8448, D06A8, D4748, D4680, D4E00);

	// Set nb Player to default
	mem_seek R7(D2Client,	8723B, 865BB, 81B8B, A3602, 66A02, 90162, C39F2);//6FB1C7B7-6FAA0000
	MEMJ_REF4( D2GetResolution , caller_SendPlayersCommand);
	//6FB2723A  |. E8 7D8E0300    CALL <JMP.&D2gfx.#10005>
	//6FB265BA  |. E8 7D8E0300    CALL <JMP.&D2gfx.#10005>
	//6FB21B8A   . E8 4F9C0400    CALL <JMP.&D2gfx.#10005>
	//6FB53601  |. E8 E099F6FF    CALL <JMP.&D2gfx.#10000>
	//6FB16A01  |. E8 AA65FAFF    CALL <JMP.&D2gfx.#10063>
	//6FB40161  |. E8 1ECFF7FF    CALL <JMP.&D2gfx.#10043>
	//6FB739F1  |. E8 B896F4FF    CALL <JMP.&D2gfx.#10031>

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/


void Install_AlwaysRegenMapInSP()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2Game for always regenerate maps in Single player. (AlwaysRegenMapInSP)\n");

	// Always regenerate maps in Single player
	mem_seek R7(D2Game,	517ED,	51BFA,	5DE88, 6235D, 2966D, 1E1FE, ED3BE);
	memt_byte( 0x74 , 0xEB);		// JMP SHORT D2Game.01FE2368
	//6FC8DE88  |. 74 09          JE SHORT D2Game.6FC8DE93
	//01FE235D  |. 74 09		  JE SHORT D2Game.01FE2368
	//01F9966D  |. 74 09          JE SHORT D2Game.01F99678
	//6FC3E1FE  |. 74 09          JE SHORT D2Game.6FC3E209
	//6FD0D3BE  |. 74 09          JE SHORT D2Game.6FD0D3C9

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

void Install_RunLODs()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2gfx for launch any number of Diablo II game in the same computer. (RunLODs)\n");

	// execute if it's our packet else continue
	mem_seek R7(D2gfx, 447C, 447C, 446A, 84CF, 84AF, 894F, 85BF);
	memt_byte( 0x74, 0xEB );	// JMP SHORT D2gfx.6FA884F6
	//6FA884AF  |. 74 45          JE SHORT D2gfx.6FA884F6
	//6FA8894F  |. 74 45          JE SHORT D2gfx.6FA88996
	//6FA885BF  |. 74 45          JE SHORT D2gfx.6FA88606

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/


FCT_ASM (caller_AlwaysDisplayLife_113)
	POP EAX
	CMP onRealm,0
	JNZ normalDisplayLife
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayLife
	ADD EAX,0x28
	JMP EAX
normalDisplayLife:
	CMP EDX,0x1E
	JGE cont
	ADD EAX,0xBC
cont:
	JMP EAX
}}

FCT_ASM (caller_AlwaysDisplayLife_111)
	CMP onRealm,0
	JNZ normalDisplayLife
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayLife
	POP EAX
	ADD EAX,0x25
	JMP EAX
normalDisplayLife:
	MOV EAX,ptResolutionY
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
}}

FCT_ASM (caller_AlwaysDisplayLife)
	CMP onRealm,0
	JNZ normalDisplayLife
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayLife
	POP EAX
	ADD EAX,0x28
	JMP EAX
normalDisplayLife:
	MOV EAX,ptResolutionY
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
}}



FCT_ASM (caller_AlwaysDisplayMana_113)
	MOV EAX,DWORD PTR DS:[ptResolutionY]
	MOV EAX,DWORD PTR DS:[EAX]
	CMP onRealm,0
	JNZ normalDisplayMana
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayMana
	POP EAX
	ADD EAX,0x3C
	JMP EAX
normalDisplayMana:
	RETN
}}

FCT_ASM (caller_AlwaysDisplayMana)
	CMP onRealm,0
	JNZ normalDisplayMana
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayMana
	POP EAX
	MOV WORD PTR SS:[ESP+0x14],0
	ADD EAX,0x38
	JMP EAX
normalDisplayMana:
	POP EAX
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x25C
	RETN
}}

FCT_ASM (caller_AlwaysDisplayMana_9)
	CMP onRealm,0
	JNZ normalDisplayMana
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayMana
	ADD DWORD PTR SS:[ESP],0x32
	LEA ECX,DWORD PTR SS:[ESP+0x24]
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	CALL D2PrintString
	MOV WORD PTR SS:[ESP+0x24],0
	RETN 0xC
normalDisplayMana:
	POP EAX
	ADD EAX,0xC2
	JMP EAX
}}

void Install_AlwaysDisplayLifeMana()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for always display life and mana. (ALwaysPrintLifeMana)\n");

	if ( version_D2Client >= V113 )
	{
		mem_seek R7(D2Client, 0000, 0000, 0000, 0000, 0000, 0000, 2764A);
		memt_byte( 0x0F , 0x90);
		memt_byte( 0x8C , 0xE8);
		MEMT_REF4( 0x000000BC, caller_AlwaysDisplayLife_113);
		//6FAD764A  |. 0F8C BC000000  JL D2Client.6FAD770C
		//6FAD7650  |. 83FA 6E        CMP EDX,6E
		//6FAD7653  |. 0F8F B3000000  JG D2Client.6FAD770C
		//6FAD7659  |. A1 4CBCB86F    MOV EAX,DWORD PTR DS:[6FB8BC4C]

		//6FAD7667  |. 0F8C A4000000  JL D2Client.6FAD7711
	} else {
		// Always display life.
		mem_seek R7(D2Client, 58B32, 58B32, 5F102, 2D713, B5DF3, 81733, 0000);
		memt_byte( 0xA1 , 0xE8);
		MEMT_REF4( ptResolutionY , version_D2Client >= V111 ? caller_AlwaysDisplayLife_111 : caller_AlwaysDisplayLife);
		//6FADD713  |. A1 605CBA6F    MOV EAX,DWORD PTR DS:[6FBA5C60]
		//6FB65DF3  |. A1 C84FBA6F    MOV EAX,DWORD PTR DS:[6FBA4FC8]
		//6FB31733  |. A1 E4C6B86F    MOV EAX,DWORD PTR DS:[6FB8C6E4]
	}


	// Always display mana.
	if ( version_D2Client >= V113 )
	{
		//mem_seek R7(D2Client, 0000, 0000, 0000, 0000, 0000, 0000, 27711);
		//memt_byte( 0x8B , 0x90);
		//memt_byte( 0x0D , 0xE8);
		//MEMT_REF4( offset_D2Client + 0x11C4B4 , caller_AlwaysDisplayMana_113);
		mem_seek R7(D2Client, 0000, 0000, 0000, 0000, 0000, 0000, 2770C);
		memt_byte( 0xA1 , 0xE8);
		MEMT_REF4( ptResolutionY , caller_AlwaysDisplayMana_113);
		//6FAD770C  |> A1 4CBCB86F    MOV EAX,DWORD PTR DS:[6FB8BC4C]
		//6FAD7711  |> 8B0D B4C4BC6F  MOV ECX,DWORD PTR DS:[6FBCC4B4]

		//6FAD7708  |. 8B5424 10      MOV EDX,DWORD PTR SS:[ESP+10]

		//6FAD77C7  |> 5F             POP EDI
		//6FAD77C8  |. 5E             POP ESI
		//6FAD77C9  |. 5D             POP EBP
		//6FAD77CA  |. 5B             POP EBX
		//6FAD77CB  |. 81C4 28030000  ADD ESP,328
		//6FAD77D1  \. C3             RETN
	}
	else if ( version_D2Client >= V110 )
	{
		mem_seek R7(D2Client, 0000, 0000, 5F1E6, 2D7FB, B5EDB, 8181B, 0000);
		memt_byte( 0x5F , 0xE8);
		MEMT_REF4( 0x815B5D5E , caller_AlwaysDisplayMana);
		memt_byte( 0xC4 , 0x90);	// NOP
		memt_byte( 0x5C , 0x90);	// NOP
		memt_byte( 0x02 , 0x90);	// NOP
		memt_byte( 0x00 , 0x90);	// NOP
		memt_byte( 0x00 , 0x90);	// NOP
		//6FADD7FB  |. 5F             POP EDI
		//6FADD7FC  |. 5E             POP ESI
		//6FADD7FD  |. 5D             POP EBP
		//6FADD7FE  |. 5B             POP EBX
		//6FADD7FF  |. 81C4 5C020000  ADD ESP,25C
		//6FB65EDB  |. 5F             POP EDI
		//6FB65EDC  |. 5E             POP ESI
		//6FB65EDD  |. 5D             POP EBP
		//6FB65EDE  |. 5B             POP EBX
		//6FB65EDF  |. 81C4 5C020000  ADD ESP,25C
		//6FB3181B  |. 5F             POP EDI
		//6FB3181C  |. 5E             POP ESI
		//6FB3181D  |. 5D             POP EBP
		//6FB3181E  |. 5B             POP EBX
		//6FB3181F  |. 81C4 5C020000  ADD ESP,25C
		//6FB31825  |. C3             RETN
	} else {
		mem_seek R7(D2Client, 58C09, 58C09, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0xE9 , 0xE8);
		MEMT_REF4( 0x000000C2 , caller_AlwaysDisplayMana_9);
		//6FAF8C09   . E9 C2000000    JMP D2Client.6FAF8CD0
	}

	if (active_AlwaysDisplayLifeMana==2)
		active_AlwaysDisplayLifeMana=0;

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

void Install_EnabledTXTFilesWithMSExcel()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for enabled the opening of files already opened by MS Excel. (EnabledTXTFilesWithMSExcel)\n");

	mem_seek( (DWORD)D2StormMPQOpenFile + (version_Storm >= V111 ? 0x12A : 0xFF) );
	memt_byte( 0x01 , 0x03);	//; |ShareMode = FILE_SHARE_READ|FILE_SHARE_WRITE									
	//6FC1C969  |. 6A 01          PUSH 1        ; |ShareMode = FILE_SHARE_READ

	log_msg("\n");

	isInstalled = true;
}


/****************************************************************************************************/

void STDCALL printDisplayBaseStatsValue(WORD statID, sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6)
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
		swprintf(text, getTranslatedString(STR_STATS_BASE_MIN), statValue, minValue);
		D2SetFont(1);
		D2PrintPopup(text, x+18, y-32, WHITE, 1);
	}

	if ( D2GetPlayerBaseStat(ptChar, 4, 0) <= 0)
		setFrame(data, 2);
	D2PrintImage(data,x,y,p4,p5,p6);
}

FCT_ASM ( caller_displayBaseStatsValue )
	POP EAX
	XOR ECX,ECX
	MOV CX,WORD PTR DS:[ESI+8]
	PUSH ECX
	PUSH EAX
	JMP printDisplayBaseStatsValue
}}

void Install_DisplayBaseStatsValue()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for display base stats value. (DisplayBaseStatsValue)\n");

	// Always print stat button images.
	mem_seek R7(D2Client, 29B12, 29B02, 30073, 82BBA, 8963A, 6B59A, BD1B5);
	memt_byte( 0x8B, 0xEB );	// JMP SHORT D2Client.6FAD0088
	memt_byte( 0x4C, V7(D2Client, 12, 12, 13, 13, 13, 13, 13) );
	memt_byte( 0x24, 0x90 );	// NOP
	memt_byte( V7(D2Client, 20, 20, 14, 1C, 1C, 1C, 1C), 0x90 );			// NOP (V109d:0x20 , V110:0x14
	//6FAD0073     8B4C24 14         MOV ECX,DWORD PTR SS:[ESP+14]
	//6FB32BBA   > 8B4C24 1C         MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB3963A   > 8B4C24 1C         MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB1B59A   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB6D1B5  |> 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]

	mem_seek R7(D2Client, 29B9D, 29B8D, 300FD, 82C54, 896D4, 6B637, BD23E);
	MEMJ_REF4( D2PrintImage, caller_displayBaseStatsValue);
	//6FB32C53   . E8 82A3F8FF    CALL <JMP.&D2gfx.#10047>
	//6FB396D3   . E8 D238F8FF    CALL <JMP.&D2gfx.#10044>
	//6FB1B636   . E8 431AFAFF    CALL <JMP.&D2gfx.#10024>
	//6FB6D23D  |. E8 54FEF4FF    |CALL <JMP.&D2gfx.#10041>

	log_msg("\n");

	isInstalled = true;
}


/****************************************************************************************************/

RunesBIN* STDCALL compileRunesTxt(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	RunesBIN* ptRunesBin = (RunesBIN*)D2CompileTxtFile(unused, filename, ptFields, ptRecordCount, recordLength);
	for (DWORD i=0; i < *ptRecordCount; i++)
		ptRunesBin[i].Server=0;
	return ptRunesBin;
}

void Install_LadderRunewords()
{
	static int isInstalled = false;
	if (isInstalled) return;

	if ( version_D2Common < V110 )
		return;

	log_msg("Patch D2Common for enabled the ladder only runewords. (LadderRunewords)\n");

	mem_seek R7(D2Common, 0000, 0000, 1E965, 61762, 43A72, 5D492, 724B2);
	MEMC_REF4( D2CompileTxtFile, compileRunesTxt);
	//01B6E964  |. E8 0714FFFF    CALL D2Common.#10578                     ; \#10578
	//6FDB1761  |. E8 FAA8FCFF    CALL D2Common.#10653                     ; \#10653
	//6FD93A71  |. E8 EAADFCFF    CALL D2Common.#10496                     ; \#10496
	//6FDAD491  |. E8 BA49FEFF    CALL D2Common.#10244                     ; \#10244
	//6FDC24B1  |. E8 8ACAFEFF    CALL D2Common.#10849                     ; \#10849

	log_msg("\n");

	isInstalled = true;
}



/****************************************************************************************************/

void Install_EnabledCowPortalWhenCowKingWasKill()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Game for enabled the opening of Cow Portal when player have already kill the cow king in that difficulty. (EnabledCowPortalWhenCowKingWasKill)\n");

	mem_seek R7(D2Game, 5DFF7, 5E457, 6C5E7 , B1278, 5DB68, 75C68, 67508);
	memt_byte( 0x85 , 0x33); // XOR EAX,EAX
	//6FC8DFF7   . 85C0           TEST EAX,EAX
	//6FC8E457   . 85C0           TEST EAX,EAX
	//6FC9C5E7   . 85C0           TEST EAX,EAX
	//02061278  |. 85C0           TEST EAX,EAX
	//01FEDB68  |. 85C0           TEST EAX,EAX
	//6FC95C68  |. 85C0           TEST EAX,EAX
	//6FC87508  |. 85C0           TEST EAX,EAX

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/