/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MagneticForce.cpp
 *  \brief Implementation of class OR_MagneticForce
 *  \author Gabriel Peyr� 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_MagneticForce.cpp (c) Gabriel Peyr� & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_MagneticForce.h"

#ifndef OR_USE_INLINE
	#include "OR_MagneticForce.inl"
#endif

using namespace OR;

/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce::ProcessParticule
/** 
 *   @param  particule The particule we want to compute the force.
 *   \author Gabriel Peyr� 2001-08-04
 *
 *	 Compute the force acting on the particule, and then add it to its 
 *	 force accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MagneticForce::ProcessParticule(OR_Particule& particule)
{
	particule.AddForce(particule.GetSpeed()^MagneticField_);
}



/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce::ProcessObject
/** 
 *  @param  handler The handler of the object we want to compute the force.
 *  \author Gabriel Peyr� 2001-08-04
 * 
 *	Compute the force acting on the object, and then add it to its 
 *	force accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MagneticForce::ProcessObject(OR_RigidBody& obj)
{
	obj.AddForce(obj.GetSpeed()^MagneticField_);
}

/*------------------------------------------------------------------------------*/
// Name : OR_ConstantForce::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyr� 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MagneticForce::BuildFromFile( OR_File& file )
{
	file >> MagneticField_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_MagneticForce::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyr� 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_MagneticForce::BuildToFile( OR_File& file )
{
	file << MagneticField_;
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

