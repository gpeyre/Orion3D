
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CylinderGizmo.h
 *  \brief Definition of class \c OR_CylinderGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_CylinderGizmo_h_
#define __OR_CylinderGizmo_h_

#include "../configuration/OR_Config.h"
#include "OR_Gizmo.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_CylinderGizmo
 *  \brief  a cylindric gizmo.
 *  \author Gabriel Peyré 2001-12-12
 *  
 *	A gizmo is an invisible volume use for a lot of thing [clipping ...].
 *		- Dim[X] -> radius on X.
 *		- Dim[Y] -> radius on Y.
 *		- Dim[Z] -> 1/2 of the height of the cylinder.
 *
 *	This means the cylinder is Z aligned.
 *	Note that in fact, the base of the cylinder can be a elipse.
 */ 
/*------------------------------------------------------------------------------*/
class ORION3D_API OR_CylinderGizmo: public OR_Gizmo
{
public:
	/** constructor */
	OR_CylinderGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1), 
		OR_Vector3D dim=OR_Vector3D(1,1,1));
	
	/** test if a point is inside the gizmo */
	virtual OR_Bool IsInside(OR_Vector3D pos);
	/** test if the gizmo is inside the frustrum view */
	virtual OR_Bool FrustrumClip();
	
	/* basic meta-env methods ******************************************/
	/** compute the value to add to the cell */
	virtual OR_Float MetaCellValue(OR_Vector3D pos);
	
	/** get the type of the object */
	virtual OR_Elements GetType()
	{ return OR_GIZMO_Cylinder; }
	
	/** overload virtual function from OR_Object */
	virtual void Draw();
																	
	//-------------------------------------------------------------------------
	/** \name overload from \c OR_MetaObject_ABC */
	//-------------------------------------------------------------------------
	//@{
	virtual void AddMetaValue(OR_MetaGrid& grid);
	//@}

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
	OR_DEFINE_SERIALIZATION(OR_CylinderGizmo);
	//@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_CylinderGizmo.inl"
#endif


#endif // __OR_CylinderGizmo_h_

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

