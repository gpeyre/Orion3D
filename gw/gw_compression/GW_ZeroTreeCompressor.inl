/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_ZeroTreeCompressor.inl
 *  \brief  Inlined methods for \c GW_ZeroTreeCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_ZeroTreeCompressor.h"

GW_BEGIN_NAMESPACE


/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_ZeroTreeCompressor::GW_ZeroTreeCompressor()
:	GW_VertexBasedCompressor()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_ZeroTreeCompressor::~GW_ZeroTreeCompressor()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::ComputeSignifiance
/**
 *  \param  CurVert [GW_QuadTreeVertex&] The current vertex.
 *  \param  nThreshold [GW_U32] The threshold to test for signifiance.
 *  \return [GW_Bool] Is the part signifiant ?
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Test the signifiance of a single vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::ComputeSignifiance( GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );
	GW_U32 nThreshold = 1<<nPass;
	GW_I32 nVal = GW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	return GW_ABS(nVal)>=((GW_I32) nThreshold);
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::ComputeSignifiance
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \param  CompressionType [GW_QuadTreeNode::T_NodeCompressionType] Type of node.
 *  \param  nThreshold [GW_U32] Threshold.
 *  \return [GW_Bool] Response.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Recursivly compute the signifiance of a part of a subtree (the 
 *  part depends on the compression type, either A or B).
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::ComputeSignifiance( GW_QuadTreeNode& CurNode, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_U32 nThreshold = 1<<nPass;
	if( CurNode.GetCompressionType()==GW_QuadTreeNode::kTypeA )
	{
		return GW_ZeroTreeCompressor::ComputeSignifiance_Rec( CurNode, nPass );
	}
	else if( CurNode.GetCompressionType()==GW_QuadTreeNode::kTypeB )
	{
		/* Type B : we must check for the child node of our child node */
		for( GW_U32 i=0; i<4; ++i )
		{
			GW_QuadTreeNode* pSonNode = CurNode.GetChildNode( i );
			GW_ASSERT( pSonNode!=NULL );	// being of type B implies having sons
			GW_Bool bResult = GW_ZeroTreeCompressor::ComputeSignifiance_Rec( *pSonNode, nPass );
			if( bResult )
				return GW_True;
		}
		return GW_False;
	}
	else	/* shouldn't happened */
	{
		GW_ASSERT( GW_False );
		return GW_False;
	}	
}


/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::ComputeSignifiance_Rec
/**
 *  \param  CurNode [GW_QuadTreeNode&] Current node.
 *  \param  CompressionType [GW_QuadTreeNode::T_NodeCompressionType] Type of node.
 *  \param  nThreshold [GW_U32] Threshold.
 *  \return [GW_Bool] Response.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Compute the signifiance of the tree under \c CurNode
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::ComputeSignifiance_Rec( GW_QuadTreeNode& CurNode, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_U32 nThreshold = 1<<nPass;
	/* first check for the ones of the 3 vertices we own */
	for( GW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			GW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			GW_ASSERT( pVert!=NULL );
			if( pVert!=NULL )
			if( GW_ZeroTreeCompressor::ComputeSignifiance( *pVert, nPass ) )
				return GW_True;
		}
	}
	/* for both type we must check for the child nodes */
	for( GW_U32 i=0; i<4; ++i )
	{
		GW_QuadTreeNode* pNode = CurNode.GetChildNode( i );
		GW_Bool bResult = GW_False;
		if( pNode!=NULL )
			bResult = GW_ZeroTreeCompressor::ComputeSignifiance_Rec( *pNode, nPass );
		if( bResult )
			return GW_True;
	}
	return GW_False;
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::OuputSign
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  CurVert [GW_QuadTreeVertex&] The vertex.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Output the sign of a vertex in the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_ZeroTreeCompressor::OuputSign( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_I32 nVal = GW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	GW_ASSERT( nVal!=0 );
	GW_Bool bSign = (nVal>=0);

	#ifdef GW_DEBUG
		BitStream.DebugPut( bSign, (GW_U8) (kDebugToken_SignBit+nPass) );
	#else
		BitStream << bSign;
	#endif
}


/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::InputSign
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get a sign from the stream, and modify the value of the vertex 
 *  accordingly.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_ZeroTreeCompressor::InputSign( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bSign;
	
	#ifdef GW_DEBUG
		GW_U8 nDebugToken;
		BitStream.DebugGet( bSign, nDebugToken );
		GW_ASSERT( nDebugToken==(kDebugToken_SignBit+nPass) );
	#else
		BitStream >> bSign;
	#endif

	GW_VertexBasedCompressor::SetQuantifiedValueSign(CurVert, bSign);
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::InputSignAndPredicValue
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  CurVert [GW_QuadTreeVertex&] Current vertex.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get a sign from the stream, and modify the value of the vertex 
 *  accordingly, using the fact that 2^n <= Val < 2^(n+1).
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_ZeroTreeCompressor::InputSignAndPredicValue( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bSign;
	
	#ifdef GW_DEBUG
		GW_U8 nDebugToken;
		BitStream.DebugGet( bSign, nDebugToken );
		GW_ASSERT( nDebugToken==(kDebugToken_SignBit+nPass) );
	#else
		BitStream >> bSign;
	#endif

	GW_U32 nThreshold = 1<<nPass;
	GW_I32 nVal = ((GW_I32) (nThreshold*1.5));
	if( !bSign )
		nVal = -nVal;
	GW_VertexBasedCompressor::SetQuantifiedValue(CurVert, nVal);
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::OuputBit
/**
 *  \param  rVal [GW_Float] Current vertex.
 *  \param  nThreshold [GW_U32] 2^(Number of the bit).
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Output a given bit of the absolute value of a vertex in the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_ZeroTreeCompressor::OuputBit( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_U32 nThreshold = 1<<nPass;
	GW_I32 nIVal = GW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	GW_U32 nUVal = GW_ABS( nIVal );
	GW_Bool bBit = ((nUVal&nThreshold)==nThreshold);

	#ifdef GW_DEBUG
		BitStream.DebugPut( bBit, (GW_U8) (kDebugToken_RefinementBit+nPass) );
	#else
		BitStream << bBit;
	#endif

}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::InputBit
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  CurVert [GW_QuadTreeVertex&] The current vertex.
 *  \param  nThreshold [GW_U32] 2^(Number of the bit).
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get a bit from the stream and modify the value accordingly.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_ZeroTreeCompressor::InputBit( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bBit;

	#ifdef GW_DEBUG
		GW_U8 nDebugToken;
		BitStream.DebugGet( bBit, nDebugToken );
		GW_ASSERT( nDebugToken==kDebugToken_RefinementBit+nPass );
	#else
		BitStream >> bBit;
	#endif

	/* Refinement pass */
	GW_I32 nRefine;
	if( nPass>0 )
	{
		nRefine = 1<<(nPass-1);
		if( !bBit )
			nRefine = -nRefine;
	}
	else
	{
		if( !bBit )
			nRefine = -1;
		else
			nRefine = 0;
	}
	GW_VertexBasedCompressor::AddAbsQuantifiedValue( CurVert, nRefine );
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::OutputSignifiance_Vertex
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  CurVert [GW_QuadTreeVertex&] The vertex.
 *  \param  nPass [GW_U32] The number of the bit pass.
 *  \param  Token [T_CompressionDebugToken] The token to add to the stream in debug mode.
 *  \return [GW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Compute the signifiance of the vertex, and then ouput it to the 
 *  stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::OutputSignifiance_Vertex( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bSignifiance = GW_ZeroTreeCompressor::ComputeSignifiance( CurVert, nPass );
#ifdef GW_DEBUG
	BitStream.DebugPut( bSignifiance, (GW_U8) (kDebugToken_SignifianceVertex+nPass) );
#else
	BitStream << bSignifiance;
#endif
	return bSignifiance;
}

/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::OutputSignifiance_Vertex
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  nPass [GW_U32] The number of the bit pass.
 *  \return [GW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Get the signifiance of a vertex from a stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::InputSignifiance_Vertex( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bSignifiance;
#ifdef GW_DEBUG
	GW_U8 nDebugToken;
	BitStream.DebugGet( bSignifiance, nDebugToken );
	GW_ASSERT( nDebugToken==(kDebugToken_SignifianceVertex+nPass) );
#else
	BitStream >> bSignifiance;
#endif
	return bSignifiance;
}




/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::OutputSignifiance_Node
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  CurNode [GW_QuadTreeNode&] The node.
 *  \param  nPass [GW_U32] The number of the bit pass.
 *  \param  Token [T_CompressionDebugToken] The token to add to the stream in debug mode.
 *  \return [GW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Compute the signifiance of the node, and then ouput it to the 
 *  stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::OutputSignifiance_Node( GW_BitStream& BitStream, GW_QuadTreeNode& CurNode, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bSignifiance = GW_ZeroTreeCompressor::ComputeSignifiance( CurNode, nPass );
#ifdef GW_DEBUG
	/* choose the debug token according to the type of the node */
	T_CompressionDebugToken DebugTokenToCheck;
	if( CurNode.GetCompressionType()==GW_QuadTreeNode::kTypeA )
		DebugTokenToCheck = kDebugToken_SignifianceNodeA;
	else
		DebugTokenToCheck = kDebugToken_SignifianceNodeB;
	/* put everything in the stream */
	BitStream.DebugPut( bSignifiance, (GW_U8) (DebugTokenToCheck+nPass) );
#else
	BitStream << bSignifiance;
#endif
	return bSignifiance;
}
/*------------------------------------------------------------------------------*/
// Name : GW_ZeroTreeCompressor::OutputSignifiance_Node
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \param  nPass [GW_U32] The number of the bit pass.
 *  \return [GW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Get the signifiance of a node from a stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_ZeroTreeCompressor::InputSignifiance_Node( GW_BitStream& BitStream, GW_QuadTreeNode& CurNode, GW_U32 nPass )
{
	GW_ASSERT( nPass<=GW_MAX_NBR_BITPLANES );

	GW_Bool bSignifiance;
#ifdef GW_DEBUG
	/* choose the debug token according to the type of the node */
	T_CompressionDebugToken DebugTokenToCheck;
	if( CurNode.GetCompressionType()==GW_QuadTreeNode::kTypeA )
		DebugTokenToCheck = kDebugToken_SignifianceNodeA;
	else
		DebugTokenToCheck = kDebugToken_SignifianceNodeB;
	/* get everything from the stream */
	GW_U8 nDebugToken;
	BitStream.DebugGet( bSignifiance, nDebugToken );
	GW_ASSERT( nDebugToken==(DebugTokenToCheck+nPass) );
#else
	BitStream >> bSignifiance;
#endif
	return bSignifiance;
}



GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
