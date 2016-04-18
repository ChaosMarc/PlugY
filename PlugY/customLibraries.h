/*=================================================================
	File created by Yohann NICOLAS.

	Language management.

=================================================================*/

#pragma once

typedef int (STDCALL *TsaveSaveFile) (Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
typedef int (STDCALL *TloadSaveFile) (Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize);
typedef int (STDCALL *TinitSaveFile) (BYTE** data, DWORD* maxSize, DWORD* curSize);

class TCustomDll
{
public:
	union {
		HMODULE module;
		DWORD offset;
	};
	TCustomDll* nextDll;
	void initialize(DWORD offsetDll);
	void init();
	void release();
	void saveExtendedSaveFile (Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
	int loadExtendedSaveFile (Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize);
	int initExtendedSaveFile (BYTE** data, DWORD* maxSize, DWORD* curSize);
	void saveSharedSaveFile (Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
	int loadSharedSaveFile (Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize);
	int initSharedSaveFile (BYTE** data, DWORD* maxSize, DWORD* curSize);
//	__inline TCustomDll() {ZeroMemory(this,sizeof(this));}
private:
	FARPROC initFct;
	FARPROC releaseFct;
	TsaveSaveFile saveExtendedSaveFileFct;
	TloadSaveFile loadExtendedSaveFileFct;
	TinitSaveFile initExtendedSaveFileFct;
	TsaveSaveFile saveSharedSaveFileFct;
	TloadSaveFile loadSharedSaveFileFct;
	TinitSaveFile initSharedSaveFileFct;
};

extern TCustomDll* customDlls;


/*================================= END OF FILE =================================*/