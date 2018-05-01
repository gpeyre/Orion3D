/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CollisionManager.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_CollisionManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_CollisionManager.h"

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CollisionManager constructor
 *
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_CollisionManager::OR_CollisionManager()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CollisionManager destructor
 *
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/
OR_CollisionManager::~OR_CollisionManager()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CollisionManager::AddCollision
 *
 *	\param	RB1 first rigid body involved
 *	\param	RB2 second rigid body involved
 *  \param  Position Posiion of the collision point
 *  \param  Normal  Normal at collision.
 *  \param  EdgeA edge of collision in body A
 *  \param  EdgeB edge of collision in body B
 *  \param  bIsvertexFace is the contact a vertex/face one ?
 *  \author Gabriel Peyré 2001-08-28
 *
 *	If the garbage is empty, then create a new collision, else recycle an old one.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CollisionManager::AddCollision(OR_RigidBody& RB1, OR_RigidBody& RB2,
									   OR_Vector3D Position, OR_Vector3D Normal, 
									   OR_Vector3D EdgeA, OR_Vector3D EdgeB, OR_Bool bIsvertexFace)
{
	OR_Collision* pCollision = NULL;
	if( GarbageCollector_.empty() )
	{
		/* create a new collision */
		pCollision = new OR_Collision;
	}
	else
	{
		/* get it from the garbage collector */
		pCollision = GarbageCollector_.front();
		GarbageCollector_.pop_front();
	}
	/* init the collision */
	pCollision->SetBodyA(RB1);
	pCollision->SetBodyB(RB2);
	pCollision->SetPosition(Position);
	pCollision->SetNormal(Normal);
	pCollision->SetEdgeA(EdgeA);
	pCollision->SetEdgeB(EdgeB);
	pCollision->SetIsVertexFace(bIsvertexFace);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CollisionManager::GetCollider
 *
 *  \param  Entity0 a model for collision detection.
 *  \param  Entity1 another model for collision detection.
 *  \return the collider between these two models if it exist, NULL other wise.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_Collider_ABC* OR_CollisionManager::GetCollider( OR_PhysicEntity& Entity0, OR_PhysicEntity& Entity1 )
{
	for( IT_ColliderList it=ColliderList_.begin(); it!=ColliderList_.end(); ++it )
	{
		OR_Collider_ABC* pCollider = *it;
		if( (&pCollider->GetCollidee0()==&Entity0 &&  &pCollider->GetCollidee1()==&Entity1) || 
			(&pCollider->GetCollidee0()==&Entity1 &&  &pCollider->GetCollidee1()==&Entity0)    )
			return pCollider;
	}
	/* search failed */
	return NULL;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CollisionManager::AddPhysicEntity
 *
 *  \param  Entity The physic entity to add under collision detection.
 *  \author Gabriel Peyré 2001-09-13
 *
 *	Add a collider between this object and all object involved in collision detection.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CollisionManager::AddPhysicEntity( OR_PhysicEntity& Entity )
{
	IT_PhysicEntityList it;

	switch( Entity.GetPhysicType() ) 
	{
	case OR_PhysicEntity::kPhysicEntity_ParticuleManager:
		for( it=EntityList_.begin(); it!=EntityList_.end(); ++it )
		{
			OR_PhysicEntity* pEntity = *it;
			if( pEntity->GetPhysicType()==OR_PhysicEntity::kPhysicEntity_Deflector )
				ColliderList_.push_back( new OR_DeflectorCollider( (OR_ParticuleManager&)Entity,
																   (OR_Deflector_ABC&)*pEntity ) );
		}
		break;
	case OR_PhysicEntity::kPhysicEntity_RigidBody:
		for( it=EntityList_.begin(); it!=EntityList_.end(); ++it )
		{
			OR_PhysicEntity* pEntity = *it;
			if( pEntity->GetPhysicType()==OR_PhysicEntity::kPhysicEntity_RigidBody )
				ColliderList_.push_back( new OR_RigidBodyCollider( (OR_RigidBody&)Entity,
																   (OR_RigidBody&)*pEntity ) );
		}
		break;
	case OR_PhysicEntity::kPhysicEntity_Deflector:
		for( it=EntityList_.begin(); it!=EntityList_.end(); ++it )
		{
			OR_PhysicEntity* pEntity = *it;
			if( pEntity->GetPhysicType()==OR_PhysicEntity::kPhysicEntity_ParticuleManager )
				ColliderList_.push_back( new OR_DeflectorCollider( (OR_ParticuleManager&)*pEntity,
																   (OR_Deflector_ABC&)Entity ) );
		}
		break;
	default:
		OR_Globals::MessageHandler()->Warning("OR_CollisionManager::AddPhysicEntity", 
						"This kind of entity is not supported  by the physic engine.");
		break;
	}

	EntityList_.push_back( &Entity );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_CollisionManager::ResolveCollisions
 *
 *  \author Gabriel Peyré 2001-09-13
 *
 *	Detect and then resolve each collision.
 */ 
/*------------------------------------------------------------------------------*/
void OR_CollisionManager::ResolveCollisions()
{
	/* detect collision on each pair of objects involved */
	for( IT_ColliderList itCollider=ColliderList_.begin(); itCollider!=ColliderList_.end(); ++itCollider )
		(*itCollider)->PerformCollisionDetection( *this );

	/* resolve each collision */
	for( IT_CollisionList itCollision=CollisionList_.begin(); itCollision!=CollisionList_.end(); ++itCollision )
	{
		OR_Collision* pCollision = *itCollision;
		pCollision->Resolve();
		/* re-cycle the collision */
		GarbageCollector_.push_back( pCollision );
	}

	CollisionList_.clear();
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

