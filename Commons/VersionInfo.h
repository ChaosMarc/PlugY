#include <windows.h>

union TFileVersion
{
	__int64 full;
	struct {
		WORD subrevision;
		WORD revision;
		WORD minor;
		WORD major;
	};
	WORD w[4];
};

enum eGameVersion
{
	v109b=0,
	v109d,
	v110,
	v111,
	v111b,
	v112,
	v113c,
	v113d,
	v114a
};

bool GetAppVersion(char* FileName, TFileVersion* VerInfo); // получение версии файла
bool GetD2Path(char* buf, DWORD bufsize);
int GetD2Version(char* PathGameExe);