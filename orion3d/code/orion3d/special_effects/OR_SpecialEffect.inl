/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpecialEffect.inl
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_SpecialEffect.h"

namespace OR {

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect constructor
 *
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SpecialEffect::OR_SpecialEffect()
:	bIsActive_( true )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect destructor
 *
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_SpecialEffect::~OR_SpecialEffect()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect::IsActive
 *
 *  \return is the system active ?
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_SpecialEffect::IsActive()
{
	return bIsActive_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect::SetActivity
 *
 *  \param  bIsActive activity of the effect (on/off)
 *  \return Previous activity
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_SpecialEffect::SetActivity(OR_Bool bIsActive)
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = bIsActive; 
	return old;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect::Enable
 *
 *  \return previous activity
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Turn the effect on.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_SpecialEffect::Enable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = true; 
	return old;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect::Disable
 *
 *  \return previous activity
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Turn the effect off.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_SpecialEffect::Disable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = false; 
	return old;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffect::Toggle
 *
 *  \return previous activity
 *  \author Gabriel Peyré 2001-08-29
 *
 *	Toggle the effect on/off
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_SpecialEffect::Toggle()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = !bIsActive_; 
	return old;
}


} // End namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

