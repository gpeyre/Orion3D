/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_NodeMap.cpp
 *  \brief  Definition of class \c FSW_NodeMap
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_NodeMap.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_NodeMap.h"

#ifndef FSW_USE_INLINE
    #include "FSW_NodeMap.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_NodeMap::Add
/**
 *  \param  Node [FSW_QuadTreeNode&] The node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Add a node to the map. Assign to the node its new Id.
 */
/*------------------------------------------------------------------------------*/
void FSW_NodeMap::Add( FSW_QuadTreeNode& Node )
{
	Map_[ nNextId_ ] = &Node;
	Node.SetId( nNextId_ );
	nNextId_++;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_NodeMap::Remove
/**
 *  \param  Node [FSW_QuadTreeNode&] The node to remove.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Remove an element from the map.
 */
/*------------------------------------------------------------------------------*/
void FSW_NodeMap::Remove( FSW_QuadTreeNode& Node )
{
	IT_QuadTreeNodeMap it = Map_.find( Node.GetId() );
	FSW_ASSERT( it!=Map_.end() );
	Map_.erase( it );
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
