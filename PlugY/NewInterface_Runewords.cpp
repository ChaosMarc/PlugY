/*=================================================================
  File created by Yohann NICOLAS.
  Modified by Mark Mohr

  Interface functions

=================================================================*/

#include "updateServer.h"	// Install_UpdateServer()
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "statsPoints.h"
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>

int NB_RUNES_PER_PAGE = 25;

// Close Button
// -----------------------------------------------------------
DWORD getXCloseBtn() { return 360; }
DWORD getLCloseBtn() { return 32; }

DWORD getYCloseBtn() 
{ 
  if (version_D2Client == V114d)
  {
    return RY(0x31);
  }
  else
  {
    return (ResolutionY - 60);
  }
}

DWORD getHCloseBtn() { return 32; }

bool isOnCloseBtnRunewords(DWORD x, DWORD y) { return isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), getLCloseBtn(), getHCloseBtn()); }

// -----------------------------------------------------------

// NextPage Button
// -----------------------------------------------------------
DWORD getXNextPageBtn() { return 120; }
DWORD getLNextPageBtn() { return 32; }
DWORD getYNextPageBtn() 
{ 
  if (version_D2Client == V114d)
  {
    return RY(0x31);
  }
  else
  {
    return (ResolutionY - 60);
  }
}

DWORD getHNextPageBtn() { return 32; }
bool isOnNextPageBtnRunewords(DWORD x, DWORD y) { return isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn()); }
// -----------------------------------------------------------

// Previous Rune Button
// -----------------------------------------------------------
DWORD getXPrevRunesBtn() { return 168; }
DWORD getLPrevRunesBtn() { return 32; }
DWORD getYPrevRunesBtn() 
{ 
  if (version_D2Client == V114d)
  {
    return RY(0x31);
  }
  else
  {
    return (ResolutionY - 60);
  }
}
DWORD getHPrevRunesBtn() { return 32; }
bool isOnPrevRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXPrevRunesBtn(), getYPrevRunesBtn(), getLPrevRunesBtn(), getHPrevRunesBtn()); }
// -----------------------------------------------------------

// Next Rune Button
// -----------------------------------------------------------
DWORD getXNextRunesBtn() { return 200; }
DWORD getLNextRunesBtn() { return 32; }
DWORD getYNextRunesBtn() 
{ 
  if (version_D2Client == V114d)
  {
    return RY(0x31);
  }
  else
  {
    return (ResolutionY - 60);
  }
}
DWORD getHNextRunesBtn() { return 32; }
bool isOnNextRunesBtn(DWORD x, DWORD y) { return isOnRect(x, y, getXNextRunesBtn(), getYNextRunesBtn(), getLNextRunesBtn(), getHNextRunesBtn()); }
// -----------------------------------------------------------

int curRunesPage = 0;
int maxRunesPage = 0xFFFF;

static struct
{
	union{
		DWORD all;
		struct{
			DWORD close:1;
			DWORD nextPage:1;
			DWORD prevRunes:1;
			DWORD nextRunes:1;
		};
	};
} isDownBtn;


void printRuneword(RunesBIN* runesData, DWORD pos)
{
	WCHAR temp[50];
	WCHAR runesList[50];
	WCHAR typesList[50];
	LPWSTR lpText = D2GetStringFromIndex(runesData->RuneNameID);
	D2SetFont(6);
	DWORD nbPixel = D2GetPixelLen(lpText);
	DWORD x1 = (nbPixel >= 195) ? 0 : 195-nbPixel;
    if (version_D2Client == V114d)
    {
      D2PrintString(lpText, x1, 70 + pos * 20, GOLD, 0);//MILIEU(0x00,0x70,nbPixel)
    }
    else
    {
	  D2PrintString(lpText, x1, 10 + pos*20, GOLD, 0);//MILIEU(0x00,0x70,nbPixel)
    }

	typesList[0]=L'\0';
	DWORD numItype=0;
	while (numItype<6)
	{
		WORD type = runesData->Itypes[numItype];
		if (!type) break;
		ItemTypesBIN* itemTypeData = D2GetItemTypesBIN(type);
		LPCWSTR typeName = getLocalTypeString(itemTypeData->code);
		if (numItype) wcscat(typesList,L"/");
		wcscat(typesList, typeName);
		numItype++;
	}
	nbPixel = D2GetPixelLen(typesList);
	x1 = (nbPixel >= 195) ? 0 : 195-nbPixel;
    if (version_D2Client == V114d)
    {
      D2PrintString(typesList, x1, 80 + pos * 20, WHITE, 0);//MILIEU(0x70,0xA0,nbPixel)
    }
    else
    {
	  D2PrintString(typesList, x1, 20 + pos*20, WHITE, 0);//MILIEU(0x70,0xA0,nbPixel)
    }

	runesList[0]=L'\0';
	DWORD numRune=0;
	int curRuneID = runesData->Runes[0];
	while ((curRuneID>0) && (numRune<6))
	{
		ItemsBIN* itemsData = D2GetItemsBIN(curRuneID);
		d2_assert( !itemsData , "itemsData", __FILE__, __LINE__);
        GemsBIN* gemData = nullptr;
        if (itemsData)
          gemData = D2GetGemsBIN(itemsData->GemOffset);

		if (gemData) {
		d2_assert( !gemData , "gemData", __FILE__, __LINE__);
		mbstowcs(temp, gemData->letter, 50);
		if (numRune) wcscat(runesList,L" ");
//		else wcscat(runesList,L"");
      wcscat(runesList, temp);
    }
		numRune++;
		curRuneID = runesData->Runes[numRune];
	}
//	wcscat(runesList,L"");
    if (version_D2Client == V114d)
    {
      D2SetFont(6);
    }
    else
    {
	  D2SetFont(1);
    }

	DWORD y1;
	nbPixel = D2GetPixelLen(runesList);
	if (nbPixel>195)
	{

		D2SetFont(6);

		nbPixel = D2GetPixelLen(runesList);
        if (version_D2Client == V114d)
        {
            y1 = 76;
        }
        else
        {
		    y1=16;
        }
		x1 = nbPixel>195 ? 395-nbPixel : 204;
    }
    else 
    {
	    x1=205;
        if (version_D2Client == V114d)
        {
          y1 = 78;
        }
        else
        {
		    y1=18;
	    }
    }

//	x1 = (nbPixel < 145) ? 155 : 300-nbPixel;
	D2PrintString(runesList, x1, y1 + pos*20, WHITE, 0);//MILIEU(0xD0,0xA0,nbPixel)
}


#define BUFSIZE 0x80
//6FB21FAA
void STDCALL printRunewordsPage()
{
	if (!D2isLODGame() || !D2GetResolution()) return D2PrintStatsPage();

    if (version_D2Client == V114d)
    {
      NB_RUNES_PER_PAGE = 20;
    }

	LPWSTR lpText;
	bDontPrintBorder = false;

	//Init data for print image
	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));

	//print background
/*	setImage(&data, newStatsInterfaceImages);
	setFrame(&data, 0);
	D2PrintImage(&data, 0,	256, -1, 5, 0);
	setFrame(&data, 1);
	D2PrintImage(&data, 256,256, -1, 5, 0);
	setFrame(&data, 2);
	D2PrintImage(&data, 0,	512, -1, 5, 0);
	setFrame(&data, 3);
	D2PrintImage(&data, 256,512, -1, 5, 0);
	setFrame(&data, 4);
	D2PrintImage(&data, 0,	552, -1, 5, 0);
	setFrame(&data, 5);
	D2PrintImage(&data, 256,552, -1, 5, 0);
*/
	fillRect(0,0,400,552,0,5);

	//print button close
	setImage(&data, D2LoadBuySelBtn());
	setFrame(&data, 10 + isDownBtn.close);
	D2PrintImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);
	
	//print next page button
	setFrame(&data, isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	//print previous runes button
	setImage(&data, stashBtnsImages);
	setFrame(&data, isDownBtn.prevRunes);
	D2PrintImage(&data, getXPrevRunesBtn(), getYPrevRunesBtn(), -1, 5, 0);

	//print previous runes button
	setFrame(&data, 2 + isDownBtn.nextRunes);
	D2PrintImage(&data, getXNextRunesBtn(), getYNextRunesBtn(), -1, 5, 0);

	D2SetFont(6);

	//146;//B400
	int nbRunes = *D2GetNbRunesBIN();
	RunesBIN* runesFirst = nbRunes>1 ? D2GetRunesBIN(1)-1 : NULL;
	RunesBIN* runesLast = runesFirst? runesFirst + nbRunes : NULL;
//	log_msg("nbRunes(%d,%d) runesFirst(%08X, %08X) runesLast(%08X, %08X)",nbRunes,SgptDataTables->nbRunes,runesFirst, SgptDataTables->runes,runesLast,SgptDataTables->runes + SgptDataTables->nbRunes);
 
	int nbRunesCompleted=0;
	DWORD curNbRunes=0;
	for ( RunesBIN* runesData = runesFirst; runesData < runesLast; runesData++)
	{
		if (!runesData->Complete || runesData->Server) continue;
		nbRunesCompleted++;
		if ( (curRunesPage * NB_RUNES_PER_PAGE < nbRunesCompleted) &&
			(nbRunesCompleted <= (curRunesPage+1) * NB_RUNES_PER_PAGE) )
			printRuneword(runesData, curNbRunes++);
	}
	maxRunesPage = nbRunesCompleted ?  (nbRunesCompleted-1) / NB_RUNES_PER_PAGE : 0;


//////////////////// POPUP PRINTING ////////////////////
	//set MouseX & MouseY
	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();

  if (isOnCloseBtnRunewords(x, y))			// print popup "close"
	{
		D2PrintPopup(D2GetStringFromIndex(0x1030), getXCloseBtn()+getLCloseBtn()/2, getYCloseBtn()-getHCloseBtn(), WHITE, 1);
	}
  else if (isOnNextPageBtnRunewords(x, y))	// print popup "next page"
	{
		lpText = getLocalString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn()+getLNextPageBtn()/2, getYNextPageBtn()-getHNextPageBtn(), WHITE, 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

DWORD STDCALL mouseRunewordsPageLeftDown(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

  DWORD x = D2GetMouseX();
  DWORD y = D2GetMouseY();
  if (!isOnStatsPage(x, y)) return 1;

  if (isOnCloseBtnRunewords(x, y))
	{
		log_msg("push down left button close\n");
		isDownBtn.close = 1;
		D2PlaySound(4,0,0,0,0);
	}
  else if (isOnNextPageBtnRunewords(x, y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
	}
  else if (isOnPrevRunesBtn(x, y))
	{
		log_msg("push down left button prev page\n");
		isDownBtn.prevRunes = 1;
		D2PlaySound(4,0,0,0,0);
	}
  else if (isOnNextRunesBtn(x, y))
	{
		log_msg("push down left button next runes\n");
		isDownBtn.nextRunes = 1;
		D2PlaySound(4,0,0,0,0);
	}

	freeMessage(msg);
	return 0;
}


DWORD STDCALL mouseRunewordsPageLeftUp(sWinMessage* msg)
{
	if (!D2isLODGame() || !D2GetResolution()) return -1;

  DWORD x = D2GetMouseX();
  DWORD y = D2GetMouseY();
  if (!isOnStatsPage(x, y)) return 1;

  if (isOnCloseBtnRunewords(x, y))
	{
		log_msg("push up left button close\n");
		if (isDownBtn.close)
			D2TogglePage(2,1,0);
	}
  else if (isOnNextPageBtnRunewords(x, y))
	{
		log_msg("push up left button next page\n");
		if (isDownBtn.nextPage)
		{
			GoStatPage(GetCurrentPage()+1);
			log_msg("next page press\n");
		}
	}
  else if (isOnPrevRunesBtn(x, y))
	{
		log_msg("push up left button prev runes\n");
		if (isDownBtn.prevRunes)
		{
			if (curRunesPage) curRunesPage--;
		}
	}
  else if (isOnNextRunesBtn(x, y))
	{
		log_msg("push up left button next runes\n");
		if (isDownBtn.nextRunes)
		{
			if (curRunesPage < maxRunesPage) curRunesPage++;
		}
	}

	D2CleanStatMouseUp();
	freeMessage(msg);
	isDownBtn.all=0;
	return 0;
}


/*================================= END OF FILE =================================*/