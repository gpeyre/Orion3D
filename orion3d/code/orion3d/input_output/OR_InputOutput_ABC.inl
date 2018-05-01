//*****************************************************************************
///	\author Gabriel Peyré 2001-08-30
//*****************************************************************************

#include "OR_InputOutput_ABC.h"

namespace OR {

	
OR_INLINE	
void OR_InputOutput_ABC::SetIdleFunc(OR_Idle_Func idle)
{
	Idle=idle;
}

OR_INLINE
void OR_InputOutput_ABC::SetDisplayFunc(OR_Display_Func display)
{
	Display=display;
}

OR_INLINE
void OR_InputOutput_ABC::SetReshapeFunc(OR_Reshape_Func reshape)
{
	Reshape=reshape;
}

OR_INLINE
void OR_InputOutput_ABC::SetMouseClicFunc(OR_Mouseclic_Func mouseclic)
{
	Mouseclic=mouseclic;
}

OR_INLINE
void OR_InputOutput_ABC::SetMotionFunc(OR_Mouse_Func mouse)
{
	Mouse=mouse;
}

OR_INLINE
void OR_InputOutput_ABC::SetPassiveMotionFunc(OR_Passmotion_Func passmotion)
{
	Passmotion=passmotion;
}

OR_INLINE
void OR_InputOutput_ABC::SetKeyPressedFunc(OR_KeyPressed_Func keyboard)
{
	KeyPressed=keyboard;
}

OR_INLINE
void OR_InputOutput_ABC::SetKeyReleasedFunc(OR_KeyReleased_Func keyboard)
{
	KeyReleased=keyboard;
}

OR_INLINE
void OR_InputOutput_ABC::SetSpecialFunc(OR_Special_Func special)
{
	Special=special;
}

OR_INLINE
void OR_InputOutput_ABC::SetInitFunc(OR_Init_Func init)
{
	Init=init;
}

OR_INLINE
void OR_InputOutput_ABC::SetDestroyFunc(OR_Destroy_Func destroy)
{
	Destroy=destroy;
}





/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::OR_Idle_Func		
 *
 *  \return the function called when nothing occurs
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Idle_Func OR_InputOutput_ABC::GetIdleFunc()
{
	return Idle;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetDisplayFunc
 *
 *  \return the function called to render to screen.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Display_Func OR_InputOutput_ABC::GetDisplayFunc()
{
	return Display;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::OR_Reshape_Func	
 *
 *  \return the function called when the windows is reshaped.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Reshape_Func	OR_InputOutput_ABC::GetReshapeFunc()
{
	return Reshape;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetMouseClicFunc
 *
 *  \return the function called when a mouse button is pressed.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Mouseclic_Func OR_InputOutput_ABC::GetMouseClicFunc()
{
	return Mouseclic;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetMotionFunc
 *
 *  \return the function that is called when the mouse move with a button pressed.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Mouse_Func OR_InputOutput_ABC::GetMotionFunc()
{
	return Mouse;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetPassiveMotionFunc
 *
 *  \return the function that is called when the mouse is moved with no key pressed.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Passmotion_Func OR_InputOutput_ABC::GetPassiveMotionFunc()
{
	return Passmotion;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetKeyPressedFunc
 *
 *  \return the function that is called when a key is pressed.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_KeyPressed_Func OR_InputOutput_ABC::GetKeyPressedFunc()
{
	return KeyPressed;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetKeyReleasedFunc
 *
 *  \return the function that is called when a key is released.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_KeyReleased_Func OR_InputOutput_ABC::GetKeyReleasedFunc()
{
	return KeyReleased;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetSpecialFunc
 *
 *  \return the function that is called when a special key is pressed.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Special_Func OR_InputOutput_ABC::GetSpecialFunc()
{
	return Special;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetInitFunc
 *
 *  \return the function that is called at initialisation.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Init_Func OR_InputOutput_ABC::GetInitFunc()
{
	return Init;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_InputOutput_ABC::GetDestroyFunc
 *
 *  \return the function that is called when the window is destroyed.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Destroy_Func OR_InputOutput_ABC::GetDestroyFunc()
{
	return Destroy;
}

/* to handle mouse variables ***************************************/
OR_INLINE
OR_I32 OR_InputOutput_ABC::GetMousePosX()
{
	return XMouse;
}

OR_INLINE
OR_I32 OR_InputOutput_ABC::GetMousePosY()
{
	return YMouse;
}

OR_INLINE
void OR_InputOutput_ABC::SetMousePosX(OR_I32 pos)
{
	XMouse=pos;
}

OR_INLINE
void OR_InputOutput_ABC::SetMousePosY(OR_I32 pos)
{
	YMouse=pos;
}

OR_INLINE
OR_Bool OR_InputOutput_ABC::GetLeftButtonState()
{
	return BoutG;
}

OR_INLINE
OR_Bool OR_InputOutput_ABC::GetRightButtonState()
{
	return BoutD;
}

OR_INLINE
void OR_InputOutput_ABC::SetLeftButtonState(OR_Bool state)
{
	BoutG=state;
}

OR_INLINE
void OR_InputOutput_ABC::SetRightButtonState(OR_Bool state)
{
	BoutD=state;
}

} // End namespace OR
