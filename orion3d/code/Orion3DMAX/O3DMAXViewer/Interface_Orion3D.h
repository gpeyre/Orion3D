#ifndef _INTERFACE_ORION3D_H_
#define _INTERFACE_ORION3D_H_

#include "stdafx.h"
#include "../OR_3DS_Wrapper.h"
#include "./Globals.h"

///Initialise orion3d
int			InitEngine(Interface* MaxRootNode);
///Update everything, check for Update or Quit events
void		Idlefunc();
///Draw everything
static void	Drawfunc();
///Mouse callback func
void		Mousefunc(OR_I32 x, OR_I32 y);
///Mouse click callback func
void		Mouseclick(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y);
///keyboard calback func
void		Keyboard(OR_U32, OR_I32 ,OR_I32);
///keyboard up calback func
void		Keyboardreleased(OR_U32, OR_I32 ,OR_I32);
///Main loop of orion3d
DWORD		Go(void * MaxRootNode);
///Function called when the user types 'quit' in the console
OR_U32		Orion3D_quit();	

#endif //_INTERFACE_ORION3D_H_