/*=================================================================
	File created by Yohann NICOLAS.

   @brief Diablo II Unit Structures definitions.

   NOT TESTED IN 1.10 (1.09b)
 
=================================================================*/

#pragma once

#include <windows.h>
struct CBPlayerData;
struct CBItemData;
struct Unit;

/*=================================================================*/
/*  Skill Structure.                                               */
/*=================================================================*/

struct SkillData
{								//Offset from Code. (size = 0x3C or 0x40)
	SkillsBIN*	ptSkillBin;		//+00
	SkillData*	ptNextSkill;	//+04
	DWORD	mode;           //+08
	DWORD	uk1[3];         //+0C
	DWORD	targetInfo;     //+18
	DWORD	targetType;     //+1c
	DWORD	targetUNID;     //+20
	DWORD	uk2;            //+24
	DWORD	slvl;           //+28
	DWORD	slvlBonus;      //+2c
	DWORD	uk3;            //+30
	int		state;          //+34 (-1 if index exist)
	DWORD	param1;			//+38 (nb current charge)
	DWORD	param2;			//+3C
};

struct Skills
{								//Offset from Code.
	DWORD		gameRelated;	//+00
	SkillData*	ptFirstSkill;	//+04
	SkillData*	ptLeftSkill;	//+08
	SkillData*	ptRightSkill;	//+0c
    SkillData*	ptCurrentSkill;	//+10
};


/*=================================================================*/
/*   Unit Data Structure.                                          */
/*=================================================================*/

struct Position
{
	DWORD x;
	DWORD y;
};

struct Room//size=0x80
{
//ptRoom +48 0 = spawn new units (monster, objects e.tc), 1 = don't spawn any new units
	DWORD	seed1;						//+00
	DWORD	seed2;						//+04
	BYTE	uk8[0x1C];					//+08
	Room*	ptNearRooms;				//+24
	DWORD	nbNearRooms;				//+28
	Unit*	unit;						//+2C
	BYTE	uk5[0x44];					//+30
	Room*	ptNextRoom;					//+74
	union
	{
		BYTE	flags;					//+78
		struct
		{
			BYTE isGenerated:1;
			BYTE isGenerated2:1;//???
		};
	};
};

struct ActMap//ptGame+BC size=0x60
{
	DWORD	isNotManaged;
	DWORD	uk4;
	DWORD	uk8;//size = 0x488
	Room*	ptFirstRoom;
};

struct NetClient;
//ptGame : 04E4007C
struct Game
{                              			//Offset from Code.
	BYTE	uk1[0x18];					//+00
	DWORD	_ptLock;					//+18 Unknown  
	DWORD	memoryPool;					//+1C Memory Pool (??)  
	BYTE	uk2[0x4D];					//+20
	BYTE	difficultyLevel;			//+6D (Difficulty 0,1 or 2)
	WORD	unknown1;					//+6E Cube puts 4 here
	DWORD	isLODGame;					//+70 (D2=0 LOD =1) (DWORD ?)
	BYTE	uk3[0x04];					//+71
	WORD	unknown2;					//+78
	BYTE	uk4[0x0E];					//+7A
	NetClient*	ptClient;				//+88
	BYTE	uk8C[0x30];					//+8C
	ActMap*	mapAct[5];					//+BC
	BYTE	ukD0[0x1024];				//+D0
	DWORD*	game10F4;					//+10F4
	BYTE	uk6[0x28];					//+10F8
	Unit*	units[0xA00];				//+1120
	Unit*	roomtitles[0x200];			//+1B20
};
//WORD ptGame+28 game ID ?



struct Path //(8 dword)
{                              			//Offset from Code.		Size: 20
	WORD	uk1;						//+00
	WORD	mapx;						//+02
	WORD	uk2;						//+04
	WORD	mapy;						//+06
	DWORD	uk3;						//+08
	DWORD	x;							//+0C
	DWORD	y;							//+10
	DWORD	uk6;						//+14
	DWORD	uk7;						//+18
	Room*	ptRoom;						//+1C
};


struct Inventory
{                               		//Offset from Code.		Size: 30 à 40
	DWORD	tag;						//+00	= 0x01020304
	BYTE	uk1[0x04];					//+04	=? 0
	Unit*	ptChar;						//+08
	Unit*	ptItem;						//+0C
	BYTE	uk2[0x10];					//+10
	Unit*	inventory1;					//+20
	BYTE	uk3[0x04];					//+24
	DWORD	currentUsedSocket;			//+28 //Kingpin : a variable to know how many sockets that have added to item
	DWORD	Inventory2C;				//+2C //one value
	DWORD	Inventory30;				//+30
	void*	ptCorpse;					//+34
	BYTE	uk5[0x04];					//+38
	DWORD	nextCorpseId;				//+3C //max = 15
	BYTE	uk6[0x04];					//+40
};

struct D2Stat
{
	WORD	index;
	WORD	id;
	int		value;
};


struct Stats				//sizeof(Stats)=0x64
{
	DWORD	nUnitId;				//+00
	Unit*	ptUnit;					//+04
	DWORD	nUnitType;				//+08
	DWORD	nItemNum;				//+0C
	union
	{
		DWORD	flags;				//+10
		struct
		{
			DWORD fuk1:13;			//0x00001FFF
			DWORD isDisabled:1;		//0x00002000
			DWORD fuk2:17;			//0x7FFFC000
			DWORD dontUseBaseValue:1;//0x80000000
		};
	};
	DWORD	id;						//+14
	DWORD	uk18;					//+18
	BYTE	uk2[0x08];				//+1C
	D2Stat*	ptBaseStatsTable;		//+24
	WORD	nbBaseStats;			//+28
	WORD	sizeOfBaseStatsTable;	//+2A ??
	Stats*	ptStats;				//+2C
	BYTE	uk3[0x04];				//+30
	Stats*	ptItemStats;			//+34
	BYTE	uk4[0x04];				//+38
	Stats*	ptAffixStats;			//+3C
	Stats*	ptNextStats2;			//+40
	union
	{
		Unit*	ptChar;				//+44
		Unit*	ptItem;
	};
	D2Stat*	ptStatsTable;			//+48
	WORD	nbStats;				//+4C
	WORD	sizeOfStatsTable;		//+4E ??
	BYTE	uk5[0x8];				//+50
	BYTE*	unknow0;				//+58 (sizeof(*unknow0)=0x30 (calculated)
	DWORD	unknow1;				//+5C (=0)
	DWORD	unknow2;				//+60 (=0)
};


struct MonsterData					// sizeof(MonsterData)=0x60
{										//Offset from Code.
    BYTE	uk[0x16];					//+00
 	union {
		WORD	flags;					//+16
		struct {
			WORD	fuk1:1;
			WORD	isSuperUnique:1;
			WORD	isChampion:1;
			WORD	isUnique:1;
			WORD	fuk2:13;
		};
	};
   BYTE		uk1[0x0E];					//+18
   WORD		superUniqueID;				//+26
   void*	unknow1;					//+28
   BYTE		uk2[0x38];					//+28
};

struct ObjectData
{
	ObjectsBIN*	ptObjectsBIN;
	BYTE		levelID;
};
/*
Kingpin: struct MonsterData   
{  
     BYTE     uk1[0x13];          // +00  
     DWORD     Flags;               // +14  
     DWORD     uk2;               // +18  
     DWORD     MinionOwnerID;     // +1C  
     BYTE     uk3[0x5];          // +20  
     WORD     SuperUniqueID;     // +26 Superunique ID of monster  
     D2Game*     ptGame;               // +28 ptGame  
};
*/

#define F2_ITEM_IS_IDENTIFIED 0x10 //or F_IS_IDENTIFIED ?

struct ItemData//size=0x74
{										//Offset from Code.
	DWORD	quality;					//+00
	DWORD	seedLow;					//+04
	DWORD	seedHi;						//+08
	DWORD	playerID;					//+0C #10734 / #10735 (PCInventory->ptPlayer->0C)
	DWORD	seedStarting;				//+10
	DWORD	flags1;						//+14
	union {
		DWORD	flags2;					//+18
		struct {
			DWORD	fuk1:1;				//0x00000001
			DWORD	isIndentified:1;	//0x00000002
			DWORD	fuk2:2;				//0x0000000C
			DWORD	isUnindentified:1;	//0x00000010
			DWORD	fuk3:3;				//0x000000E0
			DWORD	isBroken:1;			//0x00000100
			DWORD	fuk4:2;				//0x00000600
			DWORD	isSocketed:1;		//0x00000800
			DWORD	fuk5:10;			//0x003FF000
			DWORD	isEtheral:1;		//0x00400000
			DWORD	fuk6:3;				//0x03800000
			DWORD	isRuneword:1;		//0x04000000
			DWORD	fuk7:1;				//0x08000000
			DWORD	isPersonalized:1;	//0x10000000
			DWORD	fuk8:3;				//0xE0000000
		};
	};
/*
ITEMFLAG_NEWITEM               = 0x00000001,  
ITEMFLAG_TAGETING               = 0x00000004,  
ITEMFLAG_UNIDENTIFIED               = 0x00000010,  
ITEMFLAG_QUANTITY               = 0x00000020,  
ITEMFLAG_Durability               = 0x00000100,  
ITEMFLAG_UNKNOWN2               = 0x00000400,  
ITEMFLAG_SOCKETED               = 0x00000800,  
ITEMFLAG_NON_SELLABLE               = 0x00001000,  
ITEMFLAG_NEWITEM2               = 0x00002000,  
ITEMFLAG_UNKNOWN3               = 0x00004000,  
ITEMFLAG_CHECKSECPRICE               = 0x00010000,  
ITEMFLAG_CHECKGAMBLEPRICE          = 0x00020000,  
ITEMFLAG_UNKNOWN4               = 0x00080000,  
ITEMFLAG_INDESTRUCTIBLE(ETHERAL) = 0x00400000,  
ITEMFLAG_UNKNOWN5               = 0x00800000,  
ITEMFLAG_FROMPLAYER               = 0x01000000,  
ITEMFLAG_RUNEWORD               = 0x04000000
*/
	DWORD	guid1;						//+1C Global Unique ID 1  
	DWORD	guid2;						//+20 Global Unique ID 2  
	DWORD	guid3;						//+24 Global Unique ID 3  
	DWORD	uniqueID;					//+28
	BYTE	ilvl;						//+2C
	BYTE	uk1[0x03];					//+2D
	WORD	version;					//+30
	WORD	rarePrefix;					//+32
	WORD	rareSuffix;					//+34
	WORD	autoPref;					//+36
	WORD	prefix[3];					//+38
	WORD	suffix[3];					//+3E
	BYTE	equipLoc;					//+44
    /*	emplacement si équipé
	*	00 = noequip/inBelt
	*   01 = head
	*	02 = neck
	*	03 = tors
	*	04 = rarm
	*	05 = larm
	*	06 = lrin
	*	07 = rrin
	*	08 = belt
	*	09 = feet
	*	0A = glov
	*	0B = ralt
	*	0C = lalt
*/
	BYTE	page;						//+45
    /*	page dans laquel se trouve l'item
    *	FF = mouse/equip/onEarth
    *	00 = inventory
    *   01 = cube
    *	04 = stash
    */
	BYTE	uk4[0x01];					//+46
	BYTE	ItemData3;					//+47 //D2Common10854 D2Common10853
	BYTE	pEarLevel;					//+48
	BYTE	varGfx;						//+49
	char	IName[0x12];				//+4A //inscribed/ear name  
	Inventory*	ptInventory;			//+5C
	Unit*	ptPrevItem;					//+60
	Unit*	ptNextItem;					//+64
	BYTE	uk8[0x01];					//+68
	BYTE	ItemData2;					//+69
	BYTE	uk9[0x0A];					//+6A
};


struct NetClient
{
	DWORD	clientID;					//+00
	BYTE	uk1[0x06];					//+04
	union {								//+0A
		WORD	flag;
		struct {
			WORD f1:1;
			WORD f2:1;
			WORD isHardCoreGame:1;
		};
	};
	BYTE	uk2[0x170];					//+0C
	BYTE*	savefile;					//+17C
	DWORD	finalSize;					//+180
	DWORD	counter;					//+184
	DWORD	currentSize;				//+188
	BYTE	uk3[0x1C];					//+18C
	Game*	ptGame;						//+1A8
	//+1A8 is ptGame
	//+4A8 ptNextClient
/*
Kingpin: ptPclient  
+16C is either act or unit type 
+170 Active UniqueID for player 
+174 Active ptPlayer on Client 
+1a8 ptGame 
+1b4 Current or next ptRoom  
*/
};
/*
struct PlayerData
{
	char		name[0x10];				//+00 (size min 0x08 max 0x11)
	BYTE		uk1[0x8C];				//+10
	NetClient*	ptNetClient;			//+9C
};
*/
struct PlayerData   
{  
	char		name[0x10];				//+00	Player Name  
	void*		ptQuest[3];				//+10	Quest Pointers for each difficulty  
	BYTE		uk1[0x18];				//+1C		//before : 0x14
	void*		ptArenaUnit;			//+34	ptArena for the Unit  
	BYTE		uk2[0x4];				//+38		//before : 0x7
	WORD		MPSourcePortalUniqueID;	//+3C	Source Portal Unique_ID  
	BYTE		uk3[0x2];				//+3E
	WORD		MPDestPortalUniqueID;	//+40	Destination Portal Unique_ID  
	BYTE		uk4[0x06];				//+42  
	BYTE		ptObjectUnID;			//+48	Object UniqueID for TownPortals       
	BYTE		uk5[0x53];				//+49  
	NetClient*	ptNetClient;			//+9C	ptClient  
};


#define F1_IS_SPAWNED 0x10 //or F_IS_IDENTIFIED ?
#define F2_IS_LOD 0x2000000
struct Unit
{										//Offset from Code.		Size: 0xF4+4
	DWORD		nUnitType;				//+00
	union{
		DWORD			nPlayerClass;
		DWORD			nTxtFileNo;         
    };									//+04
	DWORD		nUnitId;				//+08
	DWORD		nItemNum;				//+0C
	DWORD		CurrentAnim;			//+10
	union{
		MonsterData*	ptMonsterData;
		ObjectData*		ptObjectData;
		ItemData*		ptItemData;
		PlayerData*		ptPlayerData;
	};									//+14
	BYTE		act;					//+18
	BYTE		uk12[3];				//+19
	void*		ptAct;					//+1C
	DWORD		SeedLow;				//+20
	DWORD		SeedHi;					//+24
	DWORD		SeedStarting;			//+28
	Path*		path;					//+2C
	BYTE		uk1[0x08];				//+30
	Path*		ptPos;					//+38
	DWORD		animSpeed;				//+3C
	BYTE		uk2[0x04];				//+40
	DWORD		curFrame;				//+44
	DWORD		remainingFrame;			//+48
	WORD		animSpeedW;				//+4C
	BYTE		actionFlag;				//+4E
	BYTE		uk3[0x1];				//+4F
	void*		ptAnimData;				//+50
	BYTE		uk4[0x08];				//+54
	Stats*		ptStats;				//+5C
	Inventory*	ptInventory;		    //+60
	BYTE		uk5[0x1C];				//+64
	Game*		ptGame;					//+80
	BYTE		uk6[0x24];				//+84
	Skills*		ptSkills;				//+A8
	void*		ptCombatData;			//+AC
	BYTE		uk7[0x08];				//+B0
	DWORD		itemCode;				//+B8 for an item being dropped by this unit
	BYTE		uk8[0x08];				//+BC
	DWORD		flags1;					//+C4
	union{
		DWORD		flags2;				//+C8	//flags
		struct{
			DWORD	ukf1:25;
			DWORD	isLod:1;
		};
	};
	BYTE		uk9[0x04];				//+CC
	DWORD		clientId;				//+D0
	BYTE		uk10[0x0C];				//+D4
	Unit*		ptFirstMonster;			//+E0
	Unit*		Unit1;					//+E4
	Unit*		Unit2;					//+E8
	BYTE		uk11[0x08];				//+EC
	union{
		CBPlayerData*	ptCBPlayerData;
		CBItemData*		ptCBItemData;
		void*			ptCBData;
	};									//+F4
};



/*
struct D2Game
{
    DWORD unknown[19];
    WORD  difficulty;
};

struct ItemMod
{
	DWORD mID;			// +00 Mod ID, get it from properties.txt
	DWORD mParam;		// +04 First Property
	DWORD mMinimum;		// +04 Second Property, Min Value
	DWORD mMaximum;		// +04 Third Property, Max Value
};

struct AIStruct
{
    DWORD mSpawn;       // +00
    void* mAIFunc;      // +04
    DWORD mUnknown1[8]; // +08
    D2Game* mGame;      // +28
    DWORD mMinionOwner; // +2C
    DWORD mOwnerType;   // +30
};


struct LocInfo
{                       //Offset from Code
    Unit* noneLoc;      //+00
    Unit* headLoc;      //+04
    Unit* neckLoc;      //+08
    Unit* torsoLoc;     //+0c
    Unit* rightArmLoc;  //+10
    Unit* leftArmLoc;   //+14
    Unit* rightRingLoc; //+18
    Unit* leftRingLoc;  //+1c
    Unit* beltLoc;      //+20
    Unit* feetLoc;      //+24
    Unit* glovesLoc;    //+28
};

struct ItemData 
{                        // Offset from Code
	DWORD quality;       // +00.
    DWORD lowSeed;       // +04.
    DWORD highSeed;      // +08.
    DWORD unknown1;      // +0c.
    DWORD startLowSeed;  // +10.
    DWORD cmdFlags;      // +14.
    DWORD flags;         // +18.
    DWORD unknown2[2];   // +1C
    DWORD originID;      // +24.
    DWORD iLvl;          // +28.
    WORD  version;       // +2C.
    WORD  prefix;        // +2E.
    WORD  suffix;        // +30.
    WORD  autoPrefix;    // +32.
    WORD  prefix1;       // +34.
    WORD  prefix2;       // +36.
    WORD  prefix3;       // +38.
    WORD  suffix1;       // +3A.
    WORD  suffix2;       // +3C.
    WORD  suffix3;       // +3E.
    BYTE  bodyLoc;       // +40.	// 0=inv/stash 4=gaucheS 5=droiteS
    BYTE  inPage;        // +41.	// FF=equip 00=inv 04=stash
    BYTE  unknown3[3];   // +42
    BYTE  picture[8];    // +45
    DWORD ilvl;          // +4C
};

struct PresetUnit 
{                                   //Offset from Code
	DWORD           unitType;       //+00
	DWORD           txtFileNo;      //+04
	DWORD           unknown1[1];    //Unkonwn Data at +08
	DWORD           xPos;           //+0c
	DWORD           yPos;           //+10
	DWORD           unknown2[2];    //Unknown data at +14
	PresetUnit*     pNext;          //+1c
};

struct MissileData
{
+04 flags 
+08 0 on start 
+0c -1 on start 
+20 nDirection 
+28 range? 
+2c range? 
+30 level 
+34 number of pierces (byte) 
+35 (byte) 
+36 (byte) 
+37 (byte) 
+38 range-activate 
};


struct Combat 
{
	DWORD mHeader;		// +00 : Always 0x32 
	DWORD mDisplayFlag;	// +04 : Affect critical hit etc ...
	DWORD mPhysicalDmg; // +08 : Values are << 8
	DWORD mUnknown1;    // +0C
	DWORD mFireDmg;		// +10 : Values are << 8
	DWORD mUnknown2;    // +14
    DWORD mBurnLeng;    // +18
    DWORD mLtngDmg;     // +1C : values are << 8
    DWORD mMagDmg;      // +20 : values are << 8
    DWORD mColdDmg;     // +24 : values are << 8
    DWORD mPoisDmg;     // +28 : ??
    DWORD mPoisLeng;    // +2C
    DWORD mColdLeng;    // +30
    DWORD mFreezeLeng;  // +34
    DWORD mLifeSteal;   // +38
    DWORD mManaSteal;   // +3C
    DWORD mUnknwon3;    // +40
    DWORD mStunLeng;    // +44
    DWORD mUnknown4;    // +48
    DWORD mTotalDamage; // +4C
    DWORD mUnknown5[6]; // +50
    DWORD mOverlay;     // +68
    DWORD mUnknwon6;    // +6C
};


struct Node
{                       //Offset from Code.
    DWORD flag;         //+00 //Yoh : null->flag
    Unit* ptItem;  		//+04 //Yoh : ItemData=>Unit
    DWORD unID;         //+08
    DWORD page;         //+0c //Yoh plutot etat : inventory/stash=1; inv-belt=2; equip=3
    Node* nextNode;     //+10
};



struct MonsterData				// size110 : 60
{
    AIStruct*     AIPtr;
    void*         unkonwPtr1;
    void*         uniqueInfo;
    void*         spawnInfo;
    void*         unknownPtr2;
    DWORD         unkown[8];
    void*         lvlPtr;
    MonStatTxt*   monstatPtr;
};


struct Unit 
{                               //Offset from Code.
	DWORD   nUnitType;          //+00
    union 
    {
	    DWORD   nTxtFileNo;         
        DWORD   nPlayerClass;
    };                          //+04

	DWORD   nUnitId;            //+08
	DWORD   eMode;              //+0c
    DWORD*  unknow1;            //+10
    DWORD   nAct;               //+14
    DWORD   pActRelated;        //+18
    DWORD   unknown2[4];        //Unknown Data at +1C
    D2Seed  nSeed;              //+2C
    DWORD   startSeed;          //+34
    Path*   pPos;               //+38
	DWORD   unknown3[6];        //Unknown Data at +3C
    DWORD   animSpeed;          //+54
    DWORD   unknown32[2];       //+58
    BYTE    COFString[12];      //+60
    Stats*  ptStats;            //+6C
	
    union 
    {
		PlayerData*     pPlayerData;
		MonsterData*    pMonsterData;
		ItemData*       pItemData;
        MissileData*    pMissile;
		ObjectData*     pObjectData;
	};                          //+70

	DWORD   unknown5[2];        //+74
    BYTE    unknown6[2];        //+7C
    BYTE    rndDmg[2];          //+7e
    DWORD   unknown7;           //+80
	Inventory*  ptInventory;    //+84
	DWORD   unknown8[4];        //+88
    DWORD   startNull;          //+98
    DWORD   unknown9[2];        //+9c
    D2Game* ptGame;             //+a4
    DWORD   unknown10[4];       //+a8
	DWORD   nOwnerType;         //+b8
	DWORD   nOwnerId;           //+bc
    DWORD   unknown11[3];       //+c0
    D2Info* ptInfo;             //+cc
    Combat* ptCombat;           //+d0
    DWORD   unknown12[5];       //+d4
    DWORD   flags;              //+e8
    DWORD   LODflag;            //+ec
	DWORD   unknown13[7];       //+f0
	Unit*   pNext;              //+10c
	DWORD	unknown14[2];		//+110	//YOH
    union 
    {
		ItemData*       ptItemData;
		void*            ptData;
	};                          //+118	//YOH
};
*/
/*================================= END OF FILE =================================*/