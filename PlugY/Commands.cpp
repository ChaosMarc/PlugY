/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Updating server.

=================================================================*/

#include "updateServer.h"
#include "updateClient.h"
#include "infinityStash.h"
#include "newInterfaces.h"
#include "newInterface_CubeListing.h"
#include "extraOptions.h"
#include "windowed.h"
#include "common.h"

bool active_Commands=true;

bool active_listAllCubeFormula=true;
bool active_savegame=false;

#define MAX_CMD_SIZE 200

const char * CMD_SAVE="/save";
const char * CMD_SELECTPAGE="/page";

const char * CMD_LOCK_MOUSE = "/lockmouse";
const char * CMD_LOCK_MOUSE2 = "/lock";
const char * CMD_UNLOCK_MOUSE = "/unlockmouse";
const char * CMD_UNLOCK_MOUSE2 = "/unlock";

const char * CMD_RENAME_CHAR="/renamechar";

const char * CMD_REPAGE_NAME = "/renamepage";
const char * CMD_SET_INDEX = "/setindex";
const char * CMD_RESET_INDEX = "/resetindex";
const char * CMD_INSERT_PAGE = "/insertpage";
const char * CMD_DELETE_PAGE = "/deletepage";
const char * CMD_SWAP = "/swap";
const char * CMD_TOGGLE = "/toggle";

const char * CMD_DISPLAY_MANA_LIFE = "/dml";
const char * CMD_DISPLAY_LIFE_MANA = "/dlm";
const char * CMD_DISPLAY_LIFE = "/dl";
const char * CMD_DISPLAY_MANA = "/dm";

const char * CMD_LISTCUBEFORMULA="/listcube";
//const char * CMD_RELOAD="/reload";
//const char * CMD_MAXGOLD="/maxgold";


/*
$+21C8   02020648   |. 6A 01          PUSH 1
$+21CA   0202064A   |. 52             PUSH EDX
$+21CB   0202064B   |. 57             PUSH EDI
$+21CC   0202064C   |. 55             PUSH EBP
$+21CD   0202064D   |. 8BC3           MOV EAX,EBX
$+21CF   0202064F   |. E8 2CDEFFFF    CALL D2Game.0201E480
*/

/*
struct D2NPCRecordStrc
{
	DWORD	value;
};
struct D2NPCDataStrc
{
	DWORD	value;
};
D2NPCRecordStrc* __fastcall STORES_GetRecord(Game* pGame, int nNPC, int* pIndex)
{
	if (pGame == NULL)
		return NULL;

	if (pIndex != NULL)
		*pIndex = 0;

	D2NPCDataStrc* pControl = pGame->pVendorControl;
	if (pControl == NULL)
		return NULL;

	D2NPCRecordStrc* pList = pControl->pVendors;
	if (pList == NULL)
		return NULL;

	const int nCount = INLINE_GetCustomTXT()->nNPCCount;
	for (int i = 0; i < nCount; i++)
	{
		if (pList->nNPC == nNPC)
		{
			if (pIndex != NULL)
				*pIndex = i;

			return pList;
		}

		pList++;
	}

	return NULL;
}

Inventory* __fastcall STORES_GetGambleInventory(Game* pGame, Unit* pPlayer, Unit* pNPC)
{
	if (pGame == NULL || pPlayer == NULL || pNPC == NULL)
		return NULL;

	D2NPCRecordStrc* pRecord = STORES_GetRecord(pGame, pNPC->nUnitIndex, NULL);
	if (pRecord == NULL || !pRecord->bGambleInit)
		return NULL;

	D2NPCGambleStrc* pGamble = pRecord->pGamble;
	int nGUID = pPlayer->dwGUID;
	while (pGamble != NULL)
	{
		if (pGamble->dwGUID == nGUID)
			return pGamble->pInventory;

		pGamble = pGamble->pNext;
	}

	return NULL;
}

void __fastcall STORES_UpdateInventoryItems(D2UnitStrc* pNPC, D2InventoryStrc* pInventory, BOOL bPlayDropSounds = FALSE)
{

	D2UnitStrc* pItem = pInventory->pFirstItem;
	while (pItem != NULL)
	{
		if (pItem->nUnitType == UNIT_ITEM)
		{
			pItem->fUnitFlagsEx |= UNITFLAG_SHOPITEM;
			if (ITEMS_CheckSocketable(pItem))
				ITEMS_SetFlag(pItem, ITEMFLAG_NEWITEM, TRUE);

			ITEMS_UpdateTrade(pNPC->pInventory, pItem); //D2Common.#10283
			if (bPlayDropSounds)
			{
				FileItemTable* pRecord = INLINE_GetItemRecord(pItem->nUnitIndex);
				if (pRecord != NULL)
					D2PlaySound(pRecord->nDropSound, pInventory->pOwner, 0, 0, 0);
			}
		}

		pItem = pItem->pItemData->pNext;
	}
}

void gambleReload(Unit* ptChar)
{
	D2UnitStrc* pNPC = UNITS_GetServer(pGame, UNIT_MONSTER, pPacket->dwInteractGUID);
	if (pNPC != NULL)
	{
		if (pNPC->dwGUID == pPlayer->dwInteractGUID)
		{
			D2NPCRecord* pNPCRecord = NPC_GetRecord(pGame, pNPC->nUnitIndex);
			if (pNPCRecord->bGambleInit)
			{
				D2FillTradeOrGamble(pGame, pNPC, pPlayer, TRUE); //D2Game.0x6FCCAE20
				D2InventoryStrc* pInv = STORES_GetGambleInventory(pGame, pPlayer, pNPC);
				STORES_UpdateInventoryItems(pNPC, pInv, TRUE);
				D2RefreshUnitInventory(pNPC, TRUE); //D2Common.#10357
			}
		}
	}
}
*/


void gambleReload(Unit* ptChar)
{
	Unit* ptNPC = D2GetCurrentNPC();
	if (ptNPC)
	{
		D2TogglePage(0xC,1,0);
		__asm {
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
			NOP
		}
//		D2OpenNPCMenu(ptNPC);
		D2ReloadGambleScreen();
	}
}
//6FACFFD4  |. E8 77F90000    CALL D2Client.6FADF950

void savePlayers(Unit* ptChar)
{
	if (active_savegame)
		D2SaveGame(PCGame);
}

void maxGold(Unit* ptChar)
{
	log_msg("maxGold\n");

	DWORD maxGold =     D2GetMaxGold(ptChar);
	DWORD maxGoldBank = D2GetMaxGoldBank(ptChar);
	DWORD playerGold = D2GetPlayerStat(ptChar, STATS_GOLD, 0);
	DWORD playerGoldBank = D2GetPlayerStat(ptChar, STATS_GOLDBANK, 0);
	if ( (playerGold < maxGold) || (playerGoldBank < maxGoldBank) ) {
		D2AddPlayerStat( ptChar, STATS_GOLD,	 maxGold-playerGold, 0 );
		D2AddPlayerStat( ptChar, STATS_GOLDBANK, maxGoldBank-playerGoldBank, 0 );
	} else {
		D2AddPlayerStat( ptChar, STATS_GOLD,	 100000, 0 );
	}
	if (active_sharedGold)
	{
		PCPY->sharedGold = 0xFFFFFFFF;
		updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
	}
}

void putGold(Unit* ptChar, DWORD amount)
{
	if (!active_sharedGold) return;
	log_msg("putGold : %d\n", amount);

	DWORD playerGold = D2GetPlayerStat(ptChar, STATS_GOLD, 0);
	DWORD toAdd = 0xFFFFFFFF - PCPY->sharedGold;
	if (playerGold < toAdd)
		toAdd = playerGold;
	if (amount && (toAdd > amount))
		toAdd = amount;
	D2AddPlayerStat(ptChar, STATS_GOLD, 0-toAdd, 0);
	PCPY->sharedGold += toAdd;
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}

void takeGold(Unit* ptChar, DWORD amount)
{
	if (!active_sharedGold) return;
	log_msg("takeGold : %d\n", amount);

	DWORD maxGold =     D2GetMaxGold(ptChar) - D2GetPlayerStat(ptChar, STATS_GOLD, 0);
//	DWORD maxGoldBank = D2GetMaxGoldBank(ptChar) - D2GetPlayerStat(ptChar, STATS_GOLDBANK, 0);
	DWORD toAdd = maxGold < PCPY->sharedGold ? maxGold : PCPY->sharedGold;
	if (amount && (toAdd > amount))
		toAdd = amount;
	D2AddPlayerStat( ptChar, STATS_GOLD, toAdd, 0 );
	PCPY->sharedGold -= toAdd;
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}


void updateSharedGold(DWORD goldAmount)
{
	Unit* ptChar = D2GetClientPlayer();
	log_msg("SharedGold = %d\n",goldAmount);
	PCPY->sharedGold = goldAmount;
}

bool renameCharacter(Unit* ptChar, const char* newName)
{
	int len = strlen(newName);
	if (len < 2 || len > 15)
		return 0;
	for (int i = 0; i < len; i++)
	{
		char c = newName[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
			return 1;
	}
	// Move current save file
	{
		char szCurrentFile[MAX_PATH];
		char szNewFile[MAX_PATH];

		//Get temporary savefile name.
		D2FogGetSavePath(szCurrentFile, MAX_PATH);
		D2FogGetSavePath(szNewFile, MAX_PATH);
		strcat(szCurrentFile, ptChar->ptPlayerData->name);
		strcat(szNewFile, newName);
		strcat(szCurrentFile, ".");
		strcat(szNewFile, ".");
		int curLen = strlen(szCurrentFile);
		int newLen = strlen(szNewFile);
		strcpy(&szCurrentFile[curLen], "d2s");
		strcpy(&szNewFile[newLen], "d2s");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "d2x");
		strcpy(&szNewFile[newLen], "d2x");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "key");
		strcpy(&szNewFile[newLen], "key");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma0");
		strcpy(&szNewFile[newLen], "ma0");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma1");
		strcpy(&szNewFile[newLen], "ma1");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma2");
		strcpy(&szNewFile[newLen], "ma2");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma3");
		strcpy(&szNewFile[newLen], "ma3");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma4");
		strcpy(&szNewFile[newLen], "ma4");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "map");
		strcpy(&szNewFile[newLen], "map");
		MoveFile(szCurrentFile, szNewFile);
	}
	// Update server
	for (int i = 0; i <= len; i++)
		updateServer(US_RENAME + (newName[i] << 8));

	// Update client
	log_msg("Rename on Client : %s -> %s\n", ptChar->ptPlayerData->name, newName);
	strcpy(ptChar->ptPlayerData->name, newName);
	updateServer(US_SAVE);
	return 0;
}
/****************************************************************************************************/

int STDCALL commands (char* ptText)
{
	log_msg("Command : %s\n", ptText);
	Unit* ptChar = D2GetClientPlayer();

	char command[MAX_CMD_SIZE];
	ZeroMemory(command,MAX_CMD_SIZE);
	strncpy(command,ptText,MAX_CMD_SIZE-1);
	_strlwr(command);

	if (!strcmp(command, CMD_SAVE))
	{
		if (onRealm) return 1;
		updateServer(US_SAVE);
		return 0;
	}

	if (!strncmp(command, CMD_SELECTPAGE, strlen(CMD_SELECTPAGE)))
	{
		if (!active_newInterfaces) return 1;
		GoStatPage(atoi(&command[strlen(CMD_SELECTPAGE)]) - 1);
		return 0;
	}

	if (!strcmp(command, CMD_LOCK_MOUSE) || !strcmp(command, CMD_LOCK_MOUSE2))
	{
		if (onRealm) return 1;
		lockMouseCursor();
		return 0;
	}

	if (!strcmp(command, CMD_UNLOCK_MOUSE) || !strcmp(command, CMD_UNLOCK_MOUSE2))
	{
		if (onRealm) return 1;
		unlockMouseCursor();
		return 0;
	}

	if (!strncmp(command, CMD_RENAME_CHAR, strlen(CMD_RENAME_CHAR)))
	{
		const char* param = &command[strlen(CMD_RENAME_CHAR)];
		if (param[0] != ' ')
			return 1;
		param++;
		return renameCharacter(ptChar, param);
	}

	if (!strncmp(command, CMD_REPAGE_NAME,strlen(CMD_REPAGE_NAME)))
	{
		if (!active_multiPageStash) return 1;
		char* param = &command[strlen(CMD_REPAGE_NAME)];
		Stash* ptStash = PCPY->currentStash;
		if (!ptStash)
			return 0;

		int len = strlen(param);
		while (len > 0 && param[0] == ' ')
		{
			param++;
			len--;
		}
		if (len > 0 && len <= 15)
		{
			log_msg("Rename current page on Client : %s -> %s\n", ptStash->name, param);
			renameCurrentStash(ptChar, param);
			for (int i = 0; i <= len; i++)
				updateServer(US_PAGENAME + (param[i] << 8));
		}
		else if (len == 0)
		{
			log_msg("Rename current page on Client: %s\n", ptStash->name);
			renameCurrentStash(ptChar, NULL);
			updateServer(US_PAGENAME);
		}
		return 0;
	}

	if (!strcmp(command, CMD_SET_INDEX))
	{
		if (!active_multiPageStash) return 1;
		updateServer(US_SET_INDEX);
		return 0;
	}

	if (!strcmp(command, CMD_RESET_INDEX))
	{
		if (!active_multiPageStash) return 1;
		updateServer(US_RESET_INDEX);
		return 0;
	}

	if (!strcmp(command, CMD_INSERT_PAGE))
	{
		if (!active_multiPageStash) return 1;
		insertStash(ptChar);
		updateServer(US_INSERT_PAGE);
		return 0;
	}

	if (!strcmp(command, CMD_DELETE_PAGE))
	{
		if (!active_multiPageStash) return 1;
		if (deleteStash(ptChar))
			updateServer(US_DELETE_PAGE);
		return 0;
	}

	if (!strncmp(command, CMD_SWAP, strlen(CMD_SWAP)))
	{
		if (!active_multiPageStash) return 1;
		int page = atoi(&command[strlen(CMD_SWAP)]) - 1;
		if (page < 0)
			return 1;
		updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
		updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
		updateServer(US_SWAP1 + (page & 0xFF00));
		updateServer(US_SWAP0 + ((page & 0xFF) << 8));
		return 0;
	}

	if (!strncmp(command, CMD_TOGGLE, strlen(CMD_TOGGLE)))
	{
		if (!active_sharedStash) return 1;
		int page = atoi(&command[strlen(CMD_TOGGLE)]) - 1;
		if (page < 0)
			return 1;
		updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
		updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
		updateServer(US_SWAP1 + (page & 0xFF00));
		updateServer(US_SWAP0_TOGGLE + ((page & 0xFF) << 8));
		return 0;
	}

	if (!strcmp(command,CMD_DISPLAY_LIFE))
	{
		active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
		return 0;
	}

	if (!strcmp(command,CMD_DISPLAY_MANA))
	{
		active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
		return 0;
	}

	if (!strcmp(command,CMD_DISPLAY_LIFE_MANA) || !strcmp(command,CMD_DISPLAY_MANA_LIFE))
	{
		active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
		return 0;
	}

	if (!strcmp(command, CMD_LISTCUBEFORMULA))
	{
		if (!active_listAllCubeFormula) return 1;
		listAllCubeFormula();
		return 0;
	}

	//if (!strcmp(command,CMD_RELOAD))
	//{
	//	if (onRealm) return 1;
	//	gambleReload(ptChar);
	//	return 0;
	//}

	//if (!strcmp(command,CMD_MAXGOLD))
	//{
	//	if (onRealm) return 1;
	//	updateServer(US_MAXGOLD);
	//	return 0;
	//}

	return 1;
}

FCT_ASM ( caller_Commands )
	TEST EAX,EAX
	JE MANAGESOUNDCHAOSDEBUG
	PUSH DWORD PTR SS:[ESP+0x1C]
	CALL commands
	TEST EAX,EAX
	JNZ MANAGESOUNDCHAOSDEBUG
	ADD DWORD PTR SS:[ESP],7
MANAGESOUNDCHAOSDEBUG:
	RETN 8
}}

FCT_ASM ( caller_Commands_111 )
	TEST EAX,EAX
	JE MANAGESOUNDCHAOSDEBUG
	PUSH ESI
	CALL commands
	TEST EAX,EAX
	JNZ MANAGESOUNDCHAOSDEBUG
	ADD DWORD PTR SS:[ESP],7
MANAGESOUNDCHAOSDEBUG:
	RETN 8
}}

FCT_ASM ( caller_Commands_113d )
	TEST EAX,EAX
	JE MANAGESOUNDCHAOSDEBUG
	PUSH EDI
	CALL commands
	TEST EAX,EAX
	JNZ MANAGESOUNDCHAOSDEBUG
	ADD DWORD PTR SS:[ESP],7
MANAGESOUNDCHAOSDEBUG:
	RETN 8
}}


void Install_Commands()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();

	log_msg("Patch D2Client for install commands. (Commands)\n");

	active_listAllCubeFormula = version_D2Common >= V110;
	active_savegame = version_D2Common >= V111;

	// Run custom commmand
	mem_seek R7(D2Client, 2C120, 2C110, 32BDD, C1EE6, 91C16, 86926, 70AE6, B1FD6);
	memt_byte( 0x83, 0xE8 );	// CALL 
	MEMT_REF4( 0xC08508C4 , version_D2Client == V113d ? caller_Commands_113d : version_D2Client >= V111 ? caller_Commands_111 : caller_Commands);
	//6FB71EE6   . 83C4 08        ADD ESP,8
	//6FB71EE7   . 85C0           TEST EAX,EAX
	//6FB41C16  |. 83C4 08        ADD ESP,8
	//6FB41C19  |. 85C0           TEST EAX,EAX
	//6FB36926  |. 83C4 08        ADD ESP,8
	//6FB36929  |. 85C0           TEST EAX,EAX
	//6FB20AE6  |. 83C4 08        ADD ESP,8
	//6FB20AE9  |. 85C0           TEST EAX,EAX
	//6FB20AE6  |. 83C4 08        ADD ESP,8
	//6FB20AE9  |. 85C0           TEST EAX,EAX
	//6FB61FD6  |. 83C4 08        ADD ESP,8
	//6FB61FD9  |. 85C0           TEST EAX,EAX

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/