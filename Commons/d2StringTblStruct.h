/*=================================================================
	File created by Yohann NICOLAS.

  @brief Diablo II Tbl Structures definitions.

=================================================================*/

#pragma once

#include <windows.h>

#pragma pack(1)

struct TblHeader
{
	WORD		usCRC;					// +00
	WORD		NumElementsOffset;		// +02
	DWORD		HashTableSizeOffset;	// +04
	BYTE		VersionOffset;			// +08
	DWORD		IndexStart;				// +09
	DWORD		NumLoopsOffset;			// +0D
	DWORD		IndexEnd;				// +11 (FileLen)
};

struct TblNode
{
	BYTE		ActiveOffset;			// +00
	WORD		KeyIndex;				// +01
	DWORD		HashValueOffset;		// +03
	DWORD		KeyOffset;				// +07
	DWORD		StringOffset;			// +0B
	WORD		StringLength;			// +0F
};




#pragma pack()

//#define TBLHEADERSIZE	0x15
//#define TBLNODESIZE		0x11

/*================================= END OF FILE =================================*/