/*=================================================================
	File created by Yohann NICOLAS.

	Updating client.
 
=================================================================*/

#include "common.h"
#include "updateClient.h"
#include "error.h"
#include "d2functions.h"

#include "infinityStash.h"
#include "commands.h"


void updateClient(Unit* ptChar, DWORD mFunc, DWORD p1, DWORD p2, DWORD p3)
{
	void* ptNetClient;
	DataPacket packet;

	// Intialize the packet to send to client
	ZeroMemory(&packet, sizeof(DataPacket));
	packet.mType = 0x9D;
	packet.mFunc = (BYTE)mFunc;
	packet.mSize = sizeof(DataPacket);
	packet.mPlayerID = ptChar->nUnitId;
	packet.mParam1 = p1;
	packet.mParam2 = p2;
	packet.mParam3 = p3;

	ptNetClient = D2GetClient( ptChar, __FILE__ , __LINE__);

	// Send packet to client for remove placed skills
	D2SendPacket(ptNetClient, &packet, sizeof(DataPacket));
}

DWORD FASTCALL handleClientUpdate(DataPacket* packet)
{
	log_msg("[CLIENT] Received custom message: %d with param: %08X , %08X , %08X\n",packet->mFunc,packet->mParam1,packet->mParam2,packet->mParam3);
	switch (packet->mFunc)
	{
	case UC_SELECT_STASH :	 setSelectedStashClient(packet->mParam1,packet->mParam2,packet->mParam3); return 1;
	case UC_SHARED_GOLD :	 updateSharedGold(packet->mParam1); return 1;
	default : return 0;
	}
}


FCT_ASM ( caller_handleClientUpdate_111 )
	LEA ECX,DWORD PTR SS:[ESP+8]
	CALL handleClientUpdate
	POP EDI
	POP ESI
	MOV ESP,EBP
	POP EBP
	RETN
}}

FCT_ASM ( caller_handleClientUpdate )
	LEA ECX,DWORD PTR SS:[ESP]
	CALL handleClientUpdate
	ADD ESP,0x104
	RETN
}}


void Install_UpdateClient()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2Client for received Item packet. (UpdateClient)\n");

	// execute if it's our packet else continue
	mem_seek R7(D2Client, 14236, 14226, 145B6, 9C6B6, BFE86, 66E06, AE896);
	MEMT_REF4( version_D2Client >= V111  ? 0x000000CF : 0x000000D6, version_D2Client >= V111 ? caller_handleClientUpdate_111 : caller_handleClientUpdate);
	//6FAB45B4  |. 0F87 D6000000  JA D2Client.6FAB4690
	//6FB4C6B4  |. 0F87 CF000000  JA D2Client.6FB4C789
	//6FB6FE84  |. 0F87 CF000000  JA D2Client.6FB6FF59
	//6FB16E04  |. 0F87 CF000000  JA D2Client.6FB16ED9
	//6FB5E894  |. 0F87 CF000000  JA D2Client.6FB5E969

	log_msg("\n");

	isInstalled = true;
}

/*================================= END OF FILE =================================*/