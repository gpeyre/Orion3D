/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpringForce.inl
 *  \brief Inlined methods for \c OR_SpringForce
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_SpringForce.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpringForce::OR_DampedSpring
 *  \param  rStiffness_ the strenght of the spring 
 *  \param  pTarget1 fisrt target of the constraint
 *  \param  pTarget2 second target of the constraint
 *  \param  rLength rest length of the spring 
 *  \param  rDampling dampling constant
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SpringForce::OR_SpringForce(OR_Vector3D& Anchor, OR_Float rStiffness, OR_Float rLength, OR_Float rDampling)
:	OR_Force_ABC(),
	Anchor_		( Anchor ),
	rStiffness_	( rStiffness ),
	rRestLength_( rLength ),
	rDampling_	( rDampling )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpringForce destructor
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SpringForce::~OR_SpringForce()
{
}

//-----------------------------------------------------------------------------
// Name: OR_SpringForce::SetStiffness
/**
*   @param  rStiffness the new strength of the spring
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_SpringForce::SetStiffness(OR_Float rStiffness)
{
	rStiffness_=rStiffness;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringForce::GetStiffness
/**
*   @return the strength of the spring
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_SpringForce::GetStiffness()
{
	return rStiffness_;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringForce::SetRestLength
/**
*   @param  rRestLength size of the spring at rest
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_SpringForce::SetRestLength(OR_Float rRestLength)
{
	rRestLength_=rRestLength;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringForce::GetRestLength
/**
*   @return new size of the spring at rest
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_SpringForce::GetRestLength()
{
	return rRestLength_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpringForce::GetDampling
 *
 *  \return the dampling factor
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_SpringForce::GetDampling()
{
	return rDampling_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpringForce::SetDampling
 *
 *  \param  rDampling The dampling factor.
 *  \author Gabriel Peyré 2001-08-04
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SpringForce::SetDampling(OR_Float rDampling)
{
	rDampling_ = rDampling;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpringForce::SetAnchor
 *
 *  \param  Anchor position of the anchor the object is linked to
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_SpringForce::SetAnchor(OR_Vector3D& Anchor)
{
	Anchor_ = Anchor;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpringForce::GetAnchor
 *
 *  \return position of the anchor the object is linked to.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_SpringForce::GetAnchor()
{
	return Anchor_;
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

