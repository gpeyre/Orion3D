//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_RelaxableConstraint_ABC.h"

namespace OR {


	

//-----------------------------------------------------------------------------
// Name: OR_RelaxableConstraint_ABC constructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_RelaxableConstraint_ABC::OR_RelaxableConstraint_ABC(OR_Particule* pTarget1,
														 OR_Particule* pTarget2)
:OR_Constraint_ABC(pTarget1, pTarget2)
{

}


//-----------------------------------------------------------------------------
// Name: OR_RelaxableConstraint_ABC destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_RelaxableConstraint_ABC::~OR_RelaxableConstraint_ABC()
{

}


//-----------------------------------------------------------------------------
// Name: OR_RelaxableConstraint_ABC::IsRelaxable
/**
*   @return true since the constraint is relaxable.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_RelaxableConstraint_ABC::IsRelaxable()
{
	return true;
}


} // End namespace OR
