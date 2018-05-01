
/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_DataChunk_ABC.h
 *  \brief  Definition of class \c FSW_DataChunk_ABC
 *  \author Gabriel Peyré
 *  \date   11-12-2002
 */ 
/*------------------------------------------------------------------------------*/

#ifndef _FSW_DATACHUNK_ABC_H_
#define _FSW_DATACHUNK_ABC_H_

#include "FSW_Config.h"
#include "FSW_WaveletTransform_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
/** 
 *  \class  FSW_DataChunk_ABC
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

class FSW_DataChunk_ABC
{

public:

	virtual ~FSW_DataChunk_ABC()
	{};

	/** just to do some error checking before making an unsafe cast. */
    virtual FSW_U32 GetType() = 0;

};

FSW_END_NAMESPACE


#endif // _FSW_DATACHUNK_ABC_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
