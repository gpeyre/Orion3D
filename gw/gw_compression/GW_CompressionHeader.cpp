/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_CompressionHeader.cpp
 *  \brief  Definition of class \c GW_CompressionHeader
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_CompressionHeader.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_CompressionHeader.h"

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
GW_CompressionHeader::GW_CompressionHeader()
:	nNbrBitPlanes_	( 0 ),
	ScalingType_	( GW_Compressor_ABC::kNormL2 ),
	rMaxCoefValue_	( 0 ),
	nTreeDepth_		( 0 ),
	nMinorVersion_	( GW_COMPRESSGW_MINGW_VERSION ),
	nMajorVersion_	( GW_COMPRESSGW_MAJGW_VERSION ),
	CompressorName_						( string("[No compressor name specified.]") ),
	TransformName_						( string("[No transform name specified.]") ),
	BaseMeshName_						( string("[No base mesh name specified.]") ),
	Comments_							( string("[No comments specified.]") )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::WriteToStream
/**
 *  \param  BitStream [GW_BitStream&] The bit stream.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Write the header into a stream.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::WriteToStream(GW_BitStream& BitStream) const
{
	FILE* pStream = BitStream.GetStream();
	GW_ASSERT( pStream!=NULL );
	BitStream.Flush();	// normaly, header should be written at the begining, but anyway ...
	if( !this->BuildToFile(pStream) )
	{
		GW_ASSERT( GW_False );
		cerr << "Error in GW_CompressionHeader::WriteToStream. Unable to write header." << endl;
		return;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::ReadFromStream
/**
 *  \param  BitStream [GW_BitStream&] The stream.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Read the hader from a bit stream.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::ReadFromStream(GW_BitStream& BitStream)
{
	FILE* pStream = BitStream.GetStream();
	GW_ASSERT( pStream!=NULL );
	BitStream.Flush();	// normaly, header should be written at the begining, but anyway ...
	if( !this->BuildFromFile(pStream) )
	{
		GW_ASSERT( GW_False );
		cerr << "Error in GW_CompressionHeader::ReadFromStream. Unable to read header." << endl;
		return;
	}
	GW_ASSERT( nNbrBitPlanes_<=GW_MAX_NBR_BITPLANES );
	/* check version number */
	if( nMinorVersion_!=GW_COMPRESSGW_MINGW_VERSION || nMajorVersion_!=GW_COMPRESSGW_MAJGW_VERSION )
	{
		GW_ASSERT( GW_False );
		cerr << "Error in GW_CompressionHeader::ReadFromStream. Version of file doesn't match with expected version." << endl;
		cerr << "File version     : " << nMajorVersion_ << "." << nMinorVersion_ << endl;
		cerr << "Expected version : " << GW_COMPRESSGW_MAJGW_VERSION << "." << GW_COMPRESSGW_MINGW_VERSION << endl;
		return;
	}
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetNbrBitPlane
/**
 *  \return [GW_U32] Number of bits.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the number of bit used for quantification.
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_CompressionHeader::GetNbrBitPlane() const
{
	return nNbrBitPlanes_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetNbrBitPlane
/**
 *  \param  nNbrBitPlanes [GW_U32] Number of bit used for quantification.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the number of bit used for quantification.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetNbrBitPlane(GW_U32 nNbrBitPlanes)
{
	GW_ASSERT( nNbrBitPlanes<=GW_MAX_NBR_BITPLANES );
	nNbrBitPlanes_ = nNbrBitPlanes;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetScalingType
/**
 *  \return [GW_Compressor_ABC::T_ScalingType] Type of scaling done to the coefficients before quantification.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the type of scaling done to the coefficients before 
 *  quantification.
 */
/*------------------------------------------------------------------------------*/
GW_Compressor_ABC::T_ScalingType GW_CompressionHeader::GetScalingType() const
{
	return ScalingType_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetScalingType
/**
 *  \param  ScalingType [GW_Compressor_ABC::T_ScalingType] The type of scaling done to the coefficients before quantification.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the type of scaling done to the coefficients before 
 *  quantification.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetScalingType(GW_Compressor_ABC::T_ScalingType ScalingType)
{
	ScalingType_ = ScalingType;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetMaxCoefValue
/**
 *  \return [GW_Float] Max value
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the maximum absolute value of the wavelet coefficient 
 *  (computed before serialization).
 */
/*------------------------------------------------------------------------------*/
GW_Float GW_CompressionHeader::GetMaxCoefValue() const
{
	return rMaxCoefValue_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetMaxCoefValue
/**
 *  \param  rMaxCoefValue [GW_Float] Max value.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the maximum absolute value of the wavelet coefficient .
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetMaxCoefValue( GW_Float rMaxCoefValue )
{
	rMaxCoefValue_ = rMaxCoefValue;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetTreeDepth
/**
 *  \return [GW_U32] Depth.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Return the depth of the tree used for compression. 
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_CompressionHeader::GetTreeDepth() const
{
	return nTreeDepth_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetTreeDepth
/**
 *  \param  nTreeDepth [GW_U32] The depth.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the depth of the tree used for compression.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetTreeDepth( GW_U32 nTreeDepth )
{
	nTreeDepth_ = nTreeDepth;	
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetCompressorName
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set the name of the compressor used for compresion.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetCompressorName( const char* Name )
{
	CompressorName_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetTransformName
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set the name of the transform used for compresion.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetTransformName( const char* Name )
{
	TransformName_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetBaseMeshName
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set the name of the base mesh used for compresion.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetBaseMeshName( const char* Name )
{
	BaseMeshName_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::SetComments
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set some commments.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::SetComments( const char* Name )
{
	Comments_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetCompressorName
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the name of the compressor used for compression.
 */
/*------------------------------------------------------------------------------*/
const char* GW_CompressionHeader::GetCompressorName()
{
	return CompressorName_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetTransformName
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the name of the transform used for compression.
 */
/*------------------------------------------------------------------------------*/
const char* GW_CompressionHeader::GetTransformName()
{
	return TransformName_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetBaseMeshName
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the name of the base mesh used for compression.
 */
/*------------------------------------------------------------------------------*/
const char* GW_CompressionHeader::GetBaseMeshName()
{
	return BaseMeshName_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetComments
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the comments.
 */
/*------------------------------------------------------------------------------*/
const char* GW_CompressionHeader::GetComments()
{
	return Comments_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::ReadFromFile
/**
 *  \param  file_name [char*] The file name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Read only the header from a file.
 */
/*------------------------------------------------------------------------------*/
void GW_CompressionHeader::ReadFromFile( const char* file_name )
{
	FILE* pFile = fopen( file_name, "rb" );
	if( pFile==NULL )
		return;
	if( !this->BuildFromFile( pFile ) )
	{	
		cerr << "Error in GW_CompressionHeader::ReadFromFile. Unable to read header." << endl;
		return;
	}
	fclose( pFile );
}



/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::BuildFromFile
/**
 *  \param  pFile [FILE*] The file.
 *  \return [GW_Bool] Was the action successful ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Write the data to a file.
 */
/*------------------------------------------------------------------------------*/
GW_Bool GW_CompressionHeader::BuildFromFile( FILE* pFile )
{
	GW_ASSERT( pFile!=NULL );
	size_t nRead;

	#define	READ_DATA( var, type )					\
	nRead = fread( &var, sizeof(type), 1, pFile );	\
	if( nRead!=1 ) return GW_False

    READ_DATA(nNbrBitPlanes_, GW_U32);
	READ_DATA(nTreeDepth_, GW_U32);
	READ_DATA(ScalingType_, GW_Compressor_ABC::T_ScalingType);
	READ_DATA(rMaxCoefValue_, GW_Float);
	READ_DATA(nMinorVersion_, GW_U8);
	READ_DATA(nMajorVersion_, GW_U8);

	GW_CompressionHeader::ReadString(pFile, CompressorName_);
	GW_CompressionHeader::ReadString(pFile, TransformName_);
	GW_CompressionHeader::ReadString(pFile, BaseMeshName_);
	GW_CompressionHeader::ReadString(pFile, Comments_);

	return GW_True;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::BuildToFile
/**
 *  \param  pFile [FILE*] The file.
 *  \return [GW_Bool] Was the action successful ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Write the data to a file.
 */
/*------------------------------------------------------------------------------*/
GW_Bool GW_CompressionHeader::BuildToFile( FILE* pFile ) const
{
	GW_ASSERT( pFile!=NULL );
	size_t nWrite;

	#define	WRITE_DATA( var, type )						\
	nWrite = fwrite( &var, sizeof(type), 1, pFile );	\
	if( nWrite!=1 ) return GW_False

    WRITE_DATA(nNbrBitPlanes_, GW_U32);
	WRITE_DATA(nTreeDepth_, GW_U32);
	WRITE_DATA(ScalingType_, GW_Compressor_ABC::T_ScalingType);
	WRITE_DATA(rMaxCoefValue_, GW_Float);
	WRITE_DATA(nMinorVersion_, GW_U8);
	WRITE_DATA(nMajorVersion_, GW_U8);

	GW_CompressionHeader::WriteString(pFile, CompressorName_);
	GW_CompressionHeader::WriteString(pFile, TransformName_);
	GW_CompressionHeader::WriteString(pFile, BaseMeshName_);
	GW_CompressionHeader::WriteString(pFile, Comments_);

	return GW_True;
}



/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::ReadString
/**
 *  \param  pFile [FILE*] The file.
 *  \param  str [string&] The string.
 *  \return [GW_Bool] Success ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Read a string from a file.
 */
/*------------------------------------------------------------------------------*/
GW_Bool GW_CompressionHeader::ReadString( FILE* pFile, string& str ) 
{
	size_t nRead;
	/* read the length of the string */
	GW_I32 nLength;
	READ_DATA(nLength, GW_I32);
	GW_ASSERT(nLength>=0);
	/* set the size */
	char* astr = new char[nLength+1];
	astr[nLength]=NULL;
	/* read the data */
	nRead = fread(astr, sizeof(char), nLength, pFile);
	if( nRead!=nLength )
		return GW_False;
	str.clear();
	str = string(astr);
	GW_DELETEARRAY(astr);

	return GW_True;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::WriteString
/**
 *  \param  pFile [FILE*] the file.
 *  \param  str [string&] The string.
 *  \return [GW_Bool] Success ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Write a string to a file.
 */
/*------------------------------------------------------------------------------*/
GW_Bool GW_CompressionHeader::WriteString( FILE* pFile, const string& str ) 
{
	size_t nWrite;
	/* write the length of the string */
	GW_I32 nSize = (GW_I32) str.size();
	WRITE_DATA(nSize, GW_I32);
	GW_ASSERT( nSize>=0 );
	/* write the data */	
	fwrite(str.c_str(), sizeof(char), nSize, pFile);

	return GW_True;
}

/*------------------------------------------------------------------------------*/
// Name : GW_CompressionHeader::GetScalingTypeString
/**
 *  \return [const char*] The string.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Just for information purpose. Get a string representing the type 
 *  of the scaling.
 */
/*------------------------------------------------------------------------------*/
const char* GW_CompressionHeader::GetScalingTypeString()
{
	switch( this->GetScalingType() ) 
	{
	case GW_Compressor_ABC::kNormL1:
		return "L1 norm scaling";
		break;
	case GW_Compressor_ABC::kNormL2:
		return "L2 norm scaling";
		break;
	case GW_Compressor_ABC::kNormInf:
		return "Infinite norm scaling (no scaling)";
		break;
	default:
		return "Unknown scaling type";
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
