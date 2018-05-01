/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_WaveletTransform_ABC.inl
 *  \brief  Inlined methods for \c FSW_WaveletTransform_ABC
 *  \author Gabriel Peyré
 *  \date   10-31-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_WaveletTransform_ABC.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_WaveletTransform_ABC::SetUseUpdate
/**
 *  \param  bUseUpdate [FSW_Bool] Yes or No ?
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Set if the scheme use an update stage (for test purpose only).
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_WaveletTransform_ABC::SetUseUpdate( FSW_Bool bUseUpdate )
{
	bUseUpdate_ = bUseUpdate;	
}

/*------------------------------------------------------------------------------*/
// Name : FSW_WaveletTransform_ABC::GetUseUpdate
/**
 *  \return [FSW_Bool] Yes/No
 *  \author Gabriel Peyré
 *  \date   11-16-2002
 * 
 *  Do we use an update stage ?
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Bool FSW_WaveletTransform_ABC::GetUseUpdate()
{
	return bUseUpdate_;
}



FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
