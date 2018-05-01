
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SquareGizmo.h
 *  \brief Definition of class \c OR_SquareGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SquareGizmo_h_
#define __OR_SquareGizmo_h_

#include "../configuration/OR_Config.h"
#include "OR_Gizmo.h"
#include "../orion3d_maths/OML_RayCaster.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SquareGizmo
 *  \brief  a square (2D) gizmo.
 *  \author Gabriel Peyré 2001-12-12
 *
 *	A gizmo is an invisible volume use for a lot of thing [clipping ...].
 *		- Dim[X] -> 1/2 of the length on X.
 *		- Dim[Y] -> 1/2 of the length on Y.
 *		- Dim[Z] -> not used.
 *
 *	This means the normal to the square is Z aligned.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_SquareGizmo: public OR_Gizmo
{

public:

	/** constructor */
	OR_SquareGizmo(OR_Vector3D vX=OR_Vector3D(1,0,0),
		OR_Vector3D vY=OR_Vector3D(0,1,0),
		OR_Vector3D vZ=OR_Vector3D(0,0,1),
		OR_Vector3D dim=OR_Vector3D(1,1,0));
	
	/* basic clipping functions ****************************************/
	/** test if a point is inside the gizmo */
	virtual OR_Bool IsInside(OR_Vector3D pos);
	/** test if the gizmo is inside the frustrum view */
	virtual OR_Bool FrustrumClip();
	
	/** get the type of the object */
	virtual OR_Elements GetType()
	{ return OR_GIZMO_Square; }
	
	/** overload virtual function from OR_Object */
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
	OR_DEFINE_SERIALIZATION(OR_SquareGizmo);
	//@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SquareGizmo.inl"
#endif


#endif // __OR_SquareGizmo_h_

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

