/*=================================================================
	File created by Yohann NICOLAS.

	Language management.

=================================================================*/

#include "common.h"
#include "error.h"
#include "customLibraries.h"


TCustomDll* customDlls=NULL;

void TCustomDll::init()
{
	if (initFct)
		initFct();
};

void TCustomDll::release()
{
	if (releaseFct)
		releaseFct();
};

void TCustomDll::saveExtendedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (saveExtendedSaveFileFct)
		saveExtendedSaveFileFct(ptChar, data, maxSize, curSize);
};

int TCustomDll::loadExtendedSaveFile(Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize)
{
	if (loadExtendedSaveFileFct)
		return loadExtendedSaveFileFct(ptChar, data, maxSize, curSize);
	return 0;
};

int TCustomDll::initExtendedSaveFile(BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (initExtendedSaveFileFct)
		return initExtendedSaveFileFct(data, maxSize, curSize);
	return 0;
};

void TCustomDll::saveSharedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (saveSharedSaveFileFct)
		saveSharedSaveFileFct(ptChar, data, maxSize, curSize);
};

int TCustomDll::loadSharedSaveFile(Unit* ptChar, BYTE data[], DWORD maxSize, DWORD* curSize)
{
	if (loadSharedSaveFileFct)
		return loadSharedSaveFileFct(ptChar, data, maxSize, curSize);
	return 0;
};

int TCustomDll::initSharedSaveFile(BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (initSharedSaveFileFct)
		return initSharedSaveFileFct(data, maxSize, curSize);
	return 0;
};


void TCustomDll::initialize(DWORD offsetDll)
{
	offset = offsetDll;

	initFct = GetProcAddress(module,(LPCSTR)"_Init@0");
	if (!initFct)
		initFct = GetProcAddress(module,(LPCSTR)10000);

	releaseFct = GetProcAddress(module,(LPCSTR)"_Release@0");
	if (!releaseFct)
		releaseFct = GetProcAddress(module,(LPCSTR)10001);

	saveExtendedSaveFileFct = (TsaveSaveFile) GetProcAddress(module,"_saveExtendedSaveFile@16");
	loadExtendedSaveFileFct = (TloadSaveFile) GetProcAddress(module,"_loadExtendedSaveFile@16");
	initExtendedSaveFileFct = (TinitSaveFile) GetProcAddress(module,"_initExtendedSaveFile@12");
	saveSharedSaveFileFct = (TsaveSaveFile) GetProcAddress(module,"_saveSharedSaveFile@16");
	loadSharedSaveFileFct = (TloadSaveFile) GetProcAddress(module,"_loadSharedSaveFile@16");
	initSharedSaveFileFct = (TinitSaveFile) GetProcAddress(module,"_initSharedSaveFile@12");
}


/*================================= END OF FILE =================================*/