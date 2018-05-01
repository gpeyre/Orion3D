/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_JointManager.cpp
 *  \brief Definition of class \c OR_JointManager
 *  \author Gabriel Peyré 2001-10-30
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_JointManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_JointManager.h"

#ifndef OR_USE_INLINE
	#include "OR_JointManager.inl"
#endif

using namespace OR;

OR_JointManager* OR_JointManager::pStaticThis_ = NULL;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager constructor
 *
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Reserve free IDs for the rigid bodies.
 */ 
/*------------------------------------------------------------------------------*/
OR_JointManager::OR_JointManager()
:	OR_SmartManagerMap_Template<OR_Joint_ABC>(),
	nConstrDim_	( 0 )
{
	IDStack_.Init(0, OR_NBR_MAX_JOINT);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager destructor
 *
 *  \author Gabriel Peyré 2001-10-31
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_JointManager::~OR_JointManager()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::AddRigidBody
 *
 *  \param  RB a rigid body involoved in a contraint.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManager::AddRigidBody(OR_RigidBody& RB)
{
	/* scans the map to check if the rigid body is already used */
	for( IT_JointTokenVector it=JointTokenVector_.begin(); it!=JointTokenVector_.end(); ++it )
	{
		OR_JointManagerToken* pJointToken = *it;
		if( pJointToken->GetRigidBody()==&RB )
			return;
	}

	/* the rigid body is not already used, so create an entry for him */
	OR_ASSERT( !IDStack_.IsEmpty() );
	OR_U32 nID = IDStack_.GetNewID();
	RB.SetJointID( nID );

	/* create an entry in the token list */
	if( nID+1>JointTokenVector_.size() )
	{
		JointTokenVector_.resize( nID+1 );
		JointTokenVector_[nID] = new OR_JointManagerToken();
	}

	JointTokenVector_[nID]->SetRigidBody( RB );
	InvMassMatrix_.AddBlock( JointTokenVector_[nID]->GetInvMassMatrixBlock() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::RemoveRigidBody
 *
 *  \param  RB the rigid body to remove from the list.
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Call this method \b AFTER having removing the koint this rigid body is 
 *	involved in.
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManager::RemoveRigidBody(OR_RigidBody& RB)
{
	/* check if the rigid body is still used */
	for( IT_ManagerMap_Template(OR_Joint_ABC) it=begin(); it!=end(); ++it )
	{
		OR_Joint_ABC* pJoint = (*it).second;
		if( &pJoint->GetRigidBody1()==&RB || 
			&pJoint->GetRigidBody2()==&RB )
			return;
	}

	/* the rigid body is no more used, so remove it from the list, and remove it's block */
	OR_U32 nID = RB.GetJointID();
	OR_ASSERT( !IDStack_.IsAvailable( nID ) );
	IDStack_.ReleaseID( nID );
	OR_ASSERT( JointTokenVector_.size()>nID );
	InvMassMatrix_.RemoveBlock( JointTokenVector_[nID]->GetInvMassMatrixBlock() );
	JointTokenVector_[nID]->ReleaseRigidBody();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::AddJoint
 *
 *  \param  Joint the new joint to add to the manager.
 *  \return the ID of the joint.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
OR_I32 OR_JointManager::AddJoint(OR_Joint_ABC& Joint)
{
	this->AddRigidBody( Joint.GetRigidBody1() );
	this->AddRigidBody( Joint.GetRigidBody2() );
	Joint.SetJacobianMatrix( Jacobian_ );
	
	/* compute the new dimension of the constraint */
	nConstrDim_ += Joint.GetDimension();

	return this->AddElement( &Joint );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::RemoveJoint
 *
 *  \param  Joint the joint to remove to the manager.
 *  \author Gabriel Peyré 2001-10-31
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManager::RemoveJoint(OR_Joint_ABC& Joint)
{
	if( this->RemoveElement( &Joint )!=OR_ERROR )
	{
		/* we have remove a constraint, so compute the new dimension */
		nConstrDim_ -= Joint.GetDimension();
	}

	/* check if the rigid bodies are still used */
	this->RemoveRigidBody( Joint.GetRigidBody1() );
	this->RemoveRigidBody( Joint.GetRigidBody2() );
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::Update
 *
 *  \author Gabriel Peyré 2001-10-31
 *
 *	Resolve the constraints.
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManager::Update()
{
	OR_U32 nRigidBodyDim = this->GetRigidBodyDimension();

	if( nRigidBodyDim==0 )
		return;

	/* set up the dimensions of the system */
	Jacobian_.SetDim( nConstrDim_, nRigidBodyDim );
	Rhs_.Reset( nConstrDim_ );
	Constr_.Reset( nConstrDim_ );
	ConstrDeriv_.Reset( nConstrDim_ );
	Lambda_.Reset( nConstrDim_ );
	InvMassMatrix_.SetDim( nRigidBodyDim, nRigidBodyDim );
	ForceExt_.Reset( nRigidBodyDim );


	/* update each mass matrix block */
	for( IT_JointTokenVector it=JointTokenVector_.begin(); it!=JointTokenVector_.end(); ++it )
	{
		OR_JointManagerToken* pToken = *it;
		pToken->SetUpMassMatrix();
	}

	/* update each joint, ie. compute jacobian, constraint and constraint derivate */
	OR_U32 nConstrOffset = 0;
	for( IT_ManagerMap_Template(OR_Joint_ABC) it2=begin(); it2!=end(); ++it2 )
	{
		OR_Joint_ABC* pJoint = (*it2).second;
		pJoint->Update( Jacobian_, Constr_, ConstrDeriv_, nConstrOffset );
		nConstrOffset += pJoint->GetDimension();		
	}

	/* gather together forces acting on the system */
	this->ComputeRhs();

	/* set up static this for callback */
	pStaticThis_ = this;

	/* solve the system */
	OR_ASSERT( OR_VectorND::SolveConjugateGradient( Rhs_, Lambda_, LhsTimeVector ) );

	/* copute and assigne the forces and the torques */
	this->ComputeForceAndTorque();
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::ComputeRhs
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Gather together force and torque, and then form the rhs quantity.
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManager::ComputeRhs()
{
	ForceExt_.SetZero();
	Rhs_.SetZero();

	/* add the force to the system */
	for( IT_JointTokenVector it=JointTokenVector_.begin(); it!=JointTokenVector_.end(); ++it )
	{
		OR_JointManagerToken* pJointToken = *it;
		OR_ASSERT( pJointToken!=NULL );
		OR_RigidBody* pBody = pJointToken->GetRigidBody();
		OR_Vector3D Force;
		
		if( pBody!=NULL )
			Force = pBody->GetForceAccumulator();
		ForceExt_.SetData( pBody->GetJointID()*6,   Force[0] );
		ForceExt_.SetData( pBody->GetJointID()*6+1, Force[1] );
		ForceExt_.SetData( pBody->GetJointID()*6+2, Force[2] );
		
		Force.SetZero();
		
		if( pBody!=NULL )
			Force = pBody->GetTorqueAccumulator();
		ForceExt_.SetData( pBody->GetJointID()*6+3, Force[0] );
		ForceExt_.SetData( pBody->GetJointID()*6+4, Force[1] );
		ForceExt_.SetData( pBody->GetJointID()*6+5, Force[2] );
	}
	
	/* compute rhs = -J*W*Fext */
	OR_VectorND Temp( ForceExt_.GetDim() );
	OR_SparseMatrix::Multiply( this->GetInvMassMatrix(), ForceExt_, Temp );
	OR_SparseMatrix::Multiply( this->GetJacobian(), Temp, Rhs_ );
	OR_VectorND::Multiply(-1, Rhs_, Rhs_);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_JointManager::ComputeForceAndTorque
 *
 *  \author Gabriel Peyré 2001-11-06
 *
 *	Compute the force and torque acting on the system, and add them to each 
 *	rigid body.
 *
 *	Note that we use \c ForceExt_ as a tempoty variable, since it is no more used.
 */ 
/*------------------------------------------------------------------------------*/
void OR_JointManager::ComputeForceAndTorque()
{
	/* compute the force */
	OR_SparseMatrix::MultiplyTranspose( pStaticThis_->GetJacobian(), Lambda_, ForceExt_ );
	
	/* add the force to the system */
	for( IT_JointTokenVector it=JointTokenVector_.begin(); it!=JointTokenVector_.end(); ++it )
	{
		OR_JointManagerToken* pJointToken = *it;
		OR_ASSERT( pJointToken!=NULL );
		OR_RigidBody* pBody = pJointToken->GetRigidBody();
		if( pBody!=NULL )
		{
			OR_Vector3D Force;
			Force[0] = ForceExt_.GetData( pBody->GetJointID()*6   );
			Force[1] = ForceExt_.GetData( pBody->GetJointID()*6+1 );
			Force[2] = ForceExt_.GetData( pBody->GetJointID()*6+2 );
			pBody->AddForce( Force );
			Force[0] = ForceExt_.GetData( pBody->GetJointID()*6+3 );
			Force[1] = ForceExt_.GetData( pBody->GetJointID()*6+4 );
			Force[2] = ForceExt_.GetData( pBody->GetJointID()*6+5 );
			pBody->AddTorque( Force );
		}
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

