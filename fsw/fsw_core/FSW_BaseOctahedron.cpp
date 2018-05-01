/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseOctahedron.cpp
 *  \brief  Definition of class \c FSW_BaseOctahedron
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_BaseOctahedron.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_BaseOctahedron.h"

using namespace FSW;

/* initialize the neighbor relation among subtrees */
FSW_U32 FSW_BaseOctahedron::aSubTreeNeighbor_[8][3] =
{
	{1,3,4},
	{0,2,5},
	{3,1,6},
	{2,0,7},
	{5,7,0},
	{4,6,1},
	{7,5,2},
	{6,4,3}
};

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
FSW_BaseOctahedron::FSW_BaseOctahedron()
:FSW_BaseMesh_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_BaseOctahedron::~FSW_BaseOctahedron()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron::BuildBaseMesh
/**
 *  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
 *  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  We construct a new list of node, and create associated vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseOctahedron::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	FSW_ASSERT( BaseNodeVector.empty() );
	FSW_ASSERT( BaseVertexVector.empty() );
	pBaseNodeVector_ = &BaseNodeVector;
	BaseNodeVector.resize( 8 );
	BaseVertexVector.resize( 6 );

	/* create the nodes*/
	for( FSW_U32 i=0; i<8; ++i )
		BaseNodeVector[i] = new FSW_QuadTreeNode;
	/* create the vertex*/
	for( FSW_U32 i=0; i<6; ++i )
		BaseVertexVector[i] = new FSW_QuadTreeVertex;

	/* set up the position of the 6 vertex and assign them to the different childs */
	BaseVertexVector[k90N]->SetPosition(	FSW_Vector3D(0,0,1) );
	BaseVertexVector[k90S]->SetPosition(	FSW_Vector3D(0,0,-1) );
	BaseVertexVector[k180EW]->SetPosition(FSW_Vector3D(0,1,0) );
	BaseVertexVector[k0EW]->SetPosition(	FSW_Vector3D(0,-1,0) );
	BaseVertexVector[k90E]->SetPosition(	FSW_Vector3D(1,0,0) );
	BaseVertexVector[k90W]->SetPosition(	FSW_Vector3D(-1,0,0) );

    BaseNodeVector[0]->SetVertex( BaseVertexVector[k0EW],   BaseVertexVector[k90E], BaseVertexVector[k90N] );
	BaseNodeVector[1]->SetVertex( BaseVertexVector[k180EW], BaseVertexVector[k90E], BaseVertexVector[k90N] );
	BaseNodeVector[2]->SetVertex( BaseVertexVector[k180EW], BaseVertexVector[k90W], BaseVertexVector[k90N] );
	BaseNodeVector[3]->SetVertex( BaseVertexVector[k0EW],   BaseVertexVector[k90W], BaseVertexVector[k90N] );
	BaseNodeVector[4]->SetVertex( BaseVertexVector[k0EW],   BaseVertexVector[k90E], BaseVertexVector[k90S] );
	BaseNodeVector[5]->SetVertex( BaseVertexVector[k180EW], BaseVertexVector[k90E], BaseVertexVector[k90S] );
	BaseNodeVector[6]->SetVertex( BaseVertexVector[k180EW], BaseVertexVector[k90W], BaseVertexVector[k90S] );
	BaseNodeVector[7]->SetVertex( BaseVertexVector[k0EW],   BaseVertexVector[k90W], BaseVertexVector[k90S] );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron::GetRelativeSon
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
FSW_QuadTreeNode* FSW_BaseOctahedron::GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction)
{
	FSW_ASSERT( pBaseNodeVector_!=NULL );
	FSW_ASSERT( pBaseNodeVector_->size()==8 );
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
	for( FSW_U32 i=0; i<8; ++i )
	{
		if( (&Son)==(*pBaseNodeVector_)[i] )
			return (*pBaseNodeVector_)[ aSubTreeNeighbor_[i][nDirection] ];			
	}
	FSW_ASSERT( FSW_False );
	return NULL;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron::Positionate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The node we want to positionate.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Positionate the owned vertex of the node on a sphere.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseOctahedron::Positionate( FSW_QuadTreeNode& CurNode )
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
// Name : FSW_BaseOctahedron::ConvertToLocalFrame
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
void FSW_BaseOctahedron::ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV )
{
	FSW_Maths::ConvertCartesianToSpherical( Pos, rU, rV );
	/* U and V should be in [0,1]  */
	rU /= FSW_TWOPI;
	rV = rV/FSW_PI + 0.5f;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron::GetNbrVertex
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
FSW_U32 FSW_BaseOctahedron::GetNbrVertex( FSW_U32 nDepth )
{
	return (1 << (2*(nDepth+1)) ) + 2; // 4^(nDepth+1) + 2
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron::GetNbrFace
/**
 *  \param  nDepth [FSW_U32] Depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of face.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseOctahedron::GetNbrFace( FSW_U32 nDepth )
{
	return 12*( 1<<(2*nDepth) );	// 12*4^(nDepth)
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseOctahedron::GetNbrEdge
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of edges.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseOctahedron::GetNbrEdge( FSW_U32 nDepth )
{
	return 8*( 1<<(2*nDepth) );		// 8*4^(nDepth)
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
