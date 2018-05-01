/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_IntegralDataChunk.cpp
 *  \brief  Definition of class \c FSW_IntegralDataChunk
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_IntegralDataChunk.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_IntegralDataChunk.h"

#ifndef FSW_USE_INLINE
    #include "FSW_IntegralDataChunk.inl"
#endif

using namespace FSW;

/*------------------------------------------------------------------------------*/
// Name : FSW_IntegralDataChunk constructor
/**
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Constructor.
 */
/*------------------------------------------------------------------------------*/
FSW_IntegralDataChunk::FSW_IntegralDataChunk()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_IntegralDataChunk destructor
/**
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Destructor.
 */
/*------------------------------------------------------------------------------*/
FSW_IntegralDataChunk::~FSW_IntegralDataChunk()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_IntegralDataChunk::GetType
/**
 *  \return [T_WaveletTransformType] The type.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  The type of the chunk (for check).
 */
/*------------------------------------------------------------------------------*/
FSW_U32 FSW_IntegralDataChunk::GetType()
{
	return T_IntegralDataChunk;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
