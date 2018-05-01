/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTreeVertex.cpp
 *  \brief  Definition of class \c GW_QuadTreeVertex
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/


#ifdef GW_SCCSID
    static const char* sccsid = "@(#) GW_QuadTreeVertex.cpp(c) Gabriel Peyré2002";
#endif // GW_SCCSID

#include "stdafx.h"
#include "GW_QuadTreeVertex.h"
#include "GW_DataChunk_ABC.h"

#ifndef GW_USE_INLINE
    #include "GW_QuadTreeVertex.inl"
#endif

using namespace GW;


/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex constructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  constructor
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeVertex::GW_QuadTreeVertex()
:	pDataChunk_	( NULL ),
	rVal_		( 0 )
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex destructor
/**
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Destructor
 */
/*------------------------------------------------------------------------------*/
GW_QuadTreeVertex::~GW_QuadTreeVertex()
{
	/* delete the data chunk if needed */
	GW_DELETE( pDataChunk_ );
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::GetDataChunk
/**
 *  \return [GW_DataChunk_ABC*] The data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Return the data chunk. Can be null.
 */
/*------------------------------------------------------------------------------*/
GW_DataChunk_ABC* GW_QuadTreeVertex::GetDataChunk()
{
	return pDataChunk_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::SetDataChunk
/**
 *  \param  DataChunk [GW_DataChunk_ABC&] The new data chunk.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 * 
 *  Set the data chunk used by a transform to store some precomputed values.
 */
/*------------------------------------------------------------------------------*/
void GW_QuadTreeVertex::SetDataChunk(GW_DataChunk_ABC& DataChunk)
{
	/* delete the previous chunk if needed */
	GW_DELETE( pDataChunk_ );
	pDataChunk_ = &DataChunk;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
