
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_VertexBasedCompressor.h
 *  \brief  Definition of class \c GW_VertexBasedCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_FACEBASEDCOMPRESSGW_H_
#define _GW_FACEBASEDCOMPRESSGW_H_

#include "../gw_core/GW_Config.h"
#include "GW_Compressor_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_VertexBasedCompressor
 *  \brief  Base class for all compressor using a transform based on vertex.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  This defines a bunch of usefull function to proccess vertex base 
 *  compression scheme.
 */ 
/*------------------------------------------------------------------------------*/

class GW_VertexBasedCompressor:	public GW_Compressor_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_VertexBasedCompressor();
    virtual ~GW_VertexBasedCompressor();
    //@}

	static GW_I32 GetQuantifiedValue( const GW_QuadTreeVertex& v );
	static void SetQuantifiedValue( GW_QuadTreeVertex& Vert, GW_I32 nVal );
	static void SetQuantifiedValueSign( GW_QuadTreeVertex& Vert, GW_Bool bSign );
	static void AddAbsQuantifiedValue( GW_QuadTreeVertex& Vert, GW_I32 nAddVal );

	//-------------------------------------------------------------------------
    /** \name Helper methods for compression. */
    //-------------------------------------------------------------------------
    //@{
	static void Quantification( GW_QuadTree& QuadTree, GW_CompressionHeader& CompressionHeader );
	static void UnQuantification( GW_QuadTree& QuadTree, GW_CompressionHeader& CompressionHeader );
	static void Scaling( GW_QuadTree& QuadTree, GW_CompressionHeader& CompressionHeader );
	static void UnScaling( GW_QuadTree& QuadTree, GW_CompressionHeader& CompressionHeader );
	static void ComputeMaxCoefValue( GW_QuadTree& QuadTree, GW_CompressionHeader& CompressionHeader );
    //@}

private:

	static void Quantification_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth );
	static void UnQuantification_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth );
	static void Scaling_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth );
	static void UnScaling_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth );
	static void ComputeMaxCoefValue_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth );

	typedef void (*T_FunctionApplyableOnVertex)(GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth );
	static void ApplyFunctionOnVertex(GW_QuadTree& Tree, T_FunctionApplyableOnVertex pFunc, void* pChunk=NULL);


};

GW_END_NAMESPACE



#endif // _GW_FACEBASEDCOMPRESSGW_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
