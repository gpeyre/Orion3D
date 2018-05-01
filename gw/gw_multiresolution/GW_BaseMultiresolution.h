
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BaseMultiresolution.h
 *  \brief  Definition of class \c GW_BaseMultiresolution
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_BASEMULTIRESOLUTION_H_
#define _GW_BASEMULTIRESOLUTION_H_

#include "../gw_core/GW_Config.h"
#include "GW_BaseMesh_ABC.h"
#include "../gw_geodesic/GW_GeodesicMesh.h"
#include "../gw_geodesic/GW_VoronoiMesh.h"

namespace GW {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_BaseMultiresolution
 *  \brief  Use a parameterized mesh as base mesh.
 *  \author Gabriel Peyré
 *  \date   5-20-2003
 *
 *  Use the library \c gw_geodesic
 */ 
/*------------------------------------------------------------------------------*/

class GW_BaseMultiresolution:	public GW_BaseMesh_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_BaseMultiresolution( GW_GeodesicMesh& GeodesicMesh, GW_VoronoiMesh& VoronoiMesh );
    virtual ~GW_BaseMultiresolution();
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
	{ return "GW_BaseMultiresolution"; }
	//@}

private:

	GW_VoronoiVertex* GetVoronoiVertex( GW_QuadTreeVertex& QuadTreeVert );
	GW_Face* GetVoronoiFace( GW_QuadTreeNode& QuadTreeNode );

	GW_GeodesicMesh& GeodesicMesh_;
	GW_VoronoiMesh& VoronoiMesh_; 
	/* Map to make traduction between Voronoi data and quadtree data */
	T_U32Map QuadTreeVertexID_;
	T_U32Map QuadTreeNodeID_;

};

} // End namespace GW



#endif // _GW_BASEMULTIRESOLUTION_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
