/*==============================================
	File created by Yohann NICOLAS.

	Modification of code in memory functions.
 
/*============================================*/

#pragma once

extern void* currentMemoryPos;
DWORD mem_seek(DWORD newPos);

void memt_byte(BYTE old, BYTE val);

#define MEMT_DWORD(O, R) memt_dword((DWORD)(O), (DWORD)(R))
void memt_dword(DWORD old, DWORD val);

#define MEMT_REF4(O, R) memt_ref4((DWORD)(O), (DWORD)(R))
void memt_ref4(DWORD old, DWORD ref);

//CALL <JMP.&D2gfx.#10047>
#define MEMJ_REF4(O, R) memj_ref4((DWORD)(O), (DWORD)(R))
void memj_ref4(DWORD old, DWORD ref);

//CALL D2Common.6FD5F500
#define MEMC_REF4(O, R) memc_ref4((DWORD)(O), (DWORD)(R))
void memc_ref4(DWORD old, DWORD ref);

//CALL DWORD PTR DS:[<&USER32.GetKeyState>]
#define MEMD_REF4(O, R) memd_ref4((DWORD)(O), (DWORD)(R))
void memd_ref4(DWORD old, DWORD ref);

/*================================= END OF FILE =================================*/