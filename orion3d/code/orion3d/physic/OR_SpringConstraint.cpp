/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpringConstraint.cpp
 *  \brief Implementation of class OR_PushSpringConstraint
 *  \author Gabriel Peyr� 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SpringConstraint.cpp (c) Gabriel Peyr� & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SpringConstraint.h"

#ifndef OR_USE_INLINE
#   include "OR_SpringConstraint.inl"
#endif

using namespace OR;


//-----------------------------------------------------------------------------
// Name: OR_SpringConstraint::Update
/**
*   add the spring force to the accumulator of each target
*/
/// \author Gabriel Peyr� 2001-08-31
//-----------------------------------------------------------------------------
void OR_SpringConstraint::Update()
{
	OR_ASSERT(pTarget1_!=NULL);
	OR_ASSERT(pTarget2_!=NULL);
	/* compute distance between objects */
	OR_Float rDistance = ~(pTarget1_->GetPosition() - pTarget2_->GetPosition());
	/* compute the force */
	OR_Float rDiff = rRestLength_-rDistance;
	if( rDistance>OR_EPSILON )
	{
		OR_Vector3D Forces = (pTarget2_->GetPosition() - pTarget1_->GetPosition())
			               * ( (rStiffness_*rDiff)/rDistance );
		/* add it to each accumulator */
		pTarget1_->AddForce(-Forces);
		pTarget2_->AddForce(Forces);
	}
}

void OR_SpringConstraint::BuildFromFile( OR_File& file )
{
	/** \TODO Gab fill in this */
}

void OR_SpringConstraint::BuildToFile( OR_File& file )
{
	/** \TODO Gab fill in this */
}
