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
#include "../../orion3d/physic/OR_ConstantForce.h"
#include "../../orion3d/physic/OR_SphericalJoint.h"
#include "../../orion3d/special_effects/OR_ParticuleSystem.h"
#include "../../orion3d/animation/OR_AnimationPlayer.h"
#include "../../orion3d/animation/OR_Animation.h"
#include "../../orion3d/hierarchy/OR_Node.h"
#include "../../orion3d/physic/OR_PhysicModel.h"
#include "../../orion3d/physic/OR_RigidBodyCollider.h"
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
/** \name to handle the collision */
//-------------------------------------------------------------------------
//@{
#define KRD_FILE "../krd/collision.krd"
OR_Mesh* pSphere = NULL;
OR_Mesh* pCube = NULL;
OR_RigidBodyCollider* pCollider = NULL;
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

	OR_Float global_ambient[4]={1, 1, 1, 1};
	pToolkit->Setfv(OR_LIGHT_GlobalAmbient, global_ambient);
}

/** load the cameras */
void LoadCameras()
{
	/* create and add a sphere **********************************/
	OR_SphereGizmo* pSphere = new OR_SphereGizmo();
	pSphere->SetDim( OR_Vector3D(0.1f, 0.1f, 0.1f) );
	pSphere->Posit( OR_Vector3D(0,0,0) );
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

void LoadCollision()
{
	/* load the file */
	pToolkit->LoadFile( KRD_FILE );

	pSphere = (OR_Mesh*) pToolkit->GetByName(OR_MESH, "sphere");
	pCube  = (OR_Mesh*) pToolkit->GetByName(OR_MESH, "cube");

	if( pSphere==NULL || pCube==NULL )
	{
		pToolkit->Warning("LoadCollision", "Can't load krd object.");
		return;
	}

	/* add the sphere to the physic engine */
	OR_PhysicModel* pSphereModel = new OR_PhysicModel( *pSphere );
	OR_RigidBody* pRigidBodySphere = new OR_RigidBody( *pSphere );
	pRigidBodySphere->SetPhysicModel(*pSphereModel);
	pRigidBodySphere->SetUpMassSphere( 1, 2 );
	pRigidBodySphere->SetPosition( pSphere->GetRelativePosition() );
	pToolkit->GetPhysicEntityManager().AddElement( pRigidBodySphere, true );

	/* add the Cube to the physic engine */
	OR_PhysicModel* pCubeModel = new OR_PhysicModel(*pCube);
	OR_RigidBody* pRigidBodyCube = new OR_RigidBody( *pCube );
	pRigidBodyCube->SetPhysicModel(*pCubeModel);
	pRigidBodyCube->SetUpMassBox( 1, OR_Vector3D(1,1,1) );
	pRigidBodyCube->SetPosition( pCube->GetRelativePosition() );
	pToolkit->GetPhysicEntityManager().AddElement( pRigidBodyCube, true );

	/* get back the collider created by the physic engine to handle collision between this pair of objects */
	pCollider = (OR_RigidBodyCollider*) pToolkit->GetPhysicEntityManager().GetCollider( *pRigidBodyCube, *pRigidBodySphere );
	OR_ASSERT( pCollider!=NULL );

	/* add a force */
//	pToolkit->GetPhysicEntityManager().GetForceManager().AddElement( new OR_ConstantForce(OR_Vector3D(0,0,-1)) );
	pToolkit->GetPhysicEntityManager().SetSolverType( OR_PhysicEntityManager::kPhysicSolver_Euler );
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
	case VK_NUMPAD2:
		pCube->TranslateAbsolute(OR_Vector3D(0,-0.1f,0));
		break;
	case VK_NUMPAD8:
		pCube->TranslateAbsolute(OR_Vector3D(0,0.1f,0));
		break;
	case VK_NUMPAD4:
		pCube->TranslateAbsolute(OR_Vector3D(-0.1f,0,0));
		break;
	case VK_NUMPAD6:
		pCube->TranslateAbsolute(OR_Vector3D(0.1f,0,0));
		break;
	case VK_NUMPAD3:
		pCube->TranslateAbsolute(OR_Vector3D(0,0,-0.1f));
		break;
	case VK_NUMPAD9:
		pCube->TranslateAbsolute(OR_Vector3D(0,0,0.1f));
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
	LoadCollision();

	pToolkit->DisableDraw( OR_LOCAL_AXES );
}

int MakeCollisionReport()
{		
	if( pCollider->GetLastCollisionStatus() )
		printf("- A collision has occured : nbr.of colliding pairs : %i\n", pCollider->GetNbrCollidingPairs());
	else
		printf("- No collision\n");

	return 0;
}

void DrawTriangle(OR_Mesh* pMesh, OR_U32 nNumFace, OR_Float color)
{
	OR_U32   *aFaceArray = pMesh->GetFaceList();
	OR_Float *aVertArray = pMesh->GetVertsArray();

	OR_U32 nVert1 = aFaceArray[3*nNumFace];
	OR_U32 nVert2 = aFaceArray[3*nNumFace+1];
	OR_U32 nVert3 = aFaceArray[3*nNumFace+2];
	OR_Globals::Context()->SimpleDrawMode();
	OR_Globals::Context()->SetColor(1-color,color,0,1);

	OR_Matrix4x4& CameraMatrix = pToolkit->GetCameraManager().GetActiveCamera()->GetAbsoluteMatrix();
	OR_Matrix4x4& MeshMatrix   = pMesh->GetAbsoluteMatrix();

	OR_Vector3D	Vert1( &aVertArray[3*nVert1] );
	Vert1 += MeshMatrix.GetTranslation();

	glLoadIdentity();
	OR_Maths::MultiplyCurrentModelView( ~CameraMatrix );
	OR_Maths::MultiplyCurrentModelView( MeshMatrix );

	glDisable(GL_DEPTH_TEST);

	glBegin(GL_TRIANGLES);
		glVertex3fv( & aVertArray[3*nVert1] );
		glVertex3fv( & aVertArray[3*nVert2] );
		glVertex3fv( & aVertArray[3*nVert3] );
	glEnd();

	glEnable(GL_DEPTH_TEST);

	OR_Globals::Context()->NormalDrawMode();
}

void DrawTriangles()
{
	AABBTreeCollider& TC = pCollider->GetTreeCollider();
	OR_U32 nNbrPair = TC.GetNbPairs();
	Pair* aPair = TC.GetPairs();
	/*
	for( OR_U32 i=0; i<nNbrPair; ++i )
	{
		DrawTriangle(pCube, aPair[i].id0,1);
		DrawTriangle(pSphere, aPair[i].id1,0);
	}*/
	if( nNbrPair>0 )
	{
		DrawTriangle(pCube, aPair[0].id0,1);
		DrawTriangle(pSphere, aPair[0].id1,0);
	}
}

/** when nothing occurs */
void idle(void)
{
	pToolkit->Update();
	pToolkit->PostReDisplay();

	MakeCollisionReport();
}


void display(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	pToolkit->RenderAllViewport();
	DrawTriangles();

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
int main( int argc, char *argv[ ], char *envp[ ] )
{
	/* check if we use an up-to-date version of Orion3D */
	if( OR_Toolkit::GetVersion() < OR_ORION3D_Version )
		pToolkit->Warning("main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(*pInputOutput);

	GlWin=pInputOutput->Initialisation_Win32(NULL,NULL,0,"-==[ Test for collision ]==-",640,480,0,0);

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