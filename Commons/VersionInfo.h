/*=================================================================
	File created by Yohann NICOLAS.

	Get Game version.

=================================================================*/
#pragma once

#include <windows.h>

enum eGameVersion
{
	UNKNOW = -1,
	V100 = 0,
	V107,
	V108,
	V109,
	V109b,
	V109d,
	V110,
	V111,
	V111b,
	V112,
	V113c,
	V113d,
	V114a,
	V114b,
	V114c,
	V114d
};

const char* GetVersionString(int version);
eGameVersion GetD2Version(char* gamePath);
eGameVersion GetD2Version(HMODULE hModule);

///////////////////////// END OF FILE ///////////////////////