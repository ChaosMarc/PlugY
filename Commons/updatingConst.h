/*=================================================================
	File created by Yohann NICOLAS.

	Updating Client and Server constantes.

=================================================================*/

#pragma once

enum UpdateClientConst
{
	UC_SELECT_STASH=0x18,
	UC_SHARED_GOLD,
	UC_PAGE_NAME,
	UC_ADD_STAT,
	UC_ADD_SYNERGY,
	UC_TEST1,
	UC_TEST2,
	UC_TEST3
};

enum UpdateServerConst
{
	US_UNASSIGN_STR_POINT=0x10,//Don't change these first 8 value
	US_UNASSIGN_ENE_POINT,
	US_UNASSIGN_DEX_POINT,
	US_UNASSIGN_VIT_POINT,
	US_UNASSIGN_STR_POINTS,
	US_UNASSIGN_ENE_POINTS,
	US_UNASSIGN_DEX_POINTS,
	US_UNASSIGN_VIT_POINTS,
	US_UNASSIGN_SKILLS,
	US_SELECT_PREVIOUS,
	US_SELECT_NEXT,
	US_SELECT_SELF,
	US_SELECT_SHARED,
	US_SELECT_PREVIOUS_INDEX,
	US_SELECT_NEXT_INDEX,
	US_SELECT_PREVIOUS2,
	US_SELECT_NEXT2,
	US_SELECT_PREVIOUS_INDEX2,
	US_SELECT_NEXT_INDEX2,
	US_WORLDEVENT,
	US_SAVE,
	US_MAXGOLD,
	US_PUTGOLD,
	US_TAKEGOLD,
	US_RENAME,
	US_PAGENAME,
	US_SET_INDEX,
	US_RESET_INDEX,
	US_INSERT_PAGE,
	US_DELETE_PAGE,
	US_SWAP3,
	US_SWAP2,
	US_SWAP1,
	US_SWAP0,
	US_SWAP0_TOGGLE,
	US_TOGGLE1,
	US_TOGGLE2,
	US_TOGGLE3,
	US_TEST1,	//For CB
	US_TEST2,	//For CB
	US_TEST3	//For CB
};

/*================================= END OF FILE =================================*/