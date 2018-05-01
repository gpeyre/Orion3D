/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_BitStream.inl
 *  \brief  Inlined methods for \c GW_BitStream
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_BitStream.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::Put
/**
 *  \param  bVal [GW_Bool] The bit to add.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Add a bit to the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_BitStream::Put( GW_Bool bVal )
{
	/* do some check */
	GW_ASSERT( pStream_!=NULL );
	GW_ASSERT( Mode_ == kWriteMode );

	if( bVal ) 
		nCurChar_ |= nMask_;

	/* shift the mask */
	nMask_ >>= 1;
	if( nMask_==0 )
	{
		/* current char is full */
		size_t nCount = fwrite(&nCurChar_, sizeof(GW_U8), 1, pStream_ );
		GW_ASSERT( nCount==1 );
		/* reset char and mask */
		nCurChar_ = 0;
		nMask_ = 0x80;
	}

	nNbrBits_++;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::Put
/**
 *  \param  nVal [GW_U32] The unsigned int to add.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Add an unsigned int to the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_BitStream::Put( GW_U32 nVal )
{
	/* do some check */
	GW_ASSERT( pStream_!=NULL );
	GW_ASSERT( Mode_ == kWriteMode );

	/* flush current char */
	this->Flush();

	size_t nCount = fwrite(&nVal, sizeof(GW_U32), 1, pStream_ );
	GW_ASSERT( nCount==1 );

	/* reset char and mask */
	nCurChar_ = 0;
	nMask_ = 0x80;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::Get
/**
 *  \param  bVal [GW_Bool&] The bit to get.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Get a bit from the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_BitStream::Get( GW_Bool& bVal )
{
	/* do some check */
	GW_ASSERT( pStream_!=NULL );
	GW_ASSERT( Mode_ == kReadMode );

	if( nMask_==0 )
	{
		if( feof(pStream_) )
		{
			bError_ = GW_True;
			return;
		}
		size_t nCount = fread(&nCurChar_, sizeof(GW_U8), 1, pStream_ );
		GW_ASSERT( nCount==1 );
		nMask_ = 0x80;
	}

	if( (nCurChar_&nMask_)==0 ) 
		bVal = GW_False;
	else 
		bVal = GW_True;

	nMask_ >>= 1;

	nNbrBits_++;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::Get
/**
 *  \param  nVal [GW_U32&] The unsigned int to get.
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Get an unsigned int from the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_BitStream::Get( GW_U32& nVal )
{
	/* do some check */
	GW_ASSERT( pStream_!=NULL );
	GW_ASSERT( Mode_ == kReadMode );
	
	if( feof(pStream_) )
	{
		bError_ = GW_True;
		return;
	}
	size_t nCount = fread(&nVal, sizeof(GW_U32), 1, pStream_ );
	GW_ASSERT( nCount==1 );

	/* restart the char */
	this->Flush();
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::operator << 
/**
 *  \param  bVal [GW_Bool&] The bit.
 *  \return [GW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_BitStream& GW_BitStream::operator << ( GW_Bool bVal )
{
	this->Put( bVal );
	return *this;
}


/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::operator << 
/**
 *  \param  bVal [GW_Bool&] The bit.
 *  \return [GW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_BitStream& GW_BitStream::operator << ( GW_U32 nVal )
{
	this->Put( nVal );
	return *this;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::operator << 
/**
 *  \param  bVal [GW_Bool&] The bit.
 *  \return [GW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_BitStream& GW_BitStream::operator >> ( GW_Bool& bVal )
{
	this->Get( bVal );
	return *this;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::operator << 
/**
 *  \param  bVal [GW_Bool&] The bit.
 *  \return [GW_BitStream&] *this
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Serialize a bit in the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_BitStream& GW_BitStream::operator >> ( GW_U32& nVal )
{
	this->Get( nVal );
	return *this;
}


/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::GetError
/**
 *  \return [GW_Bool] Yes/No
 *  \author Gabriel Peyré
 *  \date   11-21-2002
 * 
 *  Set to true if there was an error during previous operations.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_BitStream::GetError()
{
	return bError_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::GetStream
/**
 *  \return [FILE*] The stream.
 *  \author Gabriel Peyré
 *  \date   11-24-2002
 * 
 *  Get the stream.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
FILE* GW_BitStream::GetStream()
{
	return pStream_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_BitStream::GetNbrBits
/**
 *  \return [GW_U32] The number of bits.
 *  \author Gabriel Peyré
 *  \date   11-27-2002
 * 
 *  Return the number of bit already put in the file.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_U32 GW_BitStream::GetNbrBits() const
{
	return nNbrBits_;
}


GW_END_NAMESPACE


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
