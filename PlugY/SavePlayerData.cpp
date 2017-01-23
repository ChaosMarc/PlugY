/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

    Save Player Custom Data.

=================================================================*/

#include "infinityStash.h"
#include "extendedSaveFile.h"
#include "sharedSaveFile.h"
#include "common.h"


void STDCALL SaveSPPlayerCustomData(Unit* ptChar)
{
	if (!D2isLODGame()) return;//D2Game but in SP so np

	log_msg("\n--- Start SaveSPPlayerCustomData ---\n");

	if (PCPY->selfStashIsOpened)
	{
		DWORD curSizeExt = 0;
		DWORD maxSizeExt = 0x4000;
		BYTE* dataExt = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeExt,__FILE__,__LINE__,0);
		d2_assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
		writeExtendedSaveFile(PCPlayerData->name, dataExt, curSizeExt);
		D2FreeMem(PCGame->memoryPool, dataExt,__FILE__,__LINE__,0);
	}

	if (active_sharedStash && PCPY->sharedStashIsOpened)
	{
		DWORD curSizeShr = 0;
		DWORD maxSizeShr = 0x4000;
		BYTE* dataShr = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeShr,__FILE__,__LINE__,0);
		d2_assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
		saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);

		NetClient* ptClient = D2GetClient(ptChar,__FILE__,__LINE__);
		writeSharedSaveFile(PCPlayerData->name, dataShr, curSizeShr, ptClient->isHardCoreGame );
		D2FreeMem(PCGame->memoryPool, dataShr,__FILE__,__LINE__,0);
	}

	log_msg("End saving.\n\n");
}


FCT_ASM ( caller_SaveSPPlayerCustomData_111 )
	CALL D2FogGetSavePath
	PUSH DWORD PTR SS:[ESP+0x2608]
	CALL SaveSPPlayerCustomData
	RETN
}}

FCT_ASM ( caller_SaveSPPlayerCustomData )
	CALL D2FogGetSavePath
	PUSH EDI
	CALL SaveSPPlayerCustomData
	RETN
}}

FCT_ASM ( caller_SaveSPPlayerCustomData_9 )
	CALL D2FogGetSavePath
	PUSH ESI
	CALL SaveSPPlayerCustomData
	RETN
}}


//////////////////////////////////////////////////////////////////////////////////////////////////

#define TC_SAVE_PERSONAL 0
#define TC_SAVE_SHARED 1

#pragma pack(1)
typedef struct {
	BYTE	packID;
	BYTE	packSize;
	BYTE	init;
	DWORD	finalSize:31;
	DWORD	isCustom:1;
	BYTE	type;
	BYTE	data[0xFF];
} t_rcvMsg;
#pragma pack()

struct s_MPSaveFile
{
	int		sizeExtended;
	int		curExtended;
	BYTE*	dataExtended;
	int		sizeShared;
	int		curShared;
	BYTE*	dataShared;
};
static s_MPSaveFile receivedSaveFiles;
static BYTE customPackID = 0xB2;
//static s_MPSaveFile* receivedSaveFiles = NULL;


struct s_dataToSend
{
	s_dataToSend*	next;
	int		clientID;
	int		sizeExtended;
	int		curExtended;
	BYTE*	dataExtended;
	int		sizeShared;
	int		curShared;
	BYTE*	dataShared;
	bool	init;
};
s_dataToSend* ptDataToSend=NULL;

/*
void sendDataToSave(DWORD clientID, BYTE* data, DWORD size, bool isShared)
{
	t_rcvMsg pack;
	d2_assert(size >= 0x40000000, "size of file > 0x40000000", __FILE__, __LINE__);

	pack.packID = customPackID;
	pack.init = !isShared;
	pack.finalSize = size;
	pack.type = isShared ? TC_SAVE_SHARED : TC_SAVE_PERSONAL;
	pack.isCustom = true;

	DWORD sended = 0;
	while (sended < size)
	{
		pack.packSize = (BYTE) (size - sended > 0xFE ? 0xFE : size - sended);
		CopyMemory(pack.data,  &data[sended], pack.packSize);
		log_msg("send: ID=%02X\tsize=%02X\tinit=%02X\ttotalsize=%08X\ttype=%d\n", pack.packID, pack.init, pack.packSize, pack.finalSize, pack.type);
		pack.packSize++;
		D2SendToClient(0, clientID, (BYTE*)&pack, pack.packSize+7);
		pack.init = false;
		sended += pack.packSize -1;
	}
	log_msg("\n");
}*/

void STDCALL SendSaveFilesToSave( Unit* ptChar )
{
//	if (!D2isLODGame()) return;
	log_msg("\n--- Start SendSaveFilesToSave ---\n");

	DWORD curSizeExt = 0;
	BYTE* dataExt = NULL;
	DWORD curSizeShr = 0;
	BYTE* dataShr = NULL;

	if (PCPY->selfStashIsOpened)
	{
		DWORD maxSizeExt = 0x4000;
		dataExt = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeExt,__FILE__,__LINE__,0);
		d2_assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
	}

	if (active_sharedStash && PCPY->sharedStashIsOpened)
	{
		DWORD maxSizeShr = 0x4000;
		dataShr = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeShr,__FILE__,__LINE__,0);
		d2_assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
		saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);
	}

	NetClient* ptClient = D2GetClient(ptChar,__FILE__,__LINE__);
	s_dataToSend* dataToSend = ptDataToSend;
	while (dataToSend && (dataToSend->clientID != ptClient->clientID))
		dataToSend = dataToSend->next;
	if (!dataToSend)
	{
		dataToSend = (s_dataToSend*) D2AllocMem(PCGame->memoryPool, sizeof(s_dataToSend), __FILE__, __LINE__, 0);
		ZeroMemory(dataToSend, sizeof(s_dataToSend));
		dataToSend->next = ptDataToSend;
		ptDataToSend = dataToSend;
	}

	//Sending savefiles
	dataToSend->clientID = ptClient->clientID;
	dataToSend->init = 1;
	dataToSend->sizeExtended = curSizeExt;
	dataToSend->curExtended = 0;
	dataToSend->dataExtended = dataExt;
	dataToSend->sizeShared = curSizeShr;
	dataToSend->curShared = 0;
	dataToSend->dataShared = dataShr;
	log_msg("clientID=%d\t init=%d\t sizeExtended=%X\t curExtended=%X\t dataExtended=%X\t sizeShared=%X\t curShared=%X\t dataShared=%08X\n", 
		dataToSend->clientID, dataToSend->init, dataToSend->sizeExtended, dataToSend->curExtended, dataToSend->dataExtended, dataToSend->sizeShared, dataToSend->curShared, dataToSend->dataShared);

/*	NetClient* ptClient = D2GetClient(ptChar,__FILE__,__LINE__);
	if (dataExt)
	{
		sendDataToSave(ptClient->clientID, dataExt, curSizeExt, false);
		D2FreeMem(PCGame->memoryPool, dataExt,__FILE__,__LINE__,0);
	}
	if (dataShr)
	{
		sendDataToSave(ptClient->clientID, dataShr, curSizeShr, true);
		D2FreeMem(PCGame->memoryPool, dataShr,__FILE__,__LINE__,0);
	}
*/
	log_msg("End SendSaveFilesToSave.\n\n");
}


DWORD STDCALL ManageNextPacketToSend(NetClient* ptClient)
{
	log_msg("ManageNextPacketToSend: ");
	s_dataToSend* dataToSend = ptDataToSend;
	while (dataToSend && (dataToSend->clientID != ptClient->clientID))
		dataToSend = dataToSend->next;
	if (!dataToSend) return 1;

	log_msg("clientID=%d\t init=%d\t sizeExtended=%X\t curExtended=%X\t dataExtended=%X\t sizeShared=%X\t curShared=%X\t dataShared=%08X\n", 
		dataToSend->clientID, dataToSend->init, dataToSend->sizeExtended, dataToSend->curExtended, dataToSend->dataExtended, dataToSend->sizeShared, dataToSend->curShared, dataToSend->dataShared);

	if (dataToSend->sizeExtended && dataToSend->dataExtended && (dataToSend->curExtended < dataToSend->sizeExtended))
	{
		DWORD remainingData = dataToSend->sizeExtended - dataToSend->curExtended;
		t_rcvMsg* msg = (t_rcvMsg*)D2AllocMem(PClientGame->memoryPool, sizeof(t_rcvMsg),__FILE__,__LINE__,0);
		msg->packID = customPackID;
		msg->init = dataToSend->init;
		msg->finalSize = dataToSend->sizeExtended;
		msg->type = TC_SAVE_PERSONAL;
		msg->isCustom = true;
		msg->packSize = remainingData > 0xFE ? 0xFF : (BYTE)remainingData + 1;
		CopyMemory(msg->data,  &dataToSend->dataExtended[dataToSend->curExtended], msg->packSize);
		log_msg("Saving Send Packet: type=%X\t init=%d\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->type, msg->init, msg->finalSize, msg->packSize, msg->data);
		D2SendToClient(0, dataToSend->clientID, msg, msg->packSize+7);
		dataToSend->init = false;
		dataToSend->curExtended += msg->packSize - 1;
		D2FreeMem(PClientGame->memoryPool, msg,__FILE__,__LINE__,0);
		if (dataToSend->curExtended == dataToSend->sizeExtended)
		{
			dataToSend->sizeExtended = 0;
			dataToSend->curExtended = 0;
			D2FreeMem(PClientGame->memoryPool, dataToSend->dataExtended,__FILE__,__LINE__,0);
			dataToSend->dataExtended = NULL;
		}
		log_msg("End Send Packet\n");
		return 0;//ManageNextPacketToSend(ptClient);//return 0;
	}

	if (dataToSend->sizeShared && dataToSend->dataShared && (dataToSend->curShared < dataToSend->sizeShared))
	{
		DWORD remainingData = dataToSend->sizeShared - dataToSend->curShared;
		t_rcvMsg* msg = (t_rcvMsg*)D2AllocMem(PClientGame->memoryPool, sizeof(t_rcvMsg),__FILE__,__LINE__,0);
		msg->packID = customPackID;
		msg->init = dataToSend->init;
		msg->finalSize = dataToSend->sizeShared;
		msg->type = TC_SAVE_SHARED;
		msg->isCustom = true;
		msg->packSize = remainingData > 0xFE ? 0xFF : (BYTE)remainingData + 1;
		CopyMemory(msg->data,  &dataToSend->dataShared[dataToSend->curShared], msg->packSize);
		log_msg("Saving Send Packet: type=%X\t init=%d\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->type, msg->init, msg->finalSize, msg->packSize, msg->data);
		D2SendToClient(0, dataToSend->clientID, msg, msg->packSize+7);
		dataToSend->init = false;
		dataToSend->curShared += msg->packSize - 1;
		D2FreeMem(PClientGame->memoryPool, msg,__FILE__,__LINE__,0);
		if (dataToSend->curShared == dataToSend->sizeShared)
		{
			dataToSend->sizeShared = 0;
			dataToSend->curShared = 0;
			D2FreeMem(PClientGame->memoryPool, dataToSend->dataShared,__FILE__,__LINE__,0);
			dataToSend->dataShared = NULL;
		}
		log_msg("End Send Packet\n");
		return 0;//ManageNextPacketToSend(ptClient);//return 0;
	}

	log_msg("End Send Packet\n");
	return 1;
}


DWORD STDCALL ReceiveSaveFilesToSave(t_rcvMsg* msg)
{
	if( (msg->packID != customPackID) || !msg->isCustom) return 0;

	log_msg("Saving Receive Packet: type=%X\t init=%d\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->type, msg->init, msg->finalSize, msg->packSize, msg->data);

	bool isShared;

	if ( msg->type == TC_SAVE_PERSONAL)
		isShared = false;
	else if (msg->type == TC_SAVE_SHARED)
		isShared = true;
	else return 0;


	if (msg->init)
	{
		D2FogMemDeAlloc(receivedSaveFiles.dataExtended,__FILE__,__LINE__,0);
		D2FogMemDeAlloc(receivedSaveFiles.dataShared,__FILE__,__LINE__,0);
		ZeroMemory(&receivedSaveFiles, sizeof(receivedSaveFiles));//TODO
	}

	log_msg("receivedSaveFiles: sizeExtended=%d\t curExtended=%d\t dataExtended=%08X\t sizeShared=%d\t curShared=%d\t dataShared=%08X\n", receivedSaveFiles.sizeExtended, receivedSaveFiles.curExtended, receivedSaveFiles.dataExtended, receivedSaveFiles.sizeShared, receivedSaveFiles.curShared, receivedSaveFiles.dataShared);

	DWORD size = msg->packSize - 1;
	if (isShared)
	{
		if (receivedSaveFiles.sizeShared == 0)
			receivedSaveFiles.sizeShared = msg->finalSize;
//		d2_assert(receivedSaveFiles.sizeShared != msg->finalSize, "Size of shared file has change", __FILE__, __LINE__);

		if (!receivedSaveFiles.dataShared)
			receivedSaveFiles.dataShared = (BYTE *)D2FogMemAlloc(receivedSaveFiles.sizeShared,__FILE__,__LINE__,0);

		CopyMemory(&receivedSaveFiles.dataShared[receivedSaveFiles.curShared], msg->data, size);
		receivedSaveFiles.curShared += size;

	} else {

		if (receivedSaveFiles.sizeExtended == 0)
			receivedSaveFiles.sizeExtended = msg->finalSize;
//		d2_assert(receivedSaveFiles.sizeExtended != msg->finalSize, "Size of extented file has change", __FILE__, __LINE__);

		if (!receivedSaveFiles.dataExtended)
			receivedSaveFiles.dataExtended = (BYTE *)D2FogMemAlloc(receivedSaveFiles.sizeExtended,__FILE__,__LINE__,0);

		CopyMemory(&receivedSaveFiles.dataExtended[receivedSaveFiles.curExtended], msg->data, size);
		receivedSaveFiles.curExtended += size;
	}
	log_msg("End Save Receive Packet\n");
	return 1;
}


void STDCALL SaveMPPlayerCustomData(BYTE* dataD2Savefile )
{
	log_msg("Start SaveMPPlayerCustomData.\n");
	Unit* ptChar = D2GetClientPlayer();
	if( receivedSaveFiles.sizeExtended && (receivedSaveFiles.sizeExtended == receivedSaveFiles.curExtended) && receivedSaveFiles.sizeShared && (receivedSaveFiles.sizeShared == receivedSaveFiles.curShared) )
	{
		log_msg("Saving can start\n");
		if (ptChar)
		{
			writeExtendedSaveFile(PCPlayerData->name, receivedSaveFiles.dataExtended, receivedSaveFiles.sizeExtended);
			D2FogMemDeAlloc(receivedSaveFiles.dataExtended,__FILE__,__LINE__,0);
			if (active_sharedStash)
				writeSharedSaveFile(PCPlayerData->name, receivedSaveFiles.dataShared, receivedSaveFiles.sizeShared, (dataD2Savefile[0x24] & 4) == 4);//6FBAB9A4-6FAA0000
			D2FogMemDeAlloc(receivedSaveFiles.dataShared,__FILE__,__LINE__,0);
			ZeroMemory(&receivedSaveFiles,sizeof(receivedSaveFiles));
		}
		log_msg("Receive Savefiles completed\n\n");
	} else {
		if (ptChar)
		{
			log_box("Connection error : back up current save file then save with client data.");
			backupSharedSaveFile();
			backupExtendedSaveFile(PCPlayerData->name);
			SaveSPPlayerCustomData(ptChar);
		}
	}
	log_msg("--- End SaveMPPlayerCustomData. ---\n\n");
}





/*
FCT_ASM ( caller_SendSaveFilesToSave_9 )
	POP ECX
	PUSH EAX
	PUSH ECX
	PUSH EBX
	CALL SendSaveFilesToSave
	MOV EDX,EBX
	MOV ECX,EDI
	RETN
}}

FCT_ASM ( caller_SendSaveFilesToSave )
	POP ECX
	PUSH EAX
	PUSH ECX
	PUSH EBX
	CALL SendSaveFilesToSave
	MOV EDX,EBX
	MOV ECX,EBP
	RETN
}}
*/

FCT_ASM( caller_ManageNextPacketToSend )
	PUSH ESI
	CALL ManageNextPacketToSend
	TEST EAX,EAX
	JNZ end_caller_ManageNextPacketToSend
	XOR ECX,ECX
	RETN
end_caller_ManageNextPacketToSend:
	MOV ECX,DWORD PTR DS:[ESI+0x17C]
	RETN
}}

FCT_ASM( caller_ManageNextPacketToSend_9 )
	PUSH ESI
	CALL ManageNextPacketToSend
	TEST EAX,EAX
	JNZ end_caller_ManageNextPacketToSend_9
	MOV DWORD PTR DS:[ESI+0x14C],5
	POP ESI
	POP ESI
	RETN
end_caller_ManageNextPacketToSend_9:
	MOV EAX,DWORD PTR DS:[ESI+0x150]
	RETN
}}

FCT_ASM( caller_ManageNextPacketToSend_9d )
	PUSH ESI
	CALL ManageNextPacketToSend
	TEST EAX,EAX
	JNZ end_caller_ManageNextPacketToSend_9d
	MOV DWORD PTR DS:[ESI+0x170],5
	POP ESI
	POP ESI
	RETN
end_caller_ManageNextPacketToSend_9d:
	MOV EAX,DWORD PTR DS:[ESI+0x174]
	RETN
}}



FCT_ASM( caller_SendSaveFilesToSave_111 )
	PUSH DWORD PTR SS:[ESP+0x2014]
	CALL SendSaveFilesToSave
	MOV EAX,DWORD PTR SS:[ESP+0x8]
	TEST EAX,EAX
	RETN
}}

FCT_ASM( caller_SendSaveFilesToSave )
	PUSH EDI
	CALL SendSaveFilesToSave
	MOV EDI,DWORD PTR SS:[ESP+0x14]
	TEST EDI,EDI
	RETN
}}

FCT_ASM( caller_SendSaveFilesToSave_9 )
	PUSH ESI
	CALL SendSaveFilesToSave
	MOV ESI,DWORD PTR SS:[ESP+0x14]
	TEST ESI,ESI
	RETN
}}


FCT_ASM ( caller_ReceivedSaveFilesToSave_111 )
	LEA EAX,DWORD PTR SS:[ESP+0x10]
	PUSH EAX
	CALL ReceiveSaveFilesToSave
	TEST EAX,EAX
	JE continue_rcvFct
	ADD DWORD PTR SS:[ESP],0x3D
	RETN
continue_rcvFct:
	MOVZX EAX,BYTE PTR SS:[ESP+0x10]
	RETN
}}

FCT_ASM ( caller_ReceivedSaveFilesToSave )
	CMP EDX,-1
	JE continue_rcvFct
	PUSH ECX
	PUSH EDX
	PUSH ECX
	CALL ReceiveSaveFilesToSave
	POP EDX
	POP ECX
	TEST EAX,EAX
	JE continue_rcvFct
	XOR EAX,EAX
	ADD ESP,4
	RETN
continue_rcvFct:
	POP EAX
	SUB ESP,0x5F4//5F4
	JMP EAX
//	JMP DWORD PTR SS:[ESP+0x5F0]
}}

FCT_ASM ( caller_SaveMPPlayerCustomData_111 )
	PUSH EAX
	PUSH ECX
	PUSH EAX
	CALL SaveMPPlayerCustomData
	POP ECX
	POP EAX
	CMP ECX,0xAA55AA55
	RETN
}}



FCT_ASM ( caller_SaveMPPlayerCustomData )
	PUSH ECX
	PUSH ECX
	CALL SaveMPPlayerCustomData
	POP ECX
	MOV EAX,DWORD PTR DS:[ECX]
	MOV EDX,DWORD PTR DS:[ECX+4]
	RETN
}}



void Install_SavePlayerData()
{
	static int isInstalled = false;
	if (isInstalled || !active_PlayerCustomData) return;

	log_msg("Patch D2Game & D2Client for save Player's custom data. (SavePlayerData)\n");

	//Save single player custom data.
	mem_seek R7(D2Game, 4DF04, 4E304, 5A624, B9365, 25475, 44165, 53F35, 39835);
	MEMJ_REF4( D2FogGetSavePath, version_D2Game >= V111 ? caller_SaveSPPlayerCustomData_111 : version_D2Game != V109b ? caller_SaveSPPlayerCustomData : caller_SaveSPPlayerCustomData_9);
	//6FC8A623   E8 3E210900      CALL <JMP.&Fog.#10115>
	//02039364  |. E8 3B0FF5FF    CALL <JMP.&Fog.#10115>
	//01F95474  |. E8 C34EFEFF    CALL <JMP.&Fog.#10115>
	//6FC64164  |. E8 EB61FCFF    CALL <JMP.&Fog.#10115>
	//6FC73F34  |. E8 DD63FBFF    CALL <JMP.&Fog.#10115>
	//6FC59834  |. E8 FB0AFDFF    CALL <JMP.&Fog.#10115>

	//Send SaveFiles
	mem_seek R7(D2Game, 4DFFA, 4E3FA, 5A720, B92DB, 253EB, 440DB, 53EAB, 397AB);
	memt_byte( 0x8B ,0x90); // NOP
	memt_byte( version_D2Game >= V111 ? 0x44 : version_D2Game != V109b ? 0x7C : 0x74 ,0xE8); // CALL
	MEMT_REF4( version_D2Game >= V111 ? 0xC0850424 : version_D2Game != V109b ? 0xFF851024 : 0xF6851024, version_D2Game >= V111 ? caller_SendSaveFilesToSave_111 : version_D2Game != V109b ? caller_SendSaveFilesToSave : caller_SendSaveFilesToSave_9);
	//6FC8A720  |. 8B7C24 10      MOV EDI,DWORD PTR SS:[ESP+10]
	//6FC8A724  |. 85FF           TEST EDI,EDI
	//020392DB  |. 8B4424 04      MOV EAX,DWORD PTR SS:[ESP+4]
	//020392DF  |. 85C0           TEST EAX,EAX
	//01F953EB  |. 8B4424 04      MOV EAX,DWORD PTR SS:[ESP+4]
	//01F953EF  |. 85C0           TEST EAX,EAX
	//6FC640DB  |. 8B4424 04      MOV EAX,DWORD PTR SS:[ESP+4]
	//6FC640DF  |. 85C0           TEST EAX,EAX
	//6FC73EAB  |. 8B4424 04      MOV EAX,DWORD PTR SS:[ESP+4]
	//6FC73EAF  |. 85C0           TEST EAX,EAX
	//6FC597AB  |. 8B4424 04      MOV EAX,DWORD PTR SS:[ESP+4]
	//6FC597AF  |. 85C0           TEST EAX,EAX

	mem_seek R7(D2Game, 7993, 7A13, 7BBB, E2943, E6D83, A89D3, 2D173, BEDD3);
	memt_byte( 0x8B ,0x90); // NOP
	memt_byte( version_D2Game >= V110 ? 0x8E : 0x86 ,0xE8); // CALL
	MEMT_REF4( version_D2Game >= V110 ? 0x0000017C : version_D2Game == V109d ? 0x0000174 : 0x00000150, version_D2Game >= V110 ? caller_ManageNextPacketToSend : version_D2Game == V109d ? caller_ManageNextPacketToSend_9d : caller_ManageNextPacketToSend_9);
	//6FC37BBB  |> 8B8E 7C010000  MOV ECX,DWORD PTR DS:[ESI+17C]
	//02062943  |. 8B8E 7C010000  MOV ECX,DWORD PTR DS:[ESI+17C]
	//02056D83  |. 8B8E 7C010000  MOV ECX,DWORD PTR DS:[ESI+17C]
	//6FCC89D3  |. 8B8E 7C010000  MOV ECX,DWORD PTR DS:[ESI+17C]
	//6FC4D173  |. 8B8E 7C010000  MOV ECX,DWORD PTR DS:[ESI+17C]
	//6FCDEDD3  |. 8B8E 7C010000  MOV ECX,DWORD PTR DS:[ESI+17C]

//	mem_seek R7(D2Game, 7B82, 7C05, 7DCF, 0000, 0000, 0000, 0000);//117FC,	117EC,	11DBC
//	memt_byte( 0x8B ,0xE8); // CALL
//	MEMT_REF4( (version_D2Game == V110) ?  0x50CD8BD3 : 0x50CF8BD3, (version_D2Game == V110) ? caller_SendSaveFilesToSave : caller_SendSaveFilesToSave_9);
	//6FC37DCF  |. 8BD3           |MOV EDX,EBX
	//6FC37DD1  |. 8BCD           |MOV ECX,EBP
	//6FC37DD3  |. 50             |PUSH EAX

	if ( version_D2Game >= V111 )
	{
		//Received SaveFiles
		mem_seek R7(D2Client, 116F0, 116E0, 11CB0, 89246, 32076, 7BCD6, 43946, 448E6);
		memt_byte( 0x0F ,0xE8);
		MEMT_REF4( 0x0C2444B6, caller_ReceivedSaveFilesToSave_111);
		//6FB39246  |. 0FB64424 0C    |MOVZX EAX,BYTE PTR SS:[ESP+C]
		//6FAE2076  |. 0FB64424 0C    |MOVZX EAX,BYTE PTR SS:[ESP+C]
		//6FB2BCD6  |. 0FB64424 0C    |MOVZX EAX,BYTE PTR SS:[ESP+C]
		//6FAF3946  |. 0FB64424 0C    |MOVZX EAX,BYTE PTR SS:[ESP+C]
		//6FAF48E6  |. 0FB64424 0C    |MOVZX EAX,BYTE PTR SS:[ESP+C]

		// Save multiplayer player custom data.
		mem_seek R7(D2Client, 117FC, 117EC, 11DBC, 99AE2, BD7F2, 64A22, AC572, 829C2);
		memt_byte( 0x81 ,0xE8); // CALL
		MEMT_REF4( 0x55AA55F9, caller_SaveMPPlayerCustomData_111);
		memt_byte( 0xAA ,0x90); // CALL
		//6FB49AE2  |. 81F9 55AA55AA  CMP ECX,AA55AA55
		//6FB6D7F2  |. 81F9 55AA55AA  CMP ECX,AA55AA55
		//6FB14A22  |. 81F9 55AA55AA  CMP ECX,AA55AA55
		//6FB5C572  |. 81F9 55AA55AA  CMP ECX,AA55AA55
		//6FB329C2  |. 81F9 55AA55AA  CMP ECX,AA55AA55
	} else {
		//Received SaveFiles
		mem_seek R7(D2Client, 116F0, 116E0, 11CB0, 89246, 32076, 7BCD6, 0000, 0000);
		memt_byte( 0x81 ,0x90); // NOP
		memt_byte( 0xEC ,0xE8); // CALL
		MEMT_REF4( 0x000005F4, caller_ReceivedSaveFilesToSave);
		//6FAB1CB0  |$ 81EC F4050000  SUB ESP,5F4

		// Save multiplayer player custom data.
		mem_seek R7(D2Client, 117FC, 117EC, 11DBC, 99AE2, BD7F2, 64A22, 0000, 0000);
		memt_byte( 0x8B ,0xE8); // CALL
		MEMT_REF4( 0x04518B01, caller_SaveMPPlayerCustomData);
		//6FAB1DBC  |. 8B01           MOV EAX,DWORD PTR DS:[ECX]
		//6FAB1DBE  |. 8B51 04        MOV EDX,DWORD PTR DS:[ECX+4]
	}

	if ( version_D2Game == V109b || version_D2Game == V109d )
		customPackID = 0xAB;
	else if ( version_D2Game >= V111 )
		customPackID++;

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/