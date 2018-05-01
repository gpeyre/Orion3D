/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellFuncDecl.cpp
 *  \brief Definition of class \c OR_ShellFuncDecl
 *  \author Gabriel Peyré 2001-11-17
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellFuncDecl.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellFuncDecl.h"

#ifndef OR_USE_INLINE
	    #include "OR_ShellFuncDecl.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellFuncDecl constructor
 *
 *  \param  ShellFunc the function callback to register to LUA.
 *  \param  FuncName the name of the function.
 *  \param  FuncDesc description of the function.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellFuncDecl::OR_ShellFuncDecl(T_ShellFunc ShellFunc, OR_String& FuncName, OR_String& FuncDesc)
:	ShellFunc_	( ShellFunc ),
	FuncName_	( FuncName ),
	FuncDesc_	( FuncDesc )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellFuncDecl destructor
 *
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellFuncDecl::~OR_ShellFuncDecl()
{
	/* NOTHING */
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

