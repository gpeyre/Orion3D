
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseOctahedron.h
 *  \brief  Definition of class \c GW_BaseOctahedron
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BASEOCTAHEDRON_H_
#define _GW_BASEOCTAHEDRON_H_

#include "../gw_core/GW_Config.h"
#include "GW_BaseMesh_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_BaseOctahedron
 *  \brief  A base mesh consisting of an octahedron, that subdivides into a sphere.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 *
 *  The octahedron is composed of 8 faces (2 pyramid), and gives an 
 *  easy way to tesslate a sphere with a consistant naming scheme.
 */ 
/*------------------------------------------------------------------------------*/

class GW_BaseOctahedron:	public GW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_BaseOctahedron();
    virtual ~GW_BaseOctahedron();
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
	{ return "GW_BaseOctahedron"; }
    //@}

private:

	/** The 6 number of the base vertex */
	enum T_BaseVertexOrientation
	{
		k90N, k90S, k180EW, k0EW, k90E, k90W
	};
	
	/** a very useful lookup table that encode 
	    proximity relations between the 8 quadrant of the octaedre */
	static GW_U32 aSubTreeNeighbor_[8][3];

};

GW_END_NAMESPACE


#endif // _GW_BASEOCTAHEDRON_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
