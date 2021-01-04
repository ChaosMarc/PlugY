/*=================================================================
	File created by Yohann NICOLAS.

	Print PlugY version on screen.

=================================================================*/
#pragma once

#include "common.h"

extern bool active_VersionTextChange;
extern char* versionText;
extern BYTE modVersionColor;
extern bool active_PrintPlugYVersion;
extern BYTE colorOfPlugYVersion;

void Install_PrintPlugYVersion();
void Install_VersionChange();

/*================================= END OF FILE =================================*/
