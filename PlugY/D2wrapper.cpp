/*=================================================================
	File created by Yohann NICOLAS.

    @file D2wrapper.cpp
    @brief Main Diablo II extra DLL handler.

    This is the sources of the D2DLL class.

=================================================================*/

// Core Class Headers
#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "customLibraries.h"

/* Beginning of Custom Header */
#include "globalVariable.h"		// Install_VariableOnRealm()
#include "commands.h"			// Install_Commands()
#include "othersFeatures.h"		// Install_ChangeResolution()
#include "mainScreen.h"			// Install_PrintPlugYVersion() Install_VersionChange()
#include "savePath.h"			// Install_ChangingSavePath()
#include "bigStash.h"			// Install_BigStash()
#include "skillPerLevelUp.h"	// Install_SkillPerLevelUp()
#include "statPerLevelUp.h"		// Install_StatPerLevelUp()
#include "statsPoints.h"		// Install_StatsPoints() Install_StatsLimitShiftClick()
#include "skillsPoints.h"		// Install_SkillsPoints()
#include "infinityStash.h"		// Install_MultiPageStash()
#include "newInterfaces.h"		// Install_NewInterfaces()
#include "worldEvent.h"			// Install_WorldEvent()
#include "uberQuest.h"			// Install_UberQuest()
#include "extraOptions.h"		// Install_AlwaysRegenMapInSP()
#include "language.h"			// Install_LanguageManagement()


int version_SmackW32=V113;
int version_D2Common=V113;
int version_ijl11=V113;
int version_D2Gdi=V113;
int version_D2Win=V113;
int version_D2sound=V113;
int version_D2MCPCLI=V113;
int version_D2Launch=V113;
int version_D2gfx=V113;
int version_D2Client=V113;
int version_D2Net=V113;
int version_D2Lang=V113;
int version_D2Game=V113;
int version_D2CMP=V113;
int version_Bnclient=V113;
int version_Fog=V113;
int version_Storm=V113;


DWORD	offset_SmackW32=NULL;
DWORD	offset_D2Common=NULL;
DWORD	offset_ijl11=NULL;
DWORD	offset_D2Gdi=NULL;
DWORD	offset_D2Win=NULL;
DWORD	offset_D2sound=NULL;
DWORD	offset_D2Multi=NULL;
DWORD	offset_D2MCPCLI=NULL;
DWORD	offset_D2Launch=NULL;
DWORD	offset_D2gfx=NULL;
DWORD	offset_D2Game=NULL;
DWORD	offset_D2Client=NULL;
DWORD	offset_D2Net=NULL;
DWORD	offset_D2Lang=NULL;
DWORD	offset_D2CMP=NULL;
DWORD	offset_Bnclient=NULL;
DWORD	offset_Fog=NULL;
DWORD	offset_Storm=NULL;
// manque : Game.exe D2DDraw.dll D2Direct3D.dll D2Glide.dll

const char* S_SmackW32 =	"SmackW32.dll";
const char* S_D2Common =	"D2Common.dll";
const char* S_ijl11 =		"ijl11.dll";
const char* S_D2Gdi =		"D2Gdi.dll";
const char* S_D2Win =		"D2Win.dll";
const char* S_D2sound =		"D2sound.dll";
const char* S_D2Multi =		"D2Multi.dll";
const char* S_D2MCPCLI =	"D2MCPClient.dll";
const char* S_D2Launch =	"D2Launch.dll";
const char* S_D2gfx =		"D2gfx.dll";
const char* S_D2Game =		"D2Game.dll";
const char* S_D2Client =	"D2Client.dll";
const char* S_D2Net =		"D2Net.dll";
const char* S_D2Lang =		"D2Lang.dll";
const char* S_D2CMP =		"D2CMP.dll";
const char* S_Bnclient =	"Bnclient.dll";
const char* S_Fog =			"Fog.dll";
const char* S_Storm =		"Storm.dll";

const char* S_CloneBattles ="CloneBattles.dll";
const char* S_DarkAlliance ="DarkAlliance.dll";

DWORD loadLibrary( const char* libraryName)
{
	DWORD offset;
/*	char currentpath[MAX_PATH];

	if (!strcmp(libraryName,"D2Common.dll") || !strcmp(libraryName,"D2Game.dll") || !strcmp(libraryName,"D2Client.dll"))
	{
		GetCurrentDirectory(MAX_PATH,currentpath);
		strncat(currentpath,"\\",MAX_PATH);
		strncat(currentpath,libraryName,MAX_PATH);
		log_msg("Load = %s : ",currentpath);
		offset = (DWORD)LoadLibrary(currentpath);
		log_msg("offset = %08X\n",offset);
		if (offset)
		{
			log_msg("%s loaded successfully at: %08X\n", libraryName,	offset);			
			return offset;
		}
	}*/
	offset = (DWORD)LoadLibrary(libraryName);
	if (!offset)
	{
		log_msg("Failed to load library : %s\n", libraryName);
		exit(-1);
	}
	log_msg("%s loaded successfully at: %08X\n", libraryName,	offset);

	return offset;
}

void freeLibrary( DWORD library )
{
	if (library)
		FreeLibrary((HINSTANCE__ *)library);
}

// Change the protection scheme of a loaded
// DLL called libraryName in memory space at address addr+size to allow us to customize it.
void hookLibrary(const char* libraryName, DWORD addr)
{
	DWORD dw=0;
	BYTE* offsetPESignature = addr + *(BYTE**)((BYTE*)addr + 0x3C);
	DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
	BYTE* baseOfCode = addr + *(BYTE**)(offsetPESignature + 0x2C);
	if( !VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READWRITE, &dw) )
	{
		log_msg("Failed to hook library : %s. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
		exit(-1);
	}
	log_msg("%s successfully hooked. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
}

void unhookLibrary(const char* libraryName, DWORD addr)
{
	DWORD dw=0;
	BYTE* offsetPESignature = addr + *(BYTE**)((BYTE*)addr + 0x3C);
	DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
	BYTE* baseOfCode = addr + *(BYTE**)(offsetPESignature + 0x2C);
	if( !VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READ, &dw) )
		log_msg("Failed to unhook library : %s. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
	else
		log_msg("%s successfully unhooked. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
}


void loadD2Libraries ()
{
	log_msg("***** Load D2 Libraries *****\n");

	offset_SmackW32	= loadLibrary( S_SmackW32);		//0xD000	0x03B90000 Already Loaded	-
	offset_D2Common	= loadLibrary( S_D2Common);		//0x8D000	0x037A0000					0x7C000
	offset_ijl11	= loadLibrary( S_ijl11);		//0x24000	0x60000000 Already Loaded	-
	offset_D2Gdi	= loadLibrary( S_D2Gdi);		//0x7000	0x6F830000 Already Loaded	-
	offset_D2Win	= loadLibrary( S_D2Win);		//0x19000	0x6F8A0000 Already Loaded	0x1C000
	offset_D2sound	= loadLibrary( S_D2sound);		//0xC000	0x6F980000 Already Loaded	0xD000
//	offset_D2Multi	= loadLibrary( S_D2Multi);		//0x1000	0x6F9A0000					?
//	offset_D2MCPCLI	= loadLibrary( S_D2MCPCLI);		//0x6000	0x6F9F0000 Already Loaded	-
	offset_D2Launch	= loadLibrary( S_D2Launch);		//0x20000	0x6FA10000 Already Loaded	0x1E000
	offset_D2gfx	= loadLibrary( S_D2gfx);		//0xB000	0x6FA70000 Already Loaded	-
	offset_D2Game	= loadLibrary( S_D2Game);		//0xF6000	0x6FC30000					0xCF000
	offset_D2Client	= loadLibrary( S_D2Client);		//0xCC000	0x6FAA0000					0xCA000
	offset_D2Net	= loadLibrary( S_D2Net);		//0x6000	0x6FC00000 Already Loaded	-	
	offset_D2Lang	= loadLibrary( S_D2Lang);		//0x0A000	0x6FC10000 Already Loaded	-
	offset_D2CMP	= loadLibrary( S_D2CMP);		//0x18000	0x6FDF0000 Already Loaded	0x19000
	offset_Bnclient	= loadLibrary( S_Bnclient);		//0x15000	0x6FF00000 Already Loaded	-
	offset_Fog		= loadLibrary( S_Fog);			//0x20000	0x6FF50000 Already Loaded	0x1F000
	offset_Storm	= loadLibrary( S_Storm);		//0x30000	0x6FFB0000 Already Loaded	-

	log_msg("\n\n");
}


void freeD2Libraries()
{
	log_msg("***** Free Libraries *****\n");

	freeLibrary( offset_SmackW32 );
	freeLibrary( offset_D2Common );
	freeLibrary( offset_ijl11 );
	freeLibrary( offset_D2Gdi );
	freeLibrary( offset_D2Win );
	freeLibrary( offset_D2sound );
//	freeLibrary( offset_D2Multi );
//	freeLibrary( offset_D2MCPCLI );
	freeLibrary( offset_D2Launch );
	freeLibrary( offset_D2gfx );
	freeLibrary( offset_D2Game );
	freeLibrary( offset_D2Client );
	freeLibrary( offset_D2Net );
	freeLibrary( offset_D2Lang );
	freeLibrary( offset_D2CMP );
	freeLibrary( offset_Bnclient );
	freeLibrary( offset_Fog	);
	freeLibrary( offset_Storm );

	log_msg("\n\n");
}

void hookLibraries()
{
	log_msg("***** Unprotect Libraries *****\n");

	hookLibrary(S_D2Common,	offset_D2Common);
	hookLibrary(S_D2Client,	offset_D2Client);
	hookLibrary(S_D2Lang,	offset_D2Lang);
	hookLibrary(S_D2Game,	offset_D2Game);
	hookLibrary(S_Fog,		offset_Fog);
	hookLibrary(S_Storm,	offset_Storm);
//	hookLibrary(S_D2Win,	offset_D2Win);
	hookLibrary(S_D2Launch,	offset_D2Launch);
	hookLibrary(S_D2gfx,	offset_D2gfx);
//	hookLibrary(S_D2Gdi,	offset_D2Gdi);

	log_msg("\n\n");
}

void unhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

	unhookLibrary(S_D2Common,	offset_D2Common);
	unhookLibrary(S_D2Client,	offset_D2Client);
	unhookLibrary(S_D2Lang,		offset_D2Lang);
	unhookLibrary(S_D2Game,		offset_D2Game);
	unhookLibrary(S_Fog,		offset_Fog);
	unhookLibrary(S_Storm,		offset_Storm);
//	unhookLibrary(S_D2Win,		offset_D2Win);
	unhookLibrary(S_D2Launch,	offset_D2Launch);
	unhookLibrary(S_D2gfx,		offset_D2gfx);
//	unhookLibrary(S_D2Gdi,		offset_D2Gdi);

	log_msg("\n\n");
}

void freeCustomLibraries()
{
	log_msg("***** Free custom libraries *****\n");

	TCustomDll* dll=customDlls;
	TCustomDll* nextDll;
	while (dll)
	{
		dll->release();
		freeLibrary(dll->offset);
		nextDll = dll->nextDll;
		D2FogMemDeAlloc(dll,__FILE__,__LINE__,0);
		dll = nextDll;
	}
}

void initCustomLibraries()
{
	log_msg("***** Init custom libraries *****\n");

	TCustomDll* dll=customDlls;
	while (dll)
	{
		dll->init();
		dll = dll->nextDll;
	}
}

void loadCustomLibraries()
{
	char* curString = NULL;
	TCustomDll* nextDll;
	DWORD offset_currentDll;

	log_msg("***** Custom libraries *****\n");

	if (dllFilenames)
		curString = strtok(dllFilenames,"|");

	if (!curString)
		log_msg("No custom libraries to load.\n");
	else
	{
		log_msg("Load custom libraries :\n");
		while (curString)
		{
			if (curString[0])
			{
				offset_currentDll = loadLibrary(curString);
				if (offset_currentDll)
				{
					nextDll = customDlls;
					customDlls = new(TCustomDll);
					customDlls->nextDll = nextDll;
					customDlls->initialize(offset_currentDll);
				}
			}
			curString=strtok(NULL,"|");
		}
	}
	if(dllFilenames)
		D2FogMemDeAlloc(dllFilenames,__FILE__,__LINE__,0);

	log_msg("\n\n");
}


/*
void getVersion(DWORD addr, DWORD addr111, int* ver, DWORD v109b, DWORD v109d, DWORD v110, DWORD v111, DWORD v111a, DWORD v111b, DWORD v112, DWORD v113, const char * filename)
{
	log_msg("version of %s\t",filename);

	if (addr==v109b) {
		*ver = V109b;
		log_msg("1.09b\n");
	} else if (addr==v109d) {
		*ver = V109d;
		log_msg("1.09d\n");
	} else if (addr==v110) {
		*ver = V110;
		log_msg("1.10\n");
	} else if ((addr==v111) && (addr111==v111a)) {
		*ver = V111;
		log_msg("1.11\n");
	} else if ((addr==v111) && (addr111==v111b)) {
		*ver = V111b;
		log_msg("1.11b\n");
	} else if (addr==v112) {
		*ver = V112;
		log_msg("1.12\n");
	} else if (addr==v113) {
		*ver = V113;
		log_msg("1.13\n");
	} else {
		*ver = V113;
		log_msg("unknow, try with 1.13\n");
	}
}
#define GET_VERSION(F,X,Y,A,B,C,D,E,G,H,I) getVersion(*(DWORD*)(offset_##F + 0x##X), *(DWORD*)(offset_##F + 0x##Y), &version_##F, 0x##A, 0x##B, 0x##C, 0x##D, 0x##E, 0x##G, 0x##H, 0x##I, S_##F)
bool initD2version()
{
	log_msg("***** Get dll versions *****\n");


//GET_VERSION(SmackW32
	GET_VERSION(D2Common,	80, 108,	B03A26A0, 9E3DE7CC, 0355C185, 8402CA7A, 42E6C2E5, 43028BA5, E58C71DA, 00000000);
//GET_VERSION(ijl11
	GET_VERSION(D2Gdi,		80, 108,	90CFD95A, 86CE337B, A8CCC67B, 06059D7D, 42E6C248, 43028B2F, 5D6490A2, 00000000);
	GET_VERSION(D2Win,		80, 108,	B595A0CD, 1995DAD2, A8F5E2FD, B6DAB75A, 42E6C266, 43028B44, 6AA01FF5, 00000000);
//GET_VERSION(D2sound
//GET_VERSION(D2MCPCLI
	GET_VERSION(D2Launch,	80, 100,	A66532FF, 66678CC5, 686223E5, 80B0E2C6, 42E6C275, 43028B50, 205A4C0F, 00000000);
	GET_VERSION(D2gfx,		80, 110,	00949FA8, 018866A8, 401526B2, 575C8A5E, 42E6C22A, 43028B19, ACBE1B9E, 00000000);
	GET_VERSION(D2Client,	80, 108,	03522F39, 6730B639, C9817825, 37EC6E13, 42E6C43F, 43028CA5, 61A3B3D5, 00000000);
	GET_VERSION(D2Net,		80, 0F0,	E60F4DEA, 940E178B, 890FCC0B, C293A9D5, 42E6C20D, 43028B05, 19FA9F76, 00000000);
	GET_VERSION(D2Lang,		80, 0F8,	111DCCB7, 13978953, DF917353, B91BAEA2, 42E6C213, 43028B09, B7B3978E, 00000000);
	GET_VERSION(D2Game,		80, 108,	B0805792, 8BB2C392, 92FA18E6, 00B6F7B7, 42E6C375, 43028C0D, BD8DD8E5, 00000000);
	GET_VERSION(D2CMP,		80, 0F8,	BA755486, 9A77DFEE, 38F44382, 4059B13F, 42E6C203, 43028AFE, 33A9427B, 00000000);
//GET_VERSION(Bnclient
	GET_VERSION(Fog,		80, 100,	6F16123B, 75990846, 7E7ED3C7, D333B997, 42E6C1F0, 43028AF2, D3BD4F1B, 00000000);
	GET_VERSION(Storm,		E0, 110,	3B4B41D8, 3B8AB1CE, 00004550, 9C2BECC4, 42E6C1CA, 43028AD9, E4FA2944, 00000000);

	log_msg("\n\n");
	return true;
}
*/

void getVersion(DWORD addr, int* ver, DWORD v109b, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113, const char * filename)
{
	log_msg("version of %s\t",filename);

	if (addr==v109b) {
		*ver = V109b;
		log_msg("1.09b\n");
	} else if (addr==v109d) {
		*ver = V109d;
		log_msg("1.09d\n");
	} else if (addr==v110) {
		*ver = V110;
		log_msg("1.10\n");
	} else if (addr==v111) {
		*ver = V111;
		log_msg("1.11\n");
	} else if (addr==v111b) {
		*ver = V111b;
		log_msg("1.11b\n");
	} else if (addr==v112) {
		*ver = V112;
		log_msg("1.12\n");
	} else if (addr==v113) {
		*ver = V113;
		log_msg("1.13\n");
	} else {
		*ver = V113;
		log_msg("unknow, try with 1.13\n");
	}
}
#define GET_VERSION(F,X,A,B,C,D,E,G,H) getVersion(*(DWORD*)(offset_##F + 0x##X), &version_##F, 0x##A, 0x##B, 0x##C, 0x##D, 0x##E, 0x##G, 0x##H, S_##F)
bool initD2version()
{
	log_msg("***** Get dll versions *****\n");

//GET_VERSION(SmackW32
	GET_VERSION(D2Common,	10CA,	A1E86FDC, B1E86FDC, 72D03B42, F883057E, 16746AC6, 00FE81C3, 74FE85DB);
//GET_VERSION(ijl11
	GET_VERSION(D2Gdi,		105,	B4000000, 0B210E00, E4000000, 48000401, 2F000401, 00000000, B7000401);
	GET_VERSION(D2Win,		1699,	88686F8C, 84686F8C, D094686F, F0030000, 001435E8, 8B088F44, 0013F5E8);
//GET_VERSION(D2sound
//GET_VERSION(D2MCPCLI
	GET_VERSION(D2Launch,	109A,	81E8526F, 01E8526F, 85E8526F, 247C8B00, 00FC6583, 15FF0424, E850E045);
	GET_VERSION(D2gfx,		10D,	EB000000, 006FA700, 00000010, 2A000401, 19000401, 0B210E00, 00000000);
	GET_VERSION(D2Client,	17F,	00000000, 14500000, 12500000, 0D814800, 0D812800, 0DA01000, 0DA03000);
	GET_VERSION(D2Net,		16E1,	78B8A73C, 68B8A73C, 10244C8B, 5349E808, 5EA9E808, 105D8B72, 53B9E808);
	GET_VERSION(D2Lang,		126D,	FC45048B, F445048B, 02C18313, C4830000, 00C6E045, 8B48408B, 0C75FF0C);
//	GET_VERSION(D2Game,		1010,	D22A78A1, D22910A1, D43FB0A1, 03E8506F, 53E8506F, 89E8506F, 63E8506F);
	GET_VERSION(D2Game,		1092,	18968BF1, 38968BF1, 28968BF1, F6335608, C690C5B9, 895FD713, 56535700);
	GET_VERSION(D2CMP,		1359,	3C686FE0, 38686FE0, 8BF78B56, 4C880424, 07C71824, CCCCCCCC, C7000005);
//GET_VERSION(Bnclient
	GET_VERSION(Fog,		102,	D0000006, 10000001, 00000006, 000042E6, 00004302, 0000483C, 00004B95);
	GET_VERSION(Storm,		1190,	19E85082, 59E85082, 13C103F6, 0474F685, 8B000321, 3B1074C9, 0D896404);

	log_msg("\n\n");
	return true;
}
//////////////////////////////////// EXPORTS FUNCTIONS ////////////////////////////////////

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
	if (IniName) log_msg("* PlugY is called from D2mod.dll\n\n");
	else log_msg("* PlugY is called from D2gfx.dll\n\n");

	static int isInstalled = false;
	if (isInstalled) return NULL;
	isInstalled=true;

	loadD2Libraries();

	if (!initD2version()) return NULL;

	if (!initD2functions()) return NULL;

	loadParameters();

	if (!active_plugin)	return NULL;

	loadCustomLibraries();

	hookLibraries();

	log_msg("***** INSTALL FUNCTIONS *****\n");

	Install_VariableOnRealm();

	if (active_Commands)
		Install_Commands();

	if (active_ChangeLanguage || active_LanguageManagement)
		Install_LanguageManagement();

	if (active_VersionTextChange)
		Install_VersionChange();

	if (active_PrintPlugYVersion || active_Windowed)
		Install_PrintPlugYVersion();

	if (active_StatsPoints)
		Install_StatsPoints();
	else if (active_DisplayBaseStatsValue)
		Install_DisplayBaseStatsValue();

	if (active_SkillsPoints)
		Install_SkillsPoints();

	if (active_changingSavePath)
		Install_ChangingSavePath();

	if (active_StatsShiftClickLimit)
		Install_StatsLimitShiftClick();

	if (active_RunLODs)
		Install_RunLODs();

	if (active_bigStash)
		Install_BigStash();

	if (active_SkillPerLevelUpChange)
		Install_SkillPerLevelUp();

	if (active_StatPerLevelUpChange)
		Install_StatPerLevelUp();

	if (active_multiPageStash)
		Install_MultiPageStash();

	if (active_othersFeatures)
		Install_OthersFeatures();

	if (active_newInterfaces)
		Install_NewInterfaces();

	if (active_WorldEvent)
		Install_WorldEvent();

	if (active_UberQuest)
		Install_UberQuest();

	if (active_alwaysRegenMapInSP)
		Install_AlwaysRegenMapInSP();

	if (nbPlayersCommandByDefault)
		Install_SendPlayersCommand();

	if (active_DisplayItemLevel)
		Install_DisplayItemLevel();

	if (active_AlwaysDisplayLifeMana)
		Install_AlwaysDisplayLifeMana();

	if (active_EnabledTXTFilesWithMSExcel)
		Install_EnabledTXTFilesWithMSExcel();

	if (active_LadderRunewords)
		Install_LadderRunewords();

	if (active_EnabledCowPortalWhenCowKingWasKill)
		Install_EnabledCowPortalWhenCowKingWasKill();

	log_msg("\nDLL patched sucessfully.\n\n\n");

	unhookLibraries();

	initCustomLibraries();

	log_msg("***** ENTERING DIABLO II *****\n\n" );

	active_logFile = active_logFile - 1;

	return NULL;
}



extern "C" __declspec(dllexport) bool __stdcall Release()
{
	log_msg("\n***** ENDING DIABLO II *****\n\n" );

	freeCustomLibraries();
	freeD2Libraries();
	return true;
}

/*================================= END OF FILE =================================*/