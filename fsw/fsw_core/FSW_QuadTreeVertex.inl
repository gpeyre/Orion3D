/*------------------------------------------------------------------------------*/
/** 
 *  \file   FSW_QuadTreeVertex.inl
 *  \brief  Inlined methods for \c FSW_QuadTreeVertex
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "FSW_QuadTreeVertex.h"

FSW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::SetPosition
/**
 *  \param  Pos [FSW_Vector3D&] The position of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the position of the vertex. Should be on a sphere, of course 
 *  ...
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeVertex::SetPosition(const FSW_Vector3D& Pos)
{
	Pos_ = Pos;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::GetPosition
/**
 *  \return [FSW_Vector3D&] The position of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get the position of the vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Vector3D& FSW_QuadTreeVertex::GetPosition()
{
	return Pos_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::GetPositionConst
/**
 *  \return [FSW_Vector3D&] The position of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get the position of the vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
const FSW_Vector3D& FSW_QuadTreeVertex::GetPositionConst() const
{
	return Pos_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::SetValue
/**
 *  \param  rVal [FSW_Float] The value hold by the slot of the vertex. Usefull in vertex base schemes.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value hold by this vertex.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeVertex::SetValue(FSW_Float rVal)
{
	rVal_ = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::GetValue
/**
 *  \return [FSW_Float] The slot value, used in vertex base wavelet.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Return the slot value.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_Float FSW_QuadTreeVertex::GetValue() const 
{
	return rVal_;
}

#ifdef FSW_DEBUG
/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::GetQuantifiedValue
/**
 *  \return [FSW_I32] Quantified value.
 *  \author Gabriel Peyré
 *  \date   12-5-2002
 * 
 *  In debug mode only. Other wise, put the I32 value in the Float 
 *  slot.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
FSW_I32 FSW_QuadTreeVertex::GetQuantifiedValue() const
{
	return nQuantifiedValue_;
}

/*------------------------------------------------------------------------------*/
// Name : FSW_QuadTreeVertex::SetQuantifiedValue
/**
 *  \param  nQuantifiedValue [FSW_I32] Set the quantified value.
 *  \author Gabriel Peyré
 *  \date   12-5-2002
 * 
 *  For debug only.
 */
/*------------------------------------------------------------------------------*/
FSW_INLINE
void FSW_QuadTreeVertex::SetQuantifiedValue(FSW_I32 nQuantifiedValue)
{
	nQuantifiedValue_ = nQuantifiedValue;
}
#endif

FSW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
