/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellObject_ABC.cpp
 *  \brief Definition of class \c OR_ShellObject_ABC
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellObject_ABC.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellObject_ABC.h"

#ifndef OR_USE_INLINE
	    #include "OR_ShellObject_ABC.inl"
#endif

using namespace OR;

//-------------------------------------------------------------------------
/** \name initialisation of static members */
//-------------------------------------------------------------------------
//@{
OR_ShellObject_ABC* OR_ShellObject_ABC::pStaticThis_ = NULL;
//@}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC constructor
 *
 *  \author Gabriel Peyré 2001-11-14
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellObject_ABC::OR_ShellObject_ABC()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellObject_ABC destructor
 *
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellObject_ABC::~OR_ShellObject_ABC()
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

