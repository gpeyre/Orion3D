/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleManager.cpp
 *  \brief OR_ParticuleManager implementation
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ParticuleManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ParticuleManager.h"

#ifndef OR_USE_INLINE
	#include "OR_ParticuleManager.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::UpdatePhysics_RK4
 *
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Launch the physics computations on each particule using a RK4 scheme.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleManager::UpdatePhysics_RK4( OR_U32 nStepRK4 )
{	
	/* update the motion of each paticule */
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
		(*it)->UpdatePhysics_RK4( nStepRK4 );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::UpdatePhysics_Verlet
 *
 *  \author Gabriel Peyré 2001-09-08
 *
 *	Launch the physics computations on each particule using a RK4 scheme.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleManager::UpdatePhysics_Verlet()
{	
	/* update the motion of each paticule */
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
		(*it)->UpdatePhysics_Verlet();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::UpdatePhysics_Euler
 *
 *  \author Gabriel Peyré 2001-09-18
 *
 *	Launch the physics computations on each particule using an \e explicit \e Euler scheme.
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleManager::UpdatePhysics_Euler()
{
	/* update the motion of each paticule */
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
		(*it)->UpdatePhysics_Euler();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::GetPhysicType
 *
 *  \return The type of the physic entity.
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The type is used by the physic engine to determine this entity should deflect that one, etc.
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity::T_PhysicEntity_Type OR_ParticuleManager::GetPhysicType()
{
	return OR_PhysicEntity::kPhysicEntity_ParticuleManager;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::ProcessForce
 *
 *  \param  ForceManager the manager common to the entities in the \c OR_PhysicEntityManager
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleManager::ProcessForce( OR_ForceManager& ForceManager )
{
	/* solve the constraints */
	if( pConstraintManager_!=NULL)
		pConstraintManager_->Update();

	for( IT_ParticuleList it=begin(); it!=end(); ++it )
	{
		OR_Particule& Particule = *(*it);
		ForceManager.ProcessParticule( Particule );
		if( pForceManager_!=NULL )
			pForceManager_->ProcessParticule( Particule );
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::ResetAccumulators
 *
 *  \return reset the accumulators of each particule.
 *  \author Gabriel Peyré 2001-09-10
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleManager::ResetAccumulators()
{
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
		(*it)->ResetAccumulators();
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

