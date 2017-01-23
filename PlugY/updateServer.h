/*=================================================================
	File created by Yohann NICOLAS.

	Updating Server.

=================================================================*/
#pragma once

#include "common.h"

__inline void updateServer(WORD p) {if (!onRealm) D2SendToServer3(0x3A, p);};
void Install_UpdateServer();

/*================================= END OF FILE =================================*/