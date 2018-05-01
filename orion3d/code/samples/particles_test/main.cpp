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
/** \name to handle the particules system */
//-------------------------------------------------------------------------
//@{
#define PARTICLE_SHAPE      "../krd/particles.krd"
#define PARTICLE_SHAPE_NAME "particle"
#define GROUND_FILE			"../krd/ground.krd"
#define PARTICULE_INVMASS 10.0f
OR_Gizmo* MyParticulesSource=NULL;
OR_ParticuleSystem* pParticuleSystem=NULL;

OR_ForceManager*  pParticuleForceManager = NULL; 

OR_GravityForce  *pGravityForce  = NULL;
OR_SpringForce   *pSpringForce   = NULL;
OR_DampingForce  *pDampingForce  = NULL;
OR_MagneticForce *pMagneticForce = NULL;
//@}

//Handle the OpenGl win
HWND GlWin;

/** to handle the mouse movements */
OR_I32 xmouse,ymouse;


/** load the lights */
void LoadLights()
{
	OR_Light_FreeSpot* pLight = new OR_Light_FreeSpot();

	OR_Float LightAmbient[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    OR_Float LightDiffuse[]    = { 1.0f,1.0f,1.0f, 1.0f};
    OR_Float LightSpecular[]   = { 0.5f, 0.5f, 0.5f, 1.0f };
	OR_Float LightPosition[]   = {-8, 0, 8};
	OR_Float LightDirection[]  = {0, 0, -1};

	pLight->SetAmbient ( OR_Vector4D(0.2f, 0.2f, 0.2f, 1.0f) );
	pLight->SetDiffuse ( OR_Vector4D(1.0f,1.0f,1.0f, 1.0f) );
	pLight->SetSpecular( OR_Vector4D(0.5f, 0.5f, 0.5f, 1.0f) );
	pLight->SetCutOff( 50 );
	pLight->SetDirection( OR_Vector3D( 0, 0, -1) );
	pLight->Posit( OR_Vector3D(-8, 0, 8) );
	
	pToolkit->AddObject( pLight );
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


/** load the default force mager [just a gravity force] */
void LoadForce()
{
	pGravityForce   = new OR_GravityForce(OR_Vector3D(0,0,-1.5f));
	pSpringForce    = new OR_SpringForce(OR_Vector3D(0,0,0), 0.05f, 0, 0) ;
	pDampingForce   = new OR_DampingForce(0.1f);
	pMagneticForce  = new OR_MagneticForce( OR_Vector3D(0,0.05f,0) );

	pGravityForce->Disable();
	pSpringForce->Disable();
	pDampingForce->Disable();
	pMagneticForce->Disable();
	

	/* we create a force manager specificaly for the particule system.
	   we don't use the global force manager, since the deflector is not affected by these force */
	pParticuleForceManager = new OR_ForceManager;
	pParticuleSystem->SetForceManager( *pParticuleForceManager );

	pParticuleForceManager->AddElement( pGravityForce );
	pParticuleForceManager->AddElement( pSpringForce );
	pParticuleForceManager->AddElement( pDampingForce );
	pParticuleForceManager->AddElement( pMagneticForce );
}


/** load a partices system */
void LoadParticleSystem()
{
	pToolkit->LogAddLine("\n--> Loading particules system.");

	/* load a krd to represent the shape */
	pToolkit->LoadFile(PARTICLE_SHAPE);
	OR_Mesh* pShape = (OR_Mesh*) pToolkit->GetByName( OR_MESH, PARTICLE_SHAPE_NAME );
	pShape->UseIt();

	/* set the shader as a bilboard one */
	if( pShape!=NULL )
	{
		OR_Node* pNode = pToolkit->GetHierarchyTree().GetNode( *pShape );
		if( pNode!=NULL )
			pNode->GetFather()->RemoveSon( *pNode );

		OR_Shader* pShader = pShape->GetShader();
		if( pShader!=NULL )
		{
			OR_BillboardShader* pBilboard = new OR_BillboardShader( pShader );			
			pShader->SetBlendingMode( OR_Blending_SrcA_1 );
			pShader->SetCullingMode( OR_Culling_None );
			pShape->SetShader( pBilboard );
		}
	}

	/* create the emiters */
	OR_VectorGizmo* pEmmitter = new OR_VectorGizmo;
	pEmmitter->Posit( OR_Vector3D(0,0,1) );
	pToolkit->AddObject( pEmmitter );
	pParticuleSystem = new OR_ParticuleSystem;
	pParticuleSystem->SetEmmitter(*pEmmitter);
	
	/* set up params */
	if( pShape!=NULL )
		pParticuleSystem->SetShape( *pShape );
	else
		pToolkit->Warning("LoadParticleSystem", "Can't retrieve the particles shape. Ooops.");
	pParticuleSystem->SetDebit(0.2f);
	pParticuleSystem->SetEmissionVariance(0.5f);
	pParticuleSystem->SetInitialSpeed(3.0f);
	pParticuleSystem->SetParticuleInvMass(PARTICULE_INVMASS);
	pParticuleSystem->SetEnergyStart(8);
	
	/* the special effects manager update the color of the particule system */
	pToolkit->GetSpecialEffectManager().AddElement(pParticuleSystem);	
	/* the physic entity manager update the position of the particules */
	pToolkit->GetPhysicEntityManager().AddElement( pParticuleSystem );

	
	pToolkit->GetPhysicEntityManager().SetTimeStep( 0.02f );
	pToolkit->GetPhysicEntityManager().SetSolverType( OR_PhysicEntityManager::kPhysicSolver_Euler );
}

void LoadGround()
{
	/* load the KRD file */
//	pToolkit->LoadFile( GROUND_FILE );

	/* create a deflector */
	#define BODY_MASS 20000

	OR_SquareGizmo* pDeflector = new OR_SquareGizmo(OR_Vector3D(-1,0,0), OR_Vector3D(0,1,0), 
													OR_Vector3D(0,0,-1), OR_Vector3D(10,10,0) );
	
	OR_RigidBody*	pRigidBody = new OR_RigidBody(*pDeflector);
	pRigidBody->SetUpMassBox(1,OR_Vector3D(10,10,1));
	pRigidBody->AdjustMass(BODY_MASS);
	
	pDeflector->SetRigidBody( *pRigidBody );
	pToolkit->GetGizmoManager().AddElement( pDeflector );
	pToolkit->AddObject( pDeflector );
	
	pToolkit->GetPhysicEntityManager().AddElement( pDeflector );
	pToolkit->GetPhysicEntityManager().AddElement( pRigidBody );
	
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

	case VK_F1:
		pGravityForce->Toggle();
		break;
	case VK_F2:
		pSpringForce->Toggle();
		break;
	case VK_F3:
		pDampingForce->Toggle();
		break;
	case VK_F4:
		pMagneticForce->Toggle();
		break;
	case VK_SPACE:
		pParticuleSystem->ModifiyDebit( 100 );
		pToolkit->Update();
		pParticuleSystem->ModifiyDebit( -100 );
		break;
	case VK_F5:
		pParticuleSystem->ModifiyDebit( -.2 );
		break;
	case VK_F6:
		pParticuleSystem->ModifiyDebit( .25 );
		break;
	case VK_F7:
		pParticuleSystem->SetInitialSpeed( pParticuleSystem->GetInitialSpeed()*0.8 );
		break;
	case VK_F8:
		pParticuleSystem->SetInitialSpeed( pParticuleSystem->GetInitialSpeed()*1.25 );
		break;
	case VK_F9:
		pParticuleSystem->SetEnergyStart( pParticuleSystem->GetEnergyStart()*.8 );
		break;
	case VK_F11:
		pParticuleSystem->SetEnergyStart( pParticuleSystem->GetEnergyStart()*1.25 );
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
	LoadParticleSystem();
	LoadForce();
	LoadGround();

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

	GlWin=pInputOutput->Initialisation_Win32(hInstance,NULL,0,"-==[ Test for particles system ]==-",640,480,0,0);

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

