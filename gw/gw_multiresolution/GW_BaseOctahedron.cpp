/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseOctahedron.cpp
 *  \brief  Definition of class \c GW_BaseOctahedron
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_BaseOctahedron.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_BaseOctahedron.h"

using namespace GW;

/* initialize the neighbor relation among subtrees */
GW_U32 GW_BaseOctahedron::aSubTreeNeighbor_[8][3] =
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
// Name : GW_BaseOctahedron constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
GW_BaseOctahedron::GW_BaseOctahedron()
:GW_BaseMesh_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_BaseOctahedron::~GW_BaseOctahedron()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron::BuildBaseMesh
/**
 *  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
 *  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  We construct a new list of node, and create associated vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_BaseOctahedron::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	GW_ASSERT( BaseNodeVector.empty() );
	GW_ASSERT( BaseVertexVector.empty() );
	pBaseNodeVector_ = &BaseNodeVector;
	BaseNodeVector.resize( 8 );
	BaseVertexVector.resize( 6 );

	/* create the nodes*/
	for( GW_U32 i=0; i<8; ++i )
		BaseNodeVector[i] = new GW_QuadTreeNode;
	/* create the vertex*/
	for( GW_U32 i=0; i<6; ++i )
		BaseVertexVector[i] = new GW_QuadTreeVertex;

	/* set up the position of the 6 vertex and assign them to the different childs */
	BaseVertexVector[k90N]->SetPosition(	GW_Vector3D(0,0,1) );
	BaseVertexVector[k90S]->SetPosition(	GW_Vector3D(0,0,-1) );
	BaseVertexVector[k180EW]->SetPosition(GW_Vector3D(0,1,0) );
	BaseVertexVector[k0EW]->SetPosition(	GW_Vector3D(0,-1,0) );
	BaseVertexVector[k90E]->SetPosition(	GW_Vector3D(1,0,0) );
	BaseVertexVector[k90W]->SetPosition(	GW_Vector3D(-1,0,0) );

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
// Name : GW_BaseOctahedron::GetRelativeSon
/**
 *  \param  nDirection [GW_U32] The direction.
 *  \return [GW_QuadTreeNode*] The neighbor.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Get the neighbor of a given node in a given direction (the node 
 *  should be a base node).
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeNode* GW_BaseOctahedron::GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction)
{
	GW_ASSERT( pBaseNodeVector_!=NULL );
	GW_ASSERT( pBaseNodeVector_->size()==8 );
	/* first translate the vertex direction into an index entry */
	GW_I32 nDirection = -1;
	for( GW_U32 i=0; i<3; ++i )
	{
		if( Son.GetVertex(i)==(&Direction) )
		{
			nDirection=i;
			break;
		}
	}
	GW_ASSERT( nDirection>=0 );
	/* first we must figure out wich is the number of pSon */
	for( GW_U32 i=0; i<8; ++i )
	{
		if( (&Son)==(*pBaseNodeVector_)[i] )
			return (*pBaseNodeVector_)[ aSubTreeNeighbor_[i][nDirection] ];			
	}
	GW_ASSERT( GW_False );
	return NULL;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron::Positionate
/**
 *  \param  CurNode [GW_QuadTreeNode&] The node we want to positionate.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Positionate the owned vertex of the node on a sphere.
 */
/*------------------------------------------------------------------------------*/
void GW_BaseOctahedron::Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, 
									GW_Vector3D BaryCoord0, GW_Vector3D BaryCoord1, GW_Vector3D BaryCoord2 )
{
	/* check for each central vertex if we need to create one new
	   or if it can be retrieve either from neighbor or from a pre-existing one */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex(i);
			GW_ASSERT( pVert!=NULL );
			GW_Vector3D Pos;
			GW_U32 s = (i+1) % 3; 
			GW_U32 t = (i+2) % 3;
			GW_ASSERT( CurNode.GetVertex(s)!=NULL );
			GW_ASSERT( CurNode.GetVertex(t)!=NULL );
			Pos = CurNode.GetVertex(s)->GetPosition() + CurNode.GetVertex(t)->GetPosition();	// compute middle
			Pos.Normalize();	// project on the sphere
			pVert->SetPosition(Pos);
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron::ConvertToLocalFrame
/**
 *  \param  Pos [GW_Vector3D&] The position.
 *  \param  rU [GW_Float&] X coord
 *  \param  rV [GW_Float] Y coord
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Compute local coordinnate from 3D vector position.
 */
/*------------------------------------------------------------------------------*/
void GW_BaseOctahedron::ConvertToLocalFrame( const GW_Vector3D& Pos, GW_Float& rU, GW_Float& rV )
{
	GW_SphericalMaths::ConvertCartesianToSpherical( Pos, rU, rV );
	/* U and V should be in [0,1]  */
	rU /= GW_TWOPI;
	rV = rV/GW_PI + 0.5f;
}


/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron::GetNbrVertex
/**
 *  \param  nDepth [GW_U32] The depth.
 *  \return [GW_U32] Number of vertice.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of vertex on the subdivided version of the 
 *  mesh, at given depth.
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseOctahedron::GetNbrVertex( GW_U32 nDepth )
{
	return (1 << (2*(nDepth+1)) ) + 2; // 4^(nDepth+1) + 2
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron::GetNbrFace
/**
 *  \param  nDepth [GW_U32] Depth.
 *  \return [GW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of face.
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseOctahedron::GetNbrFace( GW_U32 nDepth )
{
	return 12*( 1<<(2*nDepth) );	// 12*4^(nDepth)
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseOctahedron::GetNbrEdge
/**
 *  \param  nDepth [GW_U32] The depth.
 *  \return [GW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of edges.
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseOctahedron::GetNbrEdge( GW_U32 nDepth )
{
	return 8*( 1<<(2*nDepth) );		// 8*4^(nDepth)
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
