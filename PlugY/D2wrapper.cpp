/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.
    Add support 1.14d by haxifix.

    @file D2wrapper.cpp
    @brief Main Diablo II extra DLL handler.

    This is the sources of the D2DLL class.

=================================================================*/

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
#include "windowed.h"			// installed with Install_PrintPlugYVersion()
#include "customLibraries.h"
#include "common.h"

#include "interface_Stash.h"

int version_Game = UNKNOWN;
//int version_binkw32 = UNKNOWN;
//int version_Bnclient = UNKNOWN;
int version_D2Client = UNKNOWN;
int version_D2CMP = UNKNOWN;
int version_D2Common = UNKNOWN;
//int version_D2DDraw = UNKNOWN;
//int version_D2Direct3D = UNKNOWN;
int version_D2Game = UNKNOWN;
//int version_D2Gdi = UNKNOWN;
int version_D2gfx = UNKNOWN;
//int version_D2Glide = UNKNOWN;
int version_D2Lang = UNKNOWN;
int version_D2Launch = UNKNOWN;
//int version_D2MCPClient = UNKNOWN;
//int version_D2Multi = UNKNOWN;
int version_D2Net = UNKNOWN;
//int version_D2sound = UNKNOWN;
int version_D2Win = UNKNOWN;
int version_Fog = UNKNOWN;
//int version_ijl11 = UNKNOWN;
//int version_SmackW32 = UNKNOWN;
int version_Storm = UNKNOWN;

DWORD	offset_Game = NULL;
//DWORD	offset_binkw32 = NULL;
//DWORD	offset_Bnclient = NULL;
DWORD	offset_D2Client = NULL;
DWORD	offset_D2CMP = NULL;
DWORD	offset_D2Common = NULL;
//DWORD	offset_D2DDraw = NULL;
//DWORD	offset_D2Direct3D = NULL;
DWORD	offset_D2Game = NULL;
//DWORD	offset_D2Gdi = NULL;
DWORD	offset_D2gfx = NULL;
//DWORD	offset_D2Glide = NULL;
DWORD	offset_D2Lang = NULL;
DWORD	offset_D2Launch = NULL;
//DWORD	offset_D2MCPClient = NULL;
//DWORD	offset_D2Multi = NULL;
DWORD	offset_D2Net = NULL;
//DWORD	offset_D2sound = NULL;
DWORD	offset_D2Win = NULL;
DWORD	offset_Fog = NULL;
//DWORD	offset_ijl11 = NULL;
//DWORD	offset_SmackW32 = NULL;
DWORD	offset_Storm = NULL;

const char* S_Game =		"Game.exe";
//const char* S_binkw32 =		"binkw32.dll";
//const char* S_Bnclient =	"Bnclient.dll";
const char* S_D2Client =	"D2Client.dll";
const char* S_D2CMP =		"D2CMP.dll";
const char* S_D2Common =	"D2Common.dll";
//const char* S_D2DDraw =		"D2DDraw.dll";
//const char* S_D2Direct3D =	"D2Direct3D.dll";
const char* S_D2Game =		"D2Game.dll";
//const char* S_D2Gdi =		"D2Gdi.dll";
const char* S_D2gfx =		"D2gfx.dll";
//const char* S_D2Glide =		"D2Glide.dll";
const char* S_D2Lang =		"D2Lang.dll";
const char* S_D2Launch =	"D2Launch.dll";
//const char* S_D2MCPClient =	"D2MCPClient.dll";
//const char* S_D2Multi =		"D2Multi.dll";
const char* S_D2Net =		"D2Net.dll";
//const char* S_D2sound =		"D2sound.dll";
const char* S_D2Win =		"D2Win.dll";
const char* S_Fog =			"Fog.dll";
//const char* S_ijl11 =		"ijl11.dll";
//const char* S_SmackW32 =	"SmackW32.dll";
const char* S_Storm =		"Storm.dll";

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

void freeLibrary( DWORD library )
{
	if (library && library != offset_Game)
		FreeLibrary((HMODULE)library);
}

void freeD2Libraries()
{
	if (version_Game >= V114a)
		return;

	log_msg("***** Free Libraries *****\n");

//	freeLibrary( offset_binkw32 );
//	freeLibrary( offset_Bnclient );
	freeLibrary( offset_D2Client );
	freeLibrary( offset_D2CMP );
	freeLibrary( offset_D2Common );
//	freeLibrary( offset_D2DDraw );
//	freeLibrary( offset_D2Direct3D );
	freeLibrary( offset_D2Game );
//	freeLibrary( offset_D2Gdi );
	freeLibrary( offset_D2gfx );
//	freeLibrary( offset_D2Glide );
	freeLibrary( offset_D2Lang );
	freeLibrary( offset_D2Launch );
//	freeLibrary( offset_D2MCPClient );
//	freeLibrary( offset_D2Multi );
	freeLibrary( offset_D2Net );
//	freeLibrary( offset_D2sound );
	freeLibrary( offset_D2Win );
	freeLibrary( offset_Fog );
//	freeLibrary( offset_ijl11 );
//	freeLibrary( offset_SmackW32 );
	freeLibrary( offset_Storm );

	log_msg("\n\n");
}

void hookLibraries()
{
	log_msg("***** Unprotect Libraries *****\n");

    if (version_Game == V114d) {
        hookLibrary(S_Game, offset_Game);
    } else {
        hookLibrary(S_D2Client, offset_D2Client);
        //	hookLibrary(S_D2CMP,	offset_D2CMP);
        hookLibrary(S_D2Common, offset_D2Common);
        hookLibrary(S_D2Game, offset_D2Game);
        hookLibrary(S_D2gfx, offset_D2gfx);
        hookLibrary(S_D2Lang, offset_D2Lang);
        hookLibrary(S_D2Launch, offset_D2Launch);
        //	hookLibrary(S_D2Net,	offset_D2Net);
        //	hookLibrary(S_D2Win,	offset_D2Win);
        hookLibrary(S_Fog, offset_Fog);
        hookLibrary(S_Storm, offset_Storm);
    }

	log_msg("\n\n");
}

void unhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

    if (version_Game == V114d) {
        unhookLibrary(S_Game, offset_Game);
    } else {
        unhookLibrary(S_D2Client, offset_D2Client);
        //	unhookLibrary(S_D2CMP,		offset_D2CMP);
        unhookLibrary(S_D2Common, offset_D2Common);
        unhookLibrary(S_D2Game, offset_D2Game);
        unhookLibrary(S_D2gfx, offset_D2gfx);
        unhookLibrary(S_D2Lang, offset_D2Lang);
        unhookLibrary(S_D2Launch, offset_D2Launch);
        //	unhookLibrary(S_D2Net,		offset_D2Net);
        //	unhookLibrary(S_D2Win,		offset_D2Win);
        unhookLibrary(S_Fog, offset_Fog);
        unhookLibrary(S_Storm, offset_Storm);
    }

	log_msg("\n\n");
}

void freeCustomLibraries()
{
	if (!customDlls)
		return;

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
				offset_currentDll = (DWORD)LoadLibrary(curString);
				if (!offset_currentDll)
				{
					log_msg("Load library %s failed:\n", curString);
					exit(0);
				}
				nextDll = customDlls;
				customDlls = new(TCustomDll);
				customDlls->nextDll = nextDll;
				customDlls->initialize(offset_currentDll);
			}
			curString=strtok(NULL,"|");
		}
	}
  if (dllFilenames)
    D2FogMemDeAlloc(dllFilenames, __FILE__, __LINE__, 0);

	log_msg("\n\n");
}

void loadLibrary(LPCSTR libName, int* libVersion, DWORD* libOffset, int shift, DWORD v109b, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c)
{
	*libOffset = (DWORD)LoadLibrary(libName);
	if (*libOffset == NULL)
	{
		log_msg("Failed to load library : %s\n", libName);
		exit(-1);
	}
	log_msg("%s loaded at:\t%08X (", libName, *libOffset);

	DWORD addr = *(DWORD*)(*libOffset + shift);
	if (version_Game != UNKNOWN && (version_Game <= V108 || version_Game >= V113d))
		*libVersion = version_Game;
	else if (addr==v109b)
		*libVersion = V109b;
	else if (addr==v109d)
		*libVersion = V109d;
	else if (addr==v110)
		*libVersion = V110;
	else if (addr==v111)
		*libVersion = V111;
	else if (addr==v111b)
		*libVersion = V111b;
	else if (addr==v112)
		*libVersion = V112;
	else if (addr==v113c)
		*libVersion = V113c;
	else {
		*libVersion = version_Game != UNKNOWN ? version_Game : V113d;
		log_msg("unknown, try with ");
	}
	log_msg("%s)\n", GetVersionString(*libVersion));
}

#define GET_VERSION(F,S,A,B,C,D,E,G,H) loadLibrary(S_##F, &version_##F, &offset_##F, 0x##S, 0x##A, 0x##B, 0x##C, 0x##D, 0x##E, 0x##G, 0x##H)
void initD2modules()
{
	log_msg("***** Get D2 Modules address and version *****\n");
	offset_Game = (DWORD)GetModuleHandle(NULL);
	version_Game = GetD2Version((HMODULE)offset_Game);
	log_msg("Game.exe loaded at:\t%08X (%s)\n", offset_Game, GetVersionString(version_Game));

	if (version_Game >= V114a)
	{
//		offset_Bnclient		= offset_Game;	version_Bnclient	= version_Game; 
		offset_D2Client		= offset_Game;	version_D2Client	= version_Game;
		offset_D2CMP		= offset_Game;	version_D2CMP		= version_Game;
		offset_D2Common		= offset_Game;	version_D2Common	= version_Game;
//		offset_D2DDraw		= offset_Game;	version_D2DDraw		= version_Game;
//		offset_D2Direct3D	= offset_Game;	version_D2Direct3D	= version_Game;
		offset_D2Game		= offset_Game;	version_D2Game		= version_Game;
//		offset_D2Gdi		= offset_Game;	version_D2Gdi		= version_Game;
		offset_D2gfx		= offset_Game;	version_D2gfx		= version_Game;
//		offset_D2Glide		= offset_Game;	version_D2Glide		= version_Game;
		offset_D2Lang		= offset_Game;	version_D2Lang		= version_Game;
		offset_D2Launch		= offset_Game;	version_D2Launch	= version_Game;
//		offset_D2MCPClient	= offset_Game;	version_D2MCPClient	= version_Game;
//		offset_D2Multi		= offset_Game;	version_D2Multi		= version_Game;
		offset_D2Net		= offset_Game;	version_D2Net		= version_Game;
//		offset_D2sound		= offset_Game;	version_D2sound		= version_Game;
		offset_D2Win		= offset_Game;	version_D2Win		= version_Game;
		offset_Fog			= offset_Game;	version_Fog			= version_Game;
		offset_Storm		= offset_Game;	version_Storm		= version_Game;
	}
	else
	{
//		GET_VERSION(Bnclient																					//0x15000	0x6FF00000 Already Loaded	-
		GET_VERSION(D2Client,	17F,	00000000, 14500000, 12500000, 0D814800, 0D812800, 0DA01000, 0DA03000);	//0xCC000	0x6FAA0000					0xCA000
		GET_VERSION(D2CMP,		1359,	3C686FE0, 38686FE0, 8BF78B56, 4C880424, 07C71824, CCCCCCCC, C7000005);	//0x18000	0x6FDF0000 Already Loaded	0x19000
		GET_VERSION(D2Common,	10CA,	A1E86FDC, B1E86FDC, 72D03B42, F883057E, 16746AC6, 00FE81C3, 74FE85DB);	//0x8D000	0x037A0000					0x7C000
//		GET_VERSION(D2DDraw		000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//
//		GET_VERSION(D2Direct3D	000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//
//		GET_VERSION(D2Game,		1010,	D22A78A1, D22910A1, D43FB0A1, 03E8506F, 53E8506F, 89E8506F, 63E8506F);	//0xF6000	0x6FC30000					0xCF000
		GET_VERSION(D2Game,		1092,	18968BF1, 38968BF1, 28968BF1, F6335608, C690C5B9, 895FD713, 56535700);	//0xF6000	0x6FC30000					0xCF000
//		GET_VERSION(D2Gdi,		105,	B4000000, 0B210E00, E4000000, 48000401, 2F000401, 00000000, B7000401);	//0x7000	0x6F830000 Already Loaded	-
		GET_VERSION(D2gfx,		10D,	EB000000, 006FA700, 00000010, 2A000401, 19000401, 0B210E00, 00000000);	//0xB000	0x6FA70000 Already Loaded	-
//		GET_VERSION(D2Glide		000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//
		GET_VERSION(D2Lang,		126D,	FC45048B, F445048B, 02C18313, C4830000, 00C6E045, 8B48408B, 0C75FF0C);	//0x0A000	0x6FC10000 Already Loaded	-
		GET_VERSION(D2Launch,	109A,	81E8526F, 01E8526F, 85E8526F, 247C8B00, 00FC6583, 15FF0424, E850E045);	//0x20000	0x6FA10000 Already Loaded	0x1E000
//		GET_VERSION(D2MCPClient	000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//0x6000	0x6F9F0000 Already Loaded	-
//		GET_VERSION(D2Multi		000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//0x1000	0x6F9A0000					?
		GET_VERSION(D2Net,		16E1,	78B8A73C, 68B8A73C, 10244C8B, 5349E808, 5EA9E808, 105D8B72, 53B9E808);	//0x6000	0x6FC00000 Already Loaded	-	
//		GET_VERSION(D2sound		000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//0xC000	0x6F980000 Already Loaded	0xD000
		GET_VERSION(D2Win,		1699,	88686F8C, 84686F8C, D094686F, F0030000, 001435E8, 8B088F44, 0013F5E8);	//0x19000	0x6F8A0000 Already Loaded	0x1C000
		GET_VERSION(Fog,		102,	D0000006, 10000001, 00000006, 000042E6, 00004302, 0000483C, 00004B95);	//0x20000	0x6FF50000 Already Loaded	0x1F000
		GET_VERSION(Storm,		1190,	19E85082, 59E85082, 13C103F6, 0474F685, 8B000321, 3B1074C9, 0D896404);	//0x30000	0x6FFB0000 Already Loaded	-
		if (version_Game == UNKNOWN)
			 version_Game = version_D2gfx;
	}
//	GET_VERSION(binkw32		000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//
//	GET_VERSION(ijl11		000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//0x24000	0x60000000 Already Loaded	-
//	GET_VERSION(SmackW32	000,	00000000, 00000000, 00000000, 00000000, 00000000, 00000000, 00000000);	//0xD000	0x03B90000 Already Loaded	-

	log_msg("\n\n");
}
//////////////////////////////////// EXPORTS FUNCTIONS ////////////////////////////////////


extern "C" __declspec(dllexport) bool __stdcall Release()
{
	log_msg("\n***** ENDING DIABLO II *****\n\n" );

	freeCustomLibraries();
	freeD2Libraries();
	return true;
}

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
	if (IniName) log_msg("* PlugY is called from D2mod.dll\n\n");

	static int isInstalled = false;
	if (isInstalled) return NULL;
	isInstalled=true;

	initD2modules();

	if (version_Game < V109 || version_Game > V114d)
	{
		log_box("PlugY isn't compatible with this version : %s", GetVersionString(version_Game));
		Release();
		exit(0);
	}

	initD2functions();

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

    if (active_DoNotCloseNihlathakPortal)
      Install_DoNotCloseNihlathakPortal();

	log_msg("\nDLL patched sucessfully.\n\n\n");

	unhookLibraries();

	initCustomLibraries();

	loadLocalizedStrings(D2GetLang());

	log_msg("***** ENTERING DIABLO II *****\n\n" );

	active_logFile = active_logFile - 1;

	return NULL;
}

/*================================= END OF FILE =================================*/