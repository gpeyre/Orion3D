
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_VertexBasedCompressor.h
 *  \brief  Definition of class \c FSW_VertexBasedCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_FACEBASEDCOMPRESSFSW_H_
#define _FSW_FACEBASEDCOMPRESSFSW_H_

#include "../fsw_core/FSW_Config.h"
#include "FSW_Compressor_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_VertexBasedCompressor
 *  \brief  Base class for all compressor using a transform based on vertex.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  This defines a bunch of usefull function to proccess vertex base 
 *  compression scheme.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_VertexBasedCompressor:	public FSW_Compressor_ABC
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_VertexBasedCompressor();
    virtual ~FSW_VertexBasedCompressor();
    //@}

	static FSW_I32 GetQuantifiedValue( const FSW_QuadTreeVertex& v );
	static void SetQuantifiedValue( FSW_QuadTreeVertex& Vert, FSW_I32 nVal );
	static void SetQuantifiedValueSign( FSW_QuadTreeVertex& Vert, FSW_Bool bSign );
	static void AddAbsQuantifiedValue( FSW_QuadTreeVertex& Vert, FSW_I32 nAddVal );

	//-------------------------------------------------------------------------
    /** \name Helper methods for compression. */
    //-------------------------------------------------------------------------
    //@{
	static void Quantification( FSW_QuadTree& QuadTree, FSW_CompressionHeader& CompressionHeader );
	static void UnQuantification( FSW_QuadTree& QuadTree, FSW_CompressionHeader& CompressionHeader );
	static void Scaling( FSW_QuadTree& QuadTree, FSW_CompressionHeader& CompressionHeader );
	static void UnScaling( FSW_QuadTree& QuadTree, FSW_CompressionHeader& CompressionHeader );
	static void ComputeMaxCoefValue( FSW_QuadTree& QuadTree, FSW_CompressionHeader& CompressionHeader );
    //@}

private:

	static void Quantification_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth );
	static void UnQuantification_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth );
	static void Scaling_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth );
	static void UnScaling_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth );
	static void ComputeMaxCoefValue_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth );

	typedef void (*T_FunctionApplyableOnVertex)(FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth );
	static void ApplyFunctionOnVertex(FSW_QuadTree& Tree, T_FunctionApplyableOnVertex pFunc, void* pChunk=NULL);


};

FSW_END_NAMESPACE



#endif // _FSW_FACEBASEDCOMPRESSFSW_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
