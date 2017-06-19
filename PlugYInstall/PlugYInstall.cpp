/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Patch D2gfx.dll to install PlugY.

=================================================================*/
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "../Commons/VersionInfo.h"
#include <stdio.h>

DWORD loadCallerAddr;
DWORD loadCallerLen;
BYTE loadCallerNew[6] = { 0x90,0xE8,0x00,0x00,0x00,0x00 }; // Call load PlugY library
BYTE loadCallerOld[6] = { 0xFF,0x15,0x00,0x00,0x00,0x00 }; // CALL DWORD PTR DS:[<&KERNEL32.LoadLibrary>]

DWORD freeCallerAddr;
DWORD freeCallerLen;
BYTE freeCallerNew[6] = { 0x90,0xE8,0x00,0x00,0x00,0x00 }; // Call free PlugY library
BYTE freeCallerOld[6] = { 0xFF,0x15,0x00,0x00,0x00,0x00 }; // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]

DWORD loadDllAddr;
DWORD loadDllLen;
BYTE loadDll[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0x50,							//PUSH EAX
	0x68,0x80,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE80                               ; ASCII "PlugY.dll"
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x2B,						//JE SHORT d2gfx.6FA7BE33
	0x50,							//PUSH EAX
	0x68,0x90,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE10                            ;Init String
	0x50,							//PUSH EAX
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAddress>]    ; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x04,						//JE SHORT d2gfx.6FA7BDC1
	0x6A,0x00,						//PUSH 0
	0xEB,0x13,						//JMP SHORT d2gfx.6FA7BDC1
	0x68,0x10,0x27,0x00,0x00,		//PUSH 2710	                                     ;Init Ordinal(10000)
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAddress>]    ; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x02,						//JE SHORT d2gfx.6FA7BDC1
	0xFF,0xD0,						//CALL EAX
	0x58,							//POP EAX
	0x58,							//POP EAX
	0xC2,0x04,0x00,					//RETN 4
	0x00,0x00,0x00,0x00 };			//HANDLE var;

DWORD freeDllAddr;
DWORD freeDllLen;
BYTE freeDll[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x48,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]       ; kernel32.FreeLibrary
	0x50,							//PUSH EAX
	0xA1,0xFC,0xEF,0xA8,0x6F,		//MOV EAX,DWORD PTR DS:[6FA8EFFC]
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x2D,						//JE SHORT d2gfx.6FA7BE74
	0x50,							//PUSH EAX
	0x68,0xA0,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE20                            ;Release String
	0x50,							//PUSH EAX
	//0x33,0xC0,					//XOR EAX,EAX
	//0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAdd>; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x75,0x13,						//JNZ SHORT d2gfx.6FA7BDEF
	0x68,0x11,0x27,0x00,0x00,		//PUSH 2711	                                     ;Release Ordinal(10001)
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAdd>; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x02,						//JE SHORT d2gfx.6FA7BDEF
	0xFF,0xD0,						//CALL EAX
	0xFF,0x15,0x48,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.FreeLibrar>; kernel32.FreeLibrary
	0x58,							//POP EAX
	0xC2,0x04,0x00 };				//RETN 4

DWORD libraryNameAddr;
DWORD libraryNameLen;
LPCSTR libraryName = "PlugY.dll";

DWORD initNameAddr;
DWORD initNameLen;
LPCSTR initName = "_Init@4";

DWORD releaseNameAddr;
DWORD releaseNameLen;
LPCSTR releaseName = "_Release@0";

int msgBox(LPCSTR boxName, UINT uType, LPCSTR pFormat, ...)
{
	char buffer[300];
	va_list lArgs;
	va_start( lArgs, pFormat );
	vsprintf_s( buffer, sizeof(buffer), pFormat, lArgs );
	va_end(lArgs);

	return MessageBox(NULL, buffer, boxName, uType);
}

int Align(int v)
{
	return v % 16 ? v + 16 - v % 16 : v;
}

////////////////////////////// EXPORTED FUNCTIONS //////////////////////////////

int Patch(FILE *targetFile)
{
	bool error = false;
	int ident = 0;
	BYTE buffer[100];
	BYTE zeros[100];
	memset(zeros, 0, sizeof(zeros));

	fseek(targetFile, loadCallerAddr, SEEK_SET);
	fread(buffer, sizeof(loadCallerNew), 1, targetFile);
	if (memcmp(buffer, loadCallerOld, sizeof(loadCallerNew)) != 0) error = true;
	if (memcmp(buffer, loadCallerNew, sizeof(loadCallerNew)) == 0) ident++;

	fseek(targetFile, freeCallerAddr, SEEK_SET);
	fread(buffer, sizeof(freeCallerNew), 1, targetFile);
	if (memcmp(buffer, freeCallerOld, sizeof(freeCallerNew)) != 0) error = true;
	if (memcmp(buffer, freeCallerNew, sizeof(freeCallerNew)) == 0) ident++;

	fseek(targetFile, loadDllAddr, SEEK_SET);
	fread(buffer, sizeof(loadDll), 1, targetFile);
	if (memcmp(buffer, zeros, sizeof(loadDll)) != 0) error = true;
	if (memcmp(buffer, loadDll, sizeof(loadDll)) == 0) ident++;

	fseek(targetFile, freeDllAddr, SEEK_SET);
	fread(buffer, sizeof(freeDll), 1, targetFile);
	if (memcmp(buffer, zeros, sizeof(freeDll)) != 0) error = true;
	if (memcmp(buffer, freeDll, sizeof(freeDll)) == 0) ident++;

	fseek(targetFile, initNameAddr, SEEK_SET);
	fread(buffer, initNameLen, 1, targetFile);
	if (memcmp(buffer, zeros, initNameLen) != 0) error = true;
	if (memcmp(buffer, initName, initNameLen) == 0) ident++;

	fseek(targetFile, releaseNameAddr, SEEK_SET);
	fread(buffer, releaseNameLen, 1, targetFile);
	if (memcmp(buffer, zeros, releaseNameLen) != 0) error = true;
	if (memcmp(buffer, releaseName, releaseNameLen) == 0) ident++;

	fseek(targetFile, libraryNameAddr, SEEK_SET);
	fread(buffer, libraryNameLen, 1, targetFile);
	if (memcmp(buffer, zeros, libraryNameLen) != 0) error = true;
	if (memcmp(buffer, libraryName, libraryNameLen) == 0) ident++;

	if (error)
		return ident == 7 ? 1 : 2;

	fseek(targetFile, loadCallerAddr, SEEK_SET);
	fwrite(loadCallerNew, 6, 1, targetFile);

	fseek(targetFile, freeCallerAddr, SEEK_SET);
	fwrite(freeCallerNew, 6, 1, targetFile);

	fseek(targetFile, loadDllAddr, SEEK_SET);
	fwrite(loadDll, sizeof(loadDll), 1, targetFile);

	fseek(targetFile, freeDllAddr, SEEK_SET);
	fwrite(freeDll, sizeof(freeDll), 1, targetFile);

	fseek(targetFile, initNameAddr, SEEK_SET);
	fwrite(initName, initNameLen, 1, targetFile);

	fseek(targetFile, releaseNameAddr, SEEK_SET);
	fwrite(releaseName, releaseNameLen, 1, targetFile);

	fseek(targetFile, libraryNameAddr, SEEK_SET);
	fwrite(libraryName, libraryNameLen, 1, targetFile);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int Unpatch(FILE *targetFile)
{
	bool error = false;
	int ident = 0;
	BYTE buffer[100];
	BYTE zeros[100];
	memset(zeros, 0, sizeof(zeros));

	fseek(targetFile, loadCallerAddr, SEEK_SET);
	fread(buffer, 6, 1, targetFile);
	if (memcmp(buffer, loadCallerNew, 6) != 0) error = true;
	if (memcmp(buffer, loadCallerOld, 6) == 0) ident++;

	fseek(targetFile, freeCallerAddr, SEEK_SET);
	fread(buffer, 6, 1, targetFile);
	if (memcmp(buffer, freeCallerNew, 6) != 0) error = true;
	if (memcmp(buffer, freeCallerOld, 6) == 0) ident++;

	fseek(targetFile, loadDllAddr, SEEK_SET);
	fread(buffer, sizeof(loadDll), 1, targetFile);
	if (memcmp(buffer, loadDll, sizeof(loadDll)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(loadDll)) == 0) ident++;

	fseek(targetFile, freeDllAddr, SEEK_SET);
	fread(buffer, sizeof(freeDll), 1, targetFile);
	if (memcmp(buffer, freeDll, sizeof(freeDll)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(freeDll)) == 0) ident++;

	fseek(targetFile, initNameAddr, SEEK_SET);
	fread(buffer, initNameLen, 1, targetFile);
	if (memcmp(buffer, initName, initNameLen) != 0) error = true;
	if (memcmp(buffer, zeros, initNameLen) == 0) ident++;

	fseek(targetFile, releaseNameAddr, SEEK_SET);
	fread(buffer, releaseNameLen, 1, targetFile);
	if (memcmp(buffer, releaseName, releaseNameLen) != 0) error = true;
	if (memcmp(buffer, zeros, releaseNameLen) == 0) ident++;

	fseek(targetFile, libraryNameAddr, SEEK_SET);
	fread(buffer, libraryNameLen, 1, targetFile);
	if (memcmp(buffer, libraryName, libraryNameLen) != 0) error = true;
	if (memcmp(buffer, zeros, libraryNameLen) == 0) ident++;

	if (error)
		return ident == 7 ? 1 : 2;

	fseek(targetFile, loadCallerAddr, SEEK_SET);
	fwrite(loadCallerOld, 6, 1, targetFile);

	fseek(targetFile, freeCallerAddr, SEEK_SET);
	fwrite(freeCallerOld, 6, 1, targetFile);

	fseek(targetFile, loadDllAddr, SEEK_SET);
	fwrite(zeros, sizeof(loadDll), 1, targetFile);

	fseek(targetFile, freeDllAddr, SEEK_SET);
	fwrite(zeros, sizeof(freeDll), 1, targetFile);

	fseek(targetFile, initNameAddr, SEEK_SET);
	fwrite(zeros, initNameLen, 1, targetFile);

	fseek(targetFile, releaseNameAddr, SEEK_SET);
	fwrite(zeros, releaseNameLen, 1, targetFile);

	fseek(targetFile, libraryNameAddr, SEEK_SET);
	fwrite(zeros, libraryNameLen, 1, targetFile);

	return 0;
}

int main(int argc, char * argv[])
{
#ifdef RESTORE
	bool unpatch = true;
#else
	bool unpatch = argc > 1 && strcmp(argv[1], "-u") == 0;
#endif

	int version = GetD2Version("Game.exe");
	LPCSTR boxName = unpatch ? "Uninstall PlugY, The Survival Kit" : "Install PlugY, The Survival Kit";
	LPCSTR targetFilename = version > V113d ? "Game.exe" : "D2gfx.dll";

	if (version < V107 || version > V114d)
	{
		msgBox(boxName, MB_OK | MB_ICONEXCLAMATION,
			"Current version of LoD (%s) isn't compatible with PlugY.\n\n"
			"Please, install a patch between 1.09 and 1.13d.",
			GetVersionString(version));
		exit(0);
	}

	if (msgBox(boxName, MB_YESNO | MB_ICONQUESTION,
			"This programm will modify %s file in current directory.\n"
			"Before continue, you should backup it.\n\n"
			"Do you want to modify %s to %s PlugY ?",
			targetFilename, targetFilename, unpatch ? "remove": "install") == IDNO)
	{
		msgBox(boxName, MB_OK | MB_ICONASTERISK, "No changes made.");
		exit(0);
	}

	FILE *targetFile;
	if (fopen_s(&targetFile, targetFilename, "rb+"))
	{
		msgBox(boxName, MB_OK | MB_ICONEXCLAMATION,
			"Can't open %s in read/write mode.\n"
			"If Diablo II is running, can you close it and try again ?",
			targetFilename, unpatch ? "remove": "install");
		exit(0);
	}

	// Get size
	loadCallerLen = sizeof(loadCallerNew);
	freeCallerLen = sizeof(freeCallerNew);
	loadDllLen = sizeof(loadDll);
	freeDllLen = sizeof(freeDll);
	libraryNameLen = strlen(libraryName) + 1;
	initNameLen = strlen(initName) + 1;
	releaseNameLen = strlen(releaseName) + 1;

	// Get Addr
	DWORD offsetPESignature;
	fseek(targetFile, 0x3C, SEEK_SET);
	fread(&offsetPESignature, sizeof(offsetPESignature), 1, targetFile);
	DWORD sizeOfCode;
	fseek(targetFile, offsetPESignature + 0x1C, SEEK_SET);
	fread(&sizeOfCode, sizeof(sizeOfCode), 1, targetFile);
	DWORD baseOfCode;
	fseek(targetFile, offsetPESignature + 0x2C, SEEK_SET);
	fread(&baseOfCode, sizeof(baseOfCode), 1, targetFile);
	DWORD imageBase;
	fseek(targetFile, offsetPESignature + 0x34, SEEK_SET);
	fread(&imageBase, sizeof(imageBase), 1, targetFile);
	DWORD sizeOfData;
	fseek(targetFile, offsetPESignature + 0x150, SEEK_SET);
	fread(&sizeOfData, sizeof(sizeOfData), 1, targetFile);
	DWORD baseOfData;
	fseek(targetFile, offsetPESignature + 0x154, SEEK_SET);
	fread(&baseOfData, sizeof(baseOfData), 1, targetFile);

	// Set Addr
	DWORD loadLibraryAddr = imageBase;
	DWORD freeLibraryAddr = imageBase;
	DWORD getProcAddressAddr = imageBase;
	DWORD handleAddr = imageBase + baseOfData + sizeOfData;

	loadCallerAddr = 0;
	freeCallerAddr = 0;
	loadDllAddr = Align(baseOfCode + sizeOfCode - 0x100);
	freeDllAddr = Align(loadDllAddr + sizeof(loadDll));
	libraryNameAddr = Align(freeDllAddr + sizeof(freeDll));
	initNameAddr = Align(libraryNameAddr + libraryNameLen);
	releaseNameAddr = Align(initNameAddr + initNameLen);

	switch (version)
	{
	case V107:
		loadCallerAddr += 0x3882;
		freeCallerAddr += 0x3A6C;
		loadLibraryAddr += 0xC038;
		freeLibraryAddr += 0xC040;
		getProcAddressAddr += 0xC034;
		break;
	case V108:
	case V109:
	case V109b:
	case V109d:
		loadCallerAddr += 0x389B;
		freeCallerAddr += 0x3A8C;
		loadLibraryAddr += 0xC03C;
		freeLibraryAddr += 0xC044;
		getProcAddressAddr += 0xC038;
		break;
	case V110:
		loadCallerAddr += 0x3870;
		freeCallerAddr += 0x3A6D;
		loadLibraryAddr += 0xC040;
		freeLibraryAddr += 0xC048;
		getProcAddressAddr += 0xC03C;
		break;
	case V111:
		loadCallerAddr += 0x8B23;
		freeCallerAddr += 0x8ACA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case V111b:
		loadCallerAddr += 0xB423;
		freeCallerAddr += 0xB3CA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case V112:
		loadCallerAddr += 0x8F63;
		freeCallerAddr += 0x8F0A;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case V113c:
		loadCallerAddr += 0xB423;
		freeCallerAddr += 0xB3CA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case V113d:
		loadCallerAddr += 0xAA03;
		freeCallerAddr += 0xA9AA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD124;
		getProcAddressAddr += 0xD120;
		break;
	case V114a:
		loadCallerAddr += 0x1BCB;// Load advapi.dll
		freeCallerAddr += 0xF375;// Free dbghelp.dll
		loadLibraryAddr += 0x2CD118;
		freeLibraryAddr += 0x2CD120;
		getProcAddressAddr += 0x2CD11C;
		break;
	case V114b:
	case V114c:
		loadCallerAddr += 0x1BCB;// Load advapi.dll
		freeCallerAddr += 0x6F75;// Free dbghelp.dll
		loadLibraryAddr += 0x2CD11C;
		freeLibraryAddr += 0x2CD124;
		getProcAddressAddr += 0x2CD120;
		break;
	case V114d:
		loadCallerAddr += 0x621C;// Load advapi.dll
		freeCallerAddr += 0xB514;// Free dbghelp.dll
		loadLibraryAddr += 0x2CC144;
		freeLibraryAddr += 0x2CC14C;
		getProcAddressAddr += 0x2CC148;
		break;
	default:
		return false;
	}

	*(DWORD*)&loadCallerNew[2] = loadDllAddr - (loadCallerAddr + sizeof(loadCallerNew));
	*(DWORD*)&loadCallerOld[2] = loadLibraryAddr;
	*(DWORD*)&freeCallerNew[2] = freeDllAddr - (freeCallerAddr + sizeof(freeCallerNew));
	*(DWORD*)&freeCallerOld[2] = freeLibraryAddr;
	*(DWORD*)&loadDll[6] = loadLibraryAddr;
	*(DWORD*)&loadDll[12] = imageBase + libraryNameAddr;
	*(DWORD*)&loadDll[18] = loadLibraryAddr;
	*(DWORD*)&loadDll[23] = handleAddr;
	*(DWORD*)&loadDll[33] = imageBase + initNameAddr;
	*(DWORD*)&loadDll[40] = getProcAddressAddr;
	*(DWORD*)&loadDll[63] = getProcAddressAddr;
	*(DWORD*)&freeDll[6] = freeLibraryAddr;
	*(DWORD*)&freeDll[12] = handleAddr;
	*(DWORD*)&freeDll[22] = imageBase + releaseNameAddr;
	*(DWORD*)&freeDll[29] = getProcAddressAddr;
	*(DWORD*)&freeDll[48] = getProcAddressAddr;
	*(DWORD*)&freeDll[60] = freeLibraryAddr;

	// Patch / Unpatch
	int res;
	if (unpatch)
		res = Unpatch(targetFile);
	else
		res = Patch(targetFile);

	fclose(targetFile);

	if (res == 0)
		msgBox(boxName, MB_OK | MB_ICONASTERISK,
			"%s was modified.\n"
			"PlugY, The Survival Kit %s.",
			targetFilename, unpatch ? "is removed" : "is installed");
	else if (res == 1)
		msgBox(boxName, MB_OK | MB_ICONASTERISK,
			"PlugY, The Survival Kit already %s.",
			unpatch ? "uninstalled" : "installed");
	else if (res == 2)
		msgBox(boxName, MB_OK | MB_ICONASTERISK,
			"File contents in %s isn't correct.\n"
			"Unable to %s PlugY, The Survival Kit.",
			targetFilename, unpatch ? "uninstall" : "install");

    return 1;
}

///////////////////////// END OF FILE ///////////////////////