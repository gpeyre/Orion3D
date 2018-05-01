/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_Maths.cpp
 *  \brief  Definition of class \c FSW_Maths
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_Maths.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_Maths.h"
#include "FSW_QuadTreeNode.h"
#include "FSW_QuadTree.h"
#include "FSW_TreeFunction_ABC.h"
#include "FSW_BaseMesh_ABC.h"

#ifndef FSW_USE_INLINE
    #include "FSW_Maths.inl"
#endif

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::ConvertCartesianToSpherical
/**
 *  \param  Pos [FSW_Vector3D] Absolute position of the point.
 *  \param  rLong [FSW_Float&] Return value : longitude.
 *  \param  rLat [FSW_Float&] Return value : latitude.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Convert from absolute cartesian coords to polar coords
 */
/*------------------------------------------------------------------------------*/
void FSW_Maths::ConvertCartesianToSpherical(const FSW_Vector3D& Pos, FSW_Float& rLong, FSW_Float& rLat)
{
	FSW_ASSERT( Pos[X] <= 1 );
	FSW_ASSERT( Pos[X] >= -1 );
	FSW_ASSERT( Pos[Z] <= 1 );
	FSW_ASSERT( Pos[Z] >= -1 );

	rLat = (FSW_Float) asin( Pos[Z] );

	FSW_Float rVal = (FSW_Float) sqrt( Pos[X]*Pos[X] + Pos[Y]*Pos[Y] );
	if( rVal==0 )
		rLong = 0;
	else
	{
		rVal = Pos[X]/rVal;
		FSW_ASSERT( rVal >= -1 );
		FSW_ASSERT( rVal <= 1 );
		if( rVal < -1 )
			rVal = -1;
		if( rVal > 1 )
			rVal = 1;
		rLong = (FSW_Float) acos( rVal );
		if( Pos[Y]<0  )
			rLong = FSW_TWOPI-rLong;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::SphericalTriangleArea
/**
 *  \param  v1 [FSW_Vector3D&] Point of the triangle.
 *  \param  v2 [FSW_Vector3D&] Point of the triangle.
 *  \param  v3 [FSW_Vector3D&] Point of the triangle.
 *  \return [FSW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of a spherical triangle.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::SphericalTriangleArea(const FSW_Vector3D& v1, const FSW_Vector3D& v2, const FSW_Vector3D& v3)
{
  // first find the cosine of the arc lengths
  FSW_Real64 cos_a = v2 * v3;
  FSW_Real64 cos_b = v1 * v3;
  FSW_Real64 cos_c = v1 * v2;

  // now the sine (positive since 0 <= a <= pi)
  FSW_Real64 sin_a = sqrt( 1. - cos_a * cos_a );
  FSW_Real64 sin_b = sqrt( 1. - cos_b * cos_b );
  FSW_Real64 sin_c = sqrt( 1. - cos_c * cos_c );

  // now find the angles A, B, and C
  FSW_Real64 A = acos( ( cos_a - cos_b * cos_c ) / ( sin_b * sin_c ) );
  FSW_Real64 B = acos( ( cos_b - cos_c * cos_a ) / ( sin_c * sin_a ) );
  FSW_Real64 C = acos( ( cos_c - cos_a * cos_b ) / ( sin_a * sin_b ) );

  return (FSW_Float) ( A + B + C - FSW_PI );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::FlatTriangleArea
/**
 *  \param  v1 [FSW_Vector3D&] a point of the triangle.
 *  \param  v2 [FSW_Vector3D&] a point of the triangle.
 *  \param  v3 [FSW_Vector3D&] a point of the triangle.
 *  \return [FSW_Float] The area
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of a plane triangle.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::FlatTriangleArea(const FSW_Vector3D& v1, const FSW_Vector3D& v2, const FSW_Vector3D& v3)
{
	return 0.5f * ~( (v2-v1)^(v3-v1) );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::FlatTriangleNormal
/**
 *  \param  Normal [FSW_Vector3D&] The return value.
 *  \param  v1 [FSW_Vector3D&] A point in the triangle.
 *  \param  v2 [FSW_Vector3D&] A point in the triangle.
 *  \param  v3 [FSW_Vector3D&] A point in the triangle.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Comute the normal of a triangle, assuming CW orientation.
 */
/*------------------------------------------------------------------------------*/
void FSW_Maths::FlatTriangleNormal(FSW_Vector3D& Normal, const FSW_Vector3D& v1, const FSW_Vector3D& v2, const FSW_Vector3D& v3)
{
	Normal = (v2-v1)^(v3-v1);
}


/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::SphericalTriangleArea
/**
 *  \param  Node [FSW_QuadTreeNode&] The node
 *  \return [FSW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of the triangle supported by a given node.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::SphericalTriangleArea(const FSW_QuadTreeNode& Node)
{
	FSW_ASSERT( Node.GetVertexConst(QT_Vert1)!= NULL );
	FSW_ASSERT( Node.GetVertexConst(QT_Vert2)!= NULL );
	FSW_ASSERT( Node.GetVertexConst(QT_Vert3)!= NULL );
	return FSW_Maths::SphericalTriangleArea(	Node.GetVertexConst(QT_Vert1)->GetPositionConst(), 
												Node.GetVertexConst(QT_Vert2)->GetPositionConst(), 
												Node.GetVertexConst(QT_Vert3)->GetPositionConst() );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::FlatTriangleArea
/**
 *  \param  Node [FSW_QuadTreeNode&] The node.
 *  \return [FSW_Float] The area.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the area of the triangle supported by a given node.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::FlatTriangleArea(const FSW_QuadTreeNode& Node)
{
	FSW_ASSERT( Node.GetVertexConst(QT_Vert1)!= NULL );
	FSW_ASSERT( Node.GetVertexConst(QT_Vert2)!= NULL );
	FSW_ASSERT( Node.GetVertexConst(QT_Vert3)!= NULL );
	return FSW_Maths::FlatTriangleArea(	Node.GetVertexConst(QT_Vert1)->GetPositionConst(), 
										Node.GetVertexConst(QT_Vert2)->GetPositionConst(), 
										Node.GetVertexConst(QT_Vert3)->GetPositionConst() );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::FlatTriangleNormal
/**
 *  \param  Normal [FSW_Vector3D&] return : The normal.
 *  \param  Node [FSW_QuadTreeNode&] The node.
 *  \author Gabriel Peyré
 *  \date   10-28-2002
 * 
 *  Compute the normal of the triangle supported by a given node.
 */
/*------------------------------------------------------------------------------*/
void FSW_Maths::FlatTriangleNormal(FSW_Vector3D& Normal, const FSW_QuadTreeNode& Node)
{
	FSW_ASSERT( Node.GetVertexConst(QT_Vert1)!= NULL );
	FSW_ASSERT( Node.GetVertexConst(QT_Vert2)!= NULL );
	FSW_ASSERT( Node.GetVertexConst(QT_Vert3)!= NULL );
	FSW_Maths::FlatTriangleNormal(Normal, 	Node.GetVertexConst(QT_Vert1)->GetPositionConst(), 
											Node.GetVertexConst(QT_Vert2)->GetPositionConst(), 
											Node.GetVertexConst(QT_Vert3)->GetPositionConst() );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::RecurseIntegralComputation
/**
 *  \param  Tree [FSW_QuadTree&] The tree.
 *  \param  pFunc [T_RecurseIntegralComputation_Function] The function.
 *  \return [FSW_Float] Result for the whole tree.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Recurse on the hole tree to apply a function on the leaf node.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::RecurseIntegralComputation(FSW_QuadTree& Tree, T_RecurseIntegralComputation_Function pFunc, void* pChunk)
{
	FSW_Float rVal = 0;
	T_QuadTreeNodeVector BaseNodeVector = Tree.GetBaseNodeVector();
	for( IT_QuadTreeNodeVector it=BaseNodeVector.begin(); it!=BaseNodeVector.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		rVal += FSW_Maths::RecurseIntegralComputation_Rec( *pNode, pFunc, pChunk );
	}
	return rVal;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::RecurseIntegralComputation_Rec
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \param  pFunc [T_RecurseIntegralComputation_Function] The function.
 *  \return [FSW_Float] Result for the sub tree.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Recurse on the hole tree to apply a function on the leaf node.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::RecurseIntegralComputation_Rec(FSW_QuadTreeNode& CurNode, T_RecurseIntegralComputation_Function pFunc, void* pChunk)
{
	if( CurNode.GetChildNode(0)!=NULL )
	{
		FSW_Float rVal = 0;
		for( FSW_U32 i=0; i<4; ++i )
		{
			FSW_QuadTreeNode* pNode = CurNode.GetChildNode(i);
			FSW_ASSERT( pNode!=NULL );
			rVal += FSW_Maths::RecurseIntegralComputation_Rec( *pNode, pFunc, pChunk );
		}
		return rVal;
	}
	else
		return pFunc( CurNode, pChunk );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::Helper_ComputeIntegral
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \return [FSW_Float] Partial integral.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  A function applied recursivly to compute the integral of the 
 *  whole tree.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::Helper_ComputeIntegral(FSW_QuadTreeNode& CurNode, void* pChunk)
{
	FSW_Float rVal = 0;
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetVertex(i);
		FSW_ASSERT( pVert!=NULL );
		rVal += pVert->GetValue();
	}
//	FSW_Float rArea = FSW_Maths::SphericalTriangleArea(CurNode);
	FSW_Float rArea = FSW_Maths::FlatTriangleArea(CurNode);
	FSW_ASSERT( rArea>=0 );
	rVal = rVal*rArea/3;
	return rVal;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::void ComputeL1Norm
/**
 *  \param  Tree [FSW_QuadTree&] The tree.
 *  \return [FSW_Float] the norm.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the L2 norm of the whole tree.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::ComputeIntegral(FSW_QuadTree& Tree)
{
	return FSW_Maths::RecurseIntegralComputation(Tree, Helper_ComputeIntegral);
}


/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::Helper_ComputeL1Distance
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \param  pChunk [void*] The function.
 *  \return [FSW_Float] Distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the distance between the triangle and a given function.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::Helper_ComputeL1Distance(FSW_QuadTreeNode& CurNode, void* pChunk)
{
	FSW_TreeFunction_ABC* pFunc = (FSW_TreeFunction_ABC*) pChunk;
	FSW_ASSERT( pFunc!=NULL );
	FSW_Float rVal = 0;
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetVertex(i);
		FSW_ASSERT( pVert!=NULL );
		FSW_Float rU, rV;
		FSW_QuadTree* pQuadTree = FSW_QuadTree::StaticThis();
		FSW_ASSERT( pQuadTree!=NULL );
		pQuadTree->GetBaseMesh().ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
		rVal += FSW_ABS( pVert->GetValue()-pFunc->GetValue(rU, rV) );
	}
//	FSW_Float rArea = FSW_Maths::SphericalTriangleArea(CurNode);
	FSW_Float rArea = FSW_Maths::FlatTriangleArea(CurNode);
	FSW_ASSERT( rArea>=0 );
	rVal = rVal*rArea/3;
	return rVal;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::ComputeL1Distance
/**
 *  \param  Tree [FSW_QuadTree&] The tree.
 *  \param  Func [FSW_TreeFunction_ABC&] The function.
 *  \return [FSW_Float] The distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the L1 distance between the tree and a given function.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::ComputeL1Distance(FSW_QuadTree& Tree, FSW_TreeFunction_ABC& Func)
{
	Tree.SetStaticThis();
	return FSW_Maths::RecurseIntegralComputation(Tree, Helper_ComputeL1Distance, &Func);
	Tree.UnsetStaticThis();
}


/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::Helper_ComputeL2Distance
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \param  pChunk [void*] The function.
 *  \return [FSW_Float] Distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the distance between the triangle and a given function.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::Helper_ComputeL2Distance(FSW_QuadTreeNode& CurNode, void* pChunk)
{
	FSW_TreeFunction_ABC* pFunc = (FSW_TreeFunction_ABC*) pChunk;
	FSW_ASSERT( pFunc!=NULL );
	FSW_Float rVal = 0;
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetVertex(i);
		FSW_ASSERT( pVert!=NULL );
		FSW_Float rU, rV;
		FSW_QuadTree* pQuadTree = FSW_QuadTree::StaticThis();
		FSW_ASSERT( pQuadTree!=NULL );
		pQuadTree->GetBaseMesh().ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
		FSW_Float rInt = FSW_ABS( pVert->GetValue()-pFunc->GetValue(rU, rV) );
		rVal += rInt*rInt;
	}
//	FSW_Float rArea = FSW_Maths::SphericalTriangleArea(CurNode);
	FSW_Float rArea = FSW_Maths::FlatTriangleArea(CurNode);
	FSW_ASSERT( rArea>=0 );
	rVal = rVal*rArea/3;
	return rVal;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_Maths::ComputeL2Distance
/**
 *  \param  Tree [FSW_QuadTree&] The tree.
 *  \param  Func [FSW_TreeFunction_ABC&] The function.
 *  \return [FSW_Float] The distance.
 *  \author Gabriel Peyré
 *  \date   11-15-2002
 * 
 *  Compute the L2 distance between the tree and a given function.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_Maths::ComputeL2Distance(FSW_QuadTree& Tree, FSW_TreeFunction_ABC& Func)
{
	Tree.SetStaticThis();
	return (FSW_Float) sqrt( FSW_Maths::RecurseIntegralComputation(Tree, Helper_ComputeL2Distance, &Func) );
	Tree.UnsetStaticThis();
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
