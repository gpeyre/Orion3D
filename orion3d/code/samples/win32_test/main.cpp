/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief main file for \b Win32 wrapper test.
 *  \author Backchiche 2001-10-17
 */ 
/*------------------------------------------------------------------------------*/


/* first thing to do : tell to Orion3D we are using the Win32 wrapper */
#define _USE_WIN32_
/* tell that we are using the Orion3D dll */
#define ORION3D_IMPORTS

//-------------------------------------------------------------------------
/** \name orion3d file inclusion */
//-------------------------------------------------------------------------
//@{
/* this will check wich library we will need to use */
#include "../../orion3d/configuration/OR_Config.h"
#include "../../orion3d/toolkit/OR_Toolkit.h"
#include "../../orion3d/wrapper_win32/OR_InputOutput_win32.h"
/* we want to avoid putting OR:: before each Orion3D beautifull class names */
using namespace OR;
//@}

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
OR_InputOutput_Win32 MyInputOutput(*pToolkit);
//@}
//Handle the OpenGl win
HWND GlWin;

int CamFree;

int MainViewport;

OR_U32 SpotLight;
float LightRot=0;

int xmouse,ymouse;


/** load the lights */
void LoadLights()
{

	GLfloat LightAmbient[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat LightDiffuse[]    = { 1.0f,1.0f,1.0f, 1.0f};
    GLfloat LightSpecular[]   = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightPosition[]   = {-8, 0, 8};
	GLfloat LightDirection[]  = {0, 0, -1};

	SpotLight=pToolkit->AddFreeSpotLight();
	pToolkit->Setfv(OR_LIGHT_Ambient,  LightAmbient);
	pToolkit->Setfv(OR_LIGHT_Diffuse,  LightDiffuse);
	pToolkit->Setfv(OR_LIGHT_Specular, LightSpecular);
	pToolkit->Setf(OR_LIGHT_Cutoff, 50);  
	pToolkit->Setf(OR_LIGHT_Exponent, 15);  
	pToolkit->Setfv(OR_LIGHT_Direction, LightDirection);
	pToolkit->Setfv(OR_LIGHT_Pos, LightPosition);
}

/** load the cameras */
void LoadCameras()
{

	/* create a free camera ***************************************/
	float CamFreePos[3] = {0,0,5};

	CamFree=pToolkit->AddFreeCamera();
	pToolkit->Setfv(OR_CAMERA_Pos, CamFreePos);

	MainViewport=pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);

}



/** to handle mouse movements */
void mouse(OR_I32 x, OR_I32 y)
{
	bool BoutG=pToolkit->GetLeftButtonState();
	bool BoutD=pToolkit->GetRightButtonState();

	/* on other, rotate upon pressing the right mouse button */
	if (BoutD && !BoutG)
	{
		pToolkit->RotateWorldCamera(Z, (xmouse-x)*0.01);
		pToolkit->RotateCamera(X, (ymouse-y)*0.01);
	}
	else if (BoutG)
	{
		pToolkit->TranslateCamera(Z, (-ymouse+y)*0.05);
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
		pToolkit->TranslateCamera(Z, -0.5);
		break;
	case VK_DOWN:
		pToolkit->TranslateCamera(Z, 0.5);
		break;
	case VK_RIGHT:
		pToolkit->TranslateCamera(X, 0.2);
		break;
	case VK_LEFT:
		pToolkit->TranslateCamera(X, -0.2);
		break;
	case VK_ESCAPE:
		::exit(0);
		break;
	}
}

/** load the differents elements */
void init(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);   // Pour l'antialiasing
	
	LoadLights();

	LoadCameras();

	pToolkit->LoadFile("../krd/animation.krd");
}

/** when nothing occurs */
void idle(void)
{
	pToolkit->Update();

	LightRot+=0.05;
	float pos[3];
	pos[X]=7*cos(LightRot*0.2f)*cos(LightRot);
	pos[Y]=7*cos(LightRot*0.2f)*sin(LightRot);
	pos[Z]=9;
	pToolkit->Select(OR_LIGHT, SpotLight);
	pToolkit->Posit(OR_LIGHT, pos);

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
		pToolkit->Warning("Orionviewer main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(MyInputOutput);

	GlWin=MyInputOutput.Initialisation_Win32(hInstance,NULL,0,"-==[ Test for Win32 wrapper ]==-",640,480,0,0);

	/* set up callback functions */
	pToolkit->SetMotionFunc(mouse);
	pToolkit->SetKeyPressedFunc(keyboard);

	pToolkit->SetMouseClicFunc(mouse_click);

	pToolkit->SetIdleFunc(idle);

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

