/*------------------------------------------------------------------------------*/
/** 
 *  \file  main.cpp
 *  \brief Main file for particles test program.
 *  \author Gabriel Peyr� 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) main.cpp (c) Gabriel Peyr� & Antoine Bouthors 2001";
#endif // OR_SCCSID




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
#include "../../orion3d/special_effects/OR_ParticuleSystem.h"
#include "../../orion3d/animation/OR_AnimationPlayer.h"
#include "../../orion3d/animation/OR_Animation.h"
#include "../../orion3d/hierarchy/OR_Node.h"
#include "../../orion3d/special_effects/OR_Cloth.h"
#include "../../orion3d/special_effects/OR_SpecialEffectManager.h"
#include "../../orion3d/physic/OR_PhysicEntityManager.h"
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
/** \name to handle the cloth */
//-------------------------------------------------------------------------
//@{
#define CLOTH_SIZE 15
#define CLOTH_MASS 1.0f
OR_Cloth* pCloth = NULL;
OR_Gizmo* pControledGizmo = NULL;
#define LOAD_SPHERE_DEFLECTOR
//@}

//Handle the OpenGl win
HWND GlWin;

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

void LoadCloth()
{
	OR_CubeGizmo *pClothBox = new OR_CubeGizmo(OR_Vector3D(1,0,0), OR_Vector3D(0,1,0), OR_Vector3D(0,0,1), OR_Vector3D(8,8,8));
	pCloth = new OR_Cloth(CLOTH_SIZE,CLOTH_SIZE, pClothBox);
	OR_ForceManager *pClothForceManager = new OR_ForceManager;
	
	pClothForceManager->AddElement( new OR_GravityForce );
	pClothForceManager->AddElement( new OR_DampingForce(0.01f) );
	pCloth->SetForceManager(*pClothForceManager);
	
	pToolkit->GetSpecialEffectManager().AddElement(pCloth);
	pCloth->SetSideStiffness(5.0f);
	pCloth->SetDiagonalStiffness(3.0f);
	pCloth->SetStructuralStiffness(1.5f);
	pCloth->SetSideDampling(0.0f);
	pCloth->SetDiagonalDampling(0.0f);
	pCloth->SetStructuralDampling(0.0f);
	
	pCloth->SetParticuleInvMass(CLOTH_SIZE*CLOTH_SIZE/CLOTH_MASS);
	pCloth->UseRelaxableConstraints(false);
	pCloth->SetMaxRelativeElongation(1.2f);
	//	pCloth->AutoSetDampling();
	
	pCloth->Build();
	
	pCloth->GetConstaintManager()->SetNbrIteration(1);
	
	pCloth->GetParticule(0,0)->SetInvMass(0);
	pCloth->GetParticule(CLOTH_SIZE-1,0)->SetInvMass(0);
	
	/* create e deflector */
#define BODY_MASS 20.5f
	float aX1[3] = {-1,0,0};
	float aY1[3] = {0,1,0};
	float aZ1[3] = {0,0,-1};
	float aDim1[3] = {2,2,2};
	OR_Vector3D Pos(0,0,-2);
	OR_Matrix4x4 IBody( BODY_MASS, 0, 0, 0,
		0, BODY_MASS, 0, 0,
		0, 0, BODY_MASS, 0,
		0, 0, 0, 1);
	
	OR_Gizmo* pDeflector = NULL;
#ifdef LOAD_SQUARE_DEFLECTOR
	pDeflector = new OR_SquareGizmo(aX1, aY1, aZ1, aDim1);
#endif
#ifdef LOAD_SPHERE_DEFLECTOR
	pDeflector = new OR_SphereGizmo(aX1, aY1, aZ1, aDim1);
#endif
#ifdef LOAD_CYLINDER_DEFLECTOR
	pDeflector = new OR_CylinderGizmo(aX1, aY1, aZ1, aDim1);
#endif
#ifdef LOAD_CUBE_DEFLECTOR
	pDeflector = new OR_CubeGizmo(aX1, aY1, aZ1, aDim1);
#endif
	_ASSERT( pDeflector!=NULL );
	
	OR_RigidBody*	pRigidBody = new OR_RigidBody(*pDeflector);
	pRigidBody->SetUpMassSphere(1, 2);
	pRigidBody->AdjustMass(BODY_MASS);
	pRigidBody->SetPosition( Pos );
	pRigidBody->SetBounce( 0.1f );
	OR_ForceManager*  pBodyForceManager = new OR_ForceManager;
	pBodyForceManager->AddElement( new OR_SpringForce(OR_Vector3D(0,0,-3), 5.0f, 0, 0.2f) );
	pRigidBody->SetForceManager( *pBodyForceManager );
	
	pDeflector->SetRigidBody( *pRigidBody );
	pDeflector->Posit( Pos );
	pRigidBody->SetPosition( Pos );
	pToolkit->GetGizmoManager().AddElement(pDeflector);
	pToolkit->AddObject(pDeflector);
	
	pToolkit->GetPhysicEntityManager().AddElement( pCloth );
	pToolkit->GetPhysicEntityManager().AddElement( pDeflector );
	pToolkit->GetPhysicEntityManager().AddElement( pRigidBody );
	
	
	pToolkit->GetPhysicEntityManager().SetTimeStep( 0.01f );
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
}

/** load the differents elements */
void init(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);   // Pour l'antialiasing
	
	LoadLights();
	LoadCameras();
	LoadCloth();

	pToolkit->DisableDraw( OR_LOCAL_AXES );
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
 *  \author Gabriel Peyr� 2001-10-17
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
		pToolkit->Warning("main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);

	GlWin=pInputOutput->Initialisation_Win32(hInstance,NULL,0,"-==[ Test for cloth ]==-",640,480,0,0);

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