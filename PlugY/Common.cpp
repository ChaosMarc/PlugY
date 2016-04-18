/*=================================================================
	File created by Yohann NICOLAS.
	*Modified by L'Autour.

	Common functions.
 
=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "INIfile.h"

#define sPlugyExt ".\\PlugY\\PlugYLocal.dll"
s_shifting shifting;


bool isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h)
	{return (x>=x0) && (x<x0+l) && (y>y0-h) && (y<=y0);}


void freeMessage(sWinMessage* msg)
{
	msg->managed=1;
	msg->unmanaged=0;
	D2FreeWinMessage(msg);
}

//MS C++__fastcall(ecx,edx,) vs Delphi register(eax,edx,ecx) - :(

typedef int (__stdcall *p_UCS2toUTF8)(char*, int, LPWSTR, int);
p_UCS2toUTF8 _UCS2toUTF8;

int UCS2toUTF8(char* dst, int maxdst, LPWSTR src, int lensrc)
{
	if (_UCS2toUTF8 == NULL) return 0;
	return _UCS2toUTF8(dst, maxdst, src, lensrc);
}

typedef int (__stdcall *p_UTF8toUCS2)(LPWSTR, int, char*, int);
p_UTF8toUCS2 _UTF8toUCS2;

int UTF8toUCS2(LPWSTR dst, int maxdst, char* src, int lensrc)
{
	if (_UTF8toUCS2 == NULL) return 0;
	return _UTF8toUCS2(dst, maxdst, src, lensrc);
}

typedef const LPWSTR(__fastcall *p_getTypeString)(DWORD, char**); 
p_getTypeString _getTypeString;

const LPWSTR getTypeString(DWORD code, char** IdxStr)
{
	if (_getTypeString == NULL) return L"#";
	return _getTypeString(code, IdxStr);
}

typedef LPWSTR(__fastcall *p_getTranslatedString)(int); 
p_getTranslatedString _getTranslatedString;

LPWSTR getTranslatedString(int stringID)
{
	if (_getTranslatedString == NULL) return L"#";
	return _getTranslatedString(stringID);
}

typedef int(__stdcall *p_wSprintStringLastGender)(LPWSTR, int, int); 
p_wSprintStringLastGender _wSprintStringLastGender;

int wSprintStringLastGender(LPWSTR buf, int lenbuf,int stringID)
{
	if (_wSprintStringLastGender == NULL) return 0;
	return _wSprintStringLastGender(buf, lenbuf, stringID);
}

typedef LPWSTR(__fastcall *p_cutStringGender)(LPWSTR); 
p_cutStringGender _cutStringGender;

LPWSTR cutStringGender(LPWSTR str)
{
	if (_cutStringGender == NULL) return str;
	return _cutStringGender(str);
}

typedef LPWSTR(__fastcall *p_setMonoString)(LPWSTR); 
p_setMonoString _setMonoString;

LPWSTR setMonoString(LPWSTR str)
{
	if (_setMonoString == NULL) return str;
	return _setMonoString(str);
}


typedef bool(__fastcall *p_initTranslatedString)(int); 

HINSTANCE PlugyLocalLib = NULL;

bool initLocaleStrings()
{
	p_initTranslatedString initTranslatedString;
    
    PlugyLocalLib = LoadLibrary(sPlugyExt);
 
    if (PlugyLocalLib != NULL)
    {
		log_msg("Loading PlugYLocal.dll\n");
        initTranslatedString = (p_initTranslatedString)GetProcAddress(PlugyLocalLib, "__fastcall initTranslatedString");
		if (NULL != initTranslatedString)
		{
			log_msg("Loading local strings from PlugYLocal.ini\n");				

			_UCS2toUTF8 = (p_UCS2toUTF8)GetProcAddress(PlugyLocalLib, "__stdcall UCS2toUTF8");
			_UTF8toUCS2 = (p_UTF8toUCS2)GetProcAddress(PlugyLocalLib, "__stdcall UTF8toUCS2");

			_getTypeString = (p_getTypeString)GetProcAddress(PlugyLocalLib, "__fastcall getTypeString");
			_cutStringGender = (p_cutStringGender)GetProcAddress(PlugyLocalLib, "__fastcall cutStringGender");
			_wSprintStringLastGender = (p_wSprintStringLastGender)GetProcAddress(PlugyLocalLib, "__stdcall wSprintStringLastGender");
			_setMonoString = (p_setMonoString)GetProcAddress(PlugyLocalLib, "__fastcall setMonoString");

			_getTranslatedString = (p_getTranslatedString)GetProcAddress(PlugyLocalLib, "__fastcall getTranslatedString");
			if ((NULL != _getTranslatedString) && 
				(NULL != _getTypeString))
			{				
				initTranslatedString(D2GetLang());
				return true;
			}
			log_msg("Failed loading local strings\n");
		}

		if (FreeLibrary(PlugyLocalLib))
		{
			PlugyLocalLib = NULL;
		}		
    } else log_msg("Failed loading PlugYLocal.dll\n");
	return false;
}

void freeLocaleStrings()
{
	if (PlugyLocalLib == NULL) return;
	FreeLibrary(PlugyLocalLib);
}

LPWSTR getTypeUString (WORD id, LPWSTR lpText, DWORD size)
{
	ItemTypesBIN* itemTypeData = D2GetItemTypesBIN(id);
	if (!itemTypeData)
	{
		wcsncpy(lpText, L"Bad Type", size);
		return lpText;
	}
	char* idxstr;
	LPWSTR string = getTypeString(itemTypeData->code, &idxstr);

	if (idxstr)
	{
		LPWSTR string2 = D2GetStringFromString(idxstr);
		if (string2)
		{
			wcsncpy(lpText, string2, size);
			return lpText;
		}
	}
	if (!string)
	{
		struct {
			DWORD code;
			BYTE zero;
			} code;
		code.code = itemTypeData->code;
		code.zero = 0;
		UTF8toUCS2(lpText,size, (char*)&code, 0xFFFF);
	} else 
		wcsncpy(lpText, string, size);	
	return lpText;
}



/*================================= END OF FILE =================================*/