/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_IntegralDataChunk.inl
 *  \brief  Inlined methods for \c FSW_IntegralDataChunk
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_IntegralDataChunk.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_IntegralDataChunk::GetIntegral
/**
 *  \return [FSW_Float] The value of the integral.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Return the value of the integral of the scale function.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_IntegralDataChunk::GetIntegral(FSW_U32 nLevel)
{
	FSW_ASSERT( nLevel<IntegralValues_.size() );
	return IntegralValues_[nLevel];	
}

/*------------------------------------------------------------------------------*/
// Name : FSW_IntegralDataChunk::SetIntegral
/**
 *  \param  rVal [FSW_Float] The integral value.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Set the value of the integral. This should be set by the wavelet transform
 *	only once, using a recursing scheme (compute the integral on the finest level using
 *	aproximation).
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_IntegralDataChunk::SetIntegral(FSW_Float rVal, FSW_I32 nLevel)
{
	FSW_ASSERT( nLevel>=0 );
	FSW_I32 nLastLevel = (FSW_I32) IntegralValues_.size()-1;
	if( nLevel>nLastLevel )
	{
		/* the map isn't large enough */
		for( FSW_I32 i=nLastLevel; i<nLevel; i++ )
			IntegralValues_.push_back(0);
	}
	IntegralValues_[nLevel] = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_IntegralDataChunk::AddIntegral
/**
 *  \param  rVal [FSW_Float] The integral value.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Add some value to the integral already computed.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_IntegralDataChunk::AddIntegral(FSW_Float rVal, FSW_I32 nLevel)
{
	FSW_ASSERT( nLevel>=0 );
	FSW_I32 nLastLevel = (FSW_I32) IntegralValues_.size()-1;
	if( nLevel>nLastLevel )
	{
		/* the map isn't large enough */
		for( FSW_I32 i=nLastLevel; i<nLevel; i++ )
			IntegralValues_.push_back(0);
	}
	IntegralValues_[nLevel] += rVal;
}


FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
