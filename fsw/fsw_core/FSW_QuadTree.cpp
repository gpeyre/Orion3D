/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTree.cpp
 *  \brief  Definition of class \c FSW_QuadTree
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_QuadTree.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_QuadTree.h"
#include "FSW_WaveletTransform_ABC.h"
#include "FSW_BaseMesh_ABC.h"

#ifndef FSW_USE_INLINE
    #include "FSW_QuadTree.inl"
#endif

using namespace FSW;

FSW_QuadTree* FSW_QuadTree::pStaticThis_ = NULL;

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTree::FSW_QuadTree( FSW_BaseMesh_ABC& BaseMesh )
:	FSW_QuadTreeNode(),
	pBaseMesh_				( &BaseMesh )
{
	/* Important : we *must* work in double precision in order to perform accurate scaling */
	FSW_ASSERT( sizeof(FSW_Float)==8 );

	/* first build the base node/vertex */
	BaseMesh.BuildBaseMesh( BaseNodeVector_, BaseVertexVector_ );

	/* check for the map of level 0 (in fact, this will create a new one) */
	FSW_NodeMap& NodeMap = this->GetNodeMap(0);

	/* tell to the node we are their father ... so cute ... */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		pNode->SetFather( *this );
		pNode->SetDepth( 0 );
		/* add the nodes to the map of 0th level */
		NodeMap.Add( *pNode );
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTree::~FSW_QuadTree()
{
	this->ClearAllData();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::ClearAllData
/**
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Delete each node and each vertex in the tree, leaving it empty.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::ClearAllData()
{
	/* During deletion, node will need the quadtree to remove their son from nodemap, so set a global pointer */
	this->SetStaticThis();

	/* delete the nodes *after*, but don't forget to remove them from the node map */
	FSW_ASSERT( this->NodeMapExist( 0 ) );
	FSW_NodeMap& NodeMap = this->GetNodeMap( 0 );
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		NodeMap.Remove( *pNode );
		FSW_DELETE( pNode );
		*it = NULL;	// this is important, because we will be asked for neighbor information later during destruction.
	}
	/* delete the vertice */
	for( IT_QuadTreeVertexVector it=BaseVertexVector_.begin(); it!=BaseVertexVector_.end(); ++it )
	{
		FSW_QuadTreeVertex* pVert = *it;
		FSW_ASSERT( pVert!=NULL );
		FSW_DELETE( pVert );
		*it = NULL;
	}
	/* for safty : clear the list */
	BaseVertexVector_.clear();
	BaseNodeVector_.clear();

	/* remove empty nodemap at the deepest levels. *Very* important. */
	this->CleanNodeMap();
	FSW_ASSERT( NodeMapVector_.size()==0 );

//	this->UnsetStaticThis();
}



/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::BuildTree
/**
 *  \param  Func [FSW_TreeFunction_ABC&] The function that give the value of the tree at for a given face / vertex
 *  \param  nMaxLevel [FSW_U32] Max subdivision level. Should be > 0.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Subdivise the sphere up to a given resolution.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::BuildTree(const FSW_TreeFunction_ABC& Func, FSW_U32 nMaxLevel)
{
	this->SetStaticThis();
	
	/* first build the tree by recursion */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		FSW_ASSERT( pBaseMesh_!=NULL );
		/* recurse */
		pNode->BuildTree(*pBaseMesh_, Func, 1, nMaxLevel);
	}

	/* assign value to the top vertice */
	for( IT_QuadTreeVertexVector it=BaseVertexVector_.begin(); it!=BaseVertexVector_.end(); ++it )
	{
		FSW_QuadTreeVertex* pVert = *it;
		FSW_ASSERT( pVert!=NULL );
		FSW_Float rU, rV;
		pBaseMesh_->ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
		pVert->SetValue( Func.GetValue( rU, rV ) );
	}
	
	/* remove empty nodemap at the deepest levels. *Very* important. */
	this->CleanNodeMap();

	/* Now set position and value of all vertex.
	   There is no need to iterate on the last level, since there is no owned vertex for this one. */
	for( FSW_U32 nCurDepth=0; nCurDepth<this->GetDepth(); ++nCurDepth )
	{
		FSW_ASSERT( this->NodeMapExist( nCurDepth ) );
		FSW_NodeMap& NodeMapVector = this->GetNodeMap( nCurDepth );
		T_QuadTreeNodeMap& NodeMap = NodeMapVector.GetMap();
		/* recurse on each node */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=NodeMap.begin(); NodeTreeMapIT!=NodeMap.end(); ++NodeTreeMapIT )
		{
			/* get the node */
			FSW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			FSW_ASSERT( pNode!=NULL );
			pBaseMesh_->Positionate( *pNode );
			/* compute the value at each vertex and barycenter */
			this->AssignValue( Func, *pNode );
		}
	}

	this->UnsetStaticThis();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::AssignValue
/**
 *  \param  Func [FSW_TreeFunction_ABC&] The function to compute values.
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Helper method : compute the value of each vertex and of the face.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::AssignValue( const FSW_TreeFunction_ABC& Func, FSW_QuadTreeNode& CurNode )
{
	FSW_Float rU, rV;
	/* check each vertex */
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
		FSW_ASSERT( pVert!=NULL );
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			/* compute coordinate */
			pBaseMesh_->ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
			pVert->SetValue( Func.GetValue( rU, rV ) );
		}
	}
    FSW_Vector3D Barycenter;
	/* compute the barycenter for face value assignement */
	for( FSW_U32 i=0; i<3; ++i )
	{
		FSW_QuadTreeVertex* pVert = CurNode.GetVertex( i );
		FSW_ASSERT( pVert!=NULL );
		Barycenter += pVert->GetPosition();
	}
	Barycenter /= 3;
	/* set the value at the center */
	pBaseMesh_->ConvertToLocalFrame( Barycenter, rU, rV );
	CurNode.SetValue( Func.GetValue( rU, rV ) );
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::GetRelativeSon
/**
 *  \param  pSon [FSW_QuadTreeNode*] The son who wants to know about its neighbor.
 *  \param  nDirection [FSW_U32] The direction of the search, relative to the son orientation, not our orientation.
 *  \return [FSW_QuadTreeNode*] The searched neighbor.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  This is a tricky function, which normaly is only used by the 8 root node 
 *	to search for their neighbor.
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTreeNode* FSW_QuadTree::GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction)
{
	FSW_ASSERT( pBaseMesh_!=NULL );
	return pBaseMesh_->GetRelativeSon(Son, Direction);
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::ForwardTransform
/**
 *  \param  WaveletTransform [FSW_WaveletTransform_ABC&] Function used for the update and predict stages.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform recursivly the transformation.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::ForwardTransform( FSW_WaveletTransform_ABC& WaveletTransform, FSW_U32 nStartLevel )
{
	/* first check if we need to update the value of the various data chunk */
	WaveletTransform.UpdateDataChunk( NodeMapVector_ );

	/* from just before leaf to root */
	FSW_U32 nReverseLevel = 1;
	FSW_I32 nLevel = this->GetDepth()-1;
	RIT_NodeMapVector it = NodeMapVector_.rbegin();
	it++;
	while( it != NodeMapVector_.rend() && (nLevel>=(FSW_I32)nStartLevel) )
	{
		FSW_NodeMap* pMap = *it;
		if( pMap!=NULL )
			WaveletTransform.ForwardTransform( *pMap, nReverseLevel );
		nReverseLevel++;
		nLevel--;
		it++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeNode::BackwardTransform
/**
 *  \param  WaveletTransform [FSW_WaveletTransform_ABC&] Function used for the update and predict stages.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform recursivly the transformation.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::BackwardTransform( FSW_WaveletTransform_ABC& WaveletTransform, FSW_U32 nStartLevel )
{
	/* first check if we need to update the value of the various data chunk */
	WaveletTransform.UpdateDataChunk( NodeMapVector_ );
	
	/* from root to leaf */
	FSW_U32 nReverseLevel = this->GetDepth();
	IT_NodeMapVector it = NodeMapVector_.begin();
	for( FSW_U32 i =0; i<nStartLevel; ++i )		// skip the levels the user doesn't want to transform
	{
		it++;
		nReverseLevel--;
		if( it == NodeMapVector_.end() )
			return;
	}
	while( it != NodeMapVector_.end() )
	{
		FSW_NodeMap* pMap = *it;
		if( pMap!=NULL )
			WaveletTransform.BackwardTransform( *pMap, nReverseLevel );
		nReverseLevel--;
		it++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::GetNodeMap
/**
 *  \param  CurLevel [FSW_U32] A level in the tree.
 *  \return [FSW_NodeMap&] The node map.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Get the map corresponding to the given level.
 *	If the map doesn't exist, create it.
 */
/*------------------------------------------------------------------------------*/
FSW_NodeMap& FSW_QuadTree::GetNodeMap(FSW_I32 CurLevel)
{
	FSW_I32 nLastLevel = NodeMapVector_.size()-1;
	if( CurLevel>nLastLevel )
	{
		/* the map isn't large enough */
		for( FSW_I32 i=nLastLevel; i<CurLevel; i++ )
			NodeMapVector_.push_back(NULL);
	}
	FSW_NodeMap* pNodeMap = NodeMapVector_[CurLevel];
	if( pNodeMap==NULL )
	{
		pNodeMap = new FSW_NodeMap;
		NodeMapVector_[CurLevel] = pNodeMap;
	}
	return *pNodeMap;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::NodeMapExist
/**
 *  \param  CurLevel [FSW_U32] Level of the map.
 *  \return [FSW_Bool] Does it exists ?
 *  \author Gabriel Peyré
 *  \date   11-13-2002
 * 
 *  Just to check we have already created a map for the given level.
 *	Usefull because a call to GetNodeMap would create a new map if it doesn't exist.
 */
/*------------------------------------------------------------------------------*/
FSW_Bool FSW_QuadTree::NodeMapExist(FSW_U32 CurLevel)
{
	return (CurLevel+1 <= NodeMapVector_.size());
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::CleanNodeMap
/**
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Delete the map on the deepest levels that are empty.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::CleanNodeMap()
{
	FSW_NodeMap* pMap = NodeMapVector_.back();
	while( pMap!=NULL && pMap->GetMap().empty() )
	{
		FSW_DELETE( pMap );
		NodeMapVector_.pop_back();
		if( !NodeMapVector_.empty() )
			pMap = NodeMapVector_.back();
		else
			pMap=NULL;
	}	
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::SetBaseMesh
/**
 *  \param  BaseMesh [FSW_BaseMesh_ABC&] The new base mesh.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  This set a new base mesh. This clean the tree, and rebuild base 
 *  lists.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTree::SetBaseMesh(FSW_BaseMesh_ABC& BaseMesh)
{
	/* delete any previous data */
	this->ClearAllData();
	pBaseMesh_ = &BaseMesh;

	/* first build the base node/vertex */
	pBaseMesh_->BuildBaseMesh( BaseNodeVector_, BaseVertexVector_ );

	/* check for the map of level 0 (in fact, this will create a new one) */
	FSW_NodeMap& NodeMap = this->GetNodeMap(0);

	/* tell to the node we are their father ... so cute ... */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		pNode->SetFather( *this );
		pNode->SetDepth( 0 );
		/* add the nodes to the map of 0th level */
		NodeMap.Add( *pNode );
	}		
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
