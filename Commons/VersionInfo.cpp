#include "VersionInfo.h"
#pragma comment(lib, "Version.Lib") //�� ��������� � Delphi 7 - ����� ��������! :(


bool IsFile(char* sPath)
{
        bool bFile = false;
        HANDLE hFile = CreateFile
                (
                        sPath, 
                        GENERIC_READ,
                        FILE_SHARE_READ,
                        NULL, 
                        OPEN_EXISTING, 
                        FILE_ATTRIBUTE_NORMAL,
                        NULL
                );
        if(hFile != INVALID_HANDLE_VALUE)
        {
                CloseHandle(hFile);
                bFile = true;
        }
        return bFile;
}

bool GetAppVersion(char* FileName, TFileVersion* VerInfo){ // ��������� ������ �����
   VerInfo->full = -1;
   if(!IsFile(FileName)){ // ��������� ������� �����
       return false; // ���� ��� �-��� ���������
   }
   DWORD FSize = GetFileVersionInfoSize(FileName,NULL); // ������ ���� � ������ �����
   if(FSize==0){ // ���� 0 ������� ���������
       return false;
   }
   LPVOID pBlock = (char*)malloc(FSize); // ����� ������ ��� �������� ������
   GetFileVersionInfo(FileName,NULL,FSize,pBlock); // �������� ������ ���������� � ������
   LPVOID MS;
   UINT LS;
   try{
       VerQueryValue(pBlock,"\\",&MS,&LS); // ��������� ���������� �� �������
   }
   catch(...){
       return false; // � ������ ������ ������� ���������
   }
   VS_FIXEDFILEINFO FixedFileInfo; // ��������� � ����������� � ������ �����
   memmove(&FixedFileInfo, MS, LS); // �������� ���������� � ���������

   DWORD FileVersionMS = FixedFileInfo.dwFileVersionMS;
   DWORD FileVersionLS = FixedFileInfo.dwFileVersionLS;

   VerInfo->major = HIWORD(FileVersionMS)	; // �������� ��������
   VerInfo->minor = LOWORD(FileVersionMS); // � ����������� �� �������� ���������
   VerInfo->revision = HIWORD(FileVersionLS);
   VerInfo->subrevision = LOWORD(FileVersionLS);

   return true; // ������� �������
}


#define SUBKEY "Software\\Blizzard Entertainment\\Diablo II"
#define GAMEFILE "\\Game.exe"
bool GetD2Path(char* buf, DWORD bufsize)
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
};

int GetVerD2(TFileVersion GameVer)
{
	if ((GameVer.major != 1)||(GameVer.minor != 0)) return -1;
	switch (GameVer.revision)
	{
	case 9:
		if (GameVer.subrevision == 20) return v109b;
		if (GameVer.subrevision == 22) return v109d;
		break;
	case 10:
		if (GameVer.subrevision == 39) return v110;
		break;
	case 11:
		if (GameVer.subrevision == 45) return v111;
		if (GameVer.subrevision == 46) return v111b;
		break;
	case 12:
		if (GameVer.subrevision == 49) return v112;
		break;
	case 13:
		if (GameVer.subrevision == 60) return v113c;
		if (GameVer.subrevision == 64) return v113d;
		break;
	}
	return -1;
}


int GetD2Version(char* PathGameExe)
{
	TFileVersion GameVer = {-1};
	if (! GetAppVersion(PathGameExe, &GameVer)) return -1;	
	int ver = GetVerD2(GameVer);
	return ver;
}