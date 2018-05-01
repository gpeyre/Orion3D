//*****************************************************************************
/// \author Gabriel Peyré
//*****************************************************************************

#ifndef __OR_InputOutput_Win32_h_
#define __OR_InputOutput_Win32_h_

#ifdef __GNUG__
    #pragma interface
#endif

#include "../configuration/OR_Config.h"
#include "../input_output/OR_InputOutput_ABC.h"
#include "resource.h"

namespace OR {

typedef void ( * OR_WindowsMenu_Func )( UINT item , UINT flags, HMENU hmenu );

//=============================================================================
/**
*   @class  OR_InputOutput_Win32
*   @brief  Input/output wrapper for Win32 API.
*/
/// \author Gabriel Peyré
//=============================================================================
class OR_InputOutput_Win32: public OR_InputOutput_ABC
{

public:

    OR_InputOutput_Win32(OR_Renderer_ABC& Renderer);
    virtual ~OR_InputOutput_Win32();

	//-------------------------------------------------------------------------
    /** @name overload of OR_InputOutput_ABC methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void Initialisation(int *argc, char **argv, char* name,
								OR_I32 largeur=640, OR_I32 hteur=480,
								OR_I32 posx=0, OR_I32 posy=0);
	virtual void SetupPixelFormat(int *argc, char **argv);
	virtual void PostReDisplay();
	virtual void Swap();
	virtual void MainLoop();
    //@}
	
    //-------------------------------------------------------------------------
    /** @name API-specific default callbacks */
    //-------------------------------------------------------------------------
    //@{
	static void Default_Destroy();
	static void Default_KeyPressed(OR_U32 button, OR_I32 x, OR_I32 y);
	static void Default_Mouseclic(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y);
	static void Default_WindowsMenu(UINT item , UINT flags, HMENU hmenu);
	static LRESULT CALLBACK Default_WinProc(HWND hwnd, UINT uMsg,
											   WPARAM wParam, LPARAM lParam);

    //@}

	//-------------------------------------------------------------------------
    /** @name Win32 specific methods */
    //-------------------------------------------------------------------------
    //@{
	HWND Initialisation_Win32(HINSTANCE HInst, HWND hParent, DWORD dUserStyle, char* name,
								OR_I32 largeur=640, OR_I32 hauteur=480,
								OR_I32 posx=0, OR_I32 posy=0,
								HICON WindowIcon=NULL, char* MenuName=NULL); 
	void SetWindowsMenuFunc( OR_WindowsMenu_Func WindowsMenuFunc ); 
	OR_WindowsMenu_Func GetWindowsMenuFunc(); 


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
 	/** get the state of the middle mouse button */
	virtual OR_Bool GetMiddleButtonState();
   //@}

private:

    //-------------------------------------------------------------------------
    /** @name Win32 specific datas */
    //-------------------------------------------------------------------------
    //@{
	/** copy of the current instance */
	HINSTANCE HInst;
	/** copy of the current device context */
	HDC	DC;
	/** copy of the current rendering context*/
	HGLRC RC;
	/** copy of the current windows */
	HWND OpenGLWindow;
	/** mouse state */
	OR_Bool bLeft,bRight,bMiddle;
	/** window class already registered ? */
	static OR_Bool bRegistered;
	/** Mouse position */
	OR_I32 m_MouseX, m_MouseY;
	/** function that handles the menu if the window */ 
	OR_WindowsMenu_Func m_WindowsMenuFunc; 

    //@}

    //-------------------------------------------------------------------------
    /** @name Win32 specific methods */
    //-------------------------------------------------------------------------
    //@{
	void Reshape_Win32(OR_I32 w, OR_I32 h);
    //@}



};

} // End namespace OR



#endif // __OR_InputOutput_Win32_h_
