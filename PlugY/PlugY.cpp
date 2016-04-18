/*=================================================================
	File created by Yohann NICOLAS.

  Main file of this DLL

=================================================================*/

#include <windows.h>

BOOL WINAPI DllMain(HANDLE /*hModule*/, DWORD dwReason, LPVOID /*lpReserved*/)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
		break;
		case DLL_PROCESS_DETACH:
		break;
	}
	return true;
}

/*================================= END OF FILE =================================*/