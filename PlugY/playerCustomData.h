/*=================================================================
	File created by Yohann NICOLAS.

  Data added to Player base-stucture

=================================================================*/
#pragma once

#include "common.h"

extern bool active_PlayerCustomData;
extern bool openSharedStashOnLoading;

struct Unit;

struct Stash
{
	DWORD id;
	union { 
		DWORD flags; 
		struct { 
			DWORD isShared:1;	//
			DWORD isIndex:1;	//
			DWORD isMainIndex:1;	//
			DWORD isReserved:1;	// For swap items comand
		};
	};
	char* name;
	Unit* ptListItem;
	Stash* previousStash;
	Stash* nextStash;
};


struct PYPlayerData
{
	union {
		DWORD flags; 
		struct { 
			DWORD selfStashIsOpened:1;	//
			DWORD sharedStashIsOpened:1;//
			DWORD showSharedStash:1;	//
//			DWORD notOnRealm:1;			//set to 1 when the player is load from client or in SP
		}; 
	};
	DWORD	sharedGold;
	DWORD	nbSelfPages;
	DWORD	nbSharedPages;
	Stash*	currentStash;
	Stash*	selfStash;
	Stash*	sharedStash;
};

void Install_PlayerCustomData();

/*================================= END OF FILE =================================*/