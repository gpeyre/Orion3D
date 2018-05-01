//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_MaximumDistanceConstraint.h"

namespace OR {

//-----------------------------------------------------------------------------
// Name: OR_MaximumDistanceConstraint constructor
/**
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_MaximumDistanceConstraint::OR_MaximumDistanceConstraint(OR_Float rDistance,
															 OR_Particule* pTarget1,
															 OR_Particule* pTarget2)
:OR_DistanceConstraint_ABC(rDistance, pTarget1, pTarget2)
{

}


//-----------------------------------------------------------------------------
// Name: OR_MaximumDistanceConstraint destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_MaximumDistanceConstraint::~OR_MaximumDistanceConstraint()
{

}


} // End namespace OR
