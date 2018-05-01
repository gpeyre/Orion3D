//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_GravityForce.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#ifdef __GNUG__
    #pragma implementation
#endif

#include "../stdafx.h"
#include "OR_GravityForce.h"

#ifndef OR_USE_INLINE
#   include "OR_GravityForce.inl"
#endif

using namespace OR;


//-----------------------------------------------------------------------------
// Name: OR_GravityForce::ProcessParticule
/**
*   @param  particule The particule we want to compute the force.
*
*	Compute the force acting on the particule, and then add it to its 
*	force accumulator.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
void OR_GravityForce::ProcessParticule(OR_Particule& particule)
{
	OR_Float rInvMass = particule.GetInvMass();
	if( rInvMass>0 )
		particule.AddForce(g_/rInvMass);
}


//-----------------------------------------------------------------------------
// Name: OR_GravityForce::ProcessObject
/**
*   @param  handler The handler of the object we want to compute the force.
*
*	Compute the force acting on the object, and then add it to its 
*	force accumulator.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
void OR_GravityForce::ProcessObject(OR_RigidBody& handler)
{
	OR_Float rMass = handler.GetMass();
	handler.AddForce(g_*rMass);
}

/*------------------------------------------------------------------------------*/
// Name : OR_GravityForce::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_GravityForce::BuildFromFile( OR_File& file )
{
	file >> g_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_GravityForce::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_GravityForce::BuildToFile( OR_File& file )
{
	file << g_;
}