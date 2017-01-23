/*=================================================================
	File created by Yohann NICOLAS.

	Windowed mode options.

=================================================================*/
#pragma once

#include "common.h"

extern int active_Windowed;
extern int active_LockMouseCursor;
extern int active_RemoveBorder;
extern int active_WindowOnTop;
extern int active_Maximized;
extern int active_SetWindowPos;
extern int windowedX;
extern int windowedY;
extern int windowedWidth;
extern int windowedHeight;
extern int active_LockMouseOnStartup;

void SetWindowedOptions();
void lockMouseCursor();
void unlockMouseCursor();

/*================================= END OF FILE =================================*/