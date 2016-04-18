/******************************************************************************
	File modified by Yohann NICOLAS.

	NAME
		inifile.h

	DESCRIPTION
		Memory cached INI file read/write class to replace legacy MS code

	COPYRIGHT
		©1999-2004 Ultrafunk (www.ultrafunk.com) - info@ultrafunk.com

******************************************************************************/

#ifndef _INIFILE_H
#define _INIFILE_H

#include <windows.h>

#define INIFILE_READ		10
#define INIFILE_WRITE		20
#define INIFILE_MPQREAD		30

#define MAX_SECTIONNAME_LENGTH	128
#define MAX_KEYNAME_LENGTH		128

/*****************************************************************************/

class INIFile
{
public:
	INIFile();
	~INIFile();

	BOOL  InitReadWrite(char *path, int readWrite, DWORD writeCacheSize);
	BOOL  close();
	int	  GetPrivateProfileString(const char *section, const char *key, const char *def, char *dest, DWORD size);
	BOOL  WritePrivateProfileString(char *section, char *key, char *string);

private:
	int		m_readWrite;
	char	m_path[_MAX_PATH];
	HANDLE  m_file;
	char   *m_cache;
	DWORD	m_cacheWritePos;
	char   *m_sectionStart;
	char   *m_sectionEnd;
	char	m_currentSection[MAX_SECTIONNAME_LENGTH];
};


#endif // _INIFILE_H

/*================================= END OF FILE =================================*/