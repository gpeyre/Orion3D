
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseButterfly.h
 *  \brief  Definition of class \c GW_BaseButterfly
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BASEBUTTERFLY_H_
#define _GW_BASEBUTTERFLY_H_

#include "../gw_core/GW_Config.h"
#include "GW_BaseMesh_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_BaseButterfly
 *  \brief  A base mesh that uses a buttefly division scheme.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  This use another base mesh for the base faces/vertex. Positionate
 *	the vertice using a subdivision scheme.
 */ 
/*------------------------------------------------------------------------------*/

class GW_BaseButterfly:	public GW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_BaseButterfly( GW_BaseMesh_ABC& StartMesh );
    virtual ~GW_BaseButterfly();
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
	{ return "GW_BaseButterfly"; }
    //@}

	GW_Float GetTension() const;
	void SetTension(GW_Float rTension);

private:

	static void Positionate_Helper( GW_QuadTreeVertex& StencilVert, GW_Float rWeight, void* pChunk );

	/** The base mesh used for the begining of the subdivision process. */
	GW_BaseMesh_ABC* pStartMesh_;

	/** Tension of the scheme. 0 is for classical scheme (8 neighbor stencil). */
	GW_Float rTension_;

};

GW_END_NAMESPACE


#endif // _GW_BASEBUTTERFLY_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
