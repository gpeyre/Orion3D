/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_IntegralDataChunk.inl
 *  \brief  Inlined methods for \c GW_IntegralDataChunk
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_IntegralDataChunk.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_IntegralDataChunk::GetIntegral
/**
 *  \return [GW_Float] The value of the integral.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Return the value of the integral of the scale function.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_IntegralDataChunk::GetIntegral(GW_U32 nLevel)
{
	GW_ASSERT( nLevel<IntegralValues_.size() );
	return IntegralValues_[nLevel];	
}

/*------------------------------------------------------------------------------*/
// Name : GW_IntegralDataChunk::SetIntegral
/**
 *  \param  rVal [GW_Float] The integral value.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Set the value of the integral. This should be set by the wavelet transform
 *	only once, using a recursing scheme (compute the integral on the finest level using
 *	aproximation).
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_IntegralDataChunk::SetIntegral(GW_Float rVal, GW_I32 nLevel)
{
	GW_ASSERT( nLevel>=0 );
	GW_I32 nLastLevel = (GW_I32) IntegralValues_.size()-1;
	if( nLevel>nLastLevel )
	{
		/* the map isn't large enough */
		for( GW_I32 i=nLastLevel; i<nLevel; i++ )
			IntegralValues_.push_back(0);
	}
	IntegralValues_[nLevel] = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : GW_IntegralDataChunk::AddIntegral
/**
 *  \param  rVal [GW_Float] The integral value.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Add some value to the integral already computed.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_IntegralDataChunk::AddIntegral(GW_Float rVal, GW_I32 nLevel)
{
	GW_ASSERT( nLevel>=0 );
	GW_I32 nLastLevel = (GW_I32) IntegralValues_.size()-1;
	if( nLevel>nLastLevel )
	{
		/* the map isn't large enough */
		for( GW_I32 i=nLastLevel; i<nLevel; i++ )
			IntegralValues_.push_back(0);
	}
	IntegralValues_[nLevel] += rVal;
}


GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
