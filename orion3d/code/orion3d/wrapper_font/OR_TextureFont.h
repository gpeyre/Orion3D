
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_TextureFont.h
 *  \brief Definition of class \c OR_TextureFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_TextureFont_h_
#define __OR_TextureFont_h_

#include "../configuration/OR_Config.h"
#include "OR_Font_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_TextureFont
 *  \brief  tesselated Polygon Mesh fonts
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/

class OR_TextureFont: public OR_Font_ABC
{

public:

    OR_TextureFont();
	virtual void Draw(char* text);	

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_TextureFont.inl"
#endif


#endif // __OR_TextureFont_h_

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

