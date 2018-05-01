//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#pragma once
#ifndef __OR_InputOutput_ABC_h_
#define __OR_InputOutput_ABC_h_


#include "../configuration/OR_Config.h"
#include "OR_Renderer_ABC.h"
#include "../utils/OR_ExceptionHandler.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_InputOutput_ABC
*   @brief  Base class for every input/output wrapper.
*
*	Class should had API-specific default methods :
*		- Default_Destroy
*		- Default_KeyPressed
*		- Default_Mouseclic
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class ORION3D_API OR_InputOutput_ABC
{

public:

    OR_InputOutput_ABC(OR_Renderer_ABC& Renderer);
    virtual ~OR_InputOutput_ABC();

    //-------------------------------------------------------------------------
    /** @name methods to overload */
    //-------------------------------------------------------------------------
    //@{
	virtual void Initialisation(int *argc, char **argv, char* name,
								OR_I32 largeur=640, OR_I32 hteur=480,
								OR_I32 posx=0, OR_I32 posy=0)=0;
	virtual void SetupPixelFormat(int *argc, char **argv)=0;
	virtual void PostReDisplay()=0;
	virtual void Swap()=0;
	virtual void MainLoop()=0;
    //@}

    //-------------------------------------------------------------------------
    /** @name set callback functions */
    //-------------------------------------------------------------------------
    //@{
	/** function to use when nothing to do */
	void SetIdleFunc(OR_Idle_Func idle);
	/** function to use to render the scene */
	void SetDisplayFunc(OR_Display_Func display);
	/** function to use when a resize occurs */
	void SetReshapeFunc(OR_Reshape_Func reshape);
	/** function to use when a mouse clic occurs */
	void SetMouseClicFunc(OR_Mouseclic_Func mouseclic);
	/** function to use when a mouse move occurs */
	void SetMotionFunc(OR_Mouse_Func mouse);
	/** function to use when a passive mouse move occur */
	void SetPassiveMotionFunc(OR_Passmotion_Func passmotion);
	/** function to use when a key is pressed */
	void SetKeyPressedFunc(OR_KeyPressed_Func  keypressed);
	/** function to use when a key is released */
	void SetKeyReleasedFunc(OR_KeyReleased_Func  keyreleased);
	/** function to use when a special key is pressed */
	void SetSpecialFunc(OR_Special_Func special);
	/** function to use for initialisation */
	void SetInitFunc(OR_Init_Func init);
	/** function to use when the window is destroyed */
	void SetDestroyFunc(OR_Destroy_Func destroy);
    //@}

    //-------------------------------------------------------------------------
    /** @name accessors */
    //-------------------------------------------------------------------------
    //@{
	/** get X mouse pointer position */
	virtual OR_I32 GetMousePosX();
	/** get Y mouse pointer position */
	virtual OR_I32 GetMousePosY();
	/** set X mouse pointer position */
	virtual void SetMousePosX(OR_I32 pos);
	/** set Y mouse pointer position */
	virtual void SetMousePosY(OR_I32 pos);
	/** get the state of the left mouse button */
	virtual OR_Bool GetLeftButtonState();
	/** get the state of the right mouse button */
	virtual OR_Bool GetRightButtonState();
	/** set the state of the left mouse button */
	virtual void SetLeftButtonState(OR_Bool state);
	/** set the state of the right mouse button */
	virtual void SetRightButtonState(OR_Bool state);

	OR_Idle_Func		GetIdleFunc();
	OR_Display_Func		GetDisplayFunc();
	OR_Reshape_Func		GetReshapeFunc();
	OR_Mouseclic_Func	GetMouseClicFunc();
	OR_Mouse_Func		GetMotionFunc();
	OR_Passmotion_Func	GetPassiveMotionFunc();
	OR_KeyPressed_Func	GetKeyPressedFunc();
	OR_KeyReleased_Func	GetKeyReleasedFunc();
	OR_Special_Func		GetSpecialFunc();
	OR_Init_Func		GetInitFunc();
	OR_Destroy_Func		GetDestroyFunc();
    //@}

    //-------------------------------------------------------------------------
    /** @name helpers methods */
    //-------------------------------------------------------------------------
    //@{
	/** initialize EVERYTHING :
			- initialize opengl
			- initialize output functions
	*/
	void InitGL();
    //@}

protected:

	static OR_InputOutput_ABC* StaticThis_;

	/** copy of the main orion */
	static OR_Renderer_ABC* pRenderer_;

    //-------------------------------------------------------------------------
    /** @name to handle the mouse */
    //-------------------------------------------------------------------------
    //@{
	/** x position of the mouse */
	OR_I32 XMouse;
	/** y position of the mouse */
	OR_I32 YMouse;
	/** left button state */
	OR_Bool BoutD;
	/** right button state */
	OR_Bool BoutG;
    //@}

    //-------------------------------------------------------------------------
    /** @name to store callback functions */
    //-------------------------------------------------------------------------
    //@{
	/** current display function. */
	OR_Display_Func Display;
	/** current reshape function. */
	OR_Reshape_Func Reshape;
	/** current mouse clic function. */
	OR_Mouseclic_Func Mouseclic;
	/** current mouse active move function. */
	OR_Mouse_Func Mouse;
	/** current pass mouse motion function. */
	OR_Passmotion_Func Passmotion;
	/** current idling function. */
	OR_Idle_Func Idle;
	/** current key pressed function. */
	OR_KeyPressed_Func KeyPressed;
	/** current key realeased function. */
	OR_KeyReleased_Func KeyReleased;
	/** current special key function. */
	OR_Special_Func Special;
	/** current initialisation function. */
	OR_Init_Func Init;
	/** current destroy function. */
	OR_Destroy_Func Destroy;
    //@}

    //-------------------------------------------------------------------------
    /** @name default callback functions */
    //-------------------------------------------------------------------------
    //@{
	/** default display function. */
	static void Default_Display(void);
	/** default reshape function. */
	static void Default_Reshape(OR_I32 w, OR_I32 h);
	/** default mouse active move function. */
	static void Default_Mouse(OR_I32 x, OR_I32 y);
	/** default pass mouse motion function. */
	static void Default_Passmotion(OR_I32 x, OR_I32 y);
	/** default idling function. */
	static void Default_Idle(void);
	/** default key realeased function. */
	static void Default_KeyReleased(OR_U32 button, OR_I32 x, OR_I32 y);
	/** default special key function. */
	static void Default_Special(OR_I32 key, OR_I32 x, OR_I32 y);
	/** default initialisation function. */
	static void Default_Init();
    //@}

};

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_InputOutput_ABC.inl"
#endif


#endif // __OR_InputOutput_ABC_h_
