/*==============================================
	File created by Yohann NICOLAS.

    @file error.hpp
    @brief Error logger definition.

    This file defiens various functions related to 
    error handling in D2External functions.

==============================================*/

#ifndef __ERROR_H__INCLUDED__
#define __ERROR_H__INCLUDED__

#include <windows.h>

extern DWORD active_logFile;

void log_initfile();
void log_box( const char* pFormat, ... );
void log_msg( const char* pFormat, ... );
void d2_assert( bool pCondition, char* pLocation, char* pMessage, int pLineNbr );

#endif