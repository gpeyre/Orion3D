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

#include "resource.h"


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
#include "../../orion3d/physic/OR_GravityForce.h"
#include "../../orion3d/physic/OR_DampingForce.h"
#include "../../orion3d/physic/OR_MagneticForce.h"
#include "../../orion3d/physic/OR_SpringForce.h"
#include "../../orion3d/special_effects/OR_MetaEnv.h"
#include "../../orion3d/special_effects/OR_MetaMesh.h"
#include "../../orion3d/animation/OR_AnimationPlayer.h"
#include "../../orion3d/animation/OR_Animation.h"
#include "../../orion3d/hierarchy/OR_Node.h"
#include "../../orion3d/physic/OR_PhysicEntityManager.h"
/* a cool build log */
#include "../../orion3d/misc/OR_PrintBuildLog.h"
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
/** \name to handle the metaballs  */
//-------------------------------------------------------------------------
//@{
OR_MetaEnv* pMetaEnv = NULL;
OR_Mesh*	pMesh = NULL;
#define TEXTURE_ADRESSE_0 	   "../krd/images/cube_face_posx.jpg"
#define TEXTURE_ADRESSE_1      "../krd/images/cube_face_negx.jpg"
#define TEXTURE_ADRESSE_3 	   "../krd/images/cube_face_posy.jpg"
#define TEXTURE_ADRESSE_2 	   "../krd/images/cube_face_negy.jpg"
#define TEXTURE_ADRESSE_4 	   "../krd/images/cube_face_posz.jpg"
#define TEXTURE_ADRESSE_5 	   "../krd/images/cube_face_negz.jpg"
#define MESH_ADRESS			   "../krd/shape.krd"
#define MESH_NAME			   "shape"
OR_U32 nGridPrecision = 35;
OR_U32 nNbrMetaballs = 0;
#define NBR_MAX_METABALLS 20
OR_Gizmo* aMetaballs[NBR_MAX_METABALLS];
//@}

//-------------------------------------------------------------------------
/** \name to display the FPS */
//-------------------------------------------------------------------------
//@{
#define FONT_FILE "../resources/arial.ttf"
char TextFPS[100];
char TextAnouce[100] = ":: Wellcome to metaball_test ::";
//@}


//Handle the OpenGl win
HWND GlWin;
HINSTANCE HInst;

/** to handle the mouse movements */
OR_I32 xmouse,ymouse;


/** load the lights */
void LoadLights()
{
	OR_Light_FreeSpot* pLight = new OR_Light_FreeSpot();

	pLight->SetAmbient ( OR_Vector4D(0.2f, 0.2f, 0.2f, 1.0f) );
	pLight->SetDiffuse ( OR_Vector4D(1.0f,1.0f,1.0f, 1.0f) );
	pLight->SetSpecular( OR_Vector4D(0.5f, 0.5f, 0.5f, 1.0f) );
	pLight->SetCutOff( 50 );
	pLight->SetDirection( OR_Vector3D( 0, 0, -1) );
	pLight->Posit( OR_Vector3D(0, 0, 18) );
	
	pToolkit->AddObject( pLight );

//	float global_ambient[4]={1, 1, 1, 1};
//	pToolkit->Setfv(OR_LIGHT_GlobalAmbient, global_ambient);
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
	pCamera->Posit(OR_Vector3D(0,-10,5) );
	pCamera->SetTarget( pSphere );
	
	/* create a viewport for this camera ************************/
	pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);

}

void AddMetaball(OR_U32 obj_type)
{
	OR_ASSERT( obj_type>=0 && obj_type<=2 );

	if( nNbrMetaballs>=NBR_MAX_METABALLS ) 
		return;

	/* create a sphere gizmo */
	OR_Vector3D dim(0.5f+OR_RAND);
	OR_Vector3D pos(OR_RAND*5-2.5f, OR_RAND*5-2.5f, OR_RAND*5-2.5f);
	/* create the gizmo */
	OR_Gizmo* pGizmo = NULL;
	switch( obj_type )
	{
	case 0:
		pGizmo = new OR_SphereGizmo( OR_Vector3D(1,0,0), OR_Vector3D(0,1,0), OR_Vector3D(0,0,1), dim );
		break;
	case 1:
		pGizmo = new OR_CubeGizmo( OR_Vector3D(1,0,0), OR_Vector3D(0,1,0), OR_Vector3D(0,0,1), dim );
		break;
	case 2:
		pGizmo = new OR_CylinderGizmo( OR_Vector3D(1,0,0), OR_Vector3D(0,1,0), OR_Vector3D(0,0,1), dim );
		break;
	default:
		pGizmo = NULL;
		break;      
	};

	pGizmo->Posit( pos );
	pGizmo->SetInfluenceRadius( dim[X]*2 );
	pToolkit->AddObject( pGizmo );
	/* add the gizmo to the meta-env */
	pMetaEnv->AddElement( pToolkit->GetGizmoManager().GetElementSelected() );
	
	/* add the gizmo to the physic engine */
	OR_RigidBody* pRigidBody = new OR_RigidBody( *pGizmo );
	pRigidBody->SetMass( 1 );
	pRigidBody->SetPosition( pGizmo->GetRelativePosition() );
	pToolkit->GetPhysicEntityManager().AddElement( pRigidBody, false );
	
	aMetaballs[nNbrMetaballs] = pGizmo;

	nNbrMetaballs++;
}

void LoadMetaballs()
{
	#define NB_META_OBJECT 0
	#define GIZMO_DIM 6

	pToolkit->LogAddLine("\n--> Loading meta-balls.");
	pToolkit->LogAddString("  NB.meta-balls : %i\n", NB_META_OBJECT);

	/* load the textures */
	float ambient_r[4]= { 1, 1, 1, 1};
	float diffuse_r[4]= { 1, 1, 1, 1};
	float specular_r[4]={ 1, 1, 1, 1};
	OR_ReflexiveMapShader* pShader = new OR_ReflexiveMapShader(
				TEXTURE_ADRESSE_0, TEXTURE_ADRESSE_1,
				TEXTURE_ADRESSE_2, TEXTURE_ADRESSE_3,
				TEXTURE_ADRESSE_4, TEXTURE_ADRESSE_5 );
	pShader->SetAmbient(  OR_Vector4D(1, 1, 1, 1) );
	pShader->SetDiffuse(  OR_Vector4D(1, 1, 1, 1) );
	pShader->SetSpecular( OR_Vector4D(1, 1, 1, 1) );
	pToolkit->AddShader( pShader );


	/* create & select a new meta-env */
	pMetaEnv = new OR_MetaEnv();
	pToolkit->GetSpecialEffectManager().AddElement( pMetaEnv );
	pMetaEnv->SetShader( *pShader );
	pMetaEnv->GetIsoSurface().GetGrid().Reset( nGridPrecision, nGridPrecision, nGridPrecision );

	
	/* create a gizmo as a support for the meta env */
	OR_CubeGizmo *pGizmo = new OR_CubeGizmo( OR_Vector3D(1,0,0), OR_Vector3D(0,1,0),
									OR_Vector3D(0,0,1), OR_Vector3D(GIZMO_DIM+1,GIZMO_DIM+1,GIZMO_DIM+1) );
	pGizmo->Posit( OR_Vector3D(0,0,0) );
	pToolkit->AddObject( pGizmo );
	pMetaEnv->SetSupportGizmo( *pGizmo );
	

	/* create new meta-balls */
	for( OR_I32 i=0; i<NB_META_OBJECT; i++ )
		AddMetaball( i%3 );

	/* create a gloabal spring force for each ball */
	#define REST_LENGTH 0
	OR_SpringForce* pForce = new OR_SpringForce(OR_Vector3D(0,0,0), 1.0f, REST_LENGTH, 0);
	pToolkit->GetPhysicEntityManager().GetForceManager().AddElement( pForce );
	/* add some friction */
	pToolkit->GetPhysicEntityManager().GetForceManager().AddElement( new OR_DampingForce(0.5f) );
	pToolkit->GetPhysicEntityManager().SetSolverType( OR_PhysicEntityManager::kPhysicSolver_Euler );

	/* add some cool metamesh */
	pToolkit->LoadFile(MESH_ADRESS);
	pMesh = (OR_Mesh*) pToolkit->GetByName(MESH_NAME);
	if( pMesh!=NULL )
	{
		OR_MetaMesh* pMetaMesh = new OR_MetaMesh( pMesh );
		pMetaEnv->AddElement( pMetaMesh );
		pMetaMesh->SetInfluenceRadius( 3.5f );
	}
	else
	{
		pToolkit->Warning("LoadMetaballs", "Couldn't load Mesh.");
	}
}

void Shake()
{
	#define SHAKE_INTENSITY 5.0f
	
	for( OR_U32 i=0; i<nNbrMetaballs; ++i )
	{
		OR_Vector3D Impulse(OR_RAND_RANGE(-SHAKE_INTENSITY, SHAKE_INTENSITY), 
					        OR_RAND_RANGE(-SHAKE_INTENSITY,SHAKE_INTENSITY), 
							OR_RAND_RANGE(-SHAKE_INTENSITY,SHAKE_INTENSITY) );
		aMetaballs[i]->GetRigidBody()->AddForceImpulse( Impulse );
	}
}

void LoadFont()
{
	OR_PixmapFont* pFontFPS = new OR_PixmapFont;
	pFontFPS->SetPosition(0,0.02f);
	pFontFPS->SetText( TextFPS );
	if( !pFontFPS->LoadFont(FONT_FILE) )
	{
		pToolkit->Warning("LoadFont", "Can't load font file.");
		::exit(1);
	}
	if( !pFontFPS->SetFaceSize(22))
	{
		pToolkit->Warning("LoadFont", "Can't set font size.");
		::exit(1);
	}
	pToolkit->GetFontManager().AddElement( pFontFPS );

	OR_PixmapFont* pFontAnnouce = new OR_PixmapFont;
	pFontAnnouce->SetPosition(0.5f,0.02f);
	pFontAnnouce->SetText( TextAnouce );
	if( !pFontAnnouce->LoadFont(FONT_FILE) )
	{
		pToolkit->Warning("LoadFont", "Can't load font file.");
		::exit(1);
	}
	if( !pFontAnnouce->SetFaceSize(16))
	{
		pToolkit->Warning("LoadFont", "Can't set font size.");
		::exit(1);
	}
	pToolkit->GetFontManager().AddElement( pFontAnnouce );
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


/** the callback function of the about dialog box */
BOOL CALLBACK AboutDialogProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{	
	switch (msg)
	{
	case WM_INITDIALOG:
		{
			return true;
		}
    case WM_COMMAND:
		{
			int id=LOWORD(wParam);
			EndDialog(hwnd,id);
		} 
		break;
	}
	return false;
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
	case VK_PRIOR:
		break;
	case VK_NEXT:
		break;
	case VK_F1:
		pMesh->Toggle();
		break;
	case VK_F2:
		break;
	case VK_F3:
		break;
	case VK_F4:
		break;
	case VK_SPACE:
		Shake();
		break;
	default:
		DialogBox(HInst,MAKEINTRESOURCE(IDD_DIALOG_ABOUT),NULL ,AboutDialogProc);
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
	LoadMetaballs();
	LoadFont();

	pToolkit->DisableDraw( OR_LOCAL_AXES );
}

/** when nothing occurs */
void idle(void)
{
	pToolkit->Update();
	pToolkit->PostReDisplay();
 
	sprintf(TextFPS, "FPS = %.2f", pToolkit->GetFPS() );
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
	HInst = hInstance;

	/* check if we use an up-to-date version of Orion3D */
	if( OR_Toolkit::GetVersion() < OR_ORION3D_Version )
		pToolkit->Warning("particles_test main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);

	GlWin=pInputOutput->Initialisation_Win32(hInstance,NULL,0,"-==[ Test for metaballs ]==-",640,480,0,0);

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