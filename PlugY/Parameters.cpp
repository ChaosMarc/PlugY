/*=================================================================
	File created by Yohann NICOLAS.

	Loading parameters from ini file.

=================================================================*/

// Core Class Headers
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"
#include "error.h"
#include "parameters.h"		// loadParameters()
#include "D2functions.h"
#include "INIfile.h"


#define PARAMETERS_FILENAME "PlugY.ini"
#define PARAM_FIXED_FILENAME "PlugY\\PlugYFixed.ini"
#define PARAM_DEFAULT_FILENAME "PlugY\\PlugYDefault.ini"

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
extern bool displayGreenSetItemIncludeSharedStash;


char* modDataDirectory = "PlugY";
bool active_plugin = true;
bool active_DisableBattleNet = true;
bool active_CheckMemory = true;
bool active_D2Mod = false;
char* dllFilenames;

TargetMod selectModParam = MOD_NO;


const char* S_GENERAL = "GENERAL";
const char* S_dllFilenames = "DllToLoad";
const char* S_dllFilenames2 = "DllToLoad2";
const char* S_active_plugin = "ActivePlugin";
const char* S_active_DisableBattleNet = "DisableBattleNet";
const char* S_active_logFile = "ActiveLogFile";
const char* S_active_CheckMemory = "ActiveCheckMemory";
const char* S_active_Commands = "ActiveCommands";
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

const char* S_MAIN_SCREEN = "MAIN SCREEN";
const char* S_active_VersionTextChange = "ActiveVersionTextChange";
const char* S_active_VersionTextChanges = "ActiveVersionTextChanges";
const char* S_versionText = "VersionText";
const char* S_modVersionColor = "ColorOfVersionText";
const char* S_active_PrintPlugYVersion = "ActivePrintPlugYVersion";
const char* S_colorOfPlugYVersion = "ColorOfPlugYVersion";

const char* S_STASH = "STASH";
const char* S_active_multiPageStash = "ActiveMultiPageStash";
const char* S_maxSelfPages = "MaxPersonnalPages";
const char* S_nbPagesPerIndex = "NbPagesPerIndex";
const char* S_nbPagesPerIndex2 = "NbPagesPerIndex2";
const char* S_active_sharedStash = "ActiveSharedStash";
const char* S_maxSharedPages = "MaxSharedPages";
const char* S_sharedStashFilename = "SharedStashFilename";
const char* S_separateHardSoftStash = "SeparateHardcoreStash";
const char* S_active_bigStash = "ActiveBigStash";
const char* S_displaySharedSetItemNameInGreen = "DisplaySharedSetItemNameInGreen";
const char* S_active_sharedGold = "ActiveSharedGold";


const char* S_posXPreviousBtn = "PosXPreviousBtn";
const char* S_posYPreviousBtn = "PosYPreviousBtn";
const char* S_posXNextBtn = "PosXNextBtn";
const char* S_posYNextBtn = "PosYNextBtn";
const char* S_posXSharedBtn = "PosXSharedBtn";
const char* S_posYSharedBtn = "PosYSharedBtn";
const char* S_posXPreviousIndexBtn = "PosXPreviousIndexBtn";
const char* S_posYPreviousIndexBtn = "PosYPreviousIndexBtn";
const char* S_posXNextIndexBtn = "PosXNextIndexBtn";
const char* S_posYNextIndexBtn = "PosYNextIndexBtn";
const char* S_posXPutGoldBtn = "PosXPutGoldBtn";
const char* S_posYPutGoldBtn = "PosYPutGoldBtn";
const char* S_posXTakeGoldBtn = "PosXTakeGoldBtn";
const char* S_posYTakeGoldBtn = "PosYTakeGoldBtn";

const char* S_STATS_POINTS = "STATS POINTS";
const char* S_active_StatsPoints = "ActiveStatsUnassignment";
const char* S_keyUsedForUnassignStatPoint = "KeyUsed";
const char* S_active_StatsShiftClickLimit = "ActiveShiftClickLimit";
const char* S_limitValueToShiftClick = "LimitValueToShiftClick";

const char* S_SKILL_ON_LEVEL_UP = "SKILL ON LEVEL UP";
const char* S_active_SkillPerLevelUpChange = "ActiveSkillPerLevelUp";
const char* S_skillPerLevelUp = "SkillPerLevelUp";

const char* S_STAT_ON_LEVEL_UP = "STAT ON LEVEL UP";
const char* S_active_StatPerLevelUpChange = "ActiveStatPerLevelUp";
const char* S_statPerLevelUp = "StatPerLevelUp";

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

const char* S_SKILLS_POINTS = "SKILLS POINTS";
const char* S_active_SkillsPoints = "ActiveSkillsUnassignment";
const char* S_unassignSkillsPointsOneByOne = "ActiveSkillsUnassignmentOneByOne";
const char* S_posXUnassignSkillBtn = "PosXUnassignSkillBtn";
const char* S_posYUnassignSkillBtn = "PosYUnassignSkillBtn";

const char* S_INTERFACE = "INTERFACE";
const char* S_active_newInterfaces = "ActiveNewStatsInterface";
const char* S_selectMainPageOnOpenning = "SelectMainPageOnOpenning";
const char* S_printBackgroundOnMainPage = "PrintButtonsBackgroundOnMainStatsPage";

const char* S_EXTRA = "EXTRA";
const char* S_active_alwaysRegenMapInSP = "AlwaysRegenMapInSP";
const char* S_nbPlayersCommandByDefault = "NBPlayersByDefault";
const char* S_active_DisplayItemLevel = "ActiveDisplayItemLevel";
const char* S_active_RunLODs = "ActiveLaunchAnyNumberOfLOD";
const char* S_active_AlwaysDisplayLifeMana = "AlwaysDisplayLifeAndManaValues";
const char* S_active_EnabledTXTFilesWithMSExcel= "EnabledTXTFilesWhenMSExcelOpenIt";
const char* S_active_DisplayBaseStatsValue = "ActiveDisplayBaseStatsValue";
const char* S_active_LadderRunewords = "ActiveLadderRunewords";
const char* S_active_EnabledCowPortalWhenCowKingWasKill = "ActiveCowPortalWhenCowKingWasKilled";

const char* S_DLL = "DLL:\t";
const char* S_DEFAULT = "DEFAULT:";
const char* S_USER = "USER:\t";
const char* S_FIXED = "FIXED:\t";


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
	active_logFile = atoi(buffer)+1;
	log_msg("active_logFile\t\t\t\t= %d\n", active_logFile-1);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_Commands, "0");
	active_Commands = atoi(buffer) != 0;
	log_msg("active_Commands\t\t\t\t= %d\n", active_Commands);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_CheckMemory, "1");
	active_CheckMemory = atoi(buffer) != 0;
	log_msg("active_CheckMemory\t\t\t= %d\n", active_CheckMemory);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_othersFeatures, "0");
	active_othersFeatures = atoi(buffer) != 0;
	log_msg("active_othersFeatures\t\t= %u\n", active_othersFeatures);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL,S_dllFilenames,"");
	strcat(buffer,"|");
	char* buf = &buffer[strlen(buffer)];
	if (!iniFixedFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
	if (!iniFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
		iniDefaultFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize);
	dllFilenames = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
	strcpy(dllFilenames,buffer);

	log_msg("dllFilenames\t\t\t\t= %s\n",dllFilenames);

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
		log_msg("active_MoveAndResizeWindow\t= %d\n", active_SetWindowPos);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_X, "0");
		windowedX = atoi(buffer);
		log_msg("windowedX\t\t\t\t\t= %d\n", windowedX);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Y, "0");
		windowedY = atoi(buffer);
		log_msg("windowedY\t\t\t\t\t= %d\n", windowedY);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Width, "0");
		windowedWidth = atoi(buffer);
		log_msg("windowedWidth\t\t\t\t= %d\n", windowedWidth);

		GET_PRIVATE_PROFILE_STRING(S_WINDOWED, S_Height, "0");
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
//			log_msg("\tsavePath\t\t\t= %s\n", savePath);
			return;
		}

		if (buffer[start+1]!=':')
		{
			char buf[MAX_PATH];
			buf[0]=NULL;
			D2FogGetInstallPath(buf,MAX_PATH);
			savePath = (char*)D2FogMemAlloc(strlen(buf) + curSize - start + 1,__FILE__,__LINE__,0);
			strcpy(savePath,buf);
			strcat(savePath,&buffer[start]);
		} else {
			savePath = (char*)D2FogMemAlloc(curSize-start+1,__FILE__,__LINE__,0);
			strcpy(savePath,&buffer[start]);
		}
		log_msg("savePath\t\t\t\t\t= %s\n", savePath);
	}
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
			switch(version_D2Game)
			{
			case V109b: strcpy(buffer, "v 1.09b");break;
			case V109d: strcpy(buffer, "v 1.09d");break;
			//case V110:  strcpy(buffer, "v 1.10");break;
			//case V111:  strcpy(buffer, "v 1.11");break;
			case V111b: strcpy(buffer, "v 1.11b");break;
			default:
				active_VersionTextChange=0;
			}
		}

		versionText = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(versionText,buffer);
		log_msg("versionText\t\t\t\t\t= %s\n", versionText);

		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_modVersionColor, "0");
		modVersionColor = atoi(buffer);
		log_msg("modVersionColor\t\t\t\t= %u\n", modVersionColor);
	}

	GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_active_PrintPlugYVersion, "1");
	active_PrintPlugYVersion = atoi(buffer) != 0;
	log_msg("active_PrintPlugYVersion\t= %u\n", active_PrintPlugYVersion);


	if (active_PrintPlugYVersion)
	{
		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_colorOfPlugYVersion, "4");
		colorOfPlugYVersion = atoi(buffer);
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
//		log_msg("active_PlayerCustomData\t\t= %d\n", active_PlayerCustomData);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_maxSelfPages, "0");
		maxSelfPages = atoi(buffer) - 1;
		log_msg("maxSelfPages\t\t\t\t= %u\n", maxSelfPages);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_nbPagesPerIndex, "10");
		nbPagesPerIndex = atoi(buffer);
		if (!nbPagesPerIndex) nbPagesPerIndex=10;
		log_msg("nbPagesPerIndex\t\t\t\t= %u\n", nbPagesPerIndex);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_nbPagesPerIndex2, "100");
		nbPagesPerIndex2 = atoi(buffer);
		if (!nbPagesPerIndex2) nbPagesPerIndex2=100;
		log_msg("nbPagesPerIndex2\t\t\t= %u\n", nbPagesPerIndex2);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_sharedStash, "0");
		active_sharedStash = atoi(buffer) != 0;
		log_msg("active_sharedStash\t\t\t= %u\n", active_sharedStash);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPreviousBtn,"-1");
		posXPreviousBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPreviousBtn,"-1");
		posYPreviousBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXNextBtn,"-1");
		posXNextBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYNextBtn,"-1");
		posYNextBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXSharedBtn,"-1");
		posXSharedBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYSharedBtn,"-1");
		posYSharedBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPreviousIndexBtn,"-1");
		posXPreviousIndexBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPreviousIndexBtn,"-1");
		posYPreviousIndexBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXNextIndexBtn,"-1");
		posXNextIndexBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYNextIndexBtn,"-1");
		posYNextIndexBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPutGoldBtn,"-1");
		posXPutGoldBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPutGoldBtn,"-1");
		posYPutGoldBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXTakeGoldBtn,"-1");
		posXTakeGoldBtn = atoi(buffer);
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYTakeGoldBtn,"-1");
		posYTakeGoldBtn = atoi(buffer);

		log_msg("\t Buttons Positions: %d %d %d %d %d %d %d %d %d %d\n",posXPreviousBtn,posYPreviousBtn,posXNextBtn,posYNextBtn,posXSharedBtn,posYSharedBtn,posXPreviousIndexBtn,posYPreviousIndexBtn,posXNextIndexBtn,posYNextIndexBtn);

	}

	if (active_sharedStash)
	{
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_maxSharedPages, "0");
		maxSharedPages = atoi(buffer) - 1;
		log_msg("maxSharedPages\t\t\t\t= %u\n", maxSharedPages);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_sharedStashFilename, "SharedStashSave");
		sharedStashFilename = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(sharedStashFilename, buffer);
		log_msg("sharedStashFilename\t\t\t= %s\n", sharedStashFilename);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_separateHardSoftStash, "1");
		separateHardSoftStash = atoi(buffer) != 0;
		log_msg("separateHardSoftStash\t\t= %u\n", separateHardSoftStash);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_displaySharedSetItemNameInGreen, "1");
		displaySharedSetItemNameInGreen = atoi(buffer) != 0;
		log_msg("displaySharedSetItemNameInGreen = %u\n", displaySharedSetItemNameInGreen);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_sharedGold, "1");
		active_sharedGold = atoi(buffer) != 0;
		log_msg("active_sharedGold\t\t\t= %u\n", active_sharedGold);
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

	GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_unassignSkillsPointsOneByOne, "0");
	unassignSkillsPointsOneByOne = atoi(buffer) != 0;
	log_msg("unassignSkillsPointsOneByOne\t\t\t= %d\n", unassignSkillsPointsOneByOne);
	if (unassignSkillsPointsOneByOne)
	{
		active_SkillsPoints = true;
		log_msg("active_SkillsPoints\t\t\t= %d\n", active_SkillsPoints);
	}

	GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_posXUnassignSkillBtn,"-1");
	posXUnassignSkillBtn = atoi(buffer);
	log_msg("posXUnassignSkillBtn\t\t\t= %d\n", posXUnassignSkillBtn);

	GET_PRIVATE_PROFILE_STRING(S_SKILLS_POINTS, S_posYUnassignSkillBtn,"-1");
	posYUnassignSkillBtn = atoi(buffer);
	log_msg("posXUnassignSkillBtn\t\t\t= %d\n", posYUnassignSkillBtn);

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
	if (active_WorldEvent && ((version_D2Game == V109b) || (version_D2Game == V109d)) ) {
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
		triggerAtSolJSoldDelta = atoi(buffer)-triggerAtSolJSoldMin+1;
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
	if (active_UberQuest && ((version_D2Game == V109b) || (version_D2Game == V109d) || (version_D2Game == V110)) ) {
		active_UberQuest = 0;
		log_msg("active_UberQuest\t\t= %d (Warning : this feature is only for LoD version 1.11 or higher, so it's automatically disabled)\n", active_UberQuest);
	} else
		log_msg("active_UberQuest\t\t\t= %d\n", active_UberQuest);
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
	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_alwaysRegenMapInSP, "0");
	active_alwaysRegenMapInSP = atoi(buffer);
	log_msg("active_alwaysRegenMapInSP\t= %d\n", active_alwaysRegenMapInSP);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_nbPlayersCommandByDefault, "0");
	nbPlayersCommandByDefault = atoi(buffer);
	if (version_D2Common == V110)
		{if (nbPlayersCommandByDefault > 8) nbPlayersCommandByDefault=8;}
	else if (nbPlayersCommandByDefault > 64) nbPlayersCommandByDefault=64;
	log_msg("nbPlayersCommandByDefault\t= %d\n", nbPlayersCommandByDefault);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_DisplayItemLevel, "0");
	active_DisplayItemLevel = atoi(buffer);
	log_msg("active_DisplayItemLevel\t\t= %d\n", active_DisplayItemLevel);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_AlwaysDisplayLifeMana, "0");
	active_AlwaysDisplayLifeMana = atoi(buffer);
	log_msg("active_AlwaysDisplayLifeMana= %d\n", active_AlwaysDisplayLifeMana);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_RunLODs, "0");
	active_RunLODs = atoi(buffer);
	log_msg("active_RunLODs\t\t\t\t= %u\n", active_RunLODs);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_EnabledTXTFilesWithMSExcel, "0");
	active_EnabledTXTFilesWithMSExcel = atoi(buffer);
	log_msg("active_EnabledTXTFilesWithMSExcel= %u\n\n", active_EnabledTXTFilesWithMSExcel);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_DisplayBaseStatsValue, "0");
	active_DisplayBaseStatsValue = atoi(buffer);
	log_msg("active_DisplayBaseStatsValue= %u\n\n", active_DisplayBaseStatsValue);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_LadderRunewords, "0");
	active_LadderRunewords = atoi(buffer);
	if (active_LadderRunewords && (version_D2Common == V109b || version_D2Common == V109d) ) {
		active_LadderRunewords = 0;
		log_msg("active_LadderRunewords\t= %d (Warning : Warning : this feature is only for LoD version 1.10 or higher, so it's automatically disabled)\n", active_WorldEvent);
	} else
		log_msg("active_LadderRunewords\t= %u\n\n", active_LadderRunewords);

	GET_PRIVATE_PROFILE_STRING(S_EXTRA, S_active_EnabledCowPortalWhenCowKingWasKill, "0");
	active_EnabledCowPortalWhenCowKingWasKill = atoi(buffer);
	log_msg("active_EnabledCowPortalWhenCowKingWasKill= %u\n\n", active_EnabledCowPortalWhenCowKingWasKill);
}



void loadParameters()
{
	char buffer[BUFSIZE];
	int loading=0;
	INIFile *iniFile = new INIFile;
	INIFile *iniFixedFile = new INIFile;
	INIFile *iniDefaultFile = new INIFile;

	srand(time(NULL));

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