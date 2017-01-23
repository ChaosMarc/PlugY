/*=================================================================
	File created by Yohann NICOLAS.

	Cube Listing functions

=================================================================*/

#include "updateClient.h"
#include "common.h"
#include <stdio.h>
#include <direct.h>			// _getcwd()


const char* CUBEFORMULA_FILE = "cube.txt";
const LPCWSTR STRING_ERROR = L"***Error***";
bool InNoSocket;

#define BUF (&buf[*len])
#define PRINT *len += swprintf

/*
6FC9275F  |. E8 ECCCFFFF    |CALL D2Game.6FC8F450                    ; \D2Game.6FC8F450
*/
void printOutputItem(CubeOutput* output, LPWSTR buf, LPINT len, LPINT nbOutputs)
{
	if (output->outputType == 0)
		return;
	if (*nbOutputs > 0)
		PRINT(BUF, L" + ");
	*nbOutputs += 1;

	if (output->outputType == 1) {
		PRINT(BUF, getLocalString(STR_COW_PORTAL));
		return;
	} else if (output->outputType == 2) {
		PRINT(BUF, getLocalString(STR_PANDEMONIUM_PORTAL));
		return;
	} else if (output->outputType == 3) {
		PRINT(BUF, getLocalString(STR_PANDEMONIUM_FINAL_PORTAL));
		return;
	}

	if ((output->quantityOrNbSockets>1) && !output->haveSockets)
	{
		if (output->quantityOrNbSockets = 255)
			PRINT(BUF, L"%s ", getLocalString(STR_FULL));
		else
			PRINT(BUF, L"%u ", output->quantityOrNbSockets);
	}

	if (output->repair)
		PRINT(BUF, L"%s ", getLocalString(STR_REPAIR));

	if (output->repair && output->recharge)
		PRINT(BUF, L"%s ", getLocalString(STR_AND));

	if (output->recharge)
		PRINT(BUF, L"%s ", getLocalString(STR_RECHARGE));

	if (output->destroysFillers)
		PRINT(BUF, L"%s ", getLocalString(STR_DESTROY_FILLERS));

	if (output->removeFillers)
		PRINT(BUF, L"%s ", getLocalString(STR_REMOVE_FILLERS));

	if (output->regeneratesUnique)
		PRINT(BUF, L"%s ", getLocalString(STR_REGENERATE));

	if (output->upgradeToExceptional)
		PRINT(BUF, L"%s ", getLocalString(STR_UPGRADE_TO_EXCEPTIONAL));

	if (output->upgradeToElite)
		PRINT(BUF, L"%s ", getLocalString(STR_UPGRADE_TO_ELITE));

	if (output->isEthereal)
		PRINT(BUF, L"%s ", getLocalString(STR_ETHERAL));

	if (output->isSpecificItem) {
		if (output->quality == ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* uniqueItems = SgptDataTables->uniqueItems + output->specificID-1;
			PRINT(BUF, D2GetStringFromIndex(uniqueItems->uniqueNameId));
		} else if (output->quality == ITEMQUALITY_SET) {
			SetItemsBIN* setItems = SgptDataTables->setItems + output->specificID-1;
			PRINT(BUF, D2GetStringFromIndex(setItems->setNameId));
		} else {
			PRINT(BUF,STRING_ERROR);return;
		}
	} else {
		switch (output->quality)
		{
			case 1:PRINT(BUF, L"%s ", getLocalString(STR_CRACKED));break;
			case 2:PRINT(BUF, L"%s ", getLocalString(STR_NORMAL));break;
			case 3:PRINT(BUF, L"%s ", getLocalString(STR_SUPERIOR));break;
			case 4:PRINT(BUF, L"%s ", getLocalString(STR_MAGIC));break;
			case 5:PRINT(BUF, L"%s ", getLocalString(STR_SET));break;
			case 6:PRINT(BUF, L"%s ", getLocalString(STR_RARE));break;
			case 7:PRINT(BUF, L"%s ", getLocalString(STR_UNIQUE));break;
			case 8:PRINT(BUF, L"%s ", getLocalString(STR_CRAFTED));break;
			case 9:PRINT(BUF, L"%s ", getLocalString(STR_TEMPERED));break;
		}
		switch (output->outputType)
		{
		case 0xFC:
		{
			ItemsBIN* items = D2GetItemsBIN(output->ID);
			PRINT(BUF, StripGender(D2GetStringFromIndex(items->NameStr)));
			break;
		}
		case 0xFD:
		{
			ItemTypesBIN* itemTypeData = D2GetItemTypesBIN(output->ID);
			if (!itemTypeData)
				PRINT(BUF, L"Unknow Item Type");
			else
				PRINT(BUF, getLocalTypeString(itemTypeData->code));
			break;
		}
		case 0xFE: PRINT(BUF, L"%s", getLocalString(STR_ITEM)); break;
		case 0xFF: PRINT(BUF, L"%s", getLocalString(STR_ITEM_SAME_TYPE)); break;
		default: PRINT(BUF, L"%s ", STRING_ERROR); return;
		}
	}
	if (output->haveSockets == 1 || InNoSocket)
	{
		PRINT(BUF, L" ");
		if (output->quantityOrNbSockets >= 1)
			PRINT(BUF, getLocalString(STR_WITH_N_SOCKETS), output->quantityOrNbSockets);
//		else if (output->quantityOrNbSockets == 1)
	//			PRINT(BUF, getLocalString(STR_WITH_ONE_SOCKET));
		else
			PRINT(BUF, getLocalString(STR_WITH_SOCKETS));
	}
}


void printInputItem(CubeInput* input, LPWSTR buf, LPINT len, LPINT nbInputs)//maxsize)
{
	if (!input->byItemID && !input->byItemTypeID)
		return;
	if (*nbInputs)
		PRINT(BUF, L" + ");

	BYTE nb = input->quantity > 0 ? input->quantity : 1;
	*nbInputs += nb;
	if (nb > 1)
		PRINT(BUF, L"%u ", nb);

	if (input->isEthereal)
		PRINT(BUF, L"%s ", getLocalString(STR_ETHERAL));

	if (input->isNotEthereal)
		PRINT(BUF, L"%s ", getLocalString(STR_NOT_ETHERAL));

	if (input->isNotRuneword)
		PRINT(BUF, L"%s ", getLocalString(STR_NOT_RUNEWORD));

	if (input->isBasic)
		PRINT(BUF, L"%s ", getLocalString(STR_BASIC));

	if (input->isExceptional)
		PRINT(BUF, L"%s ", getLocalString(STR_EXCEPTIONAL));

	if (input->isElite)
		PRINT(BUF, L"%s ", getLocalString(STR_ELITE));

	if (input->isSpecificItem) {
		if (input->quality == ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* uniqueItems = SgptDataTables->uniqueItems + input->specificID - 1;
			PRINT(BUF, StripGender(D2GetStringFromIndex(uniqueItems->uniqueNameId)));
		}
		else if (input->quality == ITEMQUALITY_SET) {
			SetItemsBIN* setItems = SgptDataTables->setItems + input->specificID - 1;
			PRINT(BUF, StripGender(D2GetStringFromIndex(setItems->setNameId)));
		}
		else {
			PRINT(BUF, L"%s ", STRING_ERROR); return;
		}
	}
	else {
		switch (input->quality)
		{
		case 1:PRINT(BUF, L"%s ", getLocalString(STR_CRACKED)); break;
		case 2:PRINT(BUF, L"%s ", getLocalString(STR_NORMAL)); break;
		case 3:PRINT(BUF, L"%s ", getLocalString(STR_SUPERIOR)); break;
		case 4:PRINT(BUF, L"%s ", getLocalString(STR_MAGIC)); break;
		case 5:PRINT(BUF, L"%s ", getLocalString(STR_SET)); break;
		case 6:PRINT(BUF, L"%s ", getLocalString(STR_RARE)); break;
		case 7:PRINT(BUF, L"%s ", getLocalString(STR_UNIQUE)); break;
		case 8:PRINT(BUF, L"%s ", getLocalString(STR_CRAFTED)); break;
		case 9:PRINT(BUF, L"%s ", getLocalString(STR_TEMPERED)); break;
		}
		if (input->byItemTypeID) {
			ItemTypesBIN* itemTypeData = D2GetItemTypesBIN(input->ID);
			if (!itemTypeData)
				PRINT(BUF, L"Unknow Item Type");
			else
				PRINT(BUF, getLocalTypeString(itemTypeData->code));
		}
		else if (input->ID == 0xFFFF) {
			PRINT(BUF, getLocalString(STR_ITEM));
		}
		else {
			ItemsBIN* items = D2GetItemsBIN(input->ID);
			PRINT(BUF, StripGender(D2GetStringFromIndex(items->NameStr)));
		}
	}
	if (input->includeUpgradedVersions && !input->isElite)
		PRINT(BUF, L" %s", getLocalString(STR_INCLUDE_UPGRADED));

	if (input->haveNoSocket)
	{
		PRINT(BUF, L" %s", getLocalString(STR_WITHOUT_SOCKET));
		InNoSocket = true;
	}
	if (input->haveSockets)
		PRINT(BUF, L" %s", getLocalString(STR_WITH_SOCKETS));
}

DWORD print(CubeMainBIN* curForm, LPWSTR buf, LPINT len, DWORD)//maxsize)
{
	if (!buf || !curForm || !curForm->enabled) return 0;

	InNoSocket = false;
	int realNbInputs=0;

	printInputItem(&curForm->input1, buf, len, &realNbInputs);
	printInputItem(&curForm->input2, buf, len, &realNbInputs);
	printInputItem(&curForm->input3, buf, len, &realNbInputs);
	printInputItem(&curForm->input4, buf, len, &realNbInputs);
	printInputItem(&curForm->input5, buf, len, &realNbInputs);
	printInputItem(&curForm->input6, buf, len, &realNbInputs);
	printInputItem(&curForm->input7, buf, len, &realNbInputs);

	if (realNbInputs != curForm->numinputs)
	{
		PRINT(BUF, L" *** ERROR : numInputs(%d) != realNbInputs(%d) ***", curForm->numinputs, realNbInputs);
		return 1;
	}

	PRINT(BUF,L" => ");
	int realNbOutputs=0;

	printOutputItem(&curForm->output1, buf, len, &realNbOutputs);
	printOutputItem(&curForm->output2, buf, len, &realNbOutputs);
	printOutputItem(&curForm->output3, buf, len, &realNbOutputs);


//	if (curForm->ladder)
//		sprintf(BUF," [ladder only]");

	if (curForm->minDiff == 1)
		PRINT(BUF, L" %s", getLocalString(STR_ONLY_N_H));
	else if (curForm->minDiff == 2)
		PRINT(BUF, L" %s", getLocalString(STR_ONLY_HELL));

	if (curForm->playerClass != 0xFF)
	{
		CharStatsBIN* charStats = D2GetCharStatsBIN(curForm->playerClass);
		PRINT(BUF, L" (");
		PRINT(BUF, getLocalString(STR_ONLY_CLASS), charStats->name);
		PRINT(BUF, L")");
	}

	if ((curForm->op>0) && (curForm->op!=28))
		PRINT(BUF, L" [op%d(%d,%d)]", curForm->op, curForm->param, curForm->value);

//	if (curForm->version == 100)
//		sprintf(BUF, " [expansion only]");

	return 1;
}
#undef BUF



void listAllCubeFormula()
{
	log_msg("\n\n********** Print all cube formula **********\n");

	char filename[MAX_PATH];
	D2FogGetSavePath(filename, MAX_PATH);
	strcat(filename, CUBEFORMULA_FILE);

	FILE* file = fopen(filename, "w");
	if (!file)
	{
		log_msg("Failed to open save file.\n");
		return;
	}

	int nbLines = D2GetNbCubeMainBIN();
	log_msg("nbLines : %d\n",nbLines);

	WCHAR buf[512];

	// Print BOM UTF-16
	//buf[0] = 0xFEFF;
	//buf[1] = NULL;
	//write(buf, 2, 2, file);

	// Print BOM UTF-8
	//printf(file, "﻿");

	int len = 0;
	int nbCubeReceipt = 0;
	for (int i=0; i<nbLines; i++)
	{
		DWORD res = 1;
		len = 0;
		buf[len] = NULL;
		res = print(D2GetCubeMainBIN(i), buf, &len, 512);
		//wcstombs(bufa, buf, 1024);
		if (res)
		{
			nbCubeReceipt++;
			fwprintf(file, L"%3u: %s\n", i, buf);
		}
	}

	fclose(file);
	log_msg("\n********** Printing over **********\n\n");
}

/*================================= END OF FILE =================================*/