/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_RigidBody.inl
 *  \brief Inlined methods of class OR_RigidBody
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_RigidBody.h"

namespace OR {




/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetMass
/** 
 *  \return rMass the mass of the rigid body.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_RigidBody::GetMass()
{
	return rMass_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetInvMass
 *
 *  \return The inverse of the mass.
 *  \author Gabriel Peyré 2001-09-07
 *
 *	If mass is to small, return a really high number.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_RigidBody::GetInvMass()
{
	if( rMass_<OR_EPSILON )
		return 1/OR_EPSILON;
	else
		return 1/rMass_;
}


/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::SetMass
/** 
 *  \param  rMass the mass of the rigid body.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetMass(const OR_Float rMass)
{
	rMass_ = rMass;
	/* re-compute parameters depending on the mass */
	if( rMass_>OR_EPSILON )
		Speed_ = P_/rMass_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetIBody
/** 
 *  \return Inertia matrix in body space.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix3x3& OR_RigidBody::GetIBody()
{
	return IBody_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::SetIBody
/** 
 *  \param  IBody Inertia matrix in body space.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetIBody(const OR_Matrix3x3& IBody)
{
	IBody_ = IBody;
	/* compute parameters depending on IBody */
	IBodyInv_ = IBody.Invert();
	IWorld_   = RotMatrix_*IBody_*( RotMatrix_.Transpose() );
	IWorldInv_= IWorld_.Invert();
	Omega_    = IWorld_*L_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetIBodyInv
/**
 *  \return Inverse of the inertia matrix, given in body frame.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix3x3& OR_RigidBody::GetIBodyInv()
{
	return IBodyInv_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetGravityCenter
 *
 *  \return The center of gravity, in body frame.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetGravityCenter()
{
	return GravityCenter_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetGravityCenter
 *
 *  \param  GravityCenter The center of gravity, in body frame.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetGravityCenter(OR_Vector3D& GravityCenter)
{
	GravityCenter_ = GravityCenter;
}


//-----------------------------------------------------------------------------
// Name: OR_RigidBody::GetBounce
/**
*   @return Bounce coefficient.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_RigidBody::GetBounce()
{
	return rBounce_;
}


//-----------------------------------------------------------------------------
// Name: OR_RigidBody::SetBounce
/**
*   @param  rBounce Bounce coefficient.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_RigidBody::SetBounce(OR_Float rBounce)
{
	rBounce_ = rBounce;
}


//-----------------------------------------------------------------------------
// Name: OR_RigidBody::GetFriction
/**
*   @return The friction coefficient.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Float OR_RigidBody::GetFriction()
{
	return rFriction_;
}


//-----------------------------------------------------------------------------
// Name: OR_RigidBody::SetFriction
/**
*   @param  rFriction The friction coefficient.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_RigidBody::SetFriction(OR_Float rFriction)
{
	rFriction_ = rFriction;
}


/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetPosition
/** 
 *  \return the absolute position of the object.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetPosition()
{
	return Pos_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::SetPosition
/** 
 *  \param  Pos the absolute position of the object.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetPosition(const OR_Vector3D Pos)
{
	Pos_ = Pos;
	/* re-set the parameters depending on the position */
	ComputeWorldToBody();
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetRotation
/** 
 *  \return The orientation of the object.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Quaternion& OR_RigidBody::GetRotation()
{
	return Rot_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::SetRotation
/** 
 *  \param  Rot The orientation of the object.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetRotation(const OR_Quaternion& Rot)
{
	Rot_ = Rot;
	/* re-set the parameters depending on the orientation */
	RotMatrix_ = Rot_.ToMatrix();

	ComputeWorldToBody();

}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetP
/** 
 *  \return The quantity of movement (ie. p=m*v).
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetP()
{
	return P_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::SetP
/** 
 *  \param  P The quantity of movement (ie. p=m*v).
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetP(const OR_Vector3D& P)
{
	P_ = P;
	/* re-compute the parameters depending on P */
	Speed_ = P_/rMass_;
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody::GetL
/** 
 *  \return The linear momentum.
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetL()
{
	return L_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetL
 *
 *  \param  L The linear momentum.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetL(const OR_Vector3D& L)
{
	L_ = L;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetIWorldInv
 *
 *  \return Inverse of the inertia matrix, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix3x3& OR_RigidBody::GetIWorldInv()
{
	return IWorldInv_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetIWorld
 *
 *  \return Inertia matrix, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix3x3& OR_RigidBody::GetIWorld()
{
	return IWorld_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetSpeed
 *
 *  \return Speed of the object, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetSpeed()
{
	return Speed_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetSpeed
 *
 *  \param  speed Speed of the object, in world frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetSpeed(const OR_Vector3D& speed)
{
	Speed_ = speed;
	/* compute variable depending on speed */
	P_ = Speed_*rMass_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetOmega
 *
 *  \return Instananate rotation axis.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetOmega()
{
	return Omega_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetOmega
 *
 *  \param  OmegaInstananate rotation axis.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetOmega(const OR_Vector3D& Omega)
{
	Omega_ = Omega;
	/* compute variable depending on omega */
	L_ = IWorldInv_*Omega_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetWorldToBody
 *
 *  \return Transformation matrix from world frame to body frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix4x4& OR_RigidBody::GetWorldToBody()
{
	return WorldToBody_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetWorldToBodyOld
 *
 *  \return Previous transformation matrix from world frame to body frame.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix4x4& OR_RigidBody::GetWorldToBodyOld()
{
	return WorldToBodyOld_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::AddForce
 *
 *  \param  force The force to add to the accumulator.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Add a force to the accumulator of forces.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::AddForce(const OR_Vector3D& force)
{
	ForceAccumulator_ += force;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::AddTorque
 *
 *  \param  torque The torque to add to the accumulator of torque.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Add a torque to the accumulator of torque.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::AddTorque(const OR_Vector3D& torque)
{
	TorqueAccumulator_ += torque;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::AddForceImpulse
 *
 *  \param  forceImpulse The force impulse to add to the force impulse accumulator.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Add a force i^mpulse to the force impulse accumulator.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::AddForceImpulse(const OR_Vector3D& forceImpulse)
{
	ForceImpulseAccumulator_ += forceImpulse;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::AddTorqueImpulse
 *
 *  \param  torqueImpulse The torque impulse to add to the torque impulse accumulator.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Add a torque impulse to the torque impulse accumulator.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::AddTorqueImpulse(const OR_Vector3D& torqueImpulse)
{
	TorqueImpulseAccumulator_ += torqueImpulse;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::EnablePhysicComputations
 *
 *	\return Previous state.	
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Enable physic computation.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_RigidBody::EnablePhysicComputations()
{
	OR_Bool bOld = bUsePhysic_;
	bUsePhysic_ = true;
	return bOld;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::DisablePhysicComputations
 *
 *	\return Previous state.	
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Disable physic computation.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_RigidBody::DisablePhysicComputations()
{
	OR_Bool bOld = bUsePhysic_;
	bUsePhysic_ = false;
	return bOld;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::TogglePhysicComputations
 *
 *	\return Does the body use physics now ?
 *  \author Gabriel Peyré 2001-08-28
 *
 *	Toggle on/off physic computations.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_RigidBody::TogglePhysicComputations()
{
	bUsePhysic_ = !bUsePhysic_;
	return bUsePhysic_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::IsUsingPhysic
 *
 *  \return Does the physic computation are enable ?
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_RigidBody::IsUsingPhysic()
{
	return bUsePhysic_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::ComputeSpeed
 *
 *  \param  Radius vector from center of gravity to point on the rigid body.
 *  \return speed of a given point on the rigid body.
 *  \author Gabriel Peyré 2001-09-09
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D OR_RigidBody::ComputeSpeed( OR_Vector3D Radius )
{
	return Speed_ + Omega_^Radius;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::ComputePos
 *
 *  \param  Radius vector from center of gravity to point on the rigid body.
 *  \return Position of a given point on the rigid body.
 *  \author Gabriel Peyré 2001-09-09
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D OR_RigidBody::ComputePos( OR_Vector3D Radius )
{
	return WorldToBody_*Radius;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetForceManager
 *
 *  \return The manager of forces specific to this rigid body.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ForceManager* OR_RigidBody::GetForceManager()
{
	return pForceManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetForceManager
 *
 *  \param  ForceManager The manager of forces specific to this rigid body.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetForceManager(OR_ForceManager& ForceManager)
{
	pForceManager_ = &ForceManager;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetJointID
 *
 *  \return the ID used by the joint manager to store this rigid body
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_RigidBody::GetJointID()
{
	return nJointID_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetJointID
 *
 *  \param  nJointID the ID used by the joint manager to store this rigid body
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBody::SetJointID(OR_U32 nJointID)
{
	nJointID_ = nJointID;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetRotationMatrix
 *
 *  \return The rotation matrix of the rigid body.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Matrix3x3& OR_RigidBody::GetRotationMatrix()
{
	return RotMatrix_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetForceAccumulator
 *
 *  \return the force accumulator.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetForceAccumulator()
{
	return ForceAccumulator_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetTorqueAccumulator
 *
 *  \return the torque accumulator.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetTorqueAccumulator()
{
	return TorqueAccumulator_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetForceImpulseAccumulator
 *
 *  \return the force impulse accumulator.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetForceImpulseAccumulator()
{
	return ForceImpulseAccumulator_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetTorqueImpulseAccumulator
 *
 *  \return the torque impulse accumulator.
 *  \author Gabriel Peyré 2001-11-06
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Vector3D& OR_RigidBody::GetTorqueImpulseAccumulator()
{
	return TorqueImpulseAccumulator_;
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

