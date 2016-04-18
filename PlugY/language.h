/*=================================================================
	File created by Yohann NICOLAS.

	Language management.

=================================================================*/

#ifndef __LANGUAGE_H__INCLUDED
#define __LANGUAGE_H__INCLUDED

extern bool active_ChangeLanguage;
extern DWORD selectedLanguage;

extern bool active_LanguageManagement;
extern DWORD defaultLanguage;

union t_availableLanguages
{
	DWORD all;
	struct {
		DWORD eng:1;
		DWORD esp:1;
		DWORD deu:1;
		DWORD fra:1;
		DWORD por:1;
		DWORD ita:1;
		DWORD jpn:1;
		DWORD kor:1;
		DWORD sin:1;
		DWORD chi:1;
		DWORD pol:1;
		DWORD rus:1;
	};
};
extern t_availableLanguages availableLanguages;

void Install_LanguageManagement();

#endif