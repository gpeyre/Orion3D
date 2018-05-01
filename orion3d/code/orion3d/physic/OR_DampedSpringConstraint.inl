/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DampedSpringConstraint.inl
 *  \brief Inlined methods of class OR_DampedSpringConstraint
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_DampedSpringConstraint.h"

namespace OR {
	
/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DampedSpringConstraint::OR_DampedSpring
 *  \param  rStiffness_ the strenght of the spring 
 *  \param  pTarget1 fisrt target of the constraint
 *  \param  pTarget2 second target of the constraint
 *  \param  rLength rest length of the spring 
 *  \param  rDampling dampling constant
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DampedSpringConstraint::OR_DampedSpringConstraint(OR_Float rStiffness, OR_Float rLength, OR_Float rDampling, 
										   OR_Particule* pTarget1,	OR_Particule* pTarget2)
:OR_SpringConstraint(rStiffness, rLength, pTarget1, pTarget2)
{
	rDampling_ = rDampling;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DampedSpringConstraint destructor
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DampedSpringConstraint::~OR_DampedSpringConstraint()
{
}

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DampedSpringConstraint::GetDampling
 *
 *  \return the dampling factor
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_DampedSpringConstraint::GetDampling()
{
	return rDampling_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DampedSpringConstraint::SetDampling
 *
 *  \param  rDampling The dampling factor.
 *  \author Gabriel Peyré 2001-08-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DampedSpringConstraint::SetDampling(OR_Float rDampling)
{
	rDampling_ = rDampling;
}


} // End namespace OR

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