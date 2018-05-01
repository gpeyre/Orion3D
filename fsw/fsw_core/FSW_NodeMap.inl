/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_NodeMap.inl
 *  \brief  Inlined methods for \c FSW_NodeMap
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_NodeMap.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_NodeMap constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_NodeMap::FSW_NodeMap()
:	nNextId_( 0 )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_NodeMap destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_NodeMap::~FSW_NodeMap()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : FSW_NodeMap::GetMap
/**
 *  \return [T_QuadTreeNodeMap&] The map.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Returns the map containing the different nodes.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
T_QuadTreeNodeMap& FSW_NodeMap::GetMap()
{
	return Map_;
}


FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
