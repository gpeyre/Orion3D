
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_RigidBodyCollider.h
 *  \brief Definition of class \c OR_RigidBodyCollider
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_RigidBodyCollider_h_
#define __OR_RigidBodyCollider_h_

#include "../configuration/OR_Config.h"
#include "OR_Collider_ABC.h"

#undef PI	
#undef HALFPI	
#undef TWOPI
#undef INVPI
#include "../../opcode/Opcode.h"
using namespace Opcode;
#undef OR


namespace OR {

class OR_CollisionManager;

/*------------------------------------------------------------------------------*/
/**
 *  \class  OR_RigidBodyCollider
 *  \brief  Track the collision between the pair of rigid body.
 *  \author Gabriel Peyré 2001-09-12
 *  
 *	It encapsulate the function calls of \b OPCODE to check collision queries.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_RigidBodyCollider: public OR_Collider_ABC
{

public:

    OR_RigidBodyCollider( OR_RigidBody& Body0, OR_RigidBody& Body1 );
    virtual ~OR_RigidBodyCollider();

	//-------------------------------------------------------------------------
    /** \name overload of OR_Collider_ABC methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void PerformCollisionDetection( OR_CollisionManager& CollisionManager );
	virtual OR_PhysicEntity& GetCollidee0();
	virtual OR_PhysicEntity& GetCollidee1();
    //@}

    //-------------------------------------------------------------------------
    /** \name Accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_RigidBody& GetRigidBody0();
	OR_RigidBody& GetRigidBody1();

	AABBTreeCollider& GetTreeCollider();
	BVTCache& GetCollisionCache();

	OR_Bool GetLastCollisionStatus();
	OR_U32  GetNbrCollidingPairs();
    //@}

	
	static void CollisionCallback(udword triangleindex, VertexPointers& triangle, udword userdata);

private:

    //-------------------------------------------------------------------------
    /** \name helper */
    //-------------------------------------------------------------------------
    //@{
	static void ConvertMatrix(OR_Matrix4x4& a, Matrix4x4& r);
    //@}

	/** first rigid body */
	OR_RigidBody* pBody0_;
	/** second rigid body */
	OR_RigidBody* pBody1_;

	/** \b OPCODE tree colliider */
	AABBTreeCollider TreeCollider_;
	/** \b OPCODE cache */
	BVTCache CollisionCache_;


};


} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_RigidBodyCollider.inl"
#endif


#endif // __OR_RigidBodyCollider_h_

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

