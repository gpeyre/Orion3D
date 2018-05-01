//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Deflector_ABC.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Deflector_ABC.h"

#ifndef OR_USE_INLINE
#   include "OR_Deflector_ABC.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Deflector_ABC::UpdatePhysics_RK4
 *
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Nothing to update, a deflector is not a "real" physic entity.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Deflector_ABC::UpdatePhysics_RK4( OR_U32 nStepRK4 )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Deflector_ABC::UpdatePhysics_Verlet
 *
 *  \author Gabriel Peyré 2001-09-08
 *
 *	Nothing to update, a deflector is not a "real" physic entity.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Deflector_ABC::UpdatePhysics_Verlet()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Deflector_ABC::UpdatePhysics_Euler
 *
 *  \author Gabriel Peyré 2001-09-18
 *
 *	Nothing to update, a deflector is not a "real" physic entity.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Deflector_ABC::UpdatePhysics_Euler()
{
	/* NOTHING */	
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Deflector_ABC::GetPhysicType
 *	\return physic type of the object
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The type is used by the physic engine to determine this entity should deflect that one, etc.
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity::T_PhysicEntity_Type OR_Deflector_ABC::GetPhysicType()
{
	return OR_PhysicEntity::kPhysicEntity_Deflector;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Deflector_ABC::ProcessForce
 *
 *  \param  ForceManager the manager common to the entities in the \c OR_PhysicEntityManager.
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Nothing to update, a deflector is not a "real" physic entity.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Deflector_ABC::ProcessForce( OR_ForceManager& ForceManager )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Deflector_ABC::ResetAccumulators
 *
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Nothing to update, a deflector is not a "real" physic entity.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Deflector_ABC::ResetAccumulators()
{
	/* NOTHING */
}
