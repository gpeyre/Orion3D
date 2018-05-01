/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsoleText.inl
 *  \brief Inlined methods for \c OR_ShellConsoleText
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ShellConsoleText.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::OpenConsole
 *
 *  \author Gabriel Peyré 2001-11-24
 *
 *	Open a console windows.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_ShellConsoleText::OpenConsole()
{
	if( bIsOpen_ ) return true;
	
	AllocConsole();
	
	/* Get handles to STDIN and STDOUT */
	hStdin_  = GetStdHandle(STD_INPUT_HANDLE); 
	hStdout_ = GetStdHandle(STD_OUTPUT_HANDLE); 
	
	if (hStdin_  == INVALID_HANDLE_VALUE || 
        hStdout_ == INVALID_HANDLE_VALUE) 
    {
		bIsOpen_ = false;
		return false;
    }
	
	
	
	DWORD cMode;
    /* Turn off the line input mode, and echo the input mode. */
    if (! GetConsoleMode(hStdin_, &cMode)) 
	{
		bIsOpen_ = false;
		return false;
	}
	
    cMode = cMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT); 
    if(! SetConsoleMode(hStdin_, cMode)) 
	{
		bIsOpen_ = false;
		return false;
	}
	
	/* set the CTRL handler */
    bIsOpen_ = SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE);
    if (! bIsOpen_) 
		return false;
	
	/* print an about message */
	this->Display( pShellKernel_->ExecuteCmdAbout() + "\n" );
	
	/* print the first prompt */
	this->PrintPrompt();

	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::CloseConsole
 *
 *  \author Gabriel Peyré 2001-11-24
 *
 *	Close current console.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellConsoleText::CloseConsole()
{	
	if( !bIsOpen_ )
		return;

	if( !FreeConsole() )
		OR_Globals::MessageHandler()->Warning("OR_ShellConsoleText::CloseConsole", "Can't close current console.");

	bIsOpen_ = false;
}



/*------------------------------------------------------------------------------
 * Name : OR_ShellConsoleText::IsOpen
 *
 *  \return true if the console is open
 *  \author Antoine Bouthors 2001-12-03
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_ShellConsoleText::IsOpen()
{
	return bIsOpen_;
}



} // End namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

