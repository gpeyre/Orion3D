//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_NonRelaxableConstraint_ABC_h_
#define __OR_NonRelaxableConstraint_ABC_h_


#include "../configuration/OR_config.h"
#include "OR_Constraint_ABC.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_NonRelaxableConstraint_ABC
*   @brief  base class for all constraint that doesn't follow a relaxation scheme
*   
*	See OR_Constraint_ABC for a brief review of relaxable and non relaxable constraints.
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class ORION3D_API OR_NonRelaxableConstraint_ABC: public OR_Constraint_ABC
{

public:

    OR_NonRelaxableConstraint_ABC(OR_Particule* pTarget1=NULL,
								  OR_Particule* pTarget2=NULL);
    virtual ~OR_NonRelaxableConstraint_ABC();

    //-------------------------------------------------------------------------
    /** @name overload of virtual functions of OR_Constraint_ABC */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsRelaxable();
    //@}
	

private:

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_NonRelaxableConstraint_ABC.inl"
#endif


#endif // __OR_NonRelaxableConstraint_ABC_h_
