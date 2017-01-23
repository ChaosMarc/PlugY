/*=================================================================
	File created by Yohann NICOLAS.

	Common functions.
 
=================================================================*/

#include "common.h"

bool isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h)
	{return (x>=x0) && (x<x0+l) && (y>y0-h) && (y<=y0);}


void freeMessage(sWinMessage* msg)
{
	msg->managed=1;
	msg->unmanaged=0;
	D2FreeWinMessage(msg);
}

/*================================= END OF FILE =================================*/