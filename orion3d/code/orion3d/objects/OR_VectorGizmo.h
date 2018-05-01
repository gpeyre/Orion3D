
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_VectorGizmo.h
 *  \brief Definition of class \c OR_VectorGizmo
 *  \author Gabriel Peyré 2001-12-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_VectorGizmo_h_
#define __OR_VectorGizmo_h_

#include "../configuration/OR_Config.h"
#include "OR_Gizmo.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_VectorGizmo
 *  \brief  a one dimensional gizmo.
 *  \author Gabriel Peyré 2001-12-12
 *  
 *	A gizmo is an invisible volume use for a lot of thing [clipping ...].
 *		- Dim[X] -> not used.
 *		- Dim[Y] -> not used.
 *		- Dim[Z] -> lenght of the vector.
 *
 *	This means the vector is Z aligned.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_VectorGizmo: public OR_Gizmo
{
public:
	/** constructor */
	OR_VectorGizmo(OR_Vector3D vX=OR_Vector3D(0,0,1), OR_Float dim=1);
	
	/** get the type of the gizmo */
	virtual OR_Elements GetType()
	{ return OR_GIZMO_Vector; }
	
	/* overload virtual function from OR_Object */
	virtual void Draw();
	
	//-------------------------------------------------------------------------
	/** \name overload of OR_Emitter_ABC methods */
	//-------------------------------------------------------------------------
	//@{
	virtual void InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed);
	//@}
	
	//-------------------------------------------------------------------------
	/** \name serialization methods */
	//-------------------------------------------------------------------------
	//@{
	OR_DEFINE_SERIALIZATION(OR_VectorGizmo);
	//@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_VectorGizmo.inl"
#endif


#endif // __OR_VectorGizmo_h_

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

