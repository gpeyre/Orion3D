
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_ZeroTreeCompressor.h
 *  \brief  Definition of class \c GW_ZeroTreeCompressor
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_ZEROTREECOMPRESSGW_H_
#define _GW_ZEROTREECOMPRESSGW_H_

#include "../gw_core/GW_Config.h"
#include "../gw_multiresolution/GW_BaseMesh_ABC.h"
#include "GW_VertexBasedCompressor.h"
#include "GW_CompressionHeader.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_ZeroTreeCompressor
 *  \brief  A compressor based on a zerotree algorithm.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  This compressor use a recursive approach to continuously serialize the 
 *	different bits (starting from most signifiant one) of the wavelet coefficients, 
 *	starting from the greatest.
 */ 
/*------------------------------------------------------------------------------*/

class GW_ZeroTreeCompressor:	public GW_VertexBasedCompressor
{

public:

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    GW_ZeroTreeCompressor();
    virtual ~GW_ZeroTreeCompressor();
    //@}

	//-------------------------------------------------------------------------
    /** \name Overload from \c GW_ZeroTreeCompressor. */
    //-------------------------------------------------------------------------
    //@{
	virtual void Compress( GW_BitStream& BitStream, GW_QuadTree& QuadTree, GW_U32 nNbrBitPlanes = 10, T_ScalingType ScalingType = kNormL2 );
	virtual void UnCompress( GW_BitStream& BitStream, GW_QuadTree& QuadTree );
    //@}

	//-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the compressor in the file. */
	virtual const char* GetCompressorName()
	{ return "GW_ZeroTreeCompressor"; }
    //@}

	static void TestClass( GW_Bool bVerbose=GW_False );

private:

	//-------------------------------------------------------------------------
    /** \name Signifiance computations */
    //-------------------------------------------------------------------------
    //@{
	static GW_Bool ComputeSignifiance( GW_QuadTreeVertex& CurVert, GW_U32 nPass );
	static GW_Bool ComputeSignifiance( GW_QuadTreeNode& CurNode, GW_U32 nPass );
	static GW_Bool ComputeSignifiance_Rec( GW_QuadTreeNode& CurNode, GW_U32 nPass );
    //@}

	/** This is some token we put in the stream in debug mode for error checking. 
		The number of these token are chosen so that we can put in each GW_U8
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
	void InitList( GW_QuadTree& QuadTree );

	static void OuputSign( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );
	static void InputSign( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );
	static void InputSignAndPredicValue( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );
	static void OuputBit( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );
	static void InputBit( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );

	static GW_Bool OutputSignifiance_Vertex( GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );
	static GW_Bool InputSignifiance_Vertex(  GW_BitStream& BitStream, GW_QuadTreeVertex& CurVert, GW_U32 nPass );

	static GW_Bool OutputSignifiance_Node( GW_BitStream& BitStream, GW_QuadTreeNode& CurNode, GW_U32 nPass );
	static GW_Bool InputSignifiance_Node(  GW_BitStream& BitStream, GW_QuadTreeNode& CurNode, GW_U32 nPass );
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

GW_END_NAMESPACE

#ifdef GW_USE_INLINE
    #include "GW_ZeroTreeCompressor.inl"
#endif


#endif // _GW_ZEROTREECOMPRESSGW_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
