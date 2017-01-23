/*=================================================================
	File created by Yohann NICOLAS.

  Add "plugY v1.00" on screen.

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
