#include "../stdafx.h"
#include "Globals.h"

OR_Bool	volatile		Lock				= false;
HINSTANCE				hInstance			= NULL;
OR_InputOutput_Win32*	pInputOutput		= NULL;
OR_Toolkit* volatile	Engine				= NULL;
OR_3DS_Node* volatile	RootNode			= NULL;
CRITICAL_SECTION		Critic;
HWND					OrionHWND			= NULL;

HANDLE					EngineThreadHandle	= NULL;
DWORD					EngineThreadId		= 0;
OR_Animation*			SceneAnim			= NULL;
MMRESULT volatile		TimeEvent			= 0;
OR_3DSWrapper			Wrapper;
DWORD					SelectedView		= 0;
OR_Camera*				SelectedCam			= NULL;

IUtil*					IUtility			= NULL;
Interface*				MAXInterface		= NULL;
HWND	volatile		DlgHandle			= NULL;
HWND	volatile		TreeViewHandle		= NULL;

int						UpdateFlags			= 0;
OR_3DS_Node*			UpdateNode			= NULL;