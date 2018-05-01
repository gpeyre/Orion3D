/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Maths.cpp
 *  \brief Definition of class \c OR_Maths
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Maths.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Maths.h"
#include "OR_Plane.h"

#ifndef OR_USE_INLINE
	#include "OR_Maths.inl"
#endif

using namespace OR;


OR_Position OR_Maths::Classify(OR_Vector3D vect, OR_Plane* P)
{
	OR_Float d=(vect*P->N)-P->d;
	if( d>OR_EPSILON ) 
		return OR_POS_FRONT;
	if( d<-OR_EPSILON ) 
		return OR_POS_BACK;
	return OR_POS_LIE;
}

OR_Position OR_Maths::Classify(OR_Vector3D vect, OR_Plane* P, OR_Float Decal)
{
	OR_Float d=(vect*P->N)-P->d-Decal;
	if( d>OR_EPSILON ) 
		return OR_POS_FRONT;
	if( d<-OR_EPSILON ) 
		return OR_POS_BACK;
	return OR_POS_LIE;
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

