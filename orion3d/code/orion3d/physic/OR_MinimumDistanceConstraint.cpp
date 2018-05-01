//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MinimumDistanceConstraint.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_MinimumDistanceConstraint.h"

#ifndef OR_USE_INLINE
#   include "OR_MinimumDistanceConstraint.inl"
#endif

using namespace OR;


//-----------------------------------------------------------------------------
// Name: OR_MinimumDistanceConstraint::Update
/**
*   try to satisfy the distance constraint
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
void OR_MinimumDistanceConstraint::Update()
{
	if( pTarget1_!=NULL && pTarget2_!=NULL )
	{
		OR_Vector3D &Pos1 = pTarget1_->GetPosition();
		OR_Vector3D &Pos2 = pTarget2_->GetPosition();
		OR_Vector3D Delta = Pos2 - Pos1;
		OR_Float DeltaLength = ~Delta;
		if( DeltaLength  < rDistance_ )
		{
			OR_Float InvMass1 = pTarget1_->GetInvMass();
			OR_Float InvMass2 = pTarget2_->GetInvMass();
			/* take speed in account */
			OR_Float Speed = ~pTarget1_->GetSpeed();
			if( Speed<OR_CONSTRAINT_SPEED_WEIGHT ) Speed=OR_CONSTRAINT_SPEED_WEIGHT;
			InvMass1*=Speed;
			Speed = ~pTarget2_->GetSpeed();
			if( Speed<OR_CONSTRAINT_SPEED_WEIGHT ) Speed=OR_CONSTRAINT_SPEED_WEIGHT;
			InvMass2*=Speed;
		
			OR_ASSERT(DeltaLength*(InvMass1+InvMass2) != 0);
			OR_Float Diff = (DeltaLength-rDistance_) / ( DeltaLength*(InvMass1+InvMass2) );
			Pos1 += Delta * InvMass1 * Diff;
			Pos2 -= Delta * InvMass2 * Diff;
		}
	}
}

void OR_MinimumDistanceConstraint::BuildFromFile( OR_File& file )
{
	/** \TODO Gab fill in this */
}

void OR_MinimumDistanceConstraint::BuildToFile( OR_File& file )
{
	/** \TODO Gab fill in this */
}
