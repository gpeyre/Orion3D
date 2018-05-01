//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

static const char* sccsid = "@(#) OR_InputOutput_ABC.cpp (c) Mathématiques Appliquées SA 2001";

#ifdef __GNUG__
    #pragma implementation
#endif

#include "../stdafx.h"
#include "OR_InputOutput_ABC.h"

#ifndef OR_USE_INLINE
#   include "OR_InputOutput_ABC.inl"
#endif

using namespace OR;

//-------------------------------------------------------------------------
/** @name initialize static attributes */
//-------------------------------------------------------------------------
//@{
OR_InputOutput_ABC* OR_InputOutput_ABC::StaticThis_ = NULL;
OR_Renderer_ABC*	OR_InputOutput_ABC::pRenderer_	= NULL;
//@}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_ABC constructor
/**
*   @param  Renderer Copy of the main Renderer
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_InputOutput_ABC::OR_InputOutput_ABC(OR_Renderer_ABC& Renderer)
{
	pRenderer_ = &Renderer;
	StaticThis_ = this;
	/* initialize mouse varibles */
	BoutG=BoutD=false;
	XMouse=YMouse=0;

	/* initialize callback functions */
	Display=Default_Display;
	Reshape=Default_Reshape;
	Mouse=Default_Mouse;
	Passmotion=Default_Passmotion;
	Idle=Default_Idle;
	KeyReleased=Default_KeyReleased;
	Special=Default_Special;
}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_ABC destructor
/**
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_InputOutput_ABC::~OR_InputOutput_ABC()
{
	StaticThis_ = NULL;
	pRenderer_ = NULL;
}

void OR_InputOutput_ABC::Default_Display(void)
{
	OR_ASSERT(StaticThis_!=NULL);
	pRenderer_->RenderAllViewport();
	StaticThis_->Swap();
}


void OR_InputOutput_ABC::Default_Reshape(OR_I32 w, OR_I32 h)
{
	pRenderer_->Reshape(w,h);
}

void OR_InputOutput_ABC::Default_Mouse(OR_I32 x, OR_I32 y)
{
	/* NOTHING */
}

void OR_InputOutput_ABC::Default_Passmotion(OR_I32 x, OR_I32 y)
{
	OR_ASSERT(StaticThis_!=NULL);
	StaticThis_->XMouse = x;
    StaticThis_->YMouse = y;
}

void OR_InputOutput_ABC::Default_Idle(void)
{
	pRenderer_->Update();
	/* re-draw everything */
	StaticThis_->PostReDisplay();
}

void OR_InputOutput_ABC::Default_KeyReleased(OR_U32 button, OR_I32 x, OR_I32 y)
{

}


void OR_InputOutput_ABC::Default_Special(OR_I32 key, OR_I32 x, OR_I32 y)
{
	
}

void OR_InputOutput_ABC::Default_Init()
{

}

