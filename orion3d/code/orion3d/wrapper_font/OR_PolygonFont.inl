/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PolygonFont.inl
 *  \brief Inlined methods for \c OR_PolygonFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_PolygonFont.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PolygonFont constructor
 *
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_PolygonFont::OR_PolygonFont()
:	OR_Font_ABC()
{
	pFont_ = new FTGLPolygonFont();
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

