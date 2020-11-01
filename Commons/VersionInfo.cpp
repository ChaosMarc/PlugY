/*=================================================================
	File created by Yohann NICOLAS.

	Get Game version.

=================================================================*/

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "VersionInfo.h"

#pragma comment(lib, "Version.Lib")

const char* VersionStrings[16] = { "1.00","1.07","1.08","1.09","1.09b","1.09d","1.10","1.11","1.11b","1.12","1.13c","1.13d","1.14a","1.14b","1.14c","1.14d" };

const char* GetVersionString(int version)
{
	if (version < 0 || version >= sizeof(VersionStrings))
		return "UNKNOWN";
	return VersionStrings[version];
}

eGameVersion GetD2Version(LPCVOID pVersionResource)
{
	if (!pVersionResource) return UNKNOWN;

	UINT uLen;
	VS_FIXEDFILEINFO* ptFixedFileInfo;
	if (!VerQueryValue(pVersionResource, "\\", (LPVOID*)&ptFixedFileInfo, &uLen))
		return UNKNOWN;

	if (uLen == 0)
		return UNKNOWN;

	WORD major = HIWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD minor = LOWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD revision = HIWORD(ptFixedFileInfo->dwFileVersionLS);
	WORD subrevision = LOWORD(ptFixedFileInfo->dwFileVersionLS);

	if (major != 1)
		return UNKNOWN;
	if (minor == 0 && revision == 7 && subrevision == 0) return V107;
	if (minor == 0 && revision == 8 && subrevision == 28) return V108;
	if (minor == 0 && revision == 9 && subrevision == 19) return V109;
	if (minor == 0 && revision == 9 && subrevision == 20) return V109b;
	if (minor == 0 && revision == 9 && subrevision == 22) return V109d;
	if (minor == 0 && revision == 10 && subrevision == 39) return V110;
	if (minor == 0 && revision == 11 && subrevision == 45) return V111;
	if (minor == 0 && revision == 11 && subrevision == 46) return V111b;
	if (minor == 0 && revision == 12 && subrevision == 49) return V112;
	if (minor == 0 && revision == 13 && subrevision == 60) return V113c;
	if (minor == 0 && revision == 13 && subrevision == 64) return V113d;
	if (minor == 14 && revision == 0 && subrevision == 64) return V114a;
	if (minor == 14 && revision == 1 && subrevision == 68) return V114b;
	if (minor == 14 && revision == 2 && subrevision == 70) return V114c;
	if (minor == 14 && revision == 3 && subrevision == 71) return V114d;
	return UNKNOWN;
}

eGameVersion GetD2Version(char* gameExe)
{
	DWORD len = GetFileVersionInfoSize(gameExe, NULL);
	if (len == 0)
		return UNKNOWN;

	BYTE* pVersionResource = new BYTE[len];
	GetFileVersionInfo(gameExe, NULL, len, pVersionResource);
	eGameVersion version = GetD2Version(pVersionResource);
	delete pVersionResource;

	return version;
}

eGameVersion GetD2Version(HMODULE hModule)
{
	HRSRC hResInfo = FindResource(hModule, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	if (!hResInfo) return UNKNOWN;
	HGLOBAL hResData = LoadResource(hModule, hResInfo);
	if (!hResData) return UNKNOWN;
	LPVOID pVersionResource = LockResource(hResData);
	eGameVersion version = GetD2Version(pVersionResource);
	FreeResource(hResData);
	return version;
}

///////////////////////// END OF FILE ///////////////////////