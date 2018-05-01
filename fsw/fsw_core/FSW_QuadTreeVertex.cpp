/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTreeVertex.cpp
 *  \brief  Definition of class \c FSW_QuadTreeVertex
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef FSW_SCCSID
    static const char* sccsid = "@(#) FSW_QuadTreeVertex.cpp(c) Gabriel Peyré2002";
#endif // FSW_SCCSID

#include "stdafx.h"
#include "FSW_QuadTreeVertex.h"
#include "FSW_DataChunk_ABC.h"

#ifndef FSW_USE_INLINE
    #include "FSW_QuadTreeVertex.inl"
#endif

using namespace FSW;


/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  constructor
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTreeVertex::FSW_QuadTreeVertex()
:	pDataChunk_	( NULL ),
	rVal_		( 0 )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Destructor
 */
/*------------------------------------------------------------------------------*/
FSW_QuadTreeVertex::~FSW_QuadTreeVertex()
{
	/* delete the data chunk if needed */
	FSW_DELETE( pDataChunk_ );
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::GetDataChunk
/**
 *  \return [FSW_DataChunk_ABC*] The data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Return the data chunk. Can be null.
 */
/*------------------------------------------------------------------------------*/
FSW_DataChunk_ABC* FSW_QuadTreeVertex::GetDataChunk()
{
	return pDataChunk_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::SetDataChunk
/**
 *  \param  DataChunk [FSW_DataChunk_ABC&] The new data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Set the data chunk used by a transform to store some precomputed values.
 */
/*------------------------------------------------------------------------------*/
void FSW_QuadTreeVertex::SetDataChunk(FSW_DataChunk_ABC& DataChunk)
{
	/* delete the previous chunk if needed */
	FSW_DELETE( pDataChunk_ );
	pDataChunk_ = &DataChunk;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
