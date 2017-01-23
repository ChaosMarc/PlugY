/******************************************************************************
	File modified by Yohann NICOLAS.

	NAME
		inifile.h

	DESCRIPTION
		Memory cached INI file read/write class to replace legacy MS code

	COPYRIGHT
		©1999-2004 Ultrafunk (www.ultrafunk.com) - info@ultrafunk.com

******************************************************************************/
#pragma once

#include <windows.h>

#define INIFILE_READ		10
#define INIFILE_WRITE		20
#define INIFILE_MPQREAD		30

#define MAX_SECTIONNAME_LENGTH	128
#define MAX_KEYNAME_LENGTH		128

class INIFile
{
public:
	INIFile();
	~INIFile();

	BOOL InitReadWrite(const char *path, int readWrite, DWORD writeCacheSize);
	BOOL close();
	int GetPrivateProfileString(const char *section, const char *key, const char *def, char *dest, DWORD size);
	BOOL WritePrivateProfileString(char *section, char *key, char *string);

private:
	char	m_currentSection[MAX_SECTIONNAME_LENGTH];
	char   *m_cache;
	char   *m_sectionStart;
	char   *m_sectionEnd;
	int		m_readWrite;
	char	m_path[_MAX_PATH];
	HANDLE  m_file;
	DWORD	m_cacheWritePos;
};

class INIFileW
{
public:
	INIFileW();
	~INIFileW();

	BOOL InitReadWrite(const char *path, int readWrite, DWORD writeCacheSize);
	BOOL close();
	int GetPrivateProfileString(LPCWSTR section, LPCWSTR key, LPCWSTR def, LPWSTR dest, DWORD size);
	int GetPrivateProfileStringList(LPCWSTR section, LPCWSTR key, DWORD** codes, LPWSTR** values);
	//BOOL WritePrivateProfileString(char *section, char *key, char *string);
	LPWSTR m_cache;

private:
	WCHAR m_currentSection[MAX_SECTIONNAME_LENGTH];
	LPCWSTR m_sectionStart;
	LPCWSTR m_sectionEnd;
	int		m_readWrite;
	char	m_path[_MAX_PATH];
	HANDLE  m_file;
	DWORD	m_cacheWritePos;
};
/*================================= END OF FILE =================================*/