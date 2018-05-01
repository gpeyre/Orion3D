/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_OutlineFont.cpp
 *  \brief Definition of class \c OR_OutlineFont
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_OutlineFont.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_OutlineFont.h"

#ifndef OR_USE_INLINE
	    #include "OR_OutlineFont.inl"
#endif

using namespace OR;

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_OutlineFont::Draw
 *
 *  \param  text the text to output.
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
void OR_OutlineFont::Draw(char* text)
{
	OR_ASSERT( text!=NULL );
	OR_ASSERT( pFont_!=NULL );

	OR_Viewport* pViewport = OR_Globals::ViewportManager()->GetElementSelected();
	OR_ASSERT(pViewport!=NULL);

	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, pViewport->GetScreenWidth(), 0, pViewport->GetScreenHeight(), -100000.0, 100000.0);
	glMatrixMode(GL_MODELVIEW);

	
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(rPosX_*pViewport->GetScreenWidth(), rPosY_*pViewport->GetScreenHeight(), 0);		
		pFont_->render(text);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
		glPushMatrix();
	glMatrixMode(GL_MODELVIEW);

	OR_ASSERT( text!=NULL );
	OR_ASSERT( pFont_!=NULL );
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

