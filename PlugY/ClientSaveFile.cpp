/*=================================================================
	File created by Yohann NICOLAS.

  Add an extra save file for each characters.

=================================================================*/
/*
#include "common.h"
#include "error.h"
#include "d2functions.h"
#include <stdio.h>

#define BUFFER_SIZE 0x4000
#define FILE_VERSION 0x3130			//"01"
#define FILE_SAVETYPE 0x544E4C43	//"CLNT"


BYTE * openClientSaveFile(char* name, DWORD* size)
{
	char filename[512];
	BYTE* data;
	d2_assert(!name, "Bad file name (NULL)", __FILE__, __LINE__);
	D2FogGetSavePath( filename, 512-5);
	strncat(filename, name, 512 - strlen(filename) - 5);
	strcat(filename, ".clt");

	log_msg("Client file to read : %s\n",filename);
	
	FILE* file = fopen(filename, "rb");
	if (file)
	{
		fseek(file, 0, SEEK_END);
		*size = ftell(file);
		fseek(file, 0, SEEK_SET);
		data = (BYTE*)D2FogMemAlloc(*size,__FILE__,__LINE__,0);
		DWORD nbRead = fread(data, 1, *size, file);
		fclose(file);
		d2_assert(nbRead != *size , "nbRead from client save file != size", __FILE__, __LINE__);
	} else {
		log_msg("Can't open client save file in mode \"rb\" (is not an error if it's a new player)\n");
		*size = 6;
		data = (BYTE*)D2FogMemAlloc(*size,__FILE__,__LINE__,0);
		*((DWORD*)&data[0])  = FILE_SAVETYPE; //"CSTM"
		*((WORD *)&data[4])  = FILE_VERSION;
	}
	return data;
}

DWORD loadClientSaveFile()
{
	Unit* ptChar = D2GetClientPlayer();
	DWORD size=0;
	log_msg("Load client file\n");
	if (!ptChar || !PCPlayerData) return 0;

	BYTE* data = openClientSaveFile(PCPlayerData->name,&size);
	if (!data) return 0;

	DWORD curSize = 0;
	
	log_msg("Load client file.\n");
	if (*(DWORD*)&data[curSize] != FILE_SAVETYPE)
	{
		log_msg("loadClientSaveFile -> bad header\n");
		D2FogMemDeAlloc(data,__FILE__,__LINE__,0);
		return 9;
	}
	curSize += 4;

	if (*(WORD *)&data[curSize] != FILE_VERSION)
	{
		log_msg("loadClientSaveFile -> bad file version\n");
		D2FogMemDeAlloc(data,__FILE__,__LINE__,0);
		return 9;
	}
	curSize += 2;

	D2FogMemDeAlloc(data,__FILE__,__LINE__,0);
	return 0;
}


DWORD saveClientSaveFile()
{
	DWORD curSize = 0;
	BYTE data[BUFFER_SIZE];
	char szTempName[MAX_PATH];
	char szSaveName[MAX_PATH];
	FILE* customSaveFile;
	Unit* ptChar = D2GetClientPlayer();

	D2FogGetSavePath( (char*)data, BUFFER_SIZE);
	sprintf( szTempName, "%s%s.cl~", data, PCPlayerData->name );
	log_msg("Client tmp file for saving : %s\n",szTempName);
	customSaveFile = fopen(szTempName, "wb+");

	*(DWORD *)&data[curSize] = FILE_SAVETYPE;
	curSize += 4;
	*(WORD *)&data[curSize] = FILE_VERSION;
	curSize += 2;

	fwrite(data, curSize, 1, customSaveFile);
	fclose(customSaveFile);

	D2FogGetSavePath( (char*)data, BUFFER_SIZE);
	sprintf( szSaveName, "%s%s.clt", data, PCPlayerData->name );
	log_msg("Client save file for saving : %s\n",szSaveName);
//	if (!MoveFileEx(szTempName, szSaveName, MOVEFILE_WRITE_THROUGH|MOVEFILE_REPLACE_EXISTING)) 
	DeleteFile(szSaveName);
	if (!MoveFile(szTempName, szSaveName))
		log_box("Could not create the client save file.");
	return 1;
}

/*================================= END OF FILE =================================*/