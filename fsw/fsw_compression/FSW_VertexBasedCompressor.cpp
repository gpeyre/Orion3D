/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_VertexBasedCompressor.cpp
 *  \brief  Definition of class \c FSW_VertexBasedCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_VertexBasedCompressor.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_VertexBasedCompressor.h"
#include "FSW_CompressionHeader.h"


using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_VertexBasedCompressor::FSW_VertexBasedCompressor()
:	FSW_Compressor_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_VertexBasedCompressor::~FSW_VertexBasedCompressor()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::void ApplyFunctionOnVertex
/**
 *  \param  Tree [FSW_QuadTree&] The tree.
 *  \param  pFunc [T_FunctionApplyableOnVertex] The function to apply.
 *  \param  pChunk [void*] An eventual parameter.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Apply a function on each vertex of the tree.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::ApplyFunctionOnVertex(FSW_QuadTree& QuadTree, T_FunctionApplyableOnVertex pFunc, void* pChunk)
{
	FSW_U32 nDepth = QuadTree.GetDepth();

	/* first, we must deal with the base vertex of the octaedron */
	T_QuadTreeVertexVector BaseVertexVector = QuadTree.GetBaseVertexVector();
	for( IT_QuadTreeVertexVector it=BaseVertexVector.begin(); it!=BaseVertexVector.end(); ++it )
	{
		FSW_QuadTreeVertex* pVert = *it;
		FSW_ASSERT( pVert!=NULL );
		pFunc( *pVert, pChunk, 0 );
	}
	/* There is no need to iterate on the last level, since there is no owned vertex for this one. */	
	for( FSW_U32 nCurDepth=0; nCurDepth<nDepth; ++nCurDepth )
	{
		FSW_ASSERT( QuadTree.NodeMapExist( nCurDepth ) );
		FSW_NodeMap& NodeMapVector = QuadTree.GetNodeMap( nCurDepth );
		T_QuadTreeNodeMap& NodeMap = NodeMapVector.GetMap();
		/* recurse on each node */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=NodeMap.begin(); NodeTreeMapIT!=NodeMap.end(); ++NodeTreeMapIT )
		{
			/* get the node */
			FSW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			FSW_ASSERT( pNode!=NULL );
			/* check each vertex */
			for( FSW_U32 i=0; i<3; ++i )
			{
				if( pNode->GetResponsabilityForVertex(i) )
				{
					FSW_QuadTreeVertex* pVert = pNode->GetOwnedVertex( i );
					FSW_ASSERT( pVert!=NULL );
					pFunc( *pVert, pChunk, nCurDepth+1 );
				}
			}
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::ComputeMaxCoefValue
/**
 *  \param  QuadTree [FSW_QuadTree&] The tree.
 *  \return [FSW_Float] The maximum value.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Compute the maximum value of the coefficient in the tree.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::ComputeMaxCoefValue( FSW_QuadTree& QuadTree, FSW_CompressionHeader& QuantificationHeader )
{
	FSW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, FSW_VertexBasedCompressor::ComputeMaxCoefValue_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::ComputeMaxCoefValue_Helper
/**
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::ComputeMaxCoefValue_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth )
{
	FSW_CompressionHeader* pHeader = (FSW_CompressionHeader*) pChunk;
	FSW_ASSERT( pHeader!=NULL );
	if( FSW_ABS(CurVert.GetValue())>pHeader->GetMaxCoefValue() )
		pHeader->SetMaxCoefValue( FSW_ABS(CurVert.GetValue()) );
}


/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::Quantification
/**
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [FSW_CompressionHeader&] Contains information about quantification to perform.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Quantify the value of each vertice.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::Quantification( FSW_QuadTree& QuadTree, FSW_CompressionHeader& QuantificationHeader )
{
	FSW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, FSW_VertexBasedCompressor::Quantification_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::Quantification_Helper
/**
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::Quantification_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth )
{
	FSW_CompressionHeader* pHeader = (FSW_CompressionHeader*) pChunk;
	FSW_ASSERT( pHeader!=NULL );
	FSW_Float rVal = CurVert.GetValue();
	FSW_I32 nSign = 1;
	if( rVal<0 )
		nSign = -1;
	FSW_U32 nMaxPrec = 1;
	nMaxPrec <<= pHeader->GetNbrBitPlane()+1;
	nMaxPrec -= 1;	// 2^(n+1)-1
	FSW_ASSERT( pHeader->GetMaxCoefValue()>0 );
	FSW_I32 nVal = (FSW_I32) floor( FSW_ABS(rVal)*nMaxPrec/pHeader->GetMaxCoefValue() );
	FSW_ASSERT( FSW_ABS(nVal) < (1<<(pHeader->GetNbrBitPlane()+1)) );
	/* quick and dirty trick : we use the vertex slot to hold the quantized value. */
	FSW_VertexBasedCompressor::SetQuantifiedValue( CurVert, nVal*nSign );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::UnQuantification
/**
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [FSW_CompressionHeader&] Contains information about quantification to perform.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  UnQuantify the value of each vertice.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::UnQuantification( FSW_QuadTree& QuadTree, FSW_CompressionHeader& QuantificationHeader )
{
	FSW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, FSW_VertexBasedCompressor::UnQuantification_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::Quantification_Helper
/**
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::UnQuantification_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth )
{
	FSW_CompressionHeader* pHeader = (FSW_CompressionHeader*) pChunk;
	FSW_ASSERT( pHeader!=NULL );
	FSW_I32 nVal = FSW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	FSW_ASSERT( FSW_ABS(nVal) < (1<<(pHeader->GetNbrBitPlane()+1)) );
	FSW_U32 nMaxPrec = 1;
	nMaxPrec <<= pHeader->GetNbrBitPlane()+1;
	nMaxPrec -= 1;	// 2^(n+1)-1
	FSW_ASSERT( pHeader->GetMaxCoefValue()>0 );
	FSW_Float rVal = (nVal*pHeader->GetMaxCoefValue())/nMaxPrec;
	FSW_ASSERT( FSW_ABS(rVal)<=pHeader->GetMaxCoefValue() );
	/* quick and dirty trick : we use the vertex slot to hold the quantized value. */
	CurVert.SetValue( rVal );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::Scaling
/**
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [FSW_CompressionHeader&] Contains information about how to perform scaling.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Perform scaling before quantification.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::Scaling( FSW_QuadTree& QuadTree, FSW_CompressionHeader& QuantificationHeader )
{
	if( QuantificationHeader.GetScalingType()==FSW_Compressor_ABC::kNormInf )	// no scaling here.
		return;
	FSW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, FSW_VertexBasedCompressor::Scaling_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::Scaling_Helper
/**
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::Scaling_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth )
{
	FSW_CompressionHeader* pHeader = (FSW_CompressionHeader*) pChunk;
	FSW_ASSERT( pHeader!=NULL );
	FSW_U32 nScaleFactor = 1;
	switch( pHeader->GetScalingType() ) 
	{
	case FSW_Compressor_ABC::kNormL1:	//	Scaling by 4^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		nScaleFactor *= nScaleFactor;	//	4^(depth)
		CurVert.SetValue( CurVert.GetValue()/nScaleFactor );
		break;
	case FSW_Compressor_ABC::kNormL2:	//	Scaling by 2^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		CurVert.SetValue( CurVert.GetValue()/nScaleFactor );
		break;
	case FSW_Compressor_ABC::kNormInf:
		/* No scaling for Linf norm */
		break;
	default:
		FSW_ASSERT( FSW_False );
		break;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::UnScaling
/**
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [FSW_CompressionHeader&] Contains information about how to perform unscaling.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Perform unscaling before quantification.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::UnScaling( FSW_QuadTree& QuadTree, FSW_CompressionHeader& QuantificationHeader )
{
	if( QuantificationHeader.GetScalingType()==FSW_Compressor_ABC::kNormInf )	// no scaling here.
		return;
	FSW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, FSW_VertexBasedCompressor::UnScaling_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::Quantification_Helper
/**
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::UnScaling_Helper( FSW_QuadTreeVertex& CurVert, void* pChunk, FSW_U32 nDepth )
{
	FSW_CompressionHeader* pHeader = (FSW_CompressionHeader*) pChunk;
	FSW_ASSERT( pHeader!=NULL );
	FSW_U32 nScaleFactor = 1;
	switch( pHeader->GetScalingType() ) 
	{
	case FSW_Compressor_ABC::kNormL1:	//	Scaling by 4^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		nScaleFactor *= nScaleFactor;	//	4^(depth)
		CurVert.SetValue( CurVert.GetValue()*nScaleFactor );
		break;
	case FSW_Compressor_ABC::kNormL2:	//	Scaling by 2^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		CurVert.SetValue( CurVert.GetValue()*nScaleFactor );
		break;
	case FSW_Compressor_ABC::kNormInf:
		/* No scaling for Linf norm */
		break;
	default:
		FSW_ASSERT( FSW_False );
		break;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::GetQuantifiedValue
/**
 *  \param  Vert [FSW_QuadTreeVertex&] The vertex.
 *  \return [FSW_I32] The value.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the value of a vertex stored as an \c int.
 *	This is useful since in fact the value is stored in a \c float.
 */
/*------------------------------------------------------------------------------*/
FSW_I32 FSW_VertexBasedCompressor::GetQuantifiedValue( const FSW_QuadTreeVertex& Vert )
{
#ifdef FSW_DEBUG
	return Vert.GetQuantifiedValue();
#else
	FSW_I32 nVal;
	FSW_Float rVal = Vert.GetValue();
	memcpy( &nVal, &rVal, sizeof(FSW_I32) );
	return nVal;
#endif	// #ifdef FSW_DEBUG
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::GetQuantifiedValue
/**
 *  \param  Vert [FSW_QuadTreeVertex&] The vertex.
 *  \param  nVal [FSW_I32] The value.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the value of a vertex stored as an \c int.
 *	This is useful since in fact the value is stored in a \c float.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::SetQuantifiedValue( FSW_QuadTreeVertex& Vert, FSW_I32 nVal )
{
#ifdef FSW_DEBUG
	Vert.SetQuantifiedValue( nVal );
#else
	FSW_Float rVal = 0;
	memcpy( &rVal, &nVal, sizeof(FSW_I32) );
	Vert.SetValue( rVal );
#endif // #ifdef FSW_DEBUG
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::SetQuantifiedValueSign
/**
 *  \param  Vert [FSW_QuadTreeVertex&] The vertex.
 *  \param  bSign [FSW_Bool] The sign.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the sign of the vertex value.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::SetQuantifiedValueSign( FSW_QuadTreeVertex& Vert, FSW_Bool bSign )
{
	FSW_I32 nVal = FSW_VertexBasedCompressor::GetQuantifiedValue( Vert );
	FSW_ASSERT( nVal!=0 );
	if( bSign )
		FSW_VertexBasedCompressor::SetQuantifiedValue( Vert, FSW_ABS(nVal) );
	else
		FSW_VertexBasedCompressor::SetQuantifiedValue( Vert, -FSW_ABS(nVal) );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_VertexBasedCompressor::AddAbsQuantifiedValue
/**
 *  \param  Vert [FSW_QuadTreeVertex&] Vertex.
 *  \param  nAddVal [FSW_I32] Value to add.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Add a given value to the quantified absolute value of the vertex.
 */
/*------------------------------------------------------------------------------*/
void FSW_VertexBasedCompressor::AddAbsQuantifiedValue( FSW_QuadTreeVertex& Vert, FSW_I32 nAddVal )
{
	FSW_I32 nVal = FSW_VertexBasedCompressor::GetQuantifiedValue( Vert );
	FSW_I32 nSign = 1;
	if( nVal<0 )
		nSign = -1;
	nVal = (FSW_ABS( nVal ) + nAddVal)*nSign;
	FSW_ASSERT( nVal*nSign>0 );
	FSW_VertexBasedCompressor::SetQuantifiedValue( Vert, nVal );
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
