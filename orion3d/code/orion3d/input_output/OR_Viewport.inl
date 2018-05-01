/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Viewport.inl
 *  \brief Inlined methods for \c OR_Viewport
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Viewport.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Viewport::GetCamera
 *
 *  \return the camera that this viewport use.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Camera* OR_Viewport::GetCamera()
{ 
	return MyCamera; 
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Viewport::SetCamera
 *
 *  \param  c the camera that this viewport use.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Viewport::SetCamera(OR_Camera* c)
{ 
	OR_ASSERT(c!=NULL); 
	MyCamera=c; 
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Viewport::GetScreenWidth
 *
 *  \return width of the viewport on the screen, in pixels.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Viewport::GetScreenWidth()
{
	return nScreenWidth_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Viewport::GetScreenHeight
 *
 *  \return height of the viewport on the screen, in pixels.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Viewport::GetScreenHeight()
{
	return nScreenHeight_;
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

