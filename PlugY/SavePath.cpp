/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Changing the current save path.

=================================================================*/

#include "savePath.h"
#include "common.h"

char* savePath = NULL;
bool active_changingSavePath = false;


FCT_ASM( changeSavePath )
	PUSH EDI
	PUSH EDX
	PUSH ESI
	MOV EDI,DWORD PTR DS:[savePath]
	XOR AL,AL
	CLD
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	NOT ECX
	SUB EDI,ECX
	XCHG EDI,ESI
	CMP BYTE PTR [ESI+1],':'
	JE END_CHANGESP
//RELATIVE_PATH:
	MOV EDX,ECX
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	DEC EDI
	CMP BYTE PTR [EDI-1],'\\'
	JE NEXT
	MOV BYTE PTR [EDI],'\\'
	INC EDI
NEXT:
	MOV ECX,EDX
END_CHANGESP:
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	POP ESI
	POP EDX
	POP EDI
	PUSH ESI
	CALL EBP
	CMP EAX,-1
	RETN
}}

FCT_ASM( changeSavePath_111 )
	PUSH EAX
	PUSH EDI
	PUSH EDX
	PUSH ESI
	MOV EDI,DWORD PTR DS:[savePath]
	XOR AL,AL
	CLD
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	NOT ECX
	SUB EDI,ECX
	XCHG EDI,ESI
	CMP BYTE PTR [ESI+1],':'
	JE END_CHANGESP
//RELATIVE_PATH:
	MOV EDX,ECX
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	DEC EDI
	CMP BYTE PTR [EDI-1],'\\'
	JE NEXT
	MOV BYTE PTR [EDI],'\\'
	INC EDI
NEXT:
	MOV ECX,EDX
END_CHANGESP:
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	POP ESI
	POP EDX
	POP EDI
	POP EAX
	CMP EAX,-1
	JE DONOT_JMP
	ADD DWORD PTR SS:[ESP],5
DONOT_JMP:
	RETN
}}

FCT_ASM ( forCreateSavePath )
	PUSH EDI
	MOV EDI,DWORD PTR DS:[savePath]
	MOV ECX,EDI
	CMP BYTE PTR DS:[EDI+1],':'
	JNZ END_CREATESP
	PUSH ESI
	XOR AL,AL
	CLD
	OR ECX,0xFFFFFFFF
	REPNE SCAS BYTE PTR ES:[EDI]
	NOT ECX
	SUB EDI,ECX
	XCHG EDI,ESI
	REP MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]
	POP ESI
END_CREATESP:
	POP EDI
	MOV DWORD PTR SS:[ESP+8],ECX
	JMP D2Storm503
}}



void Install_ChangingSavePath()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch Fog for change the save path. (changingSavePath)\n");

	if (version_Fog >= V111)
	{
		// Appel de notre fct d'ajout d'un sous-répertoire
		mem_seek R7(Fog, 000, 000, 000, 185F6, 1C106, 1F086, 17F86, 1E146);
		memt_byte( 0x83 ,0xE8);				// CALL changeSavePath
		MEMT_REF4( 0x0575FFF8, changeSavePath_111);
		//6FF685F6   . 83F8 FF        CMP EAX,-1
		//6FF685F9   . 75 05          JNZ SHORT fog.6FF68600
		//6FF6C106   . 83F8 FF        CMP EAX,-1
		//6FF6C109   . 75 05          JNZ SHORT fog.6FF6C110
		//6FF6F086   . 83F8 FF        CMP EAX,-1
		//6FF6F089   . 75 05          JNZ SHORT Fog.6FF6F090
		//6FF67F86   . 83F8 FF        CMP EAX,-1
		//6FF67F89   . 75 05          JNZ SHORT Fog.6FF67F90
		//6FF6E146   . 83F8 FF        CMP EAX,-1
		//6FF6E149   . 75 05          JNZ SHORT Fog.6FF50F64

		// Pour créer le bon chemin de sauvegarde
		mem_seek R7(Fog, 000, 000, 000, 18616, 1C126, 1F0A6, 17FA6, 1E166);
		MEMJ_REF4( D2Storm503, forCreateSavePath);
		//6FF68615   . E8 A246FFFF    CALL <JMP.&Storm.#503>
		//6FF6C125   . E8 C20BFFFF    CALL <JMP.&Storm.#503>
		//6FF6F0A5   . E8 34DDFEFF    CALL <JMP.&Storm.#503>
		//6FF67FA5   . E8 504EFFFF    CALL <JMP.&Storm.#503>
		//6FF6E165   . E8 6AEBFEFF    CALL <JMP.&Storm.#503>


		// Remove registry update
		mem_seek R7(Fog, 000, 000, 000, 1861A, 1C12A, 1F0AA, 17FAA, 1E16A);
		memt_byte( 0x56 ,0xEB); 			// JMP SHORT fog.6FF6862C
		memt_byte( 0x6A ,0x10);				//
		memt_byte( 0x00 ,0x90);				// NOP
		//6FF6861A   . 56             PUSH ESI
		//6FF6861B   . 6A 00          PUSH 0
		//6FF6861D   . 68 7C7BF76F    PUSH fog.6FF77B7C                                    ;  ASCII "Save Path"
		//6FF68622   . 68 2876F76F    PUSH fog.6FF77628                                    ;  ASCII "Diablo II"
		//6FF68627   . E8 1A47FFFF    CALL <JMP.&Storm.#425>
		//6FF6C12A   . 56             PUSH ESI
		//6FF6C12B   . 6A 00          PUSH 0
		//6FF6C12D   . 68 BC73F76F    PUSH fog.6FF773BC                        ;  ASCII "Save Path"
		//6FF6C132   . 68 C873F76F    PUSH fog.6FF773C8                        ;  ASCII "Diablo II"
		//6FF6C137   . E8 E60BFFFF    CALL <JMP.&Storm.#425>
		//6FF6F0AA   . 56             PUSH ESI
		//6FF6F0AB   . 6A 00          PUSH 0
		//6FF6F0AD   . 68 D466F76F    PUSH Fog.6FF766D4                        ;  ASCII "Save Path"
		//6FF6F0B2   . 68 E066F76F    PUSH Fog.6FF766E0                        ;  ASCII "Diablo II"
		//6FF6F0B7   . E8 58DDFEFF    CALL <JMP.&Storm.#425>
		//6FF67FAA   . 56             PUSH ESI
		//6FF67FAB   . 6A 00          PUSH 0
		//6FF6E16A   . 56             PUSH ESI
		//6FF6E16B   . 6A 00          PUSH 0

	} else {

		// Appel de notre fct d'ajout d'un sous-répertoire
		mem_seek( (DWORD)D2FogGetSavePath + 0x28);//6FF61928-6FF50000
		memt_byte( 0x56 ,0x90);				// NOP
		memt_byte( 0xFF ,0xE8);				// CALL changeSavePath
		MEMT_REF4( 0xFFF883D5, changeSavePath);
		//6FF61928   56               PUSH ESI
		//6FF61929   FFD5             CALL EBP
		//6FF6192B   83F8 FF          CMP EAX,-1

		// Pour créer le bon chemin de sauvegarde
		mem_seek( (DWORD)D2FogGetSavePath + 0xBD);//6FF619BC
		MEMJ_REF4( D2Storm503, forCreateSavePath);
		//6FF619BC   . E8 5D2A0000    CALL <JMP.&Storm.#503>

		// Remove registry update
		mem_seek( (DWORD)D2FogGetSavePath + 0xC1);//6FF619C1-6FF50000
		memt_byte( 0x56 ,0xEB); 			// JMP SHORT FOG.6FF619D2
		memt_byte( 0x53 ,0x0F);				//6FF619C3-6FF619D2
		//6FF619C1   56               PUSH ESI
		//6FF619C2   53               PUSH EBX
		//6FF619C3   68 A877F76F      PUSH Fog.6FF777A8                        ; ASCII "Save Path"
		//6FF619C8   68 9068F76F      PUSH Fog.6FF76890                        ; ASCII "Diablo II"
		//6FF619CD   E8 AC2A0000      CALL <JMP.&Storm.#425>
	}

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/