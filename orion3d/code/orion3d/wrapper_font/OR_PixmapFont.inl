/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PixmapFont.inl
 *  \brief Inlined methods for \c OR_PixmapFont
 *  \author Gabriel Peyr� 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_PixmapFont.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PixmapFont constructor
 *
 *  \author Gabriel Peyr� 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_PixmapFont::OR_PixmapFont()
:	OR_Font_ABC()
{
	pFont_ = new FTGLPixmapFont();
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

