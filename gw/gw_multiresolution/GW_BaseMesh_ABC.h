
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseMesh_ABC.h
 *  \brief  Definition of class \c GW_BaseMesh_ABC
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BASEMESH_ABC_H_
#define _GW_BASEMESH_ABC_H_

#include "../gw_core/GW_Config.h"
#include "GW_QuadTreeNode.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_BaseMesh_ABC
 *  \brief  Base class for all orginal mesh.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  A base mesh is the 0 level of the quadtree, i.e. of the subdivision scheme.
 *	It must provide :
 *		- A function to build this 0 level (fill a list with the base node (first create them), create
 *		the vertex, and link them with the base node).
 *		- A function to positionate the 3 vertex of a newly created node.
 *		- A function to locate a neighbor of a given node (of the base mesh) in a given direction.
 *
 *	Note that you are not responsible for the vertex/nodes you created. 
 *	This is up to the quadtree who called \c BuildBaseMesh to desalocate them.
 */ 
/*------------------------------------------------------------------------------*/

class GW_BaseMesh_ABC
{

public:

	GW_BaseMesh_ABC()
	:pBaseNodeVector_(NULL){}

	/*------------------------------------------------------------------------------*/
    /** \name To overload. */
    /*------------------------------------------------------------------------------*/
    //@{
    virtual void BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector ) = 0;
	virtual GW_QuadTreeNode* GetRelativeSon(GW_QuadTreeNode& pSon, GW_QuadTreeVertex& Direction) = 0;
	
	virtual void Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, 
		GW_Vector3D BaryCoord0, GW_Vector3D BaryCoord1, GW_Vector3D BaryCoord2 ) = 0;
	virtual void ConvertToLocalFrame( const GW_Vector3D& Pos, GW_Float& rU, GW_Float& rV ) = 0;

	virtual GW_U32 GetNbrVertex( GW_U32 nDepth ) = 0;
	virtual GW_U32 GetNbrFace( GW_U32 nDepth ) = 0;
	virtual GW_U32 GetNbrEdge( GW_U32 nDepth ) = 0;
    //@}

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the base mesh in the file. */
	virtual const char* GetBaseMeshName() = 0;
    //@}

protected:

	/** This should simply be a copy of the list returned by \c T_QuadTreeNodeList, so that 
		we can retrieve the neighbor later. */
	T_QuadTreeNodeVector* pBaseNodeVector_;

};

GW_END_NAMESPACE


#endif // _GW_BASEMESH_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
