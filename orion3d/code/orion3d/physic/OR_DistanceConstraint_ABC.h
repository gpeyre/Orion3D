//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_DistanceConstraint_ABC_h_
#define __OR_DistanceConstraint_ABC_h_

#include "../configuration/OR_config.h"
#include "OR_RelaxableConstraint_ABC.h"

//-------------------------------------------------------------------------
/** @name some contraints */
//-------------------------------------------------------------------------
//@{
#define OR_CONSTRAINT_SPEED_WEIGHT 0.8f			//!< part of the speed in the resolution of constraints
//@}

namespace OR {

//=============================================================================
/**
*   @class  OR_DistanceConstraint_ABC
*   @brief  Base class for all constraints involving distance between two particules
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class OR_DistanceConstraint_ABC: public OR_RelaxableConstraint_ABC
{

public:

    OR_DistanceConstraint_ABC(OR_Float rDistance=1, 
							   OR_Particule* pTarget1=NULL,
							   OR_Particule* pTarget2=NULL);
    virtual ~OR_DistanceConstraint_ABC();
	
    //-------------------------------------------------------------------------
    /** @name accessor */
    //-------------------------------------------------------------------------
    //@{
	void SetDistance(OR_Float rDistance);
	OR_Float GetDistance();
    //@}

protected:

	OR_Float rDistance_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_DistanceConstraint_ABC.inl"
#endif


#endif // __OR_DistanceConstraint_ABC_h_
