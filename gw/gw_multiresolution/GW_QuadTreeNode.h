/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTreeNode.h
 *  \brief  Definition of class \c GW_QuadTreeNode
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_QUADTREENODE_H_
#define _GW_QUADTREENODE_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeVertex.h"
#include "GW_WaveletTransform_ABC.h"
#include "GW_DataChunk_ABC.h"

GW_BEGIN_NAMESPACE

/** Order of the vertex of the node. */
enum T_QuadTreeVert_Num 
{ QT_Vert1, QT_Vert2, QT_Vert3 };

class GW_BaseMesh_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_QuadTreeNode
 *  \brief  A node in a quadtree.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 *
 *  Each node maintains : 
 *		- 4 pointers on the 4 child nodes. They are set to \c NULL in case of a leaf node.
 *		- 3 pointers on the 3 vertex that define the triangle.
 *	In case of a non-leaf node, the node is responsible for creating the vextex (x3)
 *	of its child. They should be located in the middle of each segment that define the triangle.
 *	Of course, the node is also responsible for assigning these child vertex to its children, 
 *	and desalocating them when needed.
 *
 *	When computation are made on a per-vertex basis, the node is responsible for the computation on
 *	the vertex of its child, not on its own vertex. That's because the vertex that define the triangle 
 *	of the node are shared with its neighboors triangles.
 *
 *	\b Important : Remember that the name of the 3 vertex are {1,2,3}.
 *	So never use code as 
 *	\begincode 
 *		aVertex_[0] = NULL;
 *	\endcode
 *	But instead : 
 *	\begincode 
 *		aVertex_[QT_Vert1] = NULL;
 *	\endcode
 */ 
/*------------------------------------------------------------------------------*/

class GW_QuadTreeNode
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_QuadTreeNode();
    virtual ~GW_QuadTreeNode();
    //@}

	/*------------------------------------------------------------------------------*/
    /** \name Hierarchy management. */
    /*------------------------------------------------------------------------------*/
    //@{
	void SetChildNode(	GW_QuadTreeNode* pChild0,
						GW_QuadTreeNode* pChild1,
						GW_QuadTreeNode* pChild2,
						GW_QuadTreeNode* pChild3 );
	GW_QuadTreeNode* GetChildNode(GW_U32 Num);
	GW_U32 GetDepth();
	void SetDepth(GW_U32 nDepth);
	GW_QuadTreeNode& GetFather();
	void SetFather(GW_QuadTreeNode& Father);
	GW_Bool IsLeaf();
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Management of the 3 corner vertex. */
    /*------------------------------------------------------------------------------*/
    //@{
	virtual void SetVertex( GW_QuadTreeVertex* pVert1,
					GW_QuadTreeVertex* pVert2,
					GW_QuadTreeVertex* pVert3 );
	virtual void SetVertex( GW_QuadTreeVertex* pVert, GW_U32 nNum );
	virtual void SetVertexNull();
	virtual GW_QuadTreeVertex* GetVertex(GW_U32 Num);
	virtual GW_QuadTreeVertex* GetVertex( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 );
	virtual const GW_QuadTreeVertex* GetVertexConst(T_QuadTreeVert_Num Num) const;
	virtual GW_QuadTreeVertex* GetOwnedVertex(GW_U32 nNum);
	virtual void SetVertexNoMoreUsed(T_QuadTreeVert_Num Num);
	GW_QuadTreeVertex* GetCompletionVertex( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 );
	GW_QuadTreeVertex* GetVertexBetween( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 );
	GW_I32 GetVertexNumberBetween( GW_QuadTreeVertex& Vert1, GW_QuadTreeVertex& Vert2 );
	GW_I32 GetVertexNumber( GW_QuadTreeVertex& Vert );
	GW_I32 GetOwnedVertexNumber( GW_QuadTreeVertex& Vert );
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Management of the 3 central vertex (not our vertex), that we might be
		responsible for. */
    /*------------------------------------------------------------------------------*/
    //@{
	void SetResponsabilityForVertex(GW_Bool bResp, GW_U32 nNum);
	GW_Bool GetResponsabilityForVertex(GW_U32 nNum);
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Neighbor management. */
    /*------------------------------------------------------------------------------*/
    //@{
	GW_QuadTreeNode* GetNeighbor(GW_QuadTreeVertex& Direction);
	virtual GW_QuadTreeNode* GetRelativeSon(GW_QuadTreeNode& pSon, GW_QuadTreeVertex& Direction);
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Tree-building and wavelet transform. */
    /*------------------------------------------------------------------------------*/
    //@{
	void BuildTree(GW_BaseMesh_ABC& BaseMesh, const GW_TreeFunction_ABC& Func, GW_U32 nCurLevel, GW_U32 nMaxLevel);
	//@}

    //-------------------------------------------------------------------------
    /** \name Id management. */
    //-------------------------------------------------------------------------
    //@{
	void SetId(GW_U32 nID);
	GW_U32 GetId();
    //@}

	//-------------------------------------------------------------------------
    /** \name Data chunk management. */
    //-------------------------------------------------------------------------
    //@{
	GW_DataChunk_ABC* GetDataChunk();
	void SetDataChunk(GW_DataChunk_ABC& DataChunk);
    //@}

	    //-------------------------------------------------------------------------
    /** \name Value management. Use it for face base wavelets only. */
    //-------------------------------------------------------------------------
    //@{
	void SetValue(GW_Float rVal);
	GW_Float GetValue() const;
    //@}

	/** This is only used by compressor when making distinction
		between node already processed and node to be processed */
	enum T_NodeCompressionType
	{
		kTypeA,
		kTypeB,
		kTypeUndefined	// this is for error check (to see if the type has *really* been set)
	};

    //-------------------------------------------------------------------------
    /** \name Compression Type management. */
    //-------------------------------------------------------------------------
    //@{
	T_NodeCompressionType GetCompressionType();
	void SetCompressionType(T_NodeCompressionType CompressionType);
    //@}


private:

	enum T_NodeOrientation 
	{ 
		QT_Node1, QT_Node2, QT_Node3, QT_Node4
	};

	/** The sons of this vertex. They are \c NULL in case of a leaf node.
		\c Sons[0] is the center sub-triangle. Other triangle are labeled
		using the vertex of the main triangle they contain. */
	GW_QuadTreeNode* aChildNode_[4];
	/**
		The father node. If the node is one of the 8 root of the sphere, then the father
		is the quadtree itself (that's why the class GW_QuadTree inherit from GW_QuadTreeNode). 
		This trick allow to use the function call
		\begincode
			pFather_->GetRelativeSon( this, 1 );	// 1 is the direction in which we search
		\endcode
		Even if we are a root node (then, it's up to the Tree itself to tell us
		which node is our neighbor).
	*/
	GW_QuadTreeNode* pFather_;
	/** The 3 vertex that compose the triangle of this node.
		Remember that this node does not hold these vertex, since
		they are shared among the neighboor triangle. 
		Trey are labeled in a counter-clock wise order. 
		Numbering range from 1 to 3, so use 'QT_VertX'
		where X=1,2,3 to name the vertex. */
	GW_QuadTreeVertex* aVertex_[3];

	/** Each bool is for one of the 3 vertex of our central sub-triangle.
		If we have created one of these vertex, it means we are responsible for this 
		vertex. */
	GW_Bool aResponsibleForVertex_[3];

	/** Value hold by the face. For face base transform *ONLY* */
	GW_Float rVal_;

	/** the depth of this node */
	GW_U32 nDepth_;

	/** The Id of the node in the map reprsenting all node
	    at a given level in the tree. */
	GW_U32 nID_;

	/** for face based wavelet transform ONLY : 
		the data chunk the transform use to store some precomputed values. */
	GW_DataChunk_ABC* pDataChunk_;

	/** This is only used by compressor when making distinction
		between node already processed and node to be processed */
	T_NodeCompressionType CompressionType_;

	/** a local copy of the owned vertex, used by the destructor when the central node is destroyed */
	GW_QuadTreeVertex** aOwnedVertex_;

};

/*------------------------------------------------------------------------------*/
/** \name a list of GW_QuadTreeNode */
/*------------------------------------------------------------------------------*/
//@{
typedef std::list<GW_QuadTreeNode*> T_QuadTreeNodeList;
typedef T_QuadTreeNodeList::iterator IT_QuadTreeNodeList;
typedef T_QuadTreeNodeList::reverse_iterator RIT_QuadTreeNodeList;
typedef T_QuadTreeNodeList::const_iterator CIT_QuadTreeNodeList;
typedef T_QuadTreeNodeList::const_reverse_iterator CRIT_QuadTreeNodeList;
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of GW_QuadTreeNode */
/*------------------------------------------------------------------------------*/
//@{
typedef std::vector<GW_QuadTreeNode*> T_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::iterator IT_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::reverse_iterator RIT_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::const_iterator CIT_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::const_reverse_iterator CRIT_QuadTreeNodeVector;
//@}

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_QuadTreeNode.inl"
#endif


#endif // _GW_QUADTREENODE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
