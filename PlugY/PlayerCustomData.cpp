/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Adding custom data.
	Save and load infinity & shared Stash

=================================================================*/

#include "updateClient.h"
#include "infinityStash.h"
#include "savePlayerData.h" //Install_SavePlayerData()
#include "loadPlayerData.h" //Install_LoadPlayerData()
#include "common.h"

bool active_PlayerCustomData = true;
bool openSharedStashOnLoading = false;



/*********************************** UPDATING ***********************************/

Stash* getStashFromItem(Unit* ptChar, Unit* ptItem)
{
	Stash* curStash = PCPY->selfStash;
	Unit* curItem;
	while (curStash)
	{
		if (curStash == PCPY->currentStash)
			 curItem = D2InventoryGetFirstItem(PCInventory);
		else curItem = curStash->ptListItem;
		while (curItem)
		{
			if (D2GetRealItem(curItem) == ptItem) return curStash;
			curItem = D2UnitGetNextItem(curItem);
		}
		curStash = curStash->nextStash;
	}
	
	curStash = PCPY->sharedStash;
	while (curStash)
	{
		if (curStash == PCPY->currentStash)
			 curItem = D2InventoryGetFirstItem(PCInventory);
		else curItem = curStash->ptListItem;
		while (curItem)
		{
			if (D2GetRealItem(curItem) == ptItem) return curStash;
			curItem = D2UnitGetNextItem(curItem);
		}
		curStash = curStash->nextStash;
	}
	return NULL;
}


Unit* FASTCALL updateItem(Game* ptGame, DWORD type, DWORD itemNum, Unit* ptChar)
{
	Unit* ptItem = D2GameGetObject(ptGame, type, itemNum);
	if (ptGame->isLODGame && (D2ItemGetPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (!ptStash) return NULL;
		selectStash(ptChar, ptStash);
	}
	return ptItem;
}


void STDCALL updateClientPlayerOnLoading(Unit* ptChar)
{
	log_msg("--- Start updateClientPlayerOnLoading ---\n");
	if (PCGame->isLODGame)
	{
		//selectStash(ptChar, openSharedStashOnLoading ? PCPY->sharedStash : PCPY->selfStash);
		if (openSharedStashOnLoading)
			toggleToSharedStash(ptChar);
		else
			toggleToSelfStash(ptChar);
		log_msg("End update client on loading.\n\n");
	}
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}

/**************************** INIT CUSTOM DATA ****************************/

PlayerData* FASTCALL init_PlayerCustomData(DWORD p1, DWORD size, LPCSTR file, DWORD line, DWORD p5)
{
	log_msg("init_PlayerCustomData\n");
	PlayerData* playerData = (PlayerData*)D2AllocMem(p1,size+sizeof(PYPlayerData),file,line,p5);
	ZeroMemory((BYTE*)playerData + shifting.ptPYPlayerData, sizeof(PYPlayerData));
	return playerData;
}

/**************************** FREE CUSTOM DATA ****************************/


void freeStash(Stash* ptStash)
{
	if (!ptStash) return;
	freeStash(ptStash->nextStash);
	free(ptStash->nextStash);//	D2FogMemDeAlloc(ptStash->nextStash,__FILE__,__LINE__,0);
	if(ptStash->name)
	{
		free(ptStash->name);//D2FogMemDeAlloc(ptStash->name,__FILE__,__LINE__,0);
		ptStash->name = NULL;
	}
	ptStash->nextStash = NULL;
}


void FASTCALL free_PlayerCustomData(DWORD p1, PlayerData* playerData, LPCSTR file, DWORD line, DWORD p5)
{
	log_msg("free_PlayerCustomData\n");
	PYPlayerData* ptPYPlayerData = (PYPlayerData*)((DWORD)playerData + shifting.ptPYPlayerData);

	freeStash(ptPYPlayerData->selfStash);
	free(ptPYPlayerData->selfStash);//D2FogMemDeAlloc(ptPYPlayerData->selfStash,__FILE__,__LINE__,0);
	ptPYPlayerData->selfStash = NULL;

	freeStash(ptPYPlayerData->sharedStash);
	free(ptPYPlayerData->sharedStash);//D2FogMemDeAlloc(ptPYPlayerData->sharedStash,__FILE__,__LINE__,0);
	ptPYPlayerData->sharedStash = NULL;

	D2FreeMem(p1,playerData,file,line,p5);
}

Unit* STDCALL getNextItemToFree(Unit* ptChar, Unit* ptItem)
{
	Unit* item = D2UnitGetNextItem(ptItem);
	if (item) return item;

	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPlayerData) return NULL;
	if (!PCPY) return NULL;

	Stash* curStash = PCPY->selfStash;
	while ( curStash )
	{
		if (curStash->ptListItem)
		{
			item = curStash->ptListItem;
			curStash->ptListItem = NULL;
			return item;//->nUnitType == 4 ? item : NULL;
		}
		curStash = curStash->nextStash;
	}	

	curStash = PCPY->sharedStash;
	while ( curStash )
	{
		if (curStash->ptListItem)
		{
			item = curStash->ptListItem;
			curStash->ptListItem = NULL;
			return item->nUnitType == 4 ? item : NULL;
		}
		curStash = curStash->nextStash;
	}

	return NULL;
}


/************************ INSTALL PLAYER CUSTOM DATA ****************************/

void FASTCALL updateItem_111(Unit* ptItem, Unit* ptChar)
{
	if (PCGame->isLODGame && (D2ItemGetPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (ptStash)
			selectStash(ptChar, ptStash);
	}
}

FCT_ASM ( caller_updateItem_111 )
	MOV ECX,ESI
	MOV EDX,EBP
	CALL updateItem_111
	POP EAX
	MOV EDX,DWORD PTR SS:[ESP+0x18]
	PUSH EDX
	JMP EAX
}}

FCT_ASM ( caller_updateItemB_111 )
	MOV EDX,EBP
	CALL updateItem_111
	POP EAX
	MOV EDX,DWORD PTR SS:[ESP+0x18]
	PUSH EDX
	JMP EAX
}}

FCT_ASM ( caller_updateItem )
	PUSH EBP
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL updateItem
	RETN 4
}}

FCT_ASM ( caller_updateItem_9 )
	PUSH EBX
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL updateItem
	RETN 4
}}


FCT_ASM ( caller_updateClientPlayerOnLoading )
	PUSH DWORD PTR SS:[ESP+0x14]
	CALL updateClientPlayerOnLoading
	POP ECX
	POP EDI
	POP ESI
	POP EBP
	XOR EAX,EAX
	JMP ECX
}}

FCT_ASM ( callerServer_getNextItemToFree_111 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x30]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerServer_getNextItemToFree )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x28]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerServer_getNextItemToFree_9 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x1C]
	CALL getNextItemToFree
	RETN 4
}}


FCT_ASM ( callerClient_getNextItemToFree_111 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH EBX
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerClient_getNextItemToFree )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x24]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerClient_getNextItemToFree_9 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x28]
	CALL getNextItemToFree
	RETN 4
}}


void Install_PlayerCustomData()
{
	static int isInstalled = false;
	if (isInstalled || !active_PlayerCustomData) return;

	Install_SavePlayerData();
	Install_LoadPlayerData();
	Install_UpdateClient();

	log_msg("Patch D2Game & D2Client & D2Common for Player's custom data. (PlayerCustomData)\n");

	// Initialize custom data.
	mem_seek(version_D2Client == V113d ? offset_D2Common + 0x170DE : version_D2Client == V113c ?  offset_D2Common + 0x309BE : version_D2Client == V112 ? offset_D2Common + 0x585EE : version_D2Client == V111b ? offset_D2Common + 0x5BFCE : version_D2Common == V111 ? offset_D2Common + 0x4ED5E :(DWORD)D2InitPlayerData + 0x62 );
	MEMJ_REF4( D2AllocMem, init_PlayerCustomData);
	//01BD0381  |. E8 C03F0000    CALL <JMP.&Fog.#10045>
	//6FD9ED5D  |. E8 94A4FBFF    CALL <JMP.&Fog.#10045>
	//6FDABFCD  |. E8 34D2FAFF    CALL <JMP.&Fog.#10045>
	//6FDA85ED  |. E8 240CFBFF    CALL <JMP.&Fog.#10045>
	//6FD809BD  |. E8 6088FDFF    CALL <JMP.&Fog.#10045>
	//6FD670DD  |. E8 0C3EFFFF    CALL <JMP.&Fog.#10045>

	if ( version_D2Game >= V111 )
	{
		// update item
		mem_seek R7(D2Game, 10933, 10C03, 1100D, 8BC71, C3C51, 5F2A1, 9BB91, 75C81);
		memt_byte( 0x8B ,0xE8); // CALL
		MEMT_REF4( 0x52182454, caller_updateItem_111);
		//0200BC71  |> 8B5424 18      |MOV EDX,DWORD PTR SS:[ESP+18]
		//0200BC75  |. 52             |PUSH EDX                                ; /Arg1
		//02023C51  |> 8B5424 18      |MOV EDX,DWORD PTR SS:[ESP+18]
		//02023C55  |. 52             |PUSH EDX                                ; /Arg1
		//6FC7F2A1  |> 8B5424 18      |MOV EDX,DWORD PTR SS:[ESP+18]
		//6FC7F2A5  |. 52             |PUSH EDX                                ; /Arg1
		//6FCBBB91  |> 8B5424 18      |MOV EDX,DWORD PTR SS:[ESP+18]
		//6FCBBB95  |. 52             |PUSH EDX
		//6FC95C81  |> 8B5424 18      |MOV EDX,DWORD PTR SS:[ESP+18]
		//6FC95C85  |. 52             |PUSH EDX

		mem_seek R7(D2Game, 1097B, 10C4B, 11058, 8BCD1, C3CB1, 5F301, 9BBF1, 75CE1);
		memt_byte( 0x8B ,0xE8); // CALL
		MEMT_REF4( 0x52182454, caller_updateItemB_111);
		//0200BCD1  |> 8B5424 18      ||MOV EDX,DWORD PTR SS:[ESP+18]
		//0200BCD5  |. 52             ||PUSH EDX                               ; /Arg1
		//02023CB1  |> 8B5424 18      ||MOV EDX,DWORD PTR SS:[ESP+18]
		//02023CB5  |. 52             ||PUSH EDX                               ; /Arg1
		//6FC7F301  |> 8B5424 18      ||MOV EDX,DWORD PTR SS:[ESP+18]
		//6FC7F305  |. 52             ||PUSH EDX                               ; /Arg1
		//6FCBBBF1  |> 8B5424 18      ||MOV EDX,DWORD PTR SS:[ESP+18]
		//6FCBBBF5  |. 52             ||PUSH EDX
		//6FC95CE1  |> 8B5424 18      ||MOV EDX,DWORD PTR SS:[ESP+18]
		//6FC95CE5  |. 52             ||PUSH EDX

	} else {
		// update item
		mem_seek R7(D2Game, 10933, 10C03, 1100D, 8BC71, C3C51, 5F2A1, 0000, 0000);
		MEMC_REF4( D2GameGetObject, version_D2Game == V110?caller_updateItem: caller_updateItem_9);
		//6FC4100C  |. E8 EFAA0700    |CALL D2Game.6FCBBB00
		mem_seek R7(D2Game, 1097B, 10C4B, 11058, 8BCD1, C3CB1, 5F301, 0000, 0000);
		MEMC_REF4( D2GameGetObject, version_D2Game == V110?caller_updateItem: caller_updateItem_9);
		//6FC41057  |. E8 A4AA0700    ||CALL D2Game.6FCBBB00
	}

	// Update client on loading
	mem_seek R7(D2Game, 23EB, 2426, 25D4, 53482, C6A32, ED502, 4BF12, E7548);//6FC325D4-6FC30000
	memt_byte( 0x5F ,0xE8); // CALL
	MEMT_REF4( 0xC0335D5E , caller_updateClientPlayerOnLoading);
	//6FC325D4  |> 5F             POP EDI
	//6FC325D5  |. 5E             POP ESI
	//6FC325D6  |. 5D             POP EBP
	//6FC325D7  |. 33C0           XOR EAX,EAX
	//01FD3482  |> 5F             POP EDI
	//01FD3483  |. 5E             POP ESI
	//01FD3484  |. 5D             POP EBP
	//01FD3485  |. 33C0           XOR EAX,EAX
	//02026A32  |> 5F             POP EDI
	//02026A33  |. 5E             POP ESI
	//02026A34  |. 5D             POP EBP
	//02026A35  |. 33C0           XOR EAX,EAX
	//6FD0D502  |> 5F             POP EDI
	//6FD0D503  |. 5E             POP ESI
	//6FD0D504  |. 5D             POP EBP
	//6FD0D505  |. 33C0           XOR EAX,EAX
	//6FC6BF12  |> 5F             POP EDI
	//6FC6BF13  |. 5E             POP ESI
	//6FC6BF14  |. 5D             POP EBP
	//6FC6BF15  |. 33C0           XOR EAX,EAX
	//6FD07548  |> 5F             POP EDI
	//6FD07549  |. 5E             POP ESI
	//6FD0754A  |. 5D             POP EBP
	//6FD0754B  |. 33C0           XOR EAX,EAX

	// Free custom data.
	mem_seek R7(D2Common, 7055C, 7065C, 80483, 4F82D, 5C9CD, 5856D, 3093D, 1705D);
	MEMJ_REF4( D2FreeMem, free_PlayerCustomData);
	//01BD0482  |. E8 C53E0000    CALL <JMP.&Fog.#10046>
	//6FD9F82C  |. E8 E399FBFF    CALL <JMP.&Fog.#10046>
	//6FDAC9CC  |. E8 3BC8FAFF    CALL <JMP.&Fog.#10046>
	//6FDA856C  |. E8 E70CFBFF    CALL <JMP.&Fog.#10046>
	//6FD8093C  |. E8 E788FDFF    CALL <JMP.&Fog.#10046>
	//6FD6705C  |. E8 CF3EFFFF    CALL <JMP.&Fog.#10046>

	// Free item in Stash (Server-side)
	mem_seek R7(D2Game, 7D12B, 7D62B, 8D5A4, 99112, BFDB2, 94242, E1162, 6F7C2);
	MEMJ_REF4( D2UnitGetNextItem, version_D2Game >= V111 ? callerServer_getNextItemToFree_111 : version_D2Game == V110 ? callerServer_getNextItemToFree : callerServer_getNextItemToFree_9);//0x0005E204
	//6FCBD5A3   . E8 04E20500    CALL <JMP.&D2Common.#10304>
	//02019111  |. E8 5016F7FF    |CALL <JMP.&D2Common.#10934>
	//0202FDB1  |. E8 30AAF4FF    |CALL <JMP.&D2Common.#11140>
	//6FCB4241  |. E8 8862F7FF    |CALL <JMP.&D2Common.#10770>
	//6FD01161  |. E8 6693F2FF    |CALL <JMP.&D2Common.#10464>
	//6FC8F7C1  |. E8 44AEF9FF    |CALL <JMP.&D2Common.#10879>

	// Free item in Stash (Client-side)
	mem_seek R7(D2Client, 8EF8F, 8E30F, 89B32, 26404, 4C264, 1F2D4, A5C94, 621E4);//6FB29B31-6FAA0000
	MEMJ_REF4( D2UnitGetNextItem, version_D2Game >= V111 ? callerClient_getNextItemToFree_111 : version_D2Game == V110 ? callerClient_getNextItemToFree : callerClient_getNextItemToFree_9);//0x00040F34
	//6FB29B31   E8 340F0400      CALL <JMP.&D2Common.#10304>
	//6FAD6403  |. E8 925DFEFF    |CALL <JMP.&D2Common.#10934>
	//6FAFC263  |. E8 38FFFBFF    |CALL <JMP.&D2Common.#11140>
	//6FACF2D3  |. E8 4CD1FEFF    |CALL <JMP.&D2Common.#10770>
	//6FB55C93  |. E8 D068F6FF    |CALL <JMP.&D2Common.#10464>
	//6FB121E3  |. E8 7AA1FAFF    |CALL <JMP.&D2Common.#10879>

	if ( version_D2Common >= V110 )
	{
		// Test if it's already removed from inventory
		mem_seek R7(D2Common, 0000, 0000, 4E689, 26E33, 42133, 6AE93, 21B23, 3B393);
		memt_byte( 0x0D , 0x07);
		//01D2E688   75 0D            JNZ SHORT D2Common.01D2E697
		//6FD76E32  |. 74 0D          JE SHORT D2Common.6FD76E41
		//6FD92132  |. 74 0D          JE SHORT D2Common.6FD92141
		//6FDBAE92  |. 74 0D          JE SHORT D2Common.6FDBAEA1
		//6FD71B22  |. 74 0D          JE SHORT D2Common.6FD71B31
		//6FD8B392  |. 74 0D          JE SHORT D2Common.6FD8B3A1
	} else {
		mem_seek R7(D2Game, 7D176, 7D676, 0000, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0x74 , 0x90);//MOV EAX,EDI
		memt_byte( 0x35 , 0x90);//NOP
		//6FCAD176  |. 74 35          |JE SHORT D2Game.6FCAD1AD

		mem_seek R7(D2Client, 8F0CA, 8E44A, 0000, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0x0F , 0x90);//MOV EAX,EDI
		memt_byte( 0x84 , 0x90);//NOP
		memt_dword( 0x000000BF , 0x90909090);//NOP
		//6FB2F0CA  |. 0F84 BF000000  |JE D2Client.6FB2F18F

		mem_seek R7(D2Client, 8F13C, 8E4BC, 0000, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0x74 , 0x90);//MOV EAX,EDI
		memt_byte( 0x6F , 0x90);//NOP
		//6FB2F13C  |. 74 6F          |JE SHORT D2Client.6FB2F1AD
	}

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/