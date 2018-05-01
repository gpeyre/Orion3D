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

/*
Roman Surface
sin(2*u)*cos(v)^2, sin(u)*sin(2*v), cos(u)*sin(2*v) 
*/

/*
Dini's Surface
f(u,v) = (cos(u)sin(v),sin(u)sin(v),cos(v)+log(tan(v/2))+a*u),
0 <= u <= 2*pi, 0 < v < pi.
*/

/*
klein bottle :
x = cos(u)*(cos(u/2)*(sqrt(2)+cos(v))+(sin(u/2)*sin(v)*cos(v)))
y = sin(u)*(cos(u/2)*(sqrt(2)+cos(v))+(sin(u/2)*sin(v)*cos(v)))
z = -sin(u/2)*(sqrt_2+cos(v))+cos(u/2)*sin(v)*cos(v)
*/

/*
seashell :
x=a*(1-v/(2*OR_PI))*cos(n*v)*(1+cos(u))+c*cos(n*v) 
y=a*(1-v/(2*OR_PI))*sin(n*v)*(1+cos(u))+c*sin(n*v) 
z=b*v/(2*pi)+a*(1-v/(2*pi))*sin(u)             
Example:
a=0.2,b=1,c=0.1,n=2,u={ 0,2*pi},v={0,2*pi}
*/

/*
Kuen's Surface
This is one of the more complicated of the surfaces of constant negative curvature. 
Parametric form :
x=2*(cos(u)+u*sin(u))*sin(v)/(1+u*u*sin(v)*sin(v))
y=2*(sin(u)-u*cos(u))*sin(v)/(1+u*u*sin(v)*sin(v))
z=log(tan(v/2))+2*cos(v)/(1+u*u*sin(v)*sin(v)) 
u = {-4, 4}, v = 0.05, pi-0.05
*/


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
/** \name to handle the maths surface */
//-------------------------------------------------------------------------
//@{
OR_MathSurface* pSurface = NULL;
OR_Float rTime = 0;
OR_Float rSpeed = 0.01f;

#define TEXTURE_ADRESSE_0 	   "../krd/images/cube_face_posx.jpg"
#define TEXTURE_ADRESSE_1      "../krd/images/cube_face_negx.jpg"
#define TEXTURE_ADRESSE_2 	   "../krd/images/cube_face_posy.jpg"
#define TEXTURE_ADRESSE_3 	   "../krd/images/cube_face_negy.jpg"
#define TEXTURE_ADRESSE_4 	   "../krd/images/cube_face_posz.jpg"
#define TEXTURE_ADRESSE_5 	   "../krd/images/cube_face_negz.jpg"

#define NBR_FUNCTIONS 2
OR_U32 nSelectedFunction = 0;
T_MathSurf_Callback aMathFunc[NBR_FUNCTIONS];
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
	pCamera->SetTarget( pSphere );
	pCamera->Posit(OR_Vector3D(2,0,0));
	
	/* create a viewport for this camera ************************/
	pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);
}

#define SURF_FUNC(i, x, y, z, umin, umax, vmin, vmax)							\
void SurfFunc_##i(OR_Vector3D& val, OR_Float u, OR_Float v, void* pUserParam)	\
{																				\
OR_ASSERT(pUserParam != NULL);													\
OR_Float t = * ((OR_Float*)pUserParam);											\
u = (umin) + u*((umax)-(umin));													\
v = (vmin) + v*((vmax)-(vmin));													\
val[X] = (x);																	\
val[Y] = (y);																	\
val[Z] = (z);																	\
}


//-------------------------------------------------------------------------
/** \name the functions */
//-------------------------------------------------------------------------
//@{
/* GAB's surface (c) */
SURF_FUNC(0, 
	(1 + cos(v*5+t)*0.5f)*cos(v)*sin(u), 
	(1 + cos(v*5+t)*0.5f)*cos(v)*cos(u), 
	(1 + cos(v*5+t)*0.5f)*sin(v), 
	0,OR_TWOPI, 
	-OR_PI*0.5f,OR_PI*0.5f)

/* Dini's Surface
   f(u,v) = (cos(u)sin(v),sin(u)sin(v),cos(v)+log(tan(v/2))+a*u) */
SURF_FUNC(1, 
   cos(u)*sin(v), 
   sin(u)*sin(v), 
   cos(v)+log( OR_ABS(tan(v/2))+0.001f )+cos(t)*u, 
   0,OR_TWOPI, 
   0,OR_PI)
//@}




void LoadMathsurf()
{
	/* register the maths function */
	aMathFunc[0] = SurfFunc_0;
	aMathFunc[1] = SurfFunc_1;


	/* load the textures */
	OR_ReflexiveMapShader* pShader = new OR_ReflexiveMapShader(
		TEXTURE_ADRESSE_0, TEXTURE_ADRESSE_1,
		TEXTURE_ADRESSE_2, TEXTURE_ADRESSE_3,
		TEXTURE_ADRESSE_4, TEXTURE_ADRESSE_5 );
	pShader->SetAmbient(  OR_Vector4D(1, 1, 1, 1) );
	pShader->SetDiffuse(  OR_Vector4D(1, 1, 1, 1) );
	pShader->SetSpecular( OR_Vector4D(1, 1, 1, 1) );
	pToolkit->AddShader( pShader );
	pShader->SetCullingMode( OR_Culling_None );

	/* create the shader */	
	pSurface = new OR_MathSurface();
	pSurface->SetShader( pShader );
	pSurface->SetCallback( SurfFunc_1 );
	pSurface->SetUserParam( (void*) &rTime );
	pSurface->SetPrecision(50,50);

	/* add it to Orion3D */
	pToolkit->AddObject( pSurface );
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
		break;
	case VK_DOWN:
		break;
	case VK_RIGHT:
		rSpeed += 0.05f;
		break;
	case VK_LEFT:
		rSpeed -= 0.05f;
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
		nSelectedFunction = (nSelectedFunction+1)%NBR_FUNCTIONS;
		pSurface->SetCallback( aMathFunc[nSelectedFunction] );
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
	LoadMathsurf();

	pToolkit->DisableDraw( OR_LOCAL_AXES );
}

/** when nothing occurs */
void idle(void)
{
	pToolkit->Update();
	pToolkit->PostReDisplay();

	/* animate the surface */
	rTime += rSpeed;
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