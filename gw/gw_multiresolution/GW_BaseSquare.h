
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseSquare.h
 *  \brief  Definition of class \c GW_BaseSquare
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BASESQUARE_H_
#define _GW_BASESQUARE_H_

#include "../gw_core/GW_Config.h"
#include "GW_BaseMesh_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_BaseSquare
 *  \brief  A base mesh consisting of an octahedron, that subdivides into a sphere.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  The octahedron is composed of 8 faces (2 pyramid), and gives an 
 *  easy way to tesslate a sphere with a consistant naming scheme.
 */ 
/*------------------------------------------------------------------------------*/

class GW_BaseSquare:	public GW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_BaseSquare();
    virtual ~GW_BaseSquare();
    //@}

	
	/*------------------------------------------------------------------------------*/
    /** \name Overloaded. */
    /*------------------------------------------------------------------------------*/
    //@{
    virtual void BuildBaseMesh( T_QuadTreeNodeVector& BaseNodeVector, T_QuadTreeVertexVector& BaseVertexVector );
	virtual GW_QuadTreeNode* GetRelativeSon(GW_QuadTreeNode& Son, GW_QuadTreeVertex& Direction);

	virtual void Positionate( GW_QuadTreeNode& CurNode, GW_QuadTreeNode& RootNode, 
		GW_Vector3D BaryCoord0, GW_Vector3D BaryCoord1, GW_Vector3D BaryCoord2 );
	virtual void ConvertToLocalFrame( const GW_Vector3D& Pos, GW_Float& rU, GW_Float& rV );

	virtual GW_U32 GetNbrVertex( GW_U32 nDepth );
	virtual GW_U32 GetNbrFace( GW_U32 nDepth );
	virtual GW_U32 GetNbrEdge( GW_U32 nDepth );
    //@}

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the base mesh in the compressed files. */
	virtual const char* GetBaseMeshName()
	{ return "GW_BaseSquare"; }
    //@}

};

GW_END_NAMESPACE


#endif // _GW_BASESQUARE_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
