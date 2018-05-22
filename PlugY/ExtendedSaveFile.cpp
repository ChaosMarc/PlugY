/*=================================================================
	File created by Yohann NICOLAS.

  Add an extra save file for each characters.

=================================================================*/

#include "extendedSaveFile.h"
#include "infinityStash.h"
#include "customLibraries.h"
#include "extraOptions.h"
#include "common.h"
#include <stdio.h>

#define BUFFER_SIZE 0x4000
#define FILE_VERSION 0x3130			//"01"
#define FILE_EXTENDED 0x4D545343	//"CSTM"


BYTE * readExtendedSaveFile(char* name, DWORD* size)//WORKS
{
	char filename[512];
	BYTE* data;
	d2_assert(!name, "Bad file name (NULL)", __FILE__, __LINE__);
	D2FogGetSavePath( filename, 512-5);
	strncat(filename, name, 512 - strlen(filename) - 5);
	strcat(filename, ".d2x");

	log_msg("Extended file to read : %s\n",filename);

	FILE* file = fopen(filename, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		*size = ftell(file);
		fseek(file, 0, SEEK_SET);
		data = (BYTE*)D2FogMemAlloc(*size,__FILE__,__LINE__,0);
		DWORD nbRead = fread(data, 1, *size, file);
		fclose(file);
		d2_assert(nbRead != *size , "nbRead from extented save file != size", __FILE__, __LINE__);
	} else {
		log_msg("Can't open extented save file in mode \"rb\" (is not an error if it's a new player)\n");
		DWORD maxSize = 100;
		data = (BYTE*)D2FogMemAlloc(maxSize,__FILE__,__LINE__,0);
		*size = 14;
		*((DWORD*)&data[0])  = FILE_EXTENDED; //"CSTM"
		*((WORD *)&data[4])  = FILE_VERSION;
		*((DWORD*)&data[6])  = nbPlayersCommandByDefault - 1;
		*((DWORD*)&data[10]) = 0;// number of stash

		TCustomDll* currentDll = customDlls;
		while (currentDll)
		{
			currentDll->initExtendedSaveFile(&data, &maxSize, size);
			currentDll=currentDll->nextDll;
		}
	}
	return data;
}


int loadExtendedSaveFile(Unit* ptChar, BYTE data[], DWORD maxSize)//WORKS
{
	if (!ptChar || !PCPY || !data) return 0;

	log_msg("Load extended file\n");

	DWORD curSize = 0;

	if (*(DWORD*)&data[curSize] != FILE_EXTENDED)
	{
		log_msg("loadExtendedSaveFile -> bad header\n");
		return 9;
	}
	curSize += 4;

	if (*(WORD *)&data[curSize] != FILE_VERSION)
	{
		log_msg("loadExtendedSaveFile -> bad file version\n");
		return 9;
	}
	curSize += 2;
	nbPlayersCommand = (*(BYTE*)&data[curSize]) + 1;
	curSize += 1;
	curSize += 3;

	int ret = loadStashList(ptChar, data, maxSize, &curSize, false);

	TCustomDll* currentDll = customDlls;
	while (!ret && currentDll)
	{
		ret = currentDll->loadExtendedSaveFile(ptChar, data, maxSize, &curSize);
		currentDll=currentDll->nextDll;
	}


	PCPY->selfStashIsOpened = true;
	return ret;
}



void writeExtendedSaveFile(char* name, BYTE* data, DWORD size)
{
	char szTempName[MAX_PATH];
	char szSaveName[MAX_PATH];

	//Get temporary savefile name.
	D2FogGetSavePath(szTempName, MAX_PATH);
	strcat(szTempName, name);
	strcat(szTempName, ".d2~");
	log_msg("Extended temporary file for saving : %s\n",szTempName);

	//Write data in savefile.
	FILE* customSaveFile = fopen(szTempName, "wb+");
	fwrite(data, size, 1, customSaveFile);
	fclose(customSaveFile);

	//Get real savefile name.
	D2FogGetSavePath(szSaveName, MAX_PATH);
	strcat(szSaveName, name);
	strcat(szSaveName, ".d2x");
	log_msg("Extended file for saving : %s\n",szSaveName);

//	if (!MoveFileEx(szTempName, szSaveName, MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING)) 
	DeleteFile(szSaveName);
	if (!MoveFile(szTempName, szSaveName))
		log_box("Could not create the extended save file.");
}

void backupExtendedSaveFile(char* name)
{
	char szBackupName[MAX_PATH];
	char szSaveName[MAX_PATH];

	D2FogGetSavePath(szSaveName, MAX_PATH);
	strcat(szSaveName, name);
	strcat(szSaveName, ".d2x");

	D2FogGetSavePath(szBackupName, MAX_PATH);
	strcat(szBackupName, name);
	strcat(szBackupName, ".d2x.backup");

	CopyFile(szSaveName, szBackupName, true);
}


void saveExtendedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	*(DWORD *)(*data + *curSize) = FILE_EXTENDED; //"CSTM"
	*curSize += 4;
	*(WORD *)(*data + *curSize) = FILE_VERSION;
	*curSize += 2;
	*(DWORD *)(*data + *curSize) = (BYTE)(nbPlayersCommand - 1);
	*curSize += 4;

	saveStashList(ptChar, PCPY->selfStash, data, maxSize, curSize);

	TCustomDll* currentDll = customDlls;
	while (currentDll)
	{
		currentDll->saveExtendedSaveFile(ptChar, data, maxSize, curSize);
		currentDll=currentDll->nextDll;
	}
}

/*================================= END OF FILE =================================*/