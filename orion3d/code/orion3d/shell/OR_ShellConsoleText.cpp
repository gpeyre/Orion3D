/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsoleText.cpp
 *  \brief Definition of class \c OR_ShellConsoleText
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellConsoleText.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellConsoleText.h"

#ifndef OR_USE_INLINE
	    #include "OR_ShellConsoleText.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText constructor
 *
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellConsoleText::OR_ShellConsoleText(OR_ShellKernel* pShellKernel, OR_Bool bOpen, OR_Bool bPrintFullPrompt)
:	OR_ShellConsole_ABC	( pShellKernel , bPrintFullPrompt)
{	
	if( bOpen )
		this->OpenConsole();
	else
		bIsOpen_ = false;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText destructor
 *
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellConsoleText::~OR_ShellConsoleText()
{
	/* free the console */
	FreeConsole();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::Display
 *
 *  \param  text the text to print.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::Display(OR_String& text)
{
	if( !bIsOpen_ ) return;
	DWORD cWritten;
	
	if( ! WriteFile(hStdout_, text.val(), text.length(), &cWritten, NULL)) 
		OR_Globals::MessageHandler()->FatalError("OR_ShellConsoleText::Display",
		"Could no read from input stream.");
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::Clear
 *
 *  \return clear the console.
 *  \author Gabriel Peyré 2001-11-22
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::Clear()
{
//	UINT GetConsoleCP(VOID)
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::Update
 *
 *  \author Gabriel Peyré 2001-11-24
 *
 *	Update the console.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::Update()
{
	DWORD cNumRead;
	DWORD nNbrEvents;

	if( !bIsOpen_ )
		return;

	/* check if there are events to treat */
	if( !GetNumberOfConsoleInputEvents( hStdin_, &nNbrEvents ) )
		OR_Globals::MessageHandler()->Warning("OR_ShellConsoleText::Update", 
						"Can't get the number of events.");
	if( nNbrEvents==0 )
		return;
	
	/* Wait for the events. */
	if (! ReadConsoleInput( 
		hStdin_,		// input buffer handle 
		irInBuf_,		// buffer to read into 
		128,			// size of read buffer 
		&cNumRead) )	// number of records read 
		OR_Globals::MessageHandler()->Warning("OR_ShellConsoleText::Update", 
						"Can't access events");
	
	/* Dispatch the events to the appropriate handler. */
	for( DWORD i = 0; i < cNumRead; i++ )
	{
		switch(irInBuf_[i].EventType) 
		{ 
		case KEY_EVENT: // keyboard input 
			KeyEventProc(irInBuf_[i].Event.KeyEvent); 
			break; 
			
		case MOUSE_EVENT: // mouse input 
			break; 
			
		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
			break; 
			
		case FOCUS_EVENT:  // disregard focus events 
		case MENU_EVENT:   // disregard menu events 
			break; 
			
		default: 
			break; 
		} 
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::KeyEventProc
 *
 *  \param  record the event.
 *  \author Gabriel Peyré 2001-11-24
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::KeyEventProc(KEY_EVENT_RECORD record)
{
	/* the key is released */
	if( !record.bKeyDown )
		return;

	char c = record.uChar.AsciiChar;
	
	/* non ASCII char */
	if( c==NULL )
	{
		this->SpecialKeyPressed( record.wVirtualKeyCode );
		return;
	}

	this->KeyPressed( c );

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::CtrlHandler
 *
 *  \param  fdwCtrlType type of ctrl-event.
 *  \return get the event / release it
 *  \author Gabriel Peyré 2001-11-24
 *
 *	Callback function for control events.
 */ 
/*------------------------------------------------------------------------------*/
BOOL OR_ShellConsoleText::CtrlHandler(DWORD fdwCtrlType)
{ 
    switch (fdwCtrlType) 
    {     	
	case CTRL_C_EVENT:		// Handle the CTRL+C signal. 
		return TRUE;	
		
	case CTRL_CLOSE_EVENT:	// CTRL+CLOSE: confirm that the user wants to exit. 
		return TRUE; 
		
	case CTRL_BREAK_EVENT:	// Pass other signals to the next handler. 
	case CTRL_LOGOFF_EVENT: 
	case CTRL_SHUTDOWN_EVENT: 
	default: 
		return FALSE; 
    } 
} 


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::WriteString
 *
 *  \param  str the string to write.
 *  \author Gabriel Peyré 2001-11-24
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::WriteString(OR_String& str)
{
	if( !bIsOpen_ ) 
		return;
	DWORD cWritten;
	
	if( ! WriteFile(hStdout_, str.val(), str.length(), &cWritten, NULL)) 
		OR_Globals::MessageHandler()->FatalError("OR_ShellConsoleText::WriteString",
						"Could no read from input stream.");
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::NewLine
 *
 *  \author Gabriel Peyré 2001-11-24
 *
 *	The NewLine function handles carriage returns when the processed 
 *	input mode is disabled. It gets the current cursor position 
 *	and resets it to the first cell of the next row. 
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::NewLine()
{ 
	if( !bIsOpen_ ) 
		return;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

    if (! GetConsoleScreenBufferInfo(hStdout_, &csbiInfo)) 
        OR_ASSERT(false);
    csbiInfo.dwCursorPosition.X = 0; 
	
    // If it is the last line in the screen buffer, scroll 
    // the buffer up. 
	
    if ((csbiInfo.dwSize.Y-1) == csbiInfo.dwCursorPosition.Y) 
    { 
        this->ScrollScreenBuffer(hStdout_, 1); 
    } 
	
	
    // Otherwise, advance the cursor to the next line. 
	
    else csbiInfo.dwCursorPosition.Y += 1; 
	
    if (! SetConsoleCursorPosition(hStdout_, csbiInfo.dwCursorPosition)) 
    {
        OR_ASSERT(false);
    }
} 


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::ScrollScreenBuffer
 *
 *  \param  hStream the i/o strem.
 *  \param  nNbrLine the number of lines to scroll
 *  \author Gabriel Peyré 2001-11-24
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::ScrollScreenBuffer(HANDLE hStream, INT nNbrLine)
{

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::SetColor
 *
 *  \param  color the new color.
 *	\return previous color.
 *  \author Gabriel Peyré 2001-11-24
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_ShellConsoleText::SetColor( OR_U32 color )
{
	if( !bIsOpen_ ) 
		return 0;
	OR_U32 prev = this->GetColor();

	if( !SetConsoleTextAttribute(hStdout_, color) )
		OR_Globals::MessageHandler()->Warning("OR_ShellConsoleText::SetColorBackground", 
						"Could not set console color.");

	return prev;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::T_ShellColor 
 *
 *  \return the color.
 *  \author Gabriel Peyré 2001-11-24
 */ 
/*------------------------------------------------------------------------------*/
OR_U32 OR_ShellConsoleText::GetColor()
{
	if( !bIsOpen_ ) 
		return 0;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 
	
    if (! GetConsoleScreenBufferInfo(hStdout_, &csbiInfo)) 
        OR_ASSERT(false);

	return csbiInfo.wAttributes;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleText::EraseOneChar
 *
 *  \author Gabriel Peyré 2001-11-27
 *
 *	Erase one char printed.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleText::EraseOneChar()
{
	this->Display( OR_String("\b \b") );
}




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

