/*
	File created by Yohann NICOLAS.
*/
#include <windows.h>
#include <stdio.h>
#include <Psapi.h>
//#using <mscorlib.dll>
//#using <System.dll>
//using namespace EnvDTE;
//using namespace System;
//using namespace System::Diagnostics;
//using namespace System::ComponentModel;
//using namespace System.Diagnostics;
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
$ ==>    >44 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  D...............
$+10     >1A 13 03 00 08 00 00 00 14 13 04 00 00 00 00 00  .........
$+20     >01 00 00 00 0C C7 12 00 34 87 D1 77 81 00 00 00  ....Ç.4‡Ñw...
$+30     >0A 00 00 00 00 00 00 00 00 00 00 00 89 F6 D4 77  ............‰öÔw
$+40     >CD AB BA DC 00 00 00 00                          Í«ºÜ....

//0xE9,0x1C,0xD1,0xA8,0x6F
*/

#define SUBKEY "Software\\Blizzard Entertainment\\Diablo II"
#define GAMEFILE "\\Game.exe "
#define INIFILE "\\PlugY.ini"
#define LAUNCHING "LAUNCHING"
#define LOD_VERSION "LodVersionFolder"
#define PARAM "Param"
#define LIBRARY_NAME "Library"

BYTE loadDll[]={
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
0x00,0x00,0x00,0x00};			//HANDLE var;


BYTE freeDll[]={
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
0xC2,0x04,0x00};				//RETN 4


//LPCSTR dllName = "PlugY.dll";
LPCSTR initFctName = "_Init@4";
LPCSTR releaseFctName = "_Release@0";
static bool versionXP;

typedef int (__stdcall* tDebugActiveProcessStop)(DWORD);
tDebugActiveProcessStop debugActiveProcessStop;


void assertion(LPCSTR msg)
{
	MessageBox(0, msg, "PlugYRun", MB_OK|MB_ICONASTERISK);
	exit(1);
}

bool installPlugY(HANDLE h, DWORD addr, char* libraryName, int isAdd)
{
	BYTE buf[200];
	DWORD pos=0;
	SIZE_T nb=0;
	DWORD version;
	int res;

	// Get Version and needed addresses.
	res = ReadProcessMemory(h,(LPVOID)(addr+0x110),&version,4,&nb);//0x80
	if (!res || (nb!=4)) assertion("Read to get current d2gfx version in memory failed");
	
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
	res = ReadProcessMemory(h,(LPVOID)loadCallerAddr,buf,6,&nb);
	if (!res || nb<6 ) assertion("Read memory failed for checking.");
	if (buf[0]!=0xFF || buf[1]!=0x15 || *(DWORD*)(buf+2) != loadLibraryAddr)
		if (buf[0]!=0xE8 /*|| buf[1]!=0xD8 || buf[2]!=0x19*/ || buf[3]!=0x00 || buf[4]!=0x00 || buf[5]!=0x90)
			assertion("Checking library memory check failed.");
		else
			alreadyInstalled = true;
	res = ReadProcessMemory(h,(LPVOID)freeCallerAddr,buf,6,&nb);
	if (!res || nb<6 ) assertion("Read memory failed for checking.");
	if (buf[0]!=0xFF || buf[1]!=0x15 || *(DWORD*)(buf+2) != freeLibraryAddr)
		if (buf[0]!=0xE8 /*|| buf[1]!=0x75 || buf[2]!=0x1A*/ || buf[3]!=0x00 || buf[4]!=0x00 || buf[5]!=0x90)
			if (!alreadyInstalled)
				assertion("Checking library memory failed.");

	if (alreadyInstalled)
		return true;

	//Alloc custom memory data.
	DWORD memory = (DWORD)VirtualAllocEx(h,NULL,200,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
	DWORD oldProtect=-1;
	if (!memory)
	{
//		MessageBox(0, "no memory", "RunPlugY.\n", MB_OK|MB_ICONASTERISK);
		memory = addr + 0xBE00 + isAdd*0x1000;
		if( !VirtualProtectEx(h,(LPVOID)memory, 200, PAGE_EXECUTE_READWRITE, &oldProtect) )
			assertion("Failed to get memory pool for PlugY loading.");
	}

	//Make memory data
	int len;
	pos=0;

	//Dll name
	DWORD dllNameAddr = memory+pos;
	len = strlen(libraryName)+1;
	res = WriteProcessMemory(h,(LPVOID)dllNameAddr,libraryName,len,&nb);
	if (!res || (nb!=len)) assertion("Write custom data in memory failed");
	pos += pos%16 ? len + 16 - pos%16 : len;

	//init name
	DWORD initNameAddr = memory+pos;
	len = strlen(initFctName)+1;
	res = WriteProcessMemory(h,(LPVOID)initNameAddr,initFctName,len,&nb);
	if (!res || (nb!=len)) assertion("Write custom data in memory failed");
	pos += pos%16 ? len + 16 - pos%16 : len;

	//release name
	DWORD releaseNameAddr = memory+pos;
	len = strlen(releaseFctName)+1;
	res = WriteProcessMemory(h,(LPVOID)releaseNameAddr,releaseFctName,len,&nb);
	if (!res || (nb!=len)) assertion("Write custom data in memory failed");
	pos += pos%16 ? len + 16 - pos%16 : len;

	//load fct
	DWORD loadDllAddr = memory+pos;
	DWORD handleAddr = loadDllAddr + sizeof(loadDll) - 4;
	*(DWORD*)&loadDll[6]  = loadLibraryAddr;
	*(DWORD*)&loadDll[12] = dllNameAddr;
	*(DWORD*)&loadDll[18] = loadLibraryAddr;
	*(DWORD*)&loadDll[23] = handleAddr;
	*(DWORD*)&loadDll[33] = initNameAddr;
	*(DWORD*)&loadDll[40] = getProcAddressAddr;
	*(DWORD*)&loadDll[63] = getProcAddressAddr;
	*(DWORD*)&loadDll[80] = dllNameAddr;
	len = sizeof(loadDll);
	res = WriteProcessMemory(h,(LPVOID)loadDllAddr,loadDll,len,&nb);
	if (!res || (nb!=len)) assertion("Write custom data in memory failed");
	pos += pos%16 ? len + 16 - pos%16 : len;

	//free fct
	DWORD freeDllAddr = memory+pos;
	*(DWORD*)&freeDll[6]  = freeLibraryAddr;
	*(DWORD*)&freeDll[12] = handleAddr;
	*(DWORD*)&freeDll[22] = releaseNameAddr;
//	*(DWORD*)&freeDll[30] = handleAddr;
	*(DWORD*)&freeDll[36-7] = getProcAddressAddr;
	*(DWORD*)&freeDll[55-7] = getProcAddressAddr;
	*(DWORD*)&freeDll[67-7] = freeLibraryAddr;
	len = sizeof(freeDll);
	res = WriteProcessMemory(h,(LPVOID)freeDllAddr,freeDll,len,&nb);
	if (!res || (nb!=len)) assertion("Write custom data in memory failed");
	pos += pos%16 ? len + 16 - pos%16 : len;


	//Patch load library
	buf[0]=0x90;
	buf[1]=0xE8;
	*(DWORD*)(buf+2) = (DWORD)loadDllAddr - (DWORD)loadCallerAddr-6;
	len = 6;
	res = WriteProcessMemory(h,(LPVOID)loadCallerAddr,buf,len,&nb);
	if (!res || (nb!=len)) assertion("Write load library in memory failed");

	//Patch free library
	*(DWORD*)(buf+2) = (DWORD)freeDllAddr - (DWORD)freeCallerAddr-6;
	res = WriteProcessMemory(h,(LPVOID)freeCallerAddr,buf,len,&nb);
	if (!res || (nb!=len)) assertion("Write free library in memory failed");

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
	ReadProcessMemory(hProcess,dllAdr,buf,BUF_SIZE, &nbRead);
	if (nbRead < 0x40) return false;
	int offsetPESignature = *(DWORD*)(buf+0x3C);
	if (offsetPESignature+38 >= BUF_SIZE) return false;
	DWORD baseOfCode = *(DWORD*)(buf+offsetPESignature + 0x34);
	if ( ( baseOfCode != 0x6FA80000) && (baseOfCode != 0x6FA70000)) return false;

	return true;
}

bool getWinReg(char* buf, DWORD bufsize)
{
	HKEY hKey;
	DWORD type;
	int res;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		res = RegQueryValueEx(hKey,"InstallPath",NULL,&type,(LPBYTE)buf,&bufsize);
		RegCloseKey(hKey);
		if (res!=ERROR_SUCCESS) return false;
	} else if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, SUBKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		res = RegQueryValueEx(hKey,"InstallPath",NULL,&type,(LPBYTE)buf,&bufsize);
		RegCloseKey(hKey);
		if (res!=ERROR_SUCCESS) return false;
	} else {
		return false;
	}
	strcat(buf, GAMEFILE);
	if (GetFileAttributes(buf) == INVALID_FILE_ATTRIBUTES)
		return false;
	return true;
}

bool launchNormal(char* command, char* currentDirectory)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	BOOL success = CreateProcess(0, command, 0, 0, false, 0, 0, currentDirectory, &si, &pi);//DEBUG_ONLY_THIS_PROCESS
	return success?true:false;
}

bool launchGame98(char* command, char* currentDirectory, char* libraryName)
{
//	MessageBox(0, "LAUNCH 98", "PlugYRun", MB_OK|MB_ICONASTERISK);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	BOOL success = CreateProcess(0, command, 0, 0, false, 0, 0, currentDirectory, &si, &pi);//DEBUG_ONLY_THIS_PROCESS
	if (!success) return false;
	DWORD ret;
//	MessageBox(0, "LAUNCH 98 while", "PlugYRun", MB_OK|MB_ICONASTERISK);
	Sleep(10);
	while (true)
	{
		SuspendThread(pi.hThread);// == (DWORD)-1)
			//MessageBox(0, "Thread not suspended", "PlugYRun", MB_OK|MB_ICONASTERISK);

		if (!GetExitCodeProcess(pi.hProcess,&ret) || (ret != STILL_ACTIVE))
			exit(0);
		if (isD2gfx(pi.hProcess,(LPVOID)0x6FA80000))
		{
//			MessageBox(0, "INSTALL 98", "PlugYRun", MB_OK|MB_ICONASTERISK);
			installPlugY(pi.hProcess, 0x6FA80000, libraryName, 1);
			ResumeThread(pi.hThread);
			return true;
		}
		if (isD2gfx(pi.hProcess,(LPVOID)0x6FA70000))
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


bool launchGameXP(char* command, char* currentDirectory, char* libraryName)
{
//	MessageBox(0, "LAUNCH XP", "PlugYRun", MB_OK|MB_ICONASTERISK);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	BOOL success = CreateProcess(0, command, 0, 0, false, DEBUG_PROCESS, 0, currentDirectory, &si, &pi);//DEBUG_ONLY_THIS_PROCESS
	if (!success) return false;
	DEBUG_EVENT DebugEvent;
	DWORD status;
//	MessageBox(0, "START WAITING", "PlugYRun", MB_OK|MB_ICONASTERISK);
	while (WaitForDebugEvent(&DebugEvent,INFINITE))
	{
		status = DBG_CONTINUE;
		switch(DebugEvent.dwDebugEventCode)
		{
		case CREATE_THREAD_DEBUG_EVENT:
			CloseHandle(DebugEvent.u.CreateThread.hThread);
			break;
		case CREATE_PROCESS_DEBUG_EVENT:
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
//			MessageBox(0, "EXIT", "PlugY", MB_OK|MB_ICONASTERISK);
			exit(0);
		case EXCEPTION_DEBUG_EVENT:
			if (DebugEvent.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
				MessageBox(0, "EXCEPTION_ACCESS_VIOLATION", "PlugY", MB_OK|MB_ICONASTERISK);
//			status = DBG_EXCEPTION_NOT_HANDLED;
			break;
		case LOAD_DLL_DEBUG_EVENT:
//			if (!GetModuleBaseName(pi.hProcess,(HMODULE)DebugEvent.u.LoadDll.lpBaseOfDll,buf,100))
//				MessageBox(0, "ERROR", "PlugYRun", MB_OK|MB_ICONASTERISK);
//			sprintf(buf,"%08X : %d",DebugEvent.u.LoadDll.lpBaseOfDll,GetLastError());
//			MessageBox(0, buf, "PlugYRun", MB_OK|MB_ICONASTERISK);
//			if (!strcmp(buf,"d2gfx.dll"))
//			if ((LPVOID)GetModuleHandle("D2gfx.dll") == DebugEvent.u.LoadDll.lpBaseOfDll)//pi.hProcess,,buf,bufSize);
			if(isD2gfx(pi.hProcess, DebugEvent.u.LoadDll.lpBaseOfDll))
			{
//				MessageBox(0, "INSTALL XP", "PlugYRun", MB_OK|MB_ICONASTERISK);
				installPlugY(pi.hProcess, (DWORD)DebugEvent.u.LoadDll.lpBaseOfDll, libraryName, (DWORD)DebugEvent.u.LoadDll.lpBaseOfDll == 0x6FA8000);
				CloseHandle(DebugEvent.u.LoadDll.hFile);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				debugActiveProcessStop(DebugEvent.dwProcessId);
//				MessageBox(0, "INSTALL XP end", "PlugYRun", MB_OK|MB_ICONASTERISK);
				return true;
			} else 
				CloseHandle(DebugEvent.u.LoadDll.hFile);
			break;
		}
		ContinueDebugEvent(DebugEvent.dwProcessId,DebugEvent.dwThreadId,status);
	}
	MessageBox(0, "ERROR : PlugY isn't installed", "PlugYRun", MB_OK|MB_ICONASTERISK);
	return true;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char currrentDirectory[MAX_PATH];
	char iniFileName[MAX_PATH];
	char command[MAX_PATH+50];

//	MessageBox(NULL,"START","PlugYRun",MB_OK);
	//Get Current Directory.
	if (!GetCurrentDirectory(MAX_PATH-1,currrentDirectory))
		assertion("Current directory not found");

	int len = strlen(currrentDirectory);
	if (len && currrentDirectory[len-1] != '\\')
	{
		currrentDirectory[len+1]=NULL;
		currrentDirectory[len]='\\';
	}

	//Get ini full path name.
	strcpy(iniFileName,currrentDirectory);
	strcat(iniFileName,INIFILE);

	//Get current directory.
	strcpy(command,currrentDirectory);
	strcat(command,GAMEFILE);
	if (GetFileAttributes(command) == INVALID_FILE_ATTRIBUTES)
		if (!getWinReg(command, MAX_PATH+50))
			 return 1;

	//Add params.
	strcat(command,lpCmdLine);
	len = strlen(command);
	GetPrivateProfileString(LAUNCHING,PARAM,"",&command[len],MAX_PATH-len,iniFileName);

	//copyLodVersionFiles();

	char libraryName[50];
	if (!GetPrivateProfileString(LAUNCHING,LIBRARY_NAME,"",libraryName,50,iniFileName) || !libraryName[0])
		return !launchNormal(command, currrentDirectory);

//	MessageBox(NULL,command,"PlugYRun",MB_OK);
	HMODULE module = GetModuleHandle("Kernel32.dll");
	if (module)
	{
		debugActiveProcessStop = (tDebugActiveProcessStop) GetProcAddress(module,"DebugActiveProcessStop");
		if (debugActiveProcessStop)
			return !launchGameXP(command, currrentDirectory, libraryName);
	}
	return !launchGame98(command, currrentDirectory, libraryName);
}


/*	else if (GetVersion() & 0x80000000)
	{
		versionXP=false;
	} else {
		versionXP=true;
	}*/
//HINSTANCE
//	CreateProcessInternalA
//	HMODULE HPlugY = LoadLibrary("C:\\Jeux\\Diablo II\\PlugY.dll");
//	if (!HPlugY) return 0;
//	DuplicateHandle
//		GetCurrentProcess();
/*	typedef void* (__stdcall* Tinit)(LPSTR IniName);
	Tinit init = (Tinit)GetProcAddress(HPlugY,"_Init@4");
	if (!init) return 0;
	init(0);*/
/*
6FC2BD50  /$ 81EC 08010000  SUB ESP,108
6FC2BD56  |. 53             PUSH EBX
6FC2BD57  |. 8A9C24 1801000>MOV BL,BYTE PTR SS:[ESP+118]
6FC2BD5E  |. F6C3 10        TEST BL,10
6FC2BD61  |. 55             PUSH EBP
6FC2BD62  |. 56             PUSH ESI
6FC2BD63  |. C707 00000000  MOV DWORD PTR DS:[EDI],0
6FC2BD69  |. C74424 0C 0000>MOV DWORD PTR SS:[ESP+C],0
6FC2BD71  |. BE F3030000    MOV ESI,3F3
6FC2BD76  |. C64424 10 00   MOV BYTE PTR SS:[ESP+10],0
6FC2BD7B  |. 75 25          JNZ SHORT storm.6FC2BDA2
6FC2BD7D  |. F6C3 02        TEST BL,2
6FC2BD80  |. 68 04010000    PUSH 104
6FC2BD85  |. 74 0C          JE SHORT storm.6FC2BD93
6FC2BD87  |. 68 146AC36F    PUSH storm.6FC36A14                      ;  ASCII "Software\Battle.net\"
6FC2BD8C  |. 8D4424 18      LEA EAX,DWORD PTR SS:[ESP+18]
6FC2BD90  |. 50             PUSH EAX
6FC2BD91  |. EB 0A          JMP SHORT storm.6FC2BD9D
6FC2BD93  |> 68 F069C36F    PUSH storm.6FC369F0                      ;  ASCII "Software\Blizzard Entertainment\"
6FC2BD98  |. 8D4C24 18      LEA ECX,DWORD PTR SS:[ESP+18]
6FC2BD9C  |. 51             PUSH ECX
6FC2BD9D  |> E8 EE07FEFF    CALL storm.#501
6FC2BDA2  |> 8B9424 1801000>MOV EDX,DWORD PTR SS:[ESP+118]
6FC2BDA9  |. 68 04010000    PUSH 104
6FC2BDAE  |. 52             PUSH EDX
6FC2BDAF  |. 8D4424 18      LEA EAX,DWORD PTR SS:[ESP+18]
6FC2BDB3  |. 50             PUSH EAX
6FC2BDB4  |. E8 6705FEFF    CALL storm.#503
6FC2BDB9  |. F6C3 04        TEST BL,4
6FC2BDBC  |. 8B2D 1030C36F  MOV EBP,DWORD PTR DS:[<&ADVAPI32.RegQuer>;  advapi32.RegQueryValueExA
6FC2BDC2  |. 75 5D          JNZ SHORT storm.6FC2BE21
6FC2BDC4  |. 8D4C24 0C      LEA ECX,DWORD PTR SS:[ESP+C]
6FC2BDC8  |. 51             PUSH ECX                                 ; /pHandle
6FC2BDC9  |. 68 19000200    PUSH 20019                               ; |Access = KEY_READ
6FC2BDCE  |. 6A 00          PUSH 0                                   ; |Reserved = 0
6FC2BDD0  |. 8D5424 1C      LEA EDX,DWORD PTR SS:[ESP+1C]            ; |
6FC2BDD4  |. 52             PUSH EDX                                 ; |Subkey
6FC2BDD5  |. 68 01000080    PUSH 80000001                            ; |hKey = HKEY_CURRENT_USER
6FC2BDDA  |. FF15 0830C36F  CALL DWORD PTR DS:[<&ADVAPI32.RegOpenKey>; \RegOpenKeyExA
002281A4   80000001  |hKey = HKEY_CURRENT_USER
002281A8   002281C8  |Subkey = "Software\Blizzard Entertainment\Diablo II"
002281AC   00000000  |Reserved = 0
002281B0   00020019  |Access = KEY_READ
002281B4   002281C4  \pHandle = 002281C4


6FC2BDE0  |. 8BF0           MOV ESI,EAX
6FC2BDE2  |. 85F6           TEST ESI,ESI
6FC2BDE4  |. 75 3B          JNZ SHORT storm.6FC2BE21
6FC2BDE6  |. 8B8C24 2801000>MOV ECX,DWORD PTR SS:[ESP+128]
6FC2BDED  |. 8B9424 2401000>MOV EDX,DWORD PTR SS:[ESP+124]
6FC2BDF4  |. 8B8424 2C01000>MOV EAX,DWORD PTR SS:[ESP+12C]
6FC2BDFB  |. 57             PUSH EDI                                 ; /pBufSize
6FC2BDFC  |. 51             PUSH ECX                                 ; |Buffer
6FC2BDFD  |. 8B4C24 14      MOV ECX,DWORD PTR SS:[ESP+14]            ; |
6FC2BE01  |. 52             PUSH EDX                                 ; |pValueType
6FC2BE02  |. 8907           MOV DWORD PTR DS:[EDI],EAX               ; |
6FC2BE04  |. 8B8424 2801000>MOV EAX,DWORD PTR SS:[ESP+128]           ; |
6FC2BE0B  |. 56             PUSH ESI                                 ; |Reserved
6FC2BE0C  |. 50             PUSH EAX                                 ; |ValueName
6FC2BE0D  |. 51             PUSH ECX                                 ; |hKey
6FC2BE0E  |. FFD5           CALL EBP                                 ; \RegQueryValueExA
002281A0   00000124  |hKey = 124
002281A4   6FF77B88  |ValueName = "InstallPath"
002281A8   00000000  |Reserved = NULL
002281AC   002282FC  |pValueType = 002282FC
002281B0   00228320  |Buffer = 00228320
002281B4   00228300  \pBufSize = 00228300


6FC2BE10  |. 8B5424 0C      MOV EDX,DWORD PTR SS:[ESP+C]
6FC2BE14  |. 52             PUSH EDX                                 ; /hKey
6FC2BE15  |. 8BF0           MOV ESI,EAX                              ; |
6FC2BE17  |. FF15 1830C36F  CALL DWORD PTR DS:[<&ADVAPI32.RegCloseKe>; \RegCloseKey
002281B4   00000124  \hKey = 00000124 (window)

6FC2BE1D  |. 85F6           TEST ESI,ESI
6FC2BE1F  |. 74 62          JE SHORT storm.6FC2BE83
6FC2BE21  |> F6C3 01        TEST BL,1
6FC2BE24  |. 75 59          JNZ SHORT storm.6FC2BE7F
6FC2BE26  |. 8D4424 0C      LEA EAX,DWORD PTR SS:[ESP+C]
6FC2BE2A  |. 50             PUSH EAX                                 ; /pHandle
6FC2BE2B  |. 68 19000200    PUSH 20019                               ; |Access = KEY_READ
6FC2BE30  |. 6A 00          PUSH 0                                   ; |Reserved = 0
6FC2BE32  |. 8D4C24 1C      LEA ECX,DWORD PTR SS:[ESP+1C]            ; |
6FC2BE36  |. 51             PUSH ECX                                 ; |Subkey
6FC2BE37  |. 68 02000080    PUSH 80000002                            ; |hKey = HKEY_LOCAL_MACHINE
6FC2BE3C  |. FF15 0830C36F  CALL DWORD PTR DS:[<&ADVAPI32.RegOpenKey>; \RegOpenKeyExA
6FC2BE42  |. 8BF0           MOV ESI,EAX
6FC2BE44  |. 85F6           TEST ESI,ESI
6FC2BE46  |. 75 4C          JNZ SHORT storm.6FC2BE94
6FC2BE48  |. 8B8424 2801000>MOV EAX,DWORD PTR SS:[ESP+128]
6FC2BE4F  |. 8B8C24 2401000>MOV ECX,DWORD PTR SS:[ESP+124]
6FC2BE56  |. 8B9424 2C01000>MOV EDX,DWORD PTR SS:[ESP+12C]
6FC2BE5D  |. 57             PUSH EDI
6FC2BE5E  |. 50             PUSH EAX
6FC2BE5F  |. 8B4424 14      MOV EAX,DWORD PTR SS:[ESP+14]
6FC2BE63  |. 51             PUSH ECX
6FC2BE64  |. 8917           MOV DWORD PTR DS:[EDI],EDX
6FC2BE66  |. 8B9424 2801000>MOV EDX,DWORD PTR SS:[ESP+128]
6FC2BE6D  |. 56             PUSH ESI
6FC2BE6E  |. 52             PUSH EDX
6FC2BE6F  |. 50             PUSH EAX
6FC2BE70  |. FFD5           CALL EBP
6FC2BE72  |. 8B4C24 0C      MOV ECX,DWORD PTR SS:[ESP+C]
6FC2BE76  |. 51             PUSH ECX                                 ; /hKey
6FC2BE77  |. 8BF0           MOV ESI,EAX                              ; |
6FC2BE79  |. FF15 1830C36F  CALL DWORD PTR DS:[<&ADVAPI32.RegCloseKe>; \RegCloseKey
6FC2BE7F  |> 85F6           TEST ESI,ESI
6FC2BE81  |. 75 11          JNZ SHORT storm.6FC2BE94
6FC2BE83  |> 5E             POP ESI
6FC2BE84  |. 5D             POP EBP
6FC2BE85  |. B8 01000000    MOV EAX,1
6FC2BE8A  |. 5B             POP EBX
6FC2BE8B  |. 81C4 08010000  ADD ESP,108
6FC2BE91  |. C2 1800        RETN 18
6FC2BE94  |> 56             PUSH ESI                                 ; /Error
6FC2BE95  |. FF15 2832C36F  CALL DWORD PTR DS:[<&KERNEL32.SetLastErr>; \SetLastError
6FC2BE9B  |. 5E             POP ESI
6FC2BE9C  |. 5D             POP EBP
6FC2BE9D  |. 33C0           XOR EAX,EAX
6FC2BE9F  |. 5B             POP EBX
6FC2BEA0  |. 81C4 08010000  ADD ESP,108
6FC2BEA6  \. C2 1800        RETN 18
*/

///////////////////////// END OF FILE ///////////////////////