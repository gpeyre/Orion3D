/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicEntityManager.inl
 *  \brief inlined methods for \c OR_PhysicEntityManager
 *  \author Gabriel Peyré 2001-09-07
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_PhysicEntityManager.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::UpdatePhysics_RK4
 *
 *  \author Gabriel Peyré 2001-09-08
 *
 *	Makes physics computation uing an RK4 scheme
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_PhysicEntityManager::UpdatePhysics_RK4()
{
	IT_ManagerMap_Template(OR_PhysicEntity) it1;

	for( OR_I32 nStepRK4=1; nStepRK4<5; ++nStepRK4 )
	{
		/* force computations *******************************************************/
		for( it1=begin(); it1!=end(); ++it1 )
			(*it1).second->ProcessForce( ForceManager_ );

		/* constraint manager */
		JointManager_.Update();

		/* resolve deflexions & collisions ONLY for the last step */
		if( nStepRK4==4 )
			CollisionManager_.ResolveCollisions();
			
		/* resolve physic */
		for( it1=begin(); it1!=end(); ++it1 )
			(*it1).second->UpdatePhysics_RK4(nStepRK4);
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::UpdatePhysics_Verlet
 *
 *  \author Gabriel Peyré 2001-09-08
 *
 *	Makes physics computation uing a verlet scheme
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_PhysicEntityManager::UpdatePhysics_Verlet()
{
	IT_ManagerMap_Template(OR_PhysicEntity) it1;
	
	/* force computations *******************************************************/
	for( it1=begin(); it1!=end(); ++it1 )
		(*it1).second->ProcessForce( ForceManager_ );

	/* constraint manager */
	JointManager_.Update();

	/* resolve deflexions & collisions  */
	CollisionManager_.ResolveCollisions();

	/* resolve physic */
	for( it1 = begin(); it1!=end(); ++it1 )
		(*it1).second->UpdatePhysics_Verlet();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::UpdatePhysics_Euler
 *
 *  \author Gabriel Peyré 2001-09-08
 *
 *	Makes physics computation uing a \e Euler scheme
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_PhysicEntityManager::UpdatePhysics_Euler()
{
	IT_ManagerMap_Template(OR_PhysicEntity) it1;
	
	/* force computations *******************************************************/
	for( it1=begin(); it1!=end(); ++it1 )
		(*it1).second->ProcessForce( ForceManager_ );
	
	/* constraint manager */
	JointManager_.Update();

	/* resolve deflexions & collisions  */
	CollisionManager_.ResolveCollisions();
	
	/* resolve physic */
	for( it1 = begin(); it1!=end(); ++it1 )
		(*it1).second->UpdatePhysics_Euler();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::ResetAccumulators
 *
 *  \author Gabriel Peyré 2001-09-07
 *
 *	Initialize the accumulators of each entity.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_PhysicEntityManager::ResetAccumulators()
{
	for( IT_ManagerMap_Template(OR_PhysicEntity) it1=begin(); it1!=end(); ++it1 )
		(*it1).second->ResetAccumulators();
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::OR_Float	
 *
 *  \return time step between two updates.
 *  \author Gabriel Peyré 2001-09-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_PhysicEntityManager::GetTimeStep()
{
	return rTimeStep_;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::SetTimeStep		
 *
 *  \param  rTimeStep time step between two updates.
 *  \author Gabriel Peyré 2001-09-16
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_PhysicEntityManager::SetTimeStep(OR_Float rTimeStep)
{
	rTimeStep_ = rTimeStep;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::SetSolverType
 *
 *  \param  SolverType The EDO solver used to resolve physic equations.
 *  \author Gabriel Peyré 2001-09-08
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_PhysicEntityManager::SetSolverType( OR_PhysicEntityManager::T_PhysicSolver_Type SolverType )
{
	SolverType_ = SolverType;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::T_PhysicEntity_Type 
 *
 *  \return The EDO solver used to resolve physic equations.
 *  \author Gabriel Peyré 2001-09-08
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_PhysicEntityManager::T_PhysicSolver_Type OR_PhysicEntityManager::GetSolverType()
{
	return SolverType_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::GetForceManager
 *
 *  \return The manager of forces common to all entities.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ForceManager& OR_PhysicEntityManager::GetForceManager()
{
	return ForceManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::OR_CollisionManager
 *
 *  \return Contains colliders for paire of objects that we must check collision.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_CollisionManager& OR_PhysicEntityManager::GetCollisionManager()
{
	return CollisionManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::OR_JointManager
 *
 *  \return the joint manager.
 *  \author Gabriel Peyré 2001-11-05
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_JointManager& OR_PhysicEntityManager::GetJointManager()
{
	return JointManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::GetCollider
 *
 *  \param  Entity0 a model for collision detection.
 *  \param  Entity1 another model for collision detection.
 *  \return the collider between these two models if it exist, NULL other wise.
 *  \author Gabriel Peyré 2001-11-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Collider_ABC* OR_PhysicEntityManager::GetCollider(OR_PhysicEntity& Entity1, OR_PhysicEntity& Entity2)
{
	return CollisionManager_.GetCollider( Entity1, Entity2 );
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

