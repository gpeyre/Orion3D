/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PushSpringConstraint.cpp
 *  \brief Implementation of class OR_PushSpringConstraint
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_PushSpringConstraint.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_PushSpringConstraint.h"

#ifndef OR_USE_INLINE
#   include "OR_PushSpringConstraint.inl"
#endif

using namespace OR;

//-----------------------------------------------------------------------------
// Name: OR_PushSpringConstraint::Update
/**
*   @return add the spring force to the accumulator of each target
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
void OR_PushSpringConstraint::Update()
{
	OR_ASSERT(pTarget1_!=NULL);
	OR_ASSERT(pTarget2_!=NULL);
	/* compute distance between objects */
	OR_Float rDistance = ~(pTarget1_->GetPosition() - pTarget2_->GetPosition());
	/* compute the force */
	OR_Float rDiff = rRestLength_-rDistance;
	if( rDiff > 0)
	{
		if(rDistance>OR_EPSILON)
		{
			OR_Vector3D Forces = (pTarget2_->GetPosition() - pTarget1_->GetPosition())
					    		* ( (rStiffness_*rDiff)/rDistance );
			/* add it to each accumulator */
			pTarget1_->AddForce(-Forces);
			pTarget2_->AddForce(Forces);
		}
	}
}

