
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_CompressionHeader.h
 *  \brief  Definition of class \c GW_CompressionHeader
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_COMPRESSIONHEADER_H_
#define _GW_COMPRESSIONHEADER_H_

#include "../gw_core/GW_Config.h"
#include "GW_BitStream.h"
#include "GW_Compressor_ABC.h"

GW_BEGIN_NAMESPACE

#define GW_COMPRESSGW_MAJGW_VERSION 1
#define GW_COMPRESSGW_MINGW_VERSION 0

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_CompressionHeader
 *  \brief  This control the way the serialization is performed.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 *
 *  This class is serialized first in the stream.
 */ 
/*------------------------------------------------------------------------------*/

class GW_CompressionHeader
{

public:

	GW_CompressionHeader();

    //-------------------------------------------------------------------------
    /** \name Serialization. */
    //-------------------------------------------------------------------------
    //@{
	void WriteToStream(GW_BitStream& BitStream) const;
	void ReadFromStream(GW_BitStream& BitStream);

	void ReadFromFile( const char* file_name );
    //@}

    //-------------------------------------------------------------------------
    /** \name Accessors. */
    //-------------------------------------------------------------------------
    //@{
	GW_U32 GetNbrBitPlane() const;
	void SetNbrBitPlane(GW_U32 nNbrBitPlanes);
	GW_Compressor_ABC::T_ScalingType GetScalingType() const;
	void SetScalingType(GW_Compressor_ABC::T_ScalingType ScalingType);
	GW_Float GetMaxCoefValue() const;
	void SetMaxCoefValue( GW_Float rMaxCoefValue );
	GW_U32 GetTreeDepth() const;
	void SetTreeDepth( GW_U32 nTreeDepth );

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

	GW_Bool BuildFromFile( FILE* pFile );
	GW_Bool BuildToFile( FILE* pFile ) const;
	static GW_Bool ReadString( FILE* pFile, string& str ) ;
	static GW_Bool WriteString( FILE* pFile, const string& str ) ;

	/** The number of bits used for quantification. */
    GW_U32 nNbrBitPlanes_;
	/** The size of the Tree. */
	GW_U32 nTreeDepth_;
	/** The way coefficients are scaled before compression, and unscaled after. */
	GW_Compressor_ABC::T_ScalingType ScalingType_;
	/** The maximum absolute value of coefficients before quantification. */
	GW_Float rMaxCoefValue_;
	/** version of the file */
	GW_U8 nMinorVersion_;
	GW_U8 nMajorVersion_;

	
	/** For information purpose only : the name of the compressor used. */
	string CompressorName_;
	/** For information purpose only : the name of the transform used. */
	string TransformName_;
	/** For information purpose only : the name of the base mesh used. */
	string BaseMeshName_;
	/** For information purpose only : some comment of the author. */
	string Comments_;

};

GW_END_NAMESPACE


#endif // _GW_COMPRESSIONHEADER_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
