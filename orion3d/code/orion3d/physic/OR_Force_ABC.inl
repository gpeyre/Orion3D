/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Force_ABC.inl
 *  \brief Inlined methods for \c OR_Force_ABC
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Force_ABC.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_Force_ABC::GetActivity
/**
*   @return is the object active or not ?
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Force_ABC::IsActive()
{ 
	return bIsActive_; 
}

//-----------------------------------------------------------------------------
// Name: OR_Force_ABC::Disable
/**
*   @return previous activity 
*
*	Disable the object for rendering
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Force_ABC::Disable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = false; 
	return old;
}



//-----------------------------------------------------------------------------
// Name: OR_Force_ABC::Enable
/**
*   @return previous activity 
*
*	Enable the object for rendering
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Force_ABC::Enable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = true; 
	return old;
}

//-----------------------------------------------------------------------------
// Name: OR_Force_ABC::Toggle
/**
*   @return Current activity.
*
*	Toggel on/off the object for rendering.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Force_ABC::Toggle()
{
	bIsActive_=!bIsActive_; 
	return bIsActive_;
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

