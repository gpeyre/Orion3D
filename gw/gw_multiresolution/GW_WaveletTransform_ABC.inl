/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_WaveletTransform_ABC.inl
 *  \brief  Inlined methods for \c GW_WaveletTransform_ABC
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_WaveletTransform_ABC.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_WaveletTransform_ABC::SetUseUpdate
/**
 *  \param  bUseUpdate [GW_Bool] Yes or No ?
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Set if the scheme use an update stage (for test purpose only).
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_WaveletTransform_ABC::SetUseUpdate( GW_Bool bUseUpdate )
{
	bUseUpdate_ = bUseUpdate;	
}

/*------------------------------------------------------------------------------*/
// Name : GW_WaveletTransform_ABC::GetUseUpdate
/**
 *  \return [GW_Bool] Yes/No
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Do we use an update stage ?
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Bool GW_WaveletTransform_ABC::GetUseUpdate()
{
	return bUseUpdate_;
}



GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
