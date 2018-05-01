//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_MaximumDistanceConstraint_h_
#define __OR_MaximumDistanceConstraint_h_


#include "../configuration/OR_config.h"
#include "OR_DistanceConstraint_ABC.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_MaximumDistanceConstraint
*   @brief  A constraint of maximum distance between two particules.
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class OR_MaximumDistanceConstraint: public OR_DistanceConstraint_ABC
{

public:
	
    OR_MaximumDistanceConstraint(OR_Float rDistance=1, 
								 OR_Particule* pTarget1=NULL,
								 OR_Particule* pTarget2=NULL);
    virtual ~OR_MaximumDistanceConstraint();

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
	OR_DEFINE_SERIALIZATION(OR_MaximumDistanceConstraint);
    //@}

private:

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_MaximumDistanceConstraint.inl"
#endif


#endif // __OR_MaximumDistanceConstraint_h_
