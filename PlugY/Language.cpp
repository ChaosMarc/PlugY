/*=================================================================
	File created by Yohann NICOLAS.

	Language management.

=================================================================*/

#include "language.h"
#include "common.h"
#include <stdio.h>


bool active_ChangeLanguage = true;
DWORD selectedLanguage = LNG_ENG;

bool active_LanguageManagement = false;
DWORD defaultLanguage = LNG_ENG;
t_availableLanguages availableLanguages;

DWORD* ptCurrentLanguage;

DWORD STDCALL languageManagement ()
{
	if (active_ChangeLanguage) *ptCurrentLanguage = selectedLanguage;
	if (active_LanguageManagement)
	if ((*ptCurrentLanguage > LNG_RUS) || !((1 << *ptCurrentLanguage) & availableLanguages.all))
		*ptCurrentLanguage = defaultLanguage;
	return *ptCurrentLanguage;
}


void Install_LanguageManagement()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2Lang for language management. (LanguageManagement)\n");

	ptCurrentLanguage = *(DWORD**)((DWORD)D2GetLang + (version_D2Lang >= V111 ? 0x51: 0x5C));

	// Language management
	mem_seek( (DWORD)D2GetLang + (version_D2Lang >= V111 ? 0x3E : 0x49));//6FC13E39-6FC10000
	memt_byte( 0xA1 , 0xE8);
	MEMT_REF4( ptCurrentLanguage, languageManagement);
	//6FC13E39  |. A1 EC0CC26F    MOV EAX,DWORD PTR DS:[6FC20CEC]
	//003D91FE  |. A1 1C0A3E00    MOV EAX,DWORD PTR DS:[3E0A1C]
	//003DA0AE  |. A1 1C0A3E00    MOV EAX,DWORD PTR DS:[3E0A1C]

	log_msg("\n");

	isInstalled = true;
}


/*================================= END OF FILE =================================*/