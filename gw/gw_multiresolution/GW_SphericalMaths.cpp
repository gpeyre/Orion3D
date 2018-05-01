/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_SphericalMaths.cpp
 *  \brief  Definition of class \c GW_SphericalMaths
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_SphericalMaths.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_SphericalMaths.h"
#include "GW_QuadTreeNode.h"
#include "GW_QuadTree.h"
#include "GW_TreeFunction_ABC.h"
#include "GW_BaseMesh_ABC.h"

#ifndef GW_USE_INLINE
    #include "GW_SphericalMaths.inl"
#endif

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::ConvertCartesianToSpherical
/**
 *  \param  Pos [GW_Vector3D] Absolute position of the point.
 *  \param  rLong [GW_Float&] Return value : longitude.
 *  \param  rLat [GW_Float&] Return value : latitude.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Convert from absolute cartesian coords to polar coords
 */
/*------------------------------------------------------------------------------*/
void GW_SphericalMaths::ConvertCartesianToSpherical(const GW_Vector3D& Pos, GW_Float& rLong, GW_Float& rLat)
{
	GW_ASSERT( Pos[X] <= 1 );
	GW_ASSERT( Pos[X] >= -1 );
	GW_ASSERT( Pos[Z] <= 1 );
	GW_ASSERT( Pos[Z] >= -1 );

	rLat = (GW_Float) asin( Pos[Z] );

	GW_Float rVal = (GW_Float) sqrt( Pos[X]*Pos[X] + Pos[Y]*Pos[Y] );
	if( rVal==0 )
		rLong = 0;
	else
	{
		rVal = Pos[X]/rVal;
		GW_ASSERT( rVal >= -1 );
		GW_ASSERT( rVal <= 1 );
		if( rVal < -1 )
			rVal = -1;
		if( rVal > 1 )
			rVal = 1;
		rLong = (GW_Float) acos( rVal );
		if( Pos[Y]<0  )
			rLong = GW_TWOPI-rLong;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::SphericalTriangleArea
/**
 *  \param  v1 [GW_Vector3D&] Point of the triangle.
 *  \param  v2 [GW_Vector3D&] Point of the triangle.
 *  \param  v3 [GW_Vector3D&] Point of the triangle.
 *  \return [GW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of a spherical triangle.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::SphericalTriangleArea(const GW_Vector3D& v1, const GW_Vector3D& v2, const GW_Vector3D& v3)
{
  // first find the cosine of the arc lengths
  GW_Real64 cos_a = v2 * v3;
  GW_Real64 cos_b = v1 * v3;
  GW_Real64 cos_c = v1 * v2;

  // now the sine (positive since 0 <= a <= pi)
  GW_Real64 sin_a = sqrt( 1. - cos_a * cos_a );
  GW_Real64 sin_b = sqrt( 1. - cos_b * cos_b );
  GW_Real64 sin_c = sqrt( 1. - cos_c * cos_c );

  // now find the angles A, B, and C
  GW_Real64 A = acos( ( cos_a - cos_b * cos_c ) / ( sin_b * sin_c ) );
  GW_Real64 B = acos( ( cos_b - cos_c * cos_a ) / ( sin_c * sin_a ) );
  GW_Real64 C = acos( ( cos_c - cos_a * cos_b ) / ( sin_a * sin_b ) );

  return (GW_Float) ( A + B + C - GW_PI );
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::FlatTriangleArea
/**
 *  \param  v1 [GW_Vector3D&] a point of the triangle.
 *  \param  v2 [GW_Vector3D&] a point of the triangle.
 *  \param  v3 [GW_Vector3D&] a point of the triangle.
 *  \return [GW_Float] The area
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of a plane triangle.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::FlatTriangleArea(const GW_Vector3D& v1, const GW_Vector3D& v2, const GW_Vector3D& v3)
{
	return 0.5f * ~( (v2-v1)^(v3-v1) );
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::FlatTriangleNormal
/**
 *  \param  Normal [GW_Vector3D&] The return value.
 *  \param  v1 [GW_Vector3D&] A point in the triangle.
 *  \param  v2 [GW_Vector3D&] A point in the triangle.
 *  \param  v3 [GW_Vector3D&] A point in the triangle.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Comute the normal of a triangle, assuming CW orientation.
 */
/*------------------------------------------------------------------------------*/
void GW_SphericalMaths::FlatTriangleNormal(GW_Vector3D& Normal, const GW_Vector3D& v1, const GW_Vector3D& v2, const GW_Vector3D& v3)
{
	Normal = (v2-v1)^(v3-v1);
}


/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::SphericalTriangleArea
/**
 *  \param  Node [GW_QuadTreeNode&] The node
 *  \return [GW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of the triangle supported by a given node.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::SphericalTriangleArea(const GW_QuadTreeNode& Node)
{
	GW_ASSERT( Node.GetVertexConst(QT_Vert1)!= NULL );
	GW_ASSERT( Node.GetVertexConst(QT_Vert2)!= NULL );
	GW_ASSERT( Node.GetVertexConst(QT_Vert3)!= NULL );
	return GW_SphericalMaths::SphericalTriangleArea(	Node.GetVertexConst(QT_Vert1)->GetPositionConst(), 
												Node.GetVertexConst(QT_Vert2)->GetPositionConst(), 
												Node.GetVertexConst(QT_Vert3)->GetPositionConst() );
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::FlatTriangleArea
/**
 *  \param  Node [GW_QuadTreeNode&] The node.
 *  \return [GW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of the triangle supported by a given node.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::FlatTriangleArea(const GW_QuadTreeNode& Node)
{
	GW_ASSERT( Node.GetVertexConst(QT_Vert1)!= NULL );
	GW_ASSERT( Node.GetVertexConst(QT_Vert2)!= NULL );
	GW_ASSERT( Node.GetVertexConst(QT_Vert3)!= NULL );
	return GW_SphericalMaths::FlatTriangleArea(	Node.GetVertexConst(QT_Vert1)->GetPositionConst(), 
										Node.GetVertexConst(QT_Vert2)->GetPositionConst(), 
										Node.GetVertexConst(QT_Vert3)->GetPositionConst() );
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::FlatTriangleNormal
/**
 *  \param  Normal [GW_Vector3D&] return : The normal.
 *  \param  Node [GW_QuadTreeNode&] The node.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the normal of the triangle supported by a given node.
 */
/*------------------------------------------------------------------------------*/
void GW_SphericalMaths::FlatTriangleNormal(GW_Vector3D& Normal, const GW_QuadTreeNode& Node)
{
	GW_ASSERT( Node.GetVertexConst(QT_Vert1)!= NULL );
	GW_ASSERT( Node.GetVertexConst(QT_Vert2)!= NULL );
	GW_ASSERT( Node.GetVertexConst(QT_Vert3)!= NULL );
	GW_SphericalMaths::FlatTriangleNormal(Normal, 	Node.GetVertexConst(QT_Vert1)->GetPositionConst(), 
											Node.GetVertexConst(QT_Vert2)->GetPositionConst(), 
											Node.GetVertexConst(QT_Vert3)->GetPositionConst() );
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::RecurseIntegralComputation
/**
 *  \param  Tree [GW_QuadTree&] The tree.
 *  \param  pFunc [T_RecurseIntegralComputation_Function] The function.
 *  \return [GW_Float] Result for the whole tree.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Recurse on the hole tree to apply a function on the leaf node.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::RecurseIntegralComputation(GW_QuadTree& Tree, T_RecurseIntegralComputation_Function pFunc, void* pChunk)
{
	GW_Float rVal = 0;
	T_QuadTreeNodeVector BaseNodeVector = Tree.GetBaseNodeVector();
	for( IT_QuadTreeNodeVector it=BaseNodeVector.begin(); it!=BaseNodeVector.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
		rVal += GW_SphericalMaths::RecurseIntegralComputation_Rec( *pNode, pFunc, pChunk );
	}
	return rVal;
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::RecurseIntegralComputation_Rec
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \param  pFunc [T_RecurseIntegralComputation_Function] The function.
 *  \return [GW_Float] Result for the sub tree.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Recurse on the hole tree to apply a function on the leaf node.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::RecurseIntegralComputation_Rec(GW_QuadTreeNode& CurNode, T_RecurseIntegralComputation_Function pFunc, void* pChunk)
{
	if( CurNode.GetChildNode(0)!=NULL )
	{
		GW_Float rVal = 0;
		for( GW_U32 i=0; i<4; ++i )
		{
			GW_QuadTreeNode* pNode = CurNode.GetChildNode(i);
			GW_ASSERT( pNode!=NULL );
			rVal += GW_SphericalMaths::RecurseIntegralComputation_Rec( *pNode, pFunc, pChunk );
		}
		return rVal;
	}
	else
		return pFunc( CurNode, pChunk );
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::Helper_ComputeIntegral
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \return [GW_Float] Partial integral.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  A function applied recursivly to compute the integral of the 
 *  whole tree.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::Helper_ComputeIntegral(GW_QuadTreeNode& CurNode, void* pChunk)
{
	GW_Float rVal = 0;
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetVertex(i);
		GW_ASSERT( pVert!=NULL );
		rVal += pVert->GetValue();
	}
//	GW_Float rArea = GW_SphericalMaths::SphericalTriangleArea(CurNode);
	GW_Float rArea = GW_SphericalMaths::FlatTriangleArea(CurNode);
	GW_ASSERT( rArea>=0 );
	rVal = rVal*rArea/3;
	return rVal;
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::void ComputeL1Norm
/**
 *  \param  Tree [GW_QuadTree&] The tree.
 *  \return [GW_Float] the norm.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the L2 norm of the whole tree.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::ComputeIntegral(GW_QuadTree& Tree)
{
	return GW_SphericalMaths::RecurseIntegralComputation(Tree, Helper_ComputeIntegral);
}


/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::Helper_ComputeL1Distance
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \param  pChunk [void*] The function.
 *  \return [GW_Float] Distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the distance between the triangle and a given function.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::Helper_ComputeL1Distance(GW_QuadTreeNode& CurNode, void* pChunk)
{
	GW_TreeFunction_ABC* pFunc = (GW_TreeFunction_ABC*) pChunk;
	GW_ASSERT( pFunc!=NULL );
	GW_Float rVal = 0;
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetVertex(i);
		GW_ASSERT( pVert!=NULL );
		GW_Float rU, rV;
		GW_QuadTree* pQuadTree = GW_QuadTree::StaticThis();
		GW_ASSERT( pQuadTree!=NULL );
		pQuadTree->GetBaseMesh().ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
		rVal += GW_ABS( pVert->GetValue()-pFunc->GetValue(rU, rV) );
	}
//	GW_Float rArea = GW_SphericalMaths::SphericalTriangleArea(CurNode);
	GW_Float rArea = GW_SphericalMaths::FlatTriangleArea(CurNode);
	GW_ASSERT( rArea>=0 );
	rVal = rVal*rArea/3;
	return rVal;
}

/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::ComputeL1Distance
/**
 *  \param  Tree [GW_QuadTree&] The tree.
 *  \param  Func [GW_TreeFunction_ABC&] The function.
 *  \return [GW_Float] The distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the L1 distance between the tree and a given function.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::ComputeL1Distance(GW_QuadTree& Tree, GW_TreeFunction_ABC& Func)
{
	Tree.SetStaticThis();
	return GW_SphericalMaths::RecurseIntegralComputation(Tree, Helper_ComputeL1Distance, &Func);
	Tree.UnsetStaticThis();
}


/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::Helper_ComputeL2Distance
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \param  pChunk [void*] The function.
 *  \return [GW_Float] Distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the distance between the triangle and a given function.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::Helper_ComputeL2Distance(GW_QuadTreeNode& CurNode, void* pChunk)
{
	GW_TreeFunction_ABC* pFunc = (GW_TreeFunction_ABC*) pChunk;
	GW_ASSERT( pFunc!=NULL );
	GW_Float rVal = 0;
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetVertex(i);
		GW_ASSERT( pVert!=NULL );
		GW_Float rU, rV;
		GW_QuadTree* pQuadTree = GW_QuadTree::StaticThis();
		GW_ASSERT( pQuadTree!=NULL );
		pQuadTree->GetBaseMesh().ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
		GW_Float rInt = GW_ABS( pVert->GetValue()-pFunc->GetValue(rU, rV) );
		rVal += rInt*rInt;
	}
//	GW_Float rArea = GW_SphericalMaths::SphericalTriangleArea(CurNode);
	GW_Float rArea = GW_SphericalMaths::FlatTriangleArea(CurNode);
	GW_ASSERT( rArea>=0 );
	rVal = rVal*rArea/3;
	return rVal;
}


/*------------------------------------------------------------------------------*/
// Name : GW_SphericalMaths::ComputeL2Distance
/**
 *  \param  Tree [GW_QuadTree&] The tree.
 *  \param  Func [GW_TreeFunction_ABC&] The function.
 *  \return [GW_Float] The distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the L2 distance between the tree and a given function.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_SphericalMaths::ComputeL2Distance(GW_QuadTree& Tree, GW_TreeFunction_ABC& Func)
{
	Tree.SetStaticThis();
	return (GW_Float) sqrt( GW_SphericalMaths::RecurseIntegralComputation(Tree, Helper_ComputeL2Distance, &Func) );
	Tree.UnsetStaticThis();
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
