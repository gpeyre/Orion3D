
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_NodeMap.h
 *  \brief  Definition of class \c GW_NodeMap
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_NODEMAP_H_
#define _GW_NODEMAP_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeNode.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** \name a map of GW_QuadTreeNode */
/*------------------------------------------------------------------------------*/
//@{
typedef std::map<GW_U32, class GW_QuadTreeNode*> T_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::iterator IT_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::reverse_iterator RIT_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::const_iterator CIT_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::const_reverse_iterator CRIT_QuadTreeNodeMap;
//@}


/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_NodeMap
 *  \brief  A associative map to store all quadtree node of a given level.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 *
 *  There is a map for each level in the quadtree.
 *	When we create a new node in the tree, we should add it to the correct
 *	map. The map should return a unique id for the node, so that we
 *	can retrieve this element from the map later.
 */ 
/*------------------------------------------------------------------------------*/

class GW_NodeMap
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_NodeMap();
    virtual ~GW_NodeMap();
    //@}

	void Add( GW_QuadTreeNode& Node );
	void Remove( GW_QuadTreeNode& Node );

	T_QuadTreeNodeMap& GetMap();

private:

	T_QuadTreeNodeMap Map_;
	GW_U32 nNextId_;

};



GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_NodeMap.inl"
#endif


#endif // _GW_NODEMAP_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
