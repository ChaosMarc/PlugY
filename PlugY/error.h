/*==============================================
	File created by Yohann NICOLAS.

    @file error.hpp
    @brief Error logger definition.

    This file defiens various functions related to 
    error handling in D2External functions.

==============================================*/
#pragma once

#include <windows.h>

extern DWORD active_logFile;

void log_initfile();
void log_box( const char* pFormat, ... );
void log_msg( const char* pFormat, ... );
void d2_assert( bool pCondition, char* pLocation, char* pMessage, int pLineNbr );

/*================================= END OF FILE =================================*/