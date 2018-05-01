/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief main file for \b GLUT wrapper test.
 *  \author Gabriel Peyré 2001-10-17
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) main.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

/* first thing to do : tell to Orion3D we are using the GLUT wrapper */
#define _USE_GLUT_
/* tell that we are using the Orion3D dll */
#define ORION3D_IMPORTS


//-------------------------------------------------------------------------
/** \name orion3d file inclusion */
//-------------------------------------------------------------------------
//@{
/* this will check wich library we will need to use */
#include "../../orion3d/configuration/OR_Config.h"
#include "../../orion3d/toolkit/OR_Toolkit.h"
#include "../../orion3d/wrapper_glut/OR_InputOutput_Glut.h"
/* we want to avoid putting OR:: before each Orion3D beautifull class names */
using namespace OR;
//@}



//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef OR_DEBUG
	#pragma comment(lib, "orion3d_wrapper_glut_dbg.lib")
	#pragma comment(lib, "orion3d_toolkit_dbg.lib")
#else
	#pragma comment(lib, "orion3d_wrapper_glut.lib")
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
OR_InputOutput_Glut* pInputOutput = new OR_InputOutput_Glut(*pToolkit);
//@}


/*------------------------------------------------------------------------------*/
/** 
 * Name : LoadMyWorld
 *
 *  \author Gabriel Peyré 2001-10-17
 *
 *	Just load a tiny gizmo and a camera : add your own stuff !
 */ 
/*------------------------------------------------------------------------------*/
void LoadMyWorld()
{	
	/* create and add a sphere **********************************/
	OR_SphereGizmo* pSphere = new OR_SphereGizmo();
	pToolkit->AddObject(pSphere);

	/* create a target camera ***********************************/
	pToolkit->AddTargetCamera();
	OR_Camera_Target* pCamera = (OR_Camera_Target*) pToolkit->GetCameraManager().GetElementSelected();
	pCamera->Posit(OR_Vector3D(0,-10,5) );
	pCamera->SetTarget( pSphere );

	/* create a viewport for this camera ************************/
	pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);
}



/** to handle mouse movements */
void mouse(OR_I32 x, OR_I32 y)
{
	OR_Bool BoutG=pToolkit->GetLeftButtonState();
	OR_Bool BoutD=pToolkit->GetRightButtonState();
	OR_I32 xmouse=pToolkit->GetMousePosX();
	OR_I32 ymouse=pToolkit->GetMousePosY();

	if( BoutD && !BoutG )
	{
		pToolkit->RotateCamera(Y, (xmouse-x)*0.01);
		pToolkit->RotateCamera(X, (ymouse-y)*0.01);
	}
	else if( BoutG )
	{
		pToolkit->TranslateCamera(Z, (-ymouse+y)*0.05);
	}
	
    pToolkit->SetMousePosX(x);
    pToolkit->SetMousePosY(y);
}

/** to handle keyboard */
void keyboard(OR_U32 button, OR_I32 x, OR_I32 y)
{
	switch((char) button)
	{
	case 27:
		::exit(0);
		break;
	default:
		printf("Orion3D is SO COOL !\n");
	}
}

/** to handle arrow keys */
void keyboardspec(OR_I32  key, OR_I32 x, OR_I32 y)
{
	switch (key) 
	{
	case GLUT_KEY_UP:
		pToolkit->TranslateCamera(Z, -1);
		break;
	case GLUT_KEY_DOWN:
		pToolkit->TranslateCamera(Z, 1);
		break;
	case GLUT_KEY_LEFT:
		pToolkit->RotateCamera(Z, -0.1f);
		break;
	case GLUT_KEY_RIGHT:
		pToolkit->RotateCamera(Z, 0.1f);
		break;
	}
}

/** when nothing occurs */
void idle(void)
{
	/* update the 3D engine */
	pToolkit->Update();
	
	/* re-draw everything */
	pToolkit->PostReDisplay();

	/* here you can add code to handle things each frame */
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
int main(int argc, char** argv)
{
	
	/* check if we use an up-to-date version of Orion3D */
	if( OR_Toolkit::GetVersion() < OR_ORION3D_Version )
		pToolkit->Warning("Orionviewer main", "The version of Orion3D.dll is not supported.");
	
	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);
	pInputOutput->Initialisation(&argc, argv, "-==[OrionViewer]==-",1024,768);
	
	printf("\n\n   -==[ Test for GLUT wrapper ]==-\n");
	fflush(stdout);

	/* just load a tiny gizmo and a camera */
	LoadMyWorld();
	
	/* set up callback functions */
	pToolkit->SetMotionFunc(mouse);
	pToolkit->SetKeyPressedFunc(keyboard);
	pToolkit->SetSpecialFunc(keyboardspec);
	pToolkit->SetIdleFunc(idle);
	
	pToolkit->LogAddLine("\n--- Lauching GLUT wrapper test ---\n");
	

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

