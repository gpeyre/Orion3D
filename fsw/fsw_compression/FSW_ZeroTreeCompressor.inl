/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_ZeroTreeCompressor.inl
 *  \brief  Inlined methods for \c FSW_ZeroTreeCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_ZeroTreeCompressor.h"

FSW_BEGIN_NAMESPACE


/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_ZeroTreeCompressor::FSW_ZeroTreeCompressor()
:	FSW_VertexBasedCompressor()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_ZeroTreeCompressor::~FSW_ZeroTreeCompressor()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::ComputeSignifiance
/**
 *  \param  CurVert [FSW_QuadTreeVertex&] The current vertex.
 *  \param  nThreshold [FSW_U32] The threshold to test for signifiance.
 *  \return [FSW_Bool] Is the part signifiant ?
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Test the signifiance of a single vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::ComputeSignifiance( FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );
	FSW_U32 nThreshold = 1<<nPass;
	FSW_I32 nVal = FSW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	return FSW_ABS(nVal)>=((FSW_I32) nThreshold);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::ComputeSignifiance
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \param  CompressionType [FSW_QuadTreeNode::T_NodeCompressionType] Type of node.
 *  \param  nThreshold [FSW_U32] Threshold.
 *  \return [FSW_Bool] Response.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Recursivly compute the signifiance of a part of a subtree (the 
 *  part depends on the compression type, either A or B).
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::ComputeSignifiance( FSW_QuadTreeNode& CurNode, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_U32 nThreshold = 1<<nPass;
	if( CurNode.GetCompressionType()==FSW_QuadTreeNode::kTypeA )
	{
		return FSW_ZeroTreeCompressor::ComputeSignifiance_Rec( CurNode, nPass );
	}
	else if( CurNode.GetCompressionType()==FSW_QuadTreeNode::kTypeB )
	{
		/* Type B : we must check for the child node of our child node */
		for( FSW_U32 i=0; i<4; ++i )
		{
			FSW_QuadTreeNode* pSonNode = CurNode.GetChildNode( i );
			FSW_ASSERT( pSonNode!=NULL );	// being of type B implies having sons
			FSW_Bool bResult = FSW_ZeroTreeCompressor::ComputeSignifiance_Rec( *pSonNode, nPass );
			if( bResult )
				return FSW_True;
		}
		return FSW_False;
	}
	else	/* shouldn't happened */
	{
		FSW_ASSERT( FSW_False );
		return FSW_False;
	}	
}


/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::ComputeSignifiance_Rec
/**
 *  \param  CurNode [FSW_QuadTreeNode&] Current node.
 *  \param  CompressionType [FSW_QuadTreeNode::T_NodeCompressionType] Type of node.
 *  \param  nThreshold [FSW_U32] Threshold.
 *  \return [FSW_Bool] Response.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Compute the signifiance of the tree under \c CurNode
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::ComputeSignifiance_Rec( FSW_QuadTreeNode& CurNode, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_U32 nThreshold = 1<<nPass;
	/* first check for the ones of the 3 vertices we own */
	for( FSW_U32 i=0; i<3; ++i )
	{
		if( CurNode.GetResponsabilityForVertex(i) )
		{
			FSW_QuadTreeVertex* pVert = CurNode.GetOwnedVertex( i );
			FSW_ASSERT( pVert!=NULL );
			if( pVert!=NULL )
			if( FSW_ZeroTreeCompressor::ComputeSignifiance( *pVert, nPass ) )
				return FSW_True;
		}
	}
	/* for both type we must check for the child nodes */
	for( FSW_U32 i=0; i<4; ++i )
	{
		FSW_QuadTreeNode* pNode = CurNode.GetChildNode( i );
		FSW_Bool bResult = FSW_False;
		if( pNode!=NULL )
			bResult = FSW_ZeroTreeCompressor::ComputeSignifiance_Rec( *pNode, nPass );
		if( bResult )
			return FSW_True;
	}
	return FSW_False;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::OuputSign
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  CurVert [FSW_QuadTreeVertex&] The vertex.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Output the sign of a vertex in the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_ZeroTreeCompressor::OuputSign( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_I32 nVal = FSW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	FSW_ASSERT( nVal!=0 );
	FSW_Bool bSign = (nVal>=0);

	#ifdef FSW_DEBUG
		BitStream.DebugPut( bSign, (FSW_U8) (kDebugToken_SignBit+nPass) );
	#else
		BitStream << bSign;
	#endif
}


/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::InputSign
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get a sign from the stream, and modify the value of the vertex 
 *  accordingly.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_ZeroTreeCompressor::InputSign( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bSign;
	
	#ifdef FSW_DEBUG
		FSW_U8 nDebugToken;
		BitStream.DebugGet( bSign, nDebugToken );
		FSW_ASSERT( nDebugToken==(kDebugToken_SignBit+nPass) );
	#else
		BitStream >> bSign;
	#endif

	FSW_VertexBasedCompressor::SetQuantifiedValueSign(CurVert, bSign);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::InputSignAndPredicValue
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  CurVert [FSW_QuadTreeVertex&] Current vertex.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get a sign from the stream, and modify the value of the vertex 
 *  accordingly, using the fact that 2^n <= Val < 2^(n+1).
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_ZeroTreeCompressor::InputSignAndPredicValue( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bSign;
	
	#ifdef FSW_DEBUG
		FSW_U8 nDebugToken;
		BitStream.DebugGet( bSign, nDebugToken );
		FSW_ASSERT( nDebugToken==(kDebugToken_SignBit+nPass) );
	#else
		BitStream >> bSign;
	#endif

	FSW_U32 nThreshold = 1<<nPass;
	FSW_I32 nVal = ((FSW_I32) (nThreshold*1.5));
	if( !bSign )
		nVal = -nVal;
	FSW_VertexBasedCompressor::SetQuantifiedValue(CurVert, nVal);
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::OuputBit
/**
 *  \param  rVal [FSW_Float] Current vertex.
 *  \param  nThreshold [FSW_U32] 2^(Number of the bit).
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Output a given bit of the absolute value of a vertex in the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_ZeroTreeCompressor::OuputBit( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_U32 nThreshold = 1<<nPass;
	FSW_I32 nIVal = FSW_VertexBasedCompressor::GetQuantifiedValue( CurVert );
	FSW_U32 nUVal = FSW_ABS( nIVal );
	FSW_Bool bBit = ((nUVal&nThreshold)==nThreshold);

	#ifdef FSW_DEBUG
		BitStream.DebugPut( bBit, (FSW_U8) (kDebugToken_RefinementBit+nPass) );
	#else
		BitStream << bBit;
	#endif

}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::InputBit
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  CurVert [FSW_QuadTreeVertex&] The current vertex.
 *  \param  nThreshold [FSW_U32] 2^(Number of the bit).
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get a bit from the stream and modify the value accordingly.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_ZeroTreeCompressor::InputBit( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bBit;

	#ifdef FSW_DEBUG
		FSW_U8 nDebugToken;
		BitStream.DebugGet( bBit, nDebugToken );
		FSW_ASSERT( nDebugToken==kDebugToken_RefinementBit+nPass );
	#else
		BitStream >> bBit;
	#endif

	/* Refinement pass */
	FSW_I32 nRefine;
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
	FSW_VertexBasedCompressor::AddAbsQuantifiedValue( CurVert, nRefine );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::OutputSignifiance_Vertex
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  CurVert [FSW_QuadTreeVertex&] The vertex.
 *  \param  nPass [FSW_U32] The number of the bit pass.
 *  \param  Token [T_CompressionDebugToken] The token to add to the stream in debug mode.
 *  \return [FSW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Compute the signifiance of the vertex, and then ouput it to the 
 *  stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::OutputSignifiance_Vertex( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bSignifiance = FSW_ZeroTreeCompressor::ComputeSignifiance( CurVert, nPass );
#ifdef FSW_DEBUG
	BitStream.DebugPut( bSignifiance, (FSW_U8) (kDebugToken_SignifianceVertex+nPass) );
#else
	BitStream << bSignifiance;
#endif
	return bSignifiance;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::OutputSignifiance_Vertex
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  nPass [FSW_U32] The number of the bit pass.
 *  \return [FSW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Get the signifiance of a vertex from a stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::InputSignifiance_Vertex( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bSignifiance;
#ifdef FSW_DEBUG
	FSW_U8 nDebugToken;
	BitStream.DebugGet( bSignifiance, nDebugToken );
	FSW_ASSERT( nDebugToken==(kDebugToken_SignifianceVertex+nPass) );
#else
	BitStream >> bSignifiance;
#endif
	return bSignifiance;
}




/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::OutputSignifiance_Node
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  CurNode [FSW_QuadTreeNode&] The node.
 *  \param  nPass [FSW_U32] The number of the bit pass.
 *  \param  Token [T_CompressionDebugToken] The token to add to the stream in debug mode.
 *  \return [FSW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Compute the signifiance of the node, and then ouput it to the 
 *  stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::OutputSignifiance_Node( FSW_BitStream& BitStream, FSW_QuadTreeNode& CurNode, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bSignifiance = FSW_ZeroTreeCompressor::ComputeSignifiance( CurNode, nPass );
#ifdef FSW_DEBUG
	/* choose the debug token according to the type of the node */
	T_CompressionDebugToken DebugTokenToCheck;
	if( CurNode.GetCompressionType()==FSW_QuadTreeNode::kTypeA )
		DebugTokenToCheck = kDebugToken_SignifianceNodeA;
	else
		DebugTokenToCheck = kDebugToken_SignifianceNodeB;
	/* put everything in the stream */
	BitStream.DebugPut( bSignifiance, (FSW_U8) (DebugTokenToCheck+nPass) );
#else
	BitStream << bSignifiance;
#endif
	return bSignifiance;
}
/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::OutputSignifiance_Node
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \param  nPass [FSW_U32] The number of the bit pass.
 *  \return [FSW_Bool] The signifiance of the vertex.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Get the signifiance of a node from a stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_ZeroTreeCompressor::InputSignifiance_Node( FSW_BitStream& BitStream, FSW_QuadTreeNode& CurNode, FSW_U32 nPass )
{
	FSW_ASSERT( nPass<=FSW_MAX_NBR_BITPLANES );

	FSW_Bool bSignifiance;
#ifdef FSW_DEBUG
	/* choose the debug token according to the type of the node */
	T_CompressionDebugToken DebugTokenToCheck;
	if( CurNode.GetCompressionType()==FSW_QuadTreeNode::kTypeA )
		DebugTokenToCheck = kDebugToken_SignifianceNodeA;
	else
		DebugTokenToCheck = kDebugToken_SignifianceNodeB;
	/* get everything from the stream */
	FSW_U8 nDebugToken;
	BitStream.DebugGet( bSignifiance, nDebugToken );
	FSW_ASSERT( nDebugToken==(DebugTokenToCheck+nPass) );
#else
	BitStream >> bSignifiance;
#endif
	return bSignifiance;
}



FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
