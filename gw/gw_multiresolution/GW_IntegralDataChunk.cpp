/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_IntegralDataChunk.cpp
 *  \brief  Definition of class \c GW_IntegralDataChunk
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_IntegralDataChunk.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_IntegralDataChunk.h"

#ifndef GW_USE_INLINE
    #include "GW_IntegralDataChunk.inl"
#endif

using namespace GW;

/*------------------------------------------------------------------------------*/
// Name : GW_IntegralDataChunk constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
GW_IntegralDataChunk::GW_IntegralDataChunk()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_IntegralDataChunk destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
GW_IntegralDataChunk::~GW_IntegralDataChunk()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_IntegralDataChunk::GetType
/**
 *  \return [T_WaveletTransformType] The type.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  The type of the chunk (for check).
 */
/*------------------------------------------------------------------------------*/
GW_U32 GW_IntegralDataChunk::GetType()
{
	return T_IntegralDataChunk;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
