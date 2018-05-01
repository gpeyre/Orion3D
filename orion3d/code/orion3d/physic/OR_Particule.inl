/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Particule.inl
 *  \brief Inlined functions of particule class.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Particule.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule constructor
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Particule::OR_Particule()
{
	rInvMass_=1;
	nNbrConstaints_=0;
	bIsSpeedSpecified_=false;
	rBounce_=1;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule destructor
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Particule::~OR_Particule()
{
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::AddForce
 *
 *  \param  force The force to add to the accumulator.
 *  \author Gabriel Peyré 2001-07-18
 *
 *	Add a force acting on the particule.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::AddForce(OR_Vector3D& force)
{
	ForceAccumulator_ += force;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::AddImpulse
 *
 *  \param  impulse The impulse to add to the accumulator.
 *  \author Gabriel Peyré 2001-09-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::AddImpulse(OR_Vector3D& impulse)
{
	ImpulseAccumulator_ += impulse;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::AddConstaint
 *
 *  \author Gabriel Peyré 2001-07-18
 *
 *	Tells to the particule that a constraint is acting on it.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::AddConstaint()
{
	nNbrConstaints_++;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::RemoveConstraint
 *
 *  \author Gabriel Peyré 2001-07-18
 *
 *	Tells to the particule that a constraint is no more acting on it.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::RemoveConstraint()
{
	nNbrConstaints_--;
	OR_ASSERT(nNbrConstaints_>=0);
	if(nNbrConstaints_<0)
		nNbrConstaints_=0;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::GetPosition
 *
 *  \return Current position of the particule.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Particule::GetPosition()
{
	return Pos_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::SetPosition
 *
 *  \param  position New position of the particule.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::SetPosition(OR_Vector3D& position)
{
	Pos_=position;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::GetOldPosition
 *
 *  \return Current old position of the particule.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Particule::GetOldPosition()
{
	return PosOld_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::SetOldPosition
 *
 *  \param  position Old position of the particule.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::SetOldPosition(OR_Vector3D& position)
{
	PosOld_=position;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::ReSetPosition
 *
 *  \param  position new position of the particule.
 *  \author Gabriel Peyré 2001-10-24
 *
 *	Reset \b both the old and the current position of the particules.
 *	Usefull to re-init a particule (for exemple for the particules system).
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::ReSetPosition(OR_Vector3D& position)
{
	Pos_    = position;
	PosOld_ = position;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::GetInvMass
 *
 *  \return The inverse of the mass of the particule.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Particule::GetInvMass()
{
	return rInvMass_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::SetInvMass
 *
 *  \param  rInvMass The new inverse of the mass.
 *  \author Gabriel Peyré 2001-07-18
 *
 *	An inverse mass of 0 mean the particule won't move.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::SetInvMass(OR_Float rInvMass)
{
	rInvMass_=rInvMass;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::GetSpeed
 *
 *  \return the speed of the particule
 *  \author Gabriel Peyré 2001-07-20
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_Particule::GetSpeed()
{
	return Speed_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::SetSpeed
 *
 *  \param  Speed the speed of the particule
 *  \author Gabriel Peyré 2001-07-30
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::SetSpeed(OR_Vector3D&   Speed)
{
	Speed_=Speed;
	/* now, Pos_ needs to be recomputed at next update */
	bIsSpeedSpecified_=true;
}


//-----------------------------------------------------------------------------
// Name: OR_Particule::ReSet
/**
*	Can be called for example when we re-use particule from a garbage collector.
*/
///	\author Gabriel Peyré 2001-08-30
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Particule::ReSet()
{
	rInvMass_=1;
	nNbrConstaints_=0;
	bIsSpeedSpecified_=false;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Particule::Translate
 *
 *  \param  direction Direction of the move
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::Translate(OR_Vector3D& direction)
{
	Pos_ += direction;
	PosOld_ += direction;
}

/*------------------------------------------------------------------------------*/
// Name : OR_Particule::GetBounce
/** 
 *  \return the bounce restitution coefficient.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Particule::GetBounce()
{
	return rBounce_;
}

/*------------------------------------------------------------------------------*/
// Name : OR_Particule::SetBounce
/** 
 *  \param  rBounce the bounce restitution coefficient.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Particule::SetBounce(OR_Float rBounce)
{
	rBounce_ = rBounce;
}


//-----------------------------------------------------------------------------
// Name: OR_Particule::ResetAccumulators
/**
*   Set to (0,0,0) the force & impulse accumulators.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Particule::ResetAccumulators()
{
	ForceAccumulator_.SetCoord(0,0,0);
	ImpulseAccumulator_.SetCoord(0,0,0);
}


} // End namespace OR

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

