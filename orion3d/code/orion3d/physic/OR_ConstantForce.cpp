//*****************************************************************************
///	\author Gabriel Peyré 2001-08-30
//*****************************************************************************

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Particule.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#ifdef __GNUG__
    #pragma implementation
#endif

#include "../stdafx.h"
#include "OR_ConstantForce.h"

#ifndef OR_USE_INLINE
#   include "OR_ConstantForce.inl"
#endif

using namespace OR;

//-----------------------------------------------------------------------------
// Name: OR_ConstantForce::ProcessParticule
/**
*   @param  particule The particule we want to compute the force.
*
*	Compute the force acting on the particule, and then add it to its 
*	force accumulator.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_ConstantForce::ProcessParticule(OR_Particule& particule)
{
	particule.AddForce(Force_);
}


//-----------------------------------------------------------------------------
// Name: OR_ConstantForce::ProcessObject
/**
*   @param  handler The handler of the object we want to compute the force.
*
*	Compute the force acting on the object, and then add it to its 
*	force accumulator.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_ConstantForce::ProcessObject(OR_RigidBody& handler)
{
	handler.AddForce(Force_);
}


/*------------------------------------------------------------------------------*/
// Name : OR_ConstantForce::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ConstantForce::BuildFromFile( OR_File& file )
{
	file >> Force_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_ConstantForce::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ConstantForce::BuildToFile( OR_File& file )
{
	file << Force_;
}