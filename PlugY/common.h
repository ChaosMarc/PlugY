/*==============================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

  this file implements some common and useful
  function related to some Diablo II mechanisms.

/*============================================*/
#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#include "../Commons/d2Constants.h"
#include "../Commons/d2BinFile.h"
#include "../Commons/d2Struct.h"
#include "../Commons/d2StringTblStruct.h"
#include "../Commons/D2UnitStruct.h"
#include "../Commons/updatingConst.h"
#include "../Commons/VersionInfo.h"

#include "error.h"
#include "modifMemory.h"
#include "parameters.h"
#include "d2wrapper.h"
#include "playerCustomData.h" // include common.h
#include "globalVariable.h" // include common.h

#include "d2functions.h"
#include "LocalizedStrings.h"

bool isOnRect(DWORD x, DWORD y, DWORD x0, DWORD y0, DWORD l, DWORD h);
void freeMessage(sWinMessage* msg);

/*================================= END OF FILE =================================*/