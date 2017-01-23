/*=================================================================
	File created by Yohann NICOLAS.

  Add an extra save file for each characters.

=================================================================*/
#pragma once

#include "common.h"

BYTE* readExtendedSaveFile(char* name, DWORD* size);
void writeExtendedSaveFile(char* name, BYTE* data, DWORD size);

int loadExtendedSaveFile(Unit* ptChar, BYTE* data, DWORD maxSize);
void saveExtendedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);

void backupExtendedSaveFile(char* name);

/*================================= END OF FILE =================================*/