/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_ZeroTreeCompressor.cpp
 *  \brief  Definition of class \c FSW_ZeroTreeCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_ZeroTreeCompressor.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_ZeroTreeCompressor.h"

#ifndef FSW_USE_INLINE
    #include "FSW_ZeroTreeCompressor.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::Compress
/**
 *  \param  BitStream [FSW_BitStream&] The bitstream.
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \param  nNbrBitPlanes [FSW_U8] The number of bit used for quantification.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Compress the quadtree into a bitstream.
 *
 *	\b Important : The tree must be full.
 */
/*------------------------------------------------------------------------------*/
void FSW_ZeroTreeCompressor::Compress( FSW_BitStream& BitStream, FSW_QuadTree& QuadTree, FSW_U32 nNbrBitPlanes, T_ScalingType ScalingType )
{
	FSW_CompressionHeader CompressionHeader;
	FSW_ASSERT( nNbrBitPlanes<=FSW_MAX_NBR_BITPLANES );

	#define CHECK_AND_EXIT																			\
	if( pCompressionCallback_PerBit_!=NULL )														\
	{																								\
		if( !pCompressionCallback_PerBit_(BitStream, QuadTree, (FSW_U8) nPass) )					\
		{	UnQuantification(QuadTree,CompressionHeader);UnScaling(QuadTree,CompressionHeader);		\
			LSP_.clear();LIS_.clear();LIP_.clear(); return; } }

	/* first fill the header ***************************************************/
	CompressionHeader.SetNbrBitPlane( nNbrBitPlanes );
	CompressionHeader.SetScalingType( ScalingType );
	CompressionHeader.SetTreeDepth( QuadTree.GetDepth() );
	CompressionHeader.SetCompressorName( this->GetCompressorName() );
	CompressionHeader.SetBaseMeshName( QuadTree.GetBaseMesh().GetBaseMeshName() );
	/* Display operating system-style date and time. */
	char timeBuf[128], dateBuf[128];
    _strtime( timeBuf );
    _strdate( dateBuf );
	string Comments = string("Compressed on ") + dateBuf + ", " + timeBuf + " by FSW.";
	CompressionHeader.SetComments( Comments.c_str() );

	/* Scale and quantifiy ****************************************************/
	FSW_ZeroTreeCompressor::Scaling( QuadTree, CompressionHeader );
	FSW_ZeroTreeCompressor::ComputeMaxCoefValue( QuadTree, CompressionHeader );	// this will update the compression header
	FSW_ZeroTreeCompressor::Quantification( QuadTree, CompressionHeader );

	/* write header to the stream */
	CompressionHeader.WriteToStream( BitStream );

	/* Initialization *********************************************************/
	this->InitList( QuadTree );

	/* The main Loop *********************************************************/
	for( FSW_I32 nPass=nNbrBitPlanes; nPass>=0; --nPass )
	{
		if( pCompressionCallback_PerBitPlane_!=NULL )
		{
			FSW_Bool bContinue = pCompressionCallback_PerBitPlane_(BitStream, QuadTree, (FSW_U8) nPass);
			if( !bContinue )
				return;
		}
		/* an important thing to do : remember the entry that were already here ... */
		T_QuadTreeVertexList OldLSP = LSP_;
		/* 2 : sorting pass */
		/* 2.1 : Manage the LIP list */
		IT_QuadTreeVertexList itVert = LIP_.begin();
		while( itVert!=LIP_.end() )
		{
			FSW_QuadTreeVertex* pVert = *itVert;
			FSW_ASSERT( pVert!=NULL );
			/* output signifiance */
			FSW_Bool bSignifiance = FSW_ZeroTreeCompressor::OutputSignifiance_Vertex( BitStream, *pVert, nPass );
			CHECK_AND_EXIT
			if( bSignifiance )
			{
				/* move from LIP to LSP */
				itVert = LIP_.erase( itVert );
				LSP_.push_back( pVert );
				/*output sign */
				FSW_ZeroTreeCompressor::OuputSign( BitStream, *pVert, nPass );
				CHECK_AND_EXIT
			}
			else
			{
				/* here we didn't erase, so we have to push the iterator manualy */
				itVert++;
			}
		}
		/* 2.2 : manage LIS list */
		IT_QuadTreeNodeList itNode = LIS_.begin();
		while( itNode != LIS_.end() )
		{
			FSW_QuadTreeNode* pNode = *itNode;
			FSW_ASSERT( pNode!=NULL );
			/* first compute and output signifiance according to the type of the node */
			FSW_Bool bSignifiance;

			bSignifiance = FSW_ZeroTreeCompressor::OutputSignifiance_Node( BitStream, *pNode, nPass );
			CHECK_AND_EXIT
			if( bSignifiance ) 
			{
				switch( pNode->GetCompressionType() ) 
				{
				case FSW_QuadTreeNode::kTypeA:	// 2.2.1 :
					/* processed each vertex we are responsible for */
					for( FSW_U32 i=0; i<3; ++i )
					{
						if( pNode->GetResponsabilityForVertex(i) )
						{
							FSW_QuadTreeVertex* pVert = pNode->GetOwnedVertex( i );
							FSW_ASSERT( pVert!=NULL );
							bSignifiance = FSW_ZeroTreeCompressor::OutputSignifiance_Vertex( BitStream, *pVert, nPass );
							CHECK_AND_EXIT
							if( bSignifiance ) 
							{
								/* signifiant : add to LSP */
								LSP_.push_back( pVert );
								/* output sign */
								FSW_ZeroTreeCompressor::OuputSign( BitStream, *pVert, nPass );
								CHECK_AND_EXIT
							}
							else
							{
								/* insignifiant : add to LIP */
								LIP_.push_back( pVert );
							}
						}
					}
					/* partition the entry of type A */
					itNode = LIS_.erase( itNode );	// erasing the node automatically push the iteraror. No itNode++ should be called later.
					/* check if the child of the node has vertex */
					if( pNode->GetDepth() <= QuadTree.GetDepth()-1 )
					{
						/* the entry can be subdivised, so change it into type B */
						pNode->SetCompressionType(FSW_QuadTreeNode::kTypeB);
						LIS_.push_back( pNode );
					}
					break;
				case FSW_QuadTreeNode::kTypeB:	// 2.2.2 :
					/* first remove the node from the LIS */
					itNode = LIS_.erase( itNode );	// erasing the node automatically push the iteraror. No itNode++ should be called later.
					/* processed each sub-face */
					for( FSW_U32 i=0; i<4; ++i )
					{
						FSW_QuadTreeNode* pSonNode = pNode->GetChildNode( i );
						FSW_ASSERT( pSonNode!=NULL );
						pSonNode->SetCompressionType( FSW_QuadTreeNode::kTypeA );
						LIS_.push_back( pSonNode );
					}
					break;
				default:
					FSW_ASSERT( FSW_False );
					break;
				}	// switch( pNode->GetCompressionType() )
			}
			else	// if CurNode is not signifiant. It is not removed from LIS, so we must make ++.
			{
				/* we didn't perform an erase, so we must push the iterator manualy */
				itNode++;
			}
		}	// End loop over LIS
		/* 3 : Refinemenent pass */
		for( IT_QuadTreeVertexList itVertToRefine=OldLSP.begin(); itVertToRefine!=OldLSP.end(); ++itVertToRefine )
		{
			FSW_QuadTreeVertex* pVert = *itVertToRefine;
			FSW_ZeroTreeCompressor::OuputBit( BitStream, *pVert, nPass );
			CHECK_AND_EXIT
		}
	}	// for( FSW_U32 nPass=nNbrBitPlanes; nPass>=0; --nPass )

#ifdef FSW_DEBUG
	/* check the LIS really contains no more information */
	for( IT_QuadTreeNodeList it=LIS_.begin(); it!=LIS_.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		if( pNode->GetOwnedVertex(0)!=NULL )//&& pNode->GetCompressionType()==FSW_QuadTreeNode::kTypeA )
		{
			/* This node is not a leaf, so it must be insignifiant as all it's son */
			FSW_ASSERT( !ComputeSignifiance( *pNode, 0 ) );
		}
	}
	for( IT_QuadTreeVertexList it=LIP_.begin(); it!=LIP_.end(); ++it )
	{
		FSW_QuadTreeVertex* pVert = *it;
		FSW_ASSERT( !ComputeSignifiance( *pVert, 0 ) );
	}
#endif	// #ifdef FSW_DEBUG

	/* Clean the quantification used for compression.
	   This is a bit unusefull since we lost a lot of information during compression ... anyway ... */
	FSW_ZeroTreeCompressor::UnQuantification( QuadTree, CompressionHeader );
	FSW_ZeroTreeCompressor::UnScaling( QuadTree, CompressionHeader );
	
	/* clear the lists */
	LSP_.clear();
	LIS_.clear();
	LIP_.clear();

	#undef CHECK_AND_EXIT
}


/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::UnCompress
/**
 *  \param  BitStream [FSW_BitStream&] The bitstream.
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Compress the quadtree into a bitstream.
 */
/*------------------------------------------------------------------------------*/
void FSW_ZeroTreeCompressor::UnCompress( FSW_BitStream& BitStream, FSW_QuadTree& QuadTree )
{
	#define CHECK_AND_EXIT																			\
	if( pCompressionCallback_PerBit_!=NULL )														\
	{																								\
		if( !pCompressionCallback_PerBit_(BitStream, QuadTree, (FSW_U8) nPass) )					\
		{	UnQuantification(QuadTree,CompressionHeader);UnScaling(QuadTree,CompressionHeader);		\
			LSP_.clear();LIS_.clear();LIP_.clear(); return; } }

	FSW_CompressionHeader CompressionHeader;

	/* read the header from the stream */
	CompressionHeader.ReadFromStream( BitStream );

	/* Convenient variables name. */
	FSW_U32 nNbrBitPlanes = CompressionHeader.GetNbrBitPlane();
	T_ScalingType ScalingType = CompressionHeader.GetScalingType();

	/* first set all coefficient to zero  and make sure the tree has correct size */
	QuadTree.BuildTree( FSW_TreeFunction_ABC(), CompressionHeader.GetTreeDepth() );
	FSW_ASSERT( QuadTree.GetDepth()==CompressionHeader.GetTreeDepth() );

	/* Initialization *********************************************************/
	this->InitList( QuadTree );

	/* The main Loop *********************************************************/
	for( FSW_I32 nPass=nNbrBitPlanes; nPass>=0; --nPass )
	{
		if( pCompressionCallback_PerBitPlane_!=NULL )
		{
			FSW_Bool bContinue = pCompressionCallback_PerBitPlane_(BitStream, QuadTree, (FSW_U8) nPass);
			if( !bContinue )
				return;
		}
		/* an important thing to do : remember the entry that were already here ... */
		T_QuadTreeVertexList OldLSP = LSP_;
		/* 2 : sorting pass */
		/* 2.1 : Manage the LIP list */
		IT_QuadTreeVertexList itVert = LIP_.begin();
		while( itVert!=LIP_.end() )
		{
			FSW_QuadTreeVertex* pVert = *itVert;
			FSW_ASSERT( pVert!=NULL );
			/* output signifiance */
			FSW_Bool bSignifiance = FSW_ZeroTreeCompressor::InputSignifiance_Vertex( BitStream, *pVert, nPass );
			CHECK_AND_EXIT
			if( bSignifiance )
			{
				/* move from LIP to LSP */
				itVert = LIP_.erase( itVert );
				LSP_.push_back( pVert );
				/* input sign : as this is the first time the vertex is considered, set its value to +-1.5*2^depth*/
				FSW_ZeroTreeCompressor::InputSignAndPredicValue( BitStream, *pVert, nPass );
				CHECK_AND_EXIT
			}
			else
			{
				/* here we didn't erase, so we have to push the iterator manualy */
				itVert++;
			}
		}
		/* 2.2 : manage LIS list */
		IT_QuadTreeNodeList itNode = LIS_.begin();
		while( itNode != LIS_.end() )
		{
			FSW_QuadTreeNode* pNode = *itNode;
			FSW_ASSERT( pNode!=NULL );
			/* first input signifiance according to the type of the node */
			FSW_Bool bSignifiance;
			bSignifiance = FSW_ZeroTreeCompressor::InputSignifiance_Node( BitStream, *pNode, nPass );
			CHECK_AND_EXIT
			if( bSignifiance ) 
			{
				switch( pNode->GetCompressionType() ) 
				{
				case FSW_QuadTreeNode::kTypeA:	// 2.2.1 :
					/* processed each vertex we are responsible for */
					for( FSW_U32 i=0; i<3; ++i )
					{
						if( pNode->GetResponsabilityForVertex(i) )
						{
							FSW_QuadTreeVertex* pVert = pNode->GetOwnedVertex( i );
							FSW_ASSERT( pVert!=NULL );
							bSignifiance = FSW_ZeroTreeCompressor::InputSignifiance_Vertex( BitStream, *pVert, nPass );
							CHECK_AND_EXIT
							if( bSignifiance ) 
							{
								/* signifiant : add to LSP */
								LSP_.push_back( pVert );
								/* output sign */
								FSW_ZeroTreeCompressor::InputSignAndPredicValue( BitStream, *pVert, nPass );
								CHECK_AND_EXIT
							}
							else
							{
								/* insignifiant : add to LIP */
								LIP_.push_back( pVert );
							}
						}
					}
					/* partition the entry of type A */
					itNode = LIS_.erase( itNode );	// erasing the node automatically push the iteraror. No itNode++ should be called later.
					/* check if the child of the node has children : can be inproved */
					if( pNode->GetDepth() <= QuadTree.GetDepth()-1 )
					{
						/* the entry can be subdivised, so change it into type B */
						pNode->SetCompressionType(FSW_QuadTreeNode::kTypeB);
						LIS_.push_back( pNode );
					}
					break;
				case FSW_QuadTreeNode::kTypeB:	// 2.2.2 :
					/* first remove the node from the LIS */
					itNode = LIS_.erase( itNode );	// erasing the node automatically push the iteraror. No itNode++ should be called later.
					/* processed each sub-face */
					for( FSW_U32 i=0; i<4; ++i )
					{
						FSW_QuadTreeNode* pSonNode = pNode->GetChildNode( i );
						FSW_ASSERT( pSonNode!=NULL );
						pSonNode->SetCompressionType( FSW_QuadTreeNode::kTypeA );
						LIS_.push_back( pSonNode );
					}
					break;
				default:
					FSW_ASSERT( FSW_False );
					break;
				}	// switch( pNode->GetCompressionType() )
			}
			else	// if CurNode is not signifiant. It is not removed from LIS, so we must make ++.
			{
				/* we didn't perform an erase, so we must push the iterator manualy */
				itNode++;
			}
		}	// End loop over LIS
		/* 3 : Refinemenent pass */
		for( IT_QuadTreeVertexList itVertToRefine=OldLSP.begin(); itVertToRefine!=OldLSP.end(); ++itVertToRefine )
		{
			FSW_QuadTreeVertex* pVert = *itVertToRefine;
			FSW_ZeroTreeCompressor::InputBit( BitStream, *pVert, nPass );
			CHECK_AND_EXIT
		}

	}	// for( FSW_U32 nPass=nNbrBitPlanes; nPass>=0; --nPass )
	
#ifdef FSW_DEBUG
	/* check the LIS really contains no more information */
	for( IT_QuadTreeNodeList it=LIS_.begin(); it!=LIS_.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		if( pNode->GetOwnedVertex(0)!=NULL )//&& pNode->GetCompressionType()==FSW_QuadTreeNode::kTypeA)
		{
			/* This node is not a leaf, so it must be insignifiant as all it's son */
			FSW_ASSERT( !ComputeSignifiance( *pNode, 0 ) );
		}
	}
	for( IT_QuadTreeVertexList it=LIP_.begin(); it!=LIP_.end(); ++it )
	{
		FSW_QuadTreeVertex* pVert = *it;
		FSW_I32 nVal = FSW_VertexBasedCompressor::GetQuantifiedValue( *pVert );
		FSW_ASSERT( nVal==0 );
	}
#endif	// #ifdef FSW_DEBUG

	/* Undo quantification and scaling */
	FSW_ZeroTreeCompressor::UnQuantification( QuadTree, CompressionHeader );
	FSW_ZeroTreeCompressor::UnScaling( QuadTree, CompressionHeader );

	/* clear the lists */
	LSP_.clear();
	LIS_.clear();
	LIP_.clear();

	#undef CHECK_AND_EXIT
}

/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::TestClass
/**
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Launch a bunch of test on the class.
 */
/*------------------------------------------------------------------------------*/
void FSW_ZeroTreeCompressor::TestClass( FSW_Bool bVerbose )
{
#ifdef FSW_DEBUG
	if( bVerbose )
		cout << "FSW_ZeroTreeCompressor -- starting test ... ";

	FSW_QuadTreeVertex Vert;

	for( FSW_U32 iter=0; iter<10; ++iter )
	{
		FILE* F = fopen( FSW_TEST_FILE, "wb" );	
		FSW_ASSERT( F!=NULL );
		FSW_BitStream bs( F, FSW_BitStream::kWriteMode );

		srand( (unsigned)time( NULL ) );
		FSW_I32 nVal = (FSW_I32) (1<<29)*(0.89 + 0.1*FSW_RAND);
		if( rand()<0.5*RAND_MAX )
			nVal = -nVal;
		nVal = 113492810;
		FSW_ZeroTreeCompressor::SetQuantifiedValue( Vert, nVal );
		FSW_ASSERT( FSW_ZeroTreeCompressor::GetQuantifiedValue(Vert)==nVal );

		/* We check for each bit. When reaching the 1st non null bit, output the sign. Then refine outputing the bit. */
		FSW_I32 nMSB = -1;	// rank of the 1st non null bit.
		for( FSW_I32 i=28; i>=0; --i )
		{
			FSW_U32 nThreshold = 1<<i;
			FSW_U32 nUVal = FSW_ABS(nVal);
			if( (nUVal&nThreshold)==nThreshold && (nMSB<0) )
			{
				/* this is the most significant bit of the value, so output the sign and the *NOT* the bit */
				FSW_ZeroTreeCompressor::OuputSign( bs, Vert, i );
				nMSB = i;
			}
			else if( nMSB>=0 )
				FSW_ZeroTreeCompressor::OuputBit( bs, Vert, i );	
		}

		bs.Flush();
		fclose(F);
		F = fopen( "test.bin", "rb" );
		bs.Reset( F, FSW_BitStream::kReadMode );

		FSW_ZeroTreeCompressor::SetQuantifiedValue( Vert, 0 );
		/* First recover the sign and assign value to +-1.5*2^nMSB */
		FSW_ZeroTreeCompressor::InputSignAndPredicValue( bs, Vert, nMSB );
		for( FSW_I32 i=nMSB-1; i>=0; --i )
		{
			/* refine the value using less significant data */
			FSW_ZeroTreeCompressor::InputBit( bs, Vert, i );
		}
		
		FSW_I32 nDiff = nVal - FSW_ZeroTreeCompressor::GetQuantifiedValue(Vert);

		FSW_ASSERT( nDiff==0 );
	}

	if( bVerbose )
		cout << "test completed with success." << endl;
#endif // #ifdef FSW_DEBUG
}


/*------------------------------------------------------------------------------*/
// Name : FSW_ZeroTreeCompressor::InitList
/**
 *  \param  QuadTree [FSW_QuadTree&] The quadtree to compress.
 *  \author Gabriel Peyré
 *  \date   11-26-2002
 * 
 *  Initialisate the 3 lists involved in compression and 
 *  uncompression
 */
/*------------------------------------------------------------------------------*/
void FSW_ZeroTreeCompressor::InitList( FSW_QuadTree& QuadTree )
{
	LIP_.clear();
	LIS_.clear();
	LSP_.clear();
	/* for the LIP : put the vertice of the octahedron */
	T_QuadTreeVertexVector BaseVertexVector = QuadTree.GetBaseVertexVector();
	for( IT_QuadTreeVertexVector it=BaseVertexVector.begin(); it!=BaseVertexVector.end(); ++it )
	{
		FSW_QuadTreeVertex* pVert = *it;
		FSW_ASSERT( pVert!=NULL );
		LIP_.push_back( pVert );
	}
	/* for the LIS : put the faces of the octahedron */
	T_QuadTreeNodeVector BaseNodeVector = QuadTree.GetBaseNodeVector();
	for( IT_QuadTreeNodeVector it=BaseNodeVector.begin(); it!=BaseNodeVector.end(); ++it )
	{
		FSW_QuadTreeNode* pNode = *it;
		FSW_ASSERT( pNode!=NULL );
		pNode->SetCompressionType( FSW_QuadTreeNode::kTypeA );
		LIS_.push_back( pNode );
	}
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
