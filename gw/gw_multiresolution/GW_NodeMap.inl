/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_NodeMap.inl
 *  \brief  Inlined methods for \c GW_NodeMap
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_NodeMap.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_NodeMap constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_NodeMap::GW_NodeMap()
:	nNextId_( 0 )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_NodeMap destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_NodeMap::~GW_NodeMap()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : GW_NodeMap::GetMap
/**
 *  \return [T_QuadTreeNodeMap&] The map.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Returns the map containing the different nodes.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
T_QuadTreeNodeMap& GW_NodeMap::GetMap()
{
	return Map_;
}


GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
