//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_GravityForce.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_GravityForce constructor
/**
*   @param  g new gravity vector.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_GravityForce::OR_GravityForce(OR_Vector3D& g)
:	OR_Force_ABC()
{
	g_=g;
}



//-----------------------------------------------------------------------------
// Name: OR_GravityForce destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_GravityForce::~OR_GravityForce()
{
	/* NOTHING */
}


//-----------------------------------------------------------------------------
// Name: OR_GravityForce::SetGravity
/**
*   @param  g new gravity vector.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_GravityForce::SetGravity(OR_Vector3D& g)
{
	g_=g;
}


//-----------------------------------------------------------------------------
// Name: OR_GravityForce::GetGravity
/**
*   @return gravity vector.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Vector3D& OR_GravityForce::GetGravity()
{
	return g_;
}


} // End namespace OR
