//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_SpringConstraint.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint constructor
/**
*   @param  rStiffness_ the strenght of the spring 
*   @param  pTarget1 fisrt target of the constraint
*   @param  pTarget2 second target of the constraint
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_SpringConstraint::OR_SpringConstraint(OR_Float rStiffness, OR_Float rLength,
										   OR_Particule* pTarget1,
										   OR_Particule* pTarget2)
:OR_NonRelaxableConstraint_ABC(pTarget1, pTarget2)
{
	rRestLength_=rLength;
	rStiffness_=rStiffness;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_SpringConstraint::~OR_SpringConstraint()
{

}



//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint::SetStiffness
/**
*   @param  rStiffness the new strength of the spring
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_SpringConstraint::SetStiffness(OR_Float rStiffness)
{
	rStiffness_=rStiffness;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint::GetStiffness
/**
*   @return the strength of the spring
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_SpringConstraint::GetStiffness()
{
	return rStiffness_;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint::SetRestLength
/**
*   @param  rRestLength size of the spring at rest
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_SpringConstraint::SetRestLength(OR_Float rRestLength)
{
	rRestLength_=rRestLength;
}


//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint::GetRestLength
/**
*   @return new size of the spring at rest
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_SpringConstraint::GetRestLength()
{
	return rRestLength_;
}

} // End namespace OR
