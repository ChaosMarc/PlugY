/*=================================================================
	File created by Yohann NICOLAS.
	Modified by L'Autour.

	Cube Listing functions

=================================================================*/

#include "common.h"
#include "error.h"
#include "d2functions.h"
#include "updateClient.h"
#include <stdio.h>
#include <direct.h>			// _getcwd()


const char* CUBEFORMULA_FILE = "cube.txt";
const LPWSTR STRING_ERROR= L"***Error***";


#define lenbuf 512
#define lenbufi 256
#define BUF &buf[cntbuf], lenbuf-cntbuf
bool InNoSocket; //~~~~~

/*
6FC9275F  |. E8 ECCCFFFF    |CALL D2Game.6FC8F450                    ; \D2Game.6FC8F450


*/
void printOutput(CubeOutput* output, WCHAR* buf, BYTE* nbOutputs)
{
	if (!output->outputType)
		return;

	int cntbuf = wcslen(buf);

	if (*nbOutputs)
		cntbuf += swprintf(BUF,L" + ");
	*nbOutputs += 1;

	if (output->outputType == 1) {
		swprintf(BUF,getTranslatedString(STR_COW_PORTAL));
		return;
	} else if (output->outputType == 2) {
		swprintf(BUF,getTranslatedString(STR_PANDEMONIUM_PORTAL));
		return;
	} else if (output->outputType == 3) {
		swprintf(BUF,getTranslatedString(STR_PANDEMONIUM_FINAL_PORTAL));
		return;
	}
	
	if ((output->quantityOrNbSockets>1) && !output->haveSockets)
	{
		if (output->quantityOrNbSockets == 255)
			{cntbuf += swprintf(BUF,getTranslatedString(STR_FULL));}
		else
			{cntbuf += swprintf(BUF,L"%u ", output->quantityOrNbSockets);}
	}
		
	//-------------------------------------------------------------------------------
	WCHAR itembuf[lenbufi];
	LPWSTR itemstr = &itembuf[0];
	if (!(output->isSpecificItem))
	{
		ItemsBIN* items; LPWSTR string;
		switch (output->outputType)
		{
			case 0xFC:
				items = D2GetItemsBIN(output->ID);
				wcsncpy(itemstr, D2GetStringFromIndex(items->NameStr), lenbufi);
				break;
			case 0xFD:
				getTypeUString(output->ID, itemstr, lenbufi);
				break;
			case 0xFE: wcsncpy(itemstr, getTranslatedString(STR_ITEM),lenbufi);break;
			case 0xFF: wcsncpy(itemstr, getTranslatedString(STR_ITEM_SAME_TYPE),lenbufi);break;
			default: swprintf(BUF,STRING_ERROR);return;
		}
				
		itemstr = cutStringGender(itemstr);
	}
	//-------------------------------------------------------------------------------
	if (output->repair)
		cntbuf += wSprintStringLastGender(BUF, STR_REPAIR);

	if ((output->repair)&&(output->recharge))
		cntbuf += wSprintStringLastGender(BUF, STR_AND);

	if (output->recharge)
		cntbuf += wSprintStringLastGender(BUF, STR_RECHARGE);

	if (output->isEthereal)
		cntbuf += wSprintStringLastGender(BUF, STR_ETHERAL);

	if (output->destroysFillers)
		cntbuf += wSprintStringLastGender(BUF, STR_DESTROY_FILLERS);

	if (output->removeFillers)
		cntbuf += wSprintStringLastGender(BUF, STR_REMOVE_FILLERS);

	if (output->regeneratesUnique)
		cntbuf += wSprintStringLastGender(BUF, STR_REGENERATE);

	if (output->upgradeToExceptional)
		cntbuf += wSprintStringLastGender(BUF, STR_EXCEPTIONAL);

	if (output->upgradeToElite)
		cntbuf += wSprintStringLastGender(BUF, STR_ELITE);


	if (output->isSpecificItem) {
		if (output->quality == ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* uniqueItems = SgptDataTables->uniqueItems + output->specificID-1;
			LPWSTR string = D2GetStringFromIndex(uniqueItems->uniqueNameId);
			cntbuf += swprintf(BUF,string);
		} else if (output->quality == ITEMQUALITY_SET) {
			SetItemsBIN* setItems = SgptDataTables->setItems + output->specificID-1;
			LPWSTR string = D2GetStringFromIndex(setItems->setNameId);
			cntbuf += swprintf(BUF,string);
		} else {
			swprintf(BUF,STRING_ERROR);return;
		}
	} else {
		switch (output->quality)
		{
			case 1:cntbuf += wSprintStringLastGender(BUF, STR_CRACKED);break;
			case 2:cntbuf += wSprintStringLastGender(BUF, STR_NORMAL);break;
			case 3:cntbuf += wSprintStringLastGender(BUF, STR_SUPERIOR);break;
			case 4:cntbuf += wSprintStringLastGender(BUF, STR_MAGIC);break;
			case 5:cntbuf += wSprintStringLastGender(BUF, STR_SET);break;
			case 6:cntbuf += wSprintStringLastGender(BUF, STR_RARE);break;
			case 7:cntbuf += wSprintStringLastGender(BUF, STR_UNIQUE);break;
			case 8:cntbuf += wSprintStringLastGender(BUF, STR_CRAFTED);break;
			case 9:cntbuf += wSprintStringLastGender(BUF, STR_TEMPERED);break;
		} /*
		ItemsBIN* items; LPWSTR string;
		switch (output->outputType)
		{
			case 0xFC:
				items = D2GetItemsBIN(output->ID);
				string = D2GetStringFromIndex(items->NameStr);
				cntbuf += swprintf(BUF,string);
				break;
			case 0xFD:
				getTypeUString(output->ID,BUF);
				break;
			case 0xFE: cntbuf += swprintf(BUF,getTranslatedString(STR_ITEM));break;
			case 0xFF: cntbuf += swprintf(BUF,getTranslatedString(STR_ITEM_SAME_TYPE));break;
			default: cntbuf += swprintf(BUF,STRING_ERROR);return;
		} */
		cntbuf += swprintf(BUF,setMonoString(itemstr));

	}
	if ((output->haveSockets==1)||InNoSocket)
	{
		if(output->quantityOrNbSockets>1)
		{
			swprintf(BUF,getTranslatedString(STR_WITH_N_SOCKETS), output->quantityOrNbSockets);
		} else
		{
			swprintf(BUF,getTranslatedString(STR_WITH_SOCKET));
		}
	}

}


void printInput(CubeInput* input, WCHAR* buf, BYTE* nbInputs)//maxsize)
{
	if (!input->byItemID && !input->byItemTypeID)
		return;

	int cntbuf = wcslen(buf);

	if (*nbInputs)
		cntbuf += swprintf(BUF,L" + ");

	BYTE nb = input->quantity > 0 ? input->quantity : 1;
	*nbInputs += nb;
	if (nb>1)
		cntbuf += swprintf(BUF,L"%u ", nb);

	WCHAR itembuf[lenbufi];
	LPWSTR itemstr = &itembuf[0];
	//-------------------------------------------------------------------------------
	if (!(input->isSpecificItem))
	{
		if (input->byItemTypeID) {
			getTypeUString(input->ID, itemstr, lenbufi);
		} else if (input->ID == 0xFFFF) {
			wcsncpy(itemstr, getTranslatedString(STR_ITEM), lenbufi);
		} else {
			ItemsBIN* items = D2GetItemsBIN(input->ID);
			wcsncpy(itemstr, D2GetStringFromIndex(items->NameStr), lenbufi);
		}
		itemstr = cutStringGender(itemstr);
	}
	//-------------------------------------------------------------------------------
	if (input->isEthereal)
		cntbuf += wSprintStringLastGender(BUF, STR_ETHERAL);

	if (input->isNotEthereal)
		cntbuf += wSprintStringLastGender(BUF, STR_NOT_ETHERAL);

	if (input->isNotRuneword)
		cntbuf += wSprintStringLastGender(BUF, STR_NOT_RUNEWORD);

	if (input->isBasic)
		cntbuf += wSprintStringLastGender(BUF, STR_BASIC);

	if (input->isExceptional)
		cntbuf += wSprintStringLastGender(BUF, STR_EXCEPTIONAL);

	if (input->isElite)
		cntbuf += wSprintStringLastGender(BUF, STR_ELITE);

	if (input->isSpecificItem) {
		if (input->quality == ITEMQUALITY_UNIQUE)
		{
			UniqueItemsBIN* uniqueItems = SgptDataTables->uniqueItems + input->specificID-1;
			LPWSTR string = D2GetStringFromIndex(uniqueItems->uniqueNameId);
			cntbuf += swprintf(BUF,string);
		} else if (input->quality == ITEMQUALITY_SET) {
			SetItemsBIN* setItems = SgptDataTables->setItems + input->specificID-1;
			LPWSTR string = D2GetStringFromIndex(setItems->setNameId);
			cntbuf += swprintf(BUF,string);
		} else {
			swprintf(BUF,STRING_ERROR);return;
		}
	} else {
		switch (input->quality)
		{

			case 1:cntbuf += wSprintStringLastGender(BUF, STR_CRACKED);break;
			case 2:cntbuf += wSprintStringLastGender(BUF, STR_NORMAL);break;
			case 3:cntbuf += wSprintStringLastGender(BUF, STR_SUPERIOR);break;
			case 4:cntbuf += wSprintStringLastGender(BUF, STR_MAGIC);break;
			case 5:cntbuf += wSprintStringLastGender(BUF, STR_SET);break;
			case 6:cntbuf += wSprintStringLastGender(BUF, STR_RARE);break;
			case 7:cntbuf += wSprintStringLastGender(BUF, STR_UNIQUE);break;
			case 8:cntbuf += wSprintStringLastGender(BUF, STR_CRAFTED);break;
			case 9:cntbuf += wSprintStringLastGender(BUF, STR_TEMPERED);break;
		}/*
		if (input->byItemTypeID) {
			getTypeUString(input->ID,BUF);
		} else if (input->ID == 0xFFFF) {
			cntbuf += swprintf(BUF,getTranslatedString(STR_ITEM));
		} else {
			ItemsBIN* items = D2GetItemsBIN(input->ID);
			LPWSTR string = D2GetStringFromIndex(items->NameStr);
			cntbuf += swprintf(BUF,string); 
		}*/
		cntbuf += swprintf(BUF,itemstr);
	}
	if (input->includeUpgradedVersions && !input->isElite)
		cntbuf += swprintf(BUF,getTranslatedString(STR_OR_UPGRADED));

	if (input->haveNoSocket)
	{
		cntbuf += swprintf(BUF,getTranslatedString(STR_WITHOUT_SOCKET));
		InNoSocket = true;//~~~~~
	}

	if (input->haveSockets)
		swprintf(BUF,getTranslatedString(STR_WITH_SOCKET));
}

DWORD print(CubeMainBIN* curForm, WCHAR* buf, DWORD)//maxsize)
{
	if (!buf || !curForm || !curForm->enabled) return 0;
	InNoSocket = false; //~~~~~
	BYTE realNbInputs=0;
	printInput(&curForm->input1, buf, &realNbInputs);
	printInput(&curForm->input2, buf, &realNbInputs);
	printInput(&curForm->input3, buf, &realNbInputs);
	printInput(&curForm->input4, buf, &realNbInputs);
	printInput(&curForm->input5, buf, &realNbInputs);
	printInput(&curForm->input6, buf, &realNbInputs);
	printInput(&curForm->input7, buf, &realNbInputs);

	int cntbuf = wcslen(buf);

	if (realNbInputs != curForm->numinputs)
	{
		cntbuf += swprintf(BUF,L" *** ERROR : numInputs(%d) != realNbInputs(%d) ***", curForm->numinputs, realNbInputs);
		return 1;
	}

	cntbuf += swprintf(BUF,L" => ");
	BYTE realNbOutputs=0;
	printOutput(&curForm->output1, buf, &realNbOutputs);
	printOutput(&curForm->output2, buf, &realNbOutputs);
	printOutput(&curForm->output3, buf, &realNbOutputs);


//	if (curForm->ladder)
//		cntbuf += swprintf(BUF," [ladder only]");
	
	if (curForm->minDiff == 1)
		cntbuf += swprintf(BUF,getTranslatedString(STR_ONLY_N_H));
	else if (curForm->minDiff == 2)
		cntbuf += swprintf(BUF,getTranslatedString(STR_ONLY_HELL));

	if (curForm->playerClass != 0xFF)
	{
		CharStatsBIN* charStats = D2GetCharStatsBIN(curForm->playerClass);
		cntbuf += swprintf(BUF, getTranslatedString(STR_ONLY_CLASS), charStats->name);
	}
	
	if ((curForm->op>0) && (curForm->op!=28))
		cntbuf += swprintf(BUF, L" [op%d(%d,%d)]", curForm->op, curForm->param, curForm->value);

//	if (curForm->version == 100)
//		cntbuf += swprintf(BUF, " [expansion only]");

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

	WCHAR buf[lenbuf];
	char bufa[lenbuf];

	if (D2GetLang() != LNG_DEU)
	{
		bufa[0] = (char)0xEF;
		bufa[1] = (char)0xBB;
		bufa[2] = (char)0xBF;
		bufa[3] = (char)0x00;
		fprintf(file,"%s",bufa);
	}

	for (int i=0; i<nbLines; i++)
	{
		buf[0]=NULL;
		DWORD res = print(D2GetCubeMainBIN(i), buf, lenbuf);//SgptDataTables->cubemain + i;
		UCS2toUTF8(&bufa[0], lenbuf, &buf[0], lenbuf);
		if (res) fprintf(file,"%4u: %s\n",i,bufa);
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