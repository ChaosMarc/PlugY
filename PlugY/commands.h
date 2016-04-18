/*=================================================================
	File created by Yohann NICOLAS.

	Commands directly in game.

=================================================================*/

#ifndef __COMMANDS_H__INCLUDED
#define __COMMANDS_H__INCLUDED

extern bool active_Commands;

void savePlayers(Unit* ptChar);
void maxGold(Unit* ptChar);
void putGold(Unit* ptChar, DWORD amount);
void takeGold(Unit* ptChar, DWORD amount);
void updateSharedGold(DWORD goldAmount);

void Install_Commands();

#endif