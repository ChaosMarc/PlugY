/*=================================================================
	File created by Yohann NICOLAS.

	World Event Management.

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"

#pragma pack(1)
struct s_WEdata
{
	BYTE  type;
	BYTE  fct;
	BYTE  id;
	DWORD param;
	WORD  z;
	BYTE  uk[31];
};
#pragma pack()

bool active_WorldEvent=0;

DWORD WEactive = 0;
DWORD DCloneSpawned = 0;

DWORD nbSOJSold = 0;
DWORD nbNeedSOJSold = 100;
DWORD nbManagedSOJSold = 0;

DWORD nbTicksForNextSOJSold = 0;
DWORD prevTicks = 0;

DWORD showSOJSoldCounterInAllDiff=0;
char* itemsToSell="The Stone of Jordan"; 
DWORD worldEventmonsterID = 333;
DWORD valueOfOwnSOJSold=100;
DWORD valueInitSOJSoldMin=200;
DWORD valueInitSOJSoldDelta=2000;
DWORD triggerAtSolJSoldMin=75;
DWORD triggerAtSolJSoldDelta=51;
bool active_AutomaticSell=1;
DWORD timeBeforeAutoSellMin=00000;
DWORD timeBeforeAutoSellDelta=120000;
CubeInput itemNeeded;

DWORD getTicksForNextSOJSold()
{
	return ((DWORD)(rand()/(RAND_MAX+1.0)*timeBeforeAutoSellDelta)+timeBeforeAutoSellMin);//average of +100 in 25hours max 41h40
}


void FASTCALL sendDataToClient(void* ptclient, DWORD* param)
{
	D2SendPacket(ptclient, (void*)param[0], (DWORD)param[1]);
}

void STDCALL worldEventBroadcast(Game* ptGame, DWORD activeWE, DWORD nbSOJSold)
{
	void* param[2];
	s_WEdata data;
	data.type = 0x5A;
	data.fct = activeWE ? 0x12 : 0x11;
	data.id = 4;
	data.param = nbSOJSold;
	data.z = 0;

	param[0]=&data;
	param[1]=(void*)sizeof(data);

	D2BroadcastFunction(ptGame,&sendDataToClient,param);
}

Game* STDCALL WEManagement(DWORD clientID)
{
	Game* ptGame = D2GetGameByClientID(clientID);
	if (!ptGame) return ptGame;

	if (active_AutomaticSell)
	while (GetTickCount() - prevTicks >= nbTicksForNextSOJSold)
	{
		nbSOJSold++;
		prevTicks = prevTicks + nbTicksForNextSOJSold;
		nbTicksForNextSOJSold = getTicksForNextSOJSold();
	}

	if (nbSOJSold == nbManagedSOJSold) return ptGame;

	DWORD newWE;
	if (!WEactive && (ptGame->difficultyLevel == D2DM_HELL) && (nbSOJSold >= nbNeedSOJSold))
	{
		newWE = 1;
		WEactive = 1;
	} else newWE = 0;

	if ( showSOJSoldCounterInAllDiff || (ptGame->difficultyLevel == D2DM_HELL))
		worldEventBroadcast(ptGame, newWE, nbSOJSold);

	nbManagedSOJSold = nbSOJSold;
	return ptGame;
}


DWORD FASTCALL spawnDClone(Game* ptGame, Room* ptRoom, DWORD p3, DWORD p4, DWORD p5, DWORD p6, DWORD monsterID, DWORD p8)
{
	if (WEactive && (ptGame->difficultyLevel == D2DM_HELL) && !DCloneSpawned)
	{
		DCloneSpawned=1;
		D2SpawnMonster(ptGame,ptRoom,p3,p4,p5,p6,worldEventmonsterID,p8);
		return 0;//no minions
	}
	else return D2SpawnMonster(ptGame,ptRoom,p3,p4,p5,p6,monsterID,p8);
}

DWORD STDCALL verifIfWEItem (Unit* ptItem, DWORD flags, DWORD line, const char* filename)
{
	ItemsBIN* ptItemStats = D2GetItemsBIN(ptItem->nTxtFileNo);
	ItemsBIN* ptWantedItemStats = D2GetItemsBIN(itemNeeded.ID);

	if((itemNeeded.byItemTypeID && D2CheckItemType(ptItem,itemNeeded.ID))
	|| (itemNeeded.byItemID && (itemNeeded.ID == 0xFFFF))
	|| (itemNeeded.byItemID && !itemNeeded.includeUpgradedVersions && ((DWORD)itemNeeded.ID == ptItem->nTxtFileNo))
	|| (itemNeeded.byItemID && itemNeeded.includeUpgradedVersions) && (
		  (ptItemStats->ItemCode == ptItemStats->NormCode) && (ptItemStats->ItemCode == ptWantedItemStats->NormCode)
	   || (ptItemStats->ItemCode == ptItemStats->UberCode) && (ptItemStats->ItemCode == ptWantedItemStats->NormCode)
	   || (ptItemStats->ItemCode == ptItemStats->UberCode) && (ptItemStats->ItemCode == ptWantedItemStats->UberCode)
	   || (ptItemStats->ItemCode == ptItemStats->HellCode) && (ptItemStats->ItemCode == ptWantedItemStats->NormCode)
	   || (ptItemStats->ItemCode == ptItemStats->HellCode) && (ptItemStats->ItemCode == ptWantedItemStats->UberCode)
	   || (ptItemStats->ItemCode == ptItemStats->HellCode) && (ptItemStats->ItemCode == ptWantedItemStats->HellCode)
	  ))
	if(!(itemNeeded.isSpecificItem && (D2GetUniqueID(ptItem) != itemNeeded.specificID-1))
	&& !(itemNeeded.haveNoSocket && (D2GetPlayerStat(ptItem, STATS_ITEM_NUMSOCKETS, 0) > 0))
	&& !(itemNeeded.haveSockets && (D2GetPlayerStat(ptItem, STATS_ITEM_NUMSOCKETS, 0) == 0))
	&& !(itemNeeded.isNotEthereal && D2isEtheral(ptItem))
	&& !(itemNeeded.isEthereal && !D2isEtheral(ptItem))
	&& !(itemNeeded.isBasic && (ptItemStats->ItemCode != ptWantedItemStats->NormCode))
	&& !(itemNeeded.isExceptional && (ptItemStats->ItemCode != ptWantedItemStats->UberCode))
	&& !(itemNeeded.isElite && (ptItemStats->ItemCode != ptWantedItemStats->HellCode))
	&& !(itemNeeded.isNotRuneword && ptItem->ptItemData->isRuneword) )
	{
		nbSOJSold += valueOfOwnSOJSold;
		return 1;// Can't re-buy the item.
	}

	return D2TestFlags(ptItem, flags, line, filename);
}


void initWorldEventVariables()
{
	char buf[50];
	memset(&itemNeeded,0,sizeof(itemNeeded));
	strncpy(buf,itemsToSell,50);
	D2CompileCubeInput(&itemNeeded,buf,0,0);

	nbManagedSOJSold = 0;
	DCloneSpawned = 0;
	WEactive = 0;

	while (nbSOJSold >= nbNeedSOJSold)
		nbNeedSOJSold += (DWORD)(rand()/(RAND_MAX+1.0)*triggerAtSolJSoldDelta+triggerAtSolJSoldMin);
}


FCT_ASM ( caller_WEManagement_1XX )
	POP EAX
	PUSH ECX
	PUSH EAX
	JMP WEManagement
}}


FCT_ASM ( caller_spawnDClone_111 )
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH EAX
	PUSH DWORD PTR SS:[ESP+0x18]
	PUSH DWORD PTR SS:[ESP+0x18]
	PUSH DWORD PTR SS:[ESP+0x18]
	PUSH ECX
	MOV ECX,DWORD PTR SS:[ESP+0x1C]
	CALL spawnDClone
	RETN 0x14
}}

FCT_ASM ( caller_spawnDClone_111b )
	PUSH EDX
	PUSH ECX
	PUSH DWORD PTR SS:[ESP+0x1C]
	PUSH DWORD PTR SS:[ESP+0x1C]
	PUSH DWORD PTR SS:[ESP+0x1C]
	PUSH EAX
	MOV EDX,DWORD PTR SS:[ESP+0x20]
	MOV ECX,DWORD PTR SS:[ESP+0x1C]
	CALL spawnDClone
	RETN 0x14
}}

FCT_ASM( caller_addClientForWE_111 )
	PUSH EAX
	CALL initWorldEventVariables
	POP EAX
	JMP D2AddClient
}}


FCT_ASM( caller_addClientForWE )
	PUSH ECX
	CALL initWorldEventVariables
	POP ECX
	JMP D2AddClient
}}


void Install_WorldEvent()
{
	static int isInstalled = false;
	if (isInstalled) return;

	if ( version_D2Game < V110 )
		return;

	nbSOJSold = (DWORD)(rand()/(RAND_MAX+1.0)*valueInitSOJSoldDelta+valueInitSOJSoldMin);
	if (active_AutomaticSell)
	{
		prevTicks = GetTickCount();
		nbTicksForNextSOJSold = (DWORD)(rand()/(RAND_MAX+1.0)*(timeBeforeAutoSellDelta+timeBeforeAutoSellMin));
	}

	log_msg("Patch D2Game for active World Event. (WorldEvent)\n");

	// spawn DClone
	mem_seek R7(D2Game, 0000, 0000, 3F720, 4BCB1, ECF10, 41570, 25280);
	MEMC_REF4( V2SpawnMonster , version_D2Game >= V111b ? (DWORD)caller_spawnDClone_111b : version_D2Game == V111 ? (DWORD)caller_spawnDClone_111 : (DWORD)spawnDClone);
	//6FC6F71F  |. E8 FCFAFFFF    CALL D2Game.6FC6F220
	//01FCBCB0  |. E8 2BEFFFFF    CALL D2Game.01FCABE0                     ; \D2Game.01FCABE0
	//0205CF0F  |. E8 CCF8FFFF    CALL D2Game.0205C7E0                     ; \D2Game.0205C7E0
	//6FC6156F  |. E8 1CF6FFFF    CALL D2Game.6FC60B90                     ; \D2Game.6FC60B90
	//6FC4527F  |. E8 CCF6FFFF    CALL D2Game.6FC44950                     ; \D2Game.6FC44950

	// verify if the item sold is a trigger of WE
	mem_seek R7(D2Game, 0000, 0000, 977D0, 8E799, 92859, 84499, BFB29);
	MEMJ_REF4( D2TestFlags , verifIfWEItem);
	//6FCC77CF  |. E8 32400500    CALL <JMP.&D2Common.#10707>
	//0200E798  |. E8 E9BDF7FF    CALL <JMP.&D2Common.#10911>
	//02002858  |. E8 E57DF7FF    CALL <JMP.&D2Common.#10303>
	//6FCA4498  |. E8 3B62F8FF    CALL <JMP.&D2Common.#10989>
	//6FCDFB28  |. E8 77ADF4FF    CALL <JMP.&D2Common.#10202>

	// management of the WorldEvent
	mem_seek R7(D2Game, 0000, 0000, 3CE0, 51F01, C5681, EBF41, 4A791);
	MEMC_REF4( V2GetGameByClientID , version_D2Game >= V111 ? (DWORD)WEManagement : (DWORD)caller_WEManagement_1XX);
	//6FC33CDF   . E8 FC570000    CALL D2Game.6FC394E0
	//01FD1F00  |. E8 1BE60800    CALL D2Game.02060520
	//02035680  |. E8 1BF30100    CALL D2Game.020549A0
	//6FD0BF40  |. E8 1BA4FBFF    CALL D2Game.6FCC6360
	//6FC6A790  |. E8 4B03FEFF    CALL D2Game.6FC4AAE0

	// add client for the WorldEvent
	mem_seek R7(D2Game, 0000, 0000, 1AEF, 3786A, 7055A, 6265F, CB0BF);
	MEMC_REF4( D2AddClient , version_D2Game >= V111 ? caller_addClientForWE_111 : caller_addClientForWE);
	//6FC31AEE  |. E8 6D510000    CALL D2Game.6FC36C60
	//01FB7869  |. E8 32C50A00    CALL D2Game.02063DA0
	//01FE0559  |. E8 B27C0700    CALL D2Game.02058210
	//6FC8265E  |. E8 FD890800    CALL D2Game.6FD0B060
	//6FCEB0BE  |. E8 6DE8F7FF    CALL D2Game.6FC69930

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/