/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaGrid.cpp
 *  \brief Implementation of class \c OR_MetaGrid
 *  \author Gabriel Peyré 2002/04/14
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MetaGrid.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_MetaGrid.h"

#ifndef OR_USE_INLINE
	#include "OR_MetaGrid.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaGrid::OR_MetaGrid(OR_CubeGizmo* pSuportGizmo = NULL)
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	constructor
 */ 
/*------------------------------------------------------------------------------*/
OR_MetaGrid::OR_MetaGrid(OR_CubeGizmo* pSuportGizmo)
:	pSuportGizmo_	( pSuportGizmo ),
	aArray_			( NULL )
{
	uGridSize_[0] = uGridSize_[1] = uGridSize_[2] = 0;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaGrid::~OR_MetaGrid()
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	destructor
 */ 
/*------------------------------------------------------------------------------*/
OR_MetaGrid::~OR_MetaGrid()
{
	OR_DELETEARRAY( pSuportGizmo_ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_MetaGrid::Reset( OR_U32 size_x, OR_U32 size_y, OR_U32 size_z )
 *
 *  \author Gabriel Peyré 2002/04/14
 *
 *	resize the array.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MetaGrid::Reset( OR_U32 size_x, OR_U32 size_y, OR_U32 size_z )
{
	uGridSize_[X] = size_x;
	uGridSize_[Y] = size_y;
	uGridSize_[Z] = size_z;
	OR_DELETEARRAY( pSuportGizmo_ );
	aArray_ = new OR_Float[size_x*size_y*size_z];
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

