
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_Compressor_ABC.h
 *  \brief  Definition of class \c FSW_Compressor_ABC
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_COMPRESSOR_ABC_H_
#define _FSW_COMPRESSOR_ABC_H_

#include "../fsw_core/FSW_Config.h"
#include "FSW_BitStream.h"
#include "../fsw_core/FSW_QuadTree.h"

FSW_BEGIN_NAMESPACE

class FSW_CompressionHeader;

#define FSW_MAX_NBR_BITPLANES 28

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_Compressor_ABC
 *  \brief  Basic class for all compressor.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  Defined the method to be overloaded to compress a \c FSW_QuadTree
 *	that contains the wavelet coefficients.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_Compressor_ABC
{

public:

	/** This control the way the quantification is done by making a pre-scaling pass. */
	enum T_ScalingType
	{
		kNormL1,	//	Scaling by 4^(-j) where j is the depth in the tree.
		kNormL2,	//	Scaling by 2^(-j) where j is the depth in the tree.
		kNormInf	//	No scaling is done.
	};

    /*------------------------------------------------------------------------------*/
    /** \name Constructor and destructor */
    /*------------------------------------------------------------------------------*/
    //@{
    FSW_Compressor_ABC();
    virtual ~FSW_Compressor_ABC();
    //@}

	//-------------------------------------------------------------------------
    /** \name To be overloaded. */
    //-------------------------------------------------------------------------
    //@{
	virtual void Compress( FSW_BitStream& BitStream, FSW_QuadTree& QuadTree, FSW_U32 nNbrBitPlanes = 10, T_ScalingType ScalingType = kNormL2 ) = 0;
	virtual void UnCompress( FSW_BitStream& BitStream, FSW_QuadTree& QuadTree ) = 0;
    //@}

	//-------------------------------------------------------------------------
    /** \name Callback management. */
    //-------------------------------------------------------------------------
    //@{
	/** Type of the callback function called by the compressor to know
		if it should continue the compression/decompression process. */
	typedef FSW_Bool (*T_CompressionCallback_Func)( const FSW_BitStream& BitStream, FSW_QuadTree& QuadTree, FSW_U8 nBitPlane );
	void SetCompressionCallback_PerBit(T_CompressionCallback_Func pFunc);
	void SetCompressionCallback_PerBitPlane(T_CompressionCallback_Func pFunc);
    //@}

    //-------------------------------------------------------------------------
    /** \name Getting information. */
    //-------------------------------------------------------------------------
    //@{
	/** Use this function to set the name of the compressor in the file. */
	virtual const char* GetCompressorName() = 0;
    //@}

protected:

	/** The callback function called by the compressor to know
		if it should continue the compression/decompression process. 
		Leave it to \c NULL if you don't need any control. */
	T_CompressionCallback_Func pCompressionCallback_PerBit_;
	/** This one is called only once per bitplane. */
	T_CompressionCallback_Func pCompressionCallback_PerBitPlane_;

};

FSW_END_NAMESPACE


#endif // _FSW_COMPRESSOR_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
