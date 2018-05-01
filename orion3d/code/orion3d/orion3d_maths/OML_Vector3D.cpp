/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_Vector3D.cpp
 *  \brief Definition of class \c OML_Vector3D
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OML_SCCSID
static const char* sccsid = "@(#) OML_Vector3D.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OML_SCCSID


#include "stdafx.h"
#include "OML_Vector3D.h"
#include "OML_Maths.h"

#ifndef OML_USE_INLINE
	#include "OML_Vector3D.inl"
#endif

using namespace OML;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OML_Vector3D::CrossProductMatrix
 *
 *  \return A cross-product matrix corresponding to the vector.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OML_Matrix3x3 OML_Vector3D::CrossProductMatrix()
{
	return OML_Matrix3x3(
				0,        -Coords[Z], Coords[Y],
				Coords[Z], 0,        -Coords[X],
			   -Coords[Y], Coords[X], 0        );
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

