/*------------------------------------------------------------------------------*/
/** 
*  \file  OR_RigidBodyCollider.inl
 *  \brief Inlined methods for \c OR_RigidBodyCollider
 *  \author Gabriel Peyré 2001-09-12
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_RigidBodyCollider.h"

namespace OR {
	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::CollisionCallback
 *
 *  \param  triangleindex The index of the triangle face.
 *  \param  triangle The vertex to compute.
 *  \param  userdata Should be a pointer on the \c OR_PhysicModel.
 *  \author Gabriel Peyré 2001-09-12
 *
 *	This is the callback method used by \b OPCODE to access the datas of the objects.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBodyCollider::CollisionCallback(udword triangleindex, VertexPointers& triangle, udword userdata)
{
	OR_PhysicModel* pModel = (OR_PhysicModel*) userdata;
	OR_ASSERT( pModel!=NULL );
	OR_Mesh* pMesh = &pModel->GetMesh();

	// Get correct triangle in the app-controlled database
	udword* Tri = (udword*) &pMesh->GetFaceList()[triangleindex*3];
	// Setup pointers to vertices for the collision system
	triangle.Vertex[0] = (Point*) &pMesh->GetVertsArray()[Tri[0]];
	triangle.Vertex[1] = (Point*) &pMesh->GetVertsArray()[Tri[1]];
	triangle.Vertex[2] = (Point*) &pMesh->GetVertsArray()[Tri[2]];
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetRigidBody0
 *
 *  \return 1st model involved in collision detection.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody& OR_RigidBodyCollider::GetRigidBody0()
{
	OR_ASSERT( pBody0_!=NULL );
	return *pBody0_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetRigidBody1
 *
 *  \return 2nd model involved in collision detection.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_RigidBody& OR_RigidBodyCollider::GetRigidBody1()
{
	OR_ASSERT( pBody1_!=NULL );
	return *pBody1_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::ConvertMatrix
 *
 *  \param  a original matrix.
 *  \param  r target matrix.
 *  \author Gabriel Peyré 2001-11-07
 *
 *	Convert an \b Orion3D matrix to an \b OPCODE one.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_RigidBodyCollider::ConvertMatrix(OR_Matrix4x4& a, Matrix4x4& r)
{
	memcpy(r.m, a.GetData(), 16*sizeof(OR_Float));
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetTreeCollider
 *
 *  \return the \b OPCODE tree collider between the two rigid bodies.
 *  \author Gabriel Peyré 2001-11-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
AABBTreeCollider& OR_RigidBodyCollider::GetTreeCollider()
{
	return TreeCollider_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetCollisionCache
 *
 *  \return the \b OPCODE collision cache.
 *  \author Gabriel Peyré 2001-11-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
BVTCache& OR_RigidBodyCollider::GetCollisionCache()
{
	return CollisionCache_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetLastCollisionStatus
 *
 *  \return the result of the last collision detection query.
 *  \author Gabriel Peyré 2001-11-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_RigidBodyCollider::GetLastCollisionStatus()
{
	return TreeCollider_.GetContactStatus();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RigidBodyCollider::GetNbrCollidingPairs
 *
 *  \return the number of colliding tris pairs.
 *  \author Gabriel Peyré 2001-11-07
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_RigidBodyCollider::GetNbrCollidingPairs()
{
	return TreeCollider_.GetNbPairs();
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

