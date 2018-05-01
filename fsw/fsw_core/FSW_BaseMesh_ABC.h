
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseMesh_ABC.h
 *  \brief  Definition of class \c FSW_BaseMesh_ABC
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_BASEMESH_ABC_H_
#define _FSW_BASEMESH_ABC_H_

#include "FSW_Config.h"
#include "FSW_QuadTreeNode.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_BaseMesh_ABC
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

class FSW_BaseMesh_ABC
{

public:

	FSW_BaseMesh_ABC()
	:pBaseNodeVector_(NULL){}

	/*------------------------------------------------------------------------------*/
    /** \name To overload. */
    /*------------------------------------------------------------------------------*/
    //@{
    virtual void BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector ) = 0;
	virtual FSW_QuadTreeNode* GetRelativeSon(FSW_QuadTreeNode& pSon, FSW_QuadTreeVertex& Direction) = 0;
	
	virtual void Positionate( FSW_QuadTreeNode& CurNode ) = 0;
	virtual void ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV ) = 0;

	virtual FSW_U32 GetNbrVertex( FSW_U32 nDepth ) = 0;
	virtual FSW_U32 GetNbrFace( FSW_U32 nDepth ) = 0;
	virtual FSW_U32 GetNbrEdge( FSW_U32 nDepth ) = 0;
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

FSW_END_NAMESPACE


#endif // _FSW_BASEMESH_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
