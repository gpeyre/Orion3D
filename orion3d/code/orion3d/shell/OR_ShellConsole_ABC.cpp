/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsole_ABC.cpp
 *  \brief Definition of class \c OR_ShellConsole_ABC
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellConsole_ABC.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellConsole_ABC.h"
#include "OR_ShellKernel.h"

#ifndef OR_USE_INLINE
	    #include "OR_ShellConsole_ABC.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::SetShellKernel
 *
 *  \param  ShellKernel the kernel that this console will use to make the shell computations.
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::SetShellKernel(OR_ShellKernel& ShellKernel)
{
	pShellKernel_ = &ShellKernel;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::GetShellKernel
 *
 *  \return the kernel that this console will use to make the shell computations.
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellKernel& OR_ShellConsole_ABC::GetShellKernel()
{
	OR_ASSERT( pShellKernel_!=NULL );
	return *pShellKernel_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::KeyPressed
 *
 *  \param  c the character pressed.
 *  \author Gabriel Peyré 2001-11-27
 *
 *	 This function is called each time a key is pressed.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::KeyPressed(char c)
{
	if( c == '\r' || c == '\n' ) 
	{
		/* save the string in the history */
		HistoryStack_.PushString( TextBuffer_ );
		
		this->NewLine();
		this->Flush();
		
		this->PrintPrompt();
	}
	else if( c=='\b' )
	{
		if( TextBuffer_.length()>0 )
		{
			/* remove the last token */
			TextBuffer_.truncate( TextBuffer_.length()-1 );
			this->EraseOneChar();
		}
	}
	else if( c=='\t' )
	{
		/* try automatic completion */
		OR_String CompletedString;
		OR_String SuggestionString;
		OR_Bool bSuccess = pShellKernel_->TryCompletion( TextBuffer_, CompletedString, SuggestionString );
		
		if( bSuccess )
		{
			if( SuggestionString.length()!=0 )
			{
				/* a suggestion was found */
				this->Display( OR_String("\nPossible completions are : ") + SuggestionString + "\n" );
				this->PrintPrompt();
				this->Display( TextBuffer_ );
			}
			else
			{
				this->EraseCurrentString();
				TextBuffer_ = CompletedString;
				this->Display( TextBuffer_ );
			}
		}
	}
	else 
	{
		this->WriteString( OR_String(&c, 0, 1) );
		TextBuffer_ += OR_String(&c, 0, 1);
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::SpecialKeyPressed
 *
 *  \param  virtualKey the virtual code of the key.
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::SpecialKeyPressed(OR_U32 virtualKey)
{
	OR_Bool bSuccess = false;
	OR_String* pNewString = NULL;
	
	/* check for non ascii key*/
	switch( virtualKey )
	{
	case 40:	// down arrow 
		if( !HistoryStack_.Next() )
			break;
		/* get the string on the top of the stack */
		pNewString = HistoryStack_.GetCurrentString();		
		break;
	case 38:	// up arrow 
		if( !HistoryStack_.Prev() )
			break;
		/* get the string on the top of the stack */
		pNewString = HistoryStack_.GetCurrentString();
		break;
	case 39:	// right arrow 
		break;
	case 37:	// left arrow 
		break;
	case 33:	// page up
		break;
	case 34:	// page down
		break;
	}
	
	if( pNewString!=NULL )
	{
		/* replace the current string */
		this->EraseCurrentString();
		TextBuffer_ = *pNewString;
		this->Display( TextBuffer_ );
		return;
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::DoString
 *
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Execute a string [and add it to display].
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::DoString(OR_String& str)
{
	for( OR_U32 i=0; i< str.length(); ++i )
		this->KeyPressed( str[i] );
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::Flush
 *
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Force the execution of the string.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::Flush()
{
	OR_ASSERT( pShellKernel_!=NULL );
	pShellKernel_->DoString( TextBuffer_, *this );
	TextBuffer_.clear();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::PrintPrompt
 *
 *  print the prompt.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::PrintPrompt()
{
	OR_U32 nPrevColor = this->SetColor(kShellColor_Foreground_BLUE | kShellColor_Foreground_INTENSITY);
	OR_ASSERT( pShellKernel_!=NULL );

	if( bPrintFullPrompt_ )
		this->WriteString( pShellKernel_->ExecuteCmdPwd()+">" );
	else
	{
		/* print only the current directory */
		OR_String Prompt = pShellKernel_->GetCurrentObject().GetShellObjectName() + "/>";
		this->WriteString( Prompt );
	}

	this->SetColor(nPrevColor);
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::EraseCurrentString
 *
 *  \author Gabriel Peyré 2001-11-27
 *
 *	Erase the current string entered by the user.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsole_ABC::EraseCurrentString()
{
	OR_U32 nNbrCharToErase = TextBuffer_.length();
	TextBuffer_ = OR_String("");
	for(OR_U32 i=0; i<nNbrCharToErase; ++i)
	{
		this->EraseOneChar();
	}
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

