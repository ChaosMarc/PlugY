/*=================================================================
	File created by Yohann NICOLAS.

  Add an extra save file shared by all own characters.

=================================================================*/

#include "sharedSaveFile.h"
#include "infinityStash.h"
#include "customLibraries.h"
#include "common.h"
#include <stdio.h>

#define FILE_SHAREDSTASH 0x00535353	//"SSS "
#define BUFFER_SIZE 0x4000
#define FILE_VERSION 0x3230			//"02"

//6FC8CE8A  |. E8 A16BFAFF    CALL D2Game.6FC33A30
//$+C0     >            1F 00 00 00 03 00 00 06                  .....
// 28  0010 1000
BYTE* readSharedSaveFile(char* name, DWORD* size)
{
	char filename[512];
	BYTE* data=NULL;
	BYTE isHardCore=0;
	FILE* file=NULL;

	if (separateHardSoftStash)//Get hardcore flag
	{
		D2FogGetSavePath( filename, 512-strlen(name)-5);
		strcat(filename,name);
		strcat(filename,".d2s");
		log_msg("Normal file to read if it's hardcore character : %s\n",filename);
		file = fopen(filename, "rb");
		if (file)
		{
			fseek(file, 0x24, SEEK_SET);
			DWORD nbRead = fread(&isHardCore, 1, 1, file);
			isHardCore = (nbRead==1)? ((isHardCore & 4) == 4) : 0;
			fclose(file);
			file=NULL;
		}
		log_msg("%s is a HardCore character = %d\n",name,isHardCore);
	}

	if (active_sharedStash)
	{
		D2FogGetSavePath( filename, 512-strlen("_LOD_HC_SharedStashSave")-5);
		strcat(filename,isHardCore? "_LOD_HC_" : "_LOD_");
		strcat(filename, sharedStashFilename);
		strcat(filename,".sss");

		log_msg("Shared file to read : %s\n",filename);

		file = fopen(filename, "rb");
	}

	if (file)
	{
		fseek(file, 0, SEEK_END);
		*size = ftell(file);
		fseek(file, 0, SEEK_SET);
		data = (BYTE*)D2FogMemAlloc(*size,__FILE__,__LINE__,0);
		DWORD nbRead = fread(data, 1, *size, file);
		fclose(file);
		d2_assert(nbRead != *size , "nbRead from shared save file != size", __FILE__, __LINE__);
	} else {
		log_msg("Can't open shared save file in mode \"rb\" (is not an error if it's the first start of the mod)\n");
		*size = 14;
		DWORD maxSize = 100;
		data = (BYTE*)D2FogMemAlloc(maxSize,__FILE__,__LINE__,0);
		*((DWORD *)&data[0]) = FILE_SHAREDSTASH;
		*((WORD *)&data[4]) = FILE_VERSION;
		*((DWORD *)&data[6]) = 0;
		*((DWORD *)&data[10]) = 0;// number of stash

		TCustomDll* currentDll = customDlls;
		while (currentDll)
		{
			currentDll->initSharedSaveFile(&data, &maxSize, size);
			currentDll=currentDll->nextDll;
		}
	}

	return data;
}


int loadSharedSaveFile(Unit* ptChar, BYTE data[], DWORD maxSize)
{
	if ( !ptChar || !data) return false;

	log_msg("Load shared file\n");

	DWORD curSize = 0;

	if (*(DWORD*)&data[curSize] != FILE_SHAREDSTASH)
	{
		log_msg("loadSharedSaveFile -> bad header\n");
		return 9;
	}
	curSize += 4;

	if (*(WORD *)&data[curSize] == 0x3130) {//"01"
		curSize += 2;
		PCPY->sharedGold = 0;
	} else if (*(WORD *)&data[curSize] == FILE_VERSION) {
		curSize += 2;
		PCPY->sharedGold = *(DWORD*)&data[curSize];
		curSize += 4;
	} else {
		log_msg("loadSharedSaveFile -> bad file version : %04X\n", *(WORD *)&data[curSize]);
		return 9;
	}

	int ret = loadStashList(ptChar, data, maxSize, &curSize, true);

	TCustomDll* currentDll = customDlls;
	while (!ret && currentDll)
	{
		ret = currentDll->loadSharedSaveFile(ptChar, data, maxSize, &curSize);
		currentDll=currentDll->nextDll;
	}

	PCPY->sharedStashIsOpened = true;
	return ret;
}


void writeSharedSaveFile(char* name, BYTE* data, DWORD size, bool isHardcore)
{
	char szTempName[MAX_PATH];
	char szSaveName[MAX_PATH];

	//Get temporary savefile name.
	D2FogGetSavePath( szTempName, MAX_PATH-30);
	strcat(szTempName, separateHardSoftStash && isHardcore? "_LOD_HC_" : "_LOD_");
	strcat(szTempName, sharedStashFilename);
	strcat(szTempName,".ss~");
	log_msg("Shared temporary file for saving : %s\n", szTempName);

	//Write data in savefile.
	FILE* customSaveFile = fopen(szTempName, "wb+");
	fwrite(data, size, 1, customSaveFile);
	fclose(customSaveFile);

	//Get real savefile name.
	D2FogGetSavePath( szSaveName, MAX_PATH-30);
	strcat(szSaveName, separateHardSoftStash && isHardcore? "_LOD_HC_" : "_LOD_");
	strcat(szSaveName, sharedStashFilename);
	strcat(szSaveName,".sss");
	log_msg("Shared file for saving : %s\n", szSaveName);

//	if (!MoveFileEx(szTempName, szSaveName, MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING)) 
	DeleteFile(szSaveName);
	if (!MoveFile(szTempName, szSaveName))
		log_box("Could not create the shared save file.");
}

void backupSharedSaveFile()
{
	char szBackupName[MAX_PATH];
	char szSaveName[MAX_PATH];

	D2FogGetSavePath( szSaveName, MAX_PATH-30);
	strcat(szSaveName, "_LOD_");
	strcat(szSaveName, sharedStashFilename);
	strcat(szSaveName,".sss");

	D2FogGetSavePath( szBackupName, MAX_PATH-30);
	strcat(szBackupName, "_LOD_");
	strcat(szBackupName, sharedStashFilename);
	strcat(szBackupName,".sss.backup");

	CopyFile(szSaveName, szBackupName, true);

	if (separateHardSoftStash)
	{
		D2FogGetSavePath( szSaveName, MAX_PATH-30);
		strcat(szSaveName, "_LOD_HC_");
		strcat(szSaveName, sharedStashFilename);
		strcat(szSaveName,".sss");

		D2FogGetSavePath( szBackupName, MAX_PATH-30);
		strcat(szBackupName, "_LOD_HC_");
		strcat(szBackupName, sharedStashFilename);
		strcat(szBackupName,".sss.backup");

		CopyFile(szSaveName, szBackupName, true);
	}
}


void saveSharedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	*(DWORD *)(*data + *curSize) = FILE_SHAREDSTASH;
	*curSize += 4;
	if (PCPY->sharedGold)
	{
		*(WORD *)(*data + *curSize) = FILE_VERSION;
		*curSize += 2;

		*(DWORD *)(*data + *curSize) = PCPY->sharedGold;
		*curSize += 4;
	} else {
		*(WORD *)(*data + *curSize) = 0x3130;
		*curSize += 2;
	}
	saveStashList(ptChar, PCPY->sharedStash, data, maxSize, curSize);

	TCustomDll* currentDll = customDlls;
	while (currentDll)
	{
		currentDll->saveSharedSaveFile(ptChar, data, maxSize, curSize);
		currentDll=currentDll->nextDll;
	}
}


/*================================= END OF FILE =================================*/