/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Collider_ABC.inl
 *  \brief Inlined methods for \c OR_Collider_ABC
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Collider_ABC.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collider_ABC constructor
 *
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Collider_ABC::OR_Collider_ABC()
:	bIsActive_	( true )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collider_ABC destructor
 *
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Collider_ABC::~OR_Collider_ABC()
{
	/* NOTHING */
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collider_ABC::IsActive
 *
 *  \return Do we check collision for this pair ?
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Collider_ABC::IsActive()
{
	return bIsActive_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collider_ABC::Enable
 *
 *  \return Enable collision detection for this pair.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collider_ABC::Enable()
{
	bIsActive_ = true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Collider_ABC::Disable
 *
 *  \return Disable collision detection for this pair.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Collider_ABC::Disable()
{
	bIsActive_ = false;
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

