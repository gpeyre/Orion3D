//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_MinimumDistanceConstraint.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_MinimumDistanceConstraint constructor
/**
*   @param  rDistance minimum distance
*   @param  pTarget1 first particule involved in the constraint
*   @param  pTarget2 second particule involved in the constraint
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_MinimumDistanceConstraint::OR_MinimumDistanceConstraint(OR_Float rDistance,
															 OR_Particule* pTarget1,
															 OR_Particule* pTarget2)
:OR_DistanceConstraint_ABC(rDistance, pTarget1, pTarget2)
{

}


//-----------------------------------------------------------------------------
// Name: OR_MinimumDistanceConstraint destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_MinimumDistanceConstraint::~OR_MinimumDistanceConstraint()
{

}


} // End namespace OR
