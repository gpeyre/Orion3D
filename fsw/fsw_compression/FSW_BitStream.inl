/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_BitStream.inl
 *  \brief  Inlined methods for \c FSW_BitStream
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_BitStream.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::Put
/**
 *  \param  bVal [FSW_Bool] The bit to add.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Add a bit to the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_BitStream::Put( FSW_Bool bVal )
{
	/* do some check */
	FSW_ASSERT( pStream_!=NULL );
	FSW_ASSERT( Mode_ == kWriteMode );

	if( bVal ) 
		nCurChar_ |= nMask_;

	/* shift the mask */
	nMask_ >>= 1;
	if( nMask_==0 )
	{
		/* current char is full */
		size_t nCount = fwrite(&nCurChar_, sizeof(FSW_U8), 1, pStream_ );
		FSW_ASSERT( nCount==1 );
		/* reset char and mask */
		nCurChar_ = 0;
		nMask_ = 0x80;
	}

	nNbrBits_++;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::Put
/**
 *  \param  nVal [FSW_U32] The unsigned int to add.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Add an unsigned int to the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_BitStream::Put( FSW_U32 nVal )
{
	/* do some check */
	FSW_ASSERT( pStream_!=NULL );
	FSW_ASSERT( Mode_ == kWriteMode );

	/* flush current char */
	this->Flush();

	size_t nCount = fwrite(&nVal, sizeof(FSW_U32), 1, pStream_ );
	FSW_ASSERT( nCount==1 );

	/* reset char and mask */
	nCurChar_ = 0;
	nMask_ = 0x80;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::Get
/**
 *  \param  bVal [FSW_Bool&] The bit to get.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Get a bit from the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_BitStream::Get( FSW_Bool& bVal )
{
	/* do some check */
	FSW_ASSERT( pStream_!=NULL );
	FSW_ASSERT( Mode_ == kReadMode );

	if( nMask_==0 )
	{
		if( feof(pStream_) )
		{
			bError_ = FSW_True;
			return;
		}
		size_t nCount = fread(&nCurChar_, sizeof(FSW_U8), 1, pStream_ );
		FSW_ASSERT( nCount==1 );
		nMask_ = 0x80;
	}

	if( (nCurChar_&nMask_)==0 ) 
		bVal = FSW_False;
	else 
		bVal = FSW_True;

	nMask_ >>= 1;

	nNbrBits_++;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::Get
/**
 *  \param  nVal [FSW_U32&] The unsigned int to get.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Get an unsigned int from the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_BitStream::Get( FSW_U32& nVal )
{
	/* do some check */
	FSW_ASSERT( pStream_!=NULL );
	FSW_ASSERT( Mode_ == kReadMode );
	
	if( feof(pStream_) )
	{
		bError_ = FSW_True;
		return;
	}
	size_t nCount = fread(&nVal, sizeof(FSW_U32), 1, pStream_ );
	FSW_ASSERT( nCount==1 );

	/* restart the char */
	this->Flush();
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::operator << 
/**
 *  \param  bVal [FSW_Bool&] The bit.
 *  \return [FSW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_BitStream& FSW_BitStream::operator << ( FSW_Bool bVal )
{
	this->Put( bVal );
	return *this;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::operator << 
/**
 *  \param  bVal [FSW_Bool&] The bit.
 *  \return [FSW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_BitStream& FSW_BitStream::operator << ( FSW_U32 nVal )
{
	this->Put( nVal );
	return *this;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::operator << 
/**
 *  \param  bVal [FSW_Bool&] The bit.
 *  \return [FSW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_BitStream& FSW_BitStream::operator >> ( FSW_Bool& bVal )
{
	this->Get( bVal );
	return *this;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::operator << 
/**
 *  \param  bVal [FSW_Bool&] The bit.
 *  \return [FSW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_BitStream& FSW_BitStream::operator >> ( FSW_U32& nVal )
{
	this->Get( nVal );
	return *this;
}


/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::GetError
/**
 *  \return [FSW_Bool] Yes/No
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Set to true if there was an error during previous operations.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_BitStream::GetError()
{
	return bError_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::GetStream
/**
 *  \return [FILE*] The stream.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Get the stream.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FILE* FSW_BitStream::GetStream()
{
	return pStream_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_BitStream::GetNbrBits
/**
 *  \return [FSW_U32] The number of bits.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Return the number of bit already put in the file.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_U32 FSW_BitStream::GetNbrBits() const
{
	return nNbrBits_;
}


FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré & Antoine Bouthors
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
