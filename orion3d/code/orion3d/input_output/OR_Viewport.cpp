/*-------------------------------------------------------------*/
/*                    OR_Viewport.cpp                          */
/*-------------------------------------------------------------*/
/* implementation of class used to handle multiple viewports   */
/*-------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Viewport.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Viewport.h"

#ifndef OR_USE_INLINE
	#include "OR_Viewport.inl"
#endif

namespace OR
{
	
/*-------------------------------------------------------------*/
/*                     class OR_Viewport                       */
/*-------------------------------------------------------------*/
/* a viewport with a camera to render the scene                */
/*-------------------------------------------------------------*/

OR_Viewport::OR_Viewport(OR_Renderer_ABC& Renderer, OR_Camera* camera)
{
	pRenderer_ = &Renderer;
	MyCamera=camera;
	Lower_Left_X=Lower_Left_Y=0;
	Width=Height=1;
	UsePerCent=true;
}

void OR_Viewport::SetDimensions(OR_Float ll_x, OR_Float ll_y, OR_Float width, OR_Float height)
{
	Lower_Left_X=ll_x;
	Lower_Left_Y=ll_y;
	Width=width;
	Height=height;
}

void OR_Viewport::Enable()
{
	IsActive=true;
}

void OR_Viewport::Disable()
{
	IsActive=false;
}

OR_Bool OR_Viewport::Toggle()
{
	return (IsActive=!IsActive);
}

void OR_Viewport::EnableUsePerCent()
{
	UsePerCent=true;
}

void OR_Viewport::DisableUsePerCent()
{
	UsePerCent=false;
}

/*-------------------------------------------------------------*/
/*                     class OR_Viewport_Screen                */
/*-------------------------------------------------------------*/
/* a classical viewport that render to screen                  */
/*-------------------------------------------------------------*/

OR_Viewport_Screen::OR_Viewport_Screen(OR_Renderer_ABC& Renderer, OR_Camera* mycamera)
:OR_Viewport(Renderer, mycamera)
{
	Color[R]=0;
	Color[V]=0;
	Color[B]=0;
	Color[A]=1;
}

void OR_Viewport_Screen::Display(OR_I32 w, OR_I32 h)
{
	if (IsActive)
	{
		OR_I32 ll_x, ll_y;
		/* compute the dimensions of the windows */
		if (UsePerCent)
		{
			ll_x=(OR_I32) Lower_Left_X*w;
			ll_y=(OR_I32) Lower_Left_Y*h;
			nScreenWidth_  = (OR_I32) Width*w;
			nScreenHeight_ = (OR_I32) Height*h;
		}
		else 
		{
			ll_x = (OR_I32) Lower_Left_X;
			ll_y = (OR_I32) Lower_Left_Y;
			nScreenWidth_  = (OR_I32) Width;
			nScreenHeight_ = (OR_I32)Height;
		}		
		glViewport(ll_x, ll_y, (GLsizei) (nScreenWidth_), (GLsizei) (nScreenHeight_));
		/* set opengl parameters */
		glScissor(ll_x, ll_y, nScreenWidth_, nScreenHeight_);
		glEnable(GL_SCISSOR_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);

		/* set blending on */
		OR_Globals::Context()->SetBlendingMode(OR_Blending_SrcA_1MinusSrcA);

		glEnable(GL_DEPTH_WRITEMASK);

		OR_Globals::Context()->DisableDepthTesting();
		OR_Globals::Context()->SimpleDrawMode();

		/* set up orthogonal projection */
		glMatrixMode(GL_PROJECTION );
		glLoadIdentity();
		glOrtho(0, 1, 0, 1, -1000, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		/* draw a square */
		OR_Globals::Context()->SetColor(Color);
		OR_Globals::Context()->SetCullingMode(OR_Culling_None);
		glBegin(GL_QUADS);
			glVertex3f(1,0,0);
			glVertex3f(1,1,0);
			glVertex3f(0,1,0);
			glVertex3f(0,0,0);
		glEnd();
		OR_Globals::Context()->SetDefaultCullingMode();
		
		OR_Globals::Context()->NormalDrawMode();
		OR_Globals::Context()->SetDefaultDepthTestingMode();
		glDisable(GL_DEPTH_WRITEMASK);
		
		/* re-set blending to default value */
		OR_Globals::Context()->SetDefaultBlendingMode();

		glDisable(GL_SCISSOR_TEST);
		/* draw the scene */	
		OR_ASSERT(MyCamera);
		/* TODO : compute this only once per reshape ... */
		MyCamera->SetAspect(((OR_Float)nScreenWidth_)/((OR_Float)nScreenHeight_));
		glViewport(ll_x, ll_y, (GLsizei) (nScreenWidth_), (GLsizei) (nScreenHeight_));
		MyCamera->SetProjectionMatrix();
		/* draw the scene using this camera */
		OR_Globals::CameraManager()->SetActiveCamera(MyCamera);
		pRenderer_->RenderToViewport(*this);
	}
}


void OR_Viewport_Screen::SetColor(OR_Float color[4])
{
	Color[R]=color[R];
	Color[V]=color[V];
	Color[B]=color[B];
	Color[A]=color[A];
}

/*-------------------------------------------------------------*/
/*                     class OR_Viewport_FeedBack              */
/*-------------------------------------------------------------*/
/* a classical viewport that render to screen                  */
/*-------------------------------------------------------------*/

OR_Viewport_FeedBack::OR_Viewport_FeedBack(OR_Renderer_ABC& Renderer, OR_Camera* mycamera, OR_Texture* mytexture)
:OR_Viewport(Renderer, mycamera)
{
	MyTexture=mytexture;
}

void OR_Viewport_FeedBack::Display(OR_I32 w, OR_I32 h)
{
	if (IsActive)
	{
		OR_ASSERT(MyCamera);
		OR_ASSERT(MyTexture);
		/* TODO : compute this only once per reshape ... */
		MyCamera->SetAspect(((OR_Float)(Width*w))/((OR_Float)(Height*h)));
		MyCamera->SetProjectionMatrix();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |	GL_STENCIL_BUFFER_BIT);
		/* draw the scene using this camera */
		OR_Globals::CameraManager()->SetActiveCamera(MyCamera);
		pRenderer_->RenderToViewport(*this);
		/* use feed back mode to build the texture */
		MyTexture->BuildFromScreen((OR_I32) (Lower_Left_X*w), (OR_I32) (Lower_Left_Y*h), (OR_I32) (Width*w), (OR_I32) (Height*h));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |	GL_STENCIL_BUFFER_BIT);
	}
}

void OR_Viewport_FeedBack::SetTexture(OR_Texture *texture)
{
	MyTexture=texture;
}

/*-------------------------------------------------------------*/
/*                     class OR_ViewportManager                */
/*-------------------------------------------------------------*/
/* manager of all viewpport used to render the scene           */
/*-------------------------------------------------------------*/

OR_ViewportManager::OR_ViewportManager(OR_Renderer_ABC& Renderer)
:OR_PiorityManager_Template<OR_Viewport>()
{
	pRenderer_ = &Renderer;
	Width=640;
	Height=480;
}

OR_I32 OR_ViewportManager::AddScreenViewPort(OR_Camera* mycamera, OR_I32 prio)
{
	OR_ASSERT( pRenderer_!=NULL );
	OR_Viewport_Screen* new_viewport;
	new_viewport=new OR_Viewport_Screen(*pRenderer_, mycamera);
	return AddElement(new_viewport, prio);
}

OR_I32 OR_ViewportManager::AddFeedBackViewPort(OR_Camera* mycamera, OR_Texture* mytexture, OR_I32 prio)
{
	OR_Viewport_FeedBack* new_viewport;
	new_viewport=new OR_Viewport_FeedBack(*pRenderer_, mycamera, mytexture);
	return AddElement(new_viewport, prio);
}

OR_I32 OR_ViewportManager::SetDimensions(OR_Float ll_x, OR_Float ll_y, OR_Float width, OR_Float height)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetDimensions(ll_x, ll_y, width, height);
	return OR_OK;
}

void OR_ViewportManager::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |	GL_STENCIL_BUFFER_BIT);

	OR_PiorityManagerElt_Template<OR_Viewport> *e=Root;
	while (e!=NULL) 
	{
		e->Element->Display(Width, Height);
		e=e->Son;
	}
}

void OR_ViewportManager::Reshape(OR_I32 w, OR_I32 h)
{
	Width=w;
	Height=h;
}

OR_I32 OR_ViewportManager::SetCamera(OR_Camera* camera)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->SetCamera(camera);
	return OR_OK;
}

OR_I32 OR_ViewportManager::Enable()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->Enable();
	return OR_OK;
}

OR_I32 OR_ViewportManager::Disable()
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	GetElementSelected()->Disable();
	return OR_OK;
}

OR_Bool OR_ViewportManager::Toggle()
{
	if (IsSelectedEmpty()) return false;
	return GetElementSelected()->Toggle();
}

OR_I32 OR_ViewportManager::SetTexture(OR_Texture *texture)
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetViewportType())
	{
	case OR_VIEWPORT_FeedBack:
		((OR_Viewport_FeedBack*)GetElementSelected())->SetTexture(texture);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	}
	GetElementSelected()->Disable();
	return OR_OK;
}

OR_I32 OR_ViewportManager::SetColor(OR_Float color[4])
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	switch (GetElementSelected()->GetViewportType())
	{
	case OR_VIEWPORT_Screen:
		((OR_Viewport_Screen*)GetElementSelected())->SetColor(color);
		break;
	default:
		return OR_Manager_InvalidSelectedType;
		break;
	}
	return OR_OK;
}

OR_I32 OR_ViewportManager::SetPriority(OR_I32 prio)
{
	if (IsSelectedEmpty()) return false;
	ChangePriority(prio);
	return OR_OK;
}

OR_I32 OR_ViewportManager::EnableUsePerCent()
{
	if (IsSelectedEmpty()) return false;
	GetElementSelected()->EnableUsePerCent();
	return OR_OK;
}

OR_I32 OR_ViewportManager::DisableUsePerCent()
{
	if (IsSelectedEmpty()) return false;
	GetElementSelected()->DisableUsePerCent();
	return OR_OK;
}

} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////