/*======================================================================
	File created by Yohann NICOLAS.

  Declares the type for a STDCALL or FASTCALL function pointer
  called N with arguments list P, returning R, namedInDLL D and at @A

======================================================================*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2Common :
////D2S(D2Common,10001,	DWORD,		D2GetActIDFromLevel, (DWORD levelID));
//D2S(D2Common,11084,	DWORD,		D2Common11084, (Room* ptRoom, DWORD zero));//use only in 1.11/1.11b
//D2S(D2Common,11021,	DWORD,		D2GetLevelID, (Room* ptRoom));//1.11b
//D2S(D2Common,10491,	Room*,		D2GetDropRoom, (Room* ptRoom, Position*, Position*, DWORD, DWORD, DWORD, DWORD));//1.11b
////D2S(D2Common,10149,	Inventory*,	D2GetInventory, (Unit* ptUnit));
//D2S(D2Common,10242,	Unit*,		D2Common10242, (Inventory* ptInventory, Unit* ptItem, DWORD bIsClient));
//D2S(D2Common,10813,	Unit*,		D2CanPutItemInInv, (Inventory* ptInventory, Unit* ptItem, DWORD p3, DWORD zero, Unit* ptUnit, const char* file, DWORD line));//ONLY 1.11b
//D2S(D2Common,10827,	Unit*,		D2InvRemoveItem, (Inventory* ptInventory, Unit* ptItem));//ONLY 1.11b
//D2S(D2Common,11068,	DWORD,		D2InvAddItem, (Inventory* ptInventory, Unit* ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));//ONLY 1.11b result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
//D2S(D2Common,10250,	DWORD,		D2Common10250, (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));// result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
////D2S(D2Common,10257,	Unit*,		D2GetItemFromBodyLoc, (Inventory* ptInventory, DWORD bodyloc));
//D2S(D2Common,10273,	DWORD,		D2Common10273, (Inventory* ptInventory, void* unknow));
//D2S(D2Common,10535,	Unit*,		D2InventoryGetFirstItem, (Inventory* ptInventory));//ONLY 1.11b
//D2S(D2Common,11140,	Unit*,		D2UnitGetNextItem, (Unit* ptItem));//ONLY 1.11b
//D2S(D2Common,10748,	Unit*,		D2GetRealItem, (Unit* ptUnit));//ONLY 1.11b
////D2S(D2Common,10321,	SkillData*,	D2GetLeftSkill, (Unit* ptChar));
////D2S(D2Common,10322,	SkillData*,	D2GetRightSkill, (Unit* ptChar));
//D2S(D2Common,10326,	DWORD,		D2GetPosX, (Unit* ptUnit));//NOT IN 1.10
////D2S(D2Common,10328,	void,		D2SetPosX, (Unit* ptUnit, DWORD pos));
//D2S(D2Common,10329,	DWORD,		D2GetPosY, (Unit* ptUnit));//NOT IN 1.10
////D2S(D2Common,10331,	void,		D2SetPosY, (Unit* ptUnit, DWORD pos));
//D2S(D2Common,10056,	void,		D2GetPosition, (Unit* ptUnit, Position* pos));//1.11b
//D2S(D2Common,10864,	DWORD,		D2GetMaxGoldBank, (Unit* ptUnit));//1.11b
//D2S(D2Common,10933,	Room*,		D2GetRoom, (Unit* ptUnit));//1.11b
////D2S(D2Common,10348,	void,		D2SetUnitMode, (Unit* ptUnit, DWORD mode));
//D2S(D2Common,10394,	ObjectsBIN*,D2GetObjectsBIN, (Unit* ptObject));
//D2S(D2Common,10079,	PlayerData*,D2InitPlayerData, (Unit* ptChar));//1.11b
//D2S(D2Common,10329,	DWORD,		D2FreePlayerData, (DWORD game1C, Unit* ptChar));//1.11b
//D2S(D2Common,10800,	PlayerData*,D2GetPlayerData, (Unit* ptChar));//ONLY 1.11b
//D2S(D2Common,10431,	DWORD,		D2GetDefence, (Unit* ptChar));
//D2S(D2Common,10433,	DWORD,		D2GetChanceToBlock, (Unit* ptChar, DWORD isLODGame));
//D2S(D2Common,11131,	DWORD,		D2GetMaxGold, (Unit* ptUnit));//1.11b
//D2S(D2Common,10572,	DWORD,		D2Common10572, (Unit* ptObject, DWORD value));//use only in 1.11/1.11b
////D2S(D2Common,10463,	DWORD,		D2SetStatWithNoTest, ( Stats* ptStats, DWORD statID, DWORD statValue, DWORD statIndex));
////D2S(D2Common,10464,	void,		D2AddStat, (Stats* ptStats, DWORD statID, DWORD statValue, DWORD statIndex));
////D2S(D2Common,10465,	DWORD,		D2SetStat, (Stats* ptStats, DWORD statID, DWORD statValue, DWORD statIndex));
////D2S(D2Common,10466,	int,		D2GetStat, (Stats* ptStats, DWORD statID, DWORD statIndex));
////D2S(D2Common,10470,	Stats*,		D2AllocNewStats, (DWORD nUnitId, DWORD flags, DWORD uk18, DWORD nUnitType, DWORD nItemNum));
//D2S(D2Common,11160,	BYTE,		D2GetObjectFlags, (Unit* ptObject));
//D2S(D2Common,11048,	void,		D2SetObjectFlags, (Unit* ptObject, BYTE flags));
////D2S(D2Common,10471,	DWORD,		D2Common10471, (void*));//UNTL 1.10
////D2S(D2Common,10472,	DWORD,		D2Common10472, (void*));
////D2S(D2Common,10475,	void,		D2UpdateDisabledStat, (Stats* ptCharStats, Stats* ptStats, DWORD one));
////D2S(D2Common,10481,	void*,		D2Common10481, (Unit* ptUnit, DWORD flags));
////D2S(D2Common,10484,	Stats*,		D2GetAffixStats, (Unit* ptItem, DWORD, DWORD));
////D2S(D2Common,10485,	void,		D2FreeStats, (Stats* ptStats));
//D2S(D2Common,10487,	DWORD,		D2isInState, (Unit* ptChar, DWORD isLODGame));
////D2S(D2Common,10517,	void,		D2SetPlayerStat, (Unit* ptChar, DWORD statID, int amount, DWORD index));
//D2S(D2Common,10627,	void,		D2AddPlayerStat, (Unit* ptChar, DWORD statID, int amount, DWORD index));//ONLY 1.11b
//D2S(D2Common,10061,	int,		D2GetPlayerStat, (Unit* ptChar, DWORD statID, DWORD index));//ONLY 1.11b
////D2S(D2Common,10520,	int,		D2GetPlayerStat20, (Unit* ptChar, DWORD statID, DWORD index));
//D2S(D2Common,10550,	int,		D2GetPlayerBaseStat, (Unit* ptChar, DWORD statID, DWORD index));//ONLY 1.11b
////D2S(D2Common,10527,	DWORD,		D2Common10527, (Unit* ptUnit));
//D2S(D2Common,10539,	DWORD,		D2haveDefenceBonus, (Unit* ptChar));
//D2S(D2Common,10540,	DWORD,		D2haveFireResBonus, (Unit* ptChar));
//D2S(D2Common,10541,	DWORD,		D2haveColdResBonus, (Unit* ptChar));
//D2S(D2Common,10542,	DWORD,		D2haveLightResBonus, (Unit* ptChar));
//D2S(D2Common,10543,	DWORD,		D2havePoisonResBonus, (Unit* ptChar));
//D2S(D2Common,10546,	DWORD,		D2haveDefenceMalus, (Unit* ptChar));
//D2S(D2Common,10547,	DWORD,		D2haveFireResMalus, (Unit* ptChar));
//D2S(D2Common,10548,	DWORD,		D2haveColdResMalus, (Unit* ptChar));
//D2S(D2Common,10549,	DWORD,		D2haveLightResMalus, (Unit* ptChar));
//D2S(D2Common,10550,	DWORD,		D2havePoisonResMalus, (Unit* ptChar));
////D2S(D2Common,10552,	DWORD,		D2Common10552, (Unit* ptUnit));
////D2S(D2Common,10567,	DWORD,		D2CanBeBroken, (Unit* ptItem));
////D2S(D2Common,10573,	void,		D2CopyStats, (Stats* ptDestStats, Stats* ptSrcStats));
////D2S(D2Common,10574,	void*,		D2SetEnabledStat, (Unit* ptItem, DWORD statId, DWORD disabled));
////D2S(D2Common,10575,	void,		D2FreeBinFiles, ());
////D2S(D2Common,10576,	void,		D2LoadBinFiles, (DWORD zero1, DWORD zero2, bool));
////D2S(D2Common,10651,	DWORD,		D2CheckQuestState, (void* ptQuest, DWORD index, DWORD value));//ONLY 1.11
//D2S(D2Common,10496,	void*,		D2CompileTxtFile, (DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength));//ONLY 1.11b
//D2S(D2Common,10262,	ItemsBIN*,	D2GetItemsBIN, (DWORD itemID));//ONLY 1.11b
////D2S(D2Common,10601,	ItemsBIN*,	D2GetByCodeItemStatsBIN, (DWORD code, DWORD* itemID));
////D2S(D2Common,10604,	AffixBIN*,	D2GetAffixBIN, (int affixID));
//D2S(D2Common,10523,	GemsBIN*,	D2GetGemsBIN, (DWORD gemID));//1.11b
//D2S(D2Common,10258,	CubeMainBIN*,D2GetCubeMainBIN, (DWORD cubemainID));//ONLY 1.11b
//D2S(D2Common,11135,	int,		D2GetNbCubeMainBIN, ());//ONLY 1.11b
////D2S(D2Common,10737,	LevelsBIN*,	D2GetLevelsBIN, (DWORD levelID));
//D2S(D2Common,10628,	DWORD,		D2GetNextLevelXP, (DWORD classID, DWORD level));
//D2S(D2Common,10629,	DWORD,		D2GetMaxLevel, (DWORD classID));
//D2S(D2Common,10309,	DifficultyLevelsBIN*,	D2GetDifficultyLevelsBIN, (DWORD difficultyLevel));
////D2S(D2Common,10659,	TreasureClassBIN*,		D2GetTreasureClassBIN, (WORD id, DWORD uk));
////D2S(D2Common,10953,	SuperUniqueBIN*,		D2GetSuperUniqueBIN, (WORD id));//1.11b
//D2S(D2Common,10899,	DWORD,		D2GetItemQuality, (Unit* ptItem));//1.11b
//D2S(D2Common,10303,	DWORD,		D2TestFlags, (Unit* ptUnit, DWORD flags, DWORD line, const char* file));//ONLY 1.11b
////D2S(D2Common,10708,	void,		D2SetFlags, (Unit* ptUnit, DWORD flags, DWORD bitNewValue));
////D2S(D2Common,10709,	DWORD,		D2GetFlags, (Unit* ptUnit));
////D2S(D2Common,10711,	void,		D2ItemSetFlags, (Unit* ptItem, DWORD flags, DWORD toSet));// toSet = 0 for set to 0 the selected flags else set to 1
//D2S(D2Common,10100,	DWORD,		D2GetItemLevel, (Unit* ptItem));//ONLY 1.11b
//D2S(D2Common,10505,	BYTE,		D2ItemGetPage, (Unit* ptUnit));//ONLY 1.11b
//D2S(D2Common,10608,	void,		D2ItemSetPage, (Unit* ptItem, BYTE page));//ONLY 1.11b
//D2S(D2Common,10890,	DWORD,		D2CheckItemType, (Unit* ptItem, DWORD itype));//ONLY 1.11b
//D2S(D2Common,10685,	int,		D2GetUniqueID, (Unit* ptItem));//1.11b
//D2S(D2Common,10734,	void,		D2SetAnim, (Unit* ptUnit, int anim));
////D2S(D2Common,10749,	void,		D2GetWidthHeight, (Unit* ptItem, BYTE* Width, BYTE* Height);
////D2S(D2Common,10751,	DWORD,		D2GetItemType, (Unit* ptUnit));
////D2S(D2Common,10757,	DWORD,		D2GetItemLevelReq, (Unit* ptChar, Unit* ptItem));
//D2S(D2Common,10877,	int*,		D2GetNbRunesBIN, ());//ONLY 1.11b //return the point on th number
//D2S(D2Common,10296,	RunesBIN*,	D2GetRunesBIN, (int runesID));//ONLY 1.11b
////D2S(D2Common,10792,	DWORD,		D2CanBeRare, (Unit* ptItem));
////D2S(D2Common,10810,	BYTE,		D2CheckHasInv, (Unit* ptItem));
////D2S(D2Common,10813,	DWORD,		D2GetStaffMods, (Unit* ptItem));
////D2S(D2Common,11085,	DWORD,		D2GetNbSocket, (Unit* ptItem));//1.11b
////D2S(D2Common,10840,	DWORD,		D2Common10840, (Unit* ptItem, Unit* ptChar));
////D2S(D2Common,10855,	void,		D2AddAffix, (DWORD, DWORD, Unit* ptItem, AffixBIN* ptAffix, DWORD, DWORD));
////D2S(D2Common,10872,	DWORD,		D2WarpPlayer, (Path* ptPath, Unit* ptChar, Room* ptRoom, DWORD x, DWORD y));
////D2S(D2Common,10875,	WORD,		D2GetItemVersion, (Unit* ptItem));
//D2S(D2Common,11068,	DWORD,		D2isEtheral, (Unit* ptItem));//ONLY UNTIL 1.10 //1.11b
//D2S(D2Common,11156,	DWORD,		D2SaveItem, (Unit* ptItem, saveBitField* data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6));//1.11b
////D2S(D2Common,10916,	void,		DoNothing916, ());
////D2S(D2Common,10105,	void,		D2Common10027, (Unit* ptChar, DWORD skillID));//ONLY 1.11b
////D2S(D2Common,10950,	SkillData*,	D2GetSkillPointer, (Unit* ptChar, WORD SkillID));
////D2S(D2Common,10256,	SkillData*,	D2IncSkillBaseLevel, (Unit* ptChar, DWORD skillID));//ONLY 1.11b
//D2S(D2Common,10255,	void,		D2SetSkillBaseLevel,(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));//ONLY 1.11b
////D2S(D2Common,10963,	DWORD,		D2GetSkillID, (SkillData* ptSkill, const char* file, DWORD line));
////D2F(D2Common,10966,	SkillsBIN*,	D2GetSkillsBIN, (SkillData* ptSkill));
//D2S(D2Common,10109,	DWORD,		D2GetSkillLevel, (Unit* ptChar, SkillData* ptSkill, DWORD includingBonus));//ONLY 1.11b
////D2S(D2Common,11023,	DWORD,		D2GetCriticalStrikeFromMasteries, (Unit* ptChar, Unit* ptItem, DWORD zero, DWORD two));
////D2S(D2Common,11007,	bool,		D2TestQuestState, (void* ptQuest, DWORD QuestID, DWORD QuestState));
////D2S(D2Common,11041,	int,		D2GetPlayerSkillID, (DWORD playerID, DWORD skillNumber));
////D2S(D2Common,11042,	int,		D2GetNbSkillsPerPlayer, (DWORD playerID));
////D2S(D2Common,11269,	DWORD,		D2GetAllIndexFromStat, (Stats* ptStats, DWORD statID, D2Stat* allIndex, DWORD maxIndex));
////D2S(D2Common,11270,	DWORD,		D2GetAllIndexFromStatID, (Unit* ptItem, DWORD statID, D2Stat* allIndex, DWORD));
//D2S(D2Common,10074,	DWORD,		D2GetSkillCost, (Unit* ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel));//ONLY 1.11b (not 10447)
//E2F(D2Common,1800,	CharStatsBIN*,	D2GetCharStatsBIN, (DWORD charID));//1.11b /NOT in 1.10
//E2F(D2Common,1A100,	DWORD,			D2CompileCubeInput, (CubeInput* cubeinput, char* s, DWORD p1, DWORD p2));//1.11b
//E2F(D2Common,19B40,	DWORD,			D2CompileCubeOutput, (CubeOutput* cubeoutput, char* s, DWORD p1, DWORD p2));//1.11b
//E2F(D2Common,1380,	ItemTypesBIN*,	D2GetItemTypesBIN, (DWORD itemTypesId));//ONLY 1.11b
////E2F(D2Common,62FD0,	void,			D2EncodeValueCheckMax, (saveBitField* data, DWORD value, DWORD bitSize));
//E2F(D2Common,12F0,	ItemStatCostBIN*, D2GetItemStatCostBIN, (DWORD id));//ONLY 1.11b
////E2F(D2Common,764A0,	void*,			D2Common764A0, (Stats* ptStats, DWORD stat, ItemStatCostBIN* itemStatCost ,DWORD));
////E2S(D2Common,76E30,	void,			D2PreUpdateDisabledStat, (Stats* ptStats));
////E2F(D2Common,76C10,	void,			D2ApplyStat,(Stats* ptCharStats, DWORD statId, DWORD value, Unit* ptItem));
//E2F(D2Common,98D0,	void*,			D2ReadFile,(DWORD unused, char* filename, DWORD* size, const char*, DWORD));//1.11b
////E2F(D2Common,94D0,	void*,			D2GetStringIDForTxtFile,(const char * string));
//E2S(D2Common,32AA0,	void,			D2LoadSuperuniques,(DWORD mempool));//FASCALL UNTIL 1.10 (1.11b)



//F7(STD,  D2Common,00000,00000,00000,00000,10001,00000,00000,	DWORD,		D2GetActIDFromLevel, (DWORD levelID));
F7(STD,  D2Common,00000,00000,00000,10188,11084,11109,10346,	DWORD,		D2Common11084, (Room* ptRoom, DWORD zero));
F7(STD,  D2Common,10057,10057,10057,10332,11021,10511,10826,	DWORD,		D2GetLevelID, (Room* ptRoom));
F7(STD,  D2Common,10138,10138,10138,10623,10491,11043,10654,	Room*,		D2GetDropRoom, (Room* ptRoom, Position*, Position*, DWORD, DWORD, DWORD, DWORD));
//F7(STD,  D2Common,10149,10149,10149,00000,00000,00000,00000,	Inventory*,	D2GetInventory, (Unit* ptUnit));
F7(STD,  D2Common,10242,10242,10242,00000,00000,00000,00000,	Unit*,		D2Common10242, (Inventory* ptInventory, Unit* ptItem, DWORD bIsClient));
F7(STD,  D2Common,10246,10246,10246,10855,10813,10289,10133,	Unit*,		D2CanPutItemInInv, (Inventory* ptInventory, Unit* ptItem, DWORD p3, DWORD zero, Unit* ptUnit, const char* file, DWORD line));
F7(STD,  D2Common,10243,10243,10243,10461,10827,10936,10646,	Unit*,		D2InvRemoveItem, (Inventory* ptInventory, Unit* ptItem));
F7(STD,  D2Common,10249,10249,10249,10880,11068,10436,11107,	DWORD,		D2InvAddItem, (Inventory* ptInventory, Unit* ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));//result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
F7(STD,  D2Common,10250,10250,10250,00000,00000,00000,00000,	DWORD,		D2Common10250, (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));// result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
//F7(STD,  D2Common,10257,10257,10257,00000,00000,00000,00000,	Unit*,		D2GetItemFromBodyLoc, (Inventory* ptInventory, DWORD bodyloc));
F7(STD,  D2Common,10273,10273,10273,00000,00000,00000,00000,	DWORD,		D2Common10273, (Inventory* ptInventory, void* unknow));
F7(STD,  D2Common,10277,10277,10277,10402,10535,11151,10460,	Unit*,		D2InventoryGetFirstItem, (Inventory* ptInventory));
F7(STD,  D2Common,10304,10304,10304,10934,11140,10770,10464,	Unit*,		D2UnitGetNextItem, (Unit* ptItem));
F7(STD,  D2Common,10305,10305,10305,11095,10748,10852,11147,	Unit*,		D2GetRealItem, (Unit* ptUnit));
//F7(STD,  D2Common,10321,10321,10321,00000,00000,00000,00000,	SkillData*,	D2GetLeftSkill, (Unit* ptChar));
//F7(STD,  D2Common,10322,10322,10322,00000,00000,00000,00000,	SkillData*,	D2GetRightSkill, (Unit* ptChar));
F7(STD,  D2Common,10326,10326,00000,00000,00000,00000,00000,	DWORD,		D2GetPosX, (Unit* ptUnit));//NOT IN 1.10
//F7(STD,  D2Common,10328,10328,10328,00000,00000,00000,00000,	void,		D2SetPosX, (Unit* ptUnit, DWORD pos));
F7(STD,  D2Common,10329,10329,00000,00000,00000,00000,00000,	DWORD,		D2GetPosY, (Unit* ptUnit));//NOT IN 1.10
//F7(STD,  D2Common,10331,10331,10331,00000,00000,00000,00000,	void,		D2SetPosY, (Unit* ptUnit, DWORD pos));
F7(STD,  D2Common,10332,10332,10332,11080,10056,10543,10141,	void,		D2GetPosition, (Unit* ptUnit, Position* pos));
F7(STD,  D2Common,10339,10339,10339,10455,10864,10941,11060,	DWORD,		D2GetMaxGoldBank, (Unit* ptUnit));
F7(STD,  D2Common,10342,10342,10342,10172,10933,10366,10331,	Room*,		D2GetRoom, (Unit* ptUnit));
//F7(STD,  D2Common,10348,10348,10348,00000,00000,00000,00000,	void,		D2SetUnitMode, (Unit* ptUnit, DWORD mode));
//F7(STD,  D2Common,10394,10394,10394,00000,00000,00000,00000,	ObjectsBIN*,D2GetObjectsBIN, (Unit* ptObject));
F7(STD,  D2Common,10420,10420,10420,10218,10079,11097,10356,	PlayerData*,D2InitPlayerData, (Unit* ptChar));
//F7(STD,  D2Common,10421,10421,10421,10914,10329,00000,00000,	DWORD,		D2FreePlayerData, (DWORD game1C, Unit* ptChar));
F7(STD,  D2Common,10424,10424,10424,10562,10800,10860,10920,	PlayerData*,D2GetPlayerData, (Unit* ptChar));
F7(STD,  D2Common,10431,10431,10431,00000,00000,00000,00000,	DWORD,		D2GetDefence, (Unit* ptChar));
F7(STD,  D2Common,10433,10433,10433,00000,00000,00000,00000,	DWORD,		D2GetChanceToBlock, (Unit* ptChar, DWORD isLODGame));
F7(STD,  D2Common,10439,10439,10439,10343,11131,10729,10049,	DWORD,		D2GetMaxGold, (Unit* ptUnit));
F7(STD,  D2Common,00000,00000,00000,10440,10572,10481,11090,	DWORD,		D2Common10572, (Unit* ptObject, DWORD value));
//F7(STD,  D2Common,10463,10463,10463,00000,00000,00000,00000,	DWORD,		D2SetStatWithNoTest, ( Stats* ptStats, DWORD statID, DWORD statValue, DWORD statIndex));
//F7(STD,  D2Common,10464,10464,10464,00000,00000,00000,00000,	void,		D2AddStat, (Stats* ptStats, DWORD statID, DWORD statValue, DWORD statIndex));
//F7(STD,  D2Common,10465,10465,10465,00000,00000,00000,00000,	DWORD,		D2SetStat, (Stats* ptStats, DWORD statID, DWORD statValue, DWORD statIndex));
//F7(STD,  D2Common,10466,10466,10466,00000,00000,00000,00000,	int,		D2GetStat, (Stats* ptStats, DWORD statID, DWORD statIndex));
//F7(STD,  D2Common,10470,10470,10470,00000,00000,00000,00000,	Stats*,		D2AllocNewStats, (DWORD nUnitId, DWORD flags, DWORD uk18, DWORD nUnitType, DWORD nItemNum));
F7(STD,  D2Common,00000,00000,00000,10471,11160,10866,10258,	BYTE,		D2GetObjectFlags, (Unit* ptObject));
F7(STD,  D2Common,00000,00000,00000,10572,11048,10150,10111,	void,		D2SetObjectFlags, (Unit* ptObject, BYTE flags));
//F7(STD,  D2Common,10471,10471,10471,00000,00000,00000,00000,	DWORD,		D2Common10471, (void*));
//F7(STD,  D2Common,10472,10472,10472,00000,00000,00000,00000,	DWORD,		D2Common10472, (void*));
//F7(STD,  D2Common,10475,10475,10475,00000,00000,00000,00000,	void,		D2UpdateDisabledStat, (Stats* ptCharStats, Stats* ptStats, DWORD one));
//F7(STD,  D2Common,10481,10481,10481,00000,00000,00000,00000,	void*,		D2Common10481, (Unit* ptUnit, DWORD flags));
//F7(STD,  D2Common,10484,10484,10484,00000,00000,00000,00000,	Stats*,		D2GetAffixStats, (Unit* ptItem, DWORD, DWORD));
//F7(STD,  D2Common,10485,10485,10485,00000,00000,00000,00000,	void,		D2FreeStats, (Stats* ptStats));
F7(STD,  D2Common,10487,10487,10487,00000,00000,00000,00000,	DWORD,		D2isInState, (Unit* ptChar, DWORD isLODGame));
//F7(STD,  D2Common,10517,10517,10517,00000,00000,00000,00000,	void,		D2SetPlayerStat, (Unit* ptChar, DWORD statID, int amount, DWORD index));
F7(STD,  D2Common,10518,10518,10518,10109,10627,10762,10551,	void,		D2AddPlayerStat, (Unit* ptChar, DWORD statID, int amount, DWORD index));//ONLY 1.11b
F7(STD,  D2Common,10519,10519,10519,11092,10061,10658,10973,	int,		D2GetPlayerStat, (Unit* ptChar, DWORD statID, DWORD index));//ONLY 1.11b
//F7(STD,  D2Common,10520,10520,10520,00000,00000,00000,00000,	int,		D2GetPlayerStat20, (Unit* ptChar, DWORD statID, DWORD index));
F7(STD,  D2Common,10521,10521,10521,10733,10550,10494,10587,	int,		D2GetPlayerBaseStat, (Unit* ptChar, DWORD statID, DWORD index));//ONLY 1.11b
//F7(STD,  D2Common,10527,10527,10527,00000,00000,00000,00000,	DWORD,		D2Common10527, (Unit* ptUnit));
F7(STD,  D2Common,10539,10539,10539,00000,00000,00000,00000,	DWORD,		D2haveDefenceBonus, (Unit* ptChar));
F7(STD,  D2Common,10540,10540,10540,00000,00000,00000,00000,	DWORD,		D2haveFireResBonus, (Unit* ptChar));
F7(STD,  D2Common,10541,10541,10541,00000,00000,00000,00000,	DWORD,		D2haveColdResBonus, (Unit* ptChar));
F7(STD,  D2Common,10542,10542,10542,00000,00000,00000,00000,	DWORD,		D2haveLightResBonus, (Unit* ptChar));
F7(STD,  D2Common,10543,10543,10543,00000,00000,00000,00000,	DWORD,		D2havePoisonResBonus, (Unit* ptChar));
F7(STD,  D2Common,10546,10546,10546,00000,00000,00000,00000,	DWORD,		D2haveDefenceMalus, (Unit* ptChar));
F7(STD,  D2Common,10547,10547,10547,00000,00000,00000,00000,	DWORD,		D2haveFireResMalus, (Unit* ptChar));
F7(STD,  D2Common,10548,10548,10548,00000,00000,00000,00000,	DWORD,		D2haveColdResMalus, (Unit* ptChar));
F7(STD,  D2Common,10549,10549,10549,00000,00000,00000,00000,	DWORD,		D2haveLightResMalus, (Unit* ptChar));
F7(STD,  D2Common,10550,10550,10550,00000,00000,00000,00000,	DWORD,		D2havePoisonResMalus, (Unit* ptChar));
//F7(STD,  D2Common,10552,10552,10552,00000,00000,00000,00000,	DWORD,		D2Common10552, (Unit* ptUnit));
//F7(STD,  D2Common,10567,10567,10567,00000,00000,00000,00000,	DWORD,		D2CanBeBroken, (Unit* ptItem));
//F7(STD,  D2Common,10573,10573,10573,00000,00000,00000,00000,	void,		D2CopyStats, (Stats* ptDestStats, Stats* ptSrcStats));
//F7(STD,  D2Common,10574,10574,10574,00000,00000,00000,00000,	void*,		D2SetEnabledStat, (Unit* ptItem, DWORD statId, DWORD disabled));
//F7(STD,  D2Common,10575,10575,10575,00000,00000,00000,00000,	void,		D2FreeBinFiles, ());
//F7(STD,  D2Common,10576,10576,10576,00000,00000,00000,00000,	void,		D2LoadBinFiles, (DWORD zero1, DWORD zero2, bool));
//F7(STD,  D2Common,00000,00000,00000,10651,10651,00000,00000,	DWORD,		D2CheckQuestState, (void* ptQuest, DWORD index, DWORD value));
F7(STD,  D2Common,10578,10578,10578,10653,10496,10244,10849,	void*,		D2CompileTxtFile, (DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength));
F7(STD,  D2Common,10600,10600,10600,10573,10262,10887,10695,	ItemsBIN*,	D2GetItemsBIN, (DWORD itemID));
//F7(STD,  D2Common,10601,10601,10601,00000,00000,00000,00000,	ItemsBIN*,	D2GetByCodeItemStatsBIN, (DWORD code, DWORD* itemID));
//F7(STD,  D2Common,10604,10604,10604,00000,00000,00000,00000,	AffixBIN*,	D2GetAffixBIN, (int affixID));
F7(STD,  D2Common,10616,10616,10616,10500,10523,10774,10806,	GemsBIN*,	D2GetGemsBIN, (DWORD gemID));
F7(STD,  D2Common,11232,11232,11232,10746,10258,10913,10783,	CubeMainBIN*,D2GetCubeMainBIN, (DWORD cubemainID));
F7(STD,  D2Common,11233,11233,11233,10639,11135,10390,10675,	int,		D2GetNbCubeMainBIN, ());
//F7(STD,  D2Common,10737,10737,10737,00000,00000,00000,00000,	LevelsBIN*,	D2GetLevelsBIN, (DWORD levelID));
F7(STD,  D2Common,10628,10628,10628,00000,00000,00000,00000,	DWORD,		D2GetNextLevelXP, (DWORD classID, DWORD level));
F7(STD,  D2Common,10629,10629,10629,00000,00000,00000,00000,	DWORD,		D2GetMaxLevel, (DWORD classID));
F7(STD,  D2Common,10655,10655,10655,10655,10309,10297,10218,	DifficultyLevelsBIN*,	D2GetDifficultyLevelsBIN, (DWORD difficultyLevel));
//F7(STD,  D2Common,10659,10659,10659,00000,00000,00000,00000,	TreasureClassBIN*,		D2GetTreasureClassBIN, (WORD id, DWORD uk));
//F7(STD,  D2Common,10668,10668,10668,10450,10953,00000,00000,	SuperUniqueBIN*,		D2GetSuperUniqueBIN, (WORD id));
F7(STD,  D2Common,10695,10695,10695,10927,10899,10276,10106,	DWORD,		D2GetItemQuality, (Unit* ptItem));
F7(STD,  D2Common,10707,10707,10707,10911,10303,10989,10202,	DWORD,		D2TestFlags, (Unit* ptUnit, DWORD flags, DWORD line, const char* file));
//F7(STD,  D2Common,10708,10708,10708,00000,00000,00000,00000,	void,		D2SetFlags, (Unit* ptUnit, DWORD flags, DWORD bitNewValue));
//F7(STD,  D2Common,10709,10709,10709,00000,00000,00000,00000,	DWORD,		D2GetFlags, (Unit* ptUnit));
//F7(STD,  D2Common,10711,10711,10711,00000,00000,00000,00000,	void,		D2ItemSetFlags, (Unit* ptItem, DWORD flags, DWORD toSet));// toSet = 0 for set to 0 the selected flags else set to 1
F7(STD,  D2Common,10717,10717,10717,10898,10100,10410,10086,	DWORD,		D2GetItemLevel, (Unit* ptItem));
F7(STD,  D2Common,10719,10719,10719,10820,10505,10370,10020,	BYTE,		D2ItemGetPage, (Unit* ptUnit));
F7(STD,  D2Common,10720,10720,10720,10485,10608,10223,10012,	void,		D2ItemSetPage, (Unit* ptItem, BYTE page));
F7(STD,  D2Common,10731,10731,10731,11017,10890,10231,10744,	DWORD,		D2CheckItemType, (Unit* ptItem, DWORD itype));
F7(STD,  D2Common,10732,10732,10732,10692,10685,10280,10620,	int,		D2GetUniqueID, (Unit* ptItem));
F7(STD,  D2Common,10734,10734,10734,00000,00000,00000,00000,	void,		D2SetAnim, (Unit* ptUnit, int anim));
//F7(STD,  D2Common,10749,10749,10749,00000,00000,00000,00000,	void,		D2GetWidthHeight, (Unit* ptItem, BYTE* Width, BYTE* Height);
//F7(STD,  D2Common,10751,10751,10751,00000,00000,00000,00000,	DWORD,		D2GetItemType, (Unit* ptUnit));
//F7(STD,  D2Common,10757,10757,10757,00000,00000,00000,00000,	DWORD,		D2GetItemLevelReq, (Unit* ptChar, Unit* ptItem));
F7(STD,  D2Common,10619,10619,10619,10687,10877,10321,11032,	int*,		D2GetNbRunesBIN, ());//return the point on th number
F7(STD,  D2Common,10620,10620,10620,10775,10296,10622,10006,	RunesBIN*,	D2GetRunesBIN, (int runesID));
//F7(STD,  D2Common,10792,10792,10792,00000,00000,00000,00000,	DWORD,		D2CanBeRare, (Unit* ptItem));
//F7(STD,  D2Common,10810,10810,10810,00000,00000,00000,00000,	BYTE,		D2CheckHasInv, (Unit* ptItem));
//F7(STD,  D2Common,10813,10813,10813,00000,00000,00000,00000,	DWORD,		D2GetStaffMods, (Unit* ptItem));
//F7(STD,  D2Common,10816,10816,10816,10816,11085,00000,00000,	DWORD,		D2GetNbSocket, (Unit* ptItem));
//F7(STD,  D2Common,10840,10840,10840,00000,00000,00000,00000,	DWORD,		D2Common10840, (Unit* ptItem, Unit* ptChar));
//F7(STD,  D2Common,10855,10855,10855,00000,00000,00000,00000,	void,		D2AddAffix, (DWORD, DWORD, Unit* ptItem, AffixBIN* ptAffix, DWORD, DWORD));
//F7(STD,  D2Common,10872,10872,10872,00000,00000,00000,00000,	DWORD,		D2WarpPlayer, (Path* ptPath, Unit* ptChar, Room* ptRoom, DWORD x, DWORD y));
//F7(STD,  D2Common,10875,10875,10875,00000,00000,00000,00000,	WORD,		D2GetItemVersion, (Unit* ptItem));
F7(STD,  D2Common,11163,11163,11163,10880,11068,10436,11107,	DWORD,		D2isEtheral, (Unit* ptItem));//ONLY UNTIL 1.10
F7(STD,  D2Common,10881,10881,10881,10956,11156,10218,10987,	DWORD,		D2SaveItem, (Unit* ptItem, saveBitField* data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6));
//F7(STD,  D2Common,10916,10916,10916,00000,00000,00000,00000,	void,		DoNothing916, ());
//F7(STD,  D2Common,10940,10940,10940,10027,10105,10953,00000,	void,		D2Common10027, (Unit* ptChar, DWORD skillID));
//F7(STD,  D2Common,10950,10950,10950,00000,00000,00000,00000,	SkillData*,	D2GetSkillPointer, (Unit* ptChar, WORD SkillID));
//F7(STD,  D2Common,10952,10952,10952,10950,10256,10858,00000,	SkillData*,	D2IncSkillBaseLevel, (Unit* ptChar, DWORD skillID));
F7(STD,  D2Common,10953,10953,10953,10099,10255,10210,10302,	void,		D2SetSkillBaseLevel,(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
//F7(STD,  D2Common,10963,10963,10963,00000,00000,00000,00000,	DWORD,		D2GetSkillID, (SkillData* ptSkill, const char* file, DWORD line));
//F7(FAST, D2Common,10966,10966,10966,00000,00000,00000,00000,	SkillsBIN*,	D2GetSkillsBIN, (SkillData* ptSkill));
F7(STD,  D2Common,10968,10968,10968,10700,10109,10904,10306,	DWORD,		D2GetSkillLevel, (Unit* ptChar, SkillData* ptSkill, DWORD includingBonus));
//F7(STD,  D2Common,11023,11023,11023,00000,00000,00000,00000,	DWORD,		D2GetCriticalStrikeFromMasteries, (Unit* ptChar, Unit* ptItem, DWORD zero, DWORD two));
//F7(STD,  D2Common,11007,11007,11007,00000,00000,00000,00000,	bool,		D2TestQuestState, (void* ptQuest, DWORD QuestID, DWORD QuestState));
//F7(STD,  D2Common,11041,11041,11041,00000,00000,00000,00000,	int,		D2GetPlayerSkillID, (DWORD playerID, DWORD skillNumber));
//F7(STD,  D2Common,11042,11042,11042,00000,00000,00000,00000,	int,		D2GetNbSkillsPerPlayer, (DWORD playerID));
//F7(STD,  D2Common,11269,11269,11269,00000,00000,00000,00000,	DWORD,		D2GetAllIndexFromStat, (Stats* ptStats, DWORD statID, D2Stat* allIndex, DWORD maxIndex));
//F7(STD,  D2Common,11270,11270,11270,00000,00000,00000,00000,	DWORD,		D2GetAllIndexFromStatID, (Unit* ptItem, DWORD statID, D2Stat* allIndex, DWORD));
F7(STD,  D2Common,11276,11276,11276,10254,10074,10111,10435,	DWORD,		D2GetSkillCost, (Unit* ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel));//not 10447
A7(FAST, D2Common,00000,00000,82C80, 15D0, 1800, 1220, 12D0,	CharStatsBIN*,	D2GetCharStatsBIN, (DWORD charID));
A7(FAST, D2Common,00000,00000,12410,5D7D0,1A100,116C0,1C020,	DWORD,			D2CompileCubeInput, (CubeInput* cubeinput, char* s, DWORD p1, DWORD p2));
A7(FAST, D2Common,00000,00000,12910,5D210,19B40,11100,1BA60,	DWORD,			D2CompileCubeOutput, (CubeOutput* cubeoutput, char* s, DWORD p1, DWORD p2));
A7(FAST, D2Common,00000,00000,2B1A0, 11F0, 1380, 1140, 1300,	ItemTypesBIN*,	D2GetItemTypesBIN, (DWORD itemTypesId));
//A7(FAST, D2Common,00000,00000,62FD0,00000,00000,00000,00000,	void,			D2EncodeValueCheckMax, (saveBitField* data, DWORD value, DWORD bitSize));
A7(FAST, D2Common,00000,00000,642B0, 13F0, 12F0, 1540, 17A0,	ItemStatCostBIN*,D2GetItemStatCostBIN, (DWORD id));
//A7(FAST, D2Common,00000,00000,764A0,00000,00000,00000,00000,	void*,			D2Common764A0, (Stats* ptStats, DWORD stat, ItemStatCostBIN* itemStatCost ,DWORD));
//A7(STD,  D2Common,00000,00000,76E30,00000,00000,00000,00000,	void,			D2PreUpdateDisabledStat, (Stats* ptStats));
//A7(FAST, D2Common,00000,00000,76C10,00000,00000,00000,00000,	void,			D2ApplyStat,(Stats* ptCharStats, DWORD statId, DWORD value, Unit* ptItem));
A7(FAST, D2Common,738A4,739B4,84268, 96E0, 98D0, 9900, 9900,	void*,			D2ReadFile,(DWORD unused, char* filename, DWORD* size, const char*, DWORD));
//A7(FAST, D2Common,00000,00000, 94D0,00000,00000,00000,00000,	void*,			D2GetStringIDForTxtFile,(const char * string));
A7(STD,  D2Common,1F500,1F510,29FA0,71EB0,32AA0,7D2A0,59870,	void,			D2LoadSuperuniques,(DWORD mempool));//FASCALL UNTIL 1.10


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2Client : 6FAA0000
//E2F(D2Client,A9070,	void*,		D2LoadImage, (const char* filename, DWORD filetype));//1.11
//E2F(D2Client,0000,	void,		D2FreeImage, (void* image));//6FAA1140 // NOT IN 1.11
//E2F(D2Client,5E4E0,	void,		D2SendMsgToAll,(BYTE* data));//1.11 and 1.11b by ESI !!
////E2S(D2Client,15A80,	int,		D2GetAvgChanceMonsterWillHitYou, ());//6FAB5A80
//E2S(D2Client,15A80,	DWORD,		D2GetLastMonsterIDFight, ());//6FAB5A80
//E2S(D2Client,89320,	void,		D2PrintStatsPage, ());//ONLY 1.11b
////E2F(D2Client,45990,	Unit*,		D245990, (Inventory*,DWORD idItem);//6FAE5990
//E2F(D2Client,21250,	DWORD,		D2PrintStat,(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText));//statID=EAX, lpText=ESI 1.11b
//E2F(D2Client,62070,	LPWSTR,		D2SetColorPopup, (LPWSTR popupText, DWORD color));//1.11 and 1.11b BY EDI
////E2F(D2Client,869F0,	Unit*,		D2ClientGetObject, (DWORD itemNum, DWORD type));//6FB269F0
//E2F(D2Client,54210,	DWORD,		D2PlaySound, (DWORD id, DWORD, DWORD, DWORD, DWORD));//1.11b
////E2F(D2Client,BB0F0,	void,		D2FillRect,(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl));//UNITL 1.10
//E2F(D2Client,571C0,	Unit*,		D2GetCurrentNPC, ());//1.11b
//E2F(D2Client,5DE40,	void,		D2SendToServerXX,(DWORD size, BYTE * data));//ONLY 1.11b by EBX
//E2F(D2Client,65690,	void,		D2TogglePage, (DWORD a, DWORD b, DWORD c));//1.11b
//E2F(D2Client,710C0,	void,		D2ClickOnStashButton, (DWORD x, DWORD y));//STRICT 1.11/1.11b BY x=ESI y=EDI
//E2S(D2Client,621C0,	void*,		D2LoadBuySelBtn, ());//1.11b
//E2F(D2Client,5BA90,	void,		D2ReloadGambleScreen, ());//1.11b
//E2F(D2Client,1FEB0,	void,		D2OpenNPCMenu, (Unit* ptNPC));//1.11b by ESI

A7(FAST, D2Client, 1000, 1000, 1000,75D00,A9070,BEF70,2B420,	void*,		D2LoadImage, (const char* filename, DWORD filetype));
A7(FAST, D2Client, 1150, 1150, 1140,00000,00000,00000,00000,	void,		D2FreeImage, (void* image));//6FAA1140
A7(FAST, D2Client, D640, D630, DB50,73620,5E4E0,79670,147A0,	void,		D2SendMsgToAll,(BYTE* data));//1.11 and 1.11b by ESI !!
//A7(STD,  D2Client,00000,00000,15A80,00000,00000,00000,00000,	int,		D2GetAvgChanceMonsterWillHitYou, ());//6FAB5A80
A7(STD,  D2Client,00000,00000,15A80,00000,00000,00000,00000,	DWORD,		D2GetLastMonsterIDFight, ());//6FAB5A80
A7(STD,  D2Client,29800,297F0,2FD60,828A0,89320,6B280,BCEA0,	void,		D2PrintStatsPage, ());
//A7(FAST, D2Client,00000,00000,45990,00000,00000,00000,00000,	Unit*,		D245990, (Inventory*,DWORD idItem);//6FAE5990
A7(FAST, D2Client,4BB20,4BB20,521C0,B8CB0,21250,88EA0,54E10,	DWORD,		D2PrintStat,(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText));//statID=EAX, lpText=ESI 1.11b
A7(FAST, D2Client,85A60,84DE0,80430,9EEB0,62070,8B7A0,BF5F0,	LPWSTR,		D2SetColorPopup, (LPWSTR popupText, DWORD color));//1.11 and 1.11b BY EDI
//A7(FAST, D2Client,00000,00000,869F0,00000,00000,00000,00000,	Unit*,		D2ClientGetObject, (DWORD itemNum, DWORD type));//6FB269F0
A7(FAST, D2Client,B4360,B36E0,B5820,3ACC0,54210,31FA0,88A70,	DWORD,		D2PlaySound, (DWORD id, DWORD, DWORD, DWORD, DWORD));
//A7(FAST, D2Client,B9970,B8CF0,BB0F0,00000,00000,00000,00000,	void,		D2FillRect,(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl));
A7(FAST, D2Client,00000,00000,00000,00000,571C0,18450,46150,	Unit*,		D2GetCurrentNPC, ());
A7(FAST, D2Client,00000,00000,00000,73260,5DE40,791A0,143E0,	void,		D2SendToServerXX,(DWORD size, BYTE * data));//by EBX
A7(FAST, D2Client,88940,87CC0,83260,A1F30,65690,8EF00,C2790,	void,		D2TogglePage, (DWORD a, DWORD b, DWORD c));
A7(FAST, D2Client,00000,00000,00000,A6520,710C0,A6640,8CD00,	void,		D2ClickOnStashButton, (DWORD x, DWORD y));//BY x=ESI y=EDI
A7(STD,  D2Client,897B0,88B30,84110,9E3B0,621C0,8B8F0,BEAF0,	void*,		D2LoadBuySelBtn, ());
A7(FAST, D2Client,00000,00000,00000,8E480,5BA90,1CC00,4ABE0,	void,		D2ReloadGambleScreen, ());
//A7(FAST, D2Client,00000,00000,00000,00000,1FEB0,5CDD0,00000,	void,		D2OpenNPCMenu, (Unit* ptNPC));//by ESI


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2Game : 6FC30000
//D2F(D2Game,10007,	void,		D2SetNbPlayers, (DWORD nbPlayers));//1.11b
////E2F(D2Game,01DE0,	void*,		D2GetClientByClientID, (Game* ptGame, DWORD clientID));//6FC31DE0
//E2F(D2Game,E8210,	void,		D2AddClient, (DWORD clientID));//BY EAX //1.11b
//E2S(D2Game,E49A0,	Game*,		D2GetGameByClientID, (DWORD clientID));//6FC394E0 //1.11b
//E2F(D2Game,E36D0,	void,		D2BroadcastFunction, (Game* ptGame, void* fct, void* param));//00DAB0E0//1.11b
//E2F(D2Game,A0D50,	DWORD,		D2SendPacket, (void* ptNetClient, LPVOID pData, DWORD size));//EAX=ptNetClient [ESP]=pData //1.11b
//E2F(D2Game,A3F20,	void,		D2SetSkillBaseLevelOnClient, (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove));//ONLY 1.11 by EAX,ESI,EBX
////E2F(D2Game,0E6F0,	void,		D2UpdateClientItem, (NetClient*	ptNetClient, Unit* ptChar, Unit* ptItem,DWORD,DWORD,DWORD));//6FC3E6F0
////E2F(D2Game,10FB0,	DWORD,		D2UpdateInventory, (Game* ptGame, Unit* ptChar, void* ptNetClient, Inventory* pInventory));//6FC40FB0
////E2F(D2Game,110E0,	DWORD,		D2UpdateItem, (Unit* ptChar, Unit* ptItem, Unit* ptSocketedItem, void* ptNetClient));//6FC410E0
//E2S(D2Game,109F0,	DWORD,		D2LinkPortal, (Game* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID));//ONLY 1.11b
//E2F(D2Game,43E60,	DWORD,		D2VerifIfNotCarry1, (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem));// BY EBX=itemsData EAX=ptFirstItem [ESP]=ptItem//1.11b
////E2F(D2Game,1ED80,	Unit*,		D2CreateItem, (Game* ptGame, ItemGenerationData* itemGenerationData, DWORD));//6FC4ED80
//E2F(D2Game,01DF0,	Room*,		D2TestPositionInRoom, (Room* ptRoom, DWORD x, DWORD y));//1.11b
////E2F(D2Game,22410,	void,		D2AddStaffModAffixes, (Unit* ptItem, ItemGenerationData* itemParam));//6FC52410
////E2F(D2Game,22C00,	WORD,		D2GetNewAffix, (Unit* ptItem, DWORD testIfSpawnable, DWORD mustSelectOne, DWORD addToItem, DWORD isPrefix, int affixID, WORD autoAffixGroupID));//6FC52C00
////E2F(D2Game,23610,	WORD,		D2GetRareAffixName, (Unit* ptItem, DWORD wantPrefix));//6FC53610
////E2F(D2Game,3AD10,	DWORD,		D2GetSuperUniqueMonsterID, (Game* ptGame, Unit* ptMonster));//6FC6AD10
//E2F(D2Game,EC7E0,	DWORD,		D2SpawnMonster, (Game* ptGame, Room* ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2));//1.11b (wrong param)
//E2S(D2Game,235C0,	void,		D2Game235C0, (Game* ptGame, Room* ptRoom));//1.11/1.11b
//E2F(D2Game,4C7B0,	Unit*,		D2GetSkillItem, (Unit* ptChar));//6FC7C7B0
////E2F(D2Game,5A500,	DWORD,		D2SavePlayer, (Game* ptGame, Unit* ptChar, char* playername, DWORD zero));//6FC8A500
//E2F(D2Game,25D50,	DWORD,		D2LoadInventory, (Game* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead));//6FC8B8A0//1.11b
//E2F(D2Game,BEF80,	Unit*,		D2GameGetObject, (Game* ptGame, DWORD type, DWORD itemNum));//6FCBBB00//1.11b
//E2F(D2Game,F1C50,	Unit*,		D2GetOwnerMonster, (Unit* ptMonster));//ONLY 1.11b
////E2F(D2Game,E08D0,	void,		D2UpdateSkillDataAfterUnassignment, (Game* ptGame, Unit* ptChar, DWORD skillID));//6FD108D0
//E2F(D2Game,C09E0,	Unit*,		D2CreateUnit, (DWORD type, DWORD id, DWORD x, DWORD y, Game* ptGame, Room* ptRoom, DWORD uk1, DWORD uk2, DWORD uk3));//1.11b
//E2F(D2Game,34920,	void,		D2OpenPandPortal, (Game* ptGame, Unit* ptChar));//1.11b
//E2F(D2Game,34910,	void,		D2OpenPandFinalPortal, (Game* ptGame, Unit* ptChar));//1.11b
//E2F(D2Game,85AA0,	void,		D2MephIA, (Game* ptGame, Unit* ptMonster, DWORD*));//1.11b
//E2F(D2Game,D7BD0,	void,		D2DiabloIA, (Game* ptGame, Unit* ptMonster, DWORD*));//1.11b
//E2F(D2Game,2BC80,	void,		D2BaalIA, (Game* ptGame, Unit* ptMonster, DWORD*));//1.11b
//E2F(D2Game,D2D70,	void,		D2UberMephIA, (Game* ptGame, Unit* ptMonster, DWORD*));//1.11b
//E2F(D2Game,7FE60,	void,		D2UberDiabloIA, (Game* ptGame, Unit* ptMonster, DWORD*));//1.11b
//E2F(D2Game,2A300,	void,		D2UberBaalIA, (Game* ptGame, Unit* ptMonster, DWORD*));//1.11b
////E2F(D2Game,92420,	void,		D2ReloadGambleScreenGame, (Unit* ptNPC, Game* ptGame, Unit* ptChar, DWORD, DWORD one));//1.11b
//E2S(D2Game,E66D0,	void,		D2SaveGame, (Game* ptGame));//1.11b


F7(FAST, D2Game,10059,10059,10059,10039,10007,10037,10049,	void,		D2SetNbPlayers, (DWORD nbPlayers));
//A7(FAST, D2Game,00000,00000,01DE0,00000,00000,00000,00000,	void*,		D2GetClientByClientID, (Game* ptGame, DWORD clientID));//6FC31DE0
A7(FAST, D2Game,00000,00000, 6C60,E3DA0,E8210,EB060,49930,	void,		D2AddClient, (DWORD clientID));//BY EAX
A7(STD,  D2Game,00000,00000, 94E0,E0520,E49A0,A6360,2AAE0,	Game*,		D2GetGameByClientID, (DWORD clientID));//6FC394E0
A7(FAST, D2Game,00000,00000, B0E0,DF250,E36D0,A5080,29820,	void,		D2BroadcastFunction, (Game* ptGame, void* fct, void* param));//00DAB0E0
A7(FAST, D2Game, C380, C650, C710,41420,A0D50,7D220,8A3E0,	DWORD,		D2SendPacket, (void* ptNetClient, LPVOID pData, DWORD size));//EAX=ptNetClient [ESP]=pData
A7(FAST, D2Game, D650, D920, DB50,44D00,A3F20,802E0,8D5F0,	void,		D2SetSkillBaseLevelOnClient, (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove));//by EAX,ESI,EBX
//A7(FAST, D2Game,00000,00000,0E6F0,00000,00000,00000,00000,	void,		D2UpdateClientItem, (NetClient*	ptNetClient, Unit* ptChar, Unit* ptItem,DWORD,DWORD,DWORD));//6FC3E6F0
//A7(FAST, D2Game,00000,00000,10FB0,00000,00000,00000,00000,	DWORD,		D2UpdateInventory, (Game* ptGame, Unit* ptChar, void* ptNetClient, Inventory* pInventory));//6FC40FB0
//A7(FAST, D2Game,00000,00000,110E0,00000,00000,00000,00000,	DWORD,		D2UpdateItem, (Unit* ptChar, Unit* ptItem, Unit* ptSocketedItem, void* ptNetClient));//6FC410E0
A7(STD,  D2Game,00000,00000,00000,27230,109F0,AE930,A22E0,	DWORD,		D2LinkPortal, (Game* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID));
A7(FAST, D2Game,00000,00000,128F0,38D90,43E60,11FF0,D2070,	DWORD,		D2VerifIfNotCarry1, (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem));// BY EBX=itemsData EAX=ptFirstItem [ESP]=ptItem
//A7(FAST, D2Game,00000,00000,1ED80,00000,00000,00000,00000,	Unit*,		D2CreateItem, (Game* ptGame, ItemGenerationData* itemGenerationData, DWORD));//6FC4ED80
A7(FAST, D2Game,00000,00000,22070, 1090, 1DF0, 11F0, 1280,	Room*,		D2TestPositionInRoom, (Room* ptRoom, DWORD x, DWORD y));
//A7(FAST, D2Game,00000,00000,22410,00000,00000,00000,00000,	void,		D2AddStaffModAffixes, (Unit* ptItem, ItemGenerationData* itemParam));//6FC52410
//A7(FAST, D2Game,00000,00000,22C00,00000,00000,00000,00000,	WORD,		D2GetNewAffix, (Unit* ptItem, DWORD testIfSpawnable, DWORD mustSelectOne, DWORD addToItem, DWORD isPrefix, int affixID, WORD autoAffixGroupID));//6FC52C00
//A7(FAST, D2Game,00000,00000,23610,00000,00000,00000,00000,	WORD,		D2GetRareAffixName, (Unit* ptItem, DWORD wantPrefix));//6FC53610
//A7(FAST, D2Game,00000,00000,3AD10,00000,00000,00000,00000,	DWORD,		D2GetSuperUniqueMonsterID, (Game* ptGame, Unit* ptMonster));//6FC6AD10
A7(FAST, D2Game,00000,00000,3F220,4ABE0,EC7E0,40B90,24950,	DWORD,		D2SpawnMonster, (Game* ptGame, Room* ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2));//wrong param
A7(STD,  D2Game,00000,00000,00000,D6D10,235C0, D410,200E0,	void,		D2Game235C0, (Game* ptGame, Room* ptRoom));
//A7(FAST, D2Game,00000,00000,4C7B0,00000,00000,00000,00000,	Unit*,		D2GetSkillItem, (Unit* ptChar));//6FC7C7B0
//A7(FAST, D2Game,00000,00000,5A500,00000,00000,00000,00000,	DWORD,		D2SavePlayer, (Game* ptGame, Unit* ptChar, char* playername, DWORD zero));//6FC8A500
A7(FAST, D2Game,4F100,4F500,5B8A0,B9D70,25D50,44950,54810,	DWORD,		D2LoadInventory, (Game* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead));//6FC8B8A0
A7(FAST, D2Game,7BAE0,7BFD0,8BB00,97620,BEF80,93650,E03A0,	Unit*,		D2GameGetObject, (Game* ptGame, DWORD type, DWORD itemNum));//6FCBBB00
//A7(FAST, D2Game,00000,00000,9F320,501C0,F1C50,F1A50,F3220,	Unit*,		D2GetOwnerMonster, (Unit* ptMonster));
//A7(FAST, D2Game,00000,00000,E08D0,00000,00000,00000,00000,	void,		D2UpdateSkillDataAfterUnassignment, (Game* ptGame, Unit* ptChar, DWORD skillID));//6FD108D0
A7(FAST, D2Game,00000,00000,00000,99760,C09E0,94E70,E1D90,	Unit*,		D2CreateUnit, (DWORD type, DWORD id, DWORD x, DWORD y, Game* ptGame, Room* ptRoom, DWORD uk1, DWORD uk2, DWORD uk3));
A7(FAST, D2Game,00000,00000,00000,9B480,34920,D1AA0,70180,	void,		D2OpenPandPortal, (Game* ptGame, Unit* ptChar));
A7(FAST, D2Game,00000,00000,00000,9B470,34910,D1A90,70170,	void,		D2OpenPandFinalPortal, (Game* ptGame, Unit* ptChar));
A7(FAST, D2Game,00000,00000,00000,84730,85AA0,DBE90,A9610,	void,		D2MephIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,75980,D7BD0,CD0F0,85B60,	void,		D2DiabloIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,EAB20,2BC80,B3B90,B8610,	void,		D2BaalIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,70320,D2D70,C2A90,7B4E0,	void,		D2UberMephIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,7F200,7FE60,D6250,A39D0,	void,		D2UberDiabloIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,E92B0,2A300,B2210,B6C80,	void,		D2UberBaalIA, (Game* ptGame, Unit* ptMonster, DWORD*));
//A7(FAST, D2Game,00000,00000,00000,00000,92420,00000,00000,	void,		D2ReloadGambleScreenGame, (Unit* ptNPC, Game* ptGame, Unit* ptChar, DWORD, DWORD one));
A7(STD,  D2Game,00000,00000, 89C0,E2390,E66D0,A8090,2C830,	void,		D2SaveGame, (Game* ptGame) );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2Net : 6FC00000
//D2S(D2Net,10020,	DWORD,		D2SendToServer, (DWORD size, DWORD one, void* data));//ONLY 1.11b
//D2S(D2Net,10018,	DWORD,		D2SendToClient, (DWORD zero, DWORD clientID, void* data, DWORD size));//ONLY 1.11b

F7(STD,  D2Net,	10005,10005,10005,10035,10020,10036,10024,	DWORD,		D2SendToServer, (DWORD size, DWORD one, void* data));//(DWORD zero, void* data, DWORD size) for 1.10 and before
F7(STD,  D2Net,	10006,10006,10006,10018,10018,10015,10002,	DWORD,		D2SendToClient, (DWORD zero, DWORD clientID, void* data, DWORD size));


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fog : 6FF50000
//D2S(Fog,10023,		void,		D2FogAssertOld, (const char* ptMessage, DWORD eip, DWORD line));//ONLY 1.11/1.11b (STDCALL until 1.10)
//D2F(Fog,10024,		void,		D2FogAssert, (const char* ptMessage, DWORD eip, DWORD line));//ONLY 1.11/1.11b (STDCALL until 1.10)
//D2F(Fog,10042,		void*,		D2FogMemAlloc, (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
//D2F(Fog,10043,		void*,		D2FogMemDeAlloc, (void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));//1.11b
//D2F(Fog,10045,		void*,		D2AllocMem, (DWORD,DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));//1.11b
//D2F(Fog,10046,		void*,		D2FreeMem, (DWORD,void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));//1.11b
//D2F(Fog,10102,		DWORD,		D2MPQOpenFile, (char* ptPath, void** buf));//1.11
//D2F(Fog,10103,		DWORD,		D2MPQCloseFile, (void* mpqfile));//1.11
//D2F(Fog,10104,		DWORD,		D2MPQReadFile, (void* mpqfile, BYTE* buffer, DWORD nbToRead, DWORD* nbRead,DWORD,DWORD,DWORD));//1.11
//D2F(Fog,10105,		DWORD,		D2MPQGetSizeFile, (void* mpqfile, DWORD* toReset));//1.11
//D2F(Fog,10115,		void,		D2FogGetSavePath, (char* ptPath, DWORD maxsize));//1.11b
//D2F(Fog,10116,		void,		D2FogGetInstallPath, (char* ptPath, DWORD maxsize));//1.11b
////D2S(Fog,10126,		DWORD,		D2InitBitField, (saveBitField* data, BYTE* buf, DWORD bufsize));//6FF536C0
////D2S(Fog,10127,		DWORD,		D2GetBitFieldSize, (saveBitField* data));//6FF536C0
////D2S(Fog,10128,		void,		D2EncodeValue, (saveBitField* data, DWORD value, DWORD bitSize));//6FF536C0
////D2S(Fog,10130,		DWORD,		D2DecodeValue, (saveBitField* data,DWORD readingSize));//6FF53840
//D2S(Fog,10212,		void,		D2Fog10212, (DWORD unknow));//1.11b
////D2S(Fog,10217,		int,		D2GetIDFromLookUpTable, (void* table, char* string, bool));//6FF53840
//D2S(Fog,10265,		int,		D2GetInstructionPointer, ());//ONLY 1.11/1.11b NOT 1.10

F7(STD,  Fog,	10023,10023,10023,00000,00000,00000,00000,	void,		D2FogAssertOld, (const char* ptMessage, DWORD eip, DWORD line));//(STDCALL until 1.10)
F7(FAST, Fog,	00000,00000,00000,10024,10024,10024,10024,	void,		D2FogAssert, (const char* ptMessage, DWORD eip, DWORD line));
F7(FAST, Fog,	10042,10042,10042,10042,10042,10042,10042,	void*,		D2FogMemAlloc, (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10043,10043,10043,10043,10043,10043,10043,	void*,		D2FogMemDeAlloc, (void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10045,10045,10045,10045,10045,10045,10045,	void*,		D2AllocMem, (DWORD,DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10046,10046,10046,10046,10046,10046,10046,	void*,		D2FreeMem, (DWORD,void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10102,10102,10102,10102,10102,10102,10102,	DWORD,		D2MPQOpenFile, (char* ptPath, void** buf));
F7(FAST, Fog,	10103,10103,10103,10103,10103,10103,10103,	DWORD,		D2MPQCloseFile, (void* mpqfile));
F7(FAST, Fog,	10104,10104,10104,10104,10104,10104,10104,	DWORD,		D2MPQReadFile, (void* mpqfile, BYTE* buffer, DWORD nbToRead, DWORD* nbRead,DWORD,DWORD,DWORD));
F7(FAST, Fog,	10105,10105,10105,10105,10105,10105,10105,	DWORD,		D2MPQGetSizeFile, (void* mpqfile, DWORD* toReset));
F7(FAST, Fog,	10115,10115,10115,10115,10115,10115,10115,	void,		D2FogGetSavePath, (char* ptPath, DWORD maxsize));
F7(FAST, Fog,	10116,10116,10116,10116,10116,10116,10116,	void,		D2FogGetInstallPath, (char* ptPath, DWORD maxsize));
//F7(STD,  Fog, 10126,10126,10126,10126,10126,10126,10126,	DWORD,		D2InitBitField, (saveBitField* data, BYTE* buf, DWORD bufsize));//6FF536C0
//F7(STD,  Fog, 10127,10127,10127,10127,10127,10127,10127,	DWORD,		D2GetBitFieldSize, (saveBitField* data));//6FF536C0
//F7(STD,  Fog, 10128,10128,10128,10128,10128,10128,10128,	void,		D2EncodeValue, (saveBitField* data, DWORD value, DWORD bitSize));//6FF536C0
//F7(STD,  Fog, 10130,10130,10130,10130,10130,10130,10130,	DWORD,		D2DecodeValue, (saveBitField* data,DWORD readingSize));//6FF53840
F7(STD,  Fog,	10212,10212,10212,10212,10212,10212,10212,	void,		D2Fog10212, (DWORD unknow));
//F7(STD,  Fog, 10217,10217,10217,10217,10217,10217,10217,	int,		D2GetIDFromLookUpTable, (void* table, char* string, bool));//6FF53840
F7(STD,  Fog,	00000,00000,00000,10265,10265,10265,10265,	int,		D2GetInstructionPointer, ());
//Fog10213 getIndexFromLookupTable (&table,code,bool)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2Lang : 6FC10000
////D2F(D2Lang,10003,	LPWSTR,		D2GetStringFromString, (const char* ptString));//6FC13BC0
//D2F(D2Lang,10000,	LPWSTR,		D2GetStringFromIndex, (WORD dwIndexNum));//ONLY 1.11b
////D2S(D2Lang,10006,	void,		D2GetStringLang, (LPSTR ptLang, DWORD Zero));//6FC13FB0
//D2S(D2Lang,10013,	DWORD,		D2GetLang, ());//ONLY 1.11b
//D2S(D2Lang,10010,	DWORD,		D2PrintBigNumber, (LPWSTR ptBuf , DWORD number, DWORD size));//6FC14210
////D2S(D2Lang,10013,	DWORD,		D2GetStringAndIndexFromString, (const char* ptString , LPWSTR result));//6FC13960
////E2F(D2Lang,29B0,	DWORD,		D2UnicodeWidth, (DWORD MemLoc, WORD Size));//6FC129B0
////E2F(D2Lang,2E60,	LPWSTR,		D2GetStrFromIndex , (void* ptFile, void* ptMemLoc, DWORD dwIndexNum));//6FC12E60
////E2F(D2Lang,3640,	TblHeader*,	D2LoadTblFile, (LPCSTR lpszFileName));//6FC13640
////E2F(D2Lang,3A90,	WORD,		D2GetStrAndIndexFromString, (void* ptFile, void* ptMemLoc, LPSTR String, LPWSTR RetString));//6FC13A90
////E2F(D2Lang,2CD0,	DWORD,		D2unicodenwidth, (char* ptChar, DWORD size));//6FC12CD0_unicodenwidth
////E2S(D2Lang,1670,	DWORD,		D2swprintf, (DWORD bufSize, LPWSTR buf, LPWSTR string, ...));//6FC11670_sprintf

//F7(FAST, D2Lang,	10003,10003,10003,00000,00000,00000,00000,	LPWSTR,		D2GetStringFromString, (const char* ptString));//6FC13BC0
F7(FAST, D2Lang,	10004,10004,10004,10005,10000,10005,10003,	LPWSTR,		D2GetStringFromIndex, (WORD dwIndexNum));
//F7(STD,  D2Lang,	10006,10006,10006,00000,00000,00000,00000,	void,		D2GetStringLang, (LPSTR ptLang, DWORD Zero));//6FC13FB0
F7(STD,  D2Lang,	10007,10007,10007,10009,10013,10002,10009,	DWORD,		D2GetLang, ());
F7(STD,  D2Lang,	10010,10010,10010,00000,00000,00000,00000,	DWORD,		D2PrintBigNumber, (LPWSTR ptBuf , DWORD number, DWORD size));//6FC14210
//F7(STD,  D2Lang,	10013,10013,10013,00000,00000,00000,00000,	DWORD,		D2GetStringAndIndexFromString, (const char* ptString , LPWSTR result));//6FC13960
//A7(FAST, D2Lang,	00000,00000,029B0,00000,00000,00000,00000,	DWORD,		D2UnicodeWidth, (DWORD MemLoc, WORD Size));//6FC129B0
//A7(FAST, D2Lang,	00000,00000,02E60,00000,00000,00000,00000,	LPWSTR,		D2GetStrFromIndex , (void* ptFile, void* ptMemLoc, DWORD dwIndexNum));//6FC12E60
//A7(FAST, D2Lang,	00000,00000,03640,00000,00000,00000,00000,	TblHeader*,	D2LoadTblFile, (LPCSTR lpszFileName));//6FC13640
//A7(FAST, D2Lang,	00000,00000,03A90,00000,00000,00000,00000,	WORD,		D2GetStrAndIndexFromString, (void* ptFile, void* ptMemLoc, LPSTR String, LPWSTR RetString));//6FC13A90
//A7(FAST, D2Lang,	00000,00000,02CD0,00000,00000,00000,00000,	DWORD,		D2unicodenwidth, (char* ptChar, DWORD size));//6FC12CD0_unicodenwidth
//A7(STD,  D2Lang,	00000,00000,01670,00000,00000,00000,00000,	DWORD,		D2swprintf, (DWORD bufSize, LPWSTR buf, LPWSTR string, ...));//6FC11670_sprintf

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Storm : 6FFB0000
////D2S(Storm,253,		void,		D2StormMPQCloseFile, (void* mpqfile));
//D2S(Storm,268,		DWORD,		D2StormMPQOpenFile, (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void** buffer));//1.11b
//D2S(Storm,503,		void,		D2Storm503, (DWORD, DWORD, DWORD)); //+1.11
//D2S(Storm,511,		void,		D2FreeWinMessage, (sWinMessage* msg));//1.11/1.11b

//F7(STD,  Storm,	  253,  253,  253,  253,  253,  253,  000,	void,		D2StormMPQCloseFile, (void* mpqfile));
F7(STD,  Storm,	  268,  268,  268,  268,  268,  268,  268,	DWORD,		D2StormMPQOpenFile, (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void** buffer))
F7(STD,  Storm,	  503,  503,  503,  503,  503,  503,  503,	void,		D2Storm503, (DWORD, DWORD, DWORD));
F7(STD,  Storm,	  511,  511,  511,  511,  511,  511,  511,	void,		D2FreeWinMessage, (sWinMessage* msg));


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2gfx : 6FA70000
//D2S(D2gfx,10063,	DWORD,		D2GetResolution,() );//ONLY 1.11b
////D2S(D2gfx,10023,	DWORD,		D2CreateMainWindow,(DWORD,DWORD) );
////D2S(D2gfx,10026,	DWORD,		D2ShowWindow,() );
////D2S(D2gfx,10027,	HWND,		D2GetWindowHandle,() );//6FA749C0
//D2S(D2gfx,10000,	void,		D2FillArea,(DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl));//ONLY 1.11b
//D2S(D2gfx,10044,	void,		D2PrintImage,(sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6) );//ONLY 1.11b

F7(STD,  D2gfx,	10005,10005,10005,10000,10063,10043,10031,	DWORD,		D2GetResolution,() );
//F7,STD,  D2gfx,	10023,10023,10023,00000,00000,00000,00000,	DWORD,		D2CreateMainWindow,(DWORD,DWORD) );
//F7(STD,  D2gfx,	10026,10026,10026,00000,00000,00000,00000,	DWORD,		D2ShowWindow,() );
//F7,STD,  D2gfx,	10027,10027,10027,00000,00000,00000,00000,	HWND,		D2GetWindowHandle,() );//6FA749C0
F7(STD,  D2gfx,	10055,10055,10055,10028,10000,10062,10014,	void,		D2FillArea,(DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl));
F7(STD,  D2gfx,	10072,10072,10072,10047,10044,10024,10041,	void,		D2PrintImage,(sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6) );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2Win : 6F8E0000 (1.10 and 1.11)
//D2F(D2Win,10075,	void,		D2PrintLineOnTextBox,(void* screen, char* s, DWORD color) );//ONLY 1.11b
//D2F(D2Win,10064,	void,		D2PrintString,(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse) );//ONLY 1.11b
//D2F(D2Win,10128,	DWORD,		D2GetPixelLen,(LPWSTR s) );//ONLY 1.11b
//D2F(D2Win,10170,	DWORD,		D2SetFont,(DWORD fontID) );//ONLY 1.11b
//D2F(D2Win,10039,	void,		D2PrintPopup,(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center) );//ONLY 1.11b
//D2F(D2Win,10131,	void,		D2GetPixelRect,(LPWSTR s, DWORD* x, DWORD* y) );//6F8AB260
//D2F(D2Win,10132,	DWORD,		D2PrintTextPopup,(LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color) );//6F8AB080
//D2S(D2Win,10113,	void*,		D2CreateTextBox,(DWORD* data) );//ONLY 1.11b

F7(FAST, D2Win, 10046,10046,10046,10061,10075,10015,10022,	void,		D2PrintLineOnTextBox,(void* screen, char* s, DWORD color) );
F7(FAST, D2Win, 10117,10117,10117,10020,10064,10001,10150,	void,		D2PrintString,(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse) );
F7(FAST, D2Win, 10121,10121,10121,10034,10128,10132,10028,	DWORD,		D2GetPixelLen,(LPWSTR s) );
F7(FAST, D2Win, 10127,10127,10127,10141,10170,10010,10184,	DWORD,		D2SetFont,(DWORD fontID) );
F7(FAST, D2Win, 10129,10129,10129,10118,10039,10031,10085,	void,		D2PrintPopup,(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center) );
F7(FAST, D2Win, 10131,10131,10131,00000,00000,00000,00000,	void,		D2GetPixelRect,(LPWSTR s, DWORD* x, DWORD* y) );//6F8AB260
F7(FAST, D2Win, 10132,10132,10132,00000,00000,00000,00000,	DWORD,		D2PrintTextPopup,(LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color) );//6F8AB080
F7(STD,  D2Win, 10017,10017,10017,10147,10113,10098,10098,	void*,		D2CreateTextBox,(DWORD* data) );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D2CMP : ????0000
//D2S(D2CMP,10014,	DWORD,		D2CMP10014, (void* image) );//ONLY 1.11

F7(STD,  D2CMP,	10032,10032,10032,10021,10014,10106,10065,	DWORD,		D2CMP10014, (void* image) );


//ONLY UNTIL 1.10 :
A7(FAST, D2Client,	 BA00, B9F0, C080,00000,00000,00000,00000,	DWORD,		D2isLODGame, ());//6FAAC080
A7(FAST, D2Client,	00000,00000, C090,00000,00000,00000,00000,	BYTE,		D2GetDifficultyLevel, ());//6FAAC090  1.09 should be BA10 (b) BA00 (d)
A7(STD,  D2Client,	B6670,B59F0,B7BC0,00000,00000,00000,00000,	DWORD,		D2GetMouseX, ());//6FB57BC0
A7(STD,  D2Client,	B6680,B5A00,B7BD0,00000,00000,00000,00000,	DWORD,		D2GetMouseY, ());//6FB57BD0
A7(STD,  D2Client,	8DC40,8CFC0,883D0,00000,00000,00000,00000,	Unit*,		D2GetClientPlayer, ());//6FB283D0
A7(FAST, D2Client,	 B920, B910, BF60,00000,00000,00000,00000,	void,		D2CleanStatMouseUp, ());//6FAABF60
A7(FAST, D2Client,	 D210, D200, D990,00000,00000,00000,00000,	void,		D2SendToServer3, (BYTE type, WORD p));//6FAAD990
//A7(FAST, D2Client,	00000,00000, DA20,00000,00000,00000,00000,	void,		D2SendToServer5, (BYTE type, DWORD p));//6FAADA20
//A7(FAST, D2Client,	00000,00000, D9E0,00000,00000,00000,00000,	void,		D2SendToServer7, (BYTE type, WORD p1, WORD p2, WORD p3));//6FAAD9E0
//A7(FAST, D2Client,	00000,00000, DA40,00000,00000,00000,00000,	void,		D2SendToServer9, (BYTE type, DWORD p1, DWORD p2));//6FAADA40
//A7(FAST, D2Client,	00000,00000, DA70,00000,00000,00000,00000,	void,		D2SendToServer13,(BYTE type, DWORD p1, DWORD p2, DWORD p3));//6FAADA70
A7(FAST, D2Game,	7C2C0,7C7B0,8C2E0,00000,00000,00000,00000,	NetClient*,	D2GetClient, (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine));//6FCBC2E0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// VARIABLES ////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Data D2Client : 6FAA0000
////E2C(D2Common,96A20,	DataTables*,SgptDataTables); //03836A20 - 037A0000 //01EE6A20
//E2C(D2Client,F4FC8,	DWORD,		ResolutionY);//0x258 = 600 //1.11b
//E2C(D2Client,F4FC4,	DWORD,		ResolutionX);//0x320 = 800 //1.11b
//E2C(D2Client,11BEFC,DWORD,		NegWindowStartY);//0xFFFFFFC4 = -60 //1.11b
//E2C(D2Client,11BEF8,DWORD,		WindowStartX);//0x50 = 80 //1.11b
////E2C(D2Launch,2CD5C,	DWORD,		GameTypeMode);//0x50 = 80 //6FA3CD5C-6FA10000
//E2C(D2Game,  111718,NetClient*,	ClientTable);//1.11
////E2C(D2Client,104225,DWORD,		CurrentNPCNum);//1.11b
//E2C(D2Client,11A2F4,DWORD,		IsLodGame);//1.11
//E2C(D2Client,11BFB8,BYTE,		DifficultyLevel);//1.11
//E2C(D2Client,11B414,DWORD,		MouseY);//0x258 = 600 //1.11b
//E2C(D2Client,11B418,DWORD,		MouseX);//0x320 = 800 //1.11b
//E2C(D2Client,11C1E0,Unit*,		ptClientChar);//1.11b

//C7(D2Common,000000,000000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C,	DataTables*,SgptDataTables); //03836A20 - 037A0000 //01EE6A20
C7(D2Client, D50E8, D40E0, D40F0, F5C60, F4FC8, DC6E4, DBC4C,	DWORD,		ResolutionY);//0x258 = 600
C7(D2Client, D50EC, D40E4, D40F4, F5C5C, F4FC4, DC6E0, DBC48,	DWORD,		ResolutionX);//0x320 = 800
C7(D2Client,125AD8,124958,11A74C,11BD28,11BEFC,11BD2C,11B9A4,	DWORD,		NegWindowStartY);//0xFFFFFFC4 = -60
C7(D2Client,125AD4,124954,11A748,11BD24,11BEF8,11BD28,11B9A0,	DWORD,		WindowStartX);//0x50 = 80
//C7(D2Launch, 55818, 56088, 2CD5C,000000, 2CD5C,000000,000000,	DWORD,		GameTypeMode);//0x50 = 80 //6FA3CD5C-6FA10000
C7(D2Game,   F2A80, F2918,113FB8,111718,1115E0,1105E0,1107B8,	NetClient*,	ClientTable);
//C7(D2Client,000000,000000,000000,000000,104225,000000,000000,	DWORD,		CurrentNPCNum);
C7(D2Client,000000,000000,000000, FB3F4,11A2F4,10330C,119854,	DWORD,		IsLodGame);
C7(D2Client,000000,000000,10795C,11BFB8,11C2A8,11BFF4,000000,	BYTE,		DifficultyLevel);
C7(D2Client,000000,000000,000000,10A40C,11B414,101634,11B824,	DWORD,		MouseY);//0x258 = 600
C7(D2Client,000000,000000,000000,10A410,11B418,101638,11B828,	DWORD,		MouseX);//0x320 = 800
C7(D2Client,000000,000000,000000,11C4F0,11C1E0,11C3D0,11BBFC,	Unit*,		ptClientChar);


C7(D2Client, DB918, DA828,000000,000000,000000,000000,000000,	DWORD,		NbStatDesc);
C7(D2Client, DAF98, D9EA8,000000,000000,000000,000000,000000,	DWORD,		StatDescTable);

/* NEXT NOT TESTED IN 1.10 (1.09b fct)
D2_STD(D2Common10066,	void,		D2RemoveFromRoom, (DrlgRoom1* hRoom, DWORD untitype, DWORD unitID),				0x6FD7CFD0);
D2_STD(D2Common10082,	DWORD,		D2IsTown, (DrlgRoom1* hRoom),													0x6FD7D8A0);
D2_STD(D2Common10180,	Unit*,		D2GetTargetFromPath, (Path* hPath),												0x6FD9C4C0);
D2_STD(D2Common10184,	void,		D2SetPathParameter, (Path* hPath, DWORD value),									0x6FD9C5D0);
D2_STD(D2Common10240,	Inventory*,	D2InitInventory, (DWORD zero, DWORD param1, DWORD param2, DWORD param3, DWORD one), 0x6FD7E920);
D2_STD(D2Common10253,	bool,		D2EquipUnit, (Unit* ptTaker, Unit* ptItem, DWORD bodyloc),						0x6FD80020);
D2_STD(D2Common10258,	Unit*,		D2GetWeaponUnit, (Inventory* ptInventory),										0x6FD802D0);
D2_STD(D2Common10261,	void*,		D2SetMouseItem, (Inventory* ptInventory, Unit* ptUnit),							0x6FD80520);
D2_STD(D2Common10310,	Node*,		D2GetNodeForItem, (Inventory* ptInventory, Unit* ptUnit),						0x6FD82FB0);
D2_STD(D2Common10320,	SkillData*,		D2GetStartingSkill, (Unit* ptUnit),												0x6FDAD8C0);
D2_STD(D2Common10321,	SkillData*,		D2GetLeftHandSkill, (Unit* ptUnit),												0x6FDAD900);
//D2_STD(D2Common10322,	SkillData*,		D2GetRightSkill, (Unit* ptUnit),												0x6FDAD940);
D2_STD(D2Common10323,	SkillData*,		D2GetCurrentSkill, (Unit* ptUnit),												0x6FDAD9C0);
D2_STD(D2Common10326,	DWORD,		D2UNITGetXpos, ( Unit* ptUnit ),												0x6FDADA00);
D2_STD(D2Common10329,	DWORD,		D2UNITGetYpos, ( Unit* ptUnit ),												0x6FDADB70);
//D2_STD(D2Common10348,	void,		D2SetUnitMode, (Unit* ptUnit, DWORD mode),										0x6FDAEBD0);
D2_STD(D2Common10395,	ShrinesTXT*,	D2GetShrinesTXTRowFromID, (DWORD shrineID),										0x6FDAFE20);
D2_STD(D2Common10659,	void*,		D2GetTCFromID, (DWORD TCIndex),													0x6FD5E1C0);
//D2_STD(D2Common10517,	void,		D2SetPlayerStat, (Unit* ptChar, DWORD statID, DWORD Amount),					0x6FDA7D30);
//D2_STD(D2Common10581,	CharStatsBIN*,D2GetCharStatsBIN, (DWORD classID),											offset_D2Common + 0x6FD47430);
D2_STD(D2Common10746,	DWORD,		D2GetCode, (Unit* ptUnit),														0x6FD8AD70);
D2_STD(D2Common10749,	void,		D2ITEMSGetItemDimensions, (Unit* ptItem, DWORD* x, DWORD* y, char* filename, DWORD line), 0x6FD8AF00);
D2_STD(D2Common10795,	DWORD,		D2GetMaxStack, (Unit* ptUnit),													0x6FD8EEF0);
D2_STD(D2Common10804,	DWORD,		D2GetSpellIcon, (Unit* ptUnit),													0x6FD8F190);
D2_STD(D2Common10821,	DWORD,		D2IsSocketValid, (Unit* ptItem ),												0x6FD8FD70);
//D2_STD(D2Common10854,	void,		D2RemoveItem, (Unit* ptUnit, BYTE page),										0x6FD89DC0);
D2_STD(D2Common10868,	void,		D2SetMod, (Unit* ptUnit, ItemMod* ptProperty, int one),							0x6FD88950);
D2_FST(D2Common10918,	DWORD,		D2GetRandomInt, (D2Seed* ptSeed, int max),										0x6FDA0B10);
D2_STD(D2Common10952,	Unit*,		D2AddSingleSkill, (Unit* ptChar, WORD SkillID),									0x6FDA1CB0); // WORD ?
D2_FST(D2Common10966,	Unit*,		D2GetSkillPointerFromClient, (Unit* ptClientChar),								0x6FDA33A0);
D2_FST(D2Common6FC82E00,DWORD,		D2GetItemNum, (D2Game* ptGame, DWORD lvl, DWORD typenum),						0x6FC82E00);

D2_FST(D2Game6FC3E3F0,	void,		D2ClientItemRemove, (void* ptClient, Unit* ptChar, Unit* ptItem, DWORD twenty),							0x6FC3E3F0);
D2_FST(D2Game6FC3E640,	void,		D2FireScrollGraph, (void* ptClient, Unit* ptItem, int one, DWORD dwStatID, DWORD dwStatNum),			0x6FC3E640);
D2_FST(D2Game6FC3E6C0,	void,		D2SetMouseIcon, (void* ptGame, Unit* ptChar, int nSpellicon, int zero, int one, DWORD dwUnknown),		0x6FC3E6C0);
D2_FST(D2Game6FC3E740,	void*,		D2ResetMouse, (void* ptClient, Unit* ptChar),															0x6FC3E740);
D2_FST(D2Game6FC45BD0,	DWORD,		D2SwapItem, (D2Game* ptGame, Unit* ptChar, DWORD dwSrcID, DWORD dwTrgID, int x, int y, void* ptMouse),	0x6FC45BD0);
D2_FST(D2Game6FC45FE0,	void,		D2RemoveItemMem, (D2Game* ptGame, Unit* ptChar, Unit* ptItem, DWORD zero),								0x6FC45FE0);
D2_FST(D2Game6FC480D0,	DWORD,		D2PutScroll, (D2Game* ptGame, Unit* ptChar, DWORD dwSrcID, DWORD dwTrgID, void* ptMouse),				0x6FC480D0);
D2_FST(D2Game6FC497B0,	void,		D2UpdatePlayer, (void * ptGame, Unit* ptChar, DWORD nUnitType),											0x6FC497B0);
D2_FST(D2Game6FC4E170,	void*,		D2RemoveItemFromMem, (void* ptGame, Unit* ptItem),														0x6FC4E170);
D2_FST(D2Game6FC4E290,	void*,		D2GetPtrFromCode, (void* ptChar, DWORD itemcode),														0x6FC4E290);
D2_FST(D2Game6FC87E40,	void,		D2SpawnItem, (void* ptGame, Unit* ptChar, DWORD itemCode, DWORD ilvl, DWORD quality, DWORD one),		0x6FC87E40);
D2_FST(D2Game6FC4EF60,	void,		D2DropTC, (void* ptGame, Unit* ptChar, Unit* ptNPC, void* ptTC, DWORD z5, DWORD ilvl, DWORD z1, DWORD z2, DWORD z3, DWORD z4), 0x6FC4EF60);
D2_FST(D2Game6FCABAE0,	Unit*,		D2GetPtrFromID, (D2Game* ptGame, int UnitType, DWORD UniqueID),											0x6FCABAE0);
D2_FST(D2Game6FCABB70,	void,		D2SpawnPlague, (void* u1,Unit* ptMissile),																0x6FCABB70);

D2_FST(D2Client6FAB9AF0,void,		D2FireClientMissile, (Unit* ptUnit),											0x6FAB9AF0);
D2_FST(D2Client6FAE6600,void,		D2CubeLight, (DWORD code),														0x6FAE6600);
D2_FST(D2Client6FB22270,void,		D2ScrollText, (Unit* ptUnit, DWORD ptText, int zero),							0x6FB22270);
D2_FST(D2Client6FB2C1E0,Unit*,		D2GetClientUnit, (DWORD itemID, DWORD nUnitType),								0x6FB2C1E0);
D2_FST(D2Client6FB30470,void,		D2ClientUpdatePlayer, (Unit* ptChar, DWORD nUnitType),							0x6FB30470);


Storm 1.09:
251  SFileAuthenticateArchive  
252  SFileCloseArchive  
253  SFileCloseFile  
254  SFileDdaBegin  
255  SFileDdaBeginEx  
256  SFileDdaDestroy  
257  SFileDdaEnd  
258  SFileDdaGetPos  
259  SFileDdaGetVolume  
260  SFileDdaInitialize  
261  SFileDdaSetVolume  
262  SFileDestroy  
263  SFileEnableDirectAccess  
264  SFileGetFileArchive  
265  SFileGetFileSize  
266  SFileOpenArchive  
267  SFileOpenFile  
268  SFileOpenFileEx  
269  SFileReadFile  
270  SFileSetBasePath  
271  SFileSetFilePointer  
272  SFileSetLocale  
273  SFileGetBasePath  
274  SFileSetIoErrorMode  
275  SFileGetArchiveName  
276  SFileGetFileName  
277  SFileGetArchiveInfo  
278  SFileSetPlatform  
279  SFileLoadFile  
280  SFileUnloadFile  
281  SFileLoadFileEx  
282  SFilePrioritizeRequest  
283  SFile_CancelRequest  
284  SFileSetAsyncBudget  
285  SFileSetDataChunkSize  
286  SFileEnableSeekOptimization  
287  SFileReadFileEx  
288  SFile_CancelRequestEx  
289  SFileReadFileEx2  
290  SFileLoadFileEx2 

Storm1.08
401  SMemAlloc  
403  SMemFree  
404  SMemGetSize  
405  SMemReAlloc  
481  SMemFindNextBlock  
482  SMemFindNextHeap  
483  SMemGetHeapByCaller  
484  SMemGetHeapByPtr  
485  SMemHeapAlloc  
486  SMemHeapCreate  
487  SMemHeapDestroy  
488  SMemHeapFree  
489  SMemHeapReAlloc  
490  SMemHeapSize  
491  SMemCopy  
492  SMemFill  
493  SMemMove  
494  SMemZero  
495  SMemCmp  
496  SMemSetDebugFlags  
497  SMemDumpState 
*/
//Kingpin: D2Common #10027 is used to get dest unit (used for get type5 object in next room)
//D2Common10247, (ptInventory, ptItem, x,y,0xC,void*,void*,BYTE page) verif if items can be put in inventory
//D2Common10252 CheckGrid mouse over inventory/stash/etc. grid
//D2Common10284 returns current number of used sockets arg1 = ptInventory //KP
//D2Common10367 Returns number of rows in belt Kingpin: arg1 = ptItem
//D2Common10526 Kingpin know arg1 = ptUnit, arg3 = _FILE_, arg4 = ptGame
//D2Common10573 arg2 ptStatsList
//D2Common10660 is for sure returning tc entry  it uses act, difficulty as params and one more, arg3 = depends of area level (0-2)
//D2Common11064 Kingpin: Check if monster and check if current animation mode is allowed arg1 = ptUnit
//D2Common11257 Get MaxID from SuperUnique.bin adress in memory arg1 = hcIdx

//D2LoadItem D2Common10883 + 0x60370);//01D40370-1ce0000
//D2TcEx (select what item to drop from the treasureclass) at:6FC51360
//D2_STD(D2Common10578,	BYTE*,		D2LoadBinFile, (...),				offset_D2Common + 0xFD70); //01CFFD70-01CF0000
//Kingpin :I have noted that 10732 is this: get set/unique # [[+70]+24]
/*
Kingpin: d2common #11270
Kingpin: Check MonType.txt line to see if it match (returns a boolan)
Kingpin: arg1 = unknown 
arg2 = damage_vs_montype (stat from intestatscost.txt) 
arg3 = ptUnit 
arg4 = 80 (maxline maybe, but is only guessing)

//d2game.6FD1D660 reverse player name :P


Kingpin: figured out a new t hing related to D2common #10466 :P
Yohann: ah ?
Kingpin: get stat (from itemstatscost.txt) used to calculated frames (life, missile, mana e.tc)
Kingpin: arg1 = ptUnit
Kingpin: arg2 = stat_id
Kingpin: arg3 = table index


D2Game.6FCBC900 Get Target ptUnit

Kingpin: D2Client.6FB18770 returns a boolean if you have enough mana for skill
Kingpin: D2Client.6FB18AC0 sets it to selectable or not
D2Common #10480 Return ptState arg1 = ptUnit, arg2 = state_id
D2Common #10479 Get State_ID from ptState+14
D2Common #11265 Get Skill_ID from ptState+1C  Arg1 = ptState  

Kingpin: D2Common #10497 Get Duration of State  
Kingpin: arg1 = state_id


D2Client.6FB5B0F0 
Function: Draw Filled Rectangle 
void FASTCALL D2ClientFillRect(int x, int y, int Width, int Height, ULONG ulColor, ULONG transTbl);
D2_FST(D2Client6FB5B0F0,void,		D2ClientFillRect,(int x, int y, int Width, int Height, DWORD col, DWORD transTbl), offset_D2Client + 0xBB0F0);//6FB5B0F0-6FAA0000
D2Gfx.#10055 
Function: Draw Filled Rectangle 
void STDCALL D2GfxFillRect(int left, int top, int right, int bottom, ULONG ulColor, ULONG transTbl);
NOTES: 
color = Palette index. 
transTbl = pl2 transform table index ... 
0 = 75% transparent 
1 = 50% transparent 
2 = 25% transparent 
3 = color blend 1 //white is transparent black is solid 
4 = color blend 2 //black is transparent white is solid 
5 = normal draw 
6 = color blend 3 // screen + color 
7 = hilight 


6FAE7831   E8 9A380800      CALL <JMP.&D2Common.#10252> ; click inventory  
6FAE8D44   E8 87230800      CALL <JMP.&D2Common.#10252> ; Right click inventory  
6FAE8972   E8 59270800      CALL <JMP.&D2Common.#10252> ; mouse over


D2Client.6FACFCD0 then that set color for the text (it calls in this function #10121 and 10117)
Kingpin: and the position
Kingpin: arg1 = Xpos 
arg2 = Ypos 
arg3 = Pointer to Unicode String 
arg4 = Color

Kingpin: 10470 has as first arg ptGame +1C (memory alloc thing)
Kingpin: arg2 = flags i guess since they use 0x40 again
Kingpin: arg3 = 0 (no idea what it used for)
Kingpin: arg4 = 4 (same here, no idea)
Kingpin: arg5 = uniqueID

Kingpin: 10868 SetMod
arg1 = ptItem 
arg2 = ItemMod 
arg3 = 1
Kingpin: 11232 Get Cube Recipe Record (Line) from Cubemain.bin  Address in memory   
Kingpin: i have no parameters for 11232
Kingpin: 11233 Get Number of Cube Recipes

Kingpin: edi contains target unit 
Kingpin: 10342 get ptRoom from target unit
Kingpin: ecx = unique unit id
Kingpin: ebx = unit type
Kingpin: eax = ptRoom
Kingpin: 10066 remove unit from room

D2Game.6FCBC900 ; Get Target Unit 
Arg1 = ptPlayer (ptUnit)
Arg2 = ptGame



#10962 Add skill to player  
Kingpin: arg1 ptPlayer 
arg2 SkillID
Kingpin: arg3 Skill Level

10602 Gets an item ID # from an item code  

Kingpin: get Prefix/suffix
Kingpin: #10699 arg1 = ptItem, arg2 = prefix Index
Kingpin: #10701 arg1 = ptItem, arg2 = suffix index


D2EquipUnit STDCALL_FUNCTION(int,               D2Common280D,          (Inventory* ptInventory, Unit* ptItem, int bodylocation)); 
D2AddItemToInventory STDCALL_FUNCTION(int,               D2Common2802,          (Inventory* ptInventory, Unit* ptItem, int nodePage)); 
Kingpin: in my notes it should start here
Kingpin: 6FC51360  /$ 55             PUSH EBP

D2DropTC FASTCALL_FUNCTION(void,               D2Game6FC51360,          (D2Game* ptGame, Unit* ptChar, Unit* ptNPC, void* ptTC, DWORD z5, DWORD ilvl, DWORD z1, DWORD z2, DWORD z3, DWORD z4));   

Kingpin: D2CreateItemUnit FASTCALL_FUNCTION(Unit*,          D2Game6FC501A0,          (Unit* ptPlayer, DWORD itemCode, D2Game* ptGame, DWORD uk1, DWORD quality, DWORD uk3, DWORD uk4, DWORD Lvl, DWORD uk5, DWORD uk6, DWORD uk7));        
ptItem = D2CreateItemUnit(ptPlayer, D2GetItemIDfromCode(CharstatTXT->Item1), PCGame, 4, 2, 1, 1, D2GetUnitStat(ptPlayer,STATS_LEVEL,0), 0, 0, 0);  

Kingpin: monsterData +28 holds ptGame
Kingpin: ptGame +2C UniqueID (owner ID)
Kingpin: ptGame +30 UnitType 
srvDoFunc 15 adds temporarly a stat

Kingpin: we have 10041 that get ptRoom from ptAct, XOffset&Yoffset

*/
/*================================= END OF FILE =================================*/