
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SphereGizmo.h
 *  \brief Definition of class \c OR_SphereGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SphereGizmo_h_
#define __OR_SphereGizmo_h_

#include "../configuration/OR_Config.h"
#include "OR_Gizmo.h"
#include "../orion3d_maths/OML_RayCaster.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SphereGizmo
 *  \brief  a spherical gizmo.
 *  \author Gabriel Peyré 2001-12-12
 *
 *	A gizmo is an invisible volume use for a lot of thing [clipping ...].
 *		- Dim[X] -> radius on X.
 *		- Dim[Y] -> radius on Y.
 *		- Dim[Z] -> radius on Z.
 *
 *	The sphere is in fact a elipsoide, also some features [collision...] for the 
 *	moment only works with sphere gizmos.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_SphereGizmo: public OR_Gizmo
{
public:
	/** constructor */
	OR_SphereGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1), 
		OR_Vector3D dim=OR_Vector3D(1,1,1));
	/* basic collision functions ***************************************/
	/** test if a point is inside the gizmo */
	virtual OR_Bool IsInside(OR_Vector3D pos);
	/** test if the gizmo is inside the frustrum view */
	virtual OR_Bool FrustrumClip();
	
	//-------------------------------------------------------------------------
	/** \name overload from \c OR_MetaObject_ABC */
	//-------------------------------------------------------------------------
	//@{
	virtual void AddMetaValue(OR_MetaGrid& grid);
	//@}
	
	/** get the type of the object */
	virtual OR_Elements GetType()
	{ return OR_GIZMO_Sphere; }
	
	/* overload virtual function from OR_Object */
	virtual void Draw();
	
	//-------------------------------------------------------------------------
	/** \name overload of OR_Emitter_ABC methods */
	//-------------------------------------------------------------------------
	//@{
	virtual void InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed);
	//@}
	
	//-------------------------------------------------------------------------
	/** \name iverload of OR_Deflector_ABC methods */
	//-------------------------------------------------------------------------
	//@{
	void DeflectParticule(OR_Particule& particule);
	void DeflectObject(OR_RigidBody& object);
	//@}
	
	//-------------------------------------------------------------------------
	/** \name serialization methods */
	//-------------------------------------------------------------------------
	//@{
	OR_DEFINE_SERIALIZATION(OR_SphereGizmo);
	//@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SphereGizmo.inl"
#endif


#endif // __OR_SphereGizmo_h_

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

