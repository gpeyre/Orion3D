/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTree.inl
 *  \brief  Inlined methods for \c FSW_QuadTree
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_QuadTree.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::SetStaticThis
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Setup the static this pointer.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTree::SetStaticThis()
{
	pStaticThis_ = this;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::UnsetStaticThis
/**
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Set the static this pointer to NULL. Should be called once you 
 *  don't use the current \c FSW_QuadTree instance anymore.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTree::UnsetStaticThis()
{
	pStaticThis_ = NULL;
}




/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::StaticThis
/**
 *  \return [static FSW_QuadTree*] A pointer to the current instance of FSW_QuadTree beeing used.
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 * 
 *  Get the static this pointer.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_QuadTree* FSW_QuadTree::StaticThis()
{
	return pStaticThis_;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::GetMaxDepth
/**
 *  \return [FSW_U32] The depth.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Get the depth of the tree.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_U32 FSW_QuadTree::GetDepth()
{
	FSW_ASSERT( NodeMapVector_.size()>0 );
	return (FSW_U32) NodeMapVector_.size() - 1;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::GetBaseMesh
/**
 *  \return [FSW_BaseMesh_ABC&] The base mesh.
 *  \author Gabriel Peyré
 *  \date   11-29-2002
 * 
 *  Get the base mesh used for subdivision.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_BaseMesh_ABC& FSW_QuadTree::GetBaseMesh()
{
	FSW_ASSERT( pBaseMesh_!=NULL );
	return *pBaseMesh_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::GetBaseNodeVector
/**
 *  \return [T_QuadTreeNodeVector&] The vector.
 *  \author Gabriel Peyré
 *  \date   11-30-2002
 * 
 *  Get the list of all base node (each are a root of a sub tree).
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
T_QuadTreeNodeVector& FSW_QuadTree::GetBaseNodeVector()
{
	return BaseNodeVector_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTree::GetBaseVertexVector
/**
 *  \return [T_QuadTreeVertexVector&] The vector.
 *  \author Gabriel Peyré
 *  \date   11-30-2002
 * 
 *  Get the list of all base vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
T_QuadTreeVertexVector& FSW_QuadTree::GetBaseVertexVector()
{
	return BaseVertexVector_;
}



FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
