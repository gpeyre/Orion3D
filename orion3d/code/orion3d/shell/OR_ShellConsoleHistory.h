
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsoleHistory.h
 *  \brief Definition of class \c OR_ShellConsoleHistory
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellConsoleHistory_h_
#define __OR_ShellConsoleHistory_h_

#include "../configuration/OR_Config.h"
#include "../utils/OR_StringTokenizer.h"

namespace OR {

#define OR_SHELL_CONSOLE_HISTORY_DEPTH 20
typedef list<OR_String*> T_ConsoleHistoryStack;
typedef T_ConsoleHistoryStack::iterator IT_ConsoleHistoryStack;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellConsoleHistory
 *  \brief  Manager the history of the console.
 *  \author Gabriel Peyré 2001-11-27
 *	
 *	Here is a schema of the stack.
 *	
 *	\code
 *	 stack :    depth :
 *	+--------+ 
 *	|string 1|    1
 *	+--------+
 *	|string 2|    2
 *	+--------+
 *	|string 3|    3		<-- nCurDepth = 3  (this is an example)
 *	+--------+
 *	|string 4|    4		<-- nCurDepth = 4 = this->GetStackSize()
 *	+--------+
 *	\endcode
 *
 *	Note that if \c nCurDepth==0, this means the stack is empty.
 */ 
/*------------------------------------------------------------------------------*/

class OR_ShellConsoleHistory
{

public:

    OR_ShellConsoleHistory(OR_U32 nMaxDepth = OR_SHELL_CONSOLE_HISTORY_DEPTH);
    virtual ~OR_ShellConsoleHistory();

	void PushString(OR_String& str);
	OR_Bool Next();
	OR_Bool Prev();
	OR_String* GetCurrentString();
	void Reset();
	OR_U32 GetStackSize();

private:

	/** the maximum depth of the stack */
	OR_U32 nMaxDepth_;
	/** the current depth of the stack (initialy 0) */
	OR_U32 nCurDepth_;
	/** the stack */
	T_ConsoleHistoryStack Stack_;
	/** the top of the stack */
	IT_ConsoleHistoryStack Top_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ShellConsoleHistory.inl"
#endif


#endif // __OR_ShellConsoleHistory_h_

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

