/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_WaveletTransform_ABC.cpp
 *  \brief  Definition of class \c GW_WaveletTransform_ABC
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_WaveletTransform_ABC.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_WaveletTransform_ABC.h"
#include "GW_NodeMap.h"

#ifndef GW_USE_INLINE
    #include "GW_WaveletTransform_ABC.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_WaveletTransform_ABC constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_WaveletTransform_ABC::GW_WaveletTransform_ABC()
:	bUseUpdate_( GW_True )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : GW_WaveletTransform_ABC::ForwardTransform
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_WaveletTransform_ABC::ForwardTransform( GW_NodeMap& NodeMap, GW_U32 nReverseLevel )
{
	T_QuadTreeNodeMap& Map = NodeMap.GetMap();

	/* predict stage *************************************/
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		GW_QuadTreeNode* pNode = it->second;
		GW_ASSERT( pNode!=NULL );
		GW_ASSERT( pNode->GetOwnedVertex(0)!=NULL );	// this function shouldn't be called on leaf node.
		this->ForwardPredict( *pNode, nReverseLevel );
	}
	/* update stage *************************************/
	if( bUseUpdate_ )
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		GW_QuadTreeNode* pNode = it->second;;
		GW_ASSERT( pNode!=NULL );
		GW_ASSERT( pNode->GetOwnedVertex(0)!=NULL );	// this function shouldn't be called on leaf node.
		this->ForwardUpdate( *pNode, nReverseLevel );
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_WaveletTransform_ABC::BackwardTransform
/**
 *  \param  CurNode [GW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void GW_WaveletTransform_ABC::BackwardTransform( GW_NodeMap& NodeMap, GW_U32 nReverseLevel )
{
	T_QuadTreeNodeMap& Map = NodeMap.GetMap();

	if( bUseUpdate_ )
	/* update stage *************************************/
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		GW_QuadTreeNode* pNode = it->second;;
		GW_ASSERT( pNode!=NULL );
		if( pNode->GetOwnedVertex(0)!=NULL )
			this->BackwardUpdate( *pNode, nReverseLevel );
	}
	/* predict stage *************************************/
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		GW_QuadTreeNode* pNode = it->second;;
		GW_ASSERT( pNode!=NULL );
		if( pNode->GetOwnedVertex(0)!=NULL )
			this->BackwardPredict( *pNode, nReverseLevel );
	}
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////