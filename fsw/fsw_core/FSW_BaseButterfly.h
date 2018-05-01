
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BaseButterfly.h
 *  \brief  Definition of class \c FSW_BaseButterfly
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_BASEBUTTERFLY_H_
#define _FSW_BASEBUTTERFLY_H_

#include "FSW_Config.h"
#include "FSW_BaseMesh_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_BaseButterfly
 *  \brief  A base mesh that uses a buttefly division scheme.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  This use another base mesh for the base faces/vertex. Positionate
 *	the vertice using a subdivision scheme.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_BaseButterfly:	public FSW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_BaseButterfly( FSW_BaseMesh_ABC& StartMesh );
    virtual ~FSW_BaseButterfly();
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
	{ return "FSW_BaseButterfly"; }
    //@}

	FSW_Float GetTension() const;
	void SetTension(FSW_Float rTension);

private:

	static void Positionate_Helper( FSW_QuadTreeVertex& StencilVert, FSW_Float rWeight, void* pChunk );

	/** The base mesh used for the begining of the subdivision process. */
	FSW_BaseMesh_ABC* pStartMesh_;

	/** Tension of the scheme. 0 is for classical scheme (8 neighbor stencil). */
	FSW_Float rTension_;

};

FSW_END_NAMESPACE


#endif // _FSW_BASEBUTTERFLY_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
