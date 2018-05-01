/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTreeNode.cpp
 *  \brief  Definition of class \c GW_QuadTreeNode
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_QuadTreeNode.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_QuadTreeNode.h"
#include "GW_QuadTree.h"
#include "GW_NodeMap.h"
#include "GW_BaseMesh_ABC.h"

#ifndef GW_USE_INLINE
    #include "GW_QuadTreeNode.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeNode::GW_QuadTreeNode()
:	pDataChunk_			( NULL ),
	pFather_			( NULL ),
	nDepth_				( 0 ),
	nID_				( 0 ),
	CompressionType_	( kTypeUndefined ),
	rVal_				( 0 ),
	aOwnedVertex_		( NULL )
{
	aChildNode_[0] = NULL;
	aChildNode_[1] = NULL;
	aChildNode_[2] = NULL;
	aChildNode_[3] = NULL;

	aVertex_[0] = NULL;
	aVertex_[1] = NULL;
	aVertex_[2] = NULL;

	aResponsibleForVertex_[0] = GW_False;
	aResponsibleForVertex_[1] = GW_False;
	aResponsibleForVertex_[2] = GW_False;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Destructor. Recurse on child nodes.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTreeNode::~GW_QuadTreeNode()
{
	GW_QuadTree* pQuadTree = GW_QuadTree::StaticThis();
	GW_ASSERT( pQuadTree!=NULL );

	if( aChildNode_[0]!=NULL )
	{
		/* first delete the child, but remember the vertex we own [because child 0 is deleted] */
		GW_ASSERT( aOwnedVertex_==NULL );
		aOwnedVertex_ = new GW_QuadTreeVertex*[3];
		aOwnedVertex_[0] = aChildNode_[0]->GetVertex(0);
		aOwnedVertex_[1] = aChildNode_[0]->GetVertex(1);
		aOwnedVertex_[2] = aChildNode_[0]->GetVertex(2);
		GW_ASSERT( pQuadTree->NodeMapExist( this->GetDepth()+1 ) );
		GW_NodeMap& NodeMap = pQuadTree->GetNodeMap( this->GetDepth()+1 );
		/* desalocate the child */
		for( GW_U32 i=0; i<4; ++i )
		{
			NodeMap.Remove( *aChildNode_[i] );
			GW_DELETE( aChildNode_[i] );
		}

		/* delete the vertex we are responsible for [this must be done after deleting the sub-nodes] */
		for( GW_U32 i=0; i<3; ++i )
		{
			if( this->GetResponsabilityForVertex(i) )
			{
				/* oups, we are responsible for this one :
				   try to give responsabiltity to our neighbor, else
				   delete the vertex. */
				GW_ASSERT( this->GetVertex(i)!=NULL );
				GW_QuadTreeNode* pNeighbor = this->GetNeighbor( *this->GetVertex(i) );
				if( pNeighbor!=NULL )
				{
					GW_QuadTreeVertex* pVert = this->GetOwnedVertex(i);
					GW_I32 nNeighborVertexNumber = pNeighbor->GetOwnedVertexNumber( *pVert );
					GW_ASSERT( nNeighborVertexNumber>=0 );
					GW_ASSERT( pNeighbor->GetResponsabilityForVertex( nNeighborVertexNumber )==GW_False );
					pNeighbor->SetResponsabilityForVertex( GW_True, nNeighborVertexNumber );
				}
				else
				{
					/* don't use this->GetOwnedVertex(), since child 0 is deleted ! */
					GW_ASSERT( aOwnedVertex_[i] != NULL );
					GW_DELETE( aOwnedVertex_[i] );
				}
				/* we are no more responsible */
				this->SetResponsabilityForVertex( GW_False, i );
			}
		}
	}
	else
	{
		/* just some debug check */
		GW_ASSERT( aChildNode_[1]==NULL );
		GW_ASSERT( aChildNode_[2]==NULL );
		GW_ASSERT( aChildNode_[3]==NULL );
	}

	/* delete the data chunk if needed */
	GW_DELETE( pDataChunk_ );
	/* delete the local copy of the central vertex */
	GW_DELETEARRAY( aOwnedVertex_ );
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetVertexNoMoreUsed
/**
 *  \param  Num [T_QuadTreeNode_Num] the number of the vertex that have been deleted.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Called by a father node that have desalocated the given vertex, 
 *  and want us to be aware of that.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTreeNode::SetVertexNoMoreUsed(T_QuadTreeVert_Num Num)
{
	aVertex_[Num] = NULL;
	/* recurse on our children : tell to the child that 
	   use the deleted vertex that this vertex is no more used */
	if( Num==QT_Vert1 && aChildNode_[1]!=NULL ) 
		aChildNode_[1]->SetVertexNoMoreUsed( Num );
	if( Num==QT_Vert2 && aChildNode_[2]!=NULL)
		aChildNode_[2]->SetVertexNoMoreUsed( Num );
	if( Num==QT_Vert3 && aChildNode_[3]!=NULL)
		aChildNode_[3]->SetVertexNoMoreUsed( Num );
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::BuildTree
/**
 *	\param  BaseMesh  [GW_BaseMesh_ABC&] The base mesh that will carry out the subdivision.
 *  \param  Func [GW_TreeFunction_ABC&] The function we want to define on the sphere.
 *  \param  nCurLevel [GW_U32] Current level.
 *  \param  nMaxLevel [GW_U32] Maximum level.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Subdivide the tree.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTreeNode::BuildTree(GW_BaseMesh_ABC& BaseMesh, const GW_TreeFunction_ABC& Func, GW_U32 nCurLevel, GW_U32 nMaxLevel)
{
	/* use the old 'static this pointer' trick to access the global quadtree */
	GW_QuadTree* pQuadTree = GW_QuadTree::StaticThis();
	GW_ASSERT( pQuadTree!=NULL );

	/* check if we should continue to subdivide */
	if( nCurLevel>nMaxLevel )
	{
		/* stop subdivision, desallocate memory if needed */
		if( aChildNode_[0]!=NULL )
		{
			/* if the center node exist, the other must exist ! */
			GW_ASSERT( aChildNode_[1]!=NULL );
			GW_ASSERT( aChildNode_[2]!=NULL );
			GW_ASSERT( aChildNode_[3]!=NULL );
			/* check the 3 central vertex, and make 
			   something if we are responsible for one */
			for( GW_U32 i=0; i<3; ++i )
			{
				if( this->GetResponsabilityForVertex(i) )
				{
					/* oups, we are responsible for this one :
					   try to give responsabiltity to our neighbor, else
					   delete the vertex. */
					GW_ASSERT( this->GetVertex(i)!=NULL );
					GW_QuadTreeNode* pNeighbor = this->GetNeighbor( *this->GetVertex(i) );	
					GW_QuadTreeVertex* pVert = this->GetOwnedVertex(i);
					if( pNeighbor!=NULL && pNeighbor->GetChildNode(0)!=NULL )
					{
						/* retrieve the number of the vertex for the neighbor */
						GW_I32 nNeighborVertexNumber = pNeighbor->GetOwnedVertexNumber( *pVert );
						GW_ASSERT( nNeighborVertexNumber>=0 );
						pNeighbor->SetResponsabilityForVertex( GW_True, nNeighborVertexNumber );
					}
					else
					{
						GW_ASSERT( pVert != NULL );
						GW_DELETE( pVert );
					}
					/* no, we are no more responsible for this one */
					this->SetResponsabilityForVertex( GW_False, i );
				}
			}
			/* tell to the other triangle these vertex no longer exist */
			aChildNode_[0]->SetVertexNoMoreUsed(QT_Vert1);
			aChildNode_[0]->SetVertexNoMoreUsed(QT_Vert2);
			aChildNode_[0]->SetVertexNoMoreUsed(QT_Vert3);
			aChildNode_[1]->SetVertexNoMoreUsed(QT_Vert1);
			aChildNode_[1]->SetVertexNoMoreUsed(QT_Vert2);
			aChildNode_[1]->SetVertexNoMoreUsed(QT_Vert3);
			aChildNode_[2]->SetVertexNoMoreUsed(QT_Vert1);
			aChildNode_[2]->SetVertexNoMoreUsed(QT_Vert2);
			aChildNode_[2]->SetVertexNoMoreUsed(QT_Vert3);
			aChildNode_[3]->SetVertexNoMoreUsed(QT_Vert1);
			aChildNode_[3]->SetVertexNoMoreUsed(QT_Vert2);
			aChildNode_[3]->SetVertexNoMoreUsed(QT_Vert3);

			/* Retrieve the current map that store all nodes at the current level. 
			   But make a check to be sure that this map really exist (otherwise this call would create a new one). */
			GW_ASSERT( pQuadTree->NodeMapExist( nCurLevel ) );
			GW_NodeMap& NodeMap = pQuadTree->GetNodeMap( nCurLevel );
			/* desalocate the child */
			for( GW_U32 i=0; i<4; ++i )
			{
				NodeMap.Remove( *aChildNode_[i] );
				GW_DELETE( aChildNode_[i] );
			}
		}
		else
		{
			/* must reset the responsability set to true by default */
			for( GW_U32 i=0; i<3; ++i )
				this->SetResponsabilityForVertex( GW_False, i );
		}
		GW_ASSERT( this->GetResponsabilityForVertex(0)==GW_False );
		GW_ASSERT( this->GetResponsabilityForVertex(1)==GW_False );
		GW_ASSERT( this->GetResponsabilityForVertex(2)==GW_False );
		return;
	}

	/* Retrieve the current map that store all nodes at the current level
	   This will create a new one if needed. */
	GW_NodeMap& NodeMap = pQuadTree->GetNodeMap( nCurLevel );

	/* continue subdivision, allocate if needed */
	if( aChildNode_[0]==NULL )
	{
		/* if the center node doesn't exist, the other shouldn't exist ! */
		GW_ASSERT( aChildNode_[1]==NULL );
		GW_ASSERT( aChildNode_[2]==NULL );
		GW_ASSERT( aChildNode_[3]==NULL );
		/* the children have not been allocated, so do so */
		for( GW_U32 i=0; i<4; ++i )
		{
			aChildNode_[i] = new GW_QuadTreeNode;
			aChildNode_[i]->SetFather(*this);
			aChildNode_[i]->SetDepth( nCurLevel );
			NodeMap.Add( *aChildNode_[i] );
		}
	}
	/* check for each central vertex if we need to create one new
	   or if it can be retrieve either from neighbor or from a pre-existing one */
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = this->GetOwnedVertex(i);
		/* Check if we have already created the vertex.
		   If this is the case, we don't need to do anything. */
		if( pVert==NULL )
		{
			GW_ASSERT( this->GetVertex(i)!=NULL );
			GW_QuadTreeNode* pNeighbor = this->GetNeighbor( *this->GetVertex(i) );
			if( pNeighbor!=NULL )
				pVert = pNeighbor->GetVertexBetween( *this->GetVertex((i+1)%3), *this->GetVertex((i+2)%3) );
			if( pVert!=NULL )
			{
				/* Our neighbor already has a vertex : he keeps the 
				   responsability, and we use it's vertex */
				this->SetResponsabilityForVertex( GW_False, i );
				/* As we didn't has the vertex, this means that
				   our neighbor must be the responsible for this vertex. */
				GW_ASSERT( pNeighbor->GetResponsabilityForVertex( pNeighbor->GetOwnedVertexNumber( *pVert ) )==GW_True );
				/* assign it to our child */
				aChildNode_[0]->SetVertex(pVert, i);
			}
			else
			{
				/* nobody has already created this vertex, so do it */
				pVert = new GW_QuadTreeVertex;
				/* and of course, take the responsability for it */
				this->SetResponsabilityForVertex(GW_True, i);
				/* assign it only to the central face, for the moment */
				aChildNode_[0]->SetVertex(pVert, i);
			}
		}
	}

	/* assign the vertex to the 3 non-central faces (the central has already been taken care at) */
	GW_QuadTreeVertex* pVert1 = this->GetOwnedVertex(QT_Vert1);
	GW_QuadTreeVertex* pVert2 = this->GetOwnedVertex(QT_Vert2);
	GW_QuadTreeVertex* pVert3 = this->GetOwnedVertex(QT_Vert3);
	GW_ASSERT( pVert1!=NULL );
	GW_ASSERT( pVert2!=NULL );
	GW_ASSERT( pVert3!=NULL );
	/* set the vertex for the child nodes */
	aChildNode_[1]->SetVertex(aVertex_[QT_Vert1], pVert2, pVert3);
	aChildNode_[2]->SetVertex(pVert1, aVertex_[QT_Vert2], pVert3);
	aChildNode_[3]->SetVertex(pVert1, pVert2, aVertex_[QT_Vert3]);

	/* recurse on the child nodes */
	for( GW_U32 i=0; i<4; ++i )
			aChildNode_[i]->BuildTree(BaseMesh, Func, nCurLevel+1, nMaxLevel);
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetNeighbor
/**
 *  \param  Direction [GW_QuadTreeVertex&] The direction. Must be on the 3 vertex that compose the face.
 *	The neighbor node is the one opposed to the direction vertex.
 *  \return [GW_QuadTreeNode*] The neighbor. Can be NULL if a part of the tree was deleted.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  Find the neighbor in the given direction. Make use of clever calls of GetRelativeSon
 *	on the father node.
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeNode* GW_QuadTreeNode::GetNeighbor(GW_QuadTreeVertex& Direction)
{
	GW_ASSERT( pFather_!=NULL );
	return pFather_->GetRelativeSon( *this, Direction );
}



/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetRelativeSon
/**
 *  \param  Son [GW_QuadTreeNode&] The son who wants to know about its neighbor.
 *  \param  nDirection [GW_U32] The direction of the search, relative to the son orientation, not our orientation.
 *  \return [GW_QuadTreeNode*] The searched neighbor.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  This is quite a compex method. This is call by a son of us (namely \c Son), 
 *	wich wants to know who is its neighbor relative to the direction \c Direction.
 *	The direction is given by a vertex, because we are looking for the face opposed to the vertex.
 *
 *	This function is overloaded by the class GW_QuadTree, as a tricky way to 
 *	find the neighbor between root node (which in reality have no father, but
 *	we set a "vritual" father as beeing the tree himself).
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeNode* GW_QuadTreeNode::GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction)
{
	/* very simple : the son is the center node */
	if( (&Son)==aChildNode_[0] )
	{
		for( GW_U32 i=0; i<3; ++i )
		{
			if( (&Direction)==this->GetOwnedVertex(i) )
				return this->GetChildNode( i+1 );
		}
		GW_ASSERT( GW_False );
	}

	/* if the direction is one of our vertex, then the answer must be the central node */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( (&Direction)==this->GetVertex(i) )
			return aChildNode_[0];
	}


	/* difficult case : we are not able to answer to the question, and must ask to our neighbor
	   first we must figure out wich is the number of the son, should be in {1,2,3} */
	GW_I32 nSonNum = -1; 
	for( GW_U32 i=1; i<4; ++i )
	{
		if( (&Son)==aChildNode_[i] )
			nSonNum  = i;
	}
	GW_ASSERT( nSonNum>=0 );
	/* then the number of the direction */
	GW_I32 nDirection = -1; 
	for( GW_U32 i=0; i<3; ++i )
	{
		if( (&Direction)==this->GetOwnedVertex(i) )
			nDirection  = i;
	}
	GW_ASSERT( nDirection>=0 );
	/* now we can compute the direction in which to ask */
	GW_U32 nAbsoluteDirection = 4 - nDirection - nSonNum;
	GW_ASSERT( this->GetVertex(nAbsoluteDirection)!=NULL );
	GW_QuadTreeNode* pNeighbor = this->GetNeighbor( *this->GetVertex(nAbsoluteDirection) );
	if( pNeighbor!=NULL )
	{
		/* as we are not assured that our neighbor use the same naming scheme as us, we must seek for the right child ... arg. */
		for( GW_U32 i=0; i<3; ++i )
		{
			if( pNeighbor->GetVertex(i)==this->GetVertex(nSonNum-1) )
				return pNeighbor->GetChildNode( i+1 );
		}
		GW_ASSERT( GW_False );
	}
	return NULL;
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::SetDataChunk
/**
 *  \param  DataChunk [GW_DataChunk_ABC&] The new data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Set the data chunk used by a transform to store some precomputed values.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTreeNode::SetDataChunk(GW_DataChunk_ABC& DataChunk)
{
	/* delete the previous chunk if needed */
	GW_DELETE( pDataChunk_ );
	pDataChunk_ = &DataChunk;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetCompletionVertex
/**
 *  \param  Vert1 [GW_QuadTreeVertex&] 1st vertex
 *  \param  Vert2 [GW_QuadTreeVertex&] 2nd vertex
 *  \return [GW_QuadTreeVertex*] 3rd vertex
 *  \author Gabriel Peyré
 *  \date   12-24-2002
 * 
 *  Search for the third vertex of a face.
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeVertex* GW_QuadTreeNode::GetCompletionVertex( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 )
{
	for( GW_U32 i=0; i<3; ++i )
	{
		if( this->GetVertex(i)==&Vert1 )
		{
			if( this->GetVertex((i+1)%3)==&Vert2 )
				return this->GetVertex((i+2)%3);
			else if( this->GetVertex((i+2)%3)==&Vert2 )
				return this->GetVertex((i+1)%3);
			else
				return NULL;
		}
	}
	return NULL;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetVertexBetween
/**
 *  \param  Vert1 [GW_QuadTreeVertex&] 1st vertex.
 *  \param  Vert2 [GW_QuadTreeVertex&] 2nd vertex.
 *  \return [GW_QuadTreeVertex*] answer
 *  \author Gabriel Peyré
 *  \date   12-26-2002
 * 
 *  Get a owned vertex that lie between two corner vertex.
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeVertex* GW_QuadTreeNode::GetVertexBetween( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 )
{
	for( GW_U32 i=0; i<3; ++i )
	{
		if( this->GetVertex(i)==&Vert1 )
		{
			if( this->GetVertex((i+1)%3)==&Vert2 )
				return this->GetOwnedVertex((i+2)%3);
			else if( this->GetVertex((i+2)%3)==&Vert2 )
				return this->GetOwnedVertex((i+1)%3);
			else
				return NULL;
		}
	}
	return NULL;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetVertexBetween
/**
 *  \param  Vert1 [GW_QuadTreeVertex&] 1st vertex.
 *  \param  Vert2 [GW_QuadTreeVertex&] 2nd vertex.
 *  \return [GW_I32&] The number of the vertex. <0 if the provided vertex does not belong to the node.
 *  \author Gabriel Peyré
 *  \date   12-26-2002
 * 
 *  Get the number of an owned vertex that lie between two corner vertex.
 */
/*------------------------------------------------------------------------------*/
GW_I32 GW_QuadTreeNode::GetVertexNumberBetween( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 )
{
	for( GW_U32 i=0; i<3; ++i )
	{
		if( this->GetVertex(i)==&Vert1 )
		{
			if( this->GetVertex((i+1)%3)==&Vert2 )
				return (i+2)%3;
			else if( this->GetVertex((i+2)%3)==&Vert2 )
				return (i+1)%3;
			else
				return -1;
		}
	}
	return -1;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetVertexNumber
/**
 *  \param  Vert [GW_QuadTreeVertex&] The vertex
 *  \return [GW_I32] -1 if the vertex is not one of the node.
 *  \author Gabriel Peyré
 *  \date   12-27-2002
 * 
 *  Return the number of a given vertex.
 */
/*------------------------------------------------------------------------------*/
GW_I32 GW_QuadTreeNode::GetVertexNumber( GW_QuadTreeVertex& Vert )
{
	for( GW_U32 i=0; i<3; ++i )
	{
		if( (&Vert)==this->GetVertex(i) )
			return i;
	}
	return -1;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::GetOwnedVertexNumber
/**
 *  \param  Vert [GW_QuadTreeVertex&] The vertex
 *  \return [GW_I32] -1 if the vertex is not one of the node.
 *  \author Gabriel Peyré
 *  \date   12-27-2002
 * 
 *  Return the number of a given owned vertex.
 */
/*------------------------------------------------------------------------------*/
GW_I32 GW_QuadTreeNode::GetOwnedVertexNumber( GW_QuadTreeVertex& Vert )
{
	for( GW_U32 i=0; i<3; ++i )
	{
		if( (&Vert)==this->GetOwnedVertex(i) )
			return i;
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
