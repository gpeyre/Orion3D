/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellFuncDecl.inl
 *  \brief Inlined methods for \c OR_ShellFuncDecl
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ShellFuncDecl.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellFuncDecl::GetFunc
 *
 *  \return the function that will be used by \b LUA.
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
T_ShellFunc& OR_ShellFuncDecl::GetFunc()
{
	return ShellFunc_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellFuncDecl::GetFuncName
 *
 *  \return the \b LUA name of the function.
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_String& OR_ShellFuncDecl::GetFuncName()
{
	return FuncName_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellFuncDecl::GetFuncDesc
 *
 *  \return a short description of the function (used for -help).
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_String& OR_ShellFuncDecl::GetFuncDesc()
{
	return FuncDesc_;
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

