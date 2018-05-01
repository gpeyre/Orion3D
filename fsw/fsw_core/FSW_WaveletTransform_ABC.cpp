/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_WaveletTransform_ABC.cpp
 *  \brief  Definition of class \c FSW_WaveletTransform_ABC
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_WaveletTransform_ABC.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_WaveletTransform_ABC.h"
#include "FSW_NodeMap.h"

#ifndef FSW_USE_INLINE
    #include "FSW_WaveletTransform_ABC.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_WaveletTransform_ABC constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_WaveletTransform_ABC::FSW_WaveletTransform_ABC()
:	bUseUpdate_( FSW_True )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : FSW_WaveletTransform_ABC::ForwardTransform
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_WaveletTransform_ABC::ForwardTransform( FSW_NodeMap& NodeMap, FSW_U32 nReverseLevel )
{
	T_QuadTreeNodeMap& Map = NodeMap.GetMap();

	/* predict stage *************************************/
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		FSW_QuadTreeNode* pNode = it->second;
		FSW_ASSERT( pNode!=NULL );
		FSW_ASSERT( pNode->GetOwnedVertex(0)!=NULL );	// this function shouldn't be called on leaf node.
		this->ForwardPredict( *pNode, nReverseLevel );
	}
	/* update stage *************************************/
	if( bUseUpdate_ )
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		FSW_QuadTreeNode* pNode = it->second;;
		FSW_ASSERT( pNode!=NULL );
		FSW_ASSERT( pNode->GetOwnedVertex(0)!=NULL );	// this function shouldn't be called on leaf node.
		this->ForwardUpdate( *pNode, nReverseLevel );
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_WaveletTransform_ABC::BackwardTransform
/**
 *  \param  CurNode [FSW_QuadTreeNode&] The current node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Perform a forward step.
 */
/*------------------------------------------------------------------------------*/
void FSW_WaveletTransform_ABC::BackwardTransform( FSW_NodeMap& NodeMap, FSW_U32 nReverseLevel )
{
	T_QuadTreeNodeMap& Map = NodeMap.GetMap();

	if( bUseUpdate_ )
	/* update stage *************************************/
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		FSW_QuadTreeNode* pNode = it->second;;
		FSW_ASSERT( pNode!=NULL );
		if( pNode->GetOwnedVertex(0)!=NULL )
			this->BackwardUpdate( *pNode, nReverseLevel );
	}
	/* predict stage *************************************/
	for( IT_QuadTreeNodeMap it=Map.begin(); it!=Map.end(); ++it )
	{
		/* get the node */
		FSW_QuadTreeNode* pNode = it->second;;
		FSW_ASSERT( pNode!=NULL );
		if( pNode->GetOwnedVertex(0)!=NULL )
			this->BackwardPredict( *pNode, nReverseLevel );
	}
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////