/*----------------------------------------------------------------------------*/
/*                         OR_Plane.cpp                                       */
/*----------------------------------------------------------------------------*/
/* a 3d plane                                                                 */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Plane.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Plane.h"
#include "OR_Maths.h"

namespace OR
{
	
/*--------------------------------------------------------------*/
/*                   class OR_Plane                             */
/*--------------------------------------------------------------*/
/* A simple 3D plane.                                           */
/*--------------------------------------------------------------*/

OR_Vector3D OR_Plane::FindIntersection(OR_Vector3D P1,OR_Vector3D P2)
{
	return  P1 + (P2-P1) * ( ( (N*d) - P1 ) * N ) / ( (P2 - P1) * N );
}

OR_Vector3D OR_Plane::FindIntersection(OR_Vector3D P1,OR_Vector3D P2,OR_Float Rayon)
{
	return  P1 + (P2-P1) * ( ( (N*(d+Rayon)) - P1 ) * N ) / ( (P2 - P1) * N );
}


OR_Bool OR_Plane::operator==(OR_Plane P)
{
	if (P.d>d+.01) return false;
	if (P.d<d-.01) return false;
	if (P.N!=N) return false;
	return true;
}


} // namespace OR


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////