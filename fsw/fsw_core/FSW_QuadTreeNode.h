/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTreeNode.h
 *  \brief  Definition of class \c FSW_QuadTreeNode
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_QUADTREENODE_H_
#define _FSW_QUADTREENODE_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeVertex.h"
#include "FSW_WaveletTransform_ABC.h"
#include "FSW_DataChunk_ABC.h"

FSW_BEGIN_NAMESPACE

/** Order of the vertex of the node. */
enum T_QuadTreeVert_Num 
{ QT_Vert1, QT_Vert2, QT_Vert3 };

class FSW_BaseMesh_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_QuadTreeNode
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

class FSW_QuadTreeNode
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_QuadTreeNode();
    virtual ~FSW_QuadTreeNode();
    //@}

	/*------------------------------------------------------------------------------*/
    /** \name Hierarchy management. */
    /*------------------------------------------------------------------------------*/
    //@{
	void SetChildNode(	FSW_QuadTreeNode* pChild0,
						FSW_QuadTreeNode* pChild1,
						FSW_QuadTreeNode* pChild2,
						FSW_QuadTreeNode* pChild3 );
	FSW_QuadTreeNode* GetChildNode(FSW_U32 Num);
	FSW_U32 GetDepth();
	void SetDepth(FSW_U32 nDepth);
	FSW_QuadTreeNode& GetFather();
	void SetFather(FSW_QuadTreeNode& Father);
	FSW_Bool IsLeaf();
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Management of the 3 corner vertex. */
    /*------------------------------------------------------------------------------*/
    //@{
	virtual void SetVertex( FSW_QuadTreeVertex* pVert1,
					FSW_QuadTreeVertex* pVert2,
					FSW_QuadTreeVertex* pVert3 );
	virtual void SetVertex( FSW_QuadTreeVertex* pVert, FSW_U32 nNum );
	virtual void SetVertexNull();
	virtual FSW_QuadTreeVertex* GetVertex(FSW_U32 Num);
	virtual FSW_QuadTreeVertex* GetVertex( FSW_QuadTreeVertex& Vert1, FSW_QuadTreeVertex& Vert2 );
	virtual const FSW_QuadTreeVertex* GetVertexConst(T_QuadTreeVert_Num Num) const;
	virtual FSW_QuadTreeVertex* GetOwnedVertex(FSW_U32 nNum);
	virtual void SetVertexNoMoreUsed(T_QuadTreeVert_Num Num);
	FSW_QuadTreeVertex* GetCompletionVertex( FSW_QuadTreeVertex& Vert1, FSW_QuadTreeVertex& Vert2 );
	FSW_QuadTreeVertex* GetVertexBetween( FSW_QuadTreeVertex& Vert1, FSW_QuadTreeVertex& Vert2 );
	FSW_I32 GetVertexNumberBetween( FSW_QuadTreeVertex& Vert1, FSW_QuadTreeVertex& Vert2 );
	FSW_I32 GetVertexNumber( FSW_QuadTreeVertex& Vert );
	FSW_I32 GetOwnedVertexNumber( FSW_QuadTreeVertex& Vert );
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Management of the 3 central vertex (not our vertex), that we might be
		responsible for. */
    /*------------------------------------------------------------------------------*/
    //@{
	void SetResponsabilityForVertex(FSW_Bool bResp, FSW_U32 nNum);
	FSW_Bool GetResponsabilityForVertex(FSW_U32 nNum);
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Neighbor management. */
    /*------------------------------------------------------------------------------*/
    //@{
	FSW_QuadTreeNode* GetNeighbor(FSW_QuadTreeVertex& Direction);
	virtual FSW_QuadTreeNode* GetRelativeSon(FSW_QuadTreeNode& pSon, FSW_QuadTreeVertex& Direction);
	//@}

	/*------------------------------------------------------------------------------*/
    /** \name Tree-building and wavelet transform. */
    /*------------------------------------------------------------------------------*/
    //@{
	void BuildTree(FSW_BaseMesh_ABC& BaseMesh, const FSW_TreeFunction_ABC& Func, FSW_U32 nCurLevel, FSW_U32 nMaxLevel);
	//@}

    //-------------------------------------------------------------------------
    /** \name Id management. */
    //-------------------------------------------------------------------------
    //@{
	void SetId(FSW_U32 nID);
	FSW_U32 GetId();
    //@}

	//-------------------------------------------------------------------------
    /** \name Data chunk management. */
    //-------------------------------------------------------------------------
    //@{
	FSW_DataChunk_ABC* GetDataChunk();
	void SetDataChunk(FSW_DataChunk_ABC& DataChunk);
    //@}

	    //-------------------------------------------------------------------------
    /** \name Value management. Use it for face base wavelets only. */
    //-------------------------------------------------------------------------
    //@{
	void SetValue(FSW_Float rVal);
	FSW_Float GetValue() const;
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
	FSW_QuadTreeNode* aChildNode_[4];
	/**
		The father node. If the node is one of the 8 root of the sphere, then the father
		is the quadtree itself (that's why the class FSW_QuadTree inherit from FSW_QuadTreeNode). 
		This trick allow to use the function call
		\begincode
			pFather_->GetRelativeSon( this, 1 );	// 1 is the direction in which we search
		\endcode
		Even if we are a root node (then, it's up to the Tree itself to tell us
		which node is our neighbor).
	*/
	FSW_QuadTreeNode* pFather_;
	/** The 3 vertex that compose the triangle of this node.
		Remember that this node does not hold these vertex, since
		they are shared among the neighboor triangle. 
		Trey are labeled in a counter-clock wise order. 
		Numbering range from 1 to 3, so use 'QT_VertX'
		where X=1,2,3 to name the vertex. */
	FSW_QuadTreeVertex* aVertex_[3];

	/** Each bool is for one of the 3 vertex of our central sub-triangle.
		If we have created one of these vertex, it means we are responsible for this 
		vertex. */
	FSW_Bool aResponsibleForVertex_[3];

	/** Value hold by the face. For face base transform *ONLY* */
	FSW_Float rVal_;

	/** the depth of this node */
	FSW_U32 nDepth_;

	/** The Id of the node in the map reprsenting all node
	    at a given level in the tree. */
	FSW_U32 nID_;

	/** for face based wavelet transform ONLY : 
		the data chunk the transform use to store some precomputed values. */
	FSW_DataChunk_ABC* pDataChunk_;

	/** This is only used by compressor when making distinction
		between node already processed and node to be processed */
	T_NodeCompressionType CompressionType_;

	/** a local copy of the owned vertex, used by the destructor when the central node is destroyed */
	FSW_QuadTreeVertex** aOwnedVertex_;

};

/*------------------------------------------------------------------------------*/
/** \name a list of FSW_QuadTreeNode */
/*------------------------------------------------------------------------------*/
//@{
typedef list<FSW_QuadTreeNode*> T_QuadTreeNodeList;
typedef T_QuadTreeNodeList::iterator IT_QuadTreeNodeList;
typedef T_QuadTreeNodeList::reverse_iterator RIT_QuadTreeNodeList;
typedef T_QuadTreeNodeList::const_iterator CIT_QuadTreeNodeList;
typedef T_QuadTreeNodeList::const_reverse_iterator CRIT_QuadTreeNodeList;
//@}

/*------------------------------------------------------------------------------*/
/** \name a vector of FSW_QuadTreeNode */
/*------------------------------------------------------------------------------*/
//@{
typedef vector<FSW_QuadTreeNode*> T_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::iterator IT_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::reverse_iterator RIT_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::const_iterator CIT_QuadTreeNodeVector;
typedef T_QuadTreeNodeVector::const_reverse_iterator CRIT_QuadTreeNodeVector;
//@}

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_QuadTreeNode.inl"
#endif


#endif // _FSW_QUADTREENODE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
