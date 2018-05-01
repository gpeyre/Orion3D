
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OML_RayCaster.h
 *  \brief Definition of class \c OML_RayCaster
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OML_RayCaster_h_
#define __OML_RayCaster_h_

#include "OML_Config.h"
#include "OML_Maths.h"
#include "OML_Vector3D.h"
#include "OML_Matrix4x4.h"

namespace OML {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OML_RayCaster
 *  \brief  Propose ray/gizmo intersection methods.
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

class OML_RayCaster
{

public:

    static OML_Bool RayCastSphere(OML_Float rRadius, const OML_Vector3D& v1, const OML_Vector3D& v2, 
								 OML_Vector3D& normal, OML_Vector3D& intersection);
	static OML_Bool RayCastSphere_Segment(OML_Float rRadius, const OML_Vector3D& v1, const OML_Vector3D& v2, 
								 OML_Vector3D& normal, OML_Vector3D& intersection);
	static OML_Bool RayCastSphere(OML_Float rRadius, const OML_Vector3D& center, 
								 const OML_Vector3D& v1, const OML_Vector3D& v2, 
							 	 OML_Vector3D& normal, OML_Vector3D& intersection);
	static OML_Bool RayCastSphere_Segment(OML_Float rRadius, const OML_Vector3D& center, 
						  		 const OML_Vector3D& v1, const OML_Vector3D& v2, 
								 OML_Vector3D& normal, OML_Vector3D& intersection);

	static OML_Bool RayCastSquare(OML_Float rDimX, OML_Float rDimY, 
								 const OML_Vector3D& v1, const OML_Vector3D& v2, 
						 		 OML_Vector3D& normal, OML_Vector3D& intersection);
	static OML_Bool RayCastSquare_Segment(OML_Float rDimX, OML_Float rDimY, 
								 const OML_Vector3D& v1, const OML_Vector3D& v2, 
								 OML_Vector3D& normal, OML_Vector3D& intersection);
	static OML_Bool RayCastSquare(const OML_Vector3D center, const OML_Vector3D& AxeX, const OML_Vector3D& AxeY, 
								  const OML_Vector3D& v1, const OML_Vector3D& v2, 
								  OML_Vector3D& normal, OML_Vector3D& intersection);
	static OML_Bool RayCastSquare_Segment(const OML_Vector3D center, const OML_Vector3D& AxeX, const OML_Vector3D& AxeY, 
								 const OML_Vector3D& v1, const OML_Vector3D& v2, 
								 OML_Vector3D& normal, OML_Vector3D& intersection);

};

} // End namespace OML

#ifdef OML_USE_INLINE
    #include "OML_RayCaster.inl"
#endif


#endif // __OML_RayCaster_h_

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

