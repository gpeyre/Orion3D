/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseMultiresolution.cpp
 *  \brief  Definition of class \c GW_BaseMultiresolution
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_BaseMultiresolution.cpp(c) Gabriel Peyré2003";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_BaseMultiresolution.h"


using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution constructor
/**
*  \author Gabriel Peyré
*  \date   11-27-2002
* 
*  Constructor. 
*/
/*------------------------------------------------------------------------------*/
GW_BaseMultiresolution::GW_BaseMultiresolution( GW_GeodesicMesh& GeodesicMesh, GW_VoronoiMesh& VoronoiMesh )
:	GW_BaseMesh_ABC(),
GeodesicMesh_	( GeodesicMesh ),
VoronoiMesh_	( VoronoiMesh )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution destructor
/**
*  \author Gabriel Peyré
*  \date   11-27-2002
* 
*  Destructor.
*/
/*------------------------------------------------------------------------------*/
GW_BaseMultiresolution::~GW_BaseMultiresolution()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::BuildBaseMesh
/**
*  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
*  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
*  \author Gabriel Peyré
*  \date   11-27-2002
* 
*  We construct a new list of node, and create associated vertex.
*/
/*------------------------------------------------------------------------------*/
void GW_BaseMultiresolution::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	GW_ASSERT( BaseNodeVector.empty() );
	GW_ASSERT( BaseVertexVector.empty() );
	pBaseNodeVector_ = &BaseNodeVector;
	BaseNodeVector.resize( VoronoiMesh_.GetNbrFace() );
	BaseVertexVector.resize( VoronoiMesh_.GetNbrVertex() );

	/* create the nodes*/
	for( GW_U32 i=0; i<VoronoiMesh_.GetNbrFace(); ++i )
	{
		BaseNodeVector[i] = new GW_QuadTreeNode;
		GW_QuadTreeNode* pNode = BaseNodeVector[i];
		GW_U32 nID = (GW_U32) BaseNodeVector[i];
		QuadTreeNodeID_[nID] = i;
	}
	/* create the vertex*/
	for( GW_U32 i=0; i<VoronoiMesh_.GetNbrVertex(); ++i )
	{
		BaseVertexVector[i] = new GW_QuadTreeVertex;
		GW_QuadTreeVertex* pVert = BaseVertexVector[i];
		GW_U32 nID = (GW_U32) BaseVertexVector[i];
		QuadTreeVertexID_[nID] = i;
	}

	/* set up the position of the vertex and assign them to the different childs */
	for( GW_U32 i=0; i<VoronoiMesh_.GetNbrVertex(); ++i )
	{
		GW_VoronoiVertex* pVoronoiVert = (GW_VoronoiVertex*) VoronoiMesh_.GetVertex(i);
		GW_ASSERT( pVoronoiVert!=NULL );
		GW_QuadTreeVertex* pQuadTreeVert = BaseVertexVector[i];
		GW_ASSERT( pQuadTreeVert!=NULL );
		pQuadTreeVert->SetPosition( pVoronoiVert->GetPosition() );
	}

	/* assign the vertex to the nodes */
	for( GW_U32 i=0; i<VoronoiMesh_.GetNbrFace(); ++i )
	{
		GW_Face* pFace = VoronoiMesh_.GetFace(i);
		GW_ASSERT( pFace!=NULL );
		for( GW_U32 nVert = 0; nVert<3; ++nVert )
		{
			GW_VoronoiVertex* pVoronoiVert = (GW_VoronoiVertex*) pFace->GetVertex(nVert); 
			GW_ASSERT( pVoronoiVert!=NULL );
			GW_U32 nNum = pVoronoiVert->GetID();
			GW_ASSERT( nNum<BaseVertexVector.size() );
			GW_QuadTreeVertex* pQuadTreeVert = BaseVertexVector[nNum];
			GW_ASSERT( pQuadTreeVert!=NULL );
			BaseNodeVector[i]->SetVertex( pQuadTreeVert, nVert );
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::GetVoronoiVertex
/**
 *  \param  QuadTreeVert [GW_QuadTreeVertex&] The quadtree vertex
 *  \return [GW_VoronoiVertex*] The voronoi vertex.
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 * 
 *  Get the voronoi vertex corresponding to a given quadtree vertex.
 */
/*------------------------------------------------------------------------------*/
GW_VoronoiVertex* GW_BaseMultiresolution::GetVoronoiVertex( GW_QuadTreeVertex& QuadTreeVert )
{
	GW_U32 nID = (GW_U32) &QuadTreeVert;
	if( QuadTreeVertexID_.find(nID)==QuadTreeVertexID_.end() )
		return NULL;
	GW_U32 nQuadTreeVertexID = QuadTreeVertexID_[nID];
	GW_ASSERT( nQuadTreeVertexID<VoronoiMesh_.GetNbrVertex() );
	return (GW_VoronoiVertex*) VoronoiMesh_.GetVertex( nQuadTreeVertexID );
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::GetVoronoiFace
/**
 *  \param  QuadTreeNode [GW_QuadTreeNode&] The node.
 *  \return [GW_Face*] The vertex.
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 * 
 *  Get the voronoi face corresponding to a quadtree node.
 */
/*------------------------------------------------------------------------------*/
GW_Face* GW_BaseMultiresolution::GetVoronoiFace( GW_QuadTreeNode& QuadTreeNode )
{
	GW_U32 nID = (GW_U32) &QuadTreeNode;
	if( QuadTreeNodeID_.find(nID)==QuadTreeNodeID_.end() )
		return NULL;
	GW_U32 nQuadTreeNodeID = QuadTreeNodeID_[nID];
	GW_ASSERT( nQuadTreeNodeID<VoronoiMesh_.GetNbrFace() );
	return VoronoiMesh_.GetFace( nQuadTreeNodeID );
}



/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::GetRelativeSon
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
GW_QuadTreeNode* GW_BaseMultiresolution::GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction)
{
	GW_ASSERT( pBaseNodeVector_!=NULL );
	GW_ASSERT( pBaseNodeVector_->size()==VoronoiMesh_.GetNbrFace() );
	/* find the voronoi vertex corresponding to the direction */
	GW_VoronoiVertex* pVoronoiDirection = this->GetVoronoiVertex( Direction );
	GW_ASSERT( pVoronoiDirection!=NULL );
	/* find the voronoi face */
	GW_Face* pVoronoiFace = this->GetVoronoiFace( Son );
	GW_ASSERT( pVoronoiFace!=NULL );
	GW_Face* pVoronoiNeighbor = pVoronoiFace->GetFaceNeighbor( *pVoronoiDirection );
	GW_ASSERT( pVoronoiNeighbor!=NULL );
	if( pVoronoiNeighbor==NULL )
		return NULL;
	/* find the quadtree node corresponding to it */
	GW_U32 nNum = pVoronoiNeighbor->GetID();
	GW_ASSERT( nNum<pBaseNodeVector_->size() );
	return (*pBaseNodeVector_)[nNum];
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::Positionate
/**
*  \param  CurNode [GW_QuadTreeNode&] The node we want to positionate.
*  \author Gabriel Peyré
*  \date   11-27-2002
* 
*  Positionate the owned vertex of the node on a sphere.
*/
/*------------------------------------------------------------------------------*/
void GW_BaseMultiresolution::Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, 
										 GW_Vector3D BaryCoord0, GW_Vector3D BaryCoord1, GW_Vector3D BaryCoord2 )
{
	/* find the voronoi vertex corresponding to the face */
	GW_Face* pVoronoiFace = this->GetVoronoiFace( RootNode );
	GW_ASSERT( pVoronoiFace!=NULL );
	GW_VoronoiVertex* pV0 = (GW_VoronoiVertex*) pVoronoiFace->GetVertex(0);	GW_ASSERT( pV0!=NULL );
	GW_VoronoiVertex* pV1 = (GW_VoronoiVertex*) pVoronoiFace->GetVertex(1);	GW_ASSERT( pV1!=NULL );
	GW_VoronoiVertex* pV2 = (GW_VoronoiVertex*) pVoronoiFace->GetVertex(2);	GW_ASSERT( pV2!=NULL );

	/* check for each central vertex if we need to create one new
	   or if it can be retrieve either from neighbor or from a pre-existing one */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			/* compute the barycentric coordinate of the vertex */
			GW_Vector3D BaryCoord;
			if( i==0 )
				BaryCoord = ( BaryCoord1+BaryCoord2 )/2;
			if( i==1 )
				BaryCoord = ( BaryCoord0+BaryCoord2 )/2;
			if( i==2 )
				BaryCoord = ( BaryCoord0+BaryCoord1 )/2;
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex(i);
			GW_ASSERT( pVert!=NULL );
			/* ask to the mesh for the position */
			GW_Vector3D Pos;
			VoronoiMesh_.InterpolatePosition( GeodesicMesh_, Pos, *pV0, *pV1, *pV2, BaryCoord[0], BaryCoord[1], BaryCoord[2] );
//			VoronoiMesh_.InterpolatePositionExhaustiveSearch( GeodesicMesh_, Pos, *pV0, *pV1, *pV2, BaryCoord[0], BaryCoord[1], BaryCoord[2] );
			pVert->SetPosition(Pos);
		}
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::ConvertToLocalFrame
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
void GW_BaseMultiresolution::ConvertToLocalFrame( const GW_Vector3D& Pos, GW_Float& rU, GW_Float& rV )
{
	/* todo : fix it */
	rU = 0;
	rV = 0;
}


/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::GetNbrVertex
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
GW_U32 GW_BaseMultiresolution::GetNbrVertex( GW_U32 nDepth )
{
	GW_ASSERT( GW_False );	// not yet set
	return (1 << (2*(nDepth+1)) ) + 2; // 4^(nDepth+1) + 2
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::GetNbrFace
/**
*  \param  nDepth [GW_U32] Depth.
*  \return [GW_U32] Answer.
*  \author Gabriel Peyré
*  \date   11-27-2002
* 
*  Compute the number of face.
*/
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseMultiresolution::GetNbrFace( GW_U32 nDepth )
{
	GW_ASSERT( GW_False );	// not yet set
	return 12*( 1<<(2*nDepth) );	// 12*4^(nDepth)
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseMultiresolution::GetNbrEdge
/**
*  \param  nDepth [GW_U32] The depth.
*  \return [GW_U32] Answer.
*  \author Gabriel Peyré
*  \date   11-27-2002
* 
*  Compute the number of edges.
*/
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseMultiresolution::GetNbrEdge( GW_U32 nDepth )
{
	GW_ASSERT( GW_False );	// not yet set
	return 8*( 1<<(2*nDepth) );		// 8*4^(nDepth)
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
