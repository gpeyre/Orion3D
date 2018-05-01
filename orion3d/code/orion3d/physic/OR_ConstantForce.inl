//*****************************************************************************
///	\author Gabriel Peyré 2001-08-30
//*****************************************************************************

#include "OR_ConstantForce.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_ConstantForce constructor
/**
*   @param  g new Force vector.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_ConstantForce::OR_ConstantForce(OR_Vector3D& f)
:	OR_Force_ABC()
{
	Force_=f;
}



//-----------------------------------------------------------------------------
// Name: OR_ConstantForce destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_ConstantForce::~OR_ConstantForce()
{
}


//-----------------------------------------------------------------------------
// Name: OR_ConstantForce::SetForce
/**
*   @param  g new Force vector.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_ConstantForce::SetForce(OR_Vector3D& f)
{
	Force_=f;
}


//-----------------------------------------------------------------------------
// Name: OR_ConstantForce::GetForce
/**
*   @return Force vector.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Vector3D& OR_ConstantForce::GetForce()
{
	return Force_;
}

} // End namespace OR
