/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_BitmapFont.inl
 *  \brief Inlined methods for \c OR_BitmapFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_BitmapFont.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_BitmapFont constructor
 *
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_BitmapFont::OR_BitmapFont()
:	OR_Font_ABC()
{
	pFont_ = new FTGLBitmapFont();
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

