//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_NonRelaxableConstraint_ABC.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_NonRelaxableConstraint_ABC constructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_NonRelaxableConstraint_ABC::OR_NonRelaxableConstraint_ABC(OR_Particule* pTarget1,
															 OR_Particule* pTarget2)
:OR_Constraint_ABC(pTarget1, pTarget2)
{

}


//-----------------------------------------------------------------------------
// Name: OR_NonRelaxableConstraint_ABC destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_NonRelaxableConstraint_ABC::~OR_NonRelaxableConstraint_ABC()
{

}

	

//-----------------------------------------------------------------------------
// Name: OR_NonRelaxableConstraint_ABC::IsRelaxable
/**
*   @return false, since the constraint is *NOT* relaxable.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_NonRelaxableConstraint_ABC::IsRelaxable()
{
	return false;
}


} // End namespace OR
