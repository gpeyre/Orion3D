#ifndef _OR_GLOBALS_H_
#define _OR_GLOBALS_H_

#include "stdafx.h"
#include "../OR_3DS_Wrapper.h"

/// Hinstance of the program
extern HINSTANCE hInstance;

extern OR_Bool volatile		Lock;
extern OR_InputOutput_Win32* pInputOutput;
extern OR_Toolkit* volatile	Engine;
extern OR_3DS_Node* volatile		RootNode;
extern CRITICAL_SECTION		Critic;
extern HWND					OrionHWND;

extern HANDLE				EngineThreadHandle;
extern DWORD				EngineThreadId;
extern OR_Animation*		SceneAnim;
extern MMRESULT volatile	TimeEvent;
extern OR_3DSWrapper		Wrapper;
extern DWORD				SelectedView;
extern OR_Camera*			SelectedCam;

extern IUtil*				IUtility;
extern Interface*			MAXInterface;
extern HWND	volatile		DlgHandle;
extern HWND	volatile		TreeViewHandle;

extern int					UpdateFlags;
extern OR_3DS_Node*			UpdateNode;

#endif //_OR_GLOBALS_H_