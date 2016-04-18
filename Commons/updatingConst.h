/*=================================================================
	File created by Yohann NICOLAS.

	Updating Client and Server constantes.

=================================================================*/

#pragma once

enum UpdateClientConst
{
	UC_SELECT_STASH=0x18,
	UC_SHARED_GOLD,
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
	US_STARTSAVE,
	US_MAXGOLD,
	US_PUTGOLD,
	US_TAKEGOLD,

//For CB
	US_TEST1,
	US_TEST2,
	US_TEST3
};

/*================================= END OF FILE =================================*/