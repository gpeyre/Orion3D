/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellConsole_ABC.inl
 *  \brief Inlined methods for \c OR_ShellConsole_ABC
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_ShellConsole_ABC.h"

namespace OR {
	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC constructor
 *
 *  \param  ShellKernel the kernel that this console will use to make the shell computations.
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellConsole_ABC::OR_ShellConsole_ABC(OR_ShellKernel* pShellKernel, OR_Bool bPrintFullPrompt)
:	pShellKernel_		( pShellKernel ),
	bPrintFullPrompt_	( bPrintFullPrompt )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC destructor
 *
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellConsole_ABC::~OR_ShellConsole_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellConsole_ABC::SetPrintFullPrompt
 *
 *	\param bPrintFullPrompt do we print a short prompt (ie c/>) or a long one (ie. a/b/c/>) ?
 *  \author Gabriel Peyré 2001-11-27
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ShellConsole_ABC::SetPrintFullPrompt(OR_Bool bPrintFullPrompt)
{
	bPrintFullPrompt_ = bPrintFullPrompt;
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

