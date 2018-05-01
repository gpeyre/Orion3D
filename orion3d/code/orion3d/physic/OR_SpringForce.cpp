/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpringForce.cpp
 *  \brief Definition of class \c OR_SpringForce
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SpringForce.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SpringForce.h"

#ifndef OR_USE_INLINE
	    #include "OR_SpringForce.inl"
#endif

using namespace OR;

/*------------------------------------------------------------------------------*/
// Name : OR_SpringForce::ProcessParticule
/** 
 *   @param  particule The particule we want to compute the force.
 *   \author Gabriel Peyré 2001-08-04
 *
 *	 Compute the force acting on the particule, and then add it to its 
 *	 force accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpringForce::ProcessParticule(OR_Particule& particule)
{	
	OR_Vector3D delta_P = Anchor_ - particule.GetPosition();
	OR_Float rDist = ~delta_P;
	
	if( rDist>OR_EPSILON )
	{
		OR_Vector3D delta_P_normalized = delta_P/rDist;
		OR_Float rFactorS = (rDist - rRestLength_)*rStiffness_;
		OR_Float rFactorD = (particule.GetSpeed()*delta_P_normalized)*rDampling_;
		OR_Vector3D Forces = delta_P_normalized*(rFactorS - rFactorD);
		/* add the force to the accumulator */
		particule.AddForce( Forces);
	}
}



/*------------------------------------------------------------------------------*/
// Name : OR_SpringForce::ProcessObject
/** 
 *  @param  handler The handler of the object we want to compute the force.
 *  \author Gabriel Peyré 2001-08-04
 * 
 *	Compute the force acting on the object, and then add it to its 
 *	force accumulator.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpringForce::ProcessObject(OR_RigidBody& obj)
{
	OR_Vector3D delta_P = Anchor_ - obj.GetPosition();
	OR_Float rDist = ~delta_P;
	
	if( rDist>OR_EPSILON )
	{
		OR_Vector3D delta_P_normalized = delta_P/rDist;
		OR_Float rFactorS = (rDist - rRestLength_)*rStiffness_;
		OR_Float rFactorD = (obj.GetSpeed()*delta_P_normalized)*rDampling_;
		OR_Vector3D Forces = delta_P_normalized*(rFactorS - rFactorD);
		/* add the force to the accumulator */
		obj.AddForce( Forces );
		/** \todo add a torque and an attach in body frame */
	}
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
void OR_SpringForce::BuildFromFile( OR_File& file )
{
	file >> rDampling_
		 >> rStiffness_
		 >> rRestLength_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_SpringForce::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpringForce::BuildToFile( OR_File& file )
{
	file << rDampling_
		 << rStiffness_
		 << rRestLength_;
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

