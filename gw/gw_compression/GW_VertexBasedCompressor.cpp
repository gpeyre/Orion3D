/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_VertexBasedCompressor.cpp
 *  \brief  Definition of class \c GW_VertexBasedCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_VertexBasedCompressor.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_VertexBasedCompressor.h"
#include "GW_CompressionHeader.h"


using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  constructor.
 */
/*------------------------------------------------------------------------------*/
GW_VertexBasedCompressor::GW_VertexBasedCompressor()
:	GW_Compressor_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_VertexBasedCompressor::~GW_VertexBasedCompressor()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::void ApplyFunctionOnVertex
/**
 *  \param  Tree [GW_QuadTree&] The tree.
 *  \param  pFunc [T_FunctionApplyableOnVertex] The function to apply.
 *  \param  pChunk [void*] An eventual parameter.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Apply a function on each vertex of the tree.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::ApplyFunctionOnVertex(GW_QuadTree& QuadTree, T_FunctionApplyableOnVertex pFunc, void* pChunk)
{
	GW_U32 nDepth = QuadTree.GetDepth();

	/* first, we must deal with the base vertex of the octaedron */
	T_QuadTreeVertexVector BaseVertexVector = QuadTree.GetBaseVertexVector();
	for( IT_QuadTreeVertexVector it=BaseVertexVector.begin(); it!=BaseVertexVector.end(); ++it )
	{
		GW_QuadTreeVertex* pVert = *it;
		GW_ASSERT( pVert!=NULL );
		pFunc( *pVert, pChunk, 0 );
	}
	/* There is no need to iterate on the last level, since there is no owned vertex for this one. */	
	for( GW_U32 nCurDepth=0; nCurDepth<nDepth; ++nCurDepth )
	{
		GW_ASSERT( QuadTree.NodeMapExist( nCurDepth ) );
		GW_NodeMap& NodeMapVector = QuadTree.GetNodeMap( nCurDepth );
		T_QuadTreeNodeMap& NodeMap = NodeMapVector.GetMap();
		/* recurse on each node */
		for( IT_QuadTreeNodeMap NodeTreeMapIT=NodeMap.begin(); NodeTreeMapIT!=NodeMap.end(); ++NodeTreeMapIT )
		{
			/* get the node */
			GW_QuadTreeNode* pNode = NodeTreeMapIT->second;
			GW_ASSERT( pNode!=NULL );
			/* check each vertex */
			for( GW_U32 i=0; i<3; ++i )
			{
				if( pNode->GetResponsabilityForVertex(i) )
				{
					GW_QuadTreeVertex* pVert = pNode->GetOwnedVertex( i );
					GW_ASSERT( pVert!=NULL );
					pFunc( *pVert, pChunk, nCurDepth+1 );
				}
			}
		}
	}
}


/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::ComputeMaxCoefValue
/**
 *  \param  QuadTree [GW_QuadTree&] The tree.
 *  \return [GW_Float] The maximum value.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Compute the maximum value of the coefficient in the tree.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::ComputeMaxCoefValue( GW_QuadTree& QuadTree, GW_CompressionHeader& QuantificationHeader )
{
	GW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, GW_VertexBasedCompressor::ComputeMaxCoefValue_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::ComputeMaxCoefValue_Helper
/**
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::ComputeMaxCoefValue_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth )
{
	GW_CompressionHeader* pHeader = (GW_CompressionHeader*) pChunk;
	GW_ASSERT( pHeader!=NULL );
	if( GW_ABS(CurVert.GetValue())>pHeader->GetMaxCoefValue() )
		pHeader->SetMaxCoefValue( GW_ABS(CurVert.GetValue()) );
}


/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::Quantification
/**
 *  \param  QuadTree [GW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [GW_CompressionHeader&] Contains information about quantification to perform.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Quantify the value of each vertice.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::Quantification( GW_QuadTree& QuadTree, GW_CompressionHeader& QuantificationHeader )
{
	GW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, GW_VertexBasedCompressor::Quantification_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::Quantification_Helper
/**
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::Quantification_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth )
{
	GW_CompressionHeader* pHeader = (GW_CompressionHeader*) pChunk;
	GW_ASSERT( pHeader!=NULL );
	GW_Float rVal = CurVert.GetValue();
	GW_I32 nSign = 1;
	if( rVal<0 )
		nSign = -1;
	GW_U32 nMaxPrec = 1;
	nMaxPrec <<= pHeader->GetNbrBitPlane()+1;
	nMaxPrec -= 1;	// 2^(n+1)-1
	GW_ASSERT( pHeader->GetMaxCoefValue()>0 );
	GW_I32 nVal = (GW_I32) floor( GW_ABS(rVal)*nMaxPrec/pHeader->GetMaxCoefValue() );
	GW_ASSERT( GW_ABS(nVal) < (1<<(pHeader->GetNbrBitPlane()+1)) );
	/* quick and dirty trick : we use the vertex slot to hold the quantized value. */
	GW_VertexBasedCompressor::SetQuantifiedValue( CurVert, nVal*nSign );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::UnQuantification
/**
 *  \param  QuadTree [GW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [GW_CompressionHeader&] Contains information about quantification to perform.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  UnQuantify the value of each vertice.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::UnQuantification( GW_QuadTree& QuadTree, GW_CompressionHeader& QuantificationHeader )
{
	GW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, GW_VertexBasedCompressor::UnQuantification_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::Quantification_Helper
/**
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::UnQuantification_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth )
{
	GW_CompressionHeader* pHeader = (GW_CompressionHeader*) pChunk;
	GW_ASSERT( pHeader!=NULL );
	GW_I32 nVal = GW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	GW_ASSERT( GW_ABS(nVal) < (1<<(pHeader->GetNbrBitPlane()+1)) );
	GW_U32 nMaxPrec = 1;
	nMaxPrec <<= pHeader->GetNbrBitPlane()+1;
	nMaxPrec -= 1;	// 2^(n+1)-1
	GW_ASSERT( pHeader->GetMaxCoefValue()>0 );
	GW_Float rVal = (nVal*pHeader->GetMaxCoefValue())/nMaxPrec;
	GW_ASSERT( GW_ABS(rVal)<=pHeader->GetMaxCoefValue() );
	/* quick and dirty trick : we use the vertex slot to hold the quantized value. */
	CurVert.SetValue( rVal );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::Scaling
/**
 *  \param  QuadTree [GW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [GW_CompressionHeader&] Contains information about how to perform scaling.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Perform scaling before quantification.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::Scaling( GW_QuadTree& QuadTree, GW_CompressionHeader& QuantificationHeader )
{
	if( QuantificationHeader.GetScalingType()==GW_Compressor_ABC::kNormInf )	// no scaling here.
		return;
	GW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, GW_VertexBasedCompressor::Scaling_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::Scaling_Helper
/**
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::Scaling_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth )
{
	GW_CompressionHeader* pHeader = (GW_CompressionHeader*) pChunk;
	GW_ASSERT( pHeader!=NULL );
	GW_U32 nScaleFactor = 1;
	switch( pHeader->GetScalingType() ) 
	{
	case GW_Compressor_ABC::kNormL1:	//	Scaling by 4^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		nScaleFactor *= nScaleFactor;	//	4^(depth)
		CurVert.SetValue( CurVert.GetValue()/nScaleFactor );
		break;
	case GW_Compressor_ABC::kNormL2:	//	Scaling by 2^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		CurVert.SetValue( CurVert.GetValue()/nScaleFactor );
		break;
	case GW_Compressor_ABC::kNormInf:
		/* No scaling for Linf norm */
		break;
	default:
		GW_ASSERT( GW_False );
		break;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::UnScaling
/**
 *  \param  QuadTree [GW_QuadTree&] The quadtree to compress.
 *  \param  QuantificationHeader [GW_CompressionHeader&] Contains information about how to perform unscaling.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Perform unscaling before quantification.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::UnScaling( GW_QuadTree& QuadTree, GW_CompressionHeader& QuantificationHeader )
{
	if( QuantificationHeader.GetScalingType()==GW_Compressor_ABC::kNormInf )	// no scaling here.
		return;
	GW_VertexBasedCompressor::ApplyFunctionOnVertex( QuadTree, GW_VertexBasedCompressor::UnScaling_Helper, &QuantificationHeader );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::Quantification_Helper
/**
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \param  pChunk [void*] Parameter. Shouldn't be null. In fact this MUST be a compression header.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Function recursivly called on each vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::UnScaling_Helper( GW_QuadTreeVertex& CurVert, void* pChunk, GW_U32 nDepth )
{
	GW_CompressionHeader* pHeader = (GW_CompressionHeader*) pChunk;
	GW_ASSERT( pHeader!=NULL );
	GW_U32 nScaleFactor = 1;
	switch( pHeader->GetScalingType() ) 
	{
	case GW_Compressor_ABC::kNormL1:	//	Scaling by 4^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		nScaleFactor *= nScaleFactor;	//	4^(depth)
		CurVert.SetValue( CurVert.GetValue()*nScaleFactor );
		break;
	case GW_Compressor_ABC::kNormL2:	//	Scaling by 2^(-depth)
		nScaleFactor <<= nDepth;		//	2^(depth)
		CurVert.SetValue( CurVert.GetValue()*nScaleFactor );
		break;
	case GW_Compressor_ABC::kNormInf:
		/* No scaling for Linf norm */
		break;
	default:
		GW_ASSERT( GW_False );
		break;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::GetQuantifiedValue
/**
 *  \param  Vert [GW_QuadTreeVertex&] The vertex.
 *  \return [GW_I32] The value.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the value of a vertex stored as an \c int.
 *	This is useful since in fact the value is stored in a \c float.
 */
/*------------------------------------------------------------------------------*/
GW_I32 GW_VertexBasedCompressor::GetQuantifiedValue( const GW_QuadTreeVertex& Vert )
{
#ifdef GW_DEBUG
	return Vert.GetQuantifiedValue();
#else
	GW_I32 nVal;
	GW_Float rVal = Vert.GetValue();
	memcpy( &nVal, &rVal, sizeof(GW_I32) );
	return nVal;
#endif	// #ifdef GW_DEBUG
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::GetQuantifiedValue
/**
 *  \param  Vert [GW_QuadTreeVertex&] The vertex.
 *  \param  nVal [GW_I32] The value.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the value of a vertex stored as an \c int.
 *	This is useful since in fact the value is stored in a \c float.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::SetQuantifiedValue( GW_QuadTreeVertex& Vert, GW_I32 nVal )
{
#ifdef GW_DEBUG
	Vert.SetQuantifiedValue( nVal );
#else
	GW_Float rVal = 0;
	memcpy( &rVal, &nVal, sizeof(GW_I32) );
	Vert.SetValue( rVal );
#endif // #ifdef GW_DEBUG
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::SetQuantifiedValueSign
/**
 *  \param  Vert [GW_QuadTreeVertex&] The vertex.
 *  \param  bSign [GW_Bool] The sign.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the sign of the vertex value.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::SetQuantifiedValueSign( GW_QuadTreeVertex& Vert, GW_Bool bSign )
{
	GW_I32 nVal = GW_VertexBasedCompressor::GetQuantifiedValue( Vert );
	GW_ASSERT( nVal!=0 );
	if( bSign )
		GW_VertexBasedCompressor::SetQuantifiedValue( Vert, GW_ABS(nVal) );
	else
		GW_VertexBasedCompressor::SetQuantifiedValue( Vert, -GW_ABS(nVal) );
}

/*------------------------------------------------------------------------------*/
// Name : GW_VertexBasedCompressor::AddAbsQuantifiedValue
/**
 *  \param  Vert [GW_QuadTreeVertex&] Vertex.
 *  \param  nAddVal [GW_I32] Value to add.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Add a given value to the quantified absolute value of the vertex.
 */
/*------------------------------------------------------------------------------*/
void GW_VertexBasedCompressor::AddAbsQuantifiedValue( GW_QuadTreeVertex& Vert, GW_I32 nAddVal )
{
	GW_I32 nVal = GW_VertexBasedCompressor::GetQuantifiedValue( Vert );
	GW_I32 nSign = 1;
	if( nVal<0 )
		nSign = -1;
	nVal = (GW_ABS( nVal ) + nAddVal)*nSign;
	GW_ASSERT( nVal*nSign>0 );
	GW_VertexBasedCompressor::SetQuantifiedValue( Vert, nVal );
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
