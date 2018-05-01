/*-------------------------------------------------------------*/
/*                    OR_Viewport.h                            */
/*-------------------------------------------------------------*/
/* declaration of class used to handle multiple viewports      */
/*-------------------------------------------------------------*/

/** \file 
	Contains definition of different kind of viewport, wich is an abstract object
	representing the target of the rendering. It can ba the screen [OR_Viewport_Screen] or
	a texture buffer [OR_Viewport_FeedBack].
	\author Gabriel.
**/

#ifndef _OR_VIEWPORT_H_
#define _OR_VIEWPORT_H_

#include "../configuration/OR_Config.h"
#include "OR_Renderer_ABC.h"
#include "../objects/OR_Camera.h"
#include "../shaders/OR_Texture.h"
#include "../utils/OR_PriorityManager_Template.h"

namespace OR
{
	
/*-------------------------------------------------------------*/
/*               class OR_Viewport                             */
/*-------------------------------------------------------------*/
/* super class for all viewport class                          */
/*-------------------------------------------------------------*/

/// super class for all viewport class.
/** 
	a viewport is used to render the scene 
		- with a particular point of wiew (for ex. a camera)
		- to a particular output :
		   + the screen : via class OR_Viewport_Screen
		   + a texture : via class OR_Viewport_FeedBack
	\author Gabriel
*/

class ORION3D_API OR_Viewport
{

public:

	/** constructor */
	OR_Viewport(OR_Renderer_ABC& Renderer, OR_Camera* mycamera);
	
	
    //-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	OR_Camera* GetCamera();
	void SetCamera(OR_Camera* c);

	OR_U32 GetScreenWidth();
	OR_U32 GetScreenHeight();
    //@}

	//-------------------------------------------------------------------------
    /** \name method to overload */
    //-------------------------------------------------------------------------
    //@{
	/** render the scene in the viewport */
	virtual void Display(OR_I32 w, OR_I32 h) = 0;
	/** get the type of the viewport */
	virtual OR_VIEWPORT_Type GetViewportType() = 0;
    //@}

    //-------------------------------------------------------------------------
    /** \name enable & disable methods */
    //-------------------------------------------------------------------------
    //@{
	/** enable the viewport */
	void Enable();
	/** enable the viewport */
	void Disable();
	/** toggle on/off the viewport */
	OR_Bool Toggle();
    //@}

    //-------------------------------------------------------------------------
    /** \name dimension mode management */
    //-------------------------------------------------------------------------
    //@{
	/** set percent mode */
	void EnableUsePerCent();
	/** set absolute mode */
	void DisableUsePerCent();
	/** set the dimensions of the wiewport */
	void SetDimensions(OR_Float ll_x, OR_Float ll_y, OR_Float width, OR_Float height);
    //@}

	
protected:
	
	/** copy of the main Renderer, for rendering the scene */
	OR_Renderer_ABC* pRenderer_;
	/** the camera used to render the scene */
	OR_Camera* MyCamera;
	/** lower left corner, in range [0,1] */
	OR_Float Lower_Left_X;
	/** lower left corner, in range [0,1] */
	OR_Float Lower_Left_Y;

	/** width of the viewport in range [0,1] */
	OR_Float Width;
	/** height of the viewport in range [0,1] */
	OR_Float Height;

	/** real dimension of the viewport in pixel */
	OR_U32 nScreenWidth_;
	OR_U32 nScreenHeight_;

	/** is the viewport active */
	OR_Bool IsActive;
	/** are the dimension given in percent or absolut coords ? */
	OR_Bool UsePerCent;

};


/*-------------------------------------------------------------*/
/*                     class OR_Viewport_Screen                */
/*-------------------------------------------------------------*/
/* a classical viewport that render to screen                  */
/*-------------------------------------------------------------*/

/// a classical viewport that render to screen.
/** 
	render the scene to screen using a camera.
	\author Gabriel
*/

class ORION3D_API OR_Viewport_Screen: public OR_Viewport
{
private:
	OR_Float Color[4];
public:
	/** constructor */
	OR_Viewport_Screen(OR_Renderer_ABC& Renderer, OR_Camera* mycamera);
	/** render the scene in the viewport */
	virtual void Display(OR_I32 w, OR_I32 h);
	/** get the type of the viewport */
	virtual OR_VIEWPORT_Type GetViewportType()	
	{ return OR_VIEWPORT_Screen;  }
	/** set the background color */
	void SetColor(OR_Float color[4]);
};

/*-------------------------------------------------------------*/
/*                     class OR_Viewport_FeedBack              */
/*-------------------------------------------------------------*/
/* a classical viewport that render to screen                  */
/*-------------------------------------------------------------*/

/// a viewport that render the scene to a texture.
/** 
	render the scene to texture using a camera.
	\author Gabriel
*/

class ORION3D_API OR_Viewport_FeedBack: public OR_Viewport
{
private:
	OR_Texture *MyTexture;
public:
	/** constructor */
	OR_Viewport_FeedBack(OR_Renderer_ABC& Renderer, OR_Camera* mycamera, OR_Texture* mytexture);
	/** render the scene in the viewport */
	virtual void Display(OR_I32 w, OR_I32 h);
	/** get the type of the viewport */
	virtual OR_VIEWPORT_Type GetViewportType()	
	{ 
		return OR_VIEWPORT_FeedBack; 
	}
	/** set the texture used for feedback */
	void SetTexture(OR_Texture *texture);
};


/*-------------------------------------------------------------*/
/*                     class OR_ViewportManager                */
/*-------------------------------------------------------------*/
/* manager of all viewpport used to render the scene           */
/*-------------------------------------------------------------*/

/*! \ingroup group_manager 
 *  \brief class OR_ViewportManager in group group_manager
 */

/// The manager of gizmos.
/** 
	Contains a copy of every gizmos in the hirarchy.
	This alow to have an easy acces to each gizmos.
	\author Gabriel
*/


/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_PiorityManager_Template<OR_Viewport>;

class ORION3D_API OR_ViewportManager: public OR_PiorityManager_Template<OR_Viewport>
{
	/** copy of the main renderer, for rendering the scene */
	OR_Renderer_ABC* pRenderer_;
	/** the height of the screen, in pixel */
	OR_I32 Height;
	/** the width of the screen, in pixel */
	OR_I32 Width;
public:
	/** constructor */
	OR_ViewportManager(OR_Renderer_ABC& Renderer);
	/** add a new screen viewport */
	OR_I32 AddScreenViewPort(OR_Camera* mycamera=NULL, OR_I32 prio=0);
	/** add a new viewport */
	OR_I32 AddFeedBackViewPort(OR_Camera* mycamera=NULL, OR_Texture* texture=NULL, OR_I32 prio=0);
	/** set the dimension of the wiewport */
	OR_I32 SetDimensions(OR_Float ll_x, OR_Float ll_y, OR_Float width, OR_Float height);
	/** to render the scene using all active viewport */
	void Display();
	/** called after each reshape of the window */
	void Reshape(OR_I32 w, OR_I32 h);
	/** set the camera used to render the scene */
	OR_I32 SetCamera(OR_Camera* camera);
	/** enable the viewport */
	OR_I32 Enable();
	/** enable the viewport */
	OR_I32 Disable();
	/** toggle on/off the viewport */
	OR_Bool Toggle();
	/** set the texture used for feedback */
	OR_I32 SetTexture(OR_Texture *texture);
	/** set the color of the background */
	OR_I32 SetColor(OR_Float color[4]);
	/** set the priority of the viewport */
	OR_I32 SetPriority(OR_I32 prio);
	/** set percent mode */
	OR_I32 EnableUsePerCent();
	/** set absolute mode */
	OR_I32 DisableUsePerCent();
};



} // namespace OR



#ifdef OR_USE_INLINE
	#include "OR_Viewport.inl"
#endif

#endif /* #ifndef _OR_VIEWPORT_H_ */


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