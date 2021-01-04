/*=================================================================
	File created by Yohann NICOLAS.

	Localized strings functions.

=================================================================*/

#include "INIfile.h"
#include "LocalizedStrings.h"
#include "common.h"
#include <stdio.h>

const char* LOCALIZED_STRINGS_FILENAME = "PlugY\\LocalizedStrings.ini";

LPWSTR StripGender(LPWSTR text)
{
	if (text[0] == L' ')
		text++;
	if (text[0] != L'[')
		return text;
	text++;
	while (text[0] != L']' && text[0] != NULL)
		text++;
	text++;
	return text;
}
LPCWSTR StripGender(LPCWSTR text) { return StripGender((LPWSTR)text); }

///////////////////////////////////////// Get Local Strings /////////////////////////////////////////

struct LocalizedTypeString
{
	DWORD code;
	LPSTR itemStr;
	LPWSTR typeLocalizedString;
} *sLocalizedTypeStrings;

LPWSTR sLocalizedStrings[100];
int nbLocalizedTypeString = 0;

LPWSTR getLocalString(int stringId)
{
	if (stringId < 0 || stringId >= 100)
		return L"";
	return sLocalizedStrings[stringId];
}

LPCWSTR getLocalTypeString(DWORD code)
{
	for (int i = 0; i < nbLocalizedTypeString; i++)
	{
		if (sLocalizedTypeStrings[i].code == code)
		{
			log_msg("Code=%08X\n", code);
			if (sLocalizedTypeStrings[i].itemStr)
				return StripGender(D2GetStringFromString(sLocalizedTypeStrings[i].itemStr));
			LPWSTR text = StripGender(sLocalizedTypeStrings[i].typeLocalizedString);
			if (!text || !text[0])
				break;
			return text;
		}
	}
	char itemIdx[5];
	itemIdx[0] = (code) & 0xFF;
	itemIdx[1] = (code >> 8) & 0xFF;
	itemIdx[2] = (code >> 16) & 0xFF;
	itemIdx[3] = (code >> 24) & 0xFF;
	itemIdx[4] = 0;
	LPWSTR typeName = StripGender(D2GetStringFromString(itemIdx));
	if (wcsstr(typeName, L"-not xlated call ken") == NULL)
		return typeName;

	static WCHAR itemIdxW[5];
	itemIdxW[0] = (code) & 0xFF;
	itemIdxW[1] = (code >> 8) & 0xFF;
	itemIdxW[2] = (code >> 16) & 0xFF;
	itemIdxW[3] = (code >> 24) & 0xFF;
	itemIdxW[4] = 0;
	return itemIdxW;
}

///////////////////////////////////////// Load Strings /////////////////////////////////////////

#define LOAD(I) loadLocalString(iniFile, I, L#I, key)
#define BUFSIZE 0x400

void loadLocalString(INIFileW *iniFile, int id, LPCWSTR section, LPCWSTR key)
{
	WCHAR buffer[BUFSIZE];
	iniFile->GetPrivateProfileString(section, key, NULL, buffer, BUFSIZE);
	int len = wcslen(buffer);
	if (len == 0)
		iniFile->GetPrivateProfileString(section, L"ENG", section, buffer, BUFSIZE);
	len = wcslen(buffer);
	if (len == 0)
	{
		len = wcslen(section);
		sLocalizedStrings[id] = new WCHAR[len + 1];
		wcsncpy(sLocalizedStrings[id], section, len);
		sLocalizedStrings[id][len] = NULL;
		return;
	}

	int j = 0;
	int i = 0;
	if (buffer[0] == L'"' && buffer[len-1] == L'"')
	{
		buffer[len-1] = NULL;
		i++;
		len -= 2;
	}
	sLocalizedStrings[id] = new WCHAR[len + 1];
	for (; i<len; i++)
	{
		if (buffer[i] == L'\\' && buffer[i+1] == L'n')
		{
			sLocalizedStrings[id][j++] = L'\n';
			i++;
		}
		else
			sLocalizedStrings[id][j++] = buffer[i];
	}
	sLocalizedStrings[id][j] = NULL;
}

int GetPrivateProfileStringList(LPCWCHAR m_cache, LPCWSTR section, LPCWSTR key)
{
	WCHAR sectionString[MAX_SECTIONNAME_LENGTH];
	_snwprintf(sectionString, MAX_SECTIONNAME_LENGTH, L"\n[%s", section);
	WCHAR keyString[MAX_KEYNAME_LENGTH];
	_snwprintf(keyString, MAX_KEYNAME_LENGTH, L"\n%s=", key);
	int keyLen = wcslen(keyString);
	WCHAR defKeyString[MAX_KEYNAME_LENGTH];
	_snwprintf(defKeyString, MAX_KEYNAME_LENGTH, L"\n%s=", L"ENG");
	int defKeyLen = wcslen(defKeyString);
	WCHAR itemKeyString[MAX_KEYNAME_LENGTH];
	_snwprintf(itemKeyString, MAX_KEYNAME_LENGTH, L"\n%s=", L"ITEM");
	int itemKeyLen = wcslen(itemKeyString);

	// Get nb TYPE sections.
	LPCWSTR end;
	int nb = 0;
	LPCWSTR cur = m_cache;
	while ((cur = wcsstr(cur, sectionString)))
	{
		cur = wcsstr(cur, L"]") + 1;
		if (cur == NULL)
			continue;
		nb++;
	}

	// Allocation
	sLocalizedTypeStrings = new LocalizedTypeString[nb];

	// Search next section.
	cur = m_cache;
	LPCWSTR nextHeader = wcsstr(cur, sectionString);

	// Treat next section
	int i = 0;
	while (nextHeader && i < nb)
	{
		cur = nextHeader + wcslen(sectionString);
		end = wcsstr(cur, L"]");
		if (end == NULL)
			break;
		nextHeader = wcsstr(end, sectionString);
		if (cur == end) { cur++; continue; }

		// Fill code
		sLocalizedTypeStrings[i].code = (*cur & 0xFF); cur++;
		if (cur != end) { sLocalizedTypeStrings[i].code |= (*cur & 0xFF) << 8; cur++; } else sLocalizedTypeStrings[i].code |= ' ' << 8;
		if (cur != end) { sLocalizedTypeStrings[i].code |= (*cur & 0xFF) << 16; cur++; } else sLocalizedTypeStrings[i].code |= ' ' << 16;
		if (cur != end) { sLocalizedTypeStrings[i].code |= (*cur & 0xFF) << 24; cur++; } else sLocalizedTypeStrings[i].code |= ' ' << 24;
		sLocalizedTypeStrings[i].itemStr = NULL;

		// Search item key
		cur = wcsstr(end + 1, itemKeyString);
		if (!(cur == NULL || (nextHeader && cur > nextHeader) || cur[itemKeyLen] == '\r' || cur[itemKeyLen] == '\n' || cur[itemKeyLen] == NULL))// Found
		{
			cur += itemKeyLen;
			end = cur;
			while (end[0] != '\r' && end[0] != '\n' && end[0] != NULL)
				end++;
			sLocalizedTypeStrings[i].itemStr = new char[end - cur + 1];
			for (int j = 0; j < end - cur; j++)
				sLocalizedTypeStrings[i].itemStr[j] = (char)cur[j];
			sLocalizedTypeStrings[i].itemStr[end - cur] = NULL;
			i++;
			continue;
		}

		// Search lng key
		cur = wcsstr(end + 1, keyString);
		if (cur == NULL || (nextHeader && cur > nextHeader) || cur[keyLen] == '\r' || cur[keyLen] == '\n' || cur[keyLen] == NULL)// Not found
		{
			// Search def key
			cur = wcsstr(end + 1, defKeyString);
			if (cur == NULL || (nextHeader && cur > nextHeader) || cur[defKeyLen] == '\r' || cur[defKeyLen] == '\n' || cur[defKeyLen] == NULL)// Not found
			{
				sLocalizedTypeStrings[i].typeLocalizedString = new WCHAR[1];
				sLocalizedTypeStrings[i].typeLocalizedString[0] = NULL;
				i++;
				continue;
			}
			cur += defKeyLen;
		}
		else
			cur += keyLen;

		// Search end value.
		end = cur;
		while (end[0] && end[0] != '\r' && end[0] != '\n')
			end++;

		// Strip ""
		if (cur[0] == '"' && (end - 1)[0] == '"') { cur++; end--; }

		// Strip Gender
		if (cur[0] == '[')
		{
			LPCWSTR tmp = cur;
			while (tmp[0] && tmp[0] != ']' && tmp[0] != '\r' && tmp[0] != '\n')
				tmp++;
			if (tmp[0] == ']')
			{
				cur = tmp + 1;
				end = cur;
				while (end[0] && end[0] != '[' && end[0] != '\r' && end[0] != '\n' && end[0] != '"')
					end++;
			}
		}

		// Fill value
		sLocalizedTypeStrings[i].typeLocalizedString = new WCHAR[end - cur + 1];
		_snwprintf(sLocalizedTypeStrings[i].typeLocalizedString, end - cur, cur);
		sLocalizedTypeStrings[i].typeLocalizedString[end - cur] = NULL;
		i++;
	}
	return nb;
}

void loadLocalizedStrings(int language)
{
	if (sLocalizedTypeStrings)
		return;

	INIFileW *iniFile = new INIFileW;

	log_msg("***** Load localized Strings *****\n");
	if (iniFile->InitReadWrite(LOCALIZED_STRINGS_FILENAME, INIFILE_MPQREAD, 0))//C:\\Jeux\\Blizzard\\D2\\-
		log_msg("File %s loaded from MPQ.\n\n", LOCALIZED_STRINGS_FILENAME);
	else if (iniFile->InitReadWrite(LOCALIZED_STRINGS_FILENAME, INIFILE_READ, 0))//C:\\Jeux\\Blizzard\\D2\\-
		log_msg("File %s loaded from PlugY folder.\n\n", LOCALIZED_STRINGS_FILENAME);
	else
	{
		log_msg("Failed to load %s.\n\n", LOCALIZED_STRINGS_FILENAME);
		return;
	}

	LPCWSTR key;
	switch (language)
	{
		case LNG_ENG: key = L"ENG"; break;
		case LNG_ESP: key = L"ESP"; break;
		case LNG_DEU: key = L"DEU"; break;
		case LNG_FRA: key = L"FRA"; break;
		case LNG_POR: key = L"POR"; break;
		case LNG_ITA: key = L"ITA"; break;
		case LNG_JPN: key = L"JPN"; break;
		case LNG_KOR: key = L"KOR"; break;
		case LNG_SIN: key = L"SIN"; break;
		case LNG_CHI: key = L"CHI"; break;
		case LNG_POL: key = L"POL"; break;
		case LNG_RUS: key = L"RUS"; break;
		case LNG_DEF: key = L"ENG"; break;
		default: key = L"ENG";
	}

	// Load localized type string
	nbLocalizedTypeString = GetPrivateProfileStringList(iniFile->m_cache, L"TYPE_", key);

	// PlugY localized string
	LOAD(STR_STATS_UNASSIGN_WITH_LIMIT);
	LOAD(STR_STATS_UNASSIGN_WITHOUT_LIMIT);
	LOAD(STR_STATS_BASE_MIN);
	LOAD(STR_SKILLS_UNASSIGN);
	LOAD(STR_STASH_PREVIOUS_PAGE);
	LOAD(STR_STASH_NEXT_PAGE);
	LOAD(STR_TOGGLE_TO_PERSONAL);
	LOAD(STR_TOGGLE_TO_SHARED);
	LOAD(STR_TOGGLE_MULTI_DISABLED);
	LOAD(STR_STASH_PREVIOUS_INDEX);
	LOAD(STR_STASH_NEXT_INDEX);
	LOAD(STR_PUT_GOLD);
	LOAD(STR_TAKE_GOLD);
	LOAD(STR_PERSONAL_PAGE_NUMBER);
	LOAD(STR_SHARED_PAGE_NUMBER);
	LOAD(STR_NO_SELECTED_PAGE);
	LOAD(STR_SHARED_GOLD_QUANTITY);
	LOAD(STR_PREVIOUS_PAGE);
	LOAD(STR_NEXT_PAGE);
	LOAD(STR_ITEM_LEVEL);
	LOAD(STR_PAGE_TYPE_CHANGE);

	// Cube receipt :
	LOAD(STR_COW_PORTAL);
	LOAD(STR_PANDEMONIUM_PORTAL);
	LOAD(STR_PANDEMONIUM_FINAL_PORTAL);
	LOAD(STR_FULL);
	LOAD(STR_REPAIR);
	LOAD(STR_AND);
	LOAD(STR_RECHARGE);
	LOAD(STR_DESTROY_FILLERS);
	LOAD(STR_REMOVE_FILLERS);
	LOAD(STR_REGENERATE);
	LOAD(STR_UPGRADE_TO_EXCEPTIONAL);
	LOAD(STR_UPGRADE_TO_ELITE);
	LOAD(STR_ETHERAL);
	LOAD(STR_NOT_ETHERAL);
	LOAD(STR_NOT_RUNEWORD);
	LOAD(STR_BASIC);
	LOAD(STR_EXCEPTIONAL);
	LOAD(STR_ELITE);
	LOAD(STR_CRACKED);
	LOAD(STR_NORMAL);
	LOAD(STR_SUPERIOR);
	LOAD(STR_MAGIC);
	LOAD(STR_SET);
	LOAD(STR_RARE);
	LOAD(STR_UNIQUE);
	LOAD(STR_CRAFTED);
	LOAD(STR_TEMPERED);
	LOAD(STR_ITEM);
	LOAD(STR_ITEM_SAME_TYPE);
	LOAD(STR_INCLUDE_UPGRADED);
	LOAD(STR_WITHOUT_SOCKET);
	LOAD(STR_WITH_SOCKETS);
	LOAD(STR_WITH_N_SOCKETS);
	LOAD(STR_ONLY_N_H);
	LOAD(STR_ONLY_HELL);
	LOAD(STR_ONLY_CLASS);

	// Breakpoints :
	LOAD(STR_MERCENARIES);
	LOAD(STR_MERC_ACT_1);
	LOAD(STR_MERC_ACT_2);
	LOAD(STR_MERC_ACT_3);
	LOAD(STR_MERC_ACT_5);
	LOAD(STR_BREAKPOINT);
	LOAD(STR_BREAKPOINTS);
	LOAD(STR_BLOCK_FRAMES);
	LOAD(STR_CASTING_FRAMES);
	LOAD(STR_HIT_RECOVERY_FRAMES);
	LOAD(STR_1H_SWINGING_WEAPON);
	LOAD(STR_OTHER_WEAPONS);
	LOAD(STR_HUMAN_FORM);
	LOAD(STR_BEAR_FORM);
	LOAD(STR_WOLF_FORM);
	LOAD(STR_VAMPIRE_FORM);
	LOAD(STR_SPEARS_AND_STAVES);
	LOAD(STR_LIGHTNING_CHAIN_LIGHTNING);
	LOAD(STR_OTHER_SPELLS);

	iniFile->close();
	delete iniFile;
}

/*================================= END OF FILE =================================*/