/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PixmapFont.cpp
 *  \brief Definition of class \c OR_PixmapFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_PixmapFont.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_PixmapFont.h"

#ifndef OR_USE_INLINE
	    #include "OR_PixmapFont.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PixmapFont::Draw
 *
 *  \param  text the text to output.
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
void OR_PixmapFont::Draw(char* text)
{
	OR_ASSERT( text!=NULL );
	OR_ASSERT( pFont_!=NULL );

	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, -100000.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);
	
	
	glLoadIdentity();
	glRasterPos2f(rPosX_, rPosY_);
	
	OR_Globals::Context()->SimpleDrawMode();
	pFont_->render(text);
	OR_Globals::Context()->NormalDrawMode();
	
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
}


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

