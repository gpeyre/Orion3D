/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseButterfly.cpp
 *  \brief  Definition of class \c FSW_BaseButterfly
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_BaseButterfly.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_BaseButterfly.h"
#include "FSW_ButterflyWavelet.h"

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
FSW_BaseButterfly::FSW_BaseButterfly( FSW_BaseMesh_ABC& StartMesh )
:	FSW_BaseMesh_ABC(),
	pStartMesh_( &StartMesh )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_BaseButterfly::~FSW_BaseButterfly()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::BuildBaseMesh
/**
 *  \param  BaseNodeVector [T_QuadTreeNodeList&] A vector of node to fill.
 *  \param  BaseVertexVector [T_QuadTreeVertexVector&] A vector of vertex to fill.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  We construct a new list of node, and create associated vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseButterfly::BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector )
{
	FSW_ASSERT( pStartMesh_!=NULL );
	pStartMesh_->BuildBaseMesh(BaseNodeVector, BaseVertexVector);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::GetRelativeSon
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
FSW_QuadTreeNode* FSW_BaseButterfly::GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction)
{
	FSW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetRelativeSon( Son, Direction );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::Positionate
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The node we want to positionate.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Positionate the owned vertex of the node on a sphere.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseButterfly::Positionate( FSW_QuadTreeNode& CurNode )
{
	/* check for each central vertex if we need to create one new
	   or if it can be retrieve either from neighbor or from a pre-existing one */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex(i);
			FSW_ASSERT( pVert!=NULL );
			pVert->SetPosition( FSW_Vector3D(0,0,0) );	// before iterating, reset position.
			FSW_ButterflyWavelet::IterateFunctionOnLocalStencil( CurNode, Positionate_Helper, i, pVert, rTension_ );
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::Positionate_Helper
/**
 *  \param  StencilVert [FSW_QuadTreeVertex&] A vertex in the stencil.
 *  \param  rWeight [FSW_Float] It's weight.
 *  \param  pChunk [void*] Should be the center vertex.
 *  \author Gabriel Peyré
 *  \date   12-2-2002
 * 
 *  This function is called on each vertex of the stencil of a given 
 *  vertex to positionate it. So simple using \c FSW_ButterflyWavelet::IterateFunctionOnLocalStencil !
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseButterfly::Positionate_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk )
{
	FSW_QuadTreeVertex* pVert = (FSW_QuadTreeVertex*) pChunk;
	FSW_ASSERT( pVert!=NULL );
	pVert->SetPosition( pVert->GetPosition() + StencilVert.GetPosition()*rWeight );
}



/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::ConvertToLocalFrame
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
void FSW_BaseButterfly::ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV )
{
	FSW_ASSERT( pStartMesh_!=NULL );
	pStartMesh_->ConvertToLocalFrame( Pos, rU, rV );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::GetNbrVertex
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
FSW_U32 FSW_BaseButterfly::GetNbrVertex( FSW_U32 nDepth )
{
	FSW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetNbrVertex( nDepth );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::GetNbrFace
/**
 *  \param  nDepth [FSW_U32] Depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of face.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseButterfly::GetNbrFace( FSW_U32 nDepth )
{
	FSW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetNbrFace( nDepth );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::GetNbrEdge
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \return [FSW_U32] Answer.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Compute the number of edges.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_BaseButterfly::GetNbrEdge( FSW_U32 nDepth )
{
	FSW_ASSERT( pStartMesh_!=NULL );
	return pStartMesh_->GetNbrEdge( nDepth );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::GetTension
/**
 *  \return [FSW_Float] Tension.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Get the tension of the scheme.
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_BaseButterfly::GetTension() const
{
	return rTension_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BaseButterfly::SetTension
/**
 *  \param  rTension [FSW_Float] Tension.
 *  \author Gabriel Peyré
 *  \date   12-3-2002
 * 
 *  Set the tension of the scheme.
 */
/*------------------------------------------------------------------------------*/
void FSW_BaseButterfly::SetTension(FSW_Float rTension)
{
	rTension_ = rTension;
}




///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
