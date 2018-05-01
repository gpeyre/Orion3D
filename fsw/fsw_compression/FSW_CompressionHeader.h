
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_CompressionHeader.h
 *  \brief  Definition of class \c FSW_CompressionHeader
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_COMPRESSIONHEADER_H_
#define _FSW_COMPRESSIONHEADER_H_

#include "../fsw_core/FSW_Config.h"
#include "FSW_BitStream.h"
#include "FSW_Compressor_ABC.h"

FSW_BEGIN_NAMESPACE

#define FSW_COMPRESSFSW_MAJFSW_VERSION 1
#define FSW_COMPRESSFSW_MINFSW_VERSION 0

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_CompressionHeader
 *  \brief  This control the way the serialization is performed.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  This class is serialized first in the stream.
 */ 
/*------------------------------------------------------------------------------*/

class FSW_CompressionHeader
{

public:

	FSW_CompressionHeader();

    //-------------------------------------------------------------------------
    /** \name Serialization. */
    //-------------------------------------------------------------------------
    //@{
	void WriteToStream(FSW_BitStream& BitStream) const;
	void ReadFromStream(FSW_BitStream& BitStream);

	void ReadFromFile( const char* file_name );
    //@}

    //-------------------------------------------------------------------------
    /** \name Accessors. */
    //-------------------------------------------------------------------------
    //@{
	FSW_U32 GetNbrBitPlane() const;
	void SetNbrBitPlane(FSW_U32 nNbrBitPlanes);
	FSW_Compressor_ABC::T_ScalingType GetScalingType() const;
	void SetScalingType(FSW_Compressor_ABC::T_ScalingType ScalingType);
	FSW_Float GetMaxCoefValue() const;
	void SetMaxCoefValue( FSW_Float rMaxCoefValue );
	FSW_U32 GetTreeDepth() const;
	void SetTreeDepth( FSW_U32 nTreeDepth );

	void SetCompressorName( const char* Name );
	void SetTransformName( const char* Name );
	void SetBaseMeshName( const char* Name );
	void SetComments( const char* Name );
	const char* GetCompressorName();
	const char* GetTransformName();
	const char* GetBaseMeshName();
	const char* GetComments();
	const char* GetScalingTypeString();
    //@}


private:

	FSW_Bool BuildFromFile( FILE* pFile );
	FSW_Bool BuildToFile( FILE* pFile ) const;
	static FSW_Bool ReadString( FILE* pFile, string& str ) ;
	static FSW_Bool WriteString( FILE* pFile, const string& str ) ;

	/** The number of bits used for quantification. */
    FSW_U32 nNbrBitPlanes_;
	/** The size of the Tree. */
	FSW_U32 nTreeDepth_;
	/** The way coefficients are scaled before compression, and unscaled after. */
	FSW_Compressor_ABC::T_ScalingType ScalingType_;
	/** The maximum absolute value of coefficients before quantification. */
	FSW_Float rMaxCoefValue_;
	/** version of the file */
	FSW_U8 nMinorVersion_;
	FSW_U8 nMajorVersion_;

	
	/** For information purpose only : the name of the compressor used. */
	string CompressorName_;
	/** For information purpose only : the name of the transform used. */
	string TransformName_;
	/** For information purpose only : the name of the base mesh used. */
	string BaseMeshName_;
	/** For information purpose only : some comment of the author. */
	string Comments_;

};

FSW_END_NAMESPACE


#endif // _FSW_COMPRESSIONHEADER_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
