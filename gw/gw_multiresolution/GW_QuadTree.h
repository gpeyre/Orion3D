
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTree.h
 *  \brief  Definition of class \c GW_QuadTree
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_QUADTREE_H_
#define _GW_QUADTREE_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeNode.h"
#include "GW_NodeMap.h"
#include "GW_QuadtreeNode.h"

GW_BEGIN_NAMESPACE


class GW_WaveletTransform_ABC; 
class GW_BaseMesh_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_QuadTree
 *  \brief  A quadtree that represent a teslated sphere.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 *
 *  In fact the quadtee is composed of 8 sub-quadtree, each 
 *  representing a face of an octogone embeded in the sphere.
 *
 *	There is a little trick. This class inherit from GW_QuadTreeNode.
 *	This is simply because we have set the father of the 8 root nodes 
 *	to be the tree itself. This allow this 8 node to call function
 *	of their father (the tree) to find their neighboor, as a classical node
 *	would do.
 */ 
/*------------------------------------------------------------------------------*/

class GW_QuadTree: public GW_QuadTreeNode
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_QuadTree( GW_BaseMesh_ABC& BaseMesh );
    virtual ~GW_QuadTree();
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
	void BuildTree(const GW_TreeFunction_ABC& Func, GW_U32 nMaxLevel);
	void Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, const GW_TreeFunction_ABC& Func, 
					  GW_Vector3D BaryCoord0, GW_Vector3D BaryCoord1, GW_Vector3D BaryCoord2 );
	void ForwardTransform( GW_WaveletTransform_ABC& WaveletTransform, GW_U32 nStartLevel = 0 );
	void BackwardTransform( GW_WaveletTransform_ABC& WaveletTransform, GW_U32 nStartLevel = 0 );
	//@}

	//-------------------------------------------------------------------------
    /** \name Inherited by GW_QuadTreeNode. */
    //-------------------------------------------------------------------------
    //@{
	virtual GW_QuadTreeNode* GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction);
	//@}

    //-------------------------------------------------------------------------
    /** \name Static this management. */
    //-------------------------------------------------------------------------
    //@{
	void SetStaticThis();
	void UnsetStaticThis();
	static GW_QuadTree* StaticThis();
    //@}

    //-------------------------------------------------------------------------
    /** \name Node map management. */
    //-------------------------------------------------------------------------
    //@{
	GW_U32 GetDepth();
	GW_NodeMap& GetNodeMap(GW_I32 CurLevel);
	GW_Bool NodeMapExist(GW_U32 CurLevel);
	void CleanNodeMap();
    //@}

    //-------------------------------------------------------------------------
    /** \name Should not be called [overload from GW_Node]. */
    //-------------------------------------------------------------------------
    //@{
	void SetVertex( GW_QuadTreeVertex* pVert1, GW_QuadTreeVertex* pVert2, GW_QuadTreeVertex* pVert3 ) { GW_ASSERT(GW_False); }
	void SetVertex( GW_QuadTreeVertex* pVert, GW_U32 nNum ) { GW_ASSERT(GW_False); }
	void SetVertexNull() { GW_ASSERT(GW_False); }
	GW_QuadTreeVertex* GetVertex(GW_U32 Num) { GW_ASSERT(GW_False); return NULL; }
	GW_QuadTreeVertex* GetVertex( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 ) { GW_ASSERT(GW_False); return NULL; }
	const GW_QuadTreeVertex* GetVertexConst(T_QuadTreeVert_Num Num) const { GW_ASSERT(GW_False); return NULL; }
	GW_QuadTreeVertex* GetOwnedVertex(GW_U32 nNum) { GW_ASSERT(GW_False); return NULL; }
	void SetVertexNoMoreUsed(T_QuadTreeVert_Num Num) { GW_ASSERT(GW_False); }
	void SetResponsabilityForVertex(GW_Bool bResp, GW_U32 nNum) { GW_ASSERT(GW_False); }
	GW_Bool GetResponsabilityForVertex(GW_U32 nNum) { GW_ASSERT(GW_False); return GW_False; }
	GW_QuadTreeNode* GetNeighbor(GW_U32 nDirection) { GW_ASSERT(GW_False); return NULL; }
	GW_DataChunk_ABC* GetDataChunk() { GW_ASSERT(GW_False); return NULL; }
	void SetDataChunk(GW_DataChunk_ABC& DataChunk) { GW_ASSERT(GW_False); }
    //@}

	//-------------------------------------------------------------------------
    /** \name Base mesh management. */
    //-------------------------------------------------------------------------
    //@{
	GW_BaseMesh_ABC& GetBaseMesh();
	void SetBaseMesh(GW_BaseMesh_ABC& BaseMesh);
    //@}


private:

	void ClearAllData();
	void AssignValue( const GW_TreeFunction_ABC& Func, GW_QuadTreeNode& CurNode );

	/** The mesh we used to subdivide the surface and construct the tree. */
	GW_BaseMesh_ABC* pBaseMesh_;
	
	/** The 8 sub-tree representing a face of the octahedron or other manifold. */
	T_QuadTreeNodeVector BaseNodeVector_;

	/** The first base vertex that compose our sphere/manifold. So cute ... */
	T_QuadTreeVertexVector BaseVertexVector_;

	/** Hold a map per level in the tree.
	    Each map store a copy of all node at a given level. */
	T_NodeMapVector NodeMapVector_;

	/** a static copy of this pointer to access the class from GW_QuadTreeNode */
	static GW_QuadTree* pStaticThis_;

};

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_QuadTree.inl"
#endif


#endif // _GW_QUADTREE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
