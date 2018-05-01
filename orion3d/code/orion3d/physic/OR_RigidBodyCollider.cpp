/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_RigidBodyCollider.cpp
 *  \brief Definition of class \c OR_RigidBodyCollider
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_RigidBodyCollider.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_RigidBodyCollider.h"
#include "OR_CollisionManager.h"

#ifndef OR_USE_INLINE
	#include "OR_RigidBodyCollider.inl"
#endif


using namespace OR;

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider constructor
 *
 *  \param  Body0 the physic model containing the description of the first object.
 *  \param  Body1 the physic model containing the description of the second object.
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
OR_RigidBodyCollider::OR_RigidBodyCollider( OR_RigidBody& Body0, OR_RigidBody& Body1 )
:	OR_Collider_ABC	(),
	pBody0_			( &Body0 ),
	pBody1_			( &Body1 )
{
	OR_PhysicModel* pModel0 = Body0.GetPhysicModel();
	OR_PhysicModel* pModel1 = Body1.GetPhysicModel();
	OR_ASSERT( pModel0!=NULL );
	OR_ASSERT( pModel1!=NULL );
	
	/* set up the collider */
	TreeCollider_.SetFirstContact(false);		// report all contacts
	TreeCollider_.SetFullBoxBoxTest(false);		// use coarse BV-BV tests
	TreeCollider_.SetFullPrimBoxTest(false);	// use coarse primitive-BV tests
	TreeCollider_.SetTemporalCoherence(false);	// don't use temporal coherence

	/* set the callback used by the tree collider to retrieve the geometry from Orion3D */
	TreeCollider_.SetCallbackObj0( OR_RigidBodyCollider::CollisionCallback );
	TreeCollider_.SetCallbackObj1( OR_RigidBodyCollider::CollisionCallback );
	TreeCollider_.SetUserData0( (udword) pModel0 );
	TreeCollider_.SetUserData1( (udword) pModel1 );
	
	/* set up the cache for the queries */	
	CollisionCache_.Model0 = &pModel0->GetOpcodeModel();
	CollisionCache_.Model1 = &pModel1->GetOpcodeModel();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider destructor
 *
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
OR_RigidBodyCollider::~OR_RigidBodyCollider()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::PerformCollisionDetection
 *
 *  \param  CollisionManager the manager of collision.
 *  \author Gabriel Peyré 2001-09-12
 *
 *	Use \b OPCODE to check collision between the two models, and then add the collision
 *	into the collision manager.
 */ 
/*------------------------------------------------------------------------------*/
void OR_RigidBodyCollider::PerformCollisionDetection( OR_CollisionManager& CollisionManager )
{
	OR_Matrix4x4 WordlToBody0_O3D = this->GetRigidBody0().GetWorldToBody();
	OR_Matrix4x4 WordlToBody1_O3D = this->GetRigidBody1().GetWorldToBody();

	/* OPCODE matrix are as Orion3D one : column major */
	Matrix4x4 WordlToBody0_OPCODE;
	Matrix4x4 WordlToBody1_OPCODE;

	OR_RigidBodyCollider::ConvertMatrix( WordlToBody0_O3D, WordlToBody0_OPCODE);
	OR_RigidBodyCollider::ConvertMatrix( WordlToBody1_O3D, WordlToBody1_OPCODE);

	/* perform check */
	TreeCollider_.Collide(CollisionCache_, WordlToBody0_OPCODE, WordlToBody1_OPCODE);

	if( TreeCollider_.GetContactStatus() )
	{
		/* at least one collision has occurs */
		udword nNbPairs  = TreeCollider_.GetNbPairs();
		/* list of colliding triangles */
		Pair* aCollision = TreeCollider_.GetPairs();
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetCollidee0
 *
 *  \return the first collidee.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity& OR_RigidBodyCollider::GetCollidee0()
{
	return this->GetRigidBody0();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetCollidee1
 *
 *  \return the second collidee.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity& OR_RigidBodyCollider::GetCollidee1()
{
	return this->GetRigidBody1();
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


