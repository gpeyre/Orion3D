/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Font_ABC.inl
 *  \brief Inlined methods for \c OR_Font_ABC
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Font_ABC.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC constructor
 *
 *  \param  fileName name of the font file to load.
 *  \param  nFaceSize the size of the face.
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Font_ABC::OR_Font_ABC()
:	OR_SmartCounter	(),
	pFont_			( NULL ),
	RenderingMode_	( OR_Font_ABC::kFontRenderingMode_Screen ),
	rPosX_			( 0 ),
	rPosY_			( 0 ),
	pText_			( NULL )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC destructor
 *
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Font_ABC::~OR_Font_ABC()
{
	OR_DELETE( pFont_ );
}

	


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::SetRenderingMode
 *
 *  \param  RenderingMode the mode used to render the font (screen/world).
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Font_ABC::SetRenderingMode(OR_Font_ABC::T_FontRenderingMode RenderingMode)
{
	RenderingMode_ = RenderingMode;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::T_FontRenderingMode 
 *
 *  \return the mode used to render the font (screen/world).
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Font_ABC::T_FontRenderingMode OR_Font_ABC::GetRenderingMode()
{
	return RenderingMode_;
}

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::SetPosition
 *
 *  \param  rPosX position on X axis (can be world or screen relative).
 *  \param  rPosY position on Y axis (can be world or screen relative)
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Font_ABC::SetPosition(OR_Float rPosX, OR_Float rPosY)
{
	rPosX_ = rPosX;
	rPosY_ = rPosY;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::SetPositionX
 *
 *  \param  rPosX position on X axis (can be world or screen relative).
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Font_ABC::SetPositionX(OR_Float rPosX)
{
	rPosX_ = rPosX;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::SetPositionY
 *
 *  \param  rPosY position on Y axis (can be world or screen relative).
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Font_ABC::SetPositionY(OR_Float rPosY)
{
	rPosY_ = rPosY;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::GetPositionX
 *
 *  \return position on X axis (can be world or screen relative).
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Font_ABC::GetPositionX()
{
	return rPosX_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::GetPositionY
 *
 *  \return position on Y axis (can be world or screen relative).
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_Font_ABC::GetPositionY()
{
	return rPosY_;
}

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::LoadFont
 *
 *  \param  fileName name of the font file to load.
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Font_ABC::LoadFont(const char* fileName)
{
	OR_ASSERT( fileName!=NULL );
	OR_ASSERT( pFont_!=NULL );
	return pFont_->Open(fileName);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::LoadFont
 *
 *  \param  fileName name of the font file to load.
 *  \return was the operation succesful ?
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Font_ABC::LoadFont(OR_String& fileName)
{
	OR_ASSERT( fileName.val()!=NULL );
	OR_ASSERT( pFont_!=NULL );
	return pFont_->Open(fileName.val());
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::SetFaceSize
 *
 *  \param  nFaceSize the size of the face.
 *  \return was the operation succesful ?
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Font_ABC::SetFaceSize(OR_U32 nFaceSize)
{
	OR_ASSERT( pFont_!=NULL );
	return pFont_->FaceSize(nFaceSize);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::SetText
 *
 *  \param  pText the text to display automaticaly.
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Font_ABC::SetText(char* pText)
{
	pText_ = pText;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Font_ABC::GetText
 *
 *  \return the text to display automaticaly.
 *  \author Gabriel Peyré 2001-11-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
char* OR_Font_ABC::GetText()
{
	return pText_;
}


//-----------------------------------------------------------------------------
// Name: OR_Font_ABC::GetActivity
/**
*   \return is the object active or not ?
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Font_ABC::IsActive()
{ 
	return bIsActive_; 
}

//-----------------------------------------------------------------------------
// Name: OR_Font_ABC::Disable
/**
*   \return previous activity 
*
*	Disable the object for rendering
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Font_ABC::Disable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = false; 
	return old;
}



//-----------------------------------------------------------------------------
// Name: OR_Font_ABC::Enable
/**
*   \return previous activity 
*
*	Enable the object for rendering
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Font_ABC::Enable()
{
	OR_Bool old   = bIsActive_; 
	bIsActive_ = true; 
	return old;
}

//-----------------------------------------------------------------------------
// Name: OR_Font_ABC::Toggle
/**
*   \return Current activity.
*
*	Toggel on/off the object for rendering.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_Bool OR_Font_ABC::Toggle()
{
	bIsActive_=!bIsActive_; 
	return bIsActive_;
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

