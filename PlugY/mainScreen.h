/*=================================================================
	File created by Yohann NICOLAS.

  Add "plugY v1.00" on screen.

=================================================================*/

#ifndef __MAINSCREEN_H__INCLUDED
#define __MAINSCREEN_H__INCLUDED

#include <windows.h>

extern bool active_VersionTextChange;
extern char* versionText;
extern BYTE modVersionColor;
extern bool active_PrintPlugYVersion;
extern BYTE colorOfPlugYVersion;

void Install_PrintPlugYVersion();
void Install_VersionChange();

#endif