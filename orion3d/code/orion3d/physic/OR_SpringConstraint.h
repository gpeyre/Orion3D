/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpringConstraint.h
 *  \brief Definition of class OR_SpringConstraint
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SpringConstraint_h_
#define __OR_SpringConstraint_h_


#include "../configuration/OR_config.h"
#include "OR_NonRelaxableConstraint_ABC.h"

namespace OR {

//=============================================================================
/**
*   \class  OR_SpringConstraint
*   \brief  a constraint made of a spring.
*	\author Gabriel Peyré 2001-08-04
*
*	This spring as rest length 0, and is used to constraint the unit to move toward 
*	it's formation position, for instance.
*/
//=============================================================================
class ORION3D_API OR_SpringConstraint: public OR_NonRelaxableConstraint_ABC
{

public:

    OR_SpringConstraint(OR_Float rStiffness = 0.005f, OR_Float rLength = 1,
						 OR_Particule* pTarget1=NULL,
						 OR_Particule* pTarget2=NULL);
    virtual ~OR_SpringConstraint();

    //-------------------------------------------------------------------------
    /** @name accessor */
    //-------------------------------------------------------------------------
    //@{
	void SetStiffness(OR_Float rStiffness);
	OR_Float GetStiffness();
	void  SetRestLength(OR_Float rRestLength);
	OR_Float GetRestLength();
    //@}

    //-------------------------------------------------------------------------
    /** @name overload of OR_Constraint_ABC method */
    //-------------------------------------------------------------------------
	//@{
	virtual void Update();
    //@}

    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_SpringConstraint);
    //@}

protected:

	OR_Float rStiffness_;		//!< the stength of the spring	
	OR_Float rRestLength_;		//!< size of the spring when it is at rest

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_SpringConstraint.inl"
#endif


#endif // __OR_SpringConstraint_h_
