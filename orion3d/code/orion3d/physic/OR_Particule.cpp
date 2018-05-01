/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Particule.cpp
 *  \brief Implementation of particule class.
 *  \author Gabriel Peyré 2001-07-29
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Particule.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Particule.h"
#include "OR_ParticuleManager.h"

#ifndef OR_USE_INLINE
	#include "OR_Particule.inl"
#endif

#include "OR_PhysicEntityManager.h"

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::UpdatePhysics_Verlet
 *
 *  \author Gabriel Peyré 2001-07-18
 *
 *	Update the particule position using a verlet scheme.
 *	\todo use impulse accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Particule::UpdatePhysics_Verlet()
{
	OR_Float rDeltaTime = OR_PhysicEntityManager::GetTimeStep();

	if( bIsSpeedSpecified_ )
	{
		/* now PosOld_ needs to be recomputed */
		PosOld_ = Pos_ - Speed_*rDeltaTime;
		bIsSpeedSpecified_=false;
	}

	/* update the position using Verlet scheme */
	OR_Vector3D NewPos = Pos_*2 - PosOld_ + ForceAccumulator_*(rDeltaTime*rDeltaTime*rInvMass_);
	PosOld_ = Pos_;
	Pos_    = NewPos;

	/* compute new speed */
	Speed_ = (Pos_ - PosOld_)/rDeltaTime;

	/* clear the accumulators */
	this->ResetAccumulators();
}


//-----------------------------------------------------------------------------
// Name: OR_Particule::UpdatePhysics_RK4
/**
*   @param  nNbStep step of \e RK4 integration, in [1,4]
*
*	Peform a step in the \e RK4 integration.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
void OR_Particule::UpdatePhysics_RK4(OR_U32 nNbStep)
{
	OR_Float rDeltaTime = OR_PhysicEntityManager::GetTimeStep();

	OR_Vector3D RK4Offset;

	switch( nNbStep )
	{
	case 1:
		/* save speed & position at current time */
		CurSpeed_ = Speed_;
		CurPos_   = Pos_;

		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4PosAccumulator_ = RK4Offset*OR_RK4_COEF1;
		/* set up state variable for next step */
		Pos_   = CurPos_ + RK4Offset*0.5f;

		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*(rDeltaTime*rInvMass_);
		/* accumulate the result with correct RK4 weight */
		RK4SpeedAccumulator_ = RK4Offset*OR_RK4_COEF1;
		/* set up state variable for next step */
		Speed_ = CurSpeed_ + RK4Offset*0.5f;
		break;

	case 2:
		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4PosAccumulator_ += RK4Offset*OR_RK4_COEF2;
		/* set up state variable for next step */
		Pos_   = CurPos_ + RK4Offset*0.5f;

		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*(rDeltaTime*rInvMass_);
		/* accumulate the result with correct RK4 weight */
		RK4SpeedAccumulator_ += RK4Offset*OR_RK4_COEF2;
		/* set up state variable for next step */
		Speed_ = CurSpeed_ + RK4Offset*0.5f;
		break;

	case 3:
		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4PosAccumulator_ += RK4Offset*OR_RK4_COEF3;
		/* set up state variable for next step */
		Pos_   = CurPos_ + RK4Offset;

		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*(rDeltaTime*rInvMass_);
		/* accumulate the result with correct RK4 weight */
		RK4SpeedAccumulator_ += RK4Offset*OR_RK4_COEF3;
		/* set up state variable for next step */
		Speed_ = CurSpeed_ + RK4Offset;
		break;

	case 4:	
		/* save previous position, used for deflexion */
		PosOld_= CurPos_;

		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4PosAccumulator_ += RK4Offset*OR_RK4_COEF4;
		/* compute final speed */
		Pos_   = CurPos_ + RK4PosAccumulator_;

		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*(rDeltaTime*rInvMass_);
		/* accumulate the result with correct RK4 weight */
		RK4SpeedAccumulator_ += RK4Offset*OR_RK4_COEF4;
		/* compute final speed */
		Speed_ = CurSpeed_ + RK4SpeedAccumulator_;

		/* add the impulse of deflexion */
		Speed_ += ImpulseAccumulator_*rInvMass_;
		Pos_   += ImpulseAccumulator_*(rInvMass_*rDeltaTime);
		break;
	default:
		OR_ASSERT( false );
		break;
	}

	/* clear the accumulators */
	this->ResetAccumulators();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::UpdatePhysics_Euler
 *
 *  \author Gabriel Peyré 2001-09-18
 *
 *	Peform a step in the explicit \e Euler integration.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Particule::UpdatePhysics_Euler()
{
	OR_Float rDeltaTime = OR_PhysicEntityManager::GetTimeStep();
	
	PosOld_ = Pos_;

	/* add the impulse */	
	Speed_ += ImpulseAccumulator_*rInvMass_;
//	Pos_   += ImpulseAccumulator_*(rInvMass_*rDeltaTime);

	Pos_   += Speed_*rDeltaTime;
	Speed_ += ForceAccumulator_*(rInvMass_*rDeltaTime);

	
	
#if 0
	/* update equation of movement */
	Pos_   += Speed_*rDeltaTime;
	Speed_ += ForceAccumulator_*(rInvMass_*rDeltaTime);
	
	/* add the impulse of deflexion */
	Speed_ += ImpulseAccumulator_*rInvMass_;
	Pos_   += ImpulseAccumulator_*(rInvMass_*rDeltaTime);
#endif	

	/* clear the accumulators */
	this->ResetAccumulators();
}



//-----------------------------------------------------------------------------
// Name: OR_Particule::ComputeSpeed
/**
*
*	Compute the speed using the position before and after.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
void OR_Particule::ComputeSpeed()
{
	OR_ASSERT( OR_PhysicEntityManager::GetTimeStep()>0 );
	Speed_ = (Pos_ - PosOld_)/OR_PhysicEntityManager::GetTimeStep();
}


void OR_Particule::BuildFromFile( OR_File& file )
{
	/** \TODO Gab fill in this */
}

void OR_Particule::BuildToFile( OR_File& file )
{
	/** \TODO Gab fill in this */
}

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

