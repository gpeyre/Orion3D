/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Gizmo.inl
 *  \brief Inlined methods of class OR_Gizmo
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Gizmo.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Gizmo::ResolveImpulse
 *
 *  \param  particule The particule to deflect
 *  \param  Normal The normal at impact
 *  \param  ImpactPos the impact point
 *  \author Gabriel Peyré 2001-09-08
 *
 *	Compute the impulse to add to both objects.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Gizmo::ResolveImpulse(OR_Particule& particule, OR_Vector3D& Normal, OR_Vector3D& ImpactPos)
{
	/* compute the impulse created by the choc, in local coords */
	OR_Vector3D rA = ImpactPos - this->GetAbsolutePosition();
	/* compute the speed of the impact point */
	OR_Vector3D BodySpeed = pRigidBody_->ComputeSpeed( rA );
	/* compute relative speed along the normal */
	OR_Float    rSpeedRel = ( BodySpeed - particule.GetSpeed() )*Normal;

	/* check if objects are moving away */
//	if( rSpeedRel<0 )
//		return;

	OR_Float rBounce   = rBounce_*particule.GetBounce();

	OR_Float rImpulseDenom = pRigidBody_->GetInvMass() + particule.GetInvMass() +
				Normal*( (pRigidBody_->GetIWorldInv()*(rA^Normal))^rA );
	OR_ASSERT( rImpulseDenom>0 );

	OR_Float rImpulse   = -(1+rBounce)*rSpeedRel / rImpulseDenom;
	OR_Vector3D Impulse = Normal*rImpulse;

	pRigidBody_->AddForceImpulse( Impulse );
	pRigidBody_->AddTorqueImpulse( rA^Impulse );

	particule.AddImpulse( -Impulse );
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

