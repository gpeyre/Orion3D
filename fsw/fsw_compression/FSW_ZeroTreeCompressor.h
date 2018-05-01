
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_ZeroTreeCompressor.h
 *  \brief  Definition of class \c FSW_ZeroTreeCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_ZEROTREECOMPRESSFSW_H_
#define _FSW_ZEROTREECOMPRESSFSW_H_

#include "../fsw_core/FSW_Config.h"
#include "../fsw_core/FSW_BaseMesh_ABC.h"
#include "FSW_VertexBasedCompressor.h"
#include "FSW_CompressionHeader.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_ZeroTreeCompressor
 *  \brief  A compressor based on a zerotree algorithm.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  This compressor use a recursive approach to continuously serialize the 
 *	different bits (starting from most signifiant one) of the wavelet coefficients, 
 *	starting from the greatest.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_ZeroTreeCompressor:	public FSW_VertexBasedCompressor
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_ZeroTreeCompressor();
    virtual ~FSW_ZeroTreeCompressor();
    //@}

	//-------------------------------------------------------------------------
    /** \name Overload from \c FSW_ZeroTreeCompressor. */
    //-------------------------------------------------------------------------
    //@{
	virtual void Compress( FSW_BitStream& BitStream, FSW_QuadTree& QuadTree, FSW_U32 nNbrBitPlanes = 10, T_ScalingType ScalingType = kNormL2 );
	virtual void UnCompress( FSW_BitStream& BitStream, FSW_QuadTree& QuadTree );
    //@}

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the compressor in the file. */
	virtual const char* GetCompressorName()
	{ return "FSW_ZeroTreeCompressor"; }
    //@}

	static void TestClass( FSW_Bool bVerbose=FSW_False );

private:

	//-------------------------------------------------------------------------
    /** \name Signifiance computations */
    //-------------------------------------------------------------------------
    //@{
	static FSW_Bool ComputeSignifiance( FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );
	static FSW_Bool ComputeSignifiance( FSW_QuadTreeNode& CurNode, FSW_U32 nPass );
	static FSW_Bool ComputeSignifiance_Rec( FSW_QuadTreeNode& CurNode, FSW_U32 nPass );
    //@}

	/** This is some token we put in the stream in debug mode for error checking. 
		The number of these token are chosen so that we can put in each FSW_U8
		that is passed in the stream :
			- the number of the pass (in [0,30]) in the 5 least significant bits (bits 0,1,2,3,4).
			- the T_CompressionDebugToken in the bits 5,6 (except for \c kDebugToken_SignBit which will
			a bit mess up with the 5 previous bits, but anyway ...).
			- the most important : the \c bool value in the most signicant bit (what is important is not
			to mess up with *this* bit).	
	*/
	enum T_CompressionDebugToken
	{
		kDebugToken_SignifianceVertex = 0,
		kDebugToken_SignifianceNodeA = 32,
		kDebugToken_SignifianceNodeB = 64,
		kDebugToken_RefinementBit = 96,
		kDebugToken_SignBit = 16
	};

	//-------------------------------------------------------------------------
    /** \name Stream serialization helpers. */
    //-------------------------------------------------------------------------
    //@{
	void InitList( FSW_QuadTree& QuadTree );

	static void OuputSign( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );
	static void InputSign( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );
	static void InputSignAndPredicValue( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );
	static void OuputBit( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );
	static void InputBit( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );

	static FSW_Bool OutputSignifiance_Vertex( FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );
	static FSW_Bool InputSignifiance_Vertex(  FSW_BitStream& BitStream, FSW_QuadTreeVertex& CurVert, FSW_U32 nPass );

	static FSW_Bool OutputSignifiance_Node( FSW_BitStream& BitStream, FSW_QuadTreeNode& CurNode, FSW_U32 nPass );
	static FSW_Bool InputSignifiance_Node(  FSW_BitStream& BitStream, FSW_QuadTreeNode& CurNode, FSW_U32 nPass );
    //@}



	/** List of insignifiant pixel.
		List of vertex we don't already know if they are signifiant. */
	T_QuadTreeVertexList LIP_;
	/** List of signifiant pixel.
		List of vertex we already know they are signifiant. */
	T_QuadTreeVertexList LSP_;
	/** List of insignifiant set.
		List of node we don't already know if they are signifiant. */
	T_QuadTreeNodeList LIS_;

};

FSW_END_NAMESPACE

#ifdef FSW_USE_INLINE
    #include "FSW_ZeroTreeCompressor.inl"
#endif


#endif // _FSW_ZEROTREECOMPRESSFSW_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
