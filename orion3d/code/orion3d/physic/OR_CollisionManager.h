
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CollisionManager.h
 *  \brief definition of class OR_CollisionManager
 *  \author Gabriel Peyré 2001-08-28
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_CollisionManager_h_
#define __OR_CollisionManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Collision.h"
#include "OR_Collider_ABC.h"
#include "OR_DeflectorCollider.h"
#include "OR_RigidBodyCollider.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_CollisionManager
 *  \brief  Manage all collision between the rigid bodies of an OR_PhysicentityManager.
 *  \author Gabriel Peyré 2001-08-28
 *
 *	The collision are stored in a linked list. We also use a garbage collector
 *	to avoid allocating/desallocating too much memory.
 */ 
/*------------------------------------------------------------------------------*/

class OR_CollisionManager
{

public:

    OR_CollisionManager();
    virtual ~OR_CollisionManager();

	void ResolveCollisions();

    //-------------------------------------------------------------------------
    /** \name Collisions management */
    //-------------------------------------------------------------------------
    //@{
	void AddCollision(OR_RigidBody& RB1, OR_RigidBody& RB2,
					  OR_Vector3D Position, OR_Vector3D Normal_,
					  OR_Vector3D EdgeA, OR_Vector3D EdgeB, OR_Bool bIsvertexFace);
    //@}

    //-------------------------------------------------------------------------
    /** \name Collider management */
    //-------------------------------------------------------------------------
    //@{
	OR_Collider_ABC* GetCollider( OR_PhysicEntity& Entity0, OR_PhysicEntity& Entity1 );
	void AddPhysicEntity( OR_PhysicEntity& Entity );
    //@}

private:

    //-------------------------------------------------------------------------
    /** \name collision datas */
    //-------------------------------------------------------------------------
    //@{
	/** list of pairs of objects to test */
	T_ColliderList		ColliderList_;

	/** list of all objects involved in collision detection */
	T_PhysicEntityList	EntityList_;

	/** the list of collision to resolve */
	T_CollisionList CollisionList_;
	/** a list of collision to re-use */
	T_CollisionList GarbageCollector_;
    //@}


};

} // End namespace OR


#endif // __OR_CollisionManager_h_

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

