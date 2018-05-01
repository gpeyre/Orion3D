//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_DistanceConstraint_ABC.h"

namespace OR {

	

//-----------------------------------------------------------------------------
// Name: OR_DistanceConstraint_ABC constructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_DistanceConstraint_ABC::OR_DistanceConstraint_ABC(OR_Float rDistance, 
													   OR_Particule* pTarget1,
													   OR_Particule* pTarget2)
:OR_RelaxableConstraint_ABC(pTarget1, pTarget2)
{
	rDistance_=rDistance;
}


//-----------------------------------------------------------------------------
// Name: OR_DistanceConstraint_ABC destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_DistanceConstraint_ABC::~OR_DistanceConstraint_ABC()
{

}


//-----------------------------------------------------------------------------
// Name: OR_DistanceConstraint_ABC::SetDistance
/**
*   @param  rDistance new distance wanted between the two targets
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_DistanceConstraint_ABC::SetDistance(OR_Float rDistance)
{
	rDistance_=rDistance;
}


//-----------------------------------------------------------------------------
// Name: OR_DistanceConstraint_ABC::GetDistance
/**
*   @return distance wanted between the two targets
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_DistanceConstraint_ABC::GetDistance()
{
	return rDistance_;
}


} // End namespace OR
