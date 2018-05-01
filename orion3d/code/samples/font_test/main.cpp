/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief Main file for particles test program.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) main.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


/* first thing to do : tell to Orion3D we are using the Win32 wrapper */
#define _USE_WIN32_
/* tell that we are using the Orion3D dll */
#define ORION3D_IMPORTS

#define _USE_FTGL_

//-------------------------------------------------------------------------
/** \name orion3d file inclusion */
//-------------------------------------------------------------------------
//@{
/* this will check wich library we will need to use */
#include "../../orion3d/configuration/OR_Config.h"
#include "../../orion3d/toolkit/OR_Toolkit.h"
#include "../../orion3d/wrapper_win32/OR_InputOutput_win32.h"
#include "../../orion3d/physic/OR_GravityForce.h"
#include "../../orion3d/physic/OR_DampingForce.h"
#include "../../orion3d/physic/OR_MagneticForce.h"
#include "../../orion3d/physic/OR_SpringForce.h"
#include "../../orion3d/special_effects/OR_ParticuleSystem.h"
#include "../../orion3d/animation/OR_AnimationPlayer.h"
#include "../../orion3d/animation/OR_Animation.h"
#include "../../orion3d/hierarchy/OR_Node.h"

#include "../../orion3d/wrapper_font/OR_PixmapFont.h"
#include "../../orion3d/wrapper_font/OR_BitmapFont.h"
#include "../../orion3d/wrapper_font/OR_TextureFont.h"
#include "../../orion3d/wrapper_font/OR_OutlineFont.h"
#include "../../orion3d/wrapper_font/OR_PolygonFont.h"
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
OR_InputOutput_Win32* pInputOutput = new OR_InputOutput_Win32(*pToolkit);
//@}

//-------------------------------------------------------------------------
/** \name to handle the fonts */
//-------------------------------------------------------------------------
//@{
#define FONT_FILE "../resources/arial.ttf"
OR_Font_ABC* aFont[5];

char Text[200] = ":: Enter your text ::";
OR_I32 nCurPos = 21;
//@}



//Handle the OpenGl win
HWND GlWin;

/** to handle the mouse movements */
OR_I32 xmouse,ymouse;


/** load the lights */
void LoadLights()
{
	OR_Light_FreeSpot* pLight = new OR_Light_FreeSpot();

	pLight->SetAmbient ( OR_Vector4D(0.6f, 0.6f, 0.6f, 1.0f) );
	pLight->SetDiffuse ( OR_Vector4D(0.6f, 0.6f, 0.6f, 1.0f) );
	pLight->SetSpecular( OR_Vector4D(0.5f, 0.5f, 0.5f, 1.0f) );
	pLight->SetCutOff( 35 );
	pLight->SetDirection( OR_Vector3D( 0, 0, -1) );
	pLight->Posit( OR_Vector3D(0, 0, 6) );
	
	pToolkit->AddObject( pLight );

	float global_ambient[4]={1, 1, 1, 1};
	pToolkit->Setfv(OR_LIGHT_GlobalAmbient, global_ambient);
}

/** load the cameras */
void LoadCameras()
{
	/* create and add a sphere **********************************/
	OR_SphereGizmo* pSphere = new OR_SphereGizmo();
	pSphere->SetDim( OR_Vector3D(0.1f, 0.1f, 0.1f) );
	pToolkit->AddObject(pSphere);
	
	/* create a target camera ***********************************/
	pToolkit->AddTargetCamera();
	OR_Camera_Target* pCamera = (OR_Camera_Target*) pToolkit->GetCameraManager().GetElementSelected();
	pCamera->SetTarget( pSphere );
	pCamera->Posit(OR_Vector3D(2,0,0));
	
	/* create a viewport for this camera ************************/
	pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);
}


void LoadFont(OR_U32 i)
{
	aFont[i]->SetText( (char*) &Text );
	aFont[i]->SetPosition(0,i*0.15);
	
	if( !aFont[i]->LoadFont(FONT_FILE) )
	{
		pToolkit->Warning("LoadFont", "Can't load font file.");
		::exit(1);
	}
	if( !aFont[i]->SetFaceSize(54))
	{
		pToolkit->Warning("LoadFont", "Can't set font size.");
		::exit(1);
	}
}

void LoadFont()
{
	aFont[0] = new OR_PolygonFont;
	aFont[1] = new OR_OutlineFont;
	aFont[2] = new OR_TextureFont;
	aFont[3] = new OR_BitmapFont;
	aFont[4] = new OR_PixmapFont;
	
	pToolkit->GetFontManager().AddElement( aFont[0] );
	pToolkit->GetFontManager().AddElement( aFont[1] );
	pToolkit->GetFontManager().AddElement( aFont[2] );
	pToolkit->GetFontManager().AddElement( aFont[3] );
	pToolkit->GetFontManager().AddElement( aFont[4] );

	LoadFont(0);
	LoadFont(1);
	LoadFont(2);
	LoadFont(3);
	LoadFont(4);
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
	if( button>8 && button<256 )
	{
		Text[nCurPos] = button;;
		nCurPos ++;
	}

	switch (button)
	{
	case VK_BACK:
		nCurPos--;
		if( nCurPos<0 )
			nCurPos=0;
		Text[nCurPos] = NULL;
	case VK_UP:
		break;
	case VK_DOWN:
		break;
	case VK_RIGHT:
		break;
	case VK_LEFT:
		break;
	case VK_ESCAPE:
		::exit(0);
		break;
	case VK_PRIOR:
		break;
	case VK_NEXT:
		break;
	case VK_F1:
		break;
	case VK_F2:
		break;
	case VK_F3:
		break;
	case VK_F4:
		break;
	case VK_SPACE:
		break;
	}

	if( nCurPos>199 ) 
		nCurPos=199;
}

/** load the differents elements */
void init(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);   // Pour l'antialiasing
	
	LoadLights();
	LoadCameras();
	LoadFont();

	pToolkit->DisableDraw( OR_LOCAL_AXES );
}

/** when nothing occurs */
void idle(void)
{
	pToolkit->Update();
	pToolkit->PostReDisplay();
}

void display(void)
{
	pToolkit->RenderAllViewport();
	
	pInputOutput->Swap();
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
		pToolkit->Warning("particles_test main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);

	GlWin=pInputOutput->Initialisation_Win32(hInstance,NULL,0,"-==[ Test for animations ]==-",640,480,0,0);

	/* set up callback functions */
	pToolkit->SetMotionFunc(mouse);
	pToolkit->SetKeyPressedFunc(keyboard);
	pToolkit->SetMouseClicFunc(mouse_click);
	pToolkit->SetIdleFunc(idle);
	pToolkit->SetDisplayFunc(display);

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