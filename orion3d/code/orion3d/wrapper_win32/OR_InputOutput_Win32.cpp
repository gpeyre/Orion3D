/*----------------------------------------------------------------------------*/
/*                         OR_InputOutput_Win32.cpp                           */
/*----------------------------------------------------------------------------*/
/* functions implementation for win32 in/out                                  */
/*----------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_InputOutput_Win32.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_InputOutput_Win32.h"
/* print a log for this project */
#include "../misc/OR_PrintBuildLog.h"

namespace OR
{

/* initialisation of static datas */
OR_Bool		OR_InputOutput_Win32::bRegistered = false;

//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Win32 constructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_InputOutput_Win32::OR_InputOutput_Win32(OR_Renderer_ABC& Renderer)
:OR_InputOutput_ABC(Renderer)
{
	Destroy = Default_Destroy;
	KeyPressed = Default_KeyPressed;
	Mouseclic = Default_Mouseclic;
	m_WindowsMenuFunc = Default_WindowsMenu;

	bLeft=false;
	bRight=false;
	bMiddle=false;
	bRegistered = false;
}


//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Win32 destructor
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
OR_InputOutput_Win32::~OR_InputOutput_Win32()
{
	if( bRegistered )
		UnregisterClass( "Orion3D window", HInst );
	bRegistered = false;
}

/* WIN32 specific functions ****************************************************/
void OR_InputOutput_Win32::PostReDisplay()
{
	Display();
}

void OR_InputOutput_Win32::Swap()
{
	SwapBuffers(DC);
}


LRESULT CALLBACK OR_InputOutput_Win32::Default_WinProc(HWND hwnd, UINT uMsg,
											   WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT    ps;
	OR_InputOutput_Win32* This = (OR_InputOutput_Win32*)GetWindowLong( hwnd, GWL_USERDATA );
	LPCREATESTRUCT CreateStruct;
	
		
	switch(uMsg)
	{
	case WM_CLOSE:
		wglMakeCurrent( NULL, NULL );
		if( This->RC ) wglDeleteContext( This->RC );
		ReleaseDC( hwnd, This->DC );
		PostQuitMessage( 0 );
		break;
	case WM_CREATE:
		CreateStruct = (LPCREATESTRUCT)lParam;
		This = (OR_InputOutput_Win32*)(CreateStruct->lpCreateParams);
		SetWindowLong( hwnd, GWL_USERDATA, (LONG)This );
		This->DC = GetDC( hwnd );
		This->SetupPixelFormat( NULL, NULL );
		This->RC = wglCreateContext( This->DC );
		if( !This->RC ) SendMessage( hwnd, WM_CLOSE, 0, 0 );
		wglMakeCurrent( This->DC, This->RC );
		break;
	case WM_SIZE:
		This->Reshape_Win32( LOWORD(lParam), HIWORD(lParam) );
		break;
	case WM_PAINT:
        BeginPaint( hwnd, &ps ); 
        EndPaint( hwnd, &ps ); 
		break;
	case WM_MOUSEMOVE:
	{
		POINTS Coords = MAKEPOINTS( lParam );
		This->GetMotionFunc()( Coords.x, Coords.y );
		This->m_MouseX = Coords.x;
		This->m_MouseY = Coords.y;
		break;
	}
	case WM_KEYDOWN:
		This->GetKeyPressedFunc()((OR_U32) wParam, This->GetMousePosX(), This->GetMousePosY() );
		break;
	case WM_KEYUP:
		This->GetKeyReleasedFunc()((OR_U32) wParam, This->GetMousePosX(), This->GetMousePosY() );
		break;
	case WM_LBUTTONDOWN:
		This->GetMouseClicFunc()( OR_BUTTON_LEFT, OR_BUTTON_DOWN, This->GetMousePosX(), This->GetMousePosY() );
		This->bLeft=true;
		SetCapture( hwnd );
		break;
	case WM_LBUTTONUP :
		This->GetMouseClicFunc()( OR_BUTTON_LEFT,OR_BUTTON_UP, This->GetMousePosX(), This->GetMousePosY() );
		This->bLeft=false;
		if( !This->bMiddle && !This->bLeft && !This->bRight ) SetCapture( NULL );
		break;
	case WM_RBUTTONDOWN:
		This->GetMouseClicFunc()( OR_BUTTON_RIGHT,OR_BUTTON_DOWN, This->GetMousePosX(), This->GetMousePosY() );
		This->bRight=true;
		SetCapture( hwnd );
		break;
	case WM_RBUTTONUP :
		This->GetMouseClicFunc()( OR_BUTTON_RIGHT,OR_BUTTON_UP, This->GetMousePosX(), This->GetMousePosY() );
		This->bRight=false;
		if( !This->bMiddle && !This->bLeft && !This->bRight ) SetCapture( NULL );
		break;
	case WM_MBUTTONDOWN:
		This->GetMouseClicFunc()( OR_BUTTON_MIDDLE,OR_BUTTON_DOWN, This->GetMousePosX(), This->GetMousePosY() );
		This->bMiddle=true;
		SetCapture( hwnd );
		break;
	case WM_MBUTTONUP :
		This->GetMouseClicFunc()( OR_BUTTON_MIDDLE,OR_BUTTON_UP, This->GetMousePosX(), This->GetMousePosY() );
		This->bMiddle=false;
		if( !This->bMiddle && !This->bLeft && !This->bRight ) SetCapture( NULL );
		break;
	case 0x020A :	// Wheel  : No WM_MOUSEWHEEL => compilation prb under 2000
		This->GetMouseClicFunc()( OR_WHEEL,(short)HIWORD(wParam), This->GetMousePosX(), This->GetMousePosY() );
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND: 
		(This->m_WindowsMenuFunc)( (UINT)LOWORD( wParam ), (UINT)HIWORD( wParam ), (HMENU)lParam ); 
		break; 

	default:
		return DefWindowProc( hwnd, uMsg, wParam, lParam );
	}

	return 0;
}

/*------------------------------------------------------------------------------ 
* Name : OR_InputOutput_Win32::SetWindowsMenuFunc 
* 
*  \param  WindowsMenuFunc EXPLANATION 
*  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION 
*  \author Antoine Bouthors 2002-01-03 
* 
* PUT YOUR COMMENTS HERE 
*------------------------------------------------------------------------------*/ 
void OR_InputOutput_Win32::SetWindowsMenuFunc( OR_WindowsMenu_Func WindowsMenuFunc ) 
{ 
	m_WindowsMenuFunc = WindowsMenuFunc; 
} 


/*------------------------------------------------------------------------------ 
* Name : OR_InputOutput_Win32::GetWindowsMenuFunc 
* 
*  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION 
*  \author Antoine Bouthors 2002-01-03 
* 
* PUT YOUR COMMENTS HERE 
*------------------------------------------------------------------------------*/ 
OR_WindowsMenu_Func OR_InputOutput_Win32::GetWindowsMenuFunc() 
{ 
	return m_WindowsMenuFunc; 
} 


void OR_InputOutput_Win32::MainLoop()
{
	MSG msg;

    while (1) { 

        while( PeekMessage( &msg, OpenGLWindow, 0, 0, PM_NOREMOVE ) == TRUE )
        {	
			BOOL Result = GetMessage( &msg, OpenGLWindow, 0, 0);
            if( Result == 0 ) 
				return;
			else if( Result == -1 )
			{
				DWORD Error = GetLastError();
				LPVOID lpMsgBuf;
				FormatMessage( 
					FORMAT_MESSAGE_ALLOCATE_BUFFER | 
					FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS,
					NULL,
					Error,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL 
				);
				// Process any inserts in lpMsgBuf.
				// ...
				// Display the string.
				int Choice = MessageBox( NULL, (LPCTSTR)lpMsgBuf, "An Error", MB_ABORTRETRYIGNORE | MB_ICONINFORMATION );
				// Free the buffer.
				LocalFree( lpMsgBuf );
				if( Choice == IDABORT ) return;
			}
			else
            { 
                TranslateMessage(&msg); 
                DispatchMessage(&msg); 
            }
		}
		this->Idle();

    } 

}



void OR_InputOutput_Win32::Initialisation(int *argc, char **argv, char* name,OR_I32 largeur, OR_I32 hteur,
																		OR_I32 posx, OR_I32 posy ) 
{
}

//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Win32::Initialisation_Win32
//
/// \author Backchiche
//-----------------------------------------------------------------------------

HWND OR_InputOutput_Win32::Initialisation_Win32(HINSTANCE HInstance, HWND hParent,DWORD dUserStyle, char* name,
								OR_I32 largeur, OR_I32 hauteur,
								OR_I32 posx, OR_I32 posy,
								HICON WindowIcon, char* MenuName )
{
	HInst=HInstance;
	DWORD dStyle;

	if(!dUserStyle)
		dStyle = WS_VISIBLE  | WS_OVERLAPPEDWINDOW;
	else
		dStyle = dUserStyle;

	if(hParent)
		dStyle |= WS_CHILD;

	if( !bRegistered )
	{
		HCURSOR WindowCursor = LoadCursor( NULL, IDC_ARROW );

		WNDCLASSEX WindowClass = { 
			sizeof( WNDCLASSEX ),
			0,
			Default_WinProc,
			0,
			0,
			HInst,
			WindowIcon,
			WindowCursor,
			0,
			MenuName,
			"Orion3D window",
			WindowIcon
		};

		if( !RegisterClassEx( &WindowClass ) ) 
		{
			MessageBox(WindowFromDC(DC), 
					   "Unable to register window.", 
					   "Problem",
						MB_ICONERROR | MB_OK);
			return NULL;
			
		}
		bRegistered = true;
	}
	
	OpenGLWindow = CreateWindow
	( 
		"Orion3D window",			//Classe de la fenÍtre
		name,						//Nom de la fenÍtre
		dStyle,	//CaractÈristiques
		posx, posy,
		largeur,hauteur,
		hParent,						//Handle de la fenÍtre mËre
		0,						//Identifiant de la fenÍtre fille
		HInst,					//HINSTANCE du programme
		this
	);

	if (!OpenGLWindow) 
	{
		MessageBox(WindowFromDC(DC), 
				   "Unable to create window.", 
				   "Problem",
					MB_ICONERROR | MB_OK);
		return NULL;
	}

	
	/* show the window */
	ShowWindow(OpenGLWindow, SW_SHOWNORMAL);

	/* initialize opengl and openil */
	pRenderer_->InitGraphics();

	return OpenGLWindow;
}


void OR_InputOutput_Win32::SetupPixelFormat(int *argc, char **argv)
{
	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),	//taille du descripteur de format
		1,								//version
        PFD_SUPPORT_OPENGL 
		| PFD_DRAW_TO_WINDOW 
		| PFD_DOUBLEBUFFER,				//PropriÈtÈs
        PFD_TYPE_RGBA,					//Mode de couleurs
        24,								//Bits de couleur
        0, 0, 0, 0, 0, 0,				//ParamËtres des couleurs
        0, 0,							//ParamËtres alpha
        0, 0, 0, 0, 0,					//ParamËtres du buffer d'accumulation
        32,								//Bits de profondeur
        0,								//Bits du buffer stencil 
        0,								//Nombre de buffers auxiliaires
        0,								//ignorÈ (obsolËte)
        0,								//rÈservÈ
        0,								//ignorÈ (obsolËte)
        0,								//Couleur de transparence
        0								//IgnorÈ (obsolËte)
	};

    OR_I32 pixelFormat=ChoosePixelFormat( DC, &pfd );

    if( pixelFormat == 0 ) 
	{
		MessageBox( WindowFromDC( DC ), 
				   "Graphic mode not supported.", 
				   "Problem",
					MB_ICONERROR | MB_OK );
        exit(1);
    }

    if( SetPixelFormat( DC, pixelFormat, &pfd ) != TRUE ) 
	{
		MessageBox( WindowFromDC( DC ), 
				   "Graphic mode not supported.", 
				   "Problem",
					MB_ICONERROR | MB_OK );
		exit(1);
	}

}

void OR_InputOutput_Win32::Reshape_Win32( OR_I32 width, OR_I32 height )
{
	pRenderer_->Reshape(width,height);

	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

}

OR_I32 OR_InputOutput_Win32::GetMousePosX()
{
	return m_MouseX;
}

OR_I32 OR_InputOutput_Win32::GetMousePosY()
{
	return m_MouseY;
}

void OR_InputOutput_Win32::SetMousePosX(OR_I32 pos)
{
	RECT WindowRect;
	GetWindowRect( OpenGLWindow, &WindowRect );
	SetCursorPos( WindowRect.left+pos, WindowRect.top+m_MouseY );
	m_MouseX = pos - WindowRect.left;
}

void OR_InputOutput_Win32::SetMousePosY(OR_I32 pos)
{
	RECT WindowRect;
	GetWindowRect( OpenGLWindow, &WindowRect );
	SetCursorPos( WindowRect.left+m_MouseX, WindowRect.top+pos );
	m_MouseY = pos - WindowRect.top;
}

/** get the state of the left mouse button */
OR_Bool OR_InputOutput_Win32::GetLeftButtonState()
{
	return bLeft;
}

/** get the state of the right mouse button */
OR_Bool OR_InputOutput_Win32::GetRightButtonState()
{
	return bRight;
}

/** get the state of the middle mouse button */
OR_Bool OR_InputOutput_Win32::GetMiddleButtonState()
{
	return bMiddle;
}

//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Win32::Default_Destroy
/**
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_InputOutput_Win32::Default_Destroy()
{

}

//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Win32::Default_KeyPressed
/**
*   @param  button button that has been pressed.
*   @param  x x position the mouse
*   @param  y y position the mouse
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_InputOutput_Win32::Default_KeyPressed(OR_U32 button, OR_I32 x, OR_I32 y)
{
}


/*------------------------------------------------------------------------------ 
* Name : OR_InputOutput_Win32::Default_WindowsMenu 
* 
*  \param   EXPLANATION 
*  \param  flags EXPLANATION 
*  \param  hmenu EXPLANATION 
*  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION 
*  \author Antoine Bouthors 2002-01-03 
* 
* PUT YOUR COMMENTS HERE 
*------------------------------------------------------------------------------*/ 
void OR_InputOutput_Win32::Default_WindowsMenu(UINT item , UINT flags, HMENU hmenu) 
{  
}  

//-----------------------------------------------------------------------------
// Name: OR_InputOutput_Win32::Default_Mouseclic
/**
*   @param  button button that has been pressed.
*   @param  state state of the button.
*   @param  x x position of the mouse
*   @param  y y position of the mouse.
*/
/// \author Gabriel Peyré
//-----------------------------------------------------------------------------
void OR_InputOutput_Win32::Default_Mouseclic(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y)
{
}

// MessageName: this function returns the text name of the message.
char* MessageName(UINT msg)
{
	switch (msg)
	{
	case WM_NULL: return "WM_NULL";
    case WM_CREATE: return "WM_CREATE";
    case WM_DESTROY: return "WM_DESTROY";
    case WM_MOVE: return "WM_MOVE";
    case WM_SIZE: return "WM_SIZE";
    case WM_ACTIVATE: return "WM_ACTIVATE";
    case WM_SETFOCUS: return "WM_SETFOCUS";
    case WM_KILLFOCUS: return "WM_KILLFOCUS";
    case WM_ENABLE: return "WM_ENABLE";
    case WM_SETREDRAW: return "WM_SETREDRAW";
    case WM_SETTEXT: return "WM_SETTEXT";
    case WM_GETTEXT: return "WM_GETTEXT";
    case WM_GETTEXTLENGTH: return "WM_GETTEXTLENGTH";
    case WM_PAINT: return "WM_PAINT";
    case WM_CLOSE: return "WM_CLOSE";
    case WM_QUERYENDSESSION: return "WM_QUERYENDSESSION";
    case WM_QUIT: return "WM_QUIT";
    case WM_QUERYOPEN: return "WM_QUERYOPEN";
    case WM_ERASEBKGND: return "WM_ERASEBKGND";
    case WM_SYSCOLORCHANGE: return "WM_SYSCOLORCHANGE";
    case WM_ENDSESSION: return "WM_ENDSESSION";
    case WM_SHOWWINDOW: return "WM_SHOWWINDOW";
    case WM_SETTINGCHANGE: return "WM_SETTINGCHANGE";
    case WM_DEVMODECHANGE: return "WM_DEVMODECHANGE";
    case WM_ACTIVATEAPP: return "WM_ACTIVATEAPP";
    case WM_FONTCHANGE: return "WM_FONTCHANGE";
    case WM_TIMECHANGE: return "WM_TIMECHANGE";
    case WM_CANCELMODE: return "WM_CANCELMODE";
    case WM_SETCURSOR: return "WM_SETCURSOR";
    case WM_MOUSEACTIVATE: return "WM_MOUSEACTIVATE";
    case WM_CHILDACTIVATE: return "WM_CHILDACTIVATE";
    case WM_QUEUESYNC: return "WM_QUEUESYNC";
    case WM_GETMINMAXINFO: return "WM_GETMINMAXINFO";
    case WM_PAINTICON: return "WM_PAINTICON";
    case WM_ICONERASEBKGND: return "WM_ICONERASEBKGND";
    case WM_NEXTDLGCTL: return "WM_NEXTDLGCTL";
    case WM_SPOOLERSTATUS: return "WM_SPOOLERSTATUS";
    case WM_DRAWITEM: return "WM_DRAWITEM";
    case WM_MEASUREITEM: return "WM_MEASUREITEM";
    case WM_DELETEITEM: return "WM_DELETEITEM";
    case WM_VKEYTOITEM: return "WM_VKEYTOITEM";
    case WM_CHARTOITEM: return "WM_CHARTOITEM";
    case WM_SETFONT: return "WM_SETFONT";
    case WM_GETFONT: return "WM_GETFONT";
    case WM_SETHOTKEY: return "WM_SETHOTKEY";
    case WM_GETHOTKEY: return "WM_GETHOTKEY";
    case WM_QUERYDRAGICON: return "WM_QUERYDRAGICON";
    case WM_COMPAREITEM: return "WM_COMPAREITEM";
    case WM_COMPACTING: return "WM_COMPACTING";
    case WM_COMMNOTIFY: return "WM_COMMNOTIFY";
    case WM_WINDOWPOSCHANGING: return "WM_WINDOWPOSCHANGING";
    case WM_WINDOWPOSCHANGED: return "WM_WINDOWPOSCHANGED";
    case WM_POWER: return "WM_POWER";
    case WM_COPYDATA: return "WM_COPYDATA";
    case WM_CANCELJOURNAL: return "WM_CANCELJOURNAL";
    case WM_NOTIFY: return "WM_NOTIFY";
    case WM_INPUTLANGCHANGEREQUEST: return "WM_INPUTLANGCHANGEREQUEST";
    case WM_INPUTLANGCHANGE: return "WM_INPUTLANGCHANGE";
    case WM_TCARD: return "WM_TCARD";
    case WM_HELP: return "WM_HELP";
    case WM_USERCHANGED: return "WM_USERCHANGED";
    case WM_NOTIFYFORMAT: return "WM_NOTIFYFORMAT";
    case WM_CONTEXTMENU: return "WM_CONTEXTMENU";
    case WM_STYLECHANGING: return "WM_STYLECHANGING";
    case WM_STYLECHANGED: return "WM_STYLECHANGED";
    case WM_DISPLAYCHANGE: return "WM_DISPLAYCHANGE";
    case WM_GETICON: return "WM_GETICON";
    case WM_SETICON: return "WM_SETICON";
    case WM_NCCREATE: return "WM_NCCREATE";
    case WM_NCDESTROY: return "WM_NCDESTROY";
    case WM_NCCALCSIZE: return "WM_NCCALCSIZE";
    case WM_NCHITTEST: return "WM_NCHITTEST";
    case WM_NCPAINT: return "WM_NCPAINT";
    case WM_NCACTIVATE: return "WM_NCACTIVATE";
    case WM_GETDLGCODE: return "WM_GETDLGCODE";
    case WM_NCMOUSEMOVE: return "WM_NCMOUSEMOVE";
    case WM_NCLBUTTONDOWN: return "WM_NCLBUTTONDOWN";
    case WM_NCLBUTTONUP: return "WM_NCLBUTTONUP";
    case WM_NCLBUTTONDBLCLK: return "WM_NCLBUTTONDBLCLK";
    case WM_NCRBUTTONDOWN: return "WM_NCRBUTTONDOWN";
    case WM_NCRBUTTONUP: return "WM_NCRBUTTONUP";
    case WM_NCRBUTTONDBLCLK: return "WM_NCRBUTTONDBLCLK";
    case WM_NCMBUTTONDOWN: return "WM_NCMBUTTONDOWN";
    case WM_NCMBUTTONUP: return "WM_NCMBUTTONUP";
    case WM_NCMBUTTONDBLCLK: return "WM_NCMBUTTONDBLCLK";
    case WM_KEYDOWN: return "WM_KEYDOWN";
    case WM_KEYUP: return "WM_KEYUP";
    case WM_CHAR: return "WM_CHAR";
    case WM_DEADCHAR: return "WM_DEADCHAR";
    case WM_SYSKEYDOWN: return "WM_SYSKEYDOWN";
    case WM_SYSKEYUP: return "WM_SYSKEYUP";
    case WM_SYSCHAR: return "WM_SYSCHAR";
    case WM_SYSDEADCHAR: return "WM_SYSDEADCHAR";
    case WM_IME_STARTCOMPOSITION: return "WM_IME_STARTCOMPOSITION";
    case WM_IME_ENDCOMPOSITION: return "WM_IME_ENDCOMPOSITION";
    case WM_IME_COMPOSITION: return "WM_IME_COMPOSITION";
    case WM_INITDIALOG: return "WM_INITDIALOG";
    case WM_COMMAND: return "WM_COMMAND";
    case WM_SYSCOMMAND: return "WM_SYSCOMMAND";
    case WM_TIMER: return "WM_TIMER";
    case WM_HSCROLL: return "WM_HSCROLL";
    case WM_VSCROLL: return "WM_VSCROLL";
    case WM_INITMENU: return "WM_INITMENU";
    case WM_INITMENUPOPUP: return "WM_INITMENUPOPUP";
    case WM_MENUSELECT: return "WM_MENUSELECT";
    case WM_MENUCHAR: return "WM_MENUCHAR";
    case WM_ENTERIDLE: return "WM_ENTERIDLE";
    case WM_CTLCOLORMSGBOX: return "WM_CTLCOLORMSGBOX";
    case WM_CTLCOLOREDIT: return "WM_CTLCOLOREDIT";
    case WM_CTLCOLORLISTBOX: return "WM_CTLCOLORLISTBOX";
    case WM_CTLCOLORBTN: return "WM_CTLCOLORBTN";
    case WM_CTLCOLORDLG: return "WM_CTLCOLORDLG";
    case WM_CTLCOLORSCROLLBAR: return "WM_CTLCOLORSCROLLBAR";
    case WM_CTLCOLORSTATIC: return "WM_CTLCOLORSTATIC";
    case WM_MOUSEMOVE: return "WM_MOUSEMOVE";
    case WM_LBUTTONDOWN: return "WM_LBUTTONDOWN";
    case WM_LBUTTONUP: return "WM_LBUTTONUP";
    case WM_LBUTTONDBLCLK: return "WM_LBUTTONDBLCLK";
    case WM_RBUTTONDOWN: return "WM_RBUTTONDOWN";
    case WM_RBUTTONUP: return "WM_RBUTTONUP";
    case WM_RBUTTONDBLCLK: return "WM_RBUTTONDBLCLK";
    case WM_MBUTTONDOWN: return "WM_MBUTTONDOWN";
    case WM_MBUTTONUP: return "WM_MBUTTONUP";
    case WM_MBUTTONDBLCLK: return "WM_MBUTTONDBLCLK";
		//case WM_MOUSEWHEEL: return "WM_MOUSEWHEEL";
    case WM_PARENTNOTIFY: return "WM_PARENTNOTIFY";
    case WM_ENTERMENULOOP: return "WM_ENTERMENULOOP";
    case WM_EXITMENULOOP: return "WM_EXITMENULOOP";
    case WM_NEXTMENU: return "WM_NEXTMENU";
    case WM_SIZING: return "WM_SIZING";
    case WM_CAPTURECHANGED: return "WM_CAPTURECHANGED";
    case WM_MOVING: return "WM_MOVING";
    case WM_POWERBROADCAST: return "WM_POWERBROADCAST";
    case WM_DEVICECHANGE: return "WM_DEVICECHANGE";
    case WM_IME_SETCONTEXT: return "WM_IME_SETCONTEXT";
    case WM_IME_NOTIFY: return "WM_IME_NOTIFY";
    case WM_IME_CONTROL: return "WM_IME_CONTROL";
    case WM_IME_COMPOSITIONFULL: return "WM_IME_COMPOSITIONFULL";
    case WM_IME_SELECT: return "WM_IME_SELECT";
    case WM_IME_CHAR: return "WM_IME_CHAR";
    case WM_IME_KEYDOWN: return "WM_IME_KEYDOWN";
    case WM_IME_KEYUP: return "WM_IME_KEYUP";
    case WM_MDICREATE: return "WM_MDICREATE";
    case WM_MDIDESTROY: return "WM_MDIDESTROY";
    case WM_MDIACTIVATE: return "WM_MDIACTIVATE";
    case WM_MDIRESTORE: return "WM_MDIRESTORE";
    case WM_MDINEXT: return "WM_MDINEXT";
    case WM_MDIMAXIMIZE: return "WM_MDIMAXIMIZE";
    case WM_MDITILE: return "WM_MDITILE";
    case WM_MDICASCADE: return "WM_MDICASCADE";
    case WM_MDIICONARRANGE: return "WM_MDIICONARRANGE";
    case WM_MDIGETACTIVE: return "WM_MDIGETACTIVE";
    case WM_MDISETMENU: return "WM_MDISETMENU";
    case WM_ENTERSIZEMOVE: return "WM_ENTERSIZEMOVE";
    case WM_EXITSIZEMOVE: return "WM_EXITSIZEMOVE";
    case WM_DROPFILES: return "WM_DROPFILES";
    case WM_MDIREFRESHMENU: return "WM_MDIREFRESHMENU";
		//case WM_MOUSEHOVER: return "WM_MOUSEHOVER";
		//case WM_MOUSELEAVE: return "WM_MOUSELEAVE";
    case WM_CUT: return "WM_CUT";
    case WM_COPY: return "WM_COPY";
    case WM_PASTE: return "WM_PASTE";
    case WM_CLEAR: return "WM_CLEAR";
    case WM_UNDO: return "WM_UNDO";
    case WM_RENDERFORMAT: return "WM_RENDERFORMAT";
    case WM_RENDERALLFORMATS: return "WM_RENDERALLFORMATS";
    case WM_DESTROYCLIPBOARD: return "WM_DESTROYCLIPBOARD";
    case WM_DRAWCLIPBOARD: return "WM_DRAWCLIPBOARD";
    case WM_PAINTCLIPBOARD: return "WM_PAINTCLIPBOARD";
    case WM_VSCROLLCLIPBOARD: return "WM_VSCROLLCLIPBOARD";
    case WM_SIZECLIPBOARD: return "WM_SIZECLIPBOARD";
    case WM_ASKCBFORMATNAME: return "WM_ASKCBFORMATNAME";
    case WM_CHANGECBCHAIN: return "WM_CHANGECBCHAIN";
    case WM_HSCROLLCLIPBOARD: return "WM_HSCROLLCLIPBOARD";
    case WM_QUERYNEWPALETTE: return "WM_QUERYNEWPALETTE";
    case WM_PALETTEISCHANGING: return "WM_PALETTEISCHANGING";
    case WM_PALETTECHANGED: return "WM_PALETTECHANGED";
    case WM_HOTKEY: return "WM_HOTKEY";
    case WM_PRINT: return "WM_PRINT";
    case WM_PRINTCLIENT: return "WM_PRINTCLIENT";
    case WM_HANDHELDFIRST: return "WM_HANDHELDFIRST";
    case WM_HANDHELDLAST: return "WM_HANDHELDLAST";
    case WM_AFXFIRST: return "WM_AFXFIRST";
    case WM_AFXLAST: return "WM_AFXLAST";
    case WM_PENWINFIRST: return "WM_PENWINFIRST";
    case WM_PENWINLAST: return "WM_PENWINLAST";
#ifdef __VCL
    case CM_ACTIVATE: return "CM_ACTIVATE";
    case CM_DEACTIVATE: return "CM_DEACTIVATE";
    case CM_GOTFOCUS: return "CM_GOTFOCUS";
    case CM_LOSTFOCUS: return "CM_LOSTFOCUS";
    case CM_CANCELMODE: return "CM_CANCELMODE";
    case CM_DIALOGKEY: return "CM_DIALOGKEY";
    case CM_DIALOGCHAR: return "CM_DIALOGCHAR";
    case CM_FOCUSCHANGED: return "CM_FOCUSCHANGED";
    case CM_PARENTFONTCHANGED: return "CM_PARENTFONTCHANGED";
    case CM_PARENTCOLORCHANGED: return "CM_PARENTCOLORCHANGED";
    case CM_HITTEST: return "CM_HITTEST";
    case CM_VISIBLECHANGED: return "CM_VISIBLECHANGED";
    case CM_ENABLEDCHANGED: return "CM_ENABLEDCHANGED";
    case CM_COLORCHANGED: return "CM_COLORCHANGED";
    case CM_FONTCHANGED: return "CM_FONTCHANGED";
    case CM_CURSORCHANGED: return "CM_CURSORCHANGED";
    case CM_CTL3DCHANGED: return "CM_CTL3DCHANGED";
    case CM_PARENTCTL3DCHANGED: return "CM_PARENTCTL3DCHANGED";
    case CM_TEXTCHANGED: return "CM_TEXTCHANGED";
    case CM_MOUSEENTER: return "CM_MOUSEENTER";
    case CM_MOUSELEAVE: return "CM_MOUSELEAVE";
    case CM_MENUCHANGED: return "CM_MENUCHANGED";
    case CM_APPKEYDOWN: return "CM_APPKEYDOWN";
    case CM_APPSYSCOMMAND: return "CM_APPSYSCOMMAND";
    case CM_BUTTONPRESSED: return "CM_BUTTONPRESSED";
    case CM_SHOWINGCHANGED: return "CM_SHOWINGCHANGED";
    case CM_ENTER: return "CM_ENTER";
    case CM_EXIT: return "CM_EXIT";
    case CM_DESIGNHITTEST: return "CM_DESIGNHITTEST";
    case CM_ICONCHANGED: return "CM_ICONCHANGED";
    case CM_WANTSPECIALKEY: return "CM_WANTSPECIALKEY";
    case CM_INVOKEHELP: return "CM_INVOKEHELP";
    case CM_WINDOWHOOK: return "CM_WINDOWHOOK";
    case CM_RELEASE: return "CM_RELEASE";
    case CM_SHOWHINTCHANGED: return "CM_SHOWHINTCHANGED";
    case CM_PARENTSHOWHINTCHANGED: return "CM_PARENTSHOWHINTCHANGED";
    case CM_SYSCOLORCHANGE: return "CM_SYSCOLORCHANGE";
    case CM_WININICHANGE: return "CM_WININICHANGE";
    case CM_FONTCHANGE: return "CM_FONTCHANGE";
    case CM_TIMECHANGE: return "CM_TIMECHANGE";
    case CM_TABSTOPCHANGED: return "CM_TABSTOPCHANGED";
    case CM_UIACTIVATE: return "CM_UIACTIVATE";
    case CM_UIDEACTIVATE: return "CM_UIDEACTIVATE";
    case CM_DOCWINDOWACTIVATE: return "CM_DOCWINDOWACTIVATE";
    case CM_CONTROLLISTCHANGE: return "CM_CONTROLLISTCHANGE";
    case CM_GETDATALINK: return "CM_GETDATALINK";
    case CM_CHILDKEY: return "CM_CHILDKEY";
    case CM_DRAG: return "CM_DRAG";
    case CM_HINTSHOW: return "CM_HINTSHOW";
    case CM_DIALOGHANDLE: return "CM_DIALOGHANDLE";
    case CM_ISTOOLCONTROL: return "CM_ISTOOLCONTROL";
    case CM_RECREATEWND: return "CM_RECREATEWND";
    case CM_INVALIDATE: return "CM_INVALIDATE";
    case CM_SYSFONTCHANGED: return "CM_SYSFONTCHANGED";
    case CM_CONTROLCHANGE: return "CM_CONTROLCHANGE";
    case CM_CHANGED: return "CM_CHANGED";
    case CN_CHARTOITEM: return "CN_CHARTOITEM";
    case CN_COMMAND: return "CN_COMMAND";
    case CN_COMPAREITEM: return "CN_COMPAREITEM";
    case CN_CTLCOLORBTN: return "CN_CTLCOLORBTN";
    case CN_CTLCOLORDLG: return "CN_CTLCOLORDLG";
    case CN_CTLCOLOREDIT: return "CN_CTLCOLOREDIT";
    case CN_CTLCOLORLISTBOX: return "CN_CTLCOLORLISTBOX";
    case CN_CTLCOLORMSGBOX: return "CN_CTLCOLORMSGBOX";
    case CN_CTLCOLORSCROLLBAR: return "CN_CTLCOLORSCROLLBAR";
    case CN_CTLCOLORSTATIC: return "CN_CTLCOLORSTATIC";
    case CN_DELETEITEM: return "CN_DELETEITEM";
    case CN_DRAWITEM: return "CN_DRAWITEM";
    case CN_HSCROLL: return "CN_HSCROLL";
    case CN_MEASUREITEM: return "CN_MEASUREITEM";
    case CN_PARENTNOTIFY: return "CN_PARENTNOTIFY";
    case CN_VKEYTOITEM: return "CN_VKEYTOITEM";
    case CN_VSCROLL: return "CN_VSCROLL";
    case CN_KEYDOWN: return "CN_KEYDOWN";
    case CN_KEYUP: return "CN_KEYUP";
    case CN_CHAR: return "CN_CHAR";
    case CN_SYSKEYDOWN: return "CN_SYSKEYDOWN";
    case CN_SYSCHAR: return "CN_SYSCHAR";
    case CN_NOTIFY: return "CN_NOTIFY";
#endif
    default: return "WM_????";
  }
}


} // namespace OR



///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////