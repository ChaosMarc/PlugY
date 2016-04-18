/*=================================================================
	File created by Yohann NICOLAS.

	Modification of code in memory functions.

=================================================================*/

#include "common.h"
#include "error.h"
#include "modifMemory.h"
#include "d2functions.h"

const char* MSG_ERROR_READ_MEMORY = "Error : Read access missing to patch memory at %08X.\nPlease install a clean version of Lord of Destruction\n\n"
				"You can avoid this error message by setting ActiveCkeckMemory=0 in PlugY.ini\n(WARNING: Be careful when you use it, it shouldn't be used by common user)";
const char* MSG_CRITICAL_WRITE_MEMORY = "Error.\nWrite access missing to patch memory at %08X.\n\nPlease install a clean version of Lord of Destruction\n";
const char* ERROR_TESTING1 = "Error : BYTE %02X wanted but %02X found to change memory at %08X\n\n";
const char* ERROR_TESTING4 = "Error : DWORD %08X wanted but %08X found to change memory at %08X\n\n";


void* currentMemoryPos = 0;

DWORD mem_seek(DWORD newPos)
{
	currentMemoryPos = (void*)newPos;
	return (DWORD)currentMemoryPos;
}

void patchMemory1(BYTE value)
{
	if (IsBadWritePtr(currentMemoryPos,1))
	{
		log_box(MSG_CRITICAL_WRITE_MEMORY, currentMemoryPos);
		exit(1);
	}
	*(BYTE*)currentMemoryPos = value;
	currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 1);
}

void patchMemory4(DWORD value)
{
	if (IsBadWritePtr(currentMemoryPos,4))
	{
		log_box(MSG_CRITICAL_WRITE_MEMORY, currentMemoryPos);
		exit(1);
	}
	*(DWORD*)currentMemoryPos = value;
	currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 4);
}

BYTE getMemory1(LPVOID mempos)
{
	if (IsBadReadPtr(mempos,1))
	{
		log_box(MSG_ERROR_READ_MEMORY, currentMemoryPos);
		exit(1);
	}
	return *(BYTE*)mempos;
}

DWORD getMemory4(LPVOID mempos)
{
	if (IsBadReadPtr(mempos,4))
	{
		log_box(MSG_ERROR_READ_MEMORY, currentMemoryPos);
		exit(1);
	}
	return *(DWORD*)mempos;
}


void memt_byte(BYTE old, BYTE val)
{
	BYTE current = getMemory1(currentMemoryPos);
	if ( current == val)
	{
		log_msg("Warning : BYTE %02X is already set at memory %08X\n", val, currentMemoryPos);
		currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 1);
		return;
	}
	if ( old != current)
	{
		if (active_CheckMemory)
		{
			log_box(ERROR_TESTING1, old, current, currentMemoryPos);
			exit(1);
		} else log_msg(ERROR_TESTING1, old, current, currentMemoryPos);
	}
	log_msg("BYTE\t%08X : %02X->%02X\n", currentMemoryPos, old, val);
	patchMemory1(val);
}

bool testIfAlreadySet(DWORD current, DWORD wanted)
{
	if (current == wanted)
	{
		log_msg("Warning : DWORD %08X is already set at memory %08X\n", wanted, currentMemoryPos);
		currentMemoryPos = (LPVOID)((DWORD)currentMemoryPos + 4);
		return true;
	}
	return false;
}

void testMemory4(DWORD old, DWORD found)
{
	if (old != found)
		if (active_CheckMemory)
		{
			log_box(ERROR_TESTING4, old, found, currentMemoryPos);
			exit(1);
		} else log_msg(ERROR_TESTING4, old, found, currentMemoryPos);
}

void memt_dword(DWORD old, DWORD val)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = val;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, current);
	log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
	patchMemory4(wanted);
}


void memt_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref-(DWORD)currentMemoryPos-4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, current);
	log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
	patchMemory4(wanted);
}

void memc_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref-(DWORD)currentMemoryPos-4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, current + (DWORD)currentMemoryPos + 4);
	log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
	patchMemory4(wanted);
}

void memj_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref-(DWORD)currentMemoryPos-4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, getMemory4((LPVOID)getMemory4((LPVOID)(current + (DWORD)currentMemoryPos + 6))));
	log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
	patchMemory4(wanted);
}


void memd_ref4(DWORD old, DWORD ref)
{
	DWORD current = getMemory4(currentMemoryPos);
	DWORD wanted = ref-(DWORD)currentMemoryPos-4;
	if (testIfAlreadySet(current, wanted)) return;
	testMemory4(old, getMemory4((LPVOID)current));
	log_msg("DWORD\t%08X : %08X->%08X\n", currentMemoryPos, old, wanted);
	patchMemory4(wanted);
}

/*

void mem_byte(BYTE val)
{
	if ( *(BYTE*)currentMemoryPos == val)
	{
		log_msg("Warning : BYTE at %08X is already set to %02X\n", currentMemoryPos, val);
		currentMemoryPos += 1;
		return;
	}
	log_msg("BYTE\t%08X : %02X\n", currentMemoryPos, val);
	*(BYTE*)currentMemoryPos = val;
	currentMemoryPos += 1;
}

void mem_word(WORD val)
{
	if ( *(WORD*)currentMemoryPos == val)
	{
		log_msg("Warning : WORD at %08X is already set to %04X\n", currentMemoryPos, val);
		currentMemoryPos += 2;
		return;
	}
	log_msg("WORD\t%08X : %04X\n", currentMemoryPos, val);
	*(WORD*)currentMemoryPos = val;
	currentMemoryPos += 2;
}

void memt_word(WORD old, WORD val)
{
	if ( *(WORD*)currentMemoryPos == val)
	{
		log_msg("Warning : WORD at %08X is already set to %04X (normal:%04X)\n", currentMemoryPos, val, old);
		currentMemoryPos += 2;
		return;
	}
	if ( *(WORD*)currentMemoryPos != old)
	{
		log_msg("WORD %04X found, want %04X at %08X\n", *(WORD*)currentMemoryPos, old, currentMemoryPos);
		if (active_CheckMemory)
		{
			log_box(MSG_ERROR_MEMORY);
			exit(1);
		}
	}
	log_msg("WORD\t%08X : %04X->%04X\n", currentMemoryPos, old, val);
	*(WORD*)currentMemoryPos = val;
	currentMemoryPos += 2;
}

void mem_dword(DWORD val)
{
	if ( *(DWORD*)currentMemoryPos == val)
	{
		log_msg("Warning : DWORD at %08X is already set to %08X\n", currentMemoryPos, val);
		currentMemoryPos += 4;
		return;
	}
	log_msg("DWORD\t%08X : %08X\n", currentMemoryPos, val);
	*(DWORD*)currentMemoryPos = val;
	currentMemoryPos += 4;
}
void mem_ref4(DWORD ref)
{
	log_msg("DWORD\t%08X : %08X\n", currentMemoryPos, ref-(DWORD)currentMemoryPos-4);
	*(DWORD*)currentMemoryPos = ref-(DWORD)currentMemoryPos-4;
	currentMemoryPos += 4;
}
*/
/*================================= END OF FILE =================================*/