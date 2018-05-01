/*----------------------------------------------------------------------------*/
/*                         OR_MessageHandler.h                                */
/*----------------------------------------------------------------------------*/
/* defines a class to print message to screen.                                */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MessageHandler.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_MessageHandler.h"
#include "OR_Log.h"

namespace OR
{
	
/*-----------------------------------------------------------------------------*/
/*                      class OR_MessageHandler                                */
/*-----------------------------------------------------------------------------*/
/* to print various text to screen                                             */
/*-----------------------------------------------------------------------------*/

void OR_MessageHandler::DefaultPrinter(char* func, char* message, va_list argptr)
{
#ifdef _WIN32_
	char	text[1024];
	char	text2[1024];

	/* decode the arguments */
	vsprintf(text, message, argptr);
	sprintf(text2,"%s", text);

	char error_message[1024]="In ";
	strcat(error_message, func);
	strcat(error_message, " : ");
	strcat(error_message, text2);

	OR_Globals::LogManager()->AddString("\nOrion3D internal error in %s : %s", func, text);
	MessageBox(0,error_message,"Orion3D internal error",MB_OK | MB_ICONERROR);
#endif
#if (defined(_UNIX_) | defined(_MAC_OS_))
	fprintf(stderr, "Orion3D internal error in %s : %s", func, text);
#endif
}

void OR_MessageHandler::DefaultHandler(char* func, char* message, va_list argptr)
{
	/** do nothing */
}

OR_MessageHandler::OR_MessageHandler()
{
	/* initialize printer & handler */
	CurInfoPrinter=DefaultPrinter;
	CurWarningPrinter=DefaultPrinter;
	CurFatalErrorPrinter=DefaultPrinter;
	CurDebugPrinter=DefaultPrinter;
	CurInfoHandler=DefaultHandler;
	CurWarningHandler=DefaultHandler;
	CurFatalErrorHandler=DefaultHandler;
	CurDebugHandler=DefaultHandler;
}

OR_FUNCTION_MessagePrinter OR_MessageHandler::SetInfoPrinter(OR_FUNCTION_MessagePrinter n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurInfoPrinter=n;
	return old;
}

OR_FUNCTION_MessagePrinter OR_MessageHandler::SetWarningPrinter(OR_FUNCTION_MessagePrinter n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurWarningPrinter=n;
	return old;
}

OR_FUNCTION_MessagePrinter OR_MessageHandler::SetFatalErrorPrinter(OR_FUNCTION_MessagePrinter n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurFatalErrorPrinter=n;
	return old;
}

OR_FUNCTION_MessagePrinter OR_MessageHandler::SetDebugPrinter(OR_FUNCTION_MessagePrinter n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurDebugPrinter=n;
	return old;
}

OR_FUNCTION_MessageHandler OR_MessageHandler::SetInfoHandler(OR_FUNCTION_MessageHandler n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurInfoHandler=n;
	return old;
}

OR_FUNCTION_MessageHandler OR_MessageHandler::SetWarningHandler(OR_FUNCTION_MessageHandler n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurWarningHandler=n;
	return old;
}

OR_FUNCTION_MessageHandler OR_MessageHandler::SetFatalErrorHandler(OR_FUNCTION_MessageHandler n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurFatalErrorHandler=n;
	return old;
}

OR_FUNCTION_MessageHandler OR_MessageHandler::SetDebugHandler(OR_FUNCTION_MessageHandler n)
{
	OR_FUNCTION_MessagePrinter old=CurInfoPrinter;
	CurDebugHandler=n;
	return old;
}

void OR_MessageHandler::Info(char* func, char* message, ...)
{
	va_list argptr;
	va_start (argptr,message);
	CurInfoPrinter(func, message, argptr);
	CurInfoHandler(func, message, argptr);
	va_end (argptr);
}

void OR_MessageHandler::Warning(char* func, char* message, ...)
{
	va_list argptr;
	va_start (argptr,message);
	CurWarningPrinter(func, message, argptr);
	CurWarningHandler(func, message, argptr);
	va_end (argptr);
}

void OR_MessageHandler::FatalError(char* func, char* message, ...)
{
	va_list argptr;
	va_start (argptr,message);
	CurFatalErrorPrinter(func, message, argptr);
	CurFatalErrorHandler(func, message, argptr);
	va_end (argptr);
}

void OR_MessageHandler::Debug(char* func, char* message, ...)
{
	va_list argptr;
	va_start (argptr,message);
	CurDebugPrinter(func, message, argptr);
	CurDebugHandler(func, message, argptr);
	va_end (argptr);

}

void OR_MessageHandler::vInfo(char* func, char* message, va_list argptr)
{
	CurInfoPrinter(func, message, argptr);
	CurInfoHandler(func, message, argptr);
}

void OR_MessageHandler::vWarning(char* func, char* message, va_list argptr)
{
	CurWarningPrinter(func, message, argptr);
	CurWarningHandler(func, message, argptr);
}

void OR_MessageHandler::vFatalError(char* func, char* message, va_list argptr)
{
	CurFatalErrorPrinter(func, message, argptr);
	CurFatalErrorHandler(func, message, argptr);
}

void OR_MessageHandler::vDebug(char* func, char* message, va_list argptr)
{
	CurDebugPrinter(func, message, argptr);
	CurDebugHandler(func, message, argptr);
}

} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////