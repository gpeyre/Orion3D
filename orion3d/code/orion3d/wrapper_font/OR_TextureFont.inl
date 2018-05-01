/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_TextureFont.inl
 *  \brief Inlined methods for \c OR_TextureFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_TextureFont.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_TextureFont constructor
 *
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_TextureFont::OR_TextureFont()
:	OR_Font_ABC()
{
	pFont_ = new FTGLTextureFont();
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

