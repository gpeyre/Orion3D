/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_CompressionHeader.cpp
 *  \brief  Definition of class \c FSW_CompressionHeader
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_CompressionHeader.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_CompressionHeader.h"

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Constructor. 
 */
/*------------------------------------------------------------------------------*/
FSW_CompressionHeader::FSW_CompressionHeader()
:	nNbrBitPlanes_	( 0 ),
	ScalingType_	( FSW_Compressor_ABC::kNormL2 ),
	rMaxCoefValue_	( 0 ),
	nTreeDepth_		( 0 ),
	nMinorVersion_	( FSW_COMPRESSFSW_MINFSW_VERSION ),
	nMajorVersion_	( FSW_COMPRESSFSW_MAJFSW_VERSION ),
	CompressorName_						( string("[No compressor name specified.]") ),
	TransformName_						( string("[No transform name specified.]") ),
	BaseMeshName_						( string("[No base mesh name specified.]") ),
	Comments_							( string("[No comments specified.]") )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::WriteToStream
/**
 *  \param  BitStream [FSW_BitStream&] The bit stream.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Write the header into a stream.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::WriteToStream(FSW_BitStream& BitStream) const
{
	FILE* pStream = BitStream.GetStream();
	FSW_ASSERT( pStream!=NULL );
	BitStream.Flush();	// normaly, header should be written at the begining, but anyway ...
	if( !this->BuildToFile(pStream) )
	{
		FSW_ASSERT( FSW_False );
		cerr << "Error in FSW_CompressionHeader::WriteToStream. Unable to write header." << endl;
		return;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::ReadFromStream
/**
 *  \param  BitStream [FSW_BitStream&] The stream.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Read the hader from a bit stream.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::ReadFromStream(FSW_BitStream& BitStream)
{
	FILE* pStream = BitStream.GetStream();
	FSW_ASSERT( pStream!=NULL );
	BitStream.Flush();	// normaly, header should be written at the begining, but anyway ...
	if( !this->BuildFromFile(pStream) )
	{
		FSW_ASSERT( FSW_False );
		cerr << "Error in FSW_CompressionHeader::ReadFromStream. Unable to read header." << endl;
		return;
	}
	FSW_ASSERT( nNbrBitPlanes_<=FSW_MAX_NBR_BITPLANES );
	/* check version number */
	if( nMinorVersion_!=FSW_COMPRESSFSW_MINFSW_VERSION || nMajorVersion_!=FSW_COMPRESSFSW_MAJFSW_VERSION )
	{
		FSW_ASSERT( FSW_False );
		cerr << "Error in FSW_CompressionHeader::ReadFromStream. Version of file doesn't match with expected version." << endl;
		cerr << "File version     : " << nMajorVersion_ << "." << nMinorVersion_ << endl;
		cerr << "Expected version : " << FSW_COMPRESSFSW_MAJFSW_VERSION << "." << FSW_COMPRESSFSW_MINFSW_VERSION << endl;
		return;
	}
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetNbrBitPlane
/**
 *  \return [FSW_U32] Number of bits.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the number of bit used for quantification.
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_CompressionHeader::GetNbrBitPlane() const
{
	return nNbrBitPlanes_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetNbrBitPlane
/**
 *  \param  nNbrBitPlanes [FSW_U32] Number of bit used for quantification.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the number of bit used for quantification.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetNbrBitPlane(FSW_U32 nNbrBitPlanes)
{
	FSW_ASSERT( nNbrBitPlanes<=FSW_MAX_NBR_BITPLANES );
	nNbrBitPlanes_ = nNbrBitPlanes;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetScalingType
/**
 *  \return [FSW_Compressor_ABC::T_ScalingType] Type of scaling done to the coefficients before quantification.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the type of scaling done to the coefficients before 
 *  quantification.
 */
/*------------------------------------------------------------------------------*/
FSW_Compressor_ABC::T_ScalingType FSW_CompressionHeader::GetScalingType() const
{
	return ScalingType_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetScalingType
/**
 *  \param  ScalingType [FSW_Compressor_ABC::T_ScalingType] The type of scaling done to the coefficients before quantification.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the type of scaling done to the coefficients before 
 *  quantification.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetScalingType(FSW_Compressor_ABC::T_ScalingType ScalingType)
{
	ScalingType_ = ScalingType;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetMaxCoefValue
/**
 *  \return [FSW_Float] Max value
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Get the maximum absolute value of the wavelet coefficient 
 *  (computed before serialization).
 */
/*------------------------------------------------------------------------------*/
FSW_Float FSW_CompressionHeader::GetMaxCoefValue() const
{
	return rMaxCoefValue_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetMaxCoefValue
/**
 *  \param  rMaxCoefValue [FSW_Float] Max value.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the maximum absolute value of the wavelet coefficient .
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetMaxCoefValue( FSW_Float rMaxCoefValue )
{
	rMaxCoefValue_ = rMaxCoefValue;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetTreeDepth
/**
 *  \return [FSW_U32] Depth.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Return the depth of the tree used for compression. 
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_CompressionHeader::GetTreeDepth() const
{
	return nTreeDepth_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetTreeDepth
/**
 *  \param  nTreeDepth [FSW_U32] The depth.
 *  \author Gabriel Peyré
 *  \date   11-25-2002
 * 
 *  Set the depth of the tree used for compression.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetTreeDepth( FSW_U32 nTreeDepth )
{
	nTreeDepth_ = nTreeDepth;	
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetCompressorName
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set the name of the compressor used for compresion.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetCompressorName( const char* Name )
{
	CompressorName_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetTransformName
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set the name of the transform used for compresion.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetTransformName( const char* Name )
{
	TransformName_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetBaseMeshName
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set the name of the base mesh used for compresion.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetBaseMeshName( const char* Name )
{
	BaseMeshName_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::SetComments
/**
 *  \param  Name [char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Set some commments.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::SetComments( const char* Name )
{
	Comments_ = Name;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetCompressorName
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the name of the compressor used for compression.
 */
/*------------------------------------------------------------------------------*/
const char* FSW_CompressionHeader::GetCompressorName()
{
	return CompressorName_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetTransformName
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the name of the transform used for compression.
 */
/*------------------------------------------------------------------------------*/
const char* FSW_CompressionHeader::GetTransformName()
{
	return TransformName_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetBaseMeshName
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the name of the base mesh used for compression.
 */
/*------------------------------------------------------------------------------*/
const char* FSW_CompressionHeader::GetBaseMeshName()
{
	return BaseMeshName_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetComments
/**
 *  \return [const char*] The name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Get the comments.
 */
/*------------------------------------------------------------------------------*/
const char* FSW_CompressionHeader::GetComments()
{
	return Comments_.c_str();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::ReadFromFile
/**
 *  \param  file_name [char*] The file name.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Read only the header from a file.
 */
/*------------------------------------------------------------------------------*/
void FSW_CompressionHeader::ReadFromFile( const char* file_name )
{
	FILE* pFile = fopen( file_name, "rb" );
	if( pFile==NULL )
		return;
	if( !this->BuildFromFile( pFile ) )
	{	
		cerr << "Error in FSW_CompressionHeader::ReadFromFile. Unable to read header." << endl;
		return;
	}
	fclose( pFile );
}



/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::BuildFromFile
/**
 *  \param  pFile [FILE*] The file.
 *  \return [FSW_Bool] Was the action successful ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Write the data to a file.
 */
/*------------------------------------------------------------------------------*/
FSW_Bool FSW_CompressionHeader::BuildFromFile( FILE* pFile )
{
	FSW_ASSERT( pFile!=NULL );
	size_t nRead;

	#define	READ_DATA( var, type )					\
	nRead = fread( &var, sizeof(type), 1, pFile );	\
	if( nRead!=1 ) return FSW_False

    READ_DATA(nNbrBitPlanes_, FSW_U32);
	READ_DATA(nTreeDepth_, FSW_U32);
	READ_DATA(ScalingType_, FSW_Compressor_ABC::T_ScalingType);
	READ_DATA(rMaxCoefValue_, FSW_Float);
	READ_DATA(nMinorVersion_, FSW_U8);
	READ_DATA(nMajorVersion_, FSW_U8);

	FSW_CompressionHeader::ReadString(pFile, CompressorName_);
	FSW_CompressionHeader::ReadString(pFile, TransformName_);
	FSW_CompressionHeader::ReadString(pFile, BaseMeshName_);
	FSW_CompressionHeader::ReadString(pFile, Comments_);

	return FSW_True;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::BuildToFile
/**
 *  \param  pFile [FILE*] The file.
 *  \return [FSW_Bool] Was the action successful ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Write the data to a file.
 */
/*------------------------------------------------------------------------------*/
FSW_Bool FSW_CompressionHeader::BuildToFile( FILE* pFile ) const
{
	FSW_ASSERT( pFile!=NULL );
	size_t nWrite;

	#define	WRITE_DATA( var, type )						\
	nWrite = fwrite( &var, sizeof(type), 1, pFile );	\
	if( nWrite!=1 ) return FSW_False

    WRITE_DATA(nNbrBitPlanes_, FSW_U32);
	WRITE_DATA(nTreeDepth_, FSW_U32);
	WRITE_DATA(ScalingType_, FSW_Compressor_ABC::T_ScalingType);
	WRITE_DATA(rMaxCoefValue_, FSW_Float);
	WRITE_DATA(nMinorVersion_, FSW_U8);
	WRITE_DATA(nMajorVersion_, FSW_U8);

	FSW_CompressionHeader::WriteString(pFile, CompressorName_);
	FSW_CompressionHeader::WriteString(pFile, TransformName_);
	FSW_CompressionHeader::WriteString(pFile, BaseMeshName_);
	FSW_CompressionHeader::WriteString(pFile, Comments_);

	return FSW_True;
}



/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::ReadString
/**
 *  \param  pFile [FILE*] The file.
 *  \param  str [string&] The string.
 *  \return [FSW_Bool] Success ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Read a string from a file.
 */
/*------------------------------------------------------------------------------*/
FSW_Bool FSW_CompressionHeader::ReadString( FILE* pFile, string& str ) 
{
	size_t nRead;
	/* read the length of the string */
	FSW_I32 nLength;
	READ_DATA(nLength, FSW_I32);
	FSW_ASSERT(nLength>=0);
	/* set the size */
	char* astr = new char[nLength+1];
	astr[nLength]=NULL;
	/* read the data */
	nRead = fread(astr, sizeof(char), nLength, pFile);
	if( nRead!=nLength )
		return FSW_False;
	str.clear();
	str = string(astr);
	FSW_DELETEARRAY(astr);

	return FSW_True;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::WriteString
/**
 *  \param  pFile [FILE*] the file.
 *  \param  str [string&] The string.
 *  \return [FSW_Bool] Success ?
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Write a string to a file.
 */
/*------------------------------------------------------------------------------*/
FSW_Bool FSW_CompressionHeader::WriteString( FILE* pFile, const string& str ) 
{
	size_t nWrite;
	/* write the length of the string */
	FSW_I32 nSize = (FSW_I32) str.size();
	WRITE_DATA(nSize, FSW_I32);
	FSW_ASSERT( nSize>=0 );
	/* write the data */	
	fwrite(str.c_str(), sizeof(char), nSize, pFile);

	return FSW_True;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_CompressionHeader::GetScalingTypeString
/**
 *  \return [const char*] The string.
 *  \author Gabriel Peyré
 *  \date   12-1-2002
 * 
 *  Just for information purpose. Get a string representing the type 
 *  of the scaling.
 */
/*------------------------------------------------------------------------------*/
const char* FSW_CompressionHeader::GetScalingTypeString()
{
	switch( this->GetScalingType() ) 
	{
	case FSW_Compressor_ABC::kNormL1:
		return "L1 norm scaling";
		break;
	case FSW_Compressor_ABC::kNormL2:
		return "L2 norm scaling";
		break;
	case FSW_Compressor_ABC::kNormInf:
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
