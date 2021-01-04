/*=================================================================
	File created by Yohann NICOLAS.
	Add DoNotCloseNihlathakPortal by haxifix.

	Loading parameters from ini file.

=================================================================*/

#include "error.h"
#include "INIfile.h"
#include "parameters.h"		// loadParameters()
#include <stdio.h>
#include <string.h>
#include <time.h>


const char* PARAMETERS_FILENAME = "PlugY.ini";
const char* PARAM_FIXED_FILENAME = "PlugY\\PlugYFixed.ini";
const char* PARAM_DEFAULT_FILENAME = "PlugY\\PlugYDefault.ini";

#define BUFSIZE 0x400

#include "statsPoints.h"
#include "mainScreen.h"
#include "skillPerLevelUp.h"
#include "statPerLevelUp.h"
#include "savePath.h"
#include "bigStash.h"
#include "skillsPoints.h"
#include "infinityStash.h"
#include "othersFeatures.h"
#include "newInterfaces.h"
#include "worldEvent.h"
#include "uberQuest.h"
#include "extraOptions.h"
#include "commands.h"
#include "language.h"
#include "windowed.h"
#include "savePlayerData.h"


char* modDataDirectory = "PlugY";
bool active_plugin = true;
bool active_DisableBattleNet = true;
bool active_CheckMemory = true;
bool active_D2Mod = false;
char* dllFilenames;

TargetMod selectModParam = MOD_NO;


const char* S_GENERAL = "GENERAL";
const char* S_active_plugin = "ActivePlugin";
const char* S_active_DisableBattleNet = "DisableBattleNet";
const char* S_active_logFile = "ActiveLogFile";
const char* S_dllFilenames = "DllToLoad";
const char* S_dllFilenames2 = "DllToLoad2";
const char* S_active_Commands = "ActiveCommands";
const char* S_active_CheckMemory = "ActiveCheckMemory";
const char* S_active_othersFeatures = "ActiveAllOthersFeatures";

const char* S_WINDOWED = "WINDOWED";
const char* S_ActiveWindowed = "ActiveWindowed";
const char* S_RemoveBorder = "RemoveBorder";
const char* S_WindowOnTop = "WindowOnTop";
const char* S_Maximized = "Maximized";
const char* S_SetWindowPos = "SetWindowPos";
const char* S_X = "X";
const char* S_Y = "Y";
const char* S_Width = "Width";
const char* S_Height = "Height";
const char* S_LockMouseOnStartup = "LockMouseOnStartup";

const char* S_LANGUAGE = "LANGUAGE";
const char* S_active_ChangeLanguage = "ActiveChangeLanguage";
const char* S_selectedLanguage = "SelectedLanguage";
const char* S_active_LanguageManagement = "ActiveLanguageManagement";
const char* S_defaultLanguage = "DefaultLanguage";
const char* S_availableLanguages = "AvailableLanguages";

const char* S_SAVEPATH = "SAVEPATH";
const char* S_active_changingSavePath = "ActiveSavePathChange";
const char* S_savePath = "SavePath";
const char* S_active_AutoBackup = "ActiveAutoBackup";
const char* S_maxBackupPerCharacter = "MaxBackupPerCharacter";

const char* S_MAIN_SCREEN = "MAIN SCREEN";
const char* S_active_VersionTextChange = "ActiveVersionTextChange";
const char* S_versionText = "VersionText";
const char* S_modVersionColor = "ColorOfVersionText";
const char* S_active_PrintPlugYVersion = "ActivePrintPlugYVersion";
const char* S_colorOfPlugYVersion = "ColorOfPlugYVersion";

const char* S_STASH = "STASH";
const char* S_active_bigStash = "ActiveBigStash";
const char* S_active_multiPageStash = "ActiveMultiPageStash";
const char* S_nbPagesPerIndex = "NbPagesPerIndex";
const char* S_nbPagesPerIndex2 = "NbPagesPerIndex2";
const char* S_maxSelfPages = "MaxPersonnalPages";
const char* S_autoRenameStashPage = "AutoRenameStashPage";
const char* S_PersonalNormalPageColor = "PersonalNormalPageColor";
const char* S_PersonalIndexPageColor = "PersonalIndexPageColor";
const char* S_PersonalMainIndexPageColor = "PersonalMainIndexPageColor";
const char* S_SharedNormalPageColor = "SharedNormalPageColor";
const char* S_SharedIndexPageColor = "SharedIndexPageColor";
const char* S_SharedMainIndexPageColor = "SharedMainIndexPageColor";

const char* S_active_sharedStash = "ActiveSharedStash";
const char* S_active_SharedStashInMultiPlayer = "ActiveSharedStashInMultiPlayer";
const char* S_separateHardSoftStash = "SeparateHardcoreStash";
const char* S_openSharedStashOnLoading = "OpenSharedStashOnLoading";
const char* S_sharedStashFilename = "SharedStashFilename";
const char* S_displaySharedSetItemNameInGreen = "DisplaySharedSetItemNameInGreen";
const char* S_maxSharedPages = "MaxSharedPages";
const char* S_active_sharedGold = "ActiveSharedGold";

const char* S_posXPreviousBtn = "PosXPreviousBtn";
const char* S_posYPreviousBtn = "PosYPreviousBtn";
const char* S_posWPreviousBtn = "PosWPreviousBtn";
const char* S_posHPreviousBtn = "PosHPreviousBtn";
const char* S_posXNextBtn = "PosXNextBtn";
const char* S_posYNextBtn = "PosYNextBtn";
const char* S_posWNextBtn = "PosWNextBtn";
const char* S_posHNextBtn = "PosHNextBtn";
const char* S_posXSharedBtn = "PosXSharedBtn";
const char* S_posYSharedBtn = "PosYSharedBtn";
const char* S_posWSharedBtn = "PosWSharedBtn";
const char* S_posHSharedBtn = "PosHSharedBtn";
const char* S_posXPreviousIndexBtn = "PosXPreviousIndexBtn";
const char* S_posYPreviousIndexBtn = "PosYPreviousIndexBtn";
const char* S_posWPreviousIndexBtn = "PosWPreviousIndexBtn";
const char* S_posHPreviousIndexBtn = "PosHPreviousIndexBtn";
const char* S_posXNextIndexBtn = "PosXNextIndexBtn";
const char* S_posYNextIndexBtn = "PosYNextIndexBtn";
const char* S_posWNextIndexBtn = "PosWNextIndexBtn";
const char* S_posHNextIndexBtn = "PosHNextIndexBtn";
const char* S_posXPutGoldBtn = "PosXPutGoldBtn";
const char* S_posYPutGoldBtn = "PosYPutGoldBtn";
const char* S_posWPutGoldBtn = "PosWPutGoldBtn";
const char* S_posHPutGoldBtn = "PosHPutGoldBtn";
const char* S_posXTakeGoldBtn = "PosXTakeGoldBtn";
const char* S_posYTakeGoldBtn = "PosYTakeGoldBtn";
const char* S_posWTakeGoldBtn = "PosWTakeGoldBtn";
const char* S_posHTakeGoldBtn = "PosHTakeGoldBtn";
const char* S_posXStashNameField = "PosXStashNameField";
const char* S_posYStashNameField = "PosYStashNameField";
const char* S_posWStashNameField = "PosWStashNameField";
const char* S_posHStashNameField = "PosHStashNameField";
const char* S_posXStashGoldField = "PosXStashGoldField";
const char* S_posYStashGoldField = "PosYStashGoldField";
const char* S_posWStashGoldField = "PosWStashGoldField";
const char* S_posHStashGoldField = "PosHStashGoldField";


const char* S_STATS_POINTS = "STATS POINTS";
const char* S_active_StatsPoints = "ActiveStatsUnassignment";
const char* S_keyUsedForUnassignStatPoint = "KeyUsed";
const char* S_active_StatsShiftClickLimit = "ActiveShiftClickLimit";
const char* S_limitValueToShiftClick = "LimitValueToShiftClick";

const char* S_STAT_ON_LEVEL_UP = "STAT ON LEVEL UP";
const char* S_active_StatPerLevelUpChange = "ActiveStatPerLevelUp";
const char* S_statPerLevelUp = "StatPerLevelUp";

const char* S_SKILLS_POINTS = "SKILLS POINTS";
const char* S_active_SkillsPoints = "ActiveSkillsUnassignment";
const char* S_unassignSkillsPointsOneForOne = "ActiveSkillsUnassignmentOneForOne";
const char* S_posXUnassignSkillBtn = "PosXUnassignSkillBtn";
const char* S_posYUnassignSkillBtn = "PosYUnassignSkillBtn";

const char* S_SKILL_ON_LEVEL_UP = "SKILL ON LEVEL UP";
const char* S_active_SkillPerLevelUpChange = "ActiveSkillPerLevelUp";
const char* S_skillPerLevelUp = "SkillPerLevelUp";

const char* S_WORLD_EVENT = "WORLD EVENT";
const char* S_active_WorldEvent = "ActiveWorldEvent";
const char* S_showSOJSoldCounterInAllDiff = "ShowCounterInAllDifficulty";
const char* S_itemsToSell = "ItemsToSell";
const char* S_worldEventmonsterID = "MonsterID";
const char* S_valueOfOwnSOJSold = "OwnSOJSoldChargeFor";
const char* S_valueInitSOJSoldMin = "InititalSOJSoldMin";
const char* S_valueInitSOJSoldDelta = "InititalSOJSoldMax";
const char* S_triggerAtSolJSoldMin = "TriggerAtEachSOJSoldMin";
const char* S_triggerAtSolJSoldDelta = "TriggerAtEachSOJSoldMax";
const char* S_active_AutomaticSell = "ActiveAutoSell";
const char* S_timeBeforeAutoSellMin = "TimeBeforeAutoSellMin";
const char* S_timeBeforeAutoSellDelta = "TimeBeforeAutoSellMax";

const char* S_UBER_QUEST = "UBER QUEST";
const char* S_active_UberQuest = "ActiveUberQuest";
const char* S_UberMephistoX = "UberMephistoX";
const char* S_UberMephistoY = "UberMephistoY";
const char* S_UberDiabloX = "UberDiabloX";
const char* S_UberDiabloY = "UberDiabloY";
const char* S_UberBaalX = "UberBaalX";
const char* S_UberBaalY = "UberBaalY";

const char* S_active_UberMinions = "ActiveUberMinions";
//const char* S_UberMephistoMinions = "UberMephistoMinions";
const char* S_UberMephistoSpawnPercent = "UberMephistoSpawnPercent";
const char* S_UberMephistoSpawnRadius = "UberMephistoSpawnRadius";
//const char* S_UberBaalMinions = "UberBaalMinions";
const char* S_UberBaalSpawnPercent = "UberBaalSpawnPercent";
const char* S_UberBaalSpawnRadius = "UberBaalSpawnRadius";
//const char* S_UberDiabloMinions = "UberDiabloMinions";
const char* S_UberDiabloSpawnPercent = "UberDiabloSpawnPercent";
const char* S_UberDiabloSpawnRadius = "UberDiabloSpawnRadius";
const char* S_active_UberDiabloRushTweekAI = "ActiveUberDiabloRushTweekAI";
const char* S_active_UberBaalTeleportTweekAI = "ActiveUberBaalTeleportTweekAI";
const char* S_active_UberBaalChillingArmorTweekAI = "ActiveUberBaalChillingArmorTweekAI";
const char* S_uberBaalChillingArmorTimer = "UberBaalChillingArmorTimer";

const char* S_INTERFACE = "INTERFACE";
const char* S_active_newInterfaces = "ActiveNewStatsInterface";
const char* S_selectMainPageOnOpenning = "SelectMainPageOnOpenning";
const char* S_printBackgroundOnMainPage = "PrintButtonsBackgroundOnMainStatsPage";

const char* S_EXTRA = "EXTRA";
const char* S_active_RunLODs = "ActiveLaunchAnyNumberOfLOD";
const char* S_active_alwaysRegenMapInSP = "AlwaysRegenMapInSP";
const char* S_nbPlayersCommandByDefault = "NBPlayersByDefault";
const char* S_active_DisplayItemLevel = "ActiveDisplayItemLevel";
const char* S_active_AlwaysDisplayLifeMana = "AlwaysDisplayLifeAndManaValues";
const char* S_active_EnabledTXTFilesWithMSExcel= "EnabledTXTFilesWhenMSExcelOpenIt";
const char* S_active_DisplayBaseStatsValue = "ActiveDisplayBaseStatsValue";
const char* S_active_LadderRunewords = "ActiveLadderRunewords";
const char* S_active_EnabledCowPortalWhenCowKingWasKill = "ActiveCowPortalWhenCowKingWasKilled";
const char* S_active_DoNotCloseNihlathakPortal = "ActiveDoNotCloseNihlathakPortal";
const char* S_active_MoveCainNearHarrogathWaypoint = "MoveCainNearHarrogathWaypoint";
const char* S_active_RemoveExperienceDiminushingReturn = "RemoveExperienceDiminushingReturn";

const char* S_DLL = "DLL:\t";
const char* S_DEFAULT = "DEFAULT:";
const char* S_USER = "USER:\t";
const char* S_FIXED = "FIXED:\t";


// Convert 4 char code in a DWORD code
#define BIN(A,B,C,D) ((DWORD)A) + (((DWORD)B) << 8) + (((DWORD)C) << 16) + (((DWORD)D) << 24)


#define GET_PRIVATE_PROFILE_STRING(S,F,D)\
if (!iniFixedFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniDefaultFile->GetPrivateProfileString(S, F, D, buffer, maxSize)) \
	 log_msg(S_DLL); \
else log_msg(S_DEFAULT); \
else log_msg(S_USER); \
else log_msg(S_FIXED)

#define GET_PRIVATE_PROFILE_STRING2(S,F,D)\
if (!iniFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniDefaultFile->GetPrivateProfileString(S, F, D, buffer, maxSize)) \
	 log_msg(S_DLL); \
else log_msg(S_DEFAULT); \
else log_msg(S_USER)

#define GET_PRIVATE_PROFILE_STRING3(S,F,D)\
if (!iniFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniFixedFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniDefaultFile->GetPrivateProfileString(S, F, D, buffer, maxSize)) \
	 log_msg(S_DLL); \
else log_msg(S_DEFAULT); \
else log_msg(S_FIXED); \
else log_msg(S_USER)

int getColor(char* buffer)
{
	int val = atoi(buffer);
	if (val < 1 || val > 19 || val == 17)
		return 0;
	return val;
}

void init_ActivePlugin(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	iniFixedFile->GetPrivateProfileString(S_GENERAL, S_active_plugin, "0", buffer, maxSize);
	active_plugin = atoi(buffer) != 0;
	if (!active_plugin)
	{
		GET_PRIVATE_PROFILE_STRING2(S_GENERAL, S_active_plugin, "1");
		active_plugin = atoi(buffer) != 0;
	} else log_msg(S_FIXED);
	log_msg("active_plugin\t\t\t\t= %u\n", active_plugin);
}

void init_General(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_DisableBattleNet, "0");
	active_DisableBattleNet = atoi(buffer) != 0;
	log_msg("active_DisableBattleNet\t\t= %d\n", active_DisableBattleNet);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_logFile, "0");
	active_logFile = atoi(buffer) + 1;
	log_msg("active_logFile\t\t\t\t= %d\n", active_logFile);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL,S_dllFilenames,"");
	strcat(buffer,"|");
	char* buf = &buffer[strlen(buffer)];
	if (!iniFixedFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
	if (!iniFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
		iniDefaultFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize);
	dllFilenames = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
	strcpy(dllFilenames,buffer);
	log_msg("dllFilenames\t\t\t\t= %s\n", dllFilenames);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_Commands, "0");
	active_Commands = atoi(buffer) != 0;
	log_msg("active_Commands\t\t\t\t= %d\n", active_Commands);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_CheckMemory, "1");
	active_CheckMemory = atoi(buffer) != 0;
	log_msg("active_CheckMemory\t\t\t= %d\n", active_CheckMemory);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_othersFeatures, "0");
	active_othersFeatures = atoi(buffer) != 0;
	log_msg("active_othersFeatures\t\t= %u\n", active_othersFeatures);

	log_msg("\n");
}

void init_Windowed(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_ActiveWindowed, "0");
	active_Windowed = atoi(buffer) != 0;
	log_msg("active_Windowed\t\t\t\t= %d\n", active_Windowed);
	if (active_Windowed)
	{
		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_RemoveBorder, "0");
		active_RemoveBorder = atoi(buffer) != 0;
		log_msg("active_RemoveBorder\t\t\t= %d\n", active_RemoveBorder);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_WindowOnTop, "0");
		active_WindowOnTop = atoi(buffer) != 0;
		log_msg("active_WindowOnTop\t\t\t= %d\n", active_WindowOnTop);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Maximized, "0");
		active_Maximized = atoi(buffer) != 0;
		log_msg("active_Maximized\t\t\t= %d\n", active_Maximized);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_SetWindowPos, "0");
		active_SetWindowPos = atoi(buffer) != 0;
		log_msg("active_SetWindowPos\t= %d\n", active_SetWindowPos);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_X, "0");
		windowedX = atoi(buffer);
		log_msg("windowedX\t\t\t\t\t= %d\n", windowedX);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Y, "0");
		windowedY = atoi(buffer);
		log_msg("windowedY\t\t\t\t\t= %d\n", windowedY);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Width, "800");
		windowedWidth = atoi(buffer);
		log_msg("windowedWidth\t\t\t\t= %d\n", windowedWidth);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Height, "600");
		windowedHeight = atoi(buffer);
		log_msg("windowedHeight\t\t\t\t= %d\n", windowedHeight);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_LockMouseOnStartup, "0");
		active_LockMouseOnStartup = atoi(buffer) != 0;
		log_msg("active_LockMouseOnStartup\t= %d\n\n", active_LockMouseOnStartup);
	}
}

void init_ActiveLanguage(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_LANGUAGE, S_active_ChangeLanguage, "0");
	active_ChangeLanguage = atoi(buffer) != 0;
	log_msg("active_ChangeLanguage\t\t= %d\n", active_ChangeLanguage);

	if (active_ChangeLanguage)
	{
		GET_PRIVATE_PROFILE_STRING(S_LANGUAGE, S_selectedLanguage, "ENG");
		_strupr(buffer);
		switch (*(DWORD*)buffer)
		{
			case BIN('E','N','G',0) : selectedLanguage=LNG_ENG;break;
			case BIN('E','S','P',0) : selectedLanguage=LNG_ESP;break;
			case BIN('D','E','U',0) : selectedLanguage=LNG_DEU;break;
			case BIN('F','R','A',0) : selectedLanguage=LNG_FRA;break;
			case BIN('P','O','R',0) : selectedLanguage=LNG_POR;break;
			case BIN('I','T','A',0) : selectedLanguage=LNG_ITA;break;
			case BIN('J','P','N',0) : selectedLanguage=LNG_JPN;break;
			case BIN('K','O','R',0) : selectedLanguage=LNG_KOR;break;
			case BIN('S','I','N',0) : selectedLanguage=LNG_SIN;break;
			case BIN('C','H','I',0) : selectedLanguage=LNG_CHI;break;
			case BIN('P','O','L',0) : selectedLanguage=LNG_POL;break;
			case BIN('R','U','S',0) : selectedLanguage=LNG_RUS;break;
			default: active_ChangeLanguage = false;
			log_msg("active_ChangeLanguage\t\t= %d (because bad language string : %s)\n", active_ChangeLanguage, buffer);
		}
	}
	if (active_ChangeLanguage)
		log_msg("selectedLanguage\t\t\t= %u\n", selectedLanguage);


	GET_PRIVATE_PROFILE_STRING(S_LANGUAGE, S_active_LanguageManagement, "0");
	active_LanguageManagement = atoi(buffer) != 0;
	log_msg("active_LanguageManagement\t= %d\n", active_LanguageManagement);

	if (active_LanguageManagement)
	{
		GET_PRIVATE_PROFILE_STRING(S_LANGUAGE, S_defaultLanguage, "ENG");
		_strupr(buffer);
		switch (*(DWORD*)buffer)
		{
			case BIN('E','N','G',0) : defaultLanguage=LNG_ENG;break;
			case BIN('E','S','P',0) : defaultLanguage=LNG_ESP;break;
			case BIN('D','E','U',0) : defaultLanguage=LNG_DEU;break;
			case BIN('F','R','A',0) : defaultLanguage=LNG_FRA;break;
			case BIN('P','O','R',0) : defaultLanguage=LNG_POR;break;
			case BIN('I','T','A',0) : defaultLanguage=LNG_ITA;break;
			case BIN('J','P','N',0) : defaultLanguage=LNG_JPN;break;
			case BIN('K','O','R',0) : defaultLanguage=LNG_KOR;break;
			case BIN('S','I','N',0) : defaultLanguage=LNG_SIN;break;
			case BIN('C','H','I',0) : defaultLanguage=LNG_CHI;break;
			case BIN('P','O','L',0) : defaultLanguage=LNG_POL;break;
			case BIN('R','U','S',0) : defaultLanguage=LNG_RUS;break;
			default: defaultLanguage=LNG_ENG;
		}
		log_msg("defaultLanguage\t\t\t= %d\n", defaultLanguage);

		GET_PRIVATE_PROFILE_STRING(S_LANGUAGE, S_availableLanguages, "ENG|ESP|DEU|FRA|POR|ITA|JPN|KOR|SIN|CHI|POL|RUS");
		availableLanguages.all = 0;
		_strupr(buffer);
		char* curString = strtok(buffer,"|");
		while (curString)
		{
			switch (*(DWORD*)curString)
			{
				case BIN('E','N','G',0) : availableLanguages.eng=1;break;
				case BIN('E','S','P',0) : availableLanguages.esp=1;break;
				case BIN('D','E','U',0) : availableLanguages.deu=1;break;
				case BIN('F','R','A',0) : availableLanguages.fra=1;break;
				case BIN('P','O','R',0) : availableLanguages.por=1;break;
				case BIN('I','T','A',0) : availableLanguages.ita=1;break;
				case BIN('J','P','N',0) : availableLanguages.jpn=1;break;
				case BIN('K','O','R',0) : availableLanguages.kor=1;break;
				case BIN('S','I','N',0) : availableLanguages.sin=1;break;
				case BIN('C','H','I',0) : availableLanguages.chi=1;break;
				case BIN('P','O','L',0) : availableLanguages.pol=1;break;
				case BIN('R','U','S',0) : availableLanguages.rus=1;break;
				default:;
			}
			curString=strtok(NULL,"|");
		}
		log_msg("availableLanguage.all\t\t= 0x%04X\n\n",availableLanguages.all);
	}
	log_msg("\n");
}

void init_SavePath(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING3(S_SAVEPATH, S_active_changingSavePath, "0");
	active_changingSavePath = atoi(buffer) != 0;
	log_msg("active_changingSavePath\t\t= %u\n", active_changingSavePath);

	if (active_changingSavePath)
	{
		int curSize =  0;
		int start = 0;
		GET_PRIVATE_PROFILE_STRING3(S_SAVEPATH, S_savePath, "Save\\");

		while (buffer[curSize])
			curSize++;

		if ( (curSize>0) && buffer[curSize-1] != (BYTE)'\\')
		{
			buffer[curSize++] = (BYTE)'\\';
			buffer[curSize]='\0';
		}
		while (buffer[start] == '\\')
			start++;

		if (!buffer[start])
		{
			active_changingSavePath = false;
			log_msg("active_changingSavePath\t\t= %u (no valid savePath)\n\n", active_changingSavePath);
			return;
		}

		if (buffer[start+1]!=':')
		{
			char buf[MAX_PATH];
			buf[0]=NULL;
			D2FogGetSavePath(buf,MAX_PATH);
			savePath = (char*)D2FogMemAlloc(strlen(buf) + curSize - start + 1,__FILE__,__LINE__,0);
			strcpy(savePath,buf);
			strcat(savePath,&buffer[start]);
		} else {
			savePath = (char*)D2FogMemAlloc(curSize-start+1,__FILE__,__LINE__,0);
			strcpy(savePath,&buffer[start]);
		}
		log_msg("savePath\t\t\t\t\t= %s\n", savePath);
	}

	GET_PRIVATE_PROFILE_STRING3(S_SAVEPATH, S_active_AutoBackup, "0");
	active_AutoBackup = atoi(buffer) != 0;
	log_msg("active_autoBackup\t\t= %u\n", active_AutoBackup);

	GET_PRIVATE_PROFILE_STRING3(S_SAVEPATH, S_maxBackupPerCharacter, "20");
	maxBackupPerCharacter = atoi(buffer);
	log_msg("maxBackupPerCharacter\t\t= %u\n", maxBackupPerCharacter);

	log_msg("\n");
}

void init_VersionText(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_active_VersionTextChange, "0");
	active_VersionTextChange = atoi(buffer) != 0;
	log_msg("active_VersionTextChange\t= %u\n", active_VersionTextChange);

	if (active_VersionTextChange)
	{
		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_versionText, versionText);
		if (!buffer[0])
		{
			strcpy(buffer, "v ");
			strcat(buffer, GetVersionString(version_D2Game));
			//switch(version_D2Game)
			//{
			////case V107: //"v 1.07"
			////case V108: //"v 1.08"
			////case V109: //"v 1.09"
			//case V109b: //"v 1.09"
			//case V109d: //"v 1.09"
			////case V110: //"v 1.10"
			////case V111: //"v 1.11"
			//case V111b: //"v 1.11"
			////case V112: //"v 1.12"
			//case V113c: //"v 1.13"
			//case V113d: //"v 1.13"
			//case V114a: //"v 1.14"
			////case V114b: //"v 1.14b"
			////case V114c: //"v 1.14c"
			////case V114d: //"v 1.14d"
			//	strcpy(buffer, "v ");
			//	strcat(buffer, GetVersionString(version_D2Game));
			//	break;
			//default:
			//	active_VersionTextChange=0;
			//}
		}

		versionText = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(versionText,buffer);
		log_msg("versionText\t\t\t\t\t= %s\n", versionText);

		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_modVersionColor, "0");
		modVersionColor = getColor(buffer);
		log_msg("modVersionColor\t\t\t\t= %u\n", modVersionColor);
	}

	GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_active_PrintPlugYVersion, "1");
	active_PrintPlugYVersion = atoi(buffer) != 0;
	log_msg("active_PrintPlugYVersion\t= %u\n", active_PrintPlugYVersion);

	if (active_PrintPlugYVersion)
	{
		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_colorOfPlugYVersion, "4");
		colorOfPlugYVersion = getColor(buffer);
		log_msg("colorOfPlugYVersion\t\t\t= %u\n", colorOfPlugYVersion);
	}

	log_msg("\n");
}

void init_Stash(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_bigStash, "0");
	active_bigStash = atoi(buffer) != 0;
	log_msg("active_bigStash\t\t\t\t= %u\n", active_bigStash);

	GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_multiPageStash, "0");
	active_multiPageStash = atoi(buffer) != 0;
	log_msg("active_multiPageStash\t\t= %u\n", active_multiPageStash);

	if (active_multiPageStash)
	{
		active_PlayerCustomData = true;

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_nbPagesPerIndex, "10");
		nbPagesPerIndex = atoi(buffer);
		if (!nbPagesPerIndex) nbPagesPerIndex=10;
		log_msg("nbPagesPerIndex\t\t\t\t= %u\n", nbPagesPerIndex);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_nbPagesPerIndex2, "100");
		nbPagesPerIndex2 = atoi(buffer);
		if (!nbPagesPerIndex2) nbPagesPerIndex2=100;
		log_msg("nbPagesPerIndex2\t\t\t= %u\n", nbPagesPerIndex2);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_maxSelfPages, "0");
		maxSelfPages = atoi(buffer) - 1;
		log_msg("maxSelfPages\t\t\t\t= %u\n", maxSelfPages);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_autoRenameStashPage, "0");
		autoRenameStashPage = atoi(buffer) != 0;
		log_msg("autoRenameStashPage\t\t\t= %d\n", autoRenameStashPage);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_PersonalNormalPageColor, "0");
		PersonalNormalPageColor = getColor(buffer);
		log_msg("PersonalNormalPageColor\t\t\t= %d\n", PersonalNormalPageColor);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_PersonalIndexPageColor, "12");
		PersonalIndexPageColor = getColor(buffer);
		log_msg("PersonalIndexPageColor\t\t\t= %d\n", PersonalIndexPageColor);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_PersonalMainIndexPageColor, "9");
		PersonalMainIndexPageColor = getColor(buffer);
		log_msg("PersonalMainIndexPageColor\t\t\t= %d\n", PersonalMainIndexPageColor);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_SharedNormalPageColor, "4");
		SharedNormalPageColor = getColor(buffer);
		log_msg("SharedNormalPageColor\t\t\t= %d\n", SharedNormalPageColor);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_SharedIndexPageColor, "8");
		SharedIndexPageColor = getColor(buffer);
		log_msg("SharedIndexPageColor\t\t\t= %d\n", SharedIndexPageColor);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_SharedMainIndexPageColor, "1");
		SharedMainIndexPageColor = getColor(buffer);
		log_msg("SharedMainIndexPageColor\t\t\t= %d\n", SharedMainIndexPageColor);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_sharedStash, "0");
		active_sharedStash = atoi(buffer) != 0;
		log_msg("active_sharedStash\t\t\t= %u\n", active_sharedStash);

		if (active_sharedStash)
		{
			GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_SharedStashInMultiPlayer, "0");
			active_SharedStashInMultiPlayer = atoi(buffer) ? 2 : 1;
			log_msg("active_SharedStashInMultiPlayer = %u\n", active_SharedStashInMultiPlayer);

			GET_PRIVATE_PROFILE_STRING(S_STASH, S_separateHardSoftStash, "1");
			separateHardSoftStash = atoi(buffer) != 0;
			log_msg("separateHardSoftStash\t\t= %u\n", separateHardSoftStash);

			GET_PRIVATE_PROFILE_STRING(S_STASH, S_openSharedStashOnLoading, "0");
			openSharedStashOnLoading = atoi(buffer) != 0;
			log_msg("openSharedStashOnLoading\t\t= %u\n", openSharedStashOnLoading);

			GET_PRIVATE_PROFILE_STRING(S_STASH, S_sharedStashFilename, "SharedStashSave");
			sharedStashFilename = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
			strcpy(sharedStashFilename, buffer);
			log_msg("sharedStashFilename\t\t\t= %s\n", sharedStashFilename);

			GET_PRIVATE_PROFILE_STRING(S_STASH, S_displaySharedSetItemNameInGreen, "1");
			displaySharedSetItemNameInGreen = atoi(buffer) != 0;
			log_msg("displaySharedSetItemNameInGreen = %u\n", displaySharedSetItemNameInGreen);

			GET_PRIVATE_PROFILE_STRING(S_STASH, S_maxSharedPages, "0");
			maxSharedPages = atoi(buffer) - 1;
			log_msg("maxSharedPages\t\t\t\t= %u\n", maxSharedPages);

			GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_sharedGold, "1");
			active_sharedGold = atoi(buffer) != 0;
			log_msg("active_sharedGold\t\t\t= %u\n", active_sharedGold);
		}

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPreviousBtn,"-1");
		posXPreviousBtn = atoi(buffer);
		log_msg("posXPreviousBtn\t\t\t= %d\n", posXPreviousBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPreviousBtn,"-1");
		posYPreviousBtn = atoi(buffer);
		log_msg("posYPreviousBtn\t\t\t= %d\n", posYPreviousBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWPreviousBtn,"32");
		posWPreviousBtn = atoi(buffer);
		log_msg("posWPreviousBtn\t\t\t= %d\n", posWPreviousBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHPreviousBtn,"32");
		posHPreviousBtn = atoi(buffer);
		log_msg("posHPreviousBtn\t\t\t= %d\n", posHPreviousBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXNextBtn,"-1");
		posXNextBtn = atoi(buffer);
		log_msg("posXNextBtn\t\t\t= %d\n", posXNextBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYNextBtn,"-1");
		posYNextBtn = atoi(buffer);
		log_msg("posYNextBtn\t\t\t= %d\n", posYNextBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWNextBtn,"32");
		posWNextBtn = atoi(buffer);
		log_msg("posWNextBtn\t\t\t= %d\n", posWNextBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHNextBtn,"32");
		posHNextBtn = atoi(buffer);
		log_msg("posHNextBtn\t\t\t= %d\n", posHNextBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXSharedBtn,"-1");
		posXSharedBtn = atoi(buffer);
		log_msg("posXSharedBtn\t\t\t= %d\n", posXSharedBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYSharedBtn,"-1");
		posYSharedBtn = atoi(buffer);
		log_msg("posYSharedBtn\t\t\t= %d\n", posYSharedBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWSharedBtn,"32");
		posWSharedBtn = atoi(buffer);
		log_msg("posWSharedBtn\t\t\t= %d\n", posWSharedBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHSharedBtn,"32");
		posHSharedBtn = atoi(buffer);
		log_msg("posHSharedBtn\t\t\t= %d\n", posHSharedBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPreviousIndexBtn,"-1");
		posXPreviousIndexBtn = atoi(buffer);
		log_msg("posXPreviousIndexBtn\t\t\t= %d\n", posXPreviousIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPreviousIndexBtn,"-1");
		posYPreviousIndexBtn = atoi(buffer);
		log_msg("posYPreviousIndexBtn\t\t\t= %d\n", posYPreviousIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWPreviousIndexBtn,"32");
		posWPreviousIndexBtn = atoi(buffer);
		log_msg("posWPreviousIndexBtn\t\t\t= %d\n", posWPreviousIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHPreviousIndexBtn,"32");
		posHPreviousIndexBtn = atoi(buffer);
		log_msg("posHPreviousIndexBtn\t\t\t= %d\n", posHPreviousIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXNextIndexBtn,"-1");
		posXNextIndexBtn = atoi(buffer);
		log_msg("posXNextIndexBtn\t\t\t= %d\n", posXNextIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYNextIndexBtn,"-1");
		posYNextIndexBtn = atoi(buffer);
		log_msg("posYNextIndexBtn\t\t\t= %d\n", posYNextIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWNextIndexBtn,"32");
		posWNextIndexBtn = atoi(buffer);
		log_msg("posWNextIndexBtn\t\t\t= %d\n", posWNextIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHNextIndexBtn,"32");
		posHNextIndexBtn = atoi(buffer);
		log_msg("posHNextIndexBtn\t\t\t= %d\n", posHNextIndexBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPutGoldBtn,"-1");
		posXPutGoldBtn = atoi(buffer);
		log_msg("posXPutGoldBtn\t\t\t= %d\n", posXPutGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPutGoldBtn,"-1");
		posYPutGoldBtn = atoi(buffer);
		log_msg("posYPutGoldBtn\t\t\t= %d\n", posYPutGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWPutGoldBtn,"32");
		posWPutGoldBtn = atoi(buffer);
		log_msg("posWPutGoldBtn\t\t\t= %d\n", posWPutGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHPutGoldBtn,"32");
		posHPutGoldBtn = atoi(buffer);
		log_msg("posHPutGoldBtn\t\t\t= %d\n", posHPutGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXTakeGoldBtn,"-1");
		posXTakeGoldBtn = atoi(buffer);
		log_msg("posXTakeGoldBtn\t\t\t= %d\n", posXTakeGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYTakeGoldBtn,"-1");
		posYTakeGoldBtn = atoi(buffer);
		log_msg("posYTakeGoldBtn\t\t\t= %d\n", posYTakeGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWTakeGoldBtn,"32");
		posWTakeGoldBtn = atoi(buffer);
		log_msg("posWTakeGoldBtn\t\t\t= %d\n", posWTakeGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHTakeGoldBtn,"32");
		posHTakeGoldBtn = atoi(buffer);
		log_msg("posHTakeGoldBtn\t\t\t= %d\n", posHTakeGoldBtn);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXStashNameField,"-1");
		posXStashNameField = atoi(buffer);
		log_msg("posXStashNameField\t\t\t= %d\n", posXStashNameField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYStashNameField,"-1");
		posYStashNameField = atoi(buffer);
		log_msg("posYStashNameField\t\t\t= %d\n", posYStashNameField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWStashNameField,"175");
		posWStashNameField = atoi(buffer);
		log_msg("posWStashNameField\t\t\t= %d\n", posWStashNameField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHStashNameField,"20");
		posHStashNameField = atoi(buffer);
		log_msg("posHStashNameField\t\t\t= %d\n", posHStashNameField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXStashGoldField,"-1");
		posXStashGoldField = atoi(buffer);
		log_msg("posXStashGoldField\t\t\t= %d\n", posXStashGoldField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYStashGoldField,"-1");
		posYStashGoldField = atoi(buffer);
		log_msg("posYStashGoldField\t\t\t= %d\n", posYStashGoldField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posWStashGoldField,"152");
		posWStashGoldField = atoi(buffer);
		log_msg("posWStashGoldField\t\t\t= %d\n", posWStashGoldField);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posHStashGoldField,"18");
		posHStashGoldField = atoi(buffer);
		log_msg("posHStashGoldField\t\t\t= %d\n", posHStashGoldField);
	}

	log_msg("\n");
}

void init_StatsPoints(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_STATS_POINTS, S_active_StatsPoints, "0");
	active_StatsPoints = atoi(buffer) != 0;
	log_msg("active_StatsPoints\t\t\t= %u\n", active_StatsPoints);

	if (active_StatsPoints)
	{
		GET_PRIVATE_PROFILE_STRING(S_STATS_POINTS, S_keyUsedForUnassignStatPoint, "18");
		keyUsedForUnassignStatPoint = atoi(buffer);
		log_msg("keyUsedForUnassignStatPoint\t= %u (0x%x)\n", keyUsedForUnassignStatPoint);
	}

	GET_PRIVATE_PROFILE_STRING(S_STATS_POINTS, S_active_StatsShiftClickLimit, "0");
	active_StatsShiftClickLimit = atoi(buffer) != 0;
	log_msg("active_StatsShiftClickLimit\t= %u\n", active_StatsShiftClickLimit);

	if (active_StatsShiftClickLimit)
	{
		GET_PRIVATE_PROFILE_STRING(S_STATS_POINTS, S_limitValueToShiftClick, "5");
		limitValueToShiftClick = atoi(buffer);
		log_msg("limitValueToShiftClick\t\t= %u\n", limitValueToShiftClick);
	}
	log_msg("\n");
}

void init_StatPerLevelUp(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_STAT_ON_LEVEL_UP, S_active_StatPerLevelUpChange, "0");
	active_StatPerLevelUpChange = atoi(buffer) != 0;
	log_msg("active_StatPerLevelUpChange\t= %u\n", active_StatPerLevelUpChange);

	if (active_StatPerLevelUpChange)
	{
		GET_PRIVATE_PROFILE_STRING(S_STAT_ON_LEVEL_UP, S_statPerLevelUp, "5");
		statPerLevelUp = atoi(buffer);
		log_msg("statPerLevelUp\t\t\t\t= %u\n", statPerLevelUp);
	}
	log_msg("\n");
}

void init_SkillsPoints(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_active_SkillsPoints, "0");
	active_SkillsPoints = atoi(buffer) != 0;
	log_msg("active_SkillsPoints\t\t\t= %d\n", active_SkillsPoints);

	GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_unassignSkillsPointsOneForOne, "0");
	unassignSkillsPointsOneForOne = atoi(buffer) != 0;
	log_msg("unassignSkillsPointsOneForOne\t\t\t= %d\n", unassignSkillsPointsOneForOne);
	if (unassignSkillsPointsOneForOne)
	{
		active_SkillsPoints = true;
		log_msg("active_SkillsPoints\t\t\t= %d\n", active_SkillsPoints);
	}

	if (active_SkillsPoints)
	{
		GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_posXUnassignSkillBtn,"-1");
		posXUnassignSkillBtn = atoi(buffer);
		log_msg("posXUnassignSkillBtn\t\t\t= %d\n", posXUnassignSkillBtn);

		GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_posYUnassignSkillBtn,"-1");
		posYUnassignSkillBtn = atoi(buffer);
		log_msg("posXUnassignSkillBtn\t\t\t= %d\n", posYUnassignSkillBtn);
	}
	log_msg("\n");
}

void init_SkillPerLevelUp(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_SKILL_ON_LEVEL_UP, S_active_SkillPerLevelUpChange, "0");
	active_SkillPerLevelUpChange = atoi(buffer) != 0;
	log_msg("active_SkillPerLevelUpChange= %u\n", active_SkillPerLevelUpChange);

	if (active_SkillPerLevelUpChange)
	{
		GET_PRIVATE_PROFILE_STRING(S_SKILL_ON_LEVEL_UP, S_skillPerLevelUp, "1");
		skillPerLevelUp = atoi(buffer);
		log_msg("skillPerLevelUp\t\t\t\t= %u\n", skillPerLevelUp);
	}
	log_msg("\n");
}

void init_WorldEvent(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_active_WorldEvent, "0");
	active_WorldEvent = atoi(buffer) != 0;
	if (active_WorldEvent && version_D2Game < V110) {
		active_WorldEvent = 0;
		log_msg("active_WorldEvent\t\t\t= %d (Warning : this feature is only for LoD version 1.10 or higher, so it's automatically disabled)\n", active_WorldEvent);
	} else
		log_msg("active_WorldEvent\t\t\t= %d\n", active_WorldEvent);

	if (active_WorldEvent)
	{
		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_showSOJSoldCounterInAllDiff, "0");
		showSOJSoldCounterInAllDiff = atoi(buffer);
		log_msg("showSOJSoldCounterInAllDiff\t= %d\n", showSOJSoldCounterInAllDiff);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_itemsToSell, itemsToSell);
		if (strlen(buffer)>50) buffer[50]='\0';
		itemsToSell = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(itemsToSell,buffer);
		log_msg("itemsToSell\t\t\t\t\t= %s\n", itemsToSell);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_worldEventmonsterID, "333");
		worldEventmonsterID = atoi(buffer);
		log_msg("worldEventmonsterID\t\t\t= %d\n", worldEventmonsterID);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_valueOfOwnSOJSold, "100");
		valueOfOwnSOJSold = atoi(buffer);
		log_msg("valueOfOwnSOJSold\t\t\t= %d\n", valueOfOwnSOJSold);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_valueInitSOJSoldMin, "200");
		valueInitSOJSoldMin = atoi(buffer);
		log_msg("valueInitSOJSoldMin\t\t\t= %d\n", valueInitSOJSoldMin);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_valueInitSOJSoldDelta, "3000");
		valueInitSOJSoldDelta = atoi(buffer)-valueInitSOJSoldMin+1;
		log_msg("valueInitSOJSoldDelta\t\t= %d\n", valueInitSOJSoldDelta);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_triggerAtSolJSoldMin, "75");
		triggerAtSolJSoldMin = atoi(buffer);
		log_msg("triggerAtSolJSoldMin\t\t= %d\n", triggerAtSolJSoldMin);

		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_triggerAtSolJSoldDelta, "125");
		triggerAtSolJSoldDelta = atoi(buffer) - triggerAtSolJSoldMin + 1;
		log_msg("triggerAtSolJSoldDelta\t\t= %d\n", triggerAtSolJSoldDelta);


		GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_active_AutomaticSell, "1");
		active_AutomaticSell = atoi(buffer) != 0;
		log_msg("active_AutomaticSell\t\t= %d\n", active_AutomaticSell);

		if (active_AutomaticSell)
		{
			GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_timeBeforeAutoSellMin, "0");
			timeBeforeAutoSellMin = atoi(buffer)*1000;
			log_msg("timeBeforeAutoSellMin\t\t= %d\n", timeBeforeAutoSellMin);

			GET_PRIVATE_PROFILE_STRING(S_WORLD_EVENT, S_timeBeforeAutoSellDelta, "1200");
			timeBeforeAutoSellDelta = atoi(buffer)*1000-timeBeforeAutoSellMin+1;
			log_msg("timeBeforeAutoSellDelta\t\t= %d\n", timeBeforeAutoSellDelta);
		}
	}
	log_msg("\n");
}

void init_UberQuest(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_active_UberQuest, "0");
	active_UberQuest = atoi(buffer) != 0;
	if (active_UberQuest && version_D2Game < V111) {
		active_UberQuest = 0;
		log_msg("active_UberQuest\t\t= %d (Warning : this feature is only for LoD version 1.11 or higher, so it's automatically disabled)\n", active_UberQuest);
	} else
		log_msg("active_UberQuest\t\t\t= %d\n", active_UberQuest);
	if (active_UberQuest)
	{
		GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberMephistoX, "25130");
		UberMephistoX = atoi(buffer);
		log_msg("UberMephistoX\t\t= %d\n", UberMephistoX);

		GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberMephistoY, "5143");
		UberMephistoY = atoi(buffer);
		log_msg("UberMephistoY\t\t= %d\n", UberMephistoY);

		GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberDiabloX, "25139");
		UberDiabloX = atoi(buffer);
		log_msg("UberDiabloX\t\t= %d\n", UberDiabloX);

		GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberDiabloY, "5139");
		UberDiabloY = atoi(buffer);
		log_msg("UberDiabloY\t\t= %d\n", UberDiabloY);

		GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberBaalX, "25139");
		UberBaalX = atoi(buffer);
		log_msg("UberBaalX\t\t= %d\n", UberBaalX);

		GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberBaalY, "5135");
		UberBaalY = atoi(buffer);
		log_msg("UberBaalY\t\t= %d\n", UberBaalY);

		if (version_D2Game >= V113c)
		{
			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_active_UberMinions, "1");
			active_UberMinions = atoi(buffer) != 0;
			log_msg("active_UberMinions\t\t= %d\n", active_UberMinions);

			//GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberMephistoMinions, "1");
			//UberMephistoNbMinions = atoi(buffer);
			//UberMephistoMinions = atoi(buffer);
			//log_msg("ActiveUberMinions\t= %d\n", UberMephistoMinions);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberMephistoSpawnPercent, "80");
			UberMephistoSpawnPercent = atoi(buffer);
			log_msg("UberMephistoSpawnPercent\t\t= %d\n", UberMephistoSpawnPercent);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberMephistoSpawnRadius, "30");
			UberMephistoSpawnRadius = atoi(buffer);
			log_msg("UberMephistoSpawnRadius\t\t= %d\n", UberMephistoSpawnRadius);

			//GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberBaalMinions, "1");
			//UberBaalNbMinions = atoi(buffer);
			//UberBaalMinions = atoi(buffer);
			//log_msg("UberBaalMinions\t\t= %d\n", UberBaalMinions);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberBaalSpawnPercent, "30");
			UberBaalSpawnPercent = atoi(buffer);
			log_msg("UberBaalSpawnPercent\t\t= %d\n", UberBaalSpawnPercent);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberBaalSpawnRadius, "30");
			UberBaalSpawnRadius = atoi(buffer);
			log_msg("UberBaalSpawnRadius\t\t= %d\n", UberBaalSpawnRadius);

			//GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberDiabloMinions, "1");
			//UberDiabloNbMinions = atoi(buffer);
			//UberDiabloMinions = atoi(buffer);
			//log_msg("UberDiabloMinions\t\t= %d\n", UberDiabloMinions);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberDiabloSpawnPercent, "30");
			UberDiabloSpawnPercent = atoi(buffer);
			log_msg("UberDiabloSpawnPercent\t\t= %d\n", UberDiabloSpawnPercent);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_UberDiabloSpawnRadius, "30");
			UberDiabloSpawnRadius = atoi(buffer);
			log_msg("UberDiabloSpawnRadius\t\t= %d\n", UberDiabloSpawnRadius);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_active_UberDiabloRushTweekAI, "1");
			active_UberDiabloRushTweekAI = atoi(buffer) != 0;
			log_msg("active_UberDiabloRushTweekAI\t\t= %d\n", active_UberDiabloRushTweekAI);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_active_UberBaalTeleportTweekAI, "1");
			active_UberBaalTeleportTweekAI = atoi(buffer) != 0;
			log_msg("active_UberBaalTeleportTweekAI\t\t= %d\n", active_UberBaalTeleportTweekAI);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_active_UberBaalChillingArmorTweekAI, "1");
			active_UberBaalChillingArmorTweekAI = atoi(buffer) != 0;
			log_msg("active_UberBaalChillingArmorTweekAI\t\t= %d\n", active_UberBaalChillingArmorTweekAI);

			GET_PRIVATE_PROFILE_STRING(S_UBER_QUEST, S_uberBaalChillingArmorTimer, "6000");
			uberBaalChillingArmorTimer = atoi(buffer);
			log_msg("uberBaalChillingArmorTimer\t\t= %d\n", uberBaalChillingArmorTimer);
		}
	}
	log_msg("\n");
}

void init_NewInterfaces(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_INTERFACE, S_active_newInterfaces, "0");
	active_newInterfaces = atoi(buffer) != 0;
	log_msg("active_newInterfaces\t\t= %d\n", active_newInterfaces);

	if (active_newInterfaces)
	{
		GET_PRIVATE_PROFILE_STRING(S_INTERFACE, S_selectMainPageOnOpenning, "1");
		selectMainPageOnOpenning = atoi(buffer) != 0;
		log_msg("selectMainPageOnOpenning\t= %u\n", selectMainPageOnOpenning);

		GET_PRIVATE_PROFILE_STRING(S_INTERFACE, S_printBackgroundOnMainPage, "1");
		printBackgroundOnMainPage = atoi(buffer) != 0;
		log_msg("printBackgroundOnMainPage\t= %u\n", printBackgroundOnMainPage);
	}
	log_msg("\n");
}

void init_ExtraOptions(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_RunLODs, "0");
	active_RunLODs = atoi(buffer) != 0;
	log_msg("active_RunLODs\t\t\t\t= %u\n", active_RunLODs);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_alwaysRegenMapInSP, "0");
	active_alwaysRegenMapInSP = atoi(buffer) != 0;
	log_msg("active_alwaysRegenMapInSP\t= %d\n", active_alwaysRegenMapInSP);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_nbPlayersCommandByDefault, "0");
	nbPlayersCommandByDefault = atoi(buffer);
	if (version_D2Common == V109 || version_D2Common == V109b)
		{if (nbPlayersCommandByDefault > 64) nbPlayersCommandByDefault=64;}
	else if (nbPlayersCommandByDefault > 8) nbPlayersCommandByDefault=8;
	log_msg("nbPlayersCommandByDefault\t= %d\n", nbPlayersCommandByDefault);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_DisplayItemLevel, "0");
	active_DisplayItemLevel = atoi(buffer) != 0;
	log_msg("active_DisplayItemLevel\t\t= %d\n", active_DisplayItemLevel);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_AlwaysDisplayLifeMana, "0");
	active_AlwaysDisplayLifeMana = atoi(buffer);
	log_msg("active_AlwaysDisplayLifeMana= %d\n", active_AlwaysDisplayLifeMana);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_EnabledTXTFilesWithMSExcel, "0");
	active_EnabledTXTFilesWithMSExcel = atoi(buffer) != 0;
	log_msg("active_EnabledTXTFilesWithMSExcel= %u\n\n", active_EnabledTXTFilesWithMSExcel);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_DisplayBaseStatsValue, "0");
	active_DisplayBaseStatsValue = atoi(buffer) != 0;
	log_msg("active_DisplayBaseStatsValue= %u\n\n", active_DisplayBaseStatsValue);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_LadderRunewords, "0");
	active_LadderRunewords = atoi(buffer) != 0;
	if (active_LadderRunewords && version_D2Common < V110) {
		active_LadderRunewords = 0;
		log_msg("active_LadderRunewords\t= %d (Warning : this feature is only for LoD version 1.10 or higher, so it's automatically disabled)\n", active_WorldEvent);
	} else
		log_msg("active_LadderRunewords\t= %u\n\n", active_LadderRunewords);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_EnabledCowPortalWhenCowKingWasKill, "0");
	active_EnabledCowPortalWhenCowKingWasKill = atoi(buffer) != 0;
	log_msg("active_EnabledCowPortalWhenCowKingWasKill= %u\n\n", active_EnabledCowPortalWhenCowKingWasKill);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_DoNotCloseNihlathakPortal, "0");
	active_DoNotCloseNihlathakPortal = atoi(buffer) != 0;
	log_msg("active_DoNotCloseNihlathakPortal= %u\n\n", active_DoNotCloseNihlathakPortal);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_MoveCainNearHarrogathWaypoint, "0");
	active_MoveCainNearHarrogathWaypoint = atoi(buffer) != 0;
	log_msg("active_MoveCainNearHarrogathWaypoint= %u\n\n", active_MoveCainNearHarrogathWaypoint);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_RemoveExperienceDiminushingReturn, "0");
	active_RemoveExperienceDiminushingReturn = atoi(buffer) != 0;
	if (active_RemoveExperienceDiminushingReturn)
	{
		if (version_D2Common == V114d)
			log_msg("active_RemoveExperienceDiminushingReturn= %u\n\n", active_RemoveExperienceDiminushingReturn);
		else
		{
			active_RemoveExperienceDiminushingReturn = 0;
			log_msg("active_RemoveExperienceDiminushingReturn\t= %d (Warning : this feature is only for LoD version 1.14d or higher, so it's automatically disabled)\n", active_RemoveExperienceDiminushingReturn);
		}
	}
}


void loadParameters()
{
	char buffer[BUFSIZE];
	int loading=0;
	INIFile *iniFile = new INIFile;
	INIFile *iniFixedFile = new INIFile;
	INIFile *iniDefaultFile = new INIFile;

	srand((UINT)time(NULL));

	log_msg("***** PARAMETERS *****\n");
	if (iniFile->InitReadWrite(PARAMETERS_FILENAME, INIFILE_READ, 0))
	{
		log_msg("Parameters file is opened.\n\n");
		loading = 1;
	}
	if (iniFixedFile->InitReadWrite(PARAM_FIXED_FILENAME, INIFILE_MPQREAD, 0))
	{
		log_msg("Fixed Parameters file is opened.\n\n");
		loading = 1;
	}
	if (iniDefaultFile->InitReadWrite(PARAM_DEFAULT_FILENAME, INIFILE_MPQREAD, 0))
	{
		log_msg("Default Parameters file is opened.\n\n");
		loading = 1;
	}

	if(loading)
	{
		log_msg("Reading parameters.\n\n");

		init_ActivePlugin(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
		if (active_plugin)
		{
			init_General(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_Windowed(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_ActiveLanguage(iniFile, iniFixedFile, iniDefaultFile, buffer,BUFSIZE);
			init_SavePath(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_VersionText(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_Stash(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_StatsPoints(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_StatPerLevelUp(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_SkillsPoints(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_SkillPerLevelUp(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_WorldEvent(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_UberQuest(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_NewInterfaces(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_ExtraOptions(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
		}
		log_msg("Reading parameters end.\n\n\n");
	} else {
		log_msg("\nCan't open parameters files: Default values used.\n\n\n");
		active_plugin = false;
	}

	if (iniFile)
		iniFile->close();
	if (iniFixedFile)
		iniFixedFile->close();
	if (iniDefaultFile)
		iniDefaultFile->close();


	delete iniFile;
	delete iniDefaultFile;
	delete iniFixedFile;
}

/*================================= END OF FILE =================================*/