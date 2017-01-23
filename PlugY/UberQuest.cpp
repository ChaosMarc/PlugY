/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Uber Quest Management.

=================================================================*/

#include "uberQuest.h"
#include "common.h"

bool active_UberQuest=0;

/*
	void* ptQuest = D2GetPlayerData(ptChar)->ptQuest[ptGame->difficultyLevel];
	if (D2CheckQuestState(ptGame->game10F4[0xC],4,0xB) ||
		D2CheckQuestState(ptQuest,4,0xA) ||
		ptGame->ptIsLodGame && !D2CheckQuestState(ptQuest,0x28,0)
//		!ptGame->ptIsLodGame && D2CheckQuestState(ptQuest,0x1A,0)TODO for !ptGame->ptIsLodGame...
	{
//		d2_assert(!ptChar,"openPandPortal : ptChar==NULL",__FILE__,__LINE__);
//		ptChar->v6E = 0x14;
//		ptChar->v70 = ptChar;
//		D2Common10148(ptChar);
//		ptChar->flag400 = 1;
//		return 0;
	}
	Room* = ptRoom = D2GetRoom(ptChar);
	if (D2GetLevelID(ptRoom) != 1) return 0;
	Position pos1;
	D2GetPosition(ptChar, &pos1);
	void* ptPortal = NULL;
	D2Game02059FE0(ptRoom,&pos1,3,0x400,&ptPortal,0x64);
	if (!ptPortal) return 0;
	Position pos2;
	pos2.x = pos1.x;
	pos2.y = pos1.y;
	testing crash useless...
	D2GetDropRoom(ptRoom, &pos2, &pos2,3,0x3E01,0xC01,0);
*/

/*
void* FASTCALL D2Game01F81090(Room* ptRoom, DWORD x, DWORD y);//0x1090

*/

#define OBJECT_PERMANENT_PORTAL 0x3C
#define LEVEL_ACT5TOWN 109 
#define LEVEL_ACT5_PANDEMONIUM1 133
#define LEVEL_ACT5_PANDEMONIUM2 134
#define LEVEL_ACT5_PANDEMONIUM3 135
#define LEVEL_ACT5_PANDEMONIUM_FINAL 136

static struct
{
	union{
		DWORD all;
		struct{
			DWORD portal1Opened:1;
			DWORD portal2Opened:1;
			DWORD portal3Opened:1;
			DWORD portal4Opened:1;
			DWORD uber1Spawned:1;
			DWORD uber2Spawned:1;
			DWORD uber3Spawned:1;
			DWORD uber4Spawned:1;
			DWORD uber5Spawned:1;
			DWORD uber6Spawned:1;
		};
	};
	int count1;
	int count2;
	int count3;
	int count4;
	int count5;
	int count6;
	Room* room1;
	Room* room2;
	Room* room3;
	Room* room4;
	Room* room5;
	Room* room6;
} questState;

void resetQuestState()
{
	ZeroMemory(&questState,sizeof(questState));
	questState.count1 = 10 + RANDOM(10);
	questState.count2 = 20 + RANDOM(40);
	questState.count3 = 10 + RANDOM(20);
	int value = 5 + RANDOM(10);
	questState.count4 = value + RANDOM(4);
	questState.count5 = value + RANDOM(4);
	questState.count6 = value + RANDOM(4);
	log_msg("Uber Quest State : %d %d %d %d %d %d\n",questState.count1, questState.count2, questState.count3, questState.count4, questState.count5, questState.count6);
}

DWORD openPortalOnLevel(Game* ptGame, Unit* ptChar, DWORD levelID)
{
	log_msg("openning portal to level %d\n",levelID);
	Room* ptRoom = D2GetRoom(ptChar);
	if ( D2GetLevelID(ptRoom) != LEVEL_ACT5TOWN ) return 0;

	//Get position in the room
	Position pos;
	D2GetPosition(ptChar, &pos);
	if (!D2GetDropRoom(ptRoom, &pos, &pos, 3, 0x3E01, 0xC01, 0)) return 0;
	ptRoom = D2TestPositionInRoom(ptRoom, pos.x, pos.y);
	if (!ptRoom) return 0;

	// Create Portal
	Unit* ptPortal = D2CreateUnit(UNIT_OBJECT, OBJECT_PERMANENT_PORTAL, pos.x, pos.y, ptGame, ptRoom, 1, 1, 0);
	ptPortal->ptObjectData->levelID = (BYTE)levelID;
	D2Common10572(ptPortal, 1);
	D2LinkPortal(ptGame, ptPortal, levelID, LEVEL_ACT5TOWN);
	D2SetObjectFlags(ptPortal, D2GetObjectFlags(ptPortal) | 3);
	D2Common11084(ptRoom, 0);
	D2Common11084(D2GetRoom(ptPortal), 0);

	return 1;
}

DWORD FASTCALL openPandPortal(Game* ptGame, Unit* ptChar)
{
	log_msg("openPandPortal\n");
	Position pos;
	D2GetPosition(ptChar, &pos);
	log_msg("ptChar pos : %d %d\n",pos.x,pos.y);

	if (ptGame->difficultyLevel != D2DM_HELL) return 0;
	int available[3];
	int nbAvailable=0;
	if (!questState.portal1Opened) available[nbAvailable++]=LEVEL_ACT5_PANDEMONIUM1;
	if (!questState.portal2Opened) available[nbAvailable++]=LEVEL_ACT5_PANDEMONIUM2;
	if (!questState.portal3Opened) available[nbAvailable++]=LEVEL_ACT5_PANDEMONIUM3;
	int selectedTargetLevel;
	if (nbAvailable)
		selectedTargetLevel = available[RANDOM(nbAvailable)];
	else selectedTargetLevel = LEVEL_ACT5_PANDEMONIUM1 + RANDOM(3);

	int ret = openPortalOnLevel(ptGame, ptChar, selectedTargetLevel);


	if (ret)
	{
		if (selectedTargetLevel == LEVEL_ACT5_PANDEMONIUM1) questState.portal1Opened = 1;
		else if (selectedTargetLevel == LEVEL_ACT5_PANDEMONIUM2) questState.portal2Opened = 1;
		else if (selectedTargetLevel == LEVEL_ACT5_PANDEMONIUM3) questState.portal3Opened = 1;
	}
	log_msg("openPandPortal ending\n\n");
	return ret;//normally return ret;
}

DWORD FASTCALL openPandFinalPortal(Game* ptGame, Unit* ptChar)
{
	log_msg("openPandFinalPortal\n");
	Position pos;
	D2GetPosition(ptChar, &pos);
	log_msg("ptChar pos : %d %d",pos.x,pos.y);
	int ret = openPortalOnLevel(ptGame, ptChar, LEVEL_ACT5_PANDEMONIUM_FINAL);
	log_msg("openPandFinalPortal ending\n");
	return ret;//normally return ret;
}

Room* selectRoom(Game* ptGame, Room* ptCurrentRoom, DWORD level)
{
/*	Room* tab[200];
	nbRoom=0;
	Room* ptRoom = ptGame->mapAct[5]->ptFirstRoom;
	while (ptRoom);
	if(!ptCurrentRoom->nbNearRooms) return ptCurrentRoom;
	int targetRoomNum = RANDOM(ptCurrentRoom->nbNearRooms);
	Room* ptRoom = ptCurrentRoom->ptNearRooms;
	while (targetRoomNum--)
		ptRoom = ptRoom->ptNextRoom;*/
	return ptCurrentRoom;
}

void STDCALL spawnUber(Game* ptGame, Room* ptRoom)
{
	log_msg("Uber Quest State : %d %d %d %d %d %d\n",questState.count1, questState.count2, questState.count3, questState.count4, questState.count5, questState.count6);
	switch(D2GetLevelID(ptRoom))
	{
	case LEVEL_ACT5_PANDEMONIUM1:
		if (!questState.uber1Spawned)
		{
			if (questState.count1) questState.count1--;
			else {
				Room* ptTargetRoom = selectRoom(ptGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
				if (D2SpawnMonster(ptGame, ptTargetRoom, 0, 0, 0, -1, 707, 0))
					questState.uber1Spawned = 1;
			}
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM2:
		if (!questState.uber2Spawned)
		{
			if (questState.count2) questState.count2--;
			else {
				Room* ptTargetRoom = selectRoom(ptGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
				if (D2SpawnMonster(ptGame, ptTargetRoom, 0, 0, 0, -1, 708, 0))
					questState.uber2Spawned = 1;
			}
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM3:
		if (!questState.uber3Spawned)
		{
			if (questState.count3) questState.count3--;
			else {
				Room* ptTargetRoom = selectRoom(ptGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
				if (D2SpawnMonster(ptGame, ptTargetRoom, 0, 0, 0, -1, 706, 0))
					questState.uber3Spawned = 1;
			}
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM_FINAL:
		if (!questState.uber4Spawned)
		{
			if (questState.count4) questState.count4--;
			else {
				Room* ptTargetRoom = selectRoom(ptGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
				if (D2SpawnMonster(ptGame, ptTargetRoom, 0, 0, 0, -1, 704, 0))
					questState.uber4Spawned = 1;
			}
		}
		if (!questState.uber5Spawned)
		{
			if (questState.count5) questState.count5--;
			else {
				Room* ptTargetRoom = selectRoom(ptGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
				if (D2SpawnMonster(ptGame, ptTargetRoom, 0, 0, 0, -1, 705, 0))
					questState.uber5Spawned = 1;
			}
		}
		if (!questState.uber6Spawned)
		{
			if (questState.count6) questState.count6--;
			else {
				Room* ptTargetRoom = selectRoom(ptGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
				if (D2SpawnMonster(ptGame, ptTargetRoom, 0, 0, 0, -1, 709, 0))
					questState.uber6Spawned = 1;
			}
		}

//				D2SpawnMonster(PCGame, ptRoom, 0, 25113, 5138, -1, 704, 0);
//				D2SpawnMonster(PCGame, ptRoom, 0, 25125, 5150, -1, 705, 0);
//				D2SpawnMonster(PCGame, ptRoom, 0, 25135, 5140, -1, 709, 0);
	}
	D2Game235C0(ptGame, ptRoom);
}

/*DWORD STDCALL spawnUber(Path* ptPath, Unit* ptChar, Room* ptRoom, DWORD x, DWORD y)
{
	if (!D2WarpPlayer(ptPath, ptChar, ptRoom, x, y)) return 0;

	switch(D2GetLevelID(ptRoom))
	{
	case LEVEL_ACT5_PANDEMONIUM1:
		if (!questState.uber1Spawned)
		{
			Room* ptTargetRoom = selectRoom(PCGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
			D2SpawnMonster(PCGame, ptTargetRoom, 0, 0, 0, -1, 707, 0);
			questState.uber1Spawned = 1;
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM2:
		if (!questState.uber2Spawned)
		{
			Room* ptTargetRoom = selectRoom(PCGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
			D2SpawnMonster(PCGame, ptTargetRoom, 0, 0, 0, -1, 708, 0);
			questState.uber2Spawned = 1;
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM3:
		if (!questState.uber3Spawned)
		{
			Room* ptTargetRoom = selectRoom(PCGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
			D2SpawnMonster(PCGame, ptTargetRoom, 0, 0, 0, -1, 706, 0);
			questState.uber3Spawned = 1;
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM_FINAL:
		if (!questState.uber4Spawned)
		{
			Room* ptTargetRoom = selectRoom(PCGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
			D2SpawnMonster(PCGame, ptTargetRoom, 0, 0, 0, -1, 704, 0);
			ptTargetRoom = selectRoom(PCGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
			D2SpawnMonster(PCGame, ptTargetRoom, 0, 0, 0, -1, 705, 0);
			ptTargetRoom = selectRoom(PCGame, ptRoom, LEVEL_ACT5_PANDEMONIUM1);
			D2SpawnMonster(PCGame, ptTargetRoom, 0, 0, 0, -1, 709, 0);
//			D2SpawnMonster(PCGame, ptRoom, 0, 25113, 5138, -1, 704, 0);
//			D2SpawnMonster(PCGame, ptRoom, 0, 25125, 5150, -1, 705, 0);
//			D2SpawnMonster(PCGame, ptRoom, 0, 25135, 5140, -1, 709, 0);
			questState.uber4Spawned = 1;
		}
	}
	return 1;
}
*/
void FASTCALL uberMephIA(Game* ptGame, Unit* ptMonster, DWORD* ptData)
{
	D2MephIA(ptGame, ptMonster, ptData);
}

void FASTCALL uberDiabloIA(Game* ptGame, Unit* ptMonster, DWORD* ptData)
{
	D2DiabloIA(ptGame, ptMonster, ptData);
}


void FASTCALL uberBaalIA(Game* ptGame, Unit* ptMonster, DWORD* ptData)
{
	D2BaalIA(ptGame, ptMonster, ptData);
}

void Install_UberQuest()
{
	static int isInstalled = false;
	if (isInstalled) return;

	if ( version_D2Game <= V110 )
		return;

	log_msg("Patch D2Game for active Uber Quest. (UberQuest)\n");

	DWORD oldProtection;

	// open Red Portal
	VirtualProtect((LPVOID)R7(D2Game,0,0,0,FA480,FA7B8, FA228, FA5F0, FA2C4), 8, PAGE_EXECUTE_READWRITE, &oldProtection);
	mem_seek R7(D2Game, 0000, 0000, 0000, FA480, FA7B8, FA228, FA5F0, FA2C4);
	MEMT_DWORD( D2OpenPandPortal , openPandPortal);
	MEMT_DWORD( D2OpenPandFinalPortal , openPandFinalPortal);
	//0201E357  |. FFD0           |CALL EAX
	//01FA77E7  |. FFD0           |CALL EAX
	//6FCF3CC7  |. FFD0           |CALL EAX
	//6FC92437  |. FFD0           |CALL EAX
	//6FCB7127  |. FFD0           |CALL EAX
	VirtualProtect((LPVOID)R7(D2Game,0,0,0,FA480,FA7B8, FA228, FA5F0, FA2C4), 8, oldProtection, &oldProtection);


	// manage uberIA (fct table at 0209E7E8)
	VirtualProtect((LPVOID)(R7(D2Game,0,0,0,10E7E8,10ECD0,10EF58,10E788, 10ED00) + 145*0x10), 0x30, PAGE_EXECUTE_READWRITE, &oldProtection);
	mem_seek R7(D2Game, 0000, 0000, 0000, 10F100, 10F5E8, 10F870, 10F0A0, 10F618);
	MEMT_DWORD( D2UberBaalIA , uberBaalIA);
	mem_seek R7(D2Game, 0000, 0000, 0000, 10F110, 10F5F8, 10F880, 10F0B0, 10F628);
	MEMT_DWORD( D2UberMephIA , uberMephIA);
	mem_seek R7(D2Game, 0000, 0000, 0000, 10F120, 10F608, 10F890, 10F0C0, 10F638);
	MEMT_DWORD( D2UberDiabloIA , uberDiabloIA);
	VirtualProtect((LPVOID)(R7(D2Game,0,0,0,10E7E8,10ECD0,10EF58,10E788, 10ED00) + 145*0x10), 0x30, oldProtection, &oldProtection);
	//0202ADA7  |> B8 E8E70902    MOV EAX,D2Game.0209E7E8
	//01FD2BE7  |> B8 D0EC0702    MOV EAX,D2Game.0207ECD0
	//6FC3B597  |> B8 58EFD26F    MOV EAX,D2Game.6FD2EF58
	//6FCBD157  |> B8 88E7D26F    MOV EAX,D2Game.6FD2E788
	//6FC5C617  |> B8 00EDD26F    MOV EAX,D2Game.6FD2ED00

	// spawn Uber
//	mem_seek R7(D2Game, 0000, 0000, 0000, 98DAD, 0000, 0000, 0000);
//	MEMJ_REF4( D2WarpPlayer , spawnUber);
	//02028DAC  |. E8 491CF7FF    CALL <JMP.&D2Common.#10872>

	mem_seek R7(D2Game, 0000, 0000, 0000, E26E2, E6B52, A850B, 2CCAB, BE9AB);
	MEMC_REF4( D2Game235C0 , spawnUber);
	//020726E1  |. E8 2A46FFFF    ||CALL D2Game.02066D10
	//02056B51  |. E8 6ACAF3FF    ||CALL D2Game.01F935C0
	//6FCC850A  |. E8 014FF6FF    ||CALL D2Game.6FC2D410
	//6FC4CCAA  |. E8 3134FFFF    ||CALL D2Game.6FC400E0
	//6FCDE9AA  |. E8 D1AFF9FF    ||CALL D2Game.6FC79980

	log_msg("\n");

	isInstalled = true;
}
/*
call fct to manage TP :
0201E33E  |. 8B048D 78A4070>|MOV EAX,DWORD PTR DS:[ECX*4+207A478]    ;  D2Game.0201B480
0201E345  |. 85C0           |TEST EAX,EAX
0201E347  |. 74 14          |JE SHORT D2Game.0201E35D
0201E349  |. 8B9424 2C01000>|MOV EDX,DWORD PTR SS:[ESP+12C]
0201E350  |. 8B8C24 2801000>|MOV ECX,DWORD PTR SS:[ESP+128]
0201E357  |. FFD0           |CALL EAX
0201E359  |. 894424 38      |MOV DWORD PTR SS:[ESP+38],EAX

DWORD FASTCALL openPortal (Unit* ptGame, Unit* ptChar)
0201C6D0 : CowPortal
0201B480 : Pand. Portal return 0 !!
0201B470 : Pand. FInal Portal

manage IA
0202AD8B  |> 66:8B46 1E     MOV AX,WORD PTR DS:[ESI+1E]
0202AD8F  |. 66:85C0        TEST AX,AX
0202AD92  |. 7C 13          JL SHORT D2Game.0202ADA7
0202AD94  |. 66:3D 9400     CMP AX,94
0202AD98  |. 73 0D          JNB SHORT D2Game.0202ADA7
0202AD9A  |. 0FBFC0         MOVSX EAX,AX
0202AD9D  |. C1E0 04        SHL EAX,4
0202ADA0  |. 05 E8E70902    ADD EAX,D2Game.0209E7E8
0202ADA5  |. 5E             POP ESI
0202ADA6  |. C3             RETN
0202ADA7  |> B8 E8E70902    MOV EAX,D2Game.0209E7E8
0202ADAC  |. 5E             POP ESI
0202ADAD  \. C3             RETN
*/
/*================================= END OF FILE =================================*/