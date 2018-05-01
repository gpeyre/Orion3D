/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DampedSpringConstraint.cpp
 *  \brief Implementation of class OR_DampedSpringConstraint
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_DampedSpringConstraint.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_DampedSpringConstraint.h"

#ifndef OR_USE_INLINE
	#include "OR_DampedSpringConstraint.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
//  Name : OR_DampedSpringConstraint::Update
/** 
 *  \author Gabriel Peyré 2001-08-04
 *
 *   add the spring force to the accumulator of each target
 */ 
/*------------------------------------------------------------------------------*/
void OR_DampedSpringConstraint::Update()
{
	OR_ASSERT(pTarget1_!=NULL);
	OR_ASSERT(pTarget2_!=NULL);

	OR_Vector3D delta_P = pTarget1_->GetPosition() - pTarget2_->GetPosition();
	OR_Vector3D delta_V = pTarget1_->GetSpeed() - pTarget2_->GetSpeed();
	OR_Float rDist = ~delta_P;

	if( rDist>OR_EPSILON )
	{
		OR_Vector3D delta_P_normalized = delta_P/rDist;
		OR_Float rFactorS = (rDist - rRestLength_)*rStiffness_;
		OR_Float rFactorD = (delta_V*delta_P_normalized)*rDampling_;
		OR_Vector3D Forces = delta_P_normalized*(rFactorS - rFactorD);
		/* add it to each accumulator */
		pTarget1_->AddForce(-Forces);
		pTarget2_->AddForce( Forces);
	}
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

