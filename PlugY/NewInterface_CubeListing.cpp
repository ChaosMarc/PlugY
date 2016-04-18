/*=================================================================
	File created by Yohann NICOLAS.

	Cube Listing functions

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "updateClient.h"
#include <stdio.h>
#include <direct.h>			// _getcwd()


const char* CUBEFORMULA_FILE = "cube.txt";
const char * STRING_ERROR="***Error***";


#define BUF (&buf[strlen(buf)])


/*
6FC9275F  |. E8 ECCCFFFF    |CALL D2Game.6FC8F450                    ; \D2Game.6FC8F450


*/
void printOutput(CubeOutput* output, char* buf, BYTE* nbOutputs)
{
	if (!output->outputType)
		return;
	if (*nbOutputs)
		sprintf(BUF," + ");
	*nbOutputs += 1;

	if (output->outputType == 1) {
		sprintf(BUF,"Cow Portal");
		return;
	} else if (output->outputType == 2) {
		sprintf(BUF,"Pandemonium Portal");
		return;
	} else if (output->outputType == 3) {
		sprintf(BUF,"Pandemonium Final Portal");
		return;
	}
	
	if ((output->quantityOrNbSockets>1) && !output->haveSockets)
		sprintf(BUF,"%u ", output->quantityOrNbSockets);

	if (output->repair)
		sprintf(BUF,"repair ");

	if (output->recharge)
		sprintf(BUF,"recharge ");

	if (output->isEthereal)
		sprintf(BUF,"ethereal ");

	if (output->destroysFillers)
		sprintf(BUF,"destroys Fillers ");

	if (output->removeFillers)
		sprintf(BUF,"remove Fillers ");

	if (output->regeneratesUnique)
		sprintf(BUF,"regenerate ");

	if (output->upgradeToExceptional)
		sprintf(BUF,"exceptional ");

	if (output->upgradeToElite)
		sprintf(BUF,"elite ");


	if (output->isSpecificItem) {
		if (output->quality == ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* uniqueItems = SgptDataTables->uniqueItems + output->specificID-1;
			LPWSTR string = D2GetStringFromIndex(uniqueItems->uniqueNameId);
			wcstombs(BUF, string, wcslen(string)+1);
		} else if (output->quality == ITEMQUALITY_SET) {
			SetItemsBIN* setItems = SgptDataTables->setItems + output->specificID-1;
			LPWSTR string = D2GetStringFromIndex(setItems->setNameId);
			wcstombs(BUF, string, wcslen(string)+1);
		} else {
			sprintf(BUF,STRING_ERROR);return;
		}
	} else {
		switch (output->quality)
		{
			case 1:sprintf(BUF,"Cracked ");break;
			case 2:sprintf(BUF,"Normal ");break;
			case 3:sprintf(BUF,"Superior ");break;
			case 4:sprintf(BUF,"Magic ");break;
			case 5:sprintf(BUF,"Set ");break;
			case 6:sprintf(BUF,"Rare ");break;
			case 7:sprintf(BUF,"Unique ");break;
			case 8:sprintf(BUF,"Crafted ");break;
			case 9:sprintf(BUF,"Tempered ");break;
		}
		ItemsBIN* items;LPWSTR string;
		switch (output->outputType)
		{
			case 0xFC:
				items = D2GetItemsBIN(output->ID);
				string = D2GetStringFromIndex(items->NameStr);
				wcstombs(BUF, string, wcslen(string)+1);
				break;
			case 0xFD:
				getTypeAString(output->ID,BUF,50);
//				WCHAR string[50];
//				getTypeString(input->ID,string,50);
//				wcstombs(BUF, string, wcslen(string)+1);
				break;
			case 0xFE: sprintf(BUF,"Item");break;
			case 0xFF: sprintf(BUF,"Item of the same type");break;
			default: sprintf(BUF,STRING_ERROR);return;
		}
	}
	if ((output->quantityOrNbSockets>1) && (output->haveSockets==1))
		sprintf(BUF," with %u sockets", output->quantityOrNbSockets);
}


void printInput(CubeInput* input, char* buf, BYTE* nbInputs)//maxsize)
{
	if (!input->byItemID && !input->byItemTypeID)
		return;
	if (*nbInputs)
		sprintf(BUF," + ");

	BYTE nb = input->quantity > 0 ? input->quantity : 1;
	*nbInputs += nb;
	if (nb>1)
		sprintf(BUF,"%u ", nb);

	if (input->isEthereal)
		sprintf(BUF,"ethereal ");

	if (input->isNotEthereal)
		sprintf(BUF,"not ethereal ");

	if (input->isNotRuneword)
		sprintf(BUF,"not runeword ");

	if (input->isBasic)
		sprintf(BUF,"basic ");

	if (input->isExceptional)
		sprintf(BUF,"exceptional ");

	if (input->isElite)
		sprintf(BUF,"elite ");

	if (input->isSpecificItem) {
		if (input->quality == ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* uniqueItems = SgptDataTables->uniqueItems + input->specificID-1;
			LPWSTR string = D2GetStringFromIndex(uniqueItems->uniqueNameId);
			wcstombs(BUF, string, wcslen(string)+1);
		} else if (input->quality == ITEMQUALITY_SET) {
			SetItemsBIN* setItems = SgptDataTables->setItems + input->specificID-1;
			LPWSTR string = D2GetStringFromIndex(setItems->setNameId);
			wcstombs(BUF, string, wcslen(string)+1);
		} else {
			sprintf(BUF,STRING_ERROR);return;
		}
	} else {
		switch (input->quality)
		{
			case 1:sprintf(BUF,"Cracked ");break;
			case 2:sprintf(BUF,"Normal ");break;
			case 3:sprintf(BUF,"Superior ");break;
			case 4:sprintf(BUF,"Magic ");break;
			case 5:sprintf(BUF,"Set ");break;
			case 6:sprintf(BUF,"Rare ");break;
			case 7:sprintf(BUF,"Unique ");break;
			case 8:sprintf(BUF,"Crafted ");break;
			case 9:sprintf(BUF,"Tempered ");break;
		}
		if (input->byItemTypeID) {
			getTypeAString(input->ID,BUF,50);
		} else if (input->ID == 0xFFFF) {
			sprintf(BUF,"Item");
		} else {
			ItemsBIN* items = D2GetItemsBIN(input->ID);
			LPWSTR string = D2GetStringFromIndex(items->NameStr);
			wcstombs(BUF, string, wcslen(string)+1);
		}
	}
	if (input->includeUpgradedVersions && !input->isElite)
		sprintf(BUF,"(or upgraded) ");

	if (input->haveNoSocket)
		sprintf(BUF," with no socket");

	if (input->haveSockets)
		sprintf(BUF," with sockets");
}

DWORD print(CubeMainBIN* curForm, char* buf, DWORD)//maxsize)
{
	if (!buf || !curForm || !curForm->enabled) return 0;

	BYTE realNbInputs=0;
	printInput(&curForm->input1, buf, &realNbInputs);
	printInput(&curForm->input2, buf, &realNbInputs);
	printInput(&curForm->input3, buf, &realNbInputs);
	printInput(&curForm->input4, buf, &realNbInputs);
	printInput(&curForm->input5, buf, &realNbInputs);
	printInput(&curForm->input6, buf, &realNbInputs);
	printInput(&curForm->input7, buf, &realNbInputs);


	if (realNbInputs != curForm->numinputs)
	{
		sprintf(BUF," *** ERROR : numInputs(%d) != realNbInputs(%d) ***", curForm->numinputs, realNbInputs);
		return 1;
	}

	sprintf(BUF," => ");
	BYTE realNbOutputs=0;
	printOutput(&curForm->output1, buf, &realNbOutputs);
	printOutput(&curForm->output2, buf, &realNbOutputs);
	printOutput(&curForm->output3, buf, &realNbOutputs);


//	if (curForm->ladder)
//		sprintf(BUF," [ladder only]");
	
	if (curForm->minDiff == 1)
		sprintf(BUF," [Nightmare and Hell only]");
	else if (curForm->minDiff == 2)
		sprintf(BUF," [Hell only]");

	if (curForm->playerClass != 0xFF)
	{
		CharStatsBIN* charStats = D2GetCharStatsBIN(curForm->playerClass);
		sprintf(BUF, " [%s only]", charStats->name);
	}
	
	if ((curForm->op>0) && (curForm->op!=28))
		sprintf(BUF, " [op%d(%d,%d)]", curForm->op, curForm->param, curForm->value);

//	if (curForm->version == 100)
//		sprintf(BUF, " [expansion only]");

	return 1;
}
#undef BUF



void listAllCubeFormula()
{
	char filename[MAX_PATH];
	_getcwd( filename, MAX_PATH );
	if( filename[strlen(filename)] != '\\')
		strcat(filename, "\\");
	strcat(filename, CUBEFORMULA_FILE);

	FILE* file = fopen(filename, "w");

	if (!file) return;

	log_msg("\n\n********** Print all cube formula **********\n");//SgptDataTables->nbCubemain\n"

	int nbLines = D2GetNbCubeMainBIN();//SgptDataTables->nbCubemain
	log_msg("nbLines : %d\n",nbLines);

	char buf[300];
	for (int i=0; i<nbLines; i++)
	{
		buf[0]=NULL;
		DWORD res = print(D2GetCubeMainBIN(i), buf, 300);//SgptDataTables->cubemain + i;
		if (res) fprintf(file,"%4u: %s\n",i,buf);
		if (res) fflush(file);
	}

	fclose(file);
	log_msg("\n********** Printing over **********\n\n");

/*	_getcwd( filename, MAX_PATH );
	if( filename[strlen(filename)] != '\\')
		strcat(filename, "\\");
	strcat(filename, "tmp.txt");
	
	file = fopen(filename, "w");

	ItemStatCostBIN* itemStatCost;
	LPWSTR lpText;
	for (i=0;i<=STATS_ITEM_CHARGED_SKILL_MOD;i++)
	{
		buf[0]='\0';
		itemStatCost = D2GetItemStatCostBIN(i);
		lpText = D2GetStringFromIndex(itemStatCost->descstrpos);
		wcstombs(&buf[0],lpText,100);
		strcat(buf,"\t - \t");
		lpText = D2GetStringFromIndex(itemStatCost->descstrneg);
		wcstombs(&buf[strlen(buf)],lpText,100);
		fprintf(file,"%03d  %03X \t-  %s\n",i,i,buf);
	}
	fclose(file);*/
}

/*================================= END OF FILE =================================*/