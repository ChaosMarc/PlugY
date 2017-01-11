/*=================================================================
	File created by Yohann NICOLAS.

	Updating server.

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "updateServer.h"
#include "updateClient.h"
#include "infinityStash.h"
#include "newInterfaces.h"
#include "newInterface_CubeListing.h"
#include "extraOptions.h"

bool active_Commands=true;

bool active_listAllCubeFormula=true;
bool active_savegame=false;

#define MAX_CMD_SIZE 200

const char * CMD_RENAME="/rename";

const char * CMD_PAGENAME = "/pagename";
const char * CMD_LISTCUBEFORMULA="/listcube";
const char * CMD_SELECTPAGE="/page";
const char * CMD_SWAP = "/swap";
const char * CMD_TOGGLE = "/toggle";

const char * CMD_RELOAD="/reload";

const char * CMD_LOCK_MOUSE = "/lockmouse";
const char * CMD_LOCK_MOUSE2 = "/lock";

const char * CMD_STARTSAVE="/save";

const char * CMD_MAXGOLD="/maxgold";

const char * CMD_DISPLAY_MANA_LIFE = "/dml";
const char * CMD_DISPLAY_LIFE_MANA = "/dlm";
const char * CMD_DISPLAY_LIFE = "/dl";
const char * CMD_DISPLAY_MANA = "/dm";

/*
$+21C8   02020648   |. 6A 01          PUSH 1
$+21CA   0202064A   |. 52             PUSH EDX
$+21CB   0202064B   |. 57             PUSH EDI
$+21CC   0202064C   |. 55             PUSH EBP
$+21CD   0202064D   |. 8BC3           MOV EAX,EBX
$+21CF   0202064F   |. E8 2CDEFFFF    CALL D2Game.0201E480
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

/****************************************************************************************************/

int STDCALL commands (char* ptText)
{
	Unit* ptChar = D2GetClientPlayer();

	char command[MAX_CMD_SIZE];
	ZeroMemory(command,MAX_CMD_SIZE);
	strncpy(command,ptText,MAX_CMD_SIZE-1);
	_strlwr(command);

	if (!strncmp(command, CMD_RENAME, strlen(CMD_RENAME)) && ptClientNameChar != NULL)
	{
		char* param = &command[strlen(CMD_RENAME)];
		int len = strlen(param);
		if (param[0] != ' ')
			return 1;
		param++;
		len--;
		if (len < 2 || len > 15)
			return 0;
		for (int i = 0; i < len; i++)
		{
			char c = param[i];
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
			strcat(szNewFile, param);
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
		{
			updateServer(US_RENAME + (param[i] << 8));
		}

		// Update client
		log_msg("Rename on Client : %s -> %s\n", ptChar->ptPlayerData->name, param);
		strcpy(ptChar->ptPlayerData->name, param);
		strcpy(ptClientNameChar, param);
		updateServer(US_SAVE);
		return 0;
	}

	if (!strncmp(command, CMD_PAGENAME,strlen(CMD_PAGENAME)))
	{
		if (!active_multiPageStash) return 1;
		char* param = &command[strlen(CMD_PAGENAME)];
		DWORD len = strlen(param);

		Stash* ptStash = PCPY->currentStash;
		if (!ptStash) return 0;
		if (len>1 && param[0] == ' ')
		{
			D2FogMemDeAlloc(ptStash->name,__FILE__,__LINE__,0);
			ptStash->name = (char *)malloc(len);//D2FogMemAlloc(len,__FILE__,__LINE__,0);
			strcpy(ptStash->name,&param[1]);
		} else {
			D2FogMemDeAlloc(ptStash->name,__FILE__,__LINE__,0);
			ptStash->name = NULL;
		}
		return 0;
	}

	if (!strcmp(command,CMD_LISTCUBEFORMULA))
	{
		if (!active_listAllCubeFormula) return 1;
		listAllCubeFormula();
		return 0;
	}

	if (!strncmp(command,CMD_SELECTPAGE,strlen(CMD_SELECTPAGE)))
	{
		if (!active_newInterfaces) return 1;
		GoStatPage(atoi(&command[strlen(CMD_SELECTPAGE)])-1);
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

	if (!strcmp(command,CMD_RELOAD))
	{
		if (onRealm) return 1;
		gambleReload(ptChar);
		return 0;
	}

	if (!strcmp(command, CMD_LOCK_MOUSE) || !strcmp(command, CMD_LOCK_MOUSE2))
	{
		if (onRealm) return 1;
		lockMouseCursor();
		return 0;
	}

	if (!strcmp(command,CMD_STARTSAVE))
	{
		if (onRealm) return 1;
		updateServer(US_SAVE);
		return 0;
	}

	if (!strcmp(command,CMD_MAXGOLD))
	{
		if (onRealm) return 1;
		updateServer(US_MAXGOLD);
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

void Install_Commands()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();

	log_msg("Patch D2Client for install commands. (Commands)\n");

	active_listAllCubeFormula = version_D2Common >= V110;
	active_savegame = version_D2Common >= V111;

	// Run custom commmand
	mem_seek R7(D2Client, 2C120, 2C110, 32BDD, C1EE6, 91C16, 86926, 70AE6);
	memt_byte( 0x83, 0xE8 );	// CALL
	MEMT_REF4( 0xC08508C4 , version_D2Client >= V111 ? caller_Commands_111 : caller_Commands);
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

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/