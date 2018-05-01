/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellCallStack.inl
 *  \brief Inlined methods for \c OR_ShellCallStack
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ShellCallStack.h"

namespace OR {



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack constructor
 *
 *  \param  pState the \b LUA state.
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellCallStack::OR_ShellCallStack(lua_State& state)
{
	pState_ = &state;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellCallStack destructor
 *
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellCallStack::~OR_ShellCallStack()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : lua_State* OR_ShellCallStack::GetState()
 *
 *  \author Gabriel Peyré 2002/03/17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
lua_State* OR_ShellCallStack::GetState()
{
	return pState_;
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

