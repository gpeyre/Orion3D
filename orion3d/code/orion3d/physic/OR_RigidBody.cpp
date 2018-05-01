/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_RigidBody.cpp
 *  \brief Implementation of class rigid body.
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_RigidBody.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_RigidBody.h"
#include "OR_PhysicEntityManager.h"
#include "OR_PhysicModel.h"
#include "../objects/OR_Object.h"

#ifndef OR_USE_INLINE
	#include "OR_RigidBody.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody constructor
/** 
 *  \param  object the object that use this rigid body.
 *	\param  bAssignRigidBodyToObject do we need to link the rigid body to the object ?
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_RigidBody::OR_RigidBody(OR_Object& object, OR_Bool bAssignRigidBodyToObject )
:	OR_PhysicEntity(),
	rMass_        ( 1 ),
	bUsePhysic_   ( true ),
	pForceManager_( NULL ),
	rBounce_	  ( 0.8f ),
	rFriction_	  ( 0 ),
	pPhysicModel_ ( NULL )
{
	pObject_ = &object;
	if( bAssignRigidBodyToObject )
		pObject_->SetRigidBody( *this );
	this->SynchronizeWithObject();
}



/*------------------------------------------------------------------------------*/
// Name : OR_RigidBody destructor
/** 
 *  \author Gabriel Peyré 2001-08-26
 */ 
/*------------------------------------------------------------------------------*/
OR_RigidBody::~OR_RigidBody()
{
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::UpdatePhysics_RK4
 *
 *  \author Gabriel Peyré 2001-08-28
 *
 *	update the physic computrations using a \e RK4 scheme.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::UpdatePhysics_RK4( OR_U32 nStepRK4 )
{
	OR_Float rDeltaTime = OR_PhysicEntityManager::GetTimeStep();
	
	OR_Vector3D   RK4Offset;
	OR_Quaternion RK4OffsetQuat;
	
		/*
		 *	d Pos_(t)
		 *	--------- = Speed_(t)
		 *	    dt
		 *
		 *	d Rot_(t)   1
		 *	--------- = - * (#Omega_(t))*Rot_(t)
		 *      dt      2
		 *
		 *	d P_(t)
		 *	------- = ForceAccumulator_(t)
		 *	  dt
		 *	
		 *	d L_(t)
		 *	------- = TorqueAccumulator_(t)
		 *	  dt
		 */

	switch( nStepRK4 )
	{
	case 1:
		/* save speed & position at current time */
		Cur_Pos_ = Pos_;
		Cur_Rot_ = Rot_;
		Cur_P_   = P_;
		Cur_L_   = L_;
		
		/* Pos_ *****************************************/
		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Pos_Accumulator_ = RK4Offset*OR_RK4_COEF1;
		/* set up state variable for next step */
		Pos_ = Cur_Pos_ + RK4Offset*0.5f;
		
		/* Rot_ *****************************************/
		/* compute the RK4 offset */
		RK4OffsetQuat = (OR_Quaternion(Omega_)*Rot_)*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Rot_Accumulator_ = RK4OffsetQuat*OR_RK4_COEF1;
		/* set up state variable for next step */
		Rot_   = Cur_Rot_ + RK4OffsetQuat*0.5f;

		/* P_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_P_Accumulator_ = RK4Offset*OR_RK4_COEF1;
		/* set up state variable for next step */
		P_ = Cur_P_ + RK4Offset*0.5f;

		/* L_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = TorqueAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_L_Accumulator_ = RK4Offset*OR_RK4_COEF1;
		/* set up state variable for next step */
		L_ = Cur_L_ + RK4Offset*0.5f;
		break;

	case 2:
		/* Pos_ *****************************************/
		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Pos_Accumulator_ += RK4Offset*OR_RK4_COEF2;
		/* set up state variable for next step */
		Pos_ = Cur_Pos_ + RK4Offset*0.5f;
		
		/* Rot_ *****************************************/
		/* compute the RK4 offset */
		RK4OffsetQuat = (OR_Quaternion(Omega_)*Rot_)*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Rot_Accumulator_ += RK4OffsetQuat*OR_RK4_COEF2;
		/* set up state variable for next step */
		Rot_   = Cur_Rot_ + RK4OffsetQuat*0.5f;
		
		/* P_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_P_Accumulator_ += RK4Offset*OR_RK4_COEF2;
		/* set up state variable for next step */
		P_ = Cur_P_ + RK4Offset*0.5f;
		
		/* L_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = TorqueAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_L_Accumulator_ += RK4Offset*OR_RK4_COEF2;
		/* set up state variable for next step */
		L_ = Cur_L_ + RK4Offset*0.5f;
		break;

	case 3:
		/* Pos_ *****************************************/
		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Pos_Accumulator_ += RK4Offset*OR_RK4_COEF3;
		/* set up state variable for next step */
		Pos_ = Cur_Pos_ + RK4Offset;
		
		/* Rot_ *****************************************/
		/* compute the RK4 offset */
		RK4OffsetQuat = (OR_Quaternion(Omega_)*Rot_)*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Rot_Accumulator_ += RK4OffsetQuat*OR_RK4_COEF3;
		/* set up state variable for next step */
		Rot_   = Cur_Rot_ + RK4OffsetQuat;
		
		/* P_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_P_Accumulator_ += RK4Offset*OR_RK4_COEF3;
		/* set up state variable for next step */
		P_ = Cur_P_ + RK4Offset;
		
		/* L_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = TorqueAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_L_Accumulator_ += RK4Offset*OR_RK4_COEF3;
		/* set up state variable for next step */
		L_ = Cur_L_ + RK4Offset;
		break;

	case 4:	
		/* save previous position, used for deflexion */

		/* Pos_ *****************************************/
		/* compute the RK4 offset */
		RK4Offset = Speed_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Pos_Accumulator_ += RK4Offset*OR_RK4_COEF4;
		/* set up state variable for next step */
		Pos_ = Cur_Pos_ + RK4_Pos_Accumulator_;
		
		/* Rot_ *****************************************/
		/* compute the RK4 offset */
		RK4OffsetQuat = (OR_Quaternion(Omega_)*Rot_)*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_Rot_Accumulator_ += RK4OffsetQuat*OR_RK4_COEF4;
		/* set up state variable for next step */
		Rot_   = Cur_Rot_ + RK4_Rot_Accumulator_;
		
		/* P_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = ForceAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_P_Accumulator_ += RK4Offset*OR_RK4_COEF4;
		/* set up state variable for next step */
		P_ = Cur_P_ + RK4_P_Accumulator_;
		
		/* L_ *******************************************/
		/* compute the RK4 offset */
		RK4Offset = TorqueAccumulator_*rDeltaTime;
		/* accumulate the result with correct RK4 weight */
		RK4_L_Accumulator_ += RK4Offset*OR_RK4_COEF4;
		/* set up state variable for next step */
		L_ = Cur_L_ + RK4_L_Accumulator_;

		
		/* add the impulse of deflexion */
		P_ += ForceImpulseAccumulator_;
		L_ += TorqueImpulseAccumulator_;
		break;
	default:
		OR_ASSERT( false );
		break;
	}
	
	this->ComputeAuxiliaryVariables();

	if( nStepRK4==4 )
	{
		/* save previous position */
		WorldToBodyOld_ = WorldToBody_;
		this->ComputeWorldToBody();		
	}

	/* clear the accumulators */
	this->ResetAccumulators();
	

}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::UpdatePhysics_Euler
 *
 *  \author Gabriel Peyré 2001-09-18
 *
 *	update the physic computrations using an \e explicit \e Euler scheme.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::UpdatePhysics_Euler()
{
	
		/*
		 *	d Pos_(t)
		 *	--------- = Speed_(t)
		 *	    dt
		 *
		 *	d Rot_(t)   1
		 *	--------- = - * (#Omega_(t))*Rot_(t)
		 *      dt      2
		 *
		 *	d P_(t)
		 *	------- = ForceAccumulator_(t)
		 *	  dt
		 *	
		 *	d L_(t)
		 *	------- = TorqueAccumulator_(t)
		 *	  dt
		 */	
	
	OR_Float rDeltaTime = OR_PhysicEntityManager::GetTimeStep();
	
	/* add the impulse */
	P_ += ForceImpulseAccumulator_;
	/* todo check this */
//	L_ += TorqueImpulseAccumulator_;

	/* update the state variables using euler scheme */
	P_     += ForceAccumulator_*rDeltaTime;
	
	Pos_   += Speed_*rDeltaTime;
	
	L_     += TorqueAccumulator_*rDeltaTime;

	Rot_   += (OR_Quaternion(Omega_)*Rot_)*(rDeltaTime*0.5);

	
	this->ComputeAuxiliaryVariables();

	
	/* save previous position */
	WorldToBodyOld_ = WorldToBody_;
	this->ComputeWorldToBody();		


	/* clear the accumulators */
	this->ResetAccumulators();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::UpdatePhysics_Verlet
 *
 *  \author Gabriel Peyré 2001-09-08
 *
 *	update the physic computrations using a \e Verlet scheme.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::UpdatePhysics_Verlet()
{
	if( !bUsePhysic_ )
		return;
	
	/** \todo implement this */

	
	OR_Float rDeltaTime = OR_PhysicEntityManager::GetTimeStep();
	
	
	/* clear the accumulators */
	this->ResetAccumulators();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetPhysicType
 *	\return The type of the physic object
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The type is used by the physic engine to determine this entity should deflect that one, etc.
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity::T_PhysicEntity_Type OR_RigidBody::GetPhysicType()
{
	return OR_PhysicEntity::kPhysicEntity_RigidBody;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::ProcessForce
 *
 *  \param  ForceManager the manager common to the entities in the \c OR_PhysicEntityManager
 *  \author Gabriel Peyré 2001-09-10	
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::ProcessForce( OR_ForceManager& ForceManager )
{
	ForceManager.ProcessObject( *this );
	if( pForceManager_!=NULL )
		pForceManager_->ProcessObject( *this );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::ComputeWorldToBody
 *
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Compute the world to body matrix transformation.
 *	shoudl be used by the OR_Object as the transformation matrix.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::ComputeWorldToBody()
{
	WorldToBody_.SetRotation( RotMatrix_ );
	WorldToBody_.SetTranslation( Pos_/* - RotMatrix_*GravityCenter_ */ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::ComputeAuxiliaryVariables
 *
 *  \author Gabriel Peyré 2001-09-10
 *
 *	Knowing the state variables, compute the auxiliary variables.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::ComputeAuxiliaryVariables()
{
	/* compute RotMatrix_ */
	RotMatrix_ = Rot_.ToMatrix();

	/* compute IWorld_ */
	IWorld_    = RotMatrix_ * IBody_ * RotMatrix_.Transpose();
	IWorldInv_ = IWorld_.Invert();

	/* compute speed */
	Speed_ = P_*this->GetInvMass();

	/* compute Omega_ */
	Omega_ = IWorld_*L_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::ResetAccumulators
 *
 *  \return reset the force & impulse accumulators.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::ResetAccumulators()
{
	ForceAccumulator_.SetCoord(0,0,0);
	TorqueAccumulator_.SetCoord(0,0,0);
	ForceImpulseAccumulator_.SetCoord(0,0,0);
	TorqueImpulseAccumulator_.SetCoord(0,0,0);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetPhysicModel			
 *
 *  \param PhysicModel The physic model used for collision detection.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::SetPhysicModel(OR_PhysicModel& PhysicModel)
{
	pPhysicModel_ = &PhysicModel;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::GetPhysicModel
 *
 *  \return The physic model used for collision detection.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicModel* OR_RigidBody::GetPhysicModel()
{
	return pPhysicModel_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SynchronizeWithObject
 *
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Set the position and rotation of the rigid body to by in sync'
 *	with those of the object.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::SynchronizeWithObject()
{
	if( pObject_==NULL )
		return;
	
	/* set position and rotation */
	this->SetPosition( pObject_->GetAbsolutePosition() );
	Rot_.BuildFromMatrix( pObject_->GetAbsoluteRotation() );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetUpMassSphere
 *
 *  \param  rDensity density of the sphere.
 *  \param  rRadius radius of the sphere.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Set up mass and inertia to represent a sphere.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::SetUpMassSphere(OR_Float rDensity, OR_Float rRadius)
{
	this->GetIBody().LoadIdentity();
	this->SetMass( (4.0/3.0) * OR_PI * rRadius*rRadius*rRadius * rDensity );
	OR_Float Inertia = 0.4 * this->GetMass() * rRadius*rRadius;
	IBody_.SetData(0,0, Inertia);
	IBody_.SetData(1,1, Inertia);
	IBody_.SetData(2,2, Inertia);

	this->ComputeAuxiliaryVariables();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetUpMassBox
 *
 *  \param  rDensity density of the box.
 *  \param  Dim dimensions of the box.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Set up mass and inertia to represent a box.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::SetUpMassBox(OR_Float rDensity, OR_Vector3D Dim)
{
	this->GetIBody().LoadIdentity();
	OR_Float rMass = Dim[X]*Dim[Y]*Dim[Z]*rDensity;
	this->SetMass( rMass );
	
	IBody_.SetData(0,0, rMass/12.0 * (Dim[Y]*Dim[Y] + Dim[Z]*Dim[Z]) );
	IBody_.SetData(1,1, rMass/12.0 * (Dim[X]*Dim[X] + Dim[Z]*Dim[Z]) );
	IBody_.SetData(2,2, rMass/12.0 * (Dim[X]*Dim[X] + Dim[Y]*Dim[Y]) );

	this->ComputeAuxiliaryVariables();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetUpMassBox
 *
 *  \param  rDensity density of the box.
 *  \param  rDimX dimensions of the box on X axis.
 *  \param  rDimY dimensions of the box on Y axis.
 *  \param  rDimZ dimensions of the box on Z axis.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Set up mass and inertia to represent a box.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::SetUpMassBox(OR_Float rDensity, OR_Float rDimX, OR_Float rDimY, OR_Float rDimZ)
{
	this->SetUpMassBox( rDensity, OR_Vector3D(rDimX, rDimY, rDimZ) );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::SetUpMassCylinder
 *
 *  \param  rDensity density of the cylinder.
 *  \param  rHeight height of the cylinder.
 *  \param  rRadius radius of the cylinder.
 *  \author Gabriel Peyré 2001-11-05
 *
 * Set up mass and inertia to represent a cylinder aligned on the Z axis.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::SetUpMassCylinder(OR_Float rDensity, OR_Float rHeight, OR_Float rRadius)
{
	this->GetIBody().LoadIdentity();

	OR_Float M1 = OR_PI*rRadius*rRadius*rHeight*rDensity;			// cylinder mass
	OR_Float M2 = (4.0/3.0)*OR_PI*rRadius*rRadius*rRadius*rDensity;	// total cap mass
	this->SetMass( M1+M2 );
	OR_Float Ia = M1*(0.25*rRadius*rRadius + (1.0/12.0)*rHeight*rHeight) + M2*(0.4*rRadius*rRadius + 0.5*rHeight*rHeight);
	OR_Float Ib = (M1*0.5 + M2*0.4)*rRadius*rRadius;

	IBody_.SetData(0,0, Ia);
	IBody_.SetData(1,1, Ia);
	IBody_.SetData(2,2, Ib);

	this->ComputeAuxiliaryVariables();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::AdjustMass
 *
 *  \param  rNewMass new mass of the object.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Given mass parameters for some object, adjust them so the total mass is now \c rNewMass. 
 *	This is useful when using the above functions to set the mass parameters for certain objects 
 *	(they take the object density, not the total mass).		 
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::AdjustMass(OR_Float rNewMass)
{
	OR_Float rScale = rNewMass*this->GetInvMass();
	this->SetMass( rNewMass );
	IBody_.AutoScale( rScale );

	this->ComputeAuxiliaryVariables();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::TranslateMass
 *
 *  \param  Dir direction of translation.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Given mass parameters for some object, adjust them to represent 
 *	the object displaced by \c Dir relative to the body frame.  
 *
 *	If the body is translated by `a' relative to its point of reference,
 *	the new inertia about the point of reference is :
 *	\code
 *		I + mass*(crossmat(c)^2 - crossmat(c+a)^2)
 *	\endcode
 *
 *	where c is the existing center of mass and I is the old inertia.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::TranslateMass(OR_Vector3D Dir)
{
	OR_Matrix3x3 cCrossP = (this->GetGravityCenter()).CrossProductMatrix();
	cCrossP *= cCrossP;
	cCrossP.AutoScale( this->GetMass() );
	OR_Matrix3x3 caCrossP = (this->GetGravityCenter()+Dir).CrossProductMatrix();
	caCrossP *= caCrossP;
	caCrossP.AutoScale( this->GetMass() );

	this->SetIBody( IBody_ + cCrossP + caCrossP );
	
	/* ensure perfect symmetry */
	IBody_.SetData(1,0, IBody_.GetData(0,1) );
	IBody_.SetData(2,0, IBody_.GetData(0,2) );
	IBody_.SetData(2,1, IBody_.GetData(1,2) );
	
	/* adjust center of mass */
	this->GetGravityCenter() += Dir;

	this->ComputeAuxiliaryVariables();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::RotateMass
 *
 *  \param  Rot matrix of rotation.
 *  \author Gabriel Peyré 2001-11-05
 *
 *	Given mass parameters for some object, adjust them to represent 
 *	the object rotated by \c Rot relative to the body frame.
 *
 *	If the body is rotated by `R' relative to its point of reference,
 *	the new inertia about the point of reference is :
 *	\code
 *		R * I * R'
 *	\endcode
 *
 *	where I is the old inertia.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::RotateMass(OR_Matrix3x3 Rot)
{
	this->SetIBody( Rot * IBody_ * Rot.Transpose() );
	
	/* ensure perfect symmetry */
	IBody_.SetData(1,0, IBody_.GetData(0,1) );
	IBody_.SetData(2,0, IBody_.GetData(0,2) );
	IBody_.SetData(2,1, IBody_.GetData(1,2) );
	
	/* adjust center of mass */
	this->GetGravityCenter() = Rot*this->GetGravityCenter();

	this->ComputeAuxiliaryVariables();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::BuildSonList(T_ShellObjectList& ShellSonList)
{
	if( pObject_!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *pObject_, OR_String("obj_") + pObject_->GetName() );
	if( pForceManager_!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *pForceManager_, OR_String("force_manager") );
	if( pPhysicModel_!=NULL )
		OR_ADD_SHELL_SON(ShellSonList, *pPhysicModel_, OR_String("physic_model") );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBody::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBody::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Mass);	
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, IBody);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, GravityCenter);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Bounce);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Friction);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Position);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Rotation);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, P);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, L);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, IWorld);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Speed);
	OR_ADD_SHELL_ACCESSOR_FUNC(FuncDeclList, Omega);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, WorldToBody);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, WorldToBodyOld);

	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, RotationMatrix);

	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, ForceAccumulator);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, TorqueAccumulator);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, ForceImpulseAccumulator);
	OR_ADD_SHELL_GET_PRINT_FUNC(FuncDeclList, TorqueImpulseAccumulator);
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

