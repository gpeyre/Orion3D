
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_NodeMap.h
 *  \brief  Definition of class \c FSW_NodeMap
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_NODEMAP_H_
#define _FSW_NODEMAP_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeNode.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** \name a map of FSW_QuadTreeNode */
/*------------------------------------------------------------------------------*/
//@{
typedef map<FSW_U32, class FSW_QuadTreeNode*> T_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::iterator IT_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::reverse_iterator RIT_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::const_iterator CIT_QuadTreeNodeMap;
typedef T_QuadTreeNodeMap::const_reverse_iterator CRIT_QuadTreeNodeMap;
//@}


/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_NodeMap
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

class FSW_NodeMap
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_NodeMap();
    virtual ~FSW_NodeMap();
    //@}

	void Add( FSW_QuadTreeNode& Node );
	void Remove( FSW_QuadTreeNode& Node );

	T_QuadTreeNodeMap& GetMap();

private:

	T_QuadTreeNodeMap Map_;
	FSW_U32 nNextId_;

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_NodeMap.inl"
#endif


#endif // _FSW_NODEMAP_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
