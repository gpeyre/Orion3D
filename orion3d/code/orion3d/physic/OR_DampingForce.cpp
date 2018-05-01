/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DampingForce.cpp
 *  \brief Implementation of class OR_DampingForce
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_DampingForce.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_DampingForce.h"

#ifndef OR_USE_INLINE
	#include "OR_DampingForce.inl"
#endif

using namespace OR;



/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce::ProcessParticule
/** 
 *   @param  particule The particule we want to compute the force.
 *   \author Gabriel Peyré 2001-08-04
 *
 *	 Compute the force acting on the particule, and then add it to its 
 *	 force accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_DampingForce::ProcessParticule(OR_Particule& particule)
{
	particule.AddForce(particule.GetSpeed()*(-rDamping_));
}



/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce::ProcessObject
/** 
 *  @param  handler The handler of the object we want to compute the force.
 *  \author Gabriel Peyré 2001-08-04
 * 
 *	Compute the force acting on the object, and then add it to its 
 *	force accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_DampingForce::ProcessObject(OR_RigidBody& handler)
{
	handler.AddForce(handler.GetSpeed()*(-rDamping_));
}

/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_DampingForce::BuildFromFile( OR_File& file )
{
	file >> rDamping_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_DampingForce::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_DampingForce::BuildToFile( OR_File& file )
{
	file << rDamping_;
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

