/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTree.cpp
 *  \brief  Definition of class \c GW_QuadTree
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_QuadTree.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_QuadTree.h"
#include "GW_WaveletTransform_ABC.h"
#include "GW_BaseMesh_ABC.h"

#ifndef GW_USE_INLINE
    #include "GW_QuadTree.inl"
#endif

using namespace GW;

GW_QuadTree* GW_QuadTree::pStaticThis_ = NULL;

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_QuadTree::GW_QuadTree( GW_BaseMesh_ABC& BaseMesh )
:	GW_QuadTreeNode(),
	pBaseMesh_				( &BaseMesh )
{
	/* Important : we *must* work in double precision in order to perform accurate scaling */
	GW_ASSERT( sizeof(GW_Float)==8 );

	/* first build the base node/vertex */
	BaseMesh.BuildBaseMesh( BaseNodeVector_, BaseVertexVector_ );

	/* check for the map of level 0 (in fact, this will create a new one) */
	GW_NodeMap& NodeMap = this->GetNodeMap(0);

	/* tell to the node we are their father ... so cute ... */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
		pNode->SetFather( *this );
		pNode->SetDepth( 0 );
		/* add the nodes to the map of 0th level */
		NodeMap.Add( *pNode );
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_QuadTree::~GW_QuadTree()
{
	this->ClearAllData();
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::ClearAllData
/**
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Delete each node and each vertex in the tree, leaving it empty.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::ClearAllData()
{
	/* During deletion, node will need the quadtree to remove their son from nodemap, so set a global pointer */
	this->SetStaticThis();

	/* delete the nodes *after*, but don't forget to remove them from the node map */
	GW_ASSERT( this->NodeMapExist( 0 ) );
	GW_NodeMap& NodeMap = this->GetNodeMap( 0 );
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
		NodeMap.Remove( *pNode );
		GW_DELETE( pNode );
		*it = NULL;	// this is important, because we will be asked for neighbor information later during destruction.
	}
	/* delete the vertice */
	for( IT_QuadTreeVertexVector it=BaseVertexVector_.begin(); it!=BaseVertexVector_.end(); ++it )
	{
		GW_QuadTreeVertex* pVert = *it;
		GW_ASSERT( pVert!=NULL );
		GW_DELETE( pVert );
		*it = NULL;
	}
	/* for safty : clear the list */
	BaseVertexVector_.clear();
	BaseNodeVector_.clear();

	/* remove empty nodemap at the deepest levels. *Very* important. */
	this->CleanNodeMap();
	GW_ASSERT( NodeMapVector_.size()==0 );

//	this->UnsetStaticThis();
}



/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::BuildTree
/**
 *  \param  Func [GW_TreeFunction_ABC&] The function that give the value of the tree at for a given face / vertex
 *  \param  nMaxLevel [GW_U32] Max subdivision level. Should be > 0.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Subdivise the sphere up to a given resolution.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::BuildTree(const GW_TreeFunction_ABC& Func, GW_U32 nMaxLevel)
{
	this->SetStaticThis();
	
	/* first build the tree by recursion */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
		/* recurse */
		pNode->BuildTree(*pBaseMesh_, Func, 1, nMaxLevel);
	}

	/* assign value to the top vertice */
	for( IT_QuadTreeVertexVector it=BaseVertexVector_.begin(); it!=BaseVertexVector_.end(); ++it )
	{
		GW_QuadTreeVertex* pVert = *it;
		GW_ASSERT( pVert!=NULL );
		GW_Float rU, rV;
		pBaseMesh_->ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
		pVert->SetValue( Func.GetValue( rU, rV ) );
	}
	
	/* remove empty nodemap at the deepest levels. *Very* important. */
	this->CleanNodeMap();

	GW_U32 nNum = 0;
	/* positionate each node (ie. launch the Positionate function on each node with correct parameters) */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
		char str[100];
		sprintf( str, "Building root node number %d.", nNum);
		GW_OutputComment( str );
		this->Positionate( *pNode, *pNode, Func, GW_Vector3D(1,0,0), GW_Vector3D(0,1,0), GW_Vector3D(0,0,1) );
		nNum++;
	}

#if 0
	/* Now set position and value of all vertex.
	   There is no need to iterate on the last level, since there is no owned vertex for this one. */
	for( GW_U32 nCurDepth=0; nCurDepth<this->GetDepth(); ++nCurDepth )
	{
		GW_ASSERT( this->NodeMapExist( nCurDepth ) );
		GW_NodeMap& NodeMapVector = this->GetNodeMap( nCurDepth );
		T_QuadTreeNodeMap& NodeMap = NodeMapVector.GetMap();
		/* recurse on each node */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=NodeMap.begin(); NodeTreeMapIT!=NodeMap.end(); ++NodeTreeMapIT )
		{
			/* get the node */
			GW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			GW_ASSERT( pNode!=NULL );
			pBaseMesh_->Positionate( *pNode );
			/* compute the value at each vertex and barycenter */
			this->AssignValue( Func, *pNode );
		}
	}
#endif

	this->UnsetStaticThis();
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::Positionate
/**
 *  \param  CurNode [GW_QuadTreeNode&] DESCRIPTION
 *  \param  RootNode [GW_QuadTreeNode&] DESCRIPTION
 *  \param  v0 [GW_Vector3D] DESCRIPTION
 *  \param  v1 [GW_Vector3D] DESCRIPTION
 *  \param  v2 [GW_Vector3D] DESCRIPTION
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 * 
 *  ENTER YOUR DESCRIPTION HERE
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, const GW_TreeFunction_ABC& Func, 
							   GW_Vector3D v0, GW_Vector3D v1, GW_Vector3D v2 )
{
	GW_ASSERT( pBaseMesh_!=NULL );
	/* ask to the base mesh to positionate the node */
	pBaseMesh_->Positionate( CurNode, RootNode, v0, v1, v2 );
	/* compute the value at each vertex and barycenter */
	if( CurNode.GetOwnedVertex(0)!=NULL )
		this->AssignValue( Func, CurNode );
	/* recurse on each child */
	if( CurNode.GetChildNode(0)!=NULL )	// central vertex
		this->Positionate( *CurNode.GetChildNode(0), RootNode, Func, (v1+v2)/2, (v0+v2)/2, (v0+v1)/2 );
	if( CurNode.GetChildNode(1)!=NULL )
		this->Positionate( *CurNode.GetChildNode(1), RootNode, Func, v0, (v0+v2)/2, (v0+v1)/2 );
	if( CurNode.GetChildNode(2)!=NULL )
		this->Positionate( *CurNode.GetChildNode(2), RootNode, Func, (v1+v2)/2, v1, (v0+v1)/2 );
	if( CurNode.GetChildNode(3)!=NULL )
		this->Positionate( *CurNode.GetChildNode(3), RootNode, Func, (v1+v2)/2, (v0+v2)/2, v2 );

}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::AssignValue
/**
 *  \param  Func [GW_TreeFunction_ABC&] The function to compute values.
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Helper method : compute the value of each vertex and of the face.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::AssignValue( const GW_TreeFunction_ABC& Func, GW_QuadTreeNode& CurNode )
{
	GW_Float rU, rV;
	/* check each vertex */
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
		GW_ASSERT( pVert!=NULL );
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			/* compute coordinate */
			pBaseMesh_->ConvertToLocalFrame( pVert->GetPosition(), rU, rV );
			pVert->SetValue( Func.GetValue( rU, rV ) );
		}
	}
    GW_Vector3D Barycenter;
	/* compute the barycenter for face value assignement */
	for( GW_U32 i=0; i<3; ++i )
	{
		GW_QuadTreeVertex* pVert = CurNode.GetVertex( i );
		GW_ASSERT( pVert!=NULL );
		Barycenter += pVert->GetPosition();
	}
	Barycenter /= 3;
	/* set the value at the center */
	pBaseMesh_->ConvertToLocalFrame( Barycenter, rU, rV );
	CurNode.SetValue( Func.GetValue( rU, rV ) );
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::GetRelativeSon
/**
 *  \param  pSon [GW_QuadTreeNode*] The son who wants to know about its neighbor.
 *  \param  nDirection [GW_U32] The direction of the search, relative to the son orientation, not our orientation.
 *  \return [GW_QuadTreeNode*] The searched neighbor.
 *  \author Gabriel Peyré
 *  \date   10-30-2002
 * 
 *  This is a tricky function, which normaly is only used by the 8 root node 
 *	to search for their neighbor.
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeNode* GW_QuadTree::GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction)
{
	GW_ASSERT( pBaseMesh_!=NULL );
	return pBaseMesh_->GetRelativeSon(Son, Direction);
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::ForwardTransform
/**
 *  \param  WaveletTransform [GW_WaveletTransform_ABC&] Function used for the update and predict stages.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform recursivly the transformation.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::ForwardTransform( GW_WaveletTransform_ABC& WaveletTransform, GW_U32 nStartLevel )
{
	/* first check if we need to update the value of the various data chunk */
	WaveletTransform.UpdateDataChunk( NodeMapVector_ );

	/* from just before leaf to root */
	GW_U32 nReverseLevel = 1;
	GW_I32 nLevel = this->GetDepth()-1;
	RIT_NodeMapVector it = NodeMapVector_.rbegin();
	it++;
	while( it != NodeMapVector_.rend() && (nLevel>=(GW_I32)nStartLevel) )
	{
		GW_NodeMap* pMap = *it;
		if( pMap!=NULL )
			WaveletTransform.ForwardTransform( *pMap, nReverseLevel );
		nReverseLevel++;
		nLevel--;
		it++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeNode::BackwardTransform
/**
 *  \param  WaveletTransform [GW_WaveletTransform_ABC&] Function used for the update and predict stages.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform recursivly the transformation.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::BackwardTransform( GW_WaveletTransform_ABC& WaveletTransform, GW_U32 nStartLevel )
{
	/* first check if we need to update the value of the various data chunk */
	WaveletTransform.UpdateDataChunk( NodeMapVector_ );
	
	/* from root to leaf */
	GW_U32 nReverseLevel = this->GetDepth();
	IT_NodeMapVector it = NodeMapVector_.begin();
	for( GW_U32 i =0; i<nStartLevel; ++i )		// skip the levels the user doesn't want to transform
	{
		it++;
		nReverseLevel--;
		if( it == NodeMapVector_.end() )
			return;
	}
	while( it != NodeMapVector_.end() )
	{
		GW_NodeMap* pMap = *it;
		if( pMap!=NULL )
			WaveletTransform.BackwardTransform( *pMap, nReverseLevel );
		nReverseLevel--;
		it++;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::GetNodeMap
/**
 *  \param  CurLevel [GW_U32] A level in the tree.
 *  \return [GW_NodeMap&] The node map.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Get the map corresponding to the given level.
 *	If the map doesn't exist, create it.
 */
/*------------------------------------------------------------------------------*/
GW_NodeMap& GW_QuadTree::GetNodeMap(GW_I32 CurLevel)
{
	GW_I32 nLastLevel = NodeMapVector_.size()-1;
	if( CurLevel>nLastLevel )
	{
		/* the map isn't large enough */
		for( GW_I32 i=nLastLevel; i<CurLevel; i++ )
			NodeMapVector_.push_back(NULL);
	}
	GW_NodeMap* pNodeMap = NodeMapVector_[CurLevel];
	if( pNodeMap==NULL )
	{
		pNodeMap = new GW_NodeMap;
		NodeMapVector_[CurLevel] = pNodeMap;
	}
	return *pNodeMap;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::NodeMapExist
/**
 *  \param  CurLevel [GW_U32] Level of the map.
 *  \return [GW_Bool] Does it exists ?
 *  \author Gabriel Peyré
 *  \date   11-13-2002
 * 
 *  Just to check we have already created a map for the given level.
 *	Usefull because a call to GetNodeMap would create a new map if it doesn't exist.
 */
/*------------------------------------------------------------------------------*/
GW_Bool GW_QuadTree::NodeMapExist(GW_U32 CurLevel)
{
	return (CurLevel+1 <= NodeMapVector_.size());
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::CleanNodeMap
/**
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Delete the map on the deepest levels that are empty.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::CleanNodeMap()
{
	GW_NodeMap* pMap = NodeMapVector_.back();
	while( pMap!=NULL && pMap->GetMap().empty() )
	{
		GW_DELETE( pMap );
		NodeMapVector_.pop_back();
		if( !NodeMapVector_.empty() )
			pMap = NodeMapVector_.back();
		else
			pMap=NULL;
	}	
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::SetBaseMesh
/**
 *  \param  BaseMesh [GW_BaseMesh_ABC&] The new base mesh.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  This set a new base mesh. This clean the tree, and rebuild base 
 *  lists.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTree::SetBaseMesh(GW_BaseMesh_ABC& BaseMesh)
{
	/* delete any previous data */
	this->ClearAllData();
	pBaseMesh_ = &BaseMesh;

	/* first build the base node/vertex */
	pBaseMesh_->BuildBaseMesh( BaseNodeVector_, BaseVertexVector_ );

	/* check for the map of level 0 (in fact, this will create a new one) */
	GW_NodeMap& NodeMap = this->GetNodeMap(0);

	/* tell to the node we are their father ... so cute ... */
	for( IT_QuadTreeNodeVector it=BaseNodeVector_.begin(); it!=BaseNodeVector_.end(); ++it )
	{
		GW_QuadTreeNode* pNode = *it;
		GW_ASSERT( pNode!=NULL );
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
