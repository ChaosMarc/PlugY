/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
	Add support 1.14d by haxifix.

	Uber Quest Management.

=================================================================*/

#include <math.h>
#include "uberQuest.h"
#include "common.h"

#define OBJECT_PERMANENT_PORTAL 0x3C
#define LEVEL_ACT5TOWN 109
#define LEVEL_ACT5_PANDEMONIUM1 133
#define LEVEL_ACT5_PANDEMONIUM2 134
#define LEVEL_ACT5_PANDEMONIUM3 135
#define LEVEL_ACT5_PANDEMONIUM_FINAL 136

#define UBER_IZUAL_ID 706
#define UBER_ANDARIEL_ID 707
#define UBER_DURIEL_ID 708
#define UBER_MEPHISTO_ID 704
#define UBER_DIABLO_ID 705
#define UBER_BAAL_ID 709

#define UBER_MEPHISTO_SQUELETON 725
#define UBER_MEPHISTO_ARCHER 726
#define UBER_MEPHISTO_FIRE 727
#define UBER_MEPHISTO_LIGHTNING 728
#define UBER_MEPHISTO_COLD 729
#define UBER_MEPHISTO_POISON 730
#define UBER_BAAL_DARK_LORD 731
#define UBER_BAAL_SPECTER 732
#define UBER_DIABLO_PIT_LORD 711


bool active_UberQuest = false;
DWORD UberMephistoX = 25130;
DWORD UberMephistoY = 5143;
DWORD UberDiabloX = 25139;
DWORD UberDiabloY = 5139;
DWORD UberBaalX = 25139;
DWORD UberBaalY = 5135;

bool active_UberMinions = true;
DWORD UberMephistoNbMinions = 6;
DWORD UberMephistoMinions[] = {UBER_MEPHISTO_SQUELETON, UBER_MEPHISTO_ARCHER, UBER_MEPHISTO_FIRE, UBER_MEPHISTO_LIGHTNING, UBER_MEPHISTO_COLD, UBER_MEPHISTO_POISON};
int UberMephistoSpawnPercent = 80;
DWORD UberMephistoSpawnRadius = 30;
DWORD UberBaalNbMinions = 2;
DWORD UberBaalMinions[] = {UBER_BAAL_DARK_LORD, UBER_BAAL_SPECTER};
int UberBaalSpawnPercent = 30;
DWORD UberBaalSpawnRadius = 30;
DWORD UberDiabloNbMinions = 1;
DWORD UberDiabloMinions[] = {UBER_DIABLO_PIT_LORD};
int UberDiabloSpawnPercent = 30;
DWORD UberDiabloSpawnRadius = 30;

bool active_UberDiabloRushTweekAI = false;
bool active_UberBaalTeleportTweekAI = false;
bool active_UberBaalChillingArmorTweekAI = false;
int uberBaalChillingArmorTimer = 6000;

int uberBaalChillingArmorLastFrame = 0;

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
} questState;


int GetNbMonsters(Level* level, Position position, int radius);
int GetNbMonsters(Level* level);

bool IsInRoom(Room* ptRoom, DWORD x, DWORD y)
{
	DWORD startX = version_D2Game > V112 ? ptRoom->startX : *((DWORD*)ptRoom + 6);
	DWORD startY = version_D2Game > V112 ? ptRoom->startY : *((DWORD*)ptRoom + 7);
	DWORD sizeX = version_D2Game > V112 ? ptRoom->sizeX : *((DWORD*)ptRoom + 8);
	DWORD sizeY = version_D2Game > V112 ? ptRoom->sizeY : *((DWORD*)ptRoom + 9);
	return x >= startX && x <= startX + sizeX &&
		y >= startY && y <= startY + sizeY;
}

double Distance(Position p1, Position p2)
{
	return sqrt((double)(p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

void resetQuestState()
{
	ZeroMemory(&questState,sizeof(questState));
	questState.count1 = 10 + RANDOM(10);
	questState.count2 = 20 + RANDOM(40);
	questState.count3 = 10 + RANDOM(20);
	uberBaalChillingArmorLastFrame = 0;
	log_msg("Uber Quest State : %d %d %d\n",questState.count1, questState.count2, questState.count3);
}

DWORD openPortalOnLevel(Game* ptGame, Unit* ptChar, DWORD levelID)
{
	log_msg("Open portal to level %d\n", levelID);
	Room* ptRoom = D2GetRoom(ptChar);
	if ( D2GetLevelID(ptRoom) != LEVEL_ACT5TOWN ) return 0;

	//Get position in the room
	Position pos;
	D2GetPosition(ptChar, &pos);
	log_msg("ptChar pos : %d %d\n", pos.x, pos.y);

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

	if (ptGame->difficultyLevel != D2DM_HELL)
		return 0;

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

	return ret;
}

DWORD FASTCALL openPandFinalPortal(Game* ptGame, Unit* ptChar)
{
	log_msg("openPandFinalPortal\n");

	if (ptGame->difficultyLevel != D2DM_HELL)
		return 0;

	return openPortalOnLevel(ptGame, ptChar, LEVEL_ACT5_PANDEMONIUM_FINAL);
}

void STDCALL spawnUber(Game* ptGame, Room* ptRoom)
{
	log_msg("Uber Quest State : %d %d %d\n",questState.count1, questState.count2, questState.count3);
	log_msg("Uber Quest questState spawn : %d %d %d %d %d %d\n",questState.uber1Spawned, questState.uber2Spawned, questState.uber3Spawned, questState.uber4Spawned, questState.uber5Spawned, questState.uber6Spawned);
	switch(D2GetLevelID(ptRoom))
	{
	case LEVEL_ACT5_PANDEMONIUM1:
		if (!questState.uber1Spawned)
		{
			if (questState.count1) questState.count1--;
			else {
				if (D2SpawnSuperUnique(ptGame, ptRoom, 0, 0, 0, -1, UBER_ANDARIEL_ID, 0))
					questState.uber1Spawned = 1;
			}
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM2:
		if (!questState.uber2Spawned)
		{
			if (questState.count2) questState.count2--;
			else {
				if (D2SpawnSuperUnique(ptGame, ptRoom, 0, 0, 0, -1, UBER_DURIEL_ID, 0))
					questState.uber2Spawned = 1;
			}
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM3:
		if (!questState.uber3Spawned)
		{
			if (questState.count3) questState.count3--;
			else {
				if (D2SpawnSuperUnique(ptGame, ptRoom, 0, 0, 0, -1, UBER_IZUAL_ID, 0))
					questState.uber3Spawned = 1;
			}
		}
		break;
	case LEVEL_ACT5_PANDEMONIUM_FINAL:
		if (!questState.uber4Spawned)
		{
			log_msg("Spawn Mephisto ptRoom: startX:%d - startY:%d / x:%d y:%d\n", ptRoom->startX, ptRoom->startY, ptRoom->sizeX, ptRoom->sizeY);
			if (IsInRoom(ptRoom, UberMephistoX, UberMephistoY))
			{
				log_msg("Spawn Mephisto ptRoom: startX:%d - startY:%d / x:%d y:%d\n", ptRoom->startX, ptRoom->startY, ptRoom->sizeX, ptRoom->sizeY);
				if (D2SpawnSuperUnique(ptGame, ptRoom, 0, UberMephistoX, UberMephistoY, -1, UBER_MEPHISTO_ID, 0))
					questState.uber4Spawned = 1;
			}
		}
		if (!questState.uber5Spawned)
		{
			if (IsInRoom(ptRoom, UberDiabloX, UberDiabloY))
			{
				log_msg("Spawn Diablo ptRoom: startX:%d - startY:%d / x:%d y:%d\n", ptRoom->startX, ptRoom->startY, ptRoom->sizeX, ptRoom->sizeY);
				if (D2SpawnSuperUnique(ptGame, ptRoom, 0, UberDiabloX, UberDiabloY, -1, UBER_DIABLO_ID, 0))
					questState.uber4Spawned = 1;
			}
		}
		if (!questState.uber6Spawned)
		{
			if (IsInRoom(ptRoom, UberBaalX, UberBaalY))
			{
				log_msg("Spawn Baal ptRoom: startX:%d - startY:%d / x:%d y:%d\n", ptRoom->startX, ptRoom->startY, ptRoom->sizeX, ptRoom->sizeY);
				if (D2SpawnSuperUnique(ptGame, ptRoom, 0, UberBaalX, UberBaalY, -1, UBER_BAAL_ID, 0))
					questState.uber4Spawned = 1;
			}
		}
	}
	D2Game235C0(ptGame, ptRoom);
}

//////////////////////////////////////////////////////////////////////////////

int GetNbMonsters(Level* level)
{
	int nbMonsters = 0;
	for (RoomEx* roomEx = level->ptFirstRoomEx; roomEx; roomEx = roomEx->ptNextRoomEx)
	{
		if (roomEx->ptRoom)
		{
			for (Unit* unit = roomEx->ptRoom->ptFirstUnit; unit; unit = unit->ptNextUnitInRoom)
			{
				if (unit->nUnitType == UNIT_MONSTER && unit->mode != UNIT_MODE_KICK && unit->nTxtFileNo != 711)
				{
					//log_msg("GetNbMonsters ++ / type:%d - id:%d - mode:%d\n", unit->nUnitType, unit->nTxtFileNo, unit->mode);
					nbMonsters++;
				}
				//else log_msg("GetNbMonsters no / type:%d - id:%d - mode:%d\n", unit->nUnitType, unit->nTxtFileNo, unit->mode);
			}
		}
	}
	return nbMonsters;
}

int GetNbMonsters(Level* level, Position position, int radius)
{
	int nbMonsters = 0;
	for (RoomEx* roomEx = level->ptFirstRoomEx; roomEx; roomEx = roomEx->ptNextRoomEx)
	{
		if (roomEx->ptRoom)
		{
			for (Unit* unit = roomEx->ptRoom->ptFirstUnit; unit; unit = unit->ptNextUnitInRoom)
			{
				if (unit->nUnitType == UNIT_MONSTER && unit->mode != UNIT_MODE_KICK && unit->nTxtFileNo != 711)
				{
					Position p;
					D2GetPosition(unit, &p);
					if (Distance(position, p) <= radius)
						nbMonsters++;
				}
			}
		}
	}
	return nbMonsters;
}

bool CastSummonMonster(Game* ptGame, Unit* ptMonster, DWORD x, DWORD y, DWORD* minions, int minionsSize, int mode)
{
	DWORD minionId = minions[RANDOM(minionsSize)];
	log_msg("CastSummonMonster: id:%d  x:%d  y:%d  mode:%d\n", minionId, x, y, mode);

	Room* ptRoom = D2GetRoom(ptMonster);

	// Check nb of monsters
	Level* ptLevel = ptRoom->ptRoomEx->ptLevel;
	int monstersInLevel = GetNbMonsters(ptLevel);
	Position position;
	D2GetPosition(ptMonster, &position);
	int monstersNearby = GetNbMonsters(ptLevel, position, 25);

	log_msg("CastSummonMonster nbMonsters: %d - %d\n", monstersNearby, monstersInLevel);
	if (monstersNearby > 16 || monstersInLevel > 100)
		return false;

	// Spawn Monster
	log_msg("CastSummonMonster D2SpawnMonster(%d, %d, %08X, %08X, %d, %d, %d, %d)\n", minionId, mode, ptGame, ptRoom, x, y, 1, 0);
	Unit* monster = D2SpawnMonster(minionId, mode, ptGame, ptRoom, x, y, 1, 0);
	log_msg("CastSummonMonster D2SpawnMonster end\n");
	if (monster)
		return true;

	// Try in near rooms
	log_msg("CastSummonMonster Try in near rooms: %d - %d\n", ptRoom->startX, ptRoom->startY);
	for(int i = 0; i < ptRoom->nbNearRooms; i++)
	{
		Room* ptRoom2 = ptRoom->ptNearRooms[i];
		if (IsInRoom(ptRoom2, x, y))
		{
			log_msg("CastSummonMonster D2SpawnMonster(%d, %d, %08X, %08X, %d, %d, %d, %d)\n", minionId, mode, ptGame, ptRoom2, x, y, 1, 0);
			monster = D2SpawnMonster(minionId, mode, ptGame, ptRoom2, x, y, 1, 0);
			log_msg("CastSummonMonster D2SpawnMonster end\n");
			if (monster)
				return true;
		}
	}
	log_msg("CastSummonMonster end: %d - %d\n", ptRoom->startX, ptRoom->startY);
	return false;
}

void RandInCircle(Position* position, DWORD radius)
{
	double theta = RANDOMF() * 6.283185;
	double r = sqrt(RANDOMF()) * radius;
	position->x += (DWORD)(r * cos(theta));
	position->y += (DWORD)(r * sin(theta));
}

void FASTCALL uberMephAI(Game* ptGame, Unit* ptMonster, AIParam* ptAIArgs)
{
	log_msg("UberMephAI called.\n");

	// Spawn Minions
	if (active_UberMinions && RANDOM(100) < UberMephistoSpawnPercent && ptAIArgs->distanceToTarget < UberMephistoSpawnRadius)
	{
		Position pos;
		D2GetPosition(ptAIArgs->target, &pos);
		CastSummonMonster(ptGame, ptMonster, pos.x, pos.y, UberMephistoMinions, UberMephistoNbMinions, 8);
	}

	log_msg("Uber Mephisto AI activated.\n");
	D2MephAI(ptGame, ptMonster, ptAIArgs);
}

void FASTCALL uberDiabloAI(Game* ptGame, Unit* ptMonster, AIParam* ptAIArgs)
{
	log_msg("UberDiabloAI called.\n");

	// Spawn Minions
	if (active_UberMinions && RANDOM(100) < UberDiabloSpawnPercent && ptAIArgs->distanceToTarget < UberDiabloSpawnRadius)
	{
		Position pos;
		D2GetPosition(ptAIArgs->target, &pos);
		RandInCircle(&pos, 3);
		CastSummonMonster(ptGame, ptMonster, pos.x, pos.y, UberDiabloMinions, UberDiabloNbMinions, 1);
	}

	// Tweek Diablo AI Rush
	if (active_UberDiabloRushTweekAI && RANDOM(100) < (int)ptAIArgs->distanceToTarget - 10)
	{
		if (RANDOM(3) > 0)//67% to Rush
		{
			log_msg("Uber Diablo Run activated.\n");
			int diabloRunSkillId = 4;
			D2MonsterUseSkill(ptGame, ptMonster, ptAIArgs->ptMonStatsBIN->skillArg[diabloRunSkillId], ptAIArgs->ptMonStatsBIN->skill[diabloRunSkillId], ptAIArgs->target, 0, 0);
		}
		else
		{
			log_msg("Uber Diablo Move activated.\n");
			Position pos;
			D2GetPosition(ptAIArgs->target, &pos);
			D2MonsterMove(ptGame, ptMonster, NULL, 2, pos.x, pos.y, 1, 0);
		}
		return;
	}

	log_msg("Uber Diablo AI activated.\n");
	D2DiabloAI(ptGame, ptMonster, ptAIArgs);
}

void FASTCALL uberBaalAI(Game* ptGame, Unit* ptMonster, AIParam* ptAIArgs)
{
	log_msg("UberBaalAI called.\n");

	if (active_UberMinions && RANDOM(100) < UberBaalSpawnPercent && ptAIArgs->distanceToTarget < UberBaalSpawnRadius)
	{
		Position pos;
		D2GetPosition(ptAIArgs->target, &pos);
		RandInCircle(&pos, 3);
		CastSummonMonster(ptGame, ptMonster, pos.x, pos.y, UberBaalMinions, UberBaalNbMinions, 1);
	}

	// Tweek Baal AI Chilling Armor
	if (active_UberBaalChillingArmorTweekAI)
	{
		if (uberBaalChillingArmorLastFrame == 0 || ((int)ptGame->gameFrame - uberBaalChillingArmorLastFrame > uberBaalChillingArmorTimer))
		{
			log_msg("Uber Baal Chilling Armor activated.\n");
			uberBaalChillingArmorLastFrame = ptGame->gameFrame;
			const int baalChillingArmorSkillId = 7;
			D2MonsterUseSkill(ptGame, ptMonster, ptAIArgs->ptMonStatsBIN->skillArg[baalChillingArmorSkillId], ptAIArgs->ptMonStatsBIN->skill[baalChillingArmorSkillId], NULL, 0, 0);
			return;
		}
	}

	// Tweek Baal AI Teleport
	if (active_UberBaalTeleportTweekAI && RANDOM(100) < (int)ptAIArgs->distanceToTarget - 10)
	{
		if (RANDOM(3) > 0)//67% to teleport
		{
			log_msg("Uber Baal Teleport activated.\n");
			const int baalTeleportSkillId = 4;
			Position pos;
			D2GetPosition(ptAIArgs->target, &pos);
			D2MonsterUseSkill(ptGame, ptMonster, ptAIArgs->ptMonStatsBIN->skillArg[baalTeleportSkillId], ptAIArgs->ptMonStatsBIN->skill[baalTeleportSkillId], NULL/*ptAIArgs->target*/, pos.x, pos.y);
		}
		else
		{
			log_msg("Uber Baal Move activated.\n");
			Position pos;
			D2GetPosition(ptAIArgs->target, &pos);
			D2MonsterMove(ptGame, ptMonster, NULL, 2, pos.x, pos.y, 1, 0);
		}
		return;
	}

	log_msg("Uber Baal AI activated.\n");
	D2BaalAI(ptGame, ptMonster, ptAIArgs);
}

FCT_ASM ( caller_spawnUber )
	PUSH EDX
	PUSH ECX
	CALL spawnUber
	RETN
}}

void Install_UberQuest()
{
	static int isInstalled = false;
	if (isInstalled) return;

	if ( version_D2Game <= V110 )
		return;

	log_msg("Patch D2Game for active Uber Quest. (UberQuest)\n");

	DWORD oldProtection;

	// open Red Portal
	VirtualProtect((LPVOID)R8(D2Game,0,0,0,FA480,FA7B8, FA228, FA5F0, FA2C4, 2E11D0), 8, PAGE_EXECUTE_READWRITE, &oldProtection);
	mem_seek R8(D2Game, 0000, 0000, 0000, FA480, FA7B8, FA228, FA5F0, FA2C4, 2E11D0);
	MEMT_DWORD( D2OpenPandPortal , openPandPortal);
	MEMT_DWORD( D2OpenPandFinalPortal , openPandFinalPortal);
	//0201E357  |. FFD0           |CALL EAX
	//01FA77E7  |. FFD0           |CALL EAX
	//6FCF3CC7  |. FFD0           |CALL EAX
	//6FC92437  |. FFD0           |CALL EAX
	//6FCB7127  |. FFD0           |CALL EAX
	//00565D45   . FFD0           CALL EAX
	VirtualProtect((LPVOID)R8(D2Game,0,0,0,FA480,FA7B8, FA228, FA5F0, FA2C4, 2E11D0), 8, oldProtection, &oldProtection);


	// manage uberIA (fct table at 0209E7E8)
	VirtualProtect((LPVOID)(R8(D2Game,0,0,0,10E7E8,10ECD0,10EF58,10E788, 10ED00, 33CA18) + 145*0x10), 0x30, PAGE_EXECUTE_READWRITE, &oldProtection);
	mem_seek R8(D2Game, 0000, 0000, 0000, 10F100, 10F5E8, 10F870, 10F0A0, 10F618, 33D330);
	MEMT_DWORD( D2UberBaalAI , uberBaalAI);
	mem_seek R8(D2Game, 0000, 0000, 0000, 10F110, 10F5F8, 10F880, 10F0B0, 10F628, 33D340);
	MEMT_DWORD( D2UberMephAI , uberMephAI);
	mem_seek R8(D2Game, 0000, 0000, 0000, 10F120, 10F608, 10F890, 10F0C0, 10F638, 33D350);
	MEMT_DWORD( D2UberDiabloAI , uberDiabloAI);
	VirtualProtect((LPVOID)(R8(D2Game,0,0,0,10E7E8,10ECD0,10EF58,10E788, 10ED00, 33CA18) + 145*0x10), 0x30, oldProtection, &oldProtection);
	//0202ADA7  |> B8 E8E70902    MOV EAX,D2Game.0209E7E8
	//01FD2BE7  |> B8 D0EC0702    MOV EAX,D2Game.0207ECD0
	//6FC3B597  |> B8 58EFD26F    MOV EAX,D2Game.6FD2EF58
	//6FCBD157  |> B8 88E7D26F    MOV EAX,D2Game.6FD2E788
	//6FC5C617  |> B8 00EDD26F    MOV EAX,D2Game.6FD2ED00
	//005B163D  |. B8 18CA7300    MOV EAX,Game.0073CA18

	// spawn Uber
//	mem_seek R7(D2Game, 0000, 0000, 0000, 98DAD, 0000, 0000, 0000);
//	MEMJ_REF4( D2WarpPlayer , spawnUber);
	//02028DAC  |. E8 491CF7FF    CALL <JMP.&D2Common.#10872>

	mem_seek R8(D2Game, 0000, 0000, 0000, E26E2, E6B52, A850B, 2CCAB, BE9AB, 12D1DC);
	MEMC_REF4( V2Game235C0 , version_D2Game >= V114d ? (DWORD)caller_spawnUber : (DWORD)spawnUber);
	//020726E1  |. E8 2A46FFFF    ||CALL D2Game.02066D10
	//02056B51  |. E8 6ACAF3FF    ||CALL D2Game.01F935C0
	//6FCC850A  |. E8 014FF6FF    ||CALL D2Game.6FC2D410
	//6FC4CCAA  |. E8 3134FFFF    ||CALL D2Game.6FC400E0
	//6FCDE9AA  |. E8 D1AFF9FF    ||CALL D2Game.6FC79980
	//0052D1DB  |. E8 60590100    ||CALL Game.00542B40

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/