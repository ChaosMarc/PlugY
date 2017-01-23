
/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Patch D2gfx.dll to install PlugY.

=================================================================*/
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")

#include "../Commons/VersionInfo.h"
#include <windows.h>
#include <stdio.h>

const char* boxNameInstall = "Installation of PlugY, The Survival Kit Installation";
const char* boxNameUnInstall = "Uninstall PlugY, The Survival Kit ";

int CALL_LOAD[8] = { 0x389B,0x389B,0x3870,0x8B23,0xB423,0x8F63,0xB423,0xAA03 };
BYTE callNewLoad[8][6] = {	{ 0xE8,0x60,0x85,0x00,0x00,0x90 },// JMP  6FA7BE00-6FA738A0 ;install loadlibrary
							{ 0xE8,0x60,0x85,0x00,0x00,0x90 },// JMP  6FA7BE00-6FA738A0 ;install loadlibrary
							{ 0xE8,0x8B,0x85,0x00,0x00,0x90 },// JMP  6FA7BE00-6FA73875 ;install loadlibrary
							{ 0xE8,0xD8,0x42,0x00,0x00,0x90 },// JMP  6FA8CE00-6FA88B28 ;install loadlibrary
							{ 0xE8,0xD8,0x19,0x00,0x00,0x90 },// JMP  6FA8CE00-6FA8B428 ;install loadlibrary
							{ 0xE8,0x98,0x3E,0x00,0x00,0x90 },// JMP  6FA8CE00-6FA88F68 ;install loadlibrary
							{ 0xE8,0xD8,0x19,0x00,0x00,0x90 },// JMP  6FA8CE00-6FA8B428 ;install loadlibrary
							{ 0xE8,0xF8,0x23,0x00,0x00,0x90 }};// JMP  6FA8CE00-6FA8B428 ;install loadlibrary
BYTE callOldLoad[8][6] = {	{ 0xFF,0x15,0x3C,0xC0,0xA7,0x6F },
							{ 0xFF,0x15,0x3C,0xC0,0xA7,0x6F },
							{ 0xFF,0x15,0x40,0xC0,0xA7,0x6F },
							{ 0xFF,0x15,0x1C,0xD1,0xA8,0x6F },
							{ 0xFF,0x15,0x1C,0xD1,0xA8,0x6F },
							{ 0xFF,0x15,0x1C,0xD1,0xA8,0x6F },
							{ 0xFF,0x15,0x1C,0xD1,0xA8,0x6F },
							{ 0xFF,0x15,0x1C,0xD1,0xA8,0x6F }};

int CALL_FREE[8] = { 0x3A8C,0x3A8C,0x3A6D,0x8ACA,0xB3CA,0x8F0A,0xB3CA,0xA9AA };
BYTE callNewFree[8][6] = {	{ 0xE8,0xAF,0x83,0x00,0x00,0x90 }, // JMP  6FA7BE40-6FA73A91 ;install freelibrary
							{ 0xE8,0xAF,0x83,0x00,0x00,0x90 }, // JMP  6FA7BE40-6FA73A91 ;install freelibrary
							{ 0xE8,0xD2,0x83,0x00,0x00,0x90 }, // JMP  6FA7BE44-6FA73A72 ;install freelibrary
							{ 0xE8,0x75,0x43,0x00,0x00,0x90 }, // JMP  6FA8CE44-6FA88ACF ;install freelibrary
							{ 0xE8,0x75,0x1A,0x00,0x00,0x90 }, // JMP  6FA8CE44-6FA8B3CF ;install freelibrary
							{ 0xE8,0x35,0x3F,0x00,0x00,0x90 }, // JMP  6FA8CE44-6FA88F0F ;install freelibrary
							{ 0xE8,0x75,0x1A,0x00,0x00,0x90 },// JMP  6FA8CE44-6FA8B3CF ;install freelibrary
							{ 0xE8,0x95,0x24,0x00,0x00,0x90 }};// JMP  6FA8CE44-6FA8B3CF ;install freelibrary
BYTE callOldFree[8][6] = {	{ 0xFF,0x15,0x44,0xC0,0xA7,0x6F }, // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x44,0xC0,0xA7,0x6F }, // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x48,0xC0,0xA7,0x6F }, // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x2C,0xD1,0xA8,0x6F }, // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x2C,0xD1,0xA8,0x6F }, // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x2C,0xD1,0xA8,0x6F }, // CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x2C,0xD1,0xA8,0x6F },// CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]
							{ 0xFF,0x15,0x24,0xD1,0xA8,0x6F }};// CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]

int CALLER_LOADPLUGY = 0xBE00;//6FA7BE00-6FA70000
BYTE caller_LoadPlugY[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0x50,							//PUSH EAX
	0x68,0x80,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE80                               ; ASCII "PlugY.dll"
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x18,						//JE SHORT d2gfx.6FA7BE37
	0x68,0x90,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE10                            ;Init ID
	0x50,							//PUSH EAX
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAddress>]    ; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x04,						//JE SHORT d2gfx.6FA7BDC1
	0x6A,0x00,						//PUSH 0
	0xFF,0xD0,						//CALL EAX
	0x58,							//POP EAX
	0xC2,0x04,0x00,					//RETN 4
	0x59,							//POP ECX
	0xB9,0x80,0xBE,0xA7,0x6F,		//MOV ECX,d2gfx.6FA7BE80                            ;  ASCII "PlugY.dll"
	0x83,0x04,0x24,0x11,			//ADD DWORD PTR SS:[ESP],11
	0xC2,0x04,0x00 };				//RETN 4


int CALLER_FREEPLUGY = 0xBE44;//6FA7BE44-6FA70000
BYTE caller_FreePlugY[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x48,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]       ; kernel32.FreeLibrary
	0x50,							//PUSH EAX
	0xA1,0xFC,0xEF,0xA8,0x6F,		//MOV EAX,DWORD PTR DS:[6FA8EFFC]
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x20,						//JE SHORT d2gfx.6FA7BE74
	0x50,							//PUSH EAX
	0x68,0xA0,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE20                            ;release
	0x50,							//PUSH EAX
	0x33,0xC0,						//XOR EAX,EAX
	0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAdd>; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x02,						//JE SHORT d2gfx.6FA7BDEF
	0xFF,0xD0,						//CALL EAX
	0xFF,0x15,0x48,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.FreeLibrar>; kernel32.FreeLibrary
	0x58,							//POP EAX
	0xC2,0x04,0x00 };				//RETN 4


int S_DLLNAME = 0xBE80;//6FA7BE30-6FA70000
BYTE sDllName[] = { 'P','l','u','g','Y','.','d','l','l',0 };// Dll filename to load.

int S_INIT = 0xBE90;//6FA7BE10-6FA70000
BYTE sInit[] = { '_','I','n','i','t','@','4',0 };

int S_RELEASE = 0xBEA0;//6FA7BE20-6FA70000
BYTE sRelease[] = { '_','R','e','l','e','a','s','e','@','0',0 };

void updateData(int version)
{
	switch (version)
	{
	case V109b:
	case V109d:
		caller_LoadPlugY[6] -= 4;
		caller_LoadPlugY[18] -= 4;
		caller_LoadPlugY[39] -= 4;
		caller_FreePlugY[6] -= 4;
		caller_FreePlugY[36] -= 4;
		caller_FreePlugY[48] -= 4;
		break;
	case V110:
		break;
	case V111:
	case V111b:
	case V112:
	case V113c:
	case V113d:
		CALLER_LOADPLUGY += 0x1000;
		CALLER_FREEPLUGY += 0x1000;
		S_INIT += 0x1000;
		S_RELEASE += 0x1000;
		S_DLLNAME += 0x1000;
		*(DWORD*)(&caller_LoadPlugY[6]) = 0x6FA8D11C;
		*(DWORD*)(&caller_LoadPlugY[18]) = 0x6FA8D11C;
		*(DWORD*)(&caller_LoadPlugY[39]) = 0x6FA8D120;
		*(DWORD*)(&caller_FreePlugY[6]) = (version == V113d) ? 0x6FA8D124 : 0x6FA8D12C;
		*(DWORD*)(&caller_FreePlugY[36]) = 0x6FA8D120;
		*(DWORD*)(&caller_FreePlugY[48]) = (version == V113d) ? 0x6FA8D124 : 0x6FA8D12C;
		caller_LoadPlugY[13] += 0x10;
		caller_LoadPlugY[14]++;
		caller_LoadPlugY[25]++;
		caller_LoadPlugY[33] += 0x10;
		caller_LoadPlugY[34]++;
		caller_LoadPlugY[58] += 0x10;
		caller_LoadPlugY[59]++;
		caller_FreePlugY[23] += 0x10;
		caller_FreePlugY[24]++;
		caller_FreePlugY[14]++;
		caller_FreePlugY[32]++;
		break;
	}
}
////////////////////////////// EXPORTED FUNCTIONS //////////////////////////////

void Patch()
{
	if (MessageBox(0, "This programm will modify the D2gfx.dll file of the current directory.\n"
		"Before continue, don't forgot to backup D2gfx.dll if you want\n"
		"Do you want patch D2gfx.dll for the launch of PlugY ?",
		boxNameInstall, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		MessageBox(0, "D2gfx.dll isn't patched.\n",
			boxNameInstall, MB_OK | MB_ICONASTERISK);
		exit(0);
	}

	FILE *dll;

	if (fopen_s(&dll, "d2gfx.dll", "rb+"))
	{
		MessageBox(0, "Can't open D2gfx.dll in read/write mode.\n"
			"If Diablo II is running you can\'t install PlugY, The Survival Kit.\n"
			"Quit Diablo II and try again.",
			boxNameInstall, MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}

	int version = GetD2Version("Game.exe");

	if (version < V109 || version > V113d)
	{
		MessageBox(0, "Bad version of D2gfx.dll.\n"
			"You can try to uninstall any previous version of PlugY, The Survival Kit then retry.\n"
			"Or re-install a clean version (between 1.09 and 1.13d) of LOD.",
			boxNameInstall, MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}

	updateData(version);

	bool error = false;
	int ident = 0;
	BYTE buffer[100];
	BYTE zeros[100];
	memset(zeros, 0, sizeof(zeros));

	version -= V109b;

	fseek(dll, CALL_LOAD[version], SEEK_SET);
	fread(buffer, 6, 1, dll);
	if (memcmp(buffer, callOldLoad[version], 6) != 0) error = true;
	if (memcmp(buffer, callNewLoad[version], 6) == 0) ident++;

	fseek(dll, CALL_FREE[version], SEEK_SET);
	fread(buffer, 6, 1, dll);
	if (memcmp(buffer, callOldFree[version], 6) != 0) error = true;
	if (memcmp(buffer, callNewFree[version], 6) == 0) ident++;

	fseek(dll, CALLER_LOADPLUGY, SEEK_SET);
	fread(buffer, sizeof(caller_LoadPlugY), 1, dll);
	if (memcmp(buffer, zeros, sizeof(caller_LoadPlugY)) != 0) error = true;
	if (memcmp(buffer, caller_LoadPlugY, sizeof(caller_LoadPlugY)) == 0) ident++;

	fseek(dll, CALLER_FREEPLUGY, SEEK_SET);
	fread(buffer, sizeof(caller_FreePlugY), 1, dll);
	if (memcmp(buffer, zeros, sizeof(caller_FreePlugY)) != 0) error = true;
	if (memcmp(buffer, caller_FreePlugY, sizeof(caller_FreePlugY)) == 0) ident++;

	fseek(dll, S_INIT, SEEK_SET);
	fread(buffer, sizeof(sInit), 1, dll);
	if (memcmp(buffer, zeros, sizeof(sInit)) != 0) error = true;
	if (memcmp(buffer, sInit, sizeof(sInit)) == 0) ident++;

	fseek(dll, S_RELEASE, SEEK_SET);
	fread(buffer, sizeof(sRelease), 1, dll);
	if (memcmp(buffer, zeros, sizeof(sRelease)) != 0) error = true;
	if (memcmp(buffer, sRelease, sizeof(sRelease)) == 0) ident++;

	fseek(dll, S_DLLNAME, SEEK_SET);
	fread(buffer, sizeof(sDllName), 1, dll);
	if (memcmp(buffer, zeros, sizeof(sDllName)) != 0) error = true;
	if (memcmp(buffer, sDllName, sizeof(sDllName)) == 0) ident++;

	if (error)
	{
		if (ident == 7)
		{
			MessageBox(0, "PlugY, The Survival Kit already installed.",
				boxNameInstall, MB_OK | MB_ICONASTERISK);
			exit(0);
		}
		else
		{
			MessageBox(0, "Bad version of D2gfx.dll.\n"
				"You can try to uninstall any previous version of PlugY, The Survival Kit then retry.\n"
				"Or re-install a clean version (between 1.09 and 1.13d) of LOD.",
				boxNameInstall, MB_OK | MB_ICONEXCLAMATION);
			exit(0);
		}
	}

	fseek(dll, CALL_LOAD[version], SEEK_SET);
	fwrite(callNewLoad[version], 6, 1, dll);

	fseek(dll, CALL_FREE[version], SEEK_SET);
	fwrite(callNewFree[version], 6, 1, dll);

	fseek(dll, CALLER_LOADPLUGY, SEEK_SET);
	fwrite(caller_LoadPlugY, sizeof(caller_LoadPlugY), 1, dll);

	fseek(dll, CALLER_FREEPLUGY, SEEK_SET);
	fwrite(caller_FreePlugY, sizeof(caller_FreePlugY), 1, dll);

	fseek(dll, S_INIT, SEEK_SET);
	fwrite(sInit, sizeof(sInit), 1, dll);

	fseek(dll, S_RELEASE, SEEK_SET);
	fwrite(sRelease, sizeof(sRelease), 1, dll);

	fseek(dll, S_DLLNAME, SEEK_SET);
	fwrite(sDllName, sizeof(sDllName), 1, dll);

	fclose(dll);

	MessageBox(0, "D2gfx.dll patched successfully.\n"
		"PlugY, The Survival Kit installed successfully.",
		boxNameInstall, MB_OK | MB_ICONASTERISK);

	exit(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Unpatch()
{
	if (MessageBox(0, "This programm will modify the D2gfx.dll file of the current directory.\n"
		"Before continue, don't forgot to backup D2gfx.dll if you want\n"
		"Do you want patch D2gfx.dll for remove the launch of PlugY ?",
		boxNameUnInstall, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		MessageBox(0, "D2gfx.dll isn't patched.\n",
			boxNameUnInstall, MB_OK | MB_ICONASTERISK);
		exit(0);
	}

	FILE *dll;

	if (fopen_s(&dll, "d2gfx.dll", "rb+"))
	{
		MessageBox(0, "Can't open D2gfx.dll in read/write mode.\n"
			"If Diablo II is running you can\'t install PlugY, The Survival Kit.\n"
			"Quit Diablo II and try again.",
			boxNameUnInstall, MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}

	int version = GetD2Version("Game.exe");

	if (version < V109 || version > V113d)
	{
		MessageBox(0, "Bad version of D2gfx.dll.\n"
			"You can try to uninstall any previous version of PlugY, The Survival Kit then retry.\n"
			"Or re-install a clean version (between 1.09 and 1.13d) of LOD.",
			boxNameUnInstall, MB_OK | MB_ICONEXCLAMATION);
		exit(0);
	}

	updateData(version);

	bool error = false;
	int ident = 0;
	BYTE buffer[100];
	BYTE zeros[100];
	memset(zeros, 0, sizeof(zeros));

	version -= V109b;

	fseek(dll, CALL_LOAD[version], SEEK_SET);
	fread(buffer, 6, 1, dll);
	if (memcmp(buffer, callNewLoad[version], 6) != 0) error = true;
	if (memcmp(buffer, callOldLoad[version], 6) == 0) ident++;

	fseek(dll, CALL_FREE[version], SEEK_SET);
	fread(buffer, 6, 1, dll);
	if (memcmp(buffer, callNewFree[version], 6) != 0) error = true;
	if (memcmp(buffer, callOldFree[version], 6) == 0) ident++;

	fseek(dll, CALLER_LOADPLUGY, SEEK_SET);
	fread(buffer, sizeof(caller_LoadPlugY), 1, dll);
	if (memcmp(buffer, caller_LoadPlugY, sizeof(caller_LoadPlugY)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(caller_LoadPlugY)) == 0) ident++;

	fseek(dll, CALLER_FREEPLUGY, SEEK_SET);
	fread(buffer, sizeof(caller_FreePlugY), 1, dll);
	if (memcmp(buffer, caller_FreePlugY, sizeof(caller_FreePlugY)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(caller_FreePlugY)) == 0) ident++;

	fseek(dll, S_INIT, SEEK_SET);
	fread(buffer, sizeof(sInit), 1, dll);
	if (memcmp(buffer, sInit, sizeof(sInit)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(sInit)) == 0) ident++;

	fseek(dll, S_RELEASE, SEEK_SET);
	fread(buffer, sizeof(sRelease), 1, dll);
	if (memcmp(buffer, sRelease, sizeof(sRelease)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(sRelease)) == 0) ident++;

	fseek(dll, S_DLLNAME, SEEK_SET);
	fread(buffer, sizeof(sDllName), 1, dll);
	if (memcmp(buffer, sDllName, sizeof(sDllName)) != 0) error = true;
	if (memcmp(buffer, zeros, sizeof(sDllName)) == 0) ident++;

	if (error)
	{
		if (ident == 7)
		{
			MessageBox(0, "PlugY, The Survival Kit already uninstalled.",
				boxNameUnInstall, MB_OK | MB_ICONASTERISK);
			exit(0);
		} 
		else
		{
			MessageBox(0, "Bad version of D2gfx.dll.\n"
				"Unable to uninstall PlugY, The Survival Kit.",
				boxNameUnInstall, MB_OK | MB_ICONEXCLAMATION);
			exit(0);
		}
	}

	fseek(dll, CALL_LOAD[version], SEEK_SET);
	fwrite(callOldLoad[version], 6, 1, dll);

	fseek(dll, CALL_FREE[version], SEEK_SET);
	fwrite(callOldFree[version], 6, 1, dll);

	fseek(dll, CALLER_LOADPLUGY, SEEK_SET);
	fwrite(zeros, sizeof(caller_LoadPlugY), 1, dll);

	fseek(dll, CALLER_FREEPLUGY, SEEK_SET);
	fwrite(zeros, sizeof(caller_FreePlugY), 1, dll);

	fseek(dll, S_INIT, SEEK_SET);
	fwrite(zeros, sizeof(sInit), 1, dll);

	fseek(dll, S_RELEASE, SEEK_SET);
	fwrite(zeros, sizeof(sRelease), 1, dll);

	fseek(dll, S_DLLNAME, SEEK_SET);
	fwrite(zeros, sizeof(sDllName), 1, dll);

	fclose(dll);

	MessageBox(0, "D2gfx.dll patched successfully.\n"
		"PlugY, The Survival Kit uninstalled successfully.",
		boxNameUnInstall, MB_OK | MB_ICONASTERISK);
	exit(0);
}

int main(int argc, char * argv[])
{
	//	if ((argc>1) && !strcmp(argv[1],"-u"))
#ifdef RESTORE
	Unpatch();
#else
	if ((argc>1) && !strcmp(argv[1], "-u"))
		Unpatch();
	else
		Patch();
#endif

    return 1;
}
