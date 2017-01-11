/*
File created by Yohann NICOLAS.
*/
#include "stdafx.h"
#include "PlugYRun.h"
/*
0012C458   00000000  |ModuleFileName = NULL
0012C45C   0012C908  |CommandLine = ""C:\Jeux\Diablo II\Game.exe""
0012C460   00000000  |pProcessSecurity = NULL
0012C464   00000000  |pThreadSecurity = NULL
0012C468   00000000  |InheritHandles = FALSE
0012C46C   04000022  |CreationFlags = DEBUG_ONLY_THIS_PROCESS|NORMAL_PRIORITY_CLASS|CREATE_DEFAULT_ERROR_MODE
0012C470   00000000  |pEnvironment = NULL
0012C474   0012DF94  |CurrentDir = "C:\Jeux\Diablo II\"
0012C478   0012C6BC  |pStartupInfo = 0012C6BC
0012C47C   0012C5CC  \pProcessInfo = 0012C5CC
$ ==>    >44 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
$+10     >1A 13 03 00 08 00 00 00 14 13 04 00 00 00 00 00
$+20     >01 00 00 00 0C C7 12 00 34 87 D1 77 81 00 00 00
$+30     >0A 00 00 00 00 00 00 00 00 00 00 00 89 F6 D4 77
$+40     >CD AB BA DC 00 00 00 00                        

0xE9,0x1C,0xD1,0xA8,0x6F
*/

#define MAX_LOADSTRING 100
#define SUBKEY "Software\\Blizzard Entertainment\\Diablo II"
#define GAMEFILE "Game.exe "
#define INIFILE "PlugY.ini"
#define LAUNCHING "LAUNCHING"
#define LOD_VERSION "LodVersionFolder"
#define PARAM "Param"
#define WINDOWED "Windowed"
#define ACTIVE_WINDOWED "ActiveWindowed"
#define LIBRARY_NAME "Library"

BYTE loadDll[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0x50,							//PUSH EAX
	0x68,0x80,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE80                               ; ASCII "PlugY.dll"
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x2F,						//JE SHORT d2gfx.6FA7BE37
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
	0x59,							//POP ECX
	0xB9,0x80,0xBE,0xA7,0x6F,		//MOV ECX,d2gfx.6FA7BE80                            ;  ASCII "PlugY.dll"
	0x83,0x04,0x24,0x10,			//ADD DWORD PTR SS:[ESP],10
	0xC2,0x04,0x00,					//RETN 4
	0x00,0x00,0x00,0x00 };			//HANDLE var;


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


																	//LPCSTR dllName = "PlugY.dll";
LPCSTR initFctName = "_Init@4";
LPCSTR releaseFctName = "_Release@0";
static bool versionXP;

typedef int(__stdcall* tDebugActiveProcessStop)(DWORD);
tDebugActiveProcessStop debugActiveProcessStop;


void assertion(LPCSTR msg)
{
	MessageBox(0, msg, "PlugY", MB_OK | MB_ICONASTERISK);
	exit(1);
}

bool installPlugY(HANDLE h, DWORD addr, char* libraryName, int isAdd)
{
	BYTE buf[200];
	DWORD pos = 0;
	SIZE_T nb = 0;
	DWORD version;
	int res;

	// Get Version and needed addresses.
	res = ReadProcessMemory(h, (LPVOID)(addr + 0x110), &version, 4, &nb);//0x80
	if (!res || (nb != 4)) assertion("Read to get current d2gfx version in memory failed");

	DWORD loadCallerAddr = addr;
	DWORD freeCallerAddr = addr;
	DWORD loadLibraryAddr = addr;
	DWORD freeLibraryAddr = addr;
	DWORD getProcAddressAddr = addr;
	//	GET_VERSION(D2gfx,		110,	000054EB, 00001000, 0000C000, 42E6C22A, 43028B19);//110
	switch (version)
	{
	case 0x000054EB://1.09b 0x00949FA8:
	case 0x00001000://1.09d 0x018866A8:
		loadCallerAddr += 0x389B;
		freeCallerAddr += 0x3A8C;
		loadLibraryAddr += 0xC03C;
		freeLibraryAddr += 0xC044;
		getProcAddressAddr += 0xC038;
		break;
	case 0x0000C000://1.10 0x401526B2
		loadCallerAddr += 0x3870;
		freeCallerAddr += 0x3A6D;
		loadLibraryAddr += 0xC040;
		freeLibraryAddr += 0xC048;
		getProcAddressAddr += 0xC03C;
		break;
	case 0x42E6C22A://1.11 0x575C8A5E
		loadCallerAddr += 0x8B23;
		freeCallerAddr += 0x8ACA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case 0x43028B19://1.11b
		loadCallerAddr += 0xB423;
		freeCallerAddr += 0xB3CA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case 0x0A07010B://1.12a
		loadCallerAddr += 0x8F63;
		freeCallerAddr += 0x8F0A;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	case 0x00000000://1.13c
		loadCallerAddr += 0xB423;
		freeCallerAddr += 0xB3CA;
		loadLibraryAddr += 0xD11C;
		freeLibraryAddr += 0xD12C;
		getProcAddressAddr += 0xD120;
		break;
	default:
		assertion("Wrong version of the library D2gfx.dll");
	}

	//Verify if memory are ok.
	bool alreadyInstalled = false;
	res = ReadProcessMemory(h, (LPVOID)loadCallerAddr, buf, 6, &nb);
	if (!res || nb<6) assertion("Read memory failed for checking.");
	if (buf[0] != 0xFF || buf[1] != 0x15 || *(DWORD*)(buf + 2) != loadLibraryAddr)
		if (buf[0] != 0xE8 /*|| buf[1]!=0xD8 || buf[2]!=0x19*/ || buf[3] != 0x00 || buf[4] != 0x00 || buf[5] != 0x90)
			assertion("Checking library memory check failed.");
		else
			alreadyInstalled = true;
	res = ReadProcessMemory(h, (LPVOID)freeCallerAddr, buf, 6, &nb);
	if (!res || nb<6) assertion("Read memory failed for checking.");
	if (buf[0] != 0xFF || buf[1] != 0x15 || *(DWORD*)(buf + 2) != freeLibraryAddr)
		if (buf[0] != 0xE8 /*|| buf[1]!=0x75 || buf[2]!=0x1A*/ || buf[3] != 0x00 || buf[4] != 0x00 || buf[5] != 0x90)
			if (!alreadyInstalled)
				assertion("Checking library memory failed.");

	if (alreadyInstalled)
		return true;

	//Alloc custom memory data.
	DWORD memory = (DWORD)VirtualAllocEx(h, NULL, 200, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD oldProtect = -1;
	if (!memory)
	{
		//		MessageBox(0, "no memory", "RunPlugY.\n", MB_OK|MB_ICONASTERISK);
		memory = addr + 0xBE00 + isAdd * 0x1000;
		if (!VirtualProtectEx(h, (LPVOID)memory, 200, PAGE_EXECUTE_READWRITE, &oldProtect))
			assertion("Failed to get memory pool for PlugY loading.");
	}

	//Make memory data
	int len;
	pos = 0;

	//Dll name
	DWORD dllNameAddr = memory + pos;
	len = strlen(libraryName) + 1;
	res = WriteProcessMemory(h, (LPVOID)dllNameAddr, libraryName, len, &nb);
	if (!res || (nb != len)) assertion("Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	//init name
	DWORD initNameAddr = memory + pos;
	len = strlen(initFctName) + 1;
	res = WriteProcessMemory(h, (LPVOID)initNameAddr, initFctName, len, &nb);
	if (!res || (nb != len)) assertion("Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	//release name
	DWORD releaseNameAddr = memory + pos;
	len = strlen(releaseFctName) + 1;
	res = WriteProcessMemory(h, (LPVOID)releaseNameAddr, releaseFctName, len, &nb);
	if (!res || (nb != len)) assertion("Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	//load fct
	DWORD loadDllAddr = memory + pos;
	DWORD handleAddr = loadDllAddr + sizeof(loadDll) - 4;
	*(DWORD*)&loadDll[6] = loadLibraryAddr;
	*(DWORD*)&loadDll[12] = dllNameAddr;
	*(DWORD*)&loadDll[18] = loadLibraryAddr;
	*(DWORD*)&loadDll[23] = handleAddr;
	*(DWORD*)&loadDll[33] = initNameAddr;
	*(DWORD*)&loadDll[40] = getProcAddressAddr;
	*(DWORD*)&loadDll[63] = getProcAddressAddr;
	*(DWORD*)&loadDll[80] = dllNameAddr;
	len = sizeof(loadDll);
	res = WriteProcessMemory(h, (LPVOID)loadDllAddr, loadDll, len, &nb);
	if (!res || (nb != len)) assertion("Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	//free fct
	DWORD freeDllAddr = memory + pos;
	*(DWORD*)&freeDll[6] = freeLibraryAddr;
	*(DWORD*)&freeDll[12] = handleAddr;
	*(DWORD*)&freeDll[22] = releaseNameAddr;
	//	*(DWORD*)&freeDll[30] = handleAddr;
	*(DWORD*)&freeDll[36 - 7] = getProcAddressAddr;
	*(DWORD*)&freeDll[55 - 7] = getProcAddressAddr;
	*(DWORD*)&freeDll[67 - 7] = freeLibraryAddr;
	len = sizeof(freeDll);
	res = WriteProcessMemory(h, (LPVOID)freeDllAddr, freeDll, len, &nb);
	if (!res || (nb != len)) assertion("Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;


	//Patch load library
	buf[0] = 0x90;
	buf[1] = 0xE8;
	*(DWORD*)(buf + 2) = (DWORD)loadDllAddr - (DWORD)loadCallerAddr - 6;
	len = 6;
	res = WriteProcessMemory(h, (LPVOID)loadCallerAddr, buf, len, &nb);
	if (!res || (nb != len)) assertion("Write load library in memory failed");

	//Patch free library
	*(DWORD*)(buf + 2) = (DWORD)freeDllAddr - (DWORD)freeCallerAddr - 6;
	res = WriteProcessMemory(h, (LPVOID)freeCallerAddr, buf, len, &nb);
	if (!res || (nb != len)) assertion("Write free library in memory failed");

	//	sprintf(tmp,"mem = %08X (read = %d)",buf[0],nbRead);
	//	MessageBox(0, tmp, "RunPlugY.\n", MB_OK|MB_ICONASTERISK);
	//	if (oldProtect != -1)
	//		VirtualProtectEx(h,(LPVOID)memory, 200, oldProtect, &oldProtect);
	return true;
}




//###########################################################################################//


/*bool copyLodVersionFiles()
{
BYTE folder[MAX_PATH];
if (!GetPrivateProfileString(LAUNCHING,LOD_VERSION,"",folder,MAX_PATH,INI_FILE))
return true;
strcat(folder,"\\*");
WIN32_FIND_DATA FindFileData;
HANDLE hFind = FindFirstFile(folder,&FindFileData);
if (hFind==INVALID_HANDLE_VALUE)
return true;

do {
//		CopyFile();
} while (FindNextFile(hFind,&FindFileData);

FindClose(hFind);
return true;
}*/


#define BUF_SIZE 0x300
bool isD2gfx(HANDLE hProcess, LPVOID dllAdr)
{
	SIZE_T nbRead;
	BYTE buf[BUF_SIZE];
	ReadProcessMemory(hProcess, dllAdr, buf, BUF_SIZE, &nbRead);
	if (nbRead < 0x40) return false;
	int offsetPESignature = *(DWORD*)(buf + 0x3C);
	if (offsetPESignature + 38 >= BUF_SIZE) return false;
	DWORD baseOfCode = *(DWORD*)(buf + offsetPESignature + 0x34);
	if ((baseOfCode != 0x6FA80000) && (baseOfCode != 0x6FA70000)) return false;

	return true;
}

bool isGameLoaded(HANDLE hProcess, LPVOID baseAdr)
{
	SIZE_T nbRead;
	BYTE buf[BUF_SIZE];
	ReadProcessMemory(hProcess, baseAdr, buf, BUF_SIZE, &nbRead);
	if (nbRead < 0x40) return false;
	int offsetPESignature = *(DWORD*)(buf + 0x3C);
	if (offsetPESignature + 0x5C >= BUF_SIZE) return false;
	DWORD baseOfCode = *(DWORD*)(buf + offsetPESignature + 0x34);
	DWORD SizeOfImage = *(DWORD*)(buf + offsetPESignature + 0x50);
	DWORD CheckSum = *(DWORD*)(buf + offsetPESignature + 0x58);
	if ((baseOfCode==0x00400000) && (SizeOfImage == 0x005A5000) && (CheckSum == 0x00374101)) return true;//1.14c

	return false;
}

bool getWinReg(LPSTR buf, DWORD bufsize)
{
	HKEY hKey;
	DWORD type;
	int res;
	DWORD len = bufsize;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		res = RegQueryValueEx(hKey, "InstallPath", NULL, &type, (LPBYTE)buf, &len);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) return false;
	}
	else if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, SUBKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		res = RegQueryValueEx(hKey, "InstallPath", NULL, &type, (LPBYTE)buf, &len);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) return false;
	}
	else {
		return false;
	}
	if (len <= 1)
		return false;
	if (buf[len - 2] != '\\')
	{
		if (len >= bufsize)
			return false;
		buf[len - 1] = '\\';
		buf[len] = NULL;
	}
	return true;
}

bool launchNormal(LPSTR commandLine, LPSTR currentDirectory)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	BOOL success = CreateProcess(NULL, commandLine, NULL, NULL, false, 0, NULL, currentDirectory, &si, &pi);//DEBUG_ONLY_THIS_PROCESS
	return success ? true : false;
}

bool launchGame98(LPSTR commandLine, LPSTR currentDirectory, LPSTR libraryName)
{
	//	MessageBox(0, "LAUNCH 98", "PlugYRun", MB_OK|MB_ICONASTERISK);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	BOOL success = CreateProcess(0, commandLine, 0, 0, false, 0, 0, currentDirectory, &si, &pi);//DEBUG_ONLY_THIS_PROCESS
	if (!success) return false;
	DWORD ret;
	//	MessageBox(0, "LAUNCH 98 while", "PlugYRun", MB_OK|MB_ICONASTERISK);
	Sleep(10);
	while (true)
	{
		SuspendThread(pi.hThread);// == (DWORD)-1)
								  //MessageBox(0, "Thread not suspended", "PlugYRun", MB_OK|MB_ICONASTERISK);

		if (!GetExitCodeProcess(pi.hProcess, &ret) || (ret != STILL_ACTIVE))
			exit(0);
		if (isD2gfx(pi.hProcess, (LPVOID)0x6FA80000))
		{
			//			MessageBox(0, "INSTALL 98", "PlugYRun", MB_OK|MB_ICONASTERISK);
			installPlugY(pi.hProcess, 0x6FA80000, libraryName, 1);
			ResumeThread(pi.hThread);
			return true;
		}
		if (isD2gfx(pi.hProcess, (LPVOID)0x6FA70000))
		{
			//			MessageBox(0, "INSTALL 98", "PlugYRun", MB_OK|MB_ICONASTERISK);
			installPlugY(pi.hProcess, 0x6FA70000, libraryName, 0);
			ResumeThread(pi.hThread);
			return true;
		}
		ResumeThread(pi.hThread);
		//		Sleep(10);
	}
	return true;
}

bool launchGameXP(LPSTR commandLine, LPSTR currentDirectory, LPSTR libraryName)
{
	//	MessageBox(0, "LAUNCH XP", "PlugYRun", MB_OK|MB_ICONASTERISK);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	BOOL success = CreateProcess(0, commandLine, 0, 0, false, DEBUG_PROCESS, 0, currentDirectory, &si, &pi);//DEBUG_ONLY_THIS_PROCESS
	if (!success) return false;
	DEBUG_EVENT DebugEvent;
	DWORD status;
	while (WaitForDebugEvent(&DebugEvent, INFINITE))
	{
		status = DBG_CONTINUE;
		switch (DebugEvent.dwDebugEventCode)
		{
		case CREATE_THREAD_DEBUG_EVENT:
			CloseHandle(DebugEvent.u.CreateThread.hThread);
			break;
		case CREATE_PROCESS_DEBUG_EVENT:
			if (isGameLoaded(pi.hProcess, DebugEvent.u.CreateProcessInfo.lpBaseOfImage))
			{
				//installPlugYOnGame(pi.hProcess, (DWORD)DebugEvent.u.CreateProcessInfo.lpBaseOfImage, libraryName, (DWORD)DebugEvent.u.LoadDll.lpBaseOfDll == 0x6FA8000);
				CloseHandle(DebugEvent.u.CreateProcessInfo.hFile);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				debugActiveProcessStop(DebugEvent.dwProcessId);
				return true;
			}
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			exit(0);
		case EXCEPTION_DEBUG_EVENT:
			if (DebugEvent.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
				MessageBox(0, "EXCEPTION_ACCESS_VIOLATION", "PlugY", MB_OK | MB_ICONASTERISK);
			break;
		case LOAD_DLL_DEBUG_EVENT:
			if (isD2gfx(pi.hProcess, DebugEvent.u.LoadDll.lpBaseOfDll))
			{
				//				MessageBox(0, "INSTALL XP", "PlugYRun", MB_OK|MB_ICONASTERISK);
				installPlugY(pi.hProcess, (DWORD)DebugEvent.u.LoadDll.lpBaseOfDll, libraryName, (DWORD)DebugEvent.u.LoadDll.lpBaseOfDll == 0x6FA8000);
				CloseHandle(DebugEvent.u.LoadDll.hFile);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				debugActiveProcessStop(DebugEvent.dwProcessId);
				//				MessageBox(0, "INSTALL XP end", "PlugYRun", MB_OK|MB_ICONASTERISK);
				return true;
			}
			else
				CloseHandle(DebugEvent.u.LoadDll.hFile);
			break;
		}
		ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, status);
	}
	MessageBox(0, "ERROR : PlugY isn't installed", "PlugYRun", MB_OK | MB_ICONASTERISK);
	return true;
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	char currrentDirectory[MAX_PATH];
	char iniFileName[MAX_PATH];
	char command[MAX_PATH + 256];

	// Get Current Directory.
	if (!GetCurrentDirectory(sizeof(currrentDirectory), currrentDirectory))
		assertion("Current directory not found");

	int len = strlen(currrentDirectory);
	if (len == 0)
		assertion("Current directory not found");

	if (currrentDirectory[len - 1] != '\\')
	{
		if (len >= MAX_PATH - 1)
			assertion("Path length too long");
		currrentDirectory[len++] = '\\';
		currrentDirectory[len] = NULL;
	}

	// Get ini full path name.
	strcpy(iniFileName, currrentDirectory);
	if (len + strlen(INIFILE) >= sizeof(iniFileName))
		assertion("Path length too long");
	strcat(iniFileName, INIFILE);

	// Get game.exe path.
	strcpy(command, currrentDirectory);
	int cmdLen = len + strlen(GAMEFILE);
	if (cmdLen >= sizeof(command))
		assertion("Path length too long");
	strcat(command, GAMEFILE);

	if (GetFileAttributes(command) == INVALID_FILE_ATTRIBUTES)
	{
		if (!getWinReg(command, sizeof(command)))
			return 1;
		cmdLen = strlen(command) + strlen(GAMEFILE);
		if (cmdLen >= sizeof(command))
			assertion("Path length too long");
		strcat(command, GAMEFILE);
		if (GetFileAttributes(command) == INVALID_FILE_ATTRIBUTES)
			return false;
	}

	// Add params.
	int paramLen = strlen(lpCmdLine);
	if (paramLen > 0)
	{
		cmdLen += paramLen + 1;
		if (cmdLen > sizeof(command))
			assertion("Path length too long");
		strcat(command, lpCmdLine);
		strcat(command, " ");
	}
	int windowed = GetPrivateProfileInt(WINDOWED, ACTIVE_WINDOWED, 0, iniFileName);
	if (windowed)
	{
		cmdLen += paramLen + 3;
		if (cmdLen > sizeof(command))
			assertion("Path length too long");
		strcat(command, "-w ");
	}
	GetPrivateProfileString(LAUNCHING, PARAM, NULL, command + cmdLen, sizeof(command) - cmdLen, iniFileName);

	char libraryName[50];
	if (!GetPrivateProfileString(LAUNCHING, LIBRARY_NAME, "", libraryName, 50, iniFileName) || !libraryName[0])
		return !launchNormal(command, currrentDirectory);

	// Launch LoD and install PlugY
	HMODULE module = GetModuleHandle("Kernel32.dll");
	if (module)
	{
		debugActiveProcessStop = (tDebugActiveProcessStop)GetProcAddress(module, "DebugActiveProcessStop");
		if (debugActiveProcessStop)
			return !launchGameXP(command, currrentDirectory, libraryName);
	}
	return !launchGame98(command, currrentDirectory, libraryName);
}
