/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_NodeMap.cpp
 *  \brief  Definition of class \c GW_NodeMap
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_NodeMap.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_NodeMap.h"

#ifndef GW_USE_INLINE
    #include "GW_NodeMap.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_NodeMap::Add
/**
 *  \param  Node [GW_QuadTreeNode&] The node.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Add a node to the map. Assign to the node its new Id.
 */
/*------------------------------------------------------------------------------*/
void GW_NodeMap::Add( GW_QuadTreeNode& Node )
{
	Map_[ nNextId_ ] = &Node;
	Node.SetId( nNextId_ );
	nNextId_++;
}

/*------------------------------------------------------------------------------*/
// Name : GW_NodeMap::Remove
/**
 *  \param  Node [GW_QuadTreeNode&] The node to remove.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Remove an element from the map.
 */
/*------------------------------------------------------------------------------*/
void GW_NodeMap::Remove( GW_QuadTreeNode& Node )
{
	IT_QuadTreeNodeMap it = Map_.find( Node.GetId() );
	GW_ASSERT( it!=Map_.end() );
	Map_.erase( it );
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
