/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseTetrahedron.cpp
 *  \brief  Definition of class \c FSW_BaseTetrahedron
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_BaseTetrahedron.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_BaseTetrahedron.h"

using namespace FSW;

/* initialize the neighbor relation among subtrees */
FSW_U32 FSW_BaseTetrahedron::aSubTreeNeighbor_[4][3] =
{
	{2,3,1},
	{0,3,2},
	{0,1,3},
	{0,2,1}
};

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
FSW_BaseTetrahedron::FSW_BaseTetrahedron()
:FSW_BaseMesh_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_BaseTetrahedron::~FSW_BaseTetrahedron()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::BuildBaseMesh
/**
 *  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
 *  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  We construct a new list of node, and create associated vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseTetrahedron::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	FSW_ASSERT( BaseNodeVector.empty() );
	FSW_ASSERT( BaseVertexVector.empty() );
	pBaseNodeVector_ = &BaseNodeVector;
	BaseNodeVector.resize( 4 );
	BaseVertexVector.resize( 4 );

	/* create the nodes*/
	for( FSW_U32 i=0; i<4; ++i )
		BaseNodeVector[i] = new FSW_QuadTreeNode;
	/* create the vertex*/
	for( FSW_U32 i=0; i<4; ++i )
		BaseVertexVector[i] = new FSW_QuadTreeVertex;

	/* set up the position of the 6 vertex and assign them to the different childs */
	FSW_Float r=0.5773502691896f;
	BaseVertexVector[0]->SetPosition( FSW_Vector3D( r,-r,-r) );
	BaseVertexVector[1]->SetPosition( FSW_Vector3D( r, r, r) );
	BaseVertexVector[2]->SetPosition( FSW_Vector3D(-r, r,-r) );
	BaseVertexVector[3]->SetPosition( FSW_Vector3D(-r,-r, r) );

    BaseNodeVector[0]->SetVertex( BaseVertexVector[3], BaseVertexVector[1], BaseVertexVector[2] );
	BaseNodeVector[1]->SetVertex( BaseVertexVector[0], BaseVertexVector[1], BaseVertexVector[3] );
	BaseNodeVector[2]->SetVertex( BaseVertexVector[0], BaseVertexVector[2], BaseVertexVector[1] );
	BaseNodeVector[3]->SetVertex( BaseVertexVector[0], BaseVertexVector[3], BaseVertexVector[2] );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::GetRelativeSon
/**
 *  \param  nDirection [FSW_U32] The direction.
 *  \return [FSW_QuadTreeNode*] The neighbor.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Get the neighbor of a given node in a given direction (the node 
 *  should be a base node).
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTreeNode* FSW_BaseTetrahedron::GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction)
{
	FSW_ASSERT( pBaseNodeVector_!=NULL );
	FSW_ASSERT( pBaseNodeVector_->size()==4 );
	/* first translate the vertex direction into an index entry */
	FSW_I32 nDirection = -1;
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( Son.GetVertex(i)==(&Direction) )
		{
			nDirection=i;
			break;
		}
	}
	FSW_ASSERT( nDirection>=0 );
	/* first we must figure out wich is the number of pSon */
	for( FSW_U32 i=0; i<4; ++i )
	{
		if( (&Son)==(*pBaseNodeVector_)[i] )
			return (*pBaseNodeVector_)[ FSW_BaseTetrahedron::aSubTreeNeighbor_[i][nDirection] ];			
	}
	FSW_ASSERT( FSW_False );
	return NULL;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::Positionate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The node we want to positionate.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Positionate the owned vertex of the node on a sphere.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseTetrahedron::Positionate( FSW_QuadTreeNode& CurNode )
{
	/* check for each central vertex if we need to create one new
	   or if it can be retrieve either from neighbor or from a pre-existing one */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex(i);
			FSW_ASSERT( pVert!=NULL );
			FSW_Vector3D Pos;
			FSW_U32 s = (i+1) % 3; 
			FSW_U32 t = (i+2) % 3;
			FSW_ASSERT( CurNode.GetVertex(s)!=NULL );
			FSW_ASSERT( CurNode.GetVertex(t)!=NULL );
			Pos = CurNode.GetVertex(s)->GetPosition() + CurNode.GetVertex(t)->GetPosition();	// compute middle
			Pos.Normalize();	// project on the sphere
			pVert->SetPosition(Pos);
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::ConvertToLocalFrame
/**
 *  \param  Pos [FSW_Vector3D&] The position.
 *  \param  rU [FSW_Float&] X coord
 *  \param  rV [FSW_Float] Y coord
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Compute local coordinnate from 3D vector position.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseTetrahedron::ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV )
{
	FSW_Maths::ConvertCartesianToSpherical( Pos, rU, rV );
	/* U and V should be in [0,1]  */
	rU /= FSW_TWOPI;
	rV = rV/FSW_PI + 0.5f;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::GetNbrVertex
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \return [FSW_U32] Number of vertice.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of vertex on the subdivided version of the 
 *  mesh, at given depth.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseTetrahedron::GetNbrVertex( FSW_U32 nDepth )
{
	return (1 << (2*(nDepth+1)) ) + 2; // 4^(nDepth+1) + 2
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::GetNbrFace
/**
 *  \param  nDepth [FSW_U32] Depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of face.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseTetrahedron::GetNbrFace( FSW_U32 nDepth )
{
	return 12*( 1<<(2*nDepth) );	// 12*4^(nDepth)
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseTetrahedron::GetNbrEdge
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of edges.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseTetrahedron::GetNbrEdge( FSW_U32 nDepth )
{
	return 9*( 1<<(2*nDepth) );		// 9*4^(nDepth)
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
