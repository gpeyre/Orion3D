/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief Main file for particles test program.
 *  \author Antoine Bouthors 2001-12-22
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) main.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID



/* first thing to do : tell to Orion3D we are using the Win32 wrapper */
#define _USE_WIN32_
/* tell that we are using the Orion3D dll */
#define ORION3D_IMPORTS
#define MODEL_BASE_ID 1000

#include <windows.h>

//-------------------------------------------------------------------------
/** \name orion3d file inclusion */
//-------------------------------------------------------------------------
//@{
/* this will check wich library we will need to use */
#include "../../orion3d/configuration/OR_Config.h"
#include "../../orion3d/toolkit/OR_Toolkit.h"
#include "../../orion3d/wrapper_win32/OR_InputOutput_win32.h"
#include "../../orion3d/animation/or_animation.h"
#include "../../orion3d/animation/or_animationplayer.h"
/* we want to avoid putting OR:: before each Orion3D beautifull class names */
using namespace OR;
//@}

#include "resource.h"

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef OR_DEBUG
	#pragma comment(lib, "orion3d_wrapper_win32_dbg.lib")
	#pragma comment(lib, "orion3d_toolkit_dbg.lib")
#else
	#pragma comment(lib, "orion3d_wrapper_win32.lib")
	#pragma comment(lib, "orion3d_toolkit.lib")
#endif // OR_DEBUG
//@}

//-------------------------------------------------------------------------
/** @name 3D engine */
//-------------------------------------------------------------------------
//@{
/** the main helper, create all Orion3D stuff */
OR_Toolkit *pToolkit = new OR_Toolkit;
/** the wrapper used for input/output */
OR_InputOutput_Win32* pInputOutput = new OR_InputOutput_Win32(*pToolkit);
//@}

const string BaseDirKRD( "..\\krd\\" );
const string BaseDirACT( "..\\act\\" );
OR_AnimationPlayer* pAnimationPlayer = NULL;
OR_Skin* Skin=NULL;
OR_Bool ShowSkeletton = false;
OR_Bool ShowSkin = true;
OR_U32 WireFrame = GL_FILL;
vector<OR_String> Models;
vector<OR_String> Animations;

//Handle the OpenGl win
HWND GlWin;

/** to handle the mouse movements */
OR_I32 xmouse,ymouse;


void ToggleDisplaySkin()
{
	if( Skin )
	{
		ShowSkin = !ShowSkin;
		Skin->SetVisible( ShowSkin );
		HMENU ModelsMenu = GetSubMenu( GetMenu( GlWin ), 1 );
		CheckMenuItem( ModelsMenu, ID_MODEL_DISPLAYSKIN, ShowSkin?MF_CHECKED:MF_UNCHECKED );
	}	
}

void ToggleDisplaySkeletton()
{
	if( Skin ) 
	{
		ShowSkeletton = !ShowSkeletton;
		for( OR_U32 i=0 ; i<Skin->GetNbrBones() ; ++i )
		{
			Skin->GetBone( i )->SetVisible( ShowSkeletton );
		}
		HMENU ModelsMenu = GetSubMenu( GetMenu( GlWin ), 1 );
		CheckMenuItem( ModelsMenu, ID_MODEL_DISPLAYSKELETTON, ShowSkeletton?MF_CHECKED:MF_UNCHECKED );
	}
}


/** set wireframe mode on/off */
void WireOnOff()
{
	switch (WireFrame)
	{
	case GL_POINT:		WireFrame=GL_FILL;		break;
	case GL_FILL:       WireFrame=GL_LINE;	    break;
	case GL_LINE :		WireFrame=GL_POINT;	    break;
	}
	glPolygonMode(GL_FRONT_AND_BACK, WireFrame);
}

void LoadFiles()
{
	HMENU ModelsMenu = GetSubMenu( GetMenu( GlWin ), 1 );
	OR_U32 i=0;
	OR_File ListFile( "files.txt", "r" );
	if( ListFile.IsOpen() )
	{
		while( ListFile.IsOpen() && !ListFile.Eof() )
		{
			OR_I32 NbFiles;
			OR_String File = ListFile.GetLine();
			OR_String* Files = 	File.explode( NbFiles, '|' );
			if( NbFiles == 1 )
			{
				AppendMenu( ModelsMenu, 0, MODEL_BASE_ID+i, Files[0].getBytes() );
				Models.push_back( Files[0] );
				Animations.push_back( Files[1] );
				i++;
			}
			delete[] Files;
		}
		ListFile.Close();
	}

}

void LoadAnim( OR_U32 nFile )
{
	OR_String File = Animations[ nFile ];
	if( pToolkit->LoadFile( File.const_val() ) != OR_OK ) return;

	OR_Animation* pAnimation = pToolkit->GetAnimationManager().GetElementSelected();
	if( pAnimation==NULL )
	{	
		printf("ACT loading failed.\n");
		pToolkit->Warning("LoadAnimation", "ACT loading failed.");
		return;
	}

	pAnimationPlayer = new OR_AnimationPlayer(pAnimation, -1);
	OR_Node* pNode = pToolkit->GetNodeByName( pAnimation->GetName() );
	pAnimationPlayer->SetBehaviour(OR_ANIMATION_Player_Loop);
	
	if( pNode!=NULL ) 
	{
		pNode->AddPlayer(*pAnimationPlayer);
		printf("ACT loading succesful.\n");
	}
	else
	{
		printf("ACT loading failed : animation root not fond.\n");
		pToolkit->Warning("LoadAnimation", "ACT loading failed : animation root not fond.");
	}

}

void LoadSkin( OR_U32 nFile )
{
	OR_String File = Models[ nFile ];
	ShowSkin = 1;
	ShowSkeletton = 0;
	HMENU ModelsMenu = GetSubMenu( GetMenu( GlWin ), 1 );
	CheckMenuItem( ModelsMenu, ID_MODEL_DISPLAYSKIN, ShowSkin?MF_CHECKED:MF_UNCHECKED );
	CheckMenuItem( ModelsMenu, ID_MODEL_DISPLAYSKELETTON, ShowSkeletton?MF_CHECKED:MF_UNCHECKED );
	/* load the KRD file */
	pToolkit->LoadFile( File.const_val() );
	pToolkit->GetSkinManager().SelectFirstElement();
	Skin = pToolkit->GetSkinManager().GetElementSelected();
	/* load the ACT file */
	LoadAnim( nFile );

	OR_Camera* Cam = pToolkit->GetCameraManager().GetElement( "ViewCam" );
	if( !Cam )
	{
		pToolkit->AddFreeCamera();
		pToolkit->SetViewportCamera();
	}
	else
		pToolkit->GetViewportManager().GetElementSelected()->SetCamera( Cam );
}

/** load the cameras */
void Reset()
{
	pToolkit->GetHierarchyTree().DeleteSubTree( pToolkit->GetHierarchyTree().GetRootNode() );
	pToolkit->RemoveUnusedObjects();

	pToolkit->AddFreeCamera();
	pToolkit->SetViewportCamera();
}

/** to handle mouse movements */
void mouse(OR_I32 x, OR_I32 y)
{
	bool BoutG=pToolkit->GetLeftButtonState();
	bool BoutD=pToolkit->GetRightButtonState();

	if (BoutD && !BoutG)
	{
		pToolkit->RotateCamera(Y, (xmouse-x)*0.01);
		pToolkit->RotateCamera(X, (ymouse-y)*0.01);
	}
	else if (BoutG)
	{
		OR_Camera* Cam = pToolkit->GetCameraManager().GetElementSelected();
		if( Cam->GetType() == OR_CAMERA_Target )
			Cam->Translate( Z, (-ymouse+y)*0.002*~(Cam->GetTarget()->GetAbsolutePosition()-Cam->GetAbsolutePosition() ) );
		else
			pToolkit->TranslateCamera(Z, (-ymouse+y)*0.1);
	}
	
	xmouse=x;
	ymouse=y;

}

void mouse_click(OR_I32 button, OR_I32 state, OR_I32 x, OR_I32 y)
{
	if(button==OR_WHEEL)
	{
		pToolkit->TranslateCamera(Z, -state*0.005);
	}
}


/** to handle keyboard */
void keyboard(OR_U32 button, OR_I32 x, OR_I32 y)
{

	switch (button)
	{
	case VK_UP:
		pToolkit->TranslateCamera(Z, -2.5);
		break;
	case VK_DOWN:
		pToolkit->TranslateCamera(Z, 2.5);
		break;
	case VK_RIGHT:
		pToolkit->TranslateCamera(X, 2.2);
		break;
	case VK_LEFT:
		pToolkit->TranslateCamera(X, -2.2);
		break;
	case VK_ESCAPE:
		::exit(0);
		break;
	case VK_F1:
		if( pAnimationPlayer ) pAnimationPlayer->TogglePlayPause();
		break;
	case VK_F2:
		if( pAnimationPlayer ) pAnimationPlayer->Step(-0.01f);
		break;
	case VK_F3:
		if( pAnimationPlayer ) pAnimationPlayer->Step(0.01f);
		break;
	case VK_F4:
		if( pAnimationPlayer ) pAnimationPlayer->Restart();
		break;
	case VK_F5:
		WireOnOff();
		break;
	case VK_F6:
		((OR_ShellConsoleText&)pToolkit->GetShellConsole()).OpenConsole();
		break;
	case VK_F7:
		ToggleDisplaySkin();
		break;
	case VK_F8:
		ToggleDisplaySkeletton();
		break;
	}
}

void WindowsMenu(UINT item , UINT flags, HMENU hmenu)
{
	switch( item ) 
	{
	case IDM_QUIT:
		::exit(0);
		break;
	case ID_ANIMATION_CONTROL_PLAY:
		if( pAnimationPlayer ) pAnimationPlayer->TogglePlayPause();
		break;
	case ID_CONTROL_STEPBACKWARDS:
		if( pAnimationPlayer ) pAnimationPlayer->Step(-0.01f);
		break;
	case ID_CONTROL_STEPFORWARD:
		if( pAnimationPlayer ) pAnimationPlayer->Step(0.01f);
		break;
	case ID_ANIMATION_CONTROL_RESETF4:
		if( pAnimationPlayer ) pAnimationPlayer->Restart();
		break;
	case ID_MODEL_TOGGLEGOURAUD:
		WireOnOff();
		break;
	case ID_MODEL_DISPLAYSKIN:
		ToggleDisplaySkin();
		break;
	case ID_MODEL_DISPLAYSKELETTON:
		ToggleDisplaySkeletton();
		break;
	case ID_OPENCONSOLE:
		((OR_ShellConsoleText&)pToolkit->GetShellConsole()).OpenConsole();
		break;
	}
	if( item >= MODEL_BASE_ID && item < MODEL_BASE_ID + Models.size() )
	{
		Reset();
		LoadSkin( item-MODEL_BASE_ID );
	}

}

/** load the differents elements */
void init(void)
{
	pAnimationPlayer = NULL;
	pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);

	Reset();
	LoadFiles();
	/*if( Models.size() )
	{
		LoadSkin( Models[0] );
		if( pAnimationPlayer ) pAnimationPlayer->Play();
	}*/

	pToolkit->DisableDraw( OR_LIGHT );
	pToolkit->DisableDraw( OR_GIZMO );
	pToolkit->DisableDraw( OR_CAMERA );
	pToolkit->DisableDraw( OR_LOCAL_AXES );
	pToolkit->DisableDraw( OR_TRAJECTORIES );

	float Global_Ambient[4]={ 0,0,0,0.f };
	pToolkit->Setfv( OR_LIGHT_GlobalAmbient, Global_Ambient );
}

/** when nothing occurs */
void idle(void)
{
	pToolkit->Update();
	pToolkit->PostReDisplay();
 
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : main 
 *
 *  \param  argc ...
 *  \param  argv ..
 *  \author Gabriel Peyré 2001-10-17
 *
 *	entry point for the application
 */ 
/*------------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance,  
                       HINSTANCE hPrevInstance,   
                       LPSTR lpCmdLine,   
                       int nCmdShow)
{
	/* check if we use an up-to-date version of Orion3D */
	if( OR_Toolkit::GetVersion() < OR_ORION3D_Version )
		pToolkit->Warning("skin_test main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);

	
	GlWin=pInputOutput->Initialisation_Win32( hInstance, NULL, 0, "Skinning demo", 640, 480, 0, 0, LoadIcon( hInstance, MAKEINTRESOURCE( IDI_WINDOW_ICON ) ), MAKEINTRESOURCE( IDR_SKINMENU ));
	pInputOutput->SetWindowsMenuFunc( WindowsMenu );
	
	/* set up callback functions */
	pToolkit->SetMotionFunc(mouse);
	pToolkit->SetKeyPressedFunc(keyboard);
	pToolkit->SetMouseClicFunc(mouse_click);
	pToolkit->SetIdleFunc(idle);

	/* load all datas */
	init();

	/* run an infinite loop */
	pToolkit->MainLoop();

	return 0;
}



///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         //
//---------------------------------------------------------------------------//
//  This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                               END OF FILE                                 //
///////////////////////////////////////////////////////////////////////////////

