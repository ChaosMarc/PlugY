/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Adding custom data.
	Save and load infinity & shared Stash

=================================================================*/

#include "plugYFiles.h"
#include "common.h"
#include <stdio.h>

//#include "newInterfaces.h"
extern bool active_SkillsPoints, active_StatsPoints, active_newInterfaces, active_multiPageStash, active_sharedGold;

void* unassignSkillsBtnImages = NULL;
void* unassignStatsBtnImages = NULL;
void* stashBtnsImages = NULL;
void* newStatsInterfaceImages = NULL;
void* statsBackgroundImages = NULL;
void* sharedGoldBtnsImages = NULL;


//void* lookupItemStatCost = NULL;


DWORD STDCALL isModFile (char* filename)
{
	if (strstr(filename, modDataDirectory) )
	{
		char fileTemp[0x104];
		log_msg("Load custom file : %s", filename);
		strcpy(fileTemp,filename);
		D2FogGetInstallPath(filename,0x104-strlen(filename));
		strcat(filename,fileTemp);
		log_msg("-> %s\n", filename);
		if ((GetFileAttributesA(filename) & 0x10) == 0)
			return true;
	}
	return false;
}


FCT_ASM ( caller_isModFile )
	TEST ESI,ESI
	JNZ ISNOTMODDATA
	MOV EBP, DWORD PTR SS:[ESP+0x140]
	PUSH EBP
	CALL isModFile
	TEST EAX,EAX
	JE ISNOTMODDATA
	MOV BL, BYTE PTR SS:[ESP+0x144]
	POP EAX
	POP EAX
	MOV EAX,D2StormMPQOpenFile
	ADD EAX,0x9A
	JMP EAX
ISNOTMODDATA:
	JMP DWORD PTR CS:[LeaveCriticalSection]
}}

FCT_ASM ( caller_isModFile_111 )
	TEST EDI,EDI
	JNZ ISNOTMODDATA
	MOV ESI, DWORD PTR SS:[ESP+0x130]
	PUSH ESI
	CALL isModFile
	TEST EAX,EAX
	JE ISNOTMODDATA
	MOV BL, BYTE PTR SS:[ESP+0x134]
	POP EAX
	POP EAX
	MOV EAX,D2StormMPQOpenFile
	ADD EAX,0xBD
	MOV EBP,GetFileAttributesA
	JMP EAX
ISNOTMODDATA:
	JMP DWORD PTR CS:[LeaveCriticalSection]
}}

void Install_PlugYFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch Storm to found custom file. (PlugYFiles)\n");

	// Try in Diablo II\PlugY\ if file not found
	mem_seek R7(Storm,	192C6, 19296, 18677, 2CC69, 14259, 121E9, 28D89, 2DA79);//( (DWORD)D2Storm268 + V7(Storm, 01A8, 01A8, 01AB, 0429, 0429, 0429, 0000) );
	memt_byte( 0xFF ,0x90); // NOP
	memt_byte( 0x15 ,0xE8); // CALL
	MEMD_REF4( LeaveCriticalSection, version_Storm >= V111 ? caller_isModFile_111 : caller_isModFile);
	//6FFC8677  |. FF15 F411FE6F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
	//6FC1CC69  |. FF15 3832C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
	//6FC04259  |. FF15 3832C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
	//6FC021E9  |. FF15 4432C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
	//6FC18D89  |. FF15 5832C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection
	//6FC1DA79  |. FF15 3C32C36F  CALL DWORD PTR DS:[<&KERNEL32.LeaveCriti>; \LeaveCriticalSection


	log_msg("\n" );

	isInstalled = true;
}
//6FFC7EF0 >/$ 8B4C24 10      MOV ECX,DWORD PTR SS:[ESP+10]

/****************************************************************************************************/


void loadImagesFile(void** images, const char* name)
{
	if(!images || !name) return;
	if(!*images)
	{
		char buffer[MAX_PATH];
		sprintf(buffer, "%s\\%s", modDataDirectory, name);
		log_msg("Images file to load : %s\n",buffer);

		*images = D2LoadImage(buffer,0);
		if (!*images)
		{
			sprintf(buffer, "Don't find Buttons Images File : %s.dc6", name);
			d2_assert(!*images, buffer, __FILE__, __LINE__);
		}
	}
}

void STDCALL loadCustomImages()
{
	if ( active_SkillsPoints )	 loadImagesFile(&unassignSkillsBtnImages, "UnassignSkillsBtns");
	if ( active_StatsPoints )	 loadImagesFile(&unassignStatsBtnImages, "UnassignStatsBtns");
	if ( active_multiPageStash || active_newInterfaces) loadImagesFile(&stashBtnsImages, "StashBtns");
	if ( active_sharedGold)		 loadImagesFile(&sharedGoldBtnsImages, "SharedGoldBtns");
	if ( active_newInterfaces )	 loadImagesFile(&newStatsInterfaceImages, "EmptyPage");	
	if ( active_newInterfaces )	 loadImagesFile(&statsBackgroundImages, "StatsBackground");	
}

#define freeImagesFile(I) if(I) {D2FreeImage(I);I=NULL;}

void STDCALL freeCustomImages()
{
	freeImagesFile(unassignSkillsBtnImages);
	freeImagesFile(unassignStatsBtnImages);
	freeImagesFile(stashBtnsImages);
	freeImagesFile(sharedGoldBtnsImages);
	freeImagesFile(newStatsInterfaceImages);
	freeImagesFile(statsBackgroundImages);
}

FCT_ASM ( caller_loadCustomImages )
	CALL loadCustomImages
	MOV ECX,0x0C
	RETN
}}

FCT_ASM ( caller_freeCustomImages )
	CALL freeCustomImages
	MOV ECX,0x0C
	RETN
}}

void Install_PlugYImagesFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlugYFiles();

	log_msg("Patch D2Client to load/free custom images. (PlugYImagesFiles)\n");

	// Load custom images
	mem_seek R7(D2Client, 57E21, 57E21, 5E4B1, 2E101, B67E1, 82761, 27EAE, 6E0BE);
	memt_byte( 0xB9 ,0xE8);
	MEMT_REF4( 0x0000000C , caller_loadCustomImages);
	//6FAFE4B1  |. B9 0C000000    MOV ECX,0C
	//6FADE101  |. B9 0C000000    MOV ECX,0C
	//6FB667E1  |. B9 0C000000    MOV ECX,0C
	//6FB32761  |. B9 0C000000    MOV ECX,0C
	//6FAD7EAE  |. B9 0C000000    MOV ECX,0C
	//6FB1E0BE  |. B9 0C000000    MOV ECX,0C

	// Free custom images
	mem_seek R7(D2Client, 57FA9, 57FA9, 5E639, 2D12D, B580D, 8158D, 26F8D, 6D07D);
	memt_byte( 0xB9 ,0xE8);
	MEMT_REF4( 0x0000000C , caller_freeCustomImages);
	//6FAFE639  |> B9 0C000000    MOV ECX,0C
	//6FADD12D  |> B9 0C000000    MOV ECX,0C
	//6FB6580D  |> B9 0C000000    MOV ECX,0C
	//6FB3158D  |> B9 0C000000    MOV ECX,0C
	//6FAD6F8D  |> B9 0C000000    MOV ECX,0C
	//6FB1D07D  |> B9 0C000000    MOV ECX,0C

	log_msg("\n" );

	isInstalled = true;
}


/****************************************************************************************************/

void loadStatsInterfaceDesc(DWORD mempool);
void freeStatsInterfaceDesc();



void FASTCALL loadTxtFiles(DWORD mempool)
{
	loadStatsInterfaceDesc(mempool);
}

void FASTCALL freeTxtFiles()
{
	freeStatsInterfaceDesc();
}

FCT_ASM ( caller_loadTxtFiles_111 )
	MOV ECX,DWORD PTR SS:[ESP+4]
	CALL loadTxtFiles
	JMP D2LoadSuperuniques
}}

FCT_ASM ( caller_loadTxtFiles )
	PUSH ECX
	CALL loadTxtFiles
	POP ECX
	JMP D2LoadSuperuniques
}}

FCT_ASM ( caller_freeTxtFiles )
	CALL freeTxtFiles
	JMP D2Fog10212
}}


void Install_PlugYTxtFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlugYFiles();

	log_msg("Patch D2Common to load/free custom txt files. (PlugYTxtFiles)\n");

//	lookupItemStatCost =  (void*)R7(D2Common, A1D70, A1D70, AA1D8, 0000, 0000, 0000, 0000);

	// Load custom txt files
	mem_seek R7(D2Common, 7F4B, 7F4B, 2F7D7, 76854, 37444, 81C44, 5D6E4, 855E4);
	MEMC_REF4( D2LoadSuperuniques, version_D2Common >= V111 ? caller_loadTxtFiles_111 : caller_loadTxtFiles );
	//6FD47F4A  |. E8 B1750100    CALL D2Common.6FD5F500
	//6FD47F4A  |. E8 C1750100    CALL D2Common.6FD5F510
	//01B6F7D6  |. E8 C5A7FFFF    CALL D2Common.01B69FA0
	//6FDC6853  |. E8 58B6FFFF    CALL D2Common.6FDC1EB0                   ; \D2Common.6FDC1EB0
	//6FD87443  |. E8 58B6FFFF    CALL D2Common.6FD82AA0                   ; \D2Common.6FD82AA0
	//6FDD1C43  |. E8 58B6FFFF    CALL D2Common.6FDCD2A0                   ; \D2Common.6FDCD2A0
	//6FDAD6E3  |. E8 88C1FFFF    CALL D2Common.6FDA9870                   ; \D2Common.6FDA9870
	//6FDD55E3  |. E8 58B6FFFF    CALL D2Common.6FDD0C40                   ; \D2Common.6FDD0C40

	// Free custom txt files
	mem_seek R7(D2Common, 79EC, 79EC, 10186, 332B3, 15AB3, 44E13, 5E8B3, FAA3);
	MEMJ_REF4( D2Fog10212, caller_freeTxtFiles );
	//6FD479EB   . E8 C8C00600    CALL <JMP.&Fog.#10212>
	//6FD479EB   . E8 C8C00600    CALL <JMP.&Fog.#10212>
	//01B50185  |. E8 F8410700    CALL <JMP.&Fog.#10212>
	//6FD832B2  |. E8 755FFDFF    CALL <JMP.&Fog.#10212>
	//6FD65AB2  |. E8 B537FFFF    CALL <JMP.&Fog.#10212>
	//6FD94E12  |. E8 1744FCFF    CALL <JMP.&Fog.#10212>
	//6FDAE8B2  |. E8 8FA9FAFF    CALL <JMP.&Fog.#10212>
	//6FD5FAA2  |. E8 5FB4FFFF    CALL <JMP.&Fog.#10212>

	log_msg("\n" );

	isInstalled = true;
}


/*================================= END OF FILE =================================*/