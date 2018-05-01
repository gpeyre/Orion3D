/*------------------------------------------------------------------------------*/
/** 
 *  \file   GW_QuadTreeVertex.inl
 *  \brief  Inlined methods for \c GW_QuadTreeVertex
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 */ 
/*------------------------------------------------------------------------------*/

#include "GW_QuadTreeVertex.h"

GW_BEGIN_NAMESPACE

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::SetPosition
/**
 *  \param  Pos [GW_Vector3D&] The position of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the position of the vertex. Should be on a sphere, of course 
 *  ...
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeVertex::SetPosition(const GW_Vector3D& Pos)
{
	Pos_ = Pos;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::GetPosition
/**
 *  \return [GW_Vector3D&] The position of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get the position of the vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Vector3D& GW_QuadTreeVertex::GetPosition()
{
	return Pos_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::GetPositionConst
/**
 *  \return [GW_Vector3D&] The position of the vertex.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Get the position of the vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
const GW_Vector3D& GW_QuadTreeVertex::GetPositionConst() const
{
	return Pos_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::SetValue
/**
 *  \param  rVal [GW_Float] The value hold by the slot of the vertex. Usefull in vertex base schemes.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Set the value hold by this vertex.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeVertex::SetValue(GW_Float rVal)
{
	rVal_ = rVal;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::GetValue
/**
 *  \return [GW_Float] The slot value, used in vertex base wavelet.
 *  \author Gabriel Peyré
 *  \date   10-27-2002
 * 
 *  Return the slot value.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_Float GW_QuadTreeVertex::GetValue() const 
{
	return rVal_;
}

#ifdef GW_DEBUG
/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::GetQuantifiedValue
/**
 *  \return [GW_I32] Quantified value.
 *  \author Gabriel Peyré
 *  \date   12-5-2002
 * 
 *  In debug mode only. Other wise, put the I32 value in the Float 
 *  slot.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
GW_I32 GW_QuadTreeVertex::GetQuantifiedValue() const
{
	return nQuantifiedValue_;
}

/*------------------------------------------------------------------------------*/
// Name : GW_QuadTreeVertex::SetQuantifiedValue
/**
 *  \param  nQuantifiedValue [GW_I32] Set the quantified value.
 *  \author Gabriel Peyré
 *  \date   12-5-2002
 * 
 *  For debug only.
 */
/*------------------------------------------------------------------------------*/
GW_INLINE
void GW_QuadTreeVertex::SetQuantifiedValue(GW_I32 nQuantifiedValue)
{
	nQuantifiedValue_ = nQuantifiedValue;
}
#endif

GW_END_NAMESPACE


///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) Gabriel Peyré
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////
