
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_OutlineFont.h
 *  \brief Definition of class \c OR_OutlineFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_OutlineFont_h_
#define __OR_OutlineFont_h_

#include "../configuration/OR_Config.h"
#include "OR_Font_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_OutlineFont
 *  \brief  tesselated Polygon Mesh fonts
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/

class OR_OutlineFont: public OR_Font_ABC
{

public:

    OR_OutlineFont();
	virtual void Draw(char* text);	

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_OutlineFont.inl"
#endif


#endif // __OR_OutlineFont_h_

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

