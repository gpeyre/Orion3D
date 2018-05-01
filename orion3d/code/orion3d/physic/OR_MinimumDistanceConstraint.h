//*****************************************************************************
///	\author Gabriel Peyré 2001-08-30
//*****************************************************************************

#ifndef __OR_MinimumDistanceConstraint_h_
#define __OR_MinimumDistanceConstraint_h_

#include "../configuration/OR_config.h"
#include "OR_DistanceConstraint_ABC.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_MinimumDistanceConstraint
*   @brief  a constraint of minimum distance between two particules
*/
///	\author Gabriel Peyré 2001-08-30
//=============================================================================
class OR_MinimumDistanceConstraint: public OR_DistanceConstraint_ABC
{

public:

    OR_MinimumDistanceConstraint(OR_Float rDistance=1, 
								  OR_Particule* pTarget1=NULL,
								  OR_Particule* pTarget2=NULL);
    virtual ~OR_MinimumDistanceConstraint();
	
    //-------------------------------------------------------------------------
    /** @name overload of OR_Constraint_ABC method */
    //-------------------------------------------------------------------------
	//@{
	void Update();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_MinimumDistanceConstraint);
    //@}

private:


};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_MinimumDistanceConstraint.inl"
#endif


#endif // __OR_MinimumDistanceConstraint_h_
