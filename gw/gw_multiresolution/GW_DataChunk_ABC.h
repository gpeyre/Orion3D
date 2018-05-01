
/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_DataChunk_ABC.h
 *  \brief  Definition of class \c GW_DataChunk_ABC
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _GW_DATACHUNK_ABC_H_
#define _GW_DATACHUNK_ABC_H_

#include "../gw_core/GW_Config.h"
#include "GW_WaveletTransform_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  GW_DataChunk_ABC
 *  \brief  A piece of information that can be store in a vertex or in a node.
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 *
 *  Used by a wavelet transform to put pre-coputed information on each vertex
 *	or each face. This info is computed only once during a pre-computation traversal
 *	of the tree (before the first forward transform).
 *
 *	An example of information store in a data chunk can be the 
 *	integral of the current scale function for the given node/face at the given precision.
 */ 
/*------------------------------------------------------------------------------*/

class GW_DataChunk_ABC
{

public:

	virtual ~GW_DataChunk_ABC()
	{};

	/** just to do some error checking before making an unsafe cast. */
    virtual GW_U32 GetType() = 0;

};

GW_END_NAMESPACE


#endif // _GW_DATACHUNK_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
