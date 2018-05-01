/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTreeNode.inl
 *  \brief  Inlined methods for \c GW_QuadTreeNode
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_QuadTreeNode.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetVertex
/**
 *  \param  pVert1 [GW_QuadTreeVertex*] Vertex number 1.
 *  \param  pVert2 [GW_QuadTreeVertex*] Vertex number 2.
 *  \param  pVert3 [GW_QuadTreeVertex*] Vertex number 3.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value of the different vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetVertex( GW_QuadTreeVertex* pVert1, GW_QuadTreeVertex* pVert2, GW_QuadTreeVertex* pVert3 )
{
	aVertex_[QT_Vert1] = pVert1;
	aVertex_[QT_Vert2] = pVert2;
	aVertex_[QT_Vert3] = pVert3;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetVertex
/**
 *  \param  pVert [GW_QuadTreeVertex*] The vertex.
 *  \param  nNum [GW_U32] The number we want this vertex to represent.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set a given vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetVertex( GW_QuadTreeVertex* pVert, GW_U32 nNum )
{
	GW_ASSERT( nNum<3 );
	aVertex_[nNum] = pVert;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetVertexNull
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set all vertex to NULL. Should be used only by the quadtree 
 *  himself when destroying the top 6 vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetVertexNull()
{
	aVertex_[QT_Vert1] = NULL;
	aVertex_[QT_Vert2] = NULL;
	aVertex_[QT_Vert3] = NULL;
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetVertex
/**
 *  \param  Num [T_QuadTreeNode_Num] The number of the vertex.
 *  \return [GW_QuadTreeVertex*] The vertex. Watch out, as usual, check for NULL !
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get a vertex given its number.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeVertex* GW_QuadTreeNode::GetVertex(GW_U32 nNum)
{
	GW_ASSERT( nNum<3 );
	return aVertex_[nNum];	
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetVertex
/**
 *  \param  Vert1 [GW_QuadTreeVertex&] 1st vertex
 *  \param  Vert2 [GW_QuadTreeVertex&] 2nd vertex
 *  \return [GW_QuadTreeVertex*] vertex
 *  \author Gabriel Peyré
 *  \date   2-28-2003
 * 
 *  Get one of the vertex via its facing edge.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeVertex* GW_QuadTreeNode::GetVertex( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 )
{
	for( GW_U32 i=0; i<3; ++i )
	{
		if( aVertex_[i]==&Vert1 )
		{
			if( aVertex_[(i+1)%3]==&Vert2 )
				return aVertex_[(i+2)%3];
			if( aVertex_[(i+2)%3]==&Vert2 )
				return aVertex_[(i+1)%3];
		}
	}
	return NULL;
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetVertex
/**
 *  \param  Num [T_QuadTreeNode_Num] The number of the vertex.
 *  \return [GW_QuadTreeVertex*] The vertex. Watch out, as usual, check for NULL !
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get a vertex given its number.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
const GW_QuadTreeVertex* GW_QuadTreeNode::GetVertexConst(T_QuadTreeVert_Num Num) const
{
	return aVertex_[Num];
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetChildNode
/**
 *  \param  pChild0 [GW_QuadTreeNode*] Children 0 (center).
 *  \param  pChild1 [GW_QuadTreeNode*] Child 1.
 *  \param  pChild2 [GW_QuadTreeNode*] Child 2.
 *  \param  pChild3 [GW_QuadTreeNode*] Child 3.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value of the 4 children.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetChildNode(	GW_QuadTreeNode* pChild0, 
										GW_QuadTreeNode* pChild1, 
										GW_QuadTreeNode* pChild2, 
										GW_QuadTreeNode* pChild3 )
{
	aChildNode_[0] = pChild0;
	aChildNode_[1] = pChild1;
	aChildNode_[2] = pChild2;
	aChildNode_[3] = pChild3;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetChildNode
/**
 *  \param  Num [GW_U32] The number of the child.
 *  \return [GW_QuadTreeNode*] The child.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get a child given its number.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeNode* GW_QuadTreeNode::GetChildNode(GW_U32 Num)
{
	GW_ASSERT(Num<4);
	return aChildNode_[Num];
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetFather
/**
 *  \return [GW_QuadTreeNode&] The father. Can be the tree if the node is one of the 8 roots.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Return the father of the node. It should never been NULL.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeNode& GW_QuadTreeNode::GetFather()
{
	GW_ASSERT( pFather_!=NULL );
	return *pFather_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetFather
/**
 *  \param  Father [GW_QuadTreeNode&] The father.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set the father node.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetFather(GW_QuadTreeNode& Father)
{
	pFather_ = &Father;
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetResponsabilityForVertex
/**
 *  \param  bResp [GW_Bool] New responsability.
 *  \param  nNum  [GW_U32] Number of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set the tag meaning if we are or not responsible for a given 
 *  vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetResponsabilityForVertex(GW_Bool bResp, GW_U32 nNum)
{
	GW_ASSERT( nNum<3 );
	aResponsibleForVertex_[nNum] = bResp;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetResponsabilityForVertex
/**
 *  \param  nNum [GW_U32] The number of the vertex.
 *  \return [GW_Bool] The responsability.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Check if we are responsible for a given vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_QuadTreeNode::GetResponsabilityForVertex(GW_U32 nNum)
{
	GW_ASSERT( nNum<3 );
	return aResponsibleForVertex_[nNum];
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetOwnedVertex
/**
 *  \param  nNum [GW_U32] The number of the vertex.
 *  \return [GW_QuadTreeVertex*] The vertex.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Get one of the central vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeVertex* GW_QuadTreeNode::GetOwnedVertex(GW_U32 nNum)
{
	GW_ASSERT( nNum<3 );
	if( aOwnedVertex_!=NULL )
	{
		/* this should be used only on destruction of nodes */
		return aOwnedVertex_[nNum];
	}
	if( this->GetChildNode(0)==NULL )
		return NULL;
	return this->GetChildNode(0)->GetVertex( nNum );
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetDepth
/**
 *  \return [GW_U32] The depth
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Get the depth of this node.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_U32 GW_QuadTreeNode::GetDepth()
{
	return nDepth_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetDepth
/**
 *  \param  nDepth [GW_U32] The depth.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set the depth of this node.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetDepth(GW_U32 nDepth)
{
	nDepth_ = nDepth;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetId
/**
 *  \param  nID [GW_U32] The new Id.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Set the Id of the node. Should be assigned at creation when 
 *	adding the node to the map storing all node at the current level.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetId(GW_U32 nID)
{
	nID_ = nID;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetId
/**
 *  \return [GW_U32] The Id of the node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Return the Id of the node.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_U32 GW_QuadTreeNode::GetId()
{
	return nID_;	
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetDataChunk
/**
 *  \return [GW_DataChunk_ABC*] The data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Return the data chunk. Can be null.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_DataChunk_ABC* GW_QuadTreeNode::GetDataChunk()
{
	return pDataChunk_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::IsLeaf
/**
 *  \return [GW_Bool] Response
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Are we a leaf of the tree ?
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_QuadTreeNode::IsLeaf()
{
	return (this->GetChildNode(0)==NULL);
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetCompressionType
/**
 *  \return [T_NodeCompressionType] The type of node (already processed/to process).
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Used during compression only.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeNode::T_NodeCompressionType GW_QuadTreeNode::GetCompressionType()
{
	return CompressionType_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetCompressionType
/**
 *  \param  CompressionType [T_NodeCompressionType] The kind of node.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Used during compression only.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetCompressionType(GW_QuadTreeNode::T_NodeCompressionType CompressionType)
{
	CompressionType_ = CompressionType;
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetValue
/**
 *  \param  rVal [GW_Float] The value hold by the slot of the vertex. Usefull in vertex base schemes.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value hold by this vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeNode::SetValue(GW_Float rVal)
{
	rVal_ = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetValue
/**
 *  \return [GW_Float] The slot value, used in vertex base wavelet.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Return the slot value.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_QuadTreeNode::GetValue() const 
{
	return rVal_;
}


GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
