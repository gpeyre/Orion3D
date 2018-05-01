/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PushSpringConstraint.h
 *  \brief Definition of class OR_PushSpringConstraint
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_PushSpringConstraint_h_
#define __OR_PushSpringConstraint_h_

#include "../configuration/OR_config.h"
#include "OR_SpringConstraint.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_PushSpringConstraint
*   @brief  a constraint made of a spring that can only act as repulsive.
*
*	this spring is a special one : it only react when one push it. It is used for
*	soft body collision.
*/
///	\author Gabriel Peyré 2001-08-30
//=============================================================================
class ORION3D_API OR_PushSpringConstraint: public OR_SpringConstraint
{

public:

    OR_PushSpringConstraint(OR_Float rStiffness_ = 0.005f, OR_Float rLength = 1,
							 OR_Particule* pTarget1=NULL,
					  		 OR_Particule* pTarget2=NULL);
    virtual ~OR_PushSpringConstraint();

    //-------------------------------------------------------------------------
    /** @name overload of OR_Constraint_ABC method */
    //-------------------------------------------------------------------------
	//@{
	void Update();
    //@}


private:

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_PushSpringConstraint.inl"
#endif


#endif // __OR_PushSpringConstraint_h_
