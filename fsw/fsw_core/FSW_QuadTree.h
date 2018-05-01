
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTree.h
 *  \brief  Definition of class \c FSW_QuadTree
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_QUADTREE_H_
#define _FSW_QUADTREE_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeNode.h"
#include "FSW_NodeMap.h"
#include "FSW_QuadtreeNode.h"

FSW_BEGIN_NAMESPACE


class FSW_WaveletTransform_ABC; 
class FSW_BaseMesh_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_QuadTree
 *  \brief  A quadtree that represent a teslated sphere.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 *
 *  In fact the quadtee is composed of 8 sub-quadtree, each 
 *  representing a face of an octogone embeded in the sphere.
 *
 *	There is a little trick. This class inherit from FSW_QuadTreeNode.
 *	This is simply because we have set the father of the 8 root nodes 
 *	to be the tree itself. This allow this 8 node to call function
 *	of their father (the tree) to find their neighboor, as a classical node
 *	would do.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_QuadTree: public FSW_QuadTreeNode
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_QuadTree( FSW_BaseMesh_ABC& BaseMesh );
    virtual ~FSW_QuadTree();
    //@}

    //-------------------------------------------------------------------------
    /** \name Accessors */
    //-------------------------------------------------------------------------
    //@{	
	T_QuadTreeNodeVector& GetBaseNodeVector();
	T_QuadTreeVertexVector& GetBaseVertexVector();
    //@}

	/*------------------------------------------------------------------------------*/
    /** \name Tree-building and wavlet transform. */
    /*------------------------------------------------------------------------------*/
    //@{
	void BuildTree(const FSW_TreeFunction_ABC& Func, FSW_U32 nMaxLevel);
	void ForwardTransform( FSW_WaveletTransform_ABC& WaveletTransform, FSW_U32 nStartLevel = 0 );
	void BackwardTransform( FSW_WaveletTransform_ABC& WaveletTransform, FSW_U32 nStartLevel = 0 );
	//@}

	//-------------------------------------------------------------------------
    /** \name Inherited by FSW_QuadTreeNode. */
    //-------------------------------------------------------------------------
    //@{
	virtual FSW_QuadTreeNode* GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction);
	//@}

    //-------------------------------------------------------------------------
    /** \name Static this management. */
    //-------------------------------------------------------------------------
    //@{
	void SetStaticThis();
	void UnsetStaticThis();
	static FSW_QuadTree* StaticThis();
    //@}

    //-------------------------------------------------------------------------
    /** \name Node map management. */
    //-------------------------------------------------------------------------
    //@{
	FSW_U32 GetDepth();
	FSW_NodeMap& GetNodeMap(FSW_I32 CurLevel);
	FSW_Bool NodeMapExist(FSW_U32 CurLevel);
	void CleanNodeMap();
    //@}

    //-------------------------------------------------------------------------
    /** \name Should not be called [overload from FSW_Node]. */
    //-------------------------------------------------------------------------
    //@{
	void SetVertex( FSW_QuadTreeVertex* pVert1, FSW_QuadTreeVertex* pVert2, FSW_QuadTreeVertex* pVert3 ) { FSW_ASSERT(FSW_False); }
	void SetVertex( FSW_QuadTreeVertex* pVert, FSW_U32 nNum ) { FSW_ASSERT(FSW_False); }
	void SetVertexNull() { FSW_ASSERT(FSW_False); }
	FSW_QuadTreeVertex* GetVertex(FSW_U32 Num) { FSW_ASSERT(FSW_False); return NULL; }
	FSW_QuadTreeVertex* GetVertex( FSW_QuadTreeVertex& Vert1, FSW_QuadTreeVertex& Vert2 ) { FSW_ASSERT(FSW_False); return NULL; }
	const FSW_QuadTreeVertex* GetVertexConst(T_QuadTreeVert_Num Num) const { FSW_ASSERT(FSW_False); return NULL; }
	FSW_QuadTreeVertex* GetOwnedVertex(FSW_U32 nNum) { FSW_ASSERT(FSW_False); return NULL; }
	void SetVertexNoMoreUsed(T_QuadTreeVert_Num Num) { FSW_ASSERT(FSW_False); }
	void SetResponsabilityForVertex(FSW_Bool bResp, FSW_U32 nNum) { FSW_ASSERT(FSW_False); }
	FSW_Bool GetResponsabilityForVertex(FSW_U32 nNum) { FSW_ASSERT(FSW_False); return FSW_False; }
	FSW_QuadTreeNode* GetNeighbor(FSW_U32 nDirection) { FSW_ASSERT(FSW_False); return NULL; }
	FSW_DataChunk_ABC* GetDataChunk() { FSW_ASSERT(FSW_False); return NULL; }
	void SetDataChunk(FSW_DataChunk_ABC& DataChunk) { FSW_ASSERT(FSW_False); }
    //@}

	//-------------------------------------------------------------------------
    /** \name Base mesh management. */
    //-------------------------------------------------------------------------
    //@{
	FSW_BaseMesh_ABC& GetBaseMesh();
	void SetBaseMesh(FSW_BaseMesh_ABC& BaseMesh);
    //@}


private:

	void ClearAllData();
	void AssignValue( const FSW_TreeFunction_ABC& Func, FSW_QuadTreeNode& CurNode );

	/** The mesh we used to subdivide the surface and construct the tree. */
	FSW_BaseMesh_ABC* pBaseMesh_;
	
	/** The 8 sub-tree representing a face of the octahedron or other manifold. */
	T_QuadTreeNodeVector BaseNodeVector_;

	/** The first base vertex that compose our sphere/manifold. So cute ... */
	T_QuadTreeVertexVector BaseVertexVector_;

	/** Hold a map per level in the tree.
	    Each map store a copy of all node at a given level. */
	T_NodeMapVector NodeMapVector_;

	/** a static copy of this pointer to access the class from FSW_QuadTreeNode */
	static FSW_QuadTree* pStaticThis_;

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_QuadTree.inl"
#endif


#endif // _FSW_QUADTREE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
