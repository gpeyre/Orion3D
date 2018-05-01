/*----------------------------------------------------------------------------*/
/*                         OR_MessageHandler.h                                */
/*----------------------------------------------------------------------------*/
/* defines a class to print message to screen.                                */
/*----------------------------------------------------------------------------*/

/** \file 
	defines a class to print message to screen.
	\author Gabriel.
**/

#ifndef _OR_MESSAGEHANDLER_H_
#define _OR_MESSAGEHANDLER_H_

#include "../configuration/OR_Config.h"

namespace OR
{
	
/*-----------------------------------------------------------------------------*/
/*                      class OR_MessageHandler                                */
/*-----------------------------------------------------------------------------*/
/* to print various text to screen                                             */
/*-----------------------------------------------------------------------------*/

/**
	Used to print various messages to screen.
	\author Gabriel
*/

class ORION3D_API OR_MessageHandler
{
private:
	/* current printer functions **********************************/
	/** current info printer function */
	OR_FUNCTION_MessagePrinter CurInfoPrinter;
	/** current warning printer function */
	OR_FUNCTION_MessagePrinter CurWarningPrinter;
	/** current fatal error printer function */
	OR_FUNCTION_MessagePrinter CurFatalErrorPrinter;
	/** current debug printer function */
	OR_FUNCTION_MessagePrinter CurDebugPrinter;
	/* current handler functions **********************************/
	/** current info handler function */
	OR_FUNCTION_MessageHandler CurInfoHandler;
	/** current warning handler function */
	OR_FUNCTION_MessageHandler CurWarningHandler;
	/** current fatal error handler function */
	OR_FUNCTION_MessageHandler CurFatalErrorHandler;
	/** current debug handler function */
	OR_FUNCTION_MessageHandler CurDebugHandler;

	/* default printer functions **********************************/
	static void DefaultPrinter(char* func, char* message, va_list argptr);
	/** default handler function */
	static void DefaultHandler(char* func, char* message, va_list argptr);

public:
	/** constructor */
	OR_MessageHandler();

	/** set current info printer */
	OR_FUNCTION_MessagePrinter SetInfoPrinter(OR_FUNCTION_MessagePrinter n);
	/** set current warning printer */
	OR_FUNCTION_MessagePrinter SetWarningPrinter(OR_FUNCTION_MessagePrinter n);
	/** set current fatal error printer */
	OR_FUNCTION_MessagePrinter SetFatalErrorPrinter(OR_FUNCTION_MessagePrinter n);
	/** set current debug printer */
	OR_FUNCTION_MessagePrinter SetDebugPrinter(OR_FUNCTION_MessagePrinter n);

	/** set current info handler */
	OR_FUNCTION_MessageHandler SetInfoHandler(OR_FUNCTION_MessageHandler n);
	/** set current warning handler */
	OR_FUNCTION_MessageHandler SetWarningHandler(OR_FUNCTION_MessageHandler n);
	/** set current fatal error handler */
	OR_FUNCTION_MessageHandler SetFatalErrorHandler(OR_FUNCTION_MessageHandler n);
	/** set current debug handler */
	OR_FUNCTION_MessageHandler SetDebugHandler(OR_FUNCTION_MessageHandler n);

	/** send a info message */
	void Info(char* func, char* message, ...);
	/** send a warning message */
	void Warning(char* func, char* message, ...);
	/** send a fatal error message */
	void FatalError(char* func, char* message, ...);
	/** send a debug message */
	void Debug(char* func, char* message, ...);
	/** send a info message */
	void vInfo(char* func, char* message, va_list argptr);
	/** send a warning message */
	void vWarning(char* func, char* message, va_list argptr);
	/** send a fatal error message */
	void vFatalError(char* func, char* message, va_list argptr);
	/** send a debug message */
	void vDebug(char* func, char* message, va_list argptr);
};


} // namespace OR

#endif

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