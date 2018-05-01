/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Force_ABC.cpp
 *  \brief Definition of class \c OR_Force_ABC
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Force_ABC.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Force_ABC.h"


#ifndef OR_USE_INLINE
#   include "OR_Force_ABC.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Force_ABC constructor
 *
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_Force_ABC::OR_Force_ABC()
:	bIsActive_( true )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Force_ABC destructor
 *
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_Force_ABC::~OR_Force_ABC()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Force_ABC::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 *
 *	Should be overloaded by complex forces.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Force_ABC::BuildSonList(T_ShellObjectList& ShellSonList)
{
	
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Force_ABC::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Force_ABC::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{	
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Activity);
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

