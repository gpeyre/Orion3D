/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsoleHistory.cpp
 *  \brief Definition of class \c OR_ShellConsoleHistory
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellConsoleHistory.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellConsoleHistory.h"

#ifndef OR_USE_INLINE
	#include "OR_ShellConsoleHistory.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory constructor
 *
 *  \param  nMaxDepth The maximum depth of the stack.
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellConsoleHistory::OR_ShellConsoleHistory(OR_U32 nMaxDepth)
:	nCurDepth_	( 1 ),
	nMaxDepth_	( nMaxDepth ),
	Top_		( Stack_.end() )
{ 
	/* nothing */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory destructor
 *
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellConsoleHistory::~OR_ShellConsoleHistory()
{
	/* delete the whole history */
	this->Reset();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory::PushString
 *
 *  \param  str the string to pusch on the stack.
 *  \author Gabriel Peyré 2001-11-27
 *
 *	This function is called each time the enter key is pressed by the user.
 *	This set the current position to top, and add the string on the stack.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleHistory::PushString(OR_String& str)
{
	/* add the string on the stack */
	if( this->GetStackSize()>=nMaxDepth_ )
	{
		/* get a string from the front of the stack */
		OR_ASSERT( !Stack_.empty() );
		OR_String* pString = Stack_.back();
		(*pString) = str;
		Stack_.pop_front();
		Stack_.push_back(pString);
	}
	else
	{
		/* create a new entry */
		Stack_.push_back( new OR_String(str) );
	}

	/* re-init the current position */
	nCurDepth_ = this->GetStackSize()+1;
	Top_ = Stack_.end();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory::Next
 *
 *  \return was it possible to go up in the history ?
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellConsoleHistory::Next()
{
	if( nCurDepth_>=this->GetStackSize() )
		return false;

	OR_ASSERT( Top_!=Stack_.end() );
	Top_++;
	nCurDepth_++;

	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory::Prev
 *
 *  \return was it possible to go down in the history ?
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_ShellConsoleHistory::Prev()
{
	if( nCurDepth_==1 )
		return false;
	
	OR_ASSERT( Top_!=Stack_.begin() );
	Top_--;
	nCurDepth_--;
	
	return true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory::GetCurrentString
 *
 *  \return the current string (NULL if the history if empty).
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_String* OR_ShellConsoleHistory::GetCurrentString()
{
	if( Stack_.empty() )
		return NULL;
	if( Top_==Stack_.end() )
		return NULL;
	return *Top_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory::Reset
 *
 *  \author Gabriel Peyré 2001-11-27
 *
 *	Reset the whole stack.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ShellConsoleHistory::Reset()
{
	/* destroy each string */
	for(IT_ConsoleHistoryStack it=Stack_.begin(); it!=Stack_.end(); ++it)
		OR_DELETE( *it );
	
	Stack_.clear();
	nCurDepth_ = 0;
	Top_ = Stack_.end();
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

