/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsoleHistory.inl
 *  \brief Inlined methods for \c OR_ShellConsoleHistory
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ShellConsoleHistory.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsoleHistory::GetStackSize
 *
 *  \return the size of the stack.
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_ShellConsoleHistory::GetStackSize()
{
	return Stack_.size();
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

