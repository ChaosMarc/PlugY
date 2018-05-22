/*=================================================================
	File created by Yohann NICOLAS.

  Error Logger implementation.

=================================================================*/

#include "parameters.h"
#include "error.h"
#include <windows.h>
#include <stdio.h>			// fopen() fclose() fprintf() vfprintf()
#include <stdarg.h>			// ...
#include <string.h>			// strlen() strcat()
#include <direct.h>			// _getcwd()

DWORD active_logFile = 1;

static char log_file[MAX_PATH] = "";
static bool log_init = false;


void log_initfile()
{
	if (log_init) return;
	
	_getcwd( log_file, MAX_PATH );
	if( log_file[strlen(log_file)] != '\\')
		strcat(log_file, "\\");
	strcat(log_file, "PlugY.log");
	
	FILE* lLog = fopen( log_file, "w" );
	
	if( lLog != NULL )
    {
	    fclose(lLog);
	    log_init = true;
	}
	
	log_msg("<----------------------------------------------->\n"
			"\n"
			"\t\tA Plugin by Yohann\n"
			"\t\tversion %s\n"
			"\n"
			"\n"
			"<---------- Starting Diablo II Plugin ---------->\n\n\n"
			,PLUGY_VERSION);
}

void log_box( const char* pFormat, ... )
{
	char buffer[300];
	va_list lArgs;
	va_start( lArgs, pFormat );
	vsprintf( buffer, pFormat, lArgs );
	va_end(lArgs);

	log_msg(buffer);
	MessageBox(NULL, buffer, "PlugY, The Survival Kit", MB_OK|MB_ICONEXCLAMATION);
}


void log_msg( const char* pFormat, ... )
{
	if (!active_logFile) return;

	if( !log_init )
		log_initfile();

	if( log_init )
	{
		va_list lArgs;
		va_start( lArgs, pFormat );

		FILE *lDebug = fopen( log_file, "a" );

		if( lDebug != NULL )
		{
			vfprintf( lDebug, pFormat, lArgs );
			fclose( lDebug );
	    }
		else
			log_init = false;

		va_end(lArgs);
	}
}

void d2_assert( bool pCondition, char* pMessage, char* pLocation, int pLineNbr )
{
	if( pCondition )
	{
		log_msg("\n"
			"*-----------------------*\n"
			"Assertion fail at line %d of %s :\n"
			"%s\n"
			"*-----------------------*\n",
			pLineNbr, pLocation, pMessage);
		MessageBox(NULL, pMessage, "Diablo 2 Error", MB_OK|MB_ICONEXCLAMATION);
		exit(1);
	}
}

/*================================= END OF FILE =================================*/