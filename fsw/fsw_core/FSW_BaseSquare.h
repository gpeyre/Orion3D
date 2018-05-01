
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseSquare.h
 *  \brief  Definition of class \c FSW_BaseSquare
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_BASESQUARE_H_
#define _FSW_BASESQUARE_H_

#include "FSW_Config.h"
#include "FSW_BaseMesh_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_BaseSquare
 *  \brief  A base mesh consisting of an octahedron, that subdivides into a sphere.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  The octahedron is composed of 8 faces (2 pyramid), and gives an 
 *  easy way to tesslate a sphere with a consistant naming scheme.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_BaseSquare:	public FSW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_BaseSquare();
    virtual ~FSW_BaseSquare();
    //@}

	
	/*------------------------------------------------------------------------------*/
    /** \name Overloaded. */
    /*------------------------------------------------------------------------------*/
    //@{
    virtual void BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector );
	virtual FSW_QuadTreeNode* GetRelativeSon(FSW_QuadTreeNode& Son, FSW_QuadTreeVertex& Direction);

	virtual void Positionate( FSW_QuadTreeNode& CurNode );
	virtual void ConvertToLocalFrame( const FSW_Vector3D& Pos, FSW_Float& rU, FSW_Float& rV );

	virtual FSW_U32 GetNbrVertex( FSW_U32 nDepth );
	virtual FSW_U32 GetNbrFace( FSW_U32 nDepth );
	virtual FSW_U32 GetNbrEdge( FSW_U32 nDepth );
    //@}

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the base mesh in the compressed files. */
	virtual const char* GetBaseMeshName()
	{ return "FSW_BaseSquare"; }
    //@}

};

FSW_END_NAMESPACE


#endif // _FSW_BASESQUARE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
