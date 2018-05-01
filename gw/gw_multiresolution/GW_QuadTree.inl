/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTree.inl
 *  \brief  Inlined methods for \c GW_QuadTree
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_QuadTree.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::SetStaticThis
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Setup the static this pointer.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTree::SetStaticThis()
{
	pStaticThis_ = this;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::UnsetStaticThis
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Set the static this pointer to NULL. Should be called once you 
 *  don't use the current \c GW_QuadTree instance anymore.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTree::UnsetStaticThis()
{
	pStaticThis_ = NULL;
}




/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::StaticThis
/**
 *  \return [static GW_QuadTree*] A pointer to the current instance of GW_QuadTree beeing used.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Get the static this pointer.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_QuadTree* GW_QuadTree::StaticThis()
{
	return pStaticThis_;
}


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::GetMaxDepth
/**
 *  \return [GW_U32] The depth.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Get the depth of the tree.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_U32 GW_QuadTree::GetDepth()
{
	GW_ASSERT( NodeMapVector_.size()>0 );
	return (GW_U32) NodeMapVector_.size() - 1;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::GetBaseMesh
/**
 *  \return [GW_BaseMesh_ABC&] The base mesh.
 *  \author Gabriel Peyré
 *  \date   11-29-2002
 * 
 *  Get the base mesh used for subdivision.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_BaseMesh_ABC& GW_QuadTree::GetBaseMesh()
{
	GW_ASSERT( pBaseMesh_!=NULL );
	return *pBaseMesh_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::GetBaseNodeVector
/**
 *  \return [T_QuadTreeNodeVector&] The vector.
 *  \author Gabriel Peyré
 *  \date   11-30-2002
 * 
 *  Get the list of all base node (each are a root of a sub tree).
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
T_QuadTreeNodeVector& GW_QuadTree::GetBaseNodeVector()
{
	return BaseNodeVector_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTree::GetBaseVertexVector
/**
 *  \return [T_QuadTreeVertexVector&] The vector.
 *  \author Gabriel Peyré
 *  \date   11-30-2002
 * 
 *  Get the list of all base vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
T_QuadTreeVertexVector& GW_QuadTree::GetBaseVertexVector()
{
	return BaseVertexVector_;
}



GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
