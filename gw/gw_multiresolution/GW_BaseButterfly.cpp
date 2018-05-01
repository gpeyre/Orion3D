/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseButterfly.cpp
 *  \brief  Definition of class \c GW_BaseButterfly
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_BaseButterfly.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_BaseButterfly.h"
#include "GW_ButterflyWavelet.h"

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
GW_BaseButterfly::GW_BaseButterfly( GW_BaseMesh_ABC& StartMesh )
:	GW_BaseMesh_ABC(),
	pStartMesh_( &StartMesh )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_BaseButterfly::~GW_BaseButterfly()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::BuildBaseMesh
/**
 *  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
 *  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  We construct a new list of node, and create associated vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_BaseButterfly::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	GW_ASSERT( pStartMesh_!=NULL );
	pStartMesh_->BuildBaseMesh(BaseNodeVector, BaseVertexVector);
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::GetRelativeSon
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
GW_QuadTreeNode* GW_BaseButterfly::GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction)
{
	GW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetRelativeSon( Son, Direction );
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::Positionate
/**
 *  \param  CurNode [GW_QuadTreeNode&] The node we want to positionate.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Positionate the owned vertex of the node on a sphere.
 */
/*------------------------------------------------------------------------------*/
void GW_BaseButterfly::Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, 
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
			pVert->SetPosition( GW_Vector3D(0,0,0) );	// before iterating, reset position.
			GW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Positionate_Helper, i, pVert, rTension_ );
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::Positionate_Helper
/**
 *  \param  StencilVert [GW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [GW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to positionate it. So simple using \c GW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void GW_BaseButterfly::Positionate_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk )
{
	GW_QuadTreeVertex* pVert = (GW_QuadTreeVertex*) pChunk;
	GW_ASSERT( pVert!=NULL );
	pVert->SetPosition( pVert->GetPosition() + StencilVert.GetPosition()*rWeight );
}



/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::ConvertToLocalFrame
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
void GW_BaseButterfly::ConvertToLocalFrame( const GW_Vector3D& Pos, GW_Float& rU, GW_Float& rV )
{
	GW_ASSERT( pStartMesh_!=NULL );
	pStartMesh_->ConvertToLocalFrame( Pos, rU, rV );
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::GetNbrVertex
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
GW_U32 GW_BaseButterfly::GetNbrVertex( GW_U32 nDepth )
{
	GW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetNbrVertex( nDepth );
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::GetNbrFace
/**
 *  \param  nDepth [GW_U32] Depth.
 *  \return [GW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of face.
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseButterfly::GetNbrFace( GW_U32 nDepth )
{
	GW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetNbrFace( nDepth );
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::GetNbrEdge
/**
 *  \param  nDepth [GW_U32] The depth.
 *  \return [GW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of edges.
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_BaseButterfly::GetNbrEdge( GW_U32 nDepth )
{
	GW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetNbrEdge( nDepth );
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::GetTension
/**
 *  \return [GW_Float] Tension.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Get the tension of the scheme.
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_BaseButterfly::GetTension() const
{
	return rTension_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BaseButterfly::SetTension
/**
 *  \param  rTension [GW_Float] Tension.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the tension of the scheme.
 */
/*------------------------------------------------------------------------------*/
void GW_BaseButterfly::SetTension(GW_Float rTension)
{
	rTension_ = rTension;
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
