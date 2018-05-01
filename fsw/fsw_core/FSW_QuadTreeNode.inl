/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTreeNode.inl
 *  \brief  Inlined methods for \c FSW_QuadTreeNode
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_QuadTreeNode.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetVertex
/**
 *  \param  pVert1 [FSW_QuadTreeVertex*] Vertex number 1.
 *  \param  pVert2 [FSW_QuadTreeVertex*] Vertex number 2.
 *  \param  pVert3 [FSW_QuadTreeVertex*] Vertex number 3.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value of the different vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetVertex( FSW_QuadTreeVertex* pVert1, FSW_QuadTreeVertex* pVert2, FSW_QuadTreeVertex* pVert3 )
{
	aVertex_[QT_Vert1] = pVert1;
	aVertex_[QT_Vert2] = pVert2;
	aVertex_[QT_Vert3] = pVert3;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetVertex
/**
 *  \param  pVert [FSW_QuadTreeVertex*] The vertex.
 *  \param  nNum [FSW_U32] The number we want this vertex to represent.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set a given vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetVertex( FSW_QuadTreeVertex* pVert, FSW_U32 nNum )
{
	FSW_ASSERT( nNum<3 );
	aVertex_[nNum] = pVert;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetVertexNull
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set all vertex to NULL. Should be used only by the quadtree 
 *  himself when destroying the top 6 vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetVertexNull()
{
	aVertex_[QT_Vert1] = NULL;
	aVertex_[QT_Vert2] = NULL;
	aVertex_[QT_Vert3] = NULL;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetVertex
/**
 *  \param  Num [T_QuadTreeNode_Num] The number of the vertex.
 *  \return [FSW_QuadTreeVertex*] The vertex. Watch out, as usual, check for NULL !
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get a vertex given its number.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTreeVertex* FSW_QuadTreeNode::GetVertex(FSW_U32 nNum)
{
	FSW_ASSERT( nNum<3 );
	return aVertex_[nNum];	
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetVertex
/**
 *  \param  Vert1 [FSW_QuadTreeVertex&] 1st vertex
 *  \param  Vert2 [FSW_QuadTreeVertex&] 2nd vertex
 *  \return [FSW_QuadTreeVertex*] vertex
 *  \author Gabriel Peyré
 *  \date   2-28-2003
 * 
 *  Get one of the vertex via its facing edge.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTreeVertex* FSW_QuadTreeNode::GetVertex( FSW_QuadTreeVertex& Vert1, FSW_QuadTreeVertex& Vert2 )
{
	for( FSW_U32 i=0; i<3; ++i )
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
// Name : FSW_QuadTreeNode::GetVertex
/**
 *  \param  Num [T_QuadTreeNode_Num] The number of the vertex.
 *  \return [FSW_QuadTreeVertex*] The vertex. Watch out, as usual, check for NULL !
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get a vertex given its number.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
const FSW_QuadTreeVertex* FSW_QuadTreeNode::GetVertexConst(T_QuadTreeVert_Num Num) const
{
	return aVertex_[Num];
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetChildNode
/**
 *  \param  pChild0 [FSW_QuadTreeNode*] Children 0 (center).
 *  \param  pChild1 [FSW_QuadTreeNode*] Child 1.
 *  \param  pChild2 [FSW_QuadTreeNode*] Child 2.
 *  \param  pChild3 [FSW_QuadTreeNode*] Child 3.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value of the 4 children.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetChildNode(	FSW_QuadTreeNode* pChild0, 
										FSW_QuadTreeNode* pChild1, 
										FSW_QuadTreeNode* pChild2, 
										FSW_QuadTreeNode* pChild3 )
{
	aChildNode_[0] = pChild0;
	aChildNode_[1] = pChild1;
	aChildNode_[2] = pChild2;
	aChildNode_[3] = pChild3;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetChildNode
/**
 *  \param  Num [FSW_U32] The number of the child.
 *  \return [FSW_QuadTreeNode*] The child.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get a child given its number.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTreeNode* FSW_QuadTreeNode::GetChildNode(FSW_U32 Num)
{
	FSW_ASSERT(Num<4);
	return aChildNode_[Num];
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetFather
/**
 *  \return [FSW_QuadTreeNode&] The father. Can be the tree if the node is one of the 8 roots.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Return the father of the node. It should never been NULL.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTreeNode& FSW_QuadTreeNode::GetFather()
{
	FSW_ASSERT( pFather_!=NULL );
	return *pFather_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetFather
/**
 *  \param  Father [FSW_QuadTreeNode&] The father.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set the father node.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetFather(FSW_QuadTreeNode& Father)
{
	pFather_ = &Father;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetResponsabilityForVertex
/**
 *  \param  bResp [FSW_Bool] New responsability.
 *  \param  nNum  [FSW_U32] Number of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set the tag meaning if we are or not responsible for a given 
 *  vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetResponsabilityForVertex(FSW_Bool bResp, FSW_U32 nNum)
{
	FSW_ASSERT( nNum<3 );
	aResponsibleForVertex_[nNum] = bResp;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetResponsabilityForVertex
/**
 *  \param  nNum [FSW_U32] The number of the vertex.
 *  \return [FSW_Bool] The responsability.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Check if we are responsible for a given vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_QuadTreeNode::GetResponsabilityForVertex(FSW_U32 nNum)
{
	FSW_ASSERT( nNum<3 );
	return aResponsibleForVertex_[nNum];
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetOwnedVertex
/**
 *  \param  nNum [FSW_U32] The number of the vertex.
 *  \return [FSW_QuadTreeVertex*] The vertex.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Get one of the central vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTreeVertex* FSW_QuadTreeNode::GetOwnedVertex(FSW_U32 nNum)
{
	FSW_ASSERT( nNum<3 );
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
// Name : FSW_QuadTreeNode::GetDepth
/**
 *  \return [FSW_U32] The depth
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Get the depth of this node.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_U32 FSW_QuadTreeNode::GetDepth()
{
	return nDepth_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetDepth
/**
 *  \param  nDepth [FSW_U32] The depth.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Set the depth of this node.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetDepth(FSW_U32 nDepth)
{
	nDepth_ = nDepth;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetId
/**
 *  \param  nID [FSW_U32] The new Id.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Set the Id of the node. Should be assigned at creation when 
 *	adding the node to the map storing all node at the current level.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetId(FSW_U32 nID)
{
	nID_ = nID;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetId
/**
 *  \return [FSW_U32] The Id of the node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Return the Id of the node.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_U32 FSW_QuadTreeNode::GetId()
{
	return nID_;	
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetDataChunk
/**
 *  \return [FSW_DataChunk_ABC*] The data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Return the data chunk. Can be null.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_DataChunk_ABC* FSW_QuadTreeNode::GetDataChunk()
{
	return pDataChunk_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::IsLeaf
/**
 *  \return [FSW_Bool] Response
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Are we a leaf of the tree ?
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_QuadTreeNode::IsLeaf()
{
	return (this->GetChildNode(0)==NULL);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetCompressionType
/**
 *  \return [T_NodeCompressionType] The type of node (already processed/to process).
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Used during compression only.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTreeNode::T_NodeCompressionType FSW_QuadTreeNode::GetCompressionType()
{
	return CompressionType_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetCompressionType
/**
 *  \param  CompressionType [T_NodeCompressionType] The kind of node.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Used during compression only.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetCompressionType(FSW_QuadTreeNode::T_NodeCompressionType CompressionType)
{
	CompressionType_ = CompressionType;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::SetValue
/**
 *  \param  rVal [FSW_Float] The value hold by the slot of the vertex. Usefull in vertex base schemes.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value hold by this vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeNode::SetValue(FSW_Float rVal)
{
	rVal_ = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::GetValue
/**
 *  \return [FSW_Float] The slot value, used in vertex base wavelet.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Return the slot value.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_QuadTreeNode::GetValue() const 
{
	return rVal_;
}


FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
