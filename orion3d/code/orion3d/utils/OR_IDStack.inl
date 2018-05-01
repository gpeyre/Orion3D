/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_IDStack.inl
 *  \brief Inlined methods for \c OR_IDStack
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_IDStack.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack constructor
 *
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_IDStack::OR_IDStack()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack destructor
 *
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_IDStack::~OR_IDStack()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_IDStack::IsEmpty
 *
 *  \return Is the stack empty ?
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_IDStack::IsEmpty()
{
	return IDStack_.empty();
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

