/*=================================================================
	File created by Yohann NICOLAS.

	Gestion of the infinity and shared Stash.

=================================================================*/


#include "common.h"
#include "infinityStash.h"
#include "error.h"
#include "d2functions.h"
#include "updateClient.h"
#include "interface_Stash.h"

#define STASH_TAG 0x5453			//"ST"
#define JM_TAG 0x4D4A 				//"JM"

DWORD maxSelfPages = -1;
DWORD maxSharedPages = -1;
DWORD nbPagesPerIndex = 10;
DWORD nbPagesPerIndex2 = 100;
bool active_multiPageStash = false;
bool active_sharedStash = false;
bool separateHardSoftStash = false;
bool active_sharedGold=false;
char* sharedStashFilename = NULL;

typedef int (*TchangeToSelectedStash)(Unit* ptChar, Stash* newStash, DWORD bOnlyItems, DWORD bIsClient);

Unit* firstClassicStashItem(Unit* ptChar)
{
	Unit* ptItem = D2InventoryGetFirstItem(PCInventory);
	while (ptItem)
	{
		if (D2ItemGetPage(D2GetRealItem(ptItem)) == 4)
			return ptItem;
		ptItem = D2UnitGetNextItem(ptItem);
	}
	return NULL;
}

DWORD endStashList(Unit* ptChar, Stash* ptStash)//WORKS
{
	Stash* stash = ptStash;
	
	while (stash)
	{
		if (stash->ptListItem || ((stash == PCPY->currentStash) && firstClassicStashItem(ptChar))) return 0;
		stash = stash->nextStash;	
	}
	return 1;
}

//bool isInList(Stash* list, Stash* pStash)
//{
//	Stash* ptStash = list;
//	while(ptStash)
//	{
//		if (ptStash->id == pStash->id) return true;
//		ptStash = ptStash->nextStash;
//	}
//	return false;
//}


Stash* getLastStash(Stash* ptStash)//WORKS
{
	Stash* stash = ptStash;
	
	if (!stash) return NULL;
	while (stash->nextStash)
		stash = stash->nextStash;
	
	return stash;
}

Stash* newStash(DWORD id)
{
	d2_assert( id == 0xFFFFFFFF , "trop de stash", __FILE__, __LINE__);
	
	Stash* stash = (Stash*)malloc(sizeof(Stash));//D2AllocMem(memPool, sizeof(Stash),__FILE__,__LINE__,0);
	d2_assert(!stash , "pb de génération de stash", __FILE__, __LINE__);
	ZeroMemory(stash, sizeof(Stash));
	stash->id = id;
	
	return stash;
}

Stash* addStash(Unit* ptChar, bool isShared)
{
	Stash* previous;
	Stash* stash;
//	DWORD memPool = PCGame ? PCGame->memoryPool :0;
	if (isShared)
	{
		previous = getLastStash(PCPY->sharedStash);
		stash = newStash(PCPY->nbSharedPages++);
	} else {
		previous = getLastStash(PCPY->selfStash);
		stash = newStash(PCPY->nbSelfPages++);
	}
	
	stash->isShared = isShared;
	stash->previousStash = previous;
	if (previous)
		previous->nextStash = stash;
	else if (isShared)
		PCPY->sharedStash = stash;
	else
		PCPY->selfStash = stash;
	
	log_msg("AddStash: stash->id=%d\tstash->isShared=%d\tstash->previous=%08X\tnbSelf=%d\tnbShared=%d\n",
		stash->id,stash->isShared,stash->previousStash,PCPY->nbSelfPages,PCPY->nbSharedPages);
	
	return stash;
}

Stash* getStash(Unit* ptChar, DWORD isShared, DWORD id)//WORKS
{
	Stash* ptStash = isShared ? PCPY->sharedStash : PCPY->selfStash;

	while(ptStash)
	{
		if (ptStash->id == id) return ptStash;
		ptStash = ptStash->nextStash;
	}

	return NULL;
}


int changeToSelectedStash_9(Unit* ptChar, Stash* newStash, DWORD bOnlyItems, DWORD bIsClient)
{
	if (!newStash) return 0;

	log_msg("changeToSelectedStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n", newStash->id, newStash->isShared, bOnlyItems, bIsClient);

	Stash* currentStash = PCPY->currentStash;
	if (currentStash == newStash) return 0;

	d2_assert( currentStash && currentStash->ptListItem, "ERROR : currentStash isn't empty (ptListItem != NULL)",__FILE__,__LINE__);

	// collect items to remove
	Inventory* ptInventory = PCInventory;
	Unit* ptNextItem;
	Unit* ptPrevItem = NULL;
	Unit* ptItem = D2InventoryGetFirstItem(ptInventory);
	while (ptItem)
	{
		ptNextItem = D2UnitGetNextItem(ptItem);
		if (D2ItemGetPage(D2GetRealItem(ptItem)) == 4)
		{
			D2SetAnim(D2GetRealItem(ptItem),-1);
			if (ptPrevItem)	{
				ptPrevItem->CurrentAnim = (DWORD)ptNextItem;//is ptPrevItem->nextNode = ptNextItem;
			} else {
				ptInventory->currentUsedSocket = (DWORD)ptNextItem;//is ptInventory->ptListItem = ptNextItem;
			}
			if (!ptNextItem)
				ptInventory->Inventory2C = (DWORD)ptPrevItem;

			ptInventory->Inventory30 = ptInventory->Inventory30 - 1;
			D2Common10250(__FILE__,__LINE__,ptInventory, D2GetPosX(D2GetRealItem(ptItem)), D2GetPosY(D2GetRealItem(ptItem)), 0xC, bIsClient, 4);
//			ptItem = D2InvRemoveItem(PCInventory, D2GetRealItem(ptItem));
//			D2Common10250(__FILE__,__LINE__,PCInventory, D2GetPosX(ptItem), D2GetPosY(ptItem), 0xC, bIsClient, 4);
			if (currentStash)
			{
//				ptItem = setNextItem(ptItem, PCPY->currentStash->ptListItem);
				ptItem->CurrentAnim = (DWORD)currentStash->ptListItem;//is ptItem->nextNode = ptListItem
				currentStash->ptListItem = ptItem;
			};
		} else ptPrevItem = ptItem;
		ptItem = ptNextItem;
	}

	// add items of new stash
	ptItem = newStash->ptListItem;
	while (ptItem)
	{
		D2InvAddItem(PCInventory, D2GetRealItem(ptItem), D2GetPosX(D2GetRealItem(ptItem)), D2GetPosY(D2GetRealItem(ptItem)), 0xC, bIsClient, 4);
		D2Common10242(PCInventory, D2GetRealItem(ptItem), 1);
		ptItem = D2UnitGetNextItem(ptItem);
	}
	if (bOnlyItems)
		newStash->ptListItem = PCPY->currentStash->ptListItem;
	else
		PCPY->currentStash = newStash;
	PCPY->currentStash->ptListItem = NULL;

	return 1;
}

int changeToSelectedStash_10(Unit* ptChar, Stash* newStash, DWORD bOnlyItems, DWORD bIsClient)
{
	if (!newStash) return 0;

	log_msg("changeToSelectedStash ID:%d\tshared:%d\tonlyItems:%d\tclient:%d\n",newStash->id,newStash->isShared, bOnlyItems,bIsClient);

	Stash* currentStash = PCPY->currentStash;
	if (currentStash == newStash) return 0;

	d2_assert( currentStash && currentStash->ptListItem, "ERROR : currentStash isn't empty (ptListItem != NULL)",__FILE__,__LINE__);

	// Remove items from current page
	Unit* ptNextItem;
	Unit* ptItem = D2InventoryGetFirstItem(PCInventory);
	while (ptItem)
	{
		ptNextItem = D2UnitGetNextItem(ptItem);
		if (D2ItemGetPage(ptItem) == 4)
		{
			BYTE tmp = ptItem->ptItemData->ItemData2;
			ptItem = D2InvRemoveItem(PCInventory, ptItem);
			ptItem->ptItemData->ItemData2 = tmp;
			if (currentStash)
			{
				ptItem->ptItemData->ptNextItem = currentStash->ptListItem;
				currentStash->ptListItem = ptItem;
			}
		}
		ptItem = ptNextItem;
	}

	// add items of new stash
	ptItem = newStash->ptListItem;
	while (ptItem)
	{
		D2InvAddItem(PCInventory, ptItem, ptItem->path->x, ptItem->path->y, 0xC, bIsClient, 4);
		ptItem = D2UnitGetNextItem(ptItem);
	}
	if (bOnlyItems)
		newStash->ptListItem = PCPY->currentStash->ptListItem;
	else
		PCPY->currentStash = newStash;
	PCPY->currentStash->ptListItem = NULL;

	return 1;
}

TchangeToSelectedStash changeToSelectedStash;


DWORD loadStash(Unit* ptChar, Stash* ptStash, BYTE data[], DWORD startSize, DWORD maxSize, DWORD* retSize)
{
	DWORD curSize = startSize;
	DWORD nbBytesRead;

	log_msg("loadStash\n");

	*retSize = curSize;
	if( *(WORD *)&data[curSize] != STASH_TAG )//"ST"
	{
		log_msg("loadStash -> Bad tag of stash of character %s : %04X\n",PCPlayerData->name,*(WORD *)&data[curSize]);
		return 0x7;//Unable to enter game. Bad inventory data
	}
	curSize += 2;

//	if (strlen((char *)&data[curSize]) > 0xF)
//		*(char *)&data[curSize+0xF] = NULL;
	if (strlen((char *)&data[curSize]))
		ptStash->name = (char*)malloc(strlen((char *)&data[curSize]));//D2AllocMem(PCGame->memoryPool, strlen((char *)&data[curSize]),__FILE__,__LINE__,0);
	if (ptStash->name)
		strcpy(ptStash->name, (char *)&data[curSize]);
	curSize += strlen((char *)&data[curSize]) + 1;

	DWORD ret = D2LoadInventory(PCGame, ptChar, (saveBitField*)&data[curSize], 0x60, maxSize-curSize, 0, &nbBytesRead);
	if (ret) log_msg("loadStash -> D2LoadInventory failed\n");
	log_msg("Stash loaded (%d : %s)\n", ptStash->id ,ptStash->name);

	*retSize=curSize + nbBytesRead;
	return ret;
}

DWORD loadStashList(Unit* ptChar, BYTE data[], DWORD maxSize, DWORD* curSize, bool isShared)//WORKS
{
	DWORD curStash = 0;
	Stash* newStash;

	DWORD nbStash = *(DWORD*)&data[*curSize];
	*curSize += 4;

	while (curStash < nbStash)
	{
		newStash = addStash(ptChar, isShared);
		changeToSelectedStash(ptChar, newStash, 0, false);
		DWORD ret = loadStash(ptChar, newStash, data, *curSize, 10000000, curSize);
		if (ret) return ret;
		curStash++;
	}

	if (!isShared && !PCPY->selfStash)
	{
		newStash = addStash(ptChar, isShared);
		PCPY->currentStash = newStash;
	}
	
	if (isShared && !PCPY->sharedStash)
	{
		newStash = addStash(ptChar, isShared);
		if (!PCPY->currentStash)
			PCPY->currentStash = newStash;
	}

	return 0;
}

//ADDDATA(DWORD, curSize, 0);

#define DATA (*data + *curSize)
#define ADDDATA(T)		(T*)DATA;		*curSize += sizeof(T)
#define SETDATA(T,V)	*(T*)DATA = V;	*curSize += sizeof(T)

void saveStash(Unit* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	//write "ST"
	SETDATA(WORD, STASH_TAG);

	//save name
	if (ptStash->name)
	{
		int size = strlen(ptStash->name);
		if (size > 15) size = 15;
		strncpy((char*)DATA, ptStash->name, size);
		*curSize += size;
	}
	SETDATA(char, NULL);

	//Write "JM" of inventory
	SETDATA(WORD, JM_TAG);

	//Get position of counter of items in inventory
	WORD* ptNBItem = ADDDATA(WORD);
	*ptNBItem = 0;

	//Get first item
	Unit* ptItem;
	if ((ptStash->id == PCPY->currentStash->id) && (ptStash->isShared == PCPY->currentStash->isShared))
		ptItem = D2InventoryGetFirstItem(PCInventory);
	else
		ptItem = ptStash->ptListItem;

	//Write all items
	while (ptItem)
	{
		if (D2ItemGetPage(D2GetRealItem(ptItem)) == 4)
		{
			int nbBytes = D2SaveItem(D2GetRealItem(ptItem), (saveBitField*)DATA, *maxSize - *curSize, 1, 1, 0);
			d2_assert(!nbBytes, "!\"Character has too many items\"", __FILE__, __LINE__ );
			*curSize += nbBytes;
			(*ptNBItem)++;
		}
		ptItem = D2UnitGetNextItem(ptItem);
	}
}


void saveStashList(Unit* ptChar, Stash* ptStash, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	DWORD curSizeNbStash = *curSize;
	*curSize += sizeof(DWORD);

	DWORD nbStash=0;

	while(ptStash)
	{
		if (*curSize + 0x2000 > *maxSize)
		{
			BYTE* oldData = *data;
			*maxSize *= 2;
			*data = (BYTE *)D2AllocMem(PCGame->memoryPool, *maxSize,__FILE__,__LINE__,0);
			d2_assert(!*data, "Error : Memory allocation", __FILE__, __LINE__);
			CopyMemory(*data, oldData, *curSize);
			D2FreeMem(PCGame->memoryPool, oldData,__FILE__,__LINE__,0);
		}
		saveStash(ptChar, ptStash, data, maxSize, curSize);
		nbStash++;
		ptStash = endStashList(ptChar, ptStash->nextStash) ? NULL : ptStash->nextStash;
	}
	*(DWORD*)(*data + curSizeNbStash) = nbStash;
}

/////// client
void updateSelectedStashClient(Unit* ptChar)//WORKS
{
	Stash* newStash = PCPY->currentStash;
	updateClient(ptChar, UC_SELECT_STASH, newStash->id, newStash->flags, PCPY->flags);
}

void setSelectedStashClient(DWORD stashId, DWORD stashFlags, DWORD flags)//WORKS
{
	log_msg("setSelectedStashClient ID:%d, stashFlags:%d, flags:%08X\n", stashId, stashFlags, flags);
	Unit* ptChar = D2GetClientPlayer();
	Stash* newStash = getStash(ptChar, (stashFlags & 1) == 1, stashId);
	if (!newStash) do
		newStash = addStash(ptChar, (stashFlags & 1) == 1);
	while (newStash->id < stashId);
	changeToSelectedStash(ptChar, newStash, (stashFlags & 2) == 2, 1);
	PCPY->flags = flags;
}


void selectStash(Unit* ptChar, Stash* newStash)//WORKS
{
	changeToSelectedStash(ptChar, newStash, 0, 0);
	updateSelectedStashClient(ptChar);
}



///// public functions
void toggleToSelfStash(Unit* ptChar)
{
	Stash* selStash = PCPY->selfStash;
	if (selStash && (selStash != PCPY->currentStash))
	{
		PCPY->showSharedStash = false;
		selectStash(ptChar, selStash);
	}
}

void toggleToSharedStash(Unit* ptChar)
{
	Stash* selStash = PCPY->sharedStash;
	if (selStash && (selStash != PCPY->currentStash))
	{
		PCPY->showSharedStash = true;
		selectStash(ptChar, selStash);
	}
}

void swapStash(Unit* ptChar, Stash* curStash, Stash* swpStash)
{
	if (!ptChar || !curStash || !swpStash || curStash == swpStash)
		return;
	changeToSelectedStash(ptChar, swpStash, 1, 0);
	updateClient(ptChar, UC_SELECT_STASH, swpStash->id, swpStash->flags | 2, PCPY->flags);
}

void toggleStash(Unit* ptChar, DWORD page)
{
	log_msg("toggle stash page = %u\n", page);
	Stash* curStash = PCPY->currentStash;
	Stash* swpStash = curStash->isShared ? PCPY->selfStash : PCPY->sharedStash;
	swapStash(ptChar, curStash, swpStash);
}

void swapStash(Unit* ptChar, DWORD page, bool toggle)
{
	log_msg("swap stash page = %u\n", page);
	Stash* curStash = PCPY->currentStash;
	Stash* swpStash = curStash->isShared == toggle ? PCPY->selfStash : PCPY->sharedStash;
	for (DWORD i = 0; i < page; i++)
	{
		if (curStash->nextStash == NULL)
			addStash(ptChar, swpStash->isShared);
		swpStash = swpStash->nextStash;
	}
	swapStash(ptChar, curStash, swpStash);
}

void selectPreviousStash(Unit* ptChar)
{
	Stash* selStash = PCPY->currentStash->previousStash;
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}


void selectPrevious2Stash(Unit* ptChar)// Select first stash
{
	Stash* selStash = PCPY->showSharedStash ? PCPY->sharedStash : PCPY->selfStash;
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectNextStash(Unit* ptChar)
{
	Stash* selStash = PCPY->currentStash;
	if (!selStash->isShared && (selStash->id >= maxSelfPages))	return;
	if (selStash->isShared && (selStash->id >= maxSharedPages)) return;
	
	selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, PCPY->showSharedStash);

	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}


void selectNext2Stash(Unit* ptChar)//select last stash
{
	Stash* selStash = PCPY->showSharedStash ? PCPY->sharedStash : PCPY->selfStash;//PCPY->currentStash;
	Stash* lastStash = NULL;
	Unit* currentStashItem = firstClassicStashItem(ptChar);
	while (selStash)
	{
		if (selStash->ptListItem || (selStash == PCPY->currentStash) && currentStashItem) lastStash=selStash;
		selStash = selStash->nextStash;
	}
	if (!lastStash)
		lastStash = PCPY->showSharedStash ? PCPY->sharedStash : PCPY->selfStash;
	if (lastStash != PCPY->currentStash)
		selectStash(ptChar, lastStash);
}

void selectPreviousIndexStash(Unit* ptChar)
{
	selectPreviousStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while (selStash->previousStash && ((selStash->id+1) % nbPagesPerIndex != 0))
		selStash = selStash->previousStash;

	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectPreviousIndex2Stash(Unit* ptChar)
{
	selectPreviousStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while (selStash->previousStash && ((selStash->id+1) % nbPagesPerIndex2 != 0))
		selStash = selStash->previousStash;

	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectNextIndexStash(Unit* ptChar)
{
	selectNextStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while ((selStash->id+1) % nbPagesPerIndex != 0)
	{
		if (!selStash->isShared && (selStash->id >= maxSelfPages))	break;
		if (selStash->isShared && (selStash->id >= maxSharedPages)) break;
		selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, PCPY->showSharedStash);;
	}
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

void selectNextIndex2Stash(Unit* ptChar)
{
	selectNextStash(ptChar);
	Stash* selStash = PCPY->currentStash;
	while ((selStash->id+1) % nbPagesPerIndex2 != 0)
	{
		if (!selStash->isShared && (selStash->id >= maxSelfPages))	break;
		if (selStash->isShared && (selStash->id >= maxSharedPages)) break;
		selStash = selStash->nextStash ? selStash->nextStash : addStash(ptChar, PCPY->showSharedStash);;
	}
	if (selStash && (selStash != PCPY->currentStash))
		selectStash(ptChar, selStash);
}

//////////////////////////////////////////////////////////////////////
Stash* curStash2;
DWORD currentSawStash2;

Unit* STDCALL getNextItem(Unit* ptChar, Unit* ptItem)
{
	Unit* item = D2UnitGetNextItem(ptItem);
	if (item) return item;

	if (!curStash2)
	{
		switch (currentSawStash2)
		{
		case 0: curStash2 = PCPY->selfStash;
				currentSawStash2 = 1;
				break;
		case 1: curStash2 = PCPY->sharedStash;
				currentSawStash2 = 2;
				break;
		default: return NULL;//case 2:
		}
	} else {
		curStash2 = curStash2->nextStash;
	}
	if (curStash2)
	{
		item = curStash2->ptListItem;
		if (item) return item;
	}
	return getNextItem(ptChar,item);
}

Unit* STDCALL initGetNextItem(Unit* ptChar, Unit* ptItem)
{
	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPY) return NULL;

	curStash2 = NULL;
	currentSawStash2 = 0;
	if (ptItem) return ptItem;
	return getNextItem(ptChar,ptItem);
}

FCT_ASM ( caller_initGetNextItem )
	PUSH DWORD PTR SS:[ESP+0x20]
	PUSH DWORD PTR SS:[ESP+0xC]
	CALL initGetNextItem
	MOV EDI,EAX
	TEST EDI,EDI
	RETN
}}


FCT_ASM ( caller_getNextItem )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x10]
	CALL getNextItem
	RETN 4
}}


DWORD STDCALL carry1Limit(Unit* ptChar, Unit* ptItemParam, DWORD itemNum, BYTE page)
{
	if (!ptChar) return 0;
	Unit* ptItem = ptItemParam ? ptItemParam : D2GameGetObject(PCGame, UNIT_ITEM, itemNum);
	if ((page != 4) && (D2GetItemQuality(ptItem) == 7) && ptChar)
	{
		int uniqueID = D2GetUniqueID(ptItem);
		if ((uniqueID>=0) && (uniqueID < (int)SgptDataTables->nbUniqueItems))
		{
			UniqueItemsBIN*	uniqueItems = SgptDataTables->uniqueItems + uniqueID;
			if (uniqueItems && (uniqueItems->carry1==1))
			{
				ItemsBIN* ptItemsBin = D2GetItemsBIN(ptItem->nTxtFileNo);
				Unit* ptFirstItem = D2InventoryGetFirstItem(PCInventory);
				if (ptItemsBin && ptFirstItem)
					return D2VerifIfNotCarry1(ptItem, ptItemsBin, ptFirstItem);
			}
		}
	}
	return 0;
}

FCT_ASM ( caller_carry1Limit_111 )
	PUSH DWORD PTR SS:[ESP+0x08]//page
	PUSH 0//EDI
	PUSH DWORD PTR SS:[ESP+0x0C]
	PUSH ESI//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	JNZ	end_carry1Limit
	JMP D2ItemSetPage
end_carry1Limit:
	ADD ESP,0xC
	XOR EAX,EAX
	POP EDI
	POP EBX
	POP ESI
	POP EBP
	RETN 8
}}

FCT_ASM ( caller_carry1Limit )
	PUSH DWORD PTR SS:[ESP+0x08]//page
	PUSH 0//EBP
	PUSH DWORD PTR SS:[ESP+0x0C]
	PUSH DWORD PTR SS:[ESP+0x28]//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	JNZ	end_carry1Limit
	JMP D2ItemSetPage
end_carry1Limit:
	ADD ESP,0xC
	POP EDI
	POP ESI
	POP EBP
	XOR EAX,EAX
	POP EBX
	ADD ESP,0x24
	RETN 8
}}

FCT_ASM ( caller_carry1LimitSwap_112 )
	PUSH EAX
	PUSH DWORD PTR SS:[ESP+0x1C]
	PUSH 0
	PUSH ESI//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	JNZ	end_carry1Limit
	JMP D2ItemGetPage
end_carry1Limit:
	ADD ESP,8
	XOR EAX,EAX
	POP EDI
	POP EBP
	POP ESI
	POP EBX
	POP ECX
	RETN 8
}}

FCT_ASM ( caller_carry1LimitSwap_111 )
	PUSH EAX
	PUSH EBP
	PUSH 0
	PUSH DWORD PTR SS:[ESP+0x24]//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	JNZ	end_carry1Limit
	JMP D2ItemGetPage
end_carry1Limit:
	ADD ESP,8
	XOR EAX,EAX
	POP EDI
	POP EBP
	POP ESI
	POP EBX
	POP ECX
	RETN 8
}}

FCT_ASM ( caller_carry1LimitSwap )
	PUSH EAX
	PUSH DWORD PTR SS:[ESP+0x20]
	PUSH 0
	PUSH EBP//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	JNZ	end_carry1Limit
	JMP D2ItemGetPage
end_carry1Limit:
	ADD ESP,8
	POP EDI
	POP ESI
	POP EBP
	XOR EAX,EAX
	POP EBX
	ADD ESP,0x4C
	RETN 8
}}

/*
FCT_ASM ( caller_carry1LimitWhenDrop )
	PUSH EAX
	PUSH 0
	PUSH ESI//ptItem
	PUSH EDI//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	POP EAX
	JE END_carry1LimitWhenDrop
	MOV EDX,0x806
	RETN
END_carry1LimitWhenDrop:
	ADD DWORD PTR SS:[ESP],0x1F
	RETN
}}*/

FCT_ASM ( caller_carry1LimitWhenDrop_111 )
	PUSH 0
	PUSH 0
	PUSH DWORD PTR SS:[ESP+0x10] //ptItem
	PUSH ESI //ptChar
	CALL carry1Limit
	TEST EAX,EAX
	JNZ	end_carry1Limit
	JMP D2CanPutItemInInv
end_carry1Limit:
	XOR EAX,EAX
	RETN 0x1C
}}
/*
FCT_ASM ( caller_carry1LimitWhenDrop )
	PUSH 0
	PUSH 0
	PUSH DWORD PTR SS:[ESP+0x10] //ptItem
	PUSH EDI //ptChar
	CALL carry1Limit
	JNZ	end_carry1Limit
	JMP D2CanPutItemInInv
end_carry1Limit:
	XOR EAX,EAX
	RETN 0x1C
}}*/


FCT_ASM ( caller_carry1LimitWhenDrop )
	PUSH EAX
	PUSH 0
	PUSH 0
	PUSH ESI//ptItem
	PUSH EDI//ptChar
	CALL carry1Limit
	TEST EAX,EAX
	POP EAX
	JNZ END_carry1LimitWhenDrop
	MOV EDX,0x806
	RETN
END_carry1LimitWhenDrop:
	ADD DWORD PTR SS:[ESP],0x1F
	RETN
}}

FCT_ASM ( caller_carry1OutOfStash_111 )
	PUSH EDI
	CALL D2ItemGetPage
	CMP AL,4
	JNZ continue_carry1OutOfStash
	ADD DWORD PTR SS:[ESP],0x17C
	RETN
continue_carry1OutOfStash:
	MOV ESI,DWORD PTR SS:[ESP+0x10]
	TEST ESI,ESI
	RETN
}}

FCT_ASM ( caller_carry1OutOfStash )
	PUSH ESI
	CALL D2ItemGetPage
	CMP AL,4
	JNZ continue_carry1OutOfStash
	ADD DWORD PTR SS:[ESP],0x1AF
	RETN
continue_carry1OutOfStash:
	MOV EAX,DWORD PTR SS:[ESP+0x14]
	TEST EAX,EAX
	RETN
}}


void Install_MultiPageStash()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlayerCustomData();
	Install_InterfaceStash();

	changeToSelectedStash = version_D2Common >= V110 ? changeToSelectedStash_10 : changeToSelectedStash_9;

	if ( version_D2Game >= V110 )
	{
		log_msg("Patch D2Game for carry1 unique item. (MultiPageStash)\n");

		// Cannot put 2 items carry1 in inventory
		mem_seek R7(D2Game, 0000, 0000, 55050, 57CA3, 2FE63, 99B03, CF1E3);
		MEMJ_REF4( D2ItemSetPage , version_D2Game >= V111 ? caller_carry1Limit_111 : caller_carry1Limit);
		//6FC8504F   . E8 94670900    CALL <JMP.&D2Common.#10720>
		//01FD7CA2   . E8 6329FBFF    CALL <JMP.&D2Common.#10485>
		//01F9FE62   . E8 47A8FDFF    CALL <JMP.&D2Common.#10608>
		//6FCB9B02   . E8 9709F7FF    CALL <JMP.&D2Common.#10223>
		//6FCEF1E2   . E8 47B7F3FF    CALL <JMP.&D2Common.#10012>

		// Cannot put 2 items carry1 in inventory by swapping
		mem_seek R7(D2Game, 0000, 0000, 558D9, 58968, 310E8, 9B6E8, D10C8);
		MEMJ_REF4( D2ItemGetPage , version_D2Game >= V112 ? caller_carry1LimitSwap_112 : version_D2Game >= V111 ? caller_carry1LimitSwap_111 : caller_carry1LimitSwap);
		//6FC858D8   . E8 175F0900    CALL <JMP.&D2Common.#10719>
		//01FD8967   . E8 8E1DFBFF    CALL <JMP.&D2Common.#10820>
		//01FA10E7   . E8 9A96FDFF    CALL <JMP.&D2Common.#10505>
		//6FCBB6E7   . E8 CAEDF6FF    CALL <JMP.&D2Common.#10370>
		//6FCF10C7   . E8 F895F3FF    CALL <JMP.&D2Common.#10020>

		if ( version_D2Game >= V111 )
		{
			// Cannot put 2 items carry1 in inventory when drop cube
			mem_seek R7(D2Game, 0000, 0000, 0000, 3D935, 49FD5, 17AD5, D7B75);
			MEMJ_REF4( D2CanPutItemInInv , caller_carry1LimitWhenDrop_111);
			//01FBD934  |. E8 5BD3FCFF    |CALL <JMP.&D2Common.#10855>
			//01FB9FD4  |. E8 3912FCFF    |CALL <JMP.&D2Common.#10813>
			//6FC37AD4  |. E8 0535FFFF    |CALL <JMP.&D2Common.#10289>
			//6FCF7B74  |. E8 232FF3FF    |CALL <JMP.&D2Common.#10133>
		} else {
			// Cannot put 2 items carry1 in inventory when drop cube
			mem_seek R7(D2Game, 0000, 0000, 14341, 0000, 0000, 0000, 0000);
			memt_byte( 0xBA ,0xE8);
			MEMT_REF4( 0x00000806 , caller_carry1LimitWhenDrop);
			//6FC44341  |. BA 06080000    |MOV EDX,806
		}

		// Verif only carry1 out of stash page when pick up an item
		mem_seek R7(D2Game, 0000, 0000, 1299E, 38E3B, 43F0B, 1209B, D211B);
		memt_byte( 0x8B ,0xE8);
		MEMT_REF4( version_D2Game >= V111 ? 0x850C2474 : 0x85102444 , version_D2Game >= V111 ? caller_carry1OutOfStash_111 : caller_carry1OutOfStash);
		memt_byte( version_D2Game >= V111 ? 0xF6 : 0xC0 ,0x90);
		//6FC4299E  |. 8B4424 10      |MOV EAX,DWORD PTR SS:[ESP+10]
		//6FC429A2  |. 85C0           |TEST EAX,EAX
		//01FB8E3B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
		//01FB8E3F  |. 85F6           |TEST ESI,ESI
		//01FB3F0B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
		//01FB3F0F  |. 85F6           |TEST ESI,ESI
		//6FC3209B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
		//6FC3209F  |. 85F6           |TEST ESI,ESI
		//6FCF211B  |. 8B7424 0C      |MOV ESI,DWORD PTR SS:[ESP+C]
		//6FCF211F  |. 85F6           |TEST ESI,ESI

		log_msg("\n");
	}

	isInstalled = true;
}


/*================================= END OF FILE =================================*/