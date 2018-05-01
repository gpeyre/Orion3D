
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Font_ABC.h
 *  \brief Definition of class \c OR_Font_ABC
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Font_ABC_h_
#define __OR_Font_ABC_h_

#include "../configuration/OR_Config.h"

#include "../../ftgl/FTGLOutlineFont.h"
#include "../../ftgl/FTGLPolygonFont.h"
#include "../../ftgl/FTGLBitmapFont.h"
#include "../../ftgl/FTGLTextureFont.h"
#include "../../ftgl/FTGLPixmapFont.h"
#include "../objects/OR_Camera.h"
#include "../input_output/OR_Viewport.h"
#include "../utils/OR_SmartCounter.h"



#ifdef _USE_FTGL_
	#ifdef OR_DEBUG
		#pragma comment (lib, "ftglDlld.lib")
	#else
		#pragma comment (lib, "ftglDll.lib")
	#endif	// OR_DEBUG
#endif // _USE_FTGL_

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Font_ABC
 *  \brief  base class for all fonts.
 *  \author Gabriel Peyré 2001-11-13
 *
 *	A font can be rendered in 2 mode :
 *		- screen space : using screen absolute coordonates.
 *		- world space : using a square gizmo to get the position, orientation and size.
 *	
 *	The font system uses the \b FTGL wrapper for \b OpenGL, wich uses \b FreeType2 to
 *	to build the fonts.
 */ 
/*------------------------------------------------------------------------------*/

class OR_Font_ABC:	public OR_SmartCounter
{

public:

    OR_Font_ABC();
    virtual ~OR_Font_ABC();
	
	
	enum T_FontRenderingMode
	{
		kFontRenderingMode_Screen,
		kFontRenderingMode_World
	};

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetRenderingMode(OR_Font_ABC::T_FontRenderingMode RenderingMode);
	OR_Font_ABC::T_FontRenderingMode GetRenderingMode();

	void SetPosition(OR_Float rPosX, OR_Float rPosY);
	void SetPositionX(OR_Float rPosX);
	void SetPositionY(OR_Float rPosY);
	OR_Float GetPositionX();
	OR_Float GetPositionY();
    //@}

	virtual void Draw(char* text) = 0;
	virtual void Draw();

	void SetText(char* pText);
	char* GetText();

	OR_Bool LoadFont(const char* fileName);
	OR_Bool LoadFont(OR_String& fileName);
	OR_Bool SetFaceSize(OR_U32 nFaceSize);

    //-------------------------------------------------------------------------
    /** @name activity management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool IsActive();
	OR_Bool Disable();
	OR_Bool Enable();
	OR_Bool Toggle();
    //@}


protected:

	/** the \b FTGL font */
	FTFont* pFont_;

	/** pointer on the text to display */
	char* pText_;

	/** rendering mode for the font */
	T_FontRenderingMode RenderingMode_;

	/** position of the inscription in screen space on X axis, in [0,1] */
	OR_Float rPosX_;
	/** position of the inscription in screen space on Y axis, in [0,1] */
	OR_Float rPosY_;

	/** is the inscription active ? */
	OR_Bool bIsActive_;

};

/**a map of font for the FontManager (we can't use Orion3D templates) */
typedef map<OR_I32, OR_Font_ABC*>		T_FontMap;
typedef T_FontMap::iterator		IT_FontMap;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Font_ABC.inl"
#endif


#endif // __OR_Font_ABC_h_

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

