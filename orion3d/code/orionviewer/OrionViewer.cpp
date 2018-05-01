/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleManager.cpp
 *  \brief This is the main OrionViewer file. 
 *  \author Gabriel Peyré 2001-07-18
 *
 *	It declares a Orion object [pToolkit], which is used for most of the 3D stuff.
 *	It uses basic Orion3D input function, except for mouse [check for deplacement of the
 *	camera], for keyboard and idle [it shouldn't, but we do that to achive some special 
 *	effects].
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) Orionviewer.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "stdafx.h"

/* Orion3D inclusion *************************************************************************/
#if (defined(_UNIX_)|defined(WIN32))
#include "../orion3d/configuration/OR_Config.h"
	#include "../orion3d/objects/OR_Gizmo.h"
	#include "../orion3d/objects/OR_Object.h"
	#include "../orion3d/objects/OR_Mesh.h"
	#include "../orion3d/animation/OR_AnimationPlayer.h"
	#include "../orion3d/animation/OR_Animation.h"
	#include "../orion3d/hierarchy/OR_Node.h"
	#include "../orion3d/special_effects/OR_ParticuleSystem.h"
	#include "../orion3d/special_effects/OR_Cloth.h"
	#include "../orion3d/special_effects/OR_MetaEnv.h"
	#include "../orion3d/special_effects/OR_SpecialEffectManager.h"
	#include "../orion3d/special_effects/OR_LensFlare.h"
	#include "../orion3d/shaders/OR_BumpShader_Emboss.h"
	#include "../orion3d/objects/OR_Bone.h"
	#include "../orion3d/utils/OR_Log.h"
	#include "../orion3d/utils/OR_Archive.h"
	#include "../orion3d/physic/OR_GravityForce.h"
	#include "../orion3d/physic/OR_DampingForce.h"
	#include "../orion3d/physic/OR_MagneticForce.h"
	#include "../orion3d/physic/OR_SpringForce.h"
	#include "../orion3d/wrapper_glut/OR_InputOutput_Glut.h"
	#include "../orion3d/toolkit/OR_Toolkit.h"
#elif defined(_MAC_OS_)
	#error TODO
	#include <fcntl.h>
#endif

using namespace OR;

#include "OrionViewer_GTK.h"

//-------------------------------------------------------------------------
/** @name wrapper lib specification */
//-------------------------------------------------------------------------
//@{
#ifdef _USE_GLUT_
	#ifdef OR_DEBUG
		#pragma comment(lib, "orion3d_wrapper_glut_dbg.lib")
		#pragma comment(lib, "orion3d_toolkit_dbg.lib")
	#else
		#pragma comment(lib, "orion3d_wrapper_glut.lib")
		#pragma comment(lib, "orion3d_toolkit.lib")
	#endif // ORION3D_DEBUG
#endif
//@}


//-------------------------------------------------------------------------
/** @name to control wich objects are loaded */
//-------------------------------------------------------------------------
//@{
#define LOAD_LIGHT
#define LOAD_CAMERAS
//@}


//-------------------------------------------------------------------------
/** @name 3D engine */
//-------------------------------------------------------------------------
//@{
/** the main helper, create all Orion3D stuff */
OR_Toolkit *pToolkit = new OR_Toolkit;
//@}

//-------------------------------------------------------------------------
/** @name input/output management */
//-------------------------------------------------------------------------
//@{
/* to handle the menu **********************************************************/
/** is the menu active [toggle with 'space'] */
bool Menu_Actif;
/** constants for the menu */
enum 
{ 
	M_NONE, M_Objet, M_Texture, 
	M_Wire, M_Reflet, 
	M_Shadow, M_Reflexion, M_LightColor, M_Exit,
	M_CamType, M_Roll, M_Help,
	M_KSP, M_BSP, M_Particules, M_MathsSurf, M_MetaBall,
	M_MetaShader, M_SurfaceShader, M_About,
	M_DrawLights, M_DrawCameras, M_DrawGizmos, M_DrawLocalAxes, M_ACT,
	M_SoundInfo
};

/** the wrapper used for / input/output */
OR_InputOutput_Glut MyInputOutput(*pToolkit);

/* for mac-os only **************************************************************/
#ifdef _MAC_OS_
bool ZoomEnabled = false;	/* indicates wether we're in zoom mode or not */
bool RotEnabled  = false;   /* rotation mode */
#endif
//@}


//-------------------------------------------------------------------------
/** \name to handle the camera */
//-------------------------------------------------------------------------
//@{
/** orion3d number for the cameras */
int CamTarget, CamFree;
/** is the target cam the current camera ? */
bool IsTargetCamSelected;
/** the number of the target (which is a gizmo) */
int GizmoTarget;
//@}

//-------------------------------------------------------------------------
/** \name to handle the wiewport */
//-------------------------------------------------------------------------
//@{
/** the orion3d id of the main viewport */
int MainViewport;
/** the orion3d id of the small viewport */
int SmallViewport;

OR_U32 WireFrame = GL_FILL;
//@}

//-------------------------------------------------------------------------
/** \name to handle the lights */
//-------------------------------------------------------------------------
//@{
/** the number of the lights */
OR_U32 SpotLight;
float LightRot=0;
bool LightAnimation=true;
//@}


/** load a .krd file [background] */
int LoadKRD()
{
	pToolkit->LogAddLine("--> Loading KRD.\n");

	char name[256]={0};
	printf("\n------------------------- Loading KRD file -------------------------\n");

#if (defined(_UNIX_) | defined(_MAC_OS_))
	printf("\nNom du fichier a charger [ex : olaf.krd] : ");
	scanf("%s", name);
	int n=pToolkit->LoadFile(name);
	/* reset the correct selected camera */
	if (IsTargetCamSelected)
		pToolkit->Select(OR_CAMERA, CamTarget);
	else
		pToolkit->Select(OR_CAMERA, CamFree);
	printf("%i objet(s) exporte(s) avec succes \n", n);
#else  /* windows */

	OPENFILENAME ofn = 
	{
		sizeof(OPENFILENAME),
		0,
		0,
		"Orion3D KRD\0*.KRD\0",
		NULL,
		1,
		0,
		name,
		256,
		NULL,
		0,
		"..\\krd",
		"Selectionnez le fichier KRD a charger",
		OFN_FILEMUSTEXIST,
		0,
		0,
		"KRD",
		NULL,
		NULL,
		NULL
	};
	
	if (GetOpenFileName(&ofn))
	{
		/* load the krd file *******************************/
		int n=pToolkit->LoadFile( name );
		/* reset the correct selected camera */
		if (IsTargetCamSelected)
			pToolkit->Select(OR_CAMERA, CamTarget);
		else
			pToolkit->Select(OR_CAMERA, CamFree);
		printf("KRD loading successful : %i objects have been loaded.\n", n);
		
		/* load the act file if it's possible **************/
		OPENFILENAME ofn_anim = 
		{
			sizeof(OPENFILENAME),
			0,
			0,
			"Orion3D ACT\0*.ACT\0",
			NULL,
			1,
			0,
			name,
			256,
			NULL,
			0,
			"..\\act",
			"Select the corresponding ACT file :",
			OFN_FILEMUSTEXIST,
			0,
			0,
			"ACT",
			NULL,
			NULL,
			NULL
		};

		if (GetOpenFileName(&ofn_anim))
		{
			pToolkit->LoadFile(name);
			OR_Animation* anim=pToolkit->GetAnimationManager().GetElementSelected();
			OR_Node* Node=pToolkit->GetNodeByName(anim->GetName());

			if (Node!=NULL) 
			{
				OR_AnimationPlayer* AnimationPlayer=new OR_AnimationPlayer(anim, -1);
				Node->AddPlayer(*AnimationPlayer);
				printf("ACT loading succesful.\n");
			}
			else
			{
				printf("ACT loading failed : animation root not find.\n");
			}
		}
	}
	else 
	{
		printf("\nKRD loading failed : file can not be opened.\n");
	}
	
	printf("--------------------------------------------------------------------\n");
	return 0;
#endif	/* #ifdef _UNIX_ */
}

/** load a .ksp file [hierarcical objects] */
int	LoadKSP()
{
	pToolkit->LogAddLine("--> Loading KSP.\n");

	char name[256]={0};
#if (defined(_UNIX_) | defined(_MAC_OS_))

	printf("\nNom du fichier a charger [ex : level.ksp]: ");
	scanf("%s", name);

	return pToolkit->LoadKSP(name);
#else /* windows */

	OPENFILENAME ofn = 
	{
		sizeof(OPENFILENAME),
		0,
		0,
		"Orion3D BSP\0*.KSP\0",
		NULL,
		1,
		0,
		name,
		256,
		NULL,
		0,
		"..\\ksp",
		"Selectionnez le fichier KSP a charger",
		OFN_FILEMUSTEXIST,
		0,
		0,
		"KSP",
		NULL,
		NULL,
		NULL
	};

	if (GetOpenFileName(&ofn)) 
	{
		pToolkit->LogAddString("  File : %s\n", name);
		return pToolkit->LoadFile(name);
	}
	else return OR_ERROR;

	return OR_ERROR;
#endif	/* #ifdef _UNIX_ */
}

/** load a Quake3 .bsp file */
int	LoadBSP()
{
	pToolkit->LogAddLine("--> Loading Quake3 PK3.\n");

	char name[256]={0};
#if (defined(_UNIX_) | defined(_MAC_OS_))

	printf("\nNom du fichier a charger [ex : level.bsp]: ");
	scanf("%s", name);

	return pToolkit->LoadBSP(name, "");
#else /* windows */

	OPENFILENAME ofn = 
	{
		sizeof(OPENFILENAME),
		0,
		0,
		"Quake 3 Arena PAK\0*.PK3\0",
		NULL,
		1,
		0,
		name,
		256,
		NULL,
		0,
		"\\Jeux\\Quake 3 Arena\\",
		"Selectionnez le fichier PK3 a charger",
		OFN_FILEMUSTEXIST,
		0,
		0,
		"PK3",
		NULL,
		NULL,
		NULL
	};

	if (GetOpenFileName(&ofn))
	{
		pToolkit->LogAddString("  PK3 File : %s\n", name);
		OR_Archive* Archive = new OR_Archive(name);
		printf("Archive : \"%s\" , Comments : %s\n",Archive->GetName(),Archive->GetComment());
		int n=0;
		void* HName;
		do
		{
			HName = Archive->GetFile(n);
			if (HName && strstr(Archive->GetFileName(HName),".bsp"))
				printf("File number %d : %s\n",n,Archive->GetFileName(HName));
			n++;
		} while (HName);

		printf("Enter the file number you want to load : ");
		if (scanf("%d",&n) && strstr(Archive->GetFileName(Archive->GetFile(n)),".bsp"))
		{
			void* Handle = Archive->GetFile(n);
			char* bspname = strdup(Archive->GetFileName(Handle));
			pToolkit->LogAddString("  BSP File : %s\n", bspname);
			printf("loading %s...",bspname);
			delete Archive;
			if( pToolkit->LoadFile(name) ) 
			{
				printf("successful\n");
				pToolkit->LogAddLine("<-- OK\n");
			} else 
			{
				printf("failed\n");
				pToolkit->LogAddLine("<-- Failure\n");
			}
			delete[] bspname;
			return 0;
		}

		printf("Not a valid .bsp file\n");
	}
	
	return 1;
#endif	/* #ifdef _UNIX_ */
}

/** set wireframe mode on/off */
void WireOnOff()
{
	switch (WireFrame)
	{
	case GL_POINT:
		WireFrame=GL_FILL;
		printf("%s \n","Mode de remplissage : plein");
		break;
	case GL_FILL:
        WireFrame=GL_LINE;
		printf("%s \n","Mode de remplissage : fil de fer");
	    break;
	case GL_LINE :
		WireFrame=GL_POINT;
		printf("%s \n","Mode de remplissage : points");
	    break;
	}
	glPolygonMode(GL_FRONT_AND_BACK, WireFrame);
}

/** print the help message */
void PrintHelp()
{
#ifdef _WIN32_
	OR_PrintFromFile("orionviewer_help.txt", "-==[OrionViewer Help]==-");
#else
	/* Rakan, tu peux utiliser le fichier orionviewer_help.txt */
	printf("\n");
	printf("----------------------------------------------------------------\n");
	printf("                -==[ OrionViewer - HELP ]==- 					\n");
	printf("----------------------------------------------------------------\n");
	printf("  'espace' 		 : toggle to/from menu mode 					\n");
	printf("  'ESC'    		 : quit											\n");
#ifdef _MAC_OS_
	printf("  'r'			 : toggle to/from rotation mode					\n");
	printf("  'z'			 : toggle to/from zoom mode						\n");
#endif
	printf("---------------- mode de rendus | rendering mode ---------------\n");
	printf("   'w, W'        : toggle solid|wireframe|point					\n");
	printf("----------------------------- ABOUT ----------------------------\n");
	printf("  'a, A'         : about OrionViewer                            \n");
	printf("----------------------------------------------------------------\n");
#endif
}


/** load the lights */
void LoadLights()
{
	pToolkit->LogAddLine("\n--> Loading lights.");

//#if 0
	OR_Float LightAmbient[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    OR_Float LightDiffuse[]    = { 1.0f,1.0f,1.0f, 1.0f};
    OR_Float LightSpecular[]   = { 0.5f, 0.5f, 0.5f, 1.0f };
	OR_Float LightPosition[]   = {-8, 0, 8};
	OR_Float LightDirection[]  = {0, 0, -1};

	SpotLight=pToolkit->AddFreeSpotLight();
	pToolkit->Setfv(OR_LIGHT_Ambient,  LightAmbient);
	pToolkit->Setfv(OR_LIGHT_Diffuse,  LightDiffuse);
	pToolkit->Setfv(OR_LIGHT_Specular, LightSpecular);
	pToolkit->Setf(OR_LIGHT_Cutoff, 50);  
	pToolkit->Setf(OR_LIGHT_Exponent, 15);  
	pToolkit->Setfv(OR_LIGHT_Direction, LightDirection);
	pToolkit->Setfv(OR_LIGHT_Pos, LightPosition);
//#endif
//#if 0
	OR_Float LightAmbient2[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    OR_Float LightDiffuse2[]    = { 0.6f,0.6f,0.6f, 1.0f};
    OR_Float LightSpecular2[]   = { 0.5f, 0.5f, 0.5f, 1.0f };
	OR_Float LightPosition2[]   = {-8, 0, 8};
	OR_Float LightDirection2[]  = {-1, 0, -1};
	pToolkit->AddFreeDirectLight();
	pToolkit->Setfv(OR_LIGHT_Ambient,  LightAmbient2);
	pToolkit->Setfv(OR_LIGHT_Diffuse,  LightDiffuse2);
	pToolkit->Setfv(OR_LIGHT_Specular, LightSpecular2);
	pToolkit->Setfv(OR_LIGHT_Direction, LightDirection2);
	pToolkit->Setfv(OR_LIGHT_Pos, LightPosition2);
//#endif

	/* set a global lighting *****************************************/
	float global_ambient[4]={1, 1, 1, 1};
//	pToolkit->Setfv(OR_LIGHT_GlobalAmbient, global_ambient);
}

/** load the cameras */
void LoadCameras()
{
	pToolkit->LogAddLine("\n--> Loading cameras.");

	/* add a target for a camera ***********************************/
	float vX5[3]={1,0,0};
	float vY5[3]={0,1,0};
	float vZ5[3]={0,0,1};
	float dim5[3]={0.1f,0.1f,0.1f};
	float gizmo_pos5[3]={0,0,0};
	float CamFreePos[3] = {0,0,5};
	float CamTargetPos[3] = {0,-10,5};
	float color[4]={0,0,0,0.6f};

	/* create a free camera ***************************************/
	CamFree=pToolkit->AddFreeCamera();
	pToolkit->Setfv(OR_CAMERA_Pos, CamFreePos);

	/* create a target camera ***********************************/
	CamTarget=pToolkit->AddTargetCamera();
	pToolkit->Setfv(OR_CAMERA_Pos, CamTargetPos);
	/* create the target */
 	GizmoTarget=pToolkit->AddSphereGizmo(vX5, vY5, vZ5, dim5);
	pToolkit->Select(OR_GIZMO, GizmoTarget);
	/* positionnate the gizmo */
	pToolkit->Posit(OR_GIZMO, gizmo_pos5);
	/* assign the gizmo to the camera target */
	pToolkit->SetCameraGizmoTarget();
	
	pToolkit->Select(OR_CAMERA, CamTarget);
	MainViewport=pToolkit->AddScreenViewPort(1);
	pToolkit->SetViewPortDimensions(0,0,1, 1);

	IsTargetCamSelected=true;
}

/** print an about dialog box */
void About()
{
#ifdef _WIN32_		
	MessageBox(NULL,"OrionViewer : a simple Orion3D program\n\nOrion3D (c) 2000 Gabriel & Antoche",
		"About OrionViewer.",
		MB_OK | MB_ICONINFORMATION);
#else
	printf("\n\nOrionViewer : a simple Orion3D program\n\nOrion3D (c) 2000 Gabriel & Antoche\n\nPress h for help.");
#endif
}

void PrintFPSReport()
{
	
	pToolkit->PrintFPSReport();
	pToolkit->MakeFPSLog();
}

void ToggleDrawGizmo()
{
	pToolkit->ToggleDraw(OR_GIZMO);
}
void ToggleDrawLight()
{
	pToolkit->ToggleDraw(OR_LIGHT);
}

void ToggleDrawCamera()
{
	pToolkit->ToggleDraw(OR_CAMERA);
}

void ToggleDrawLocalAxe()
{
	pToolkit->ToggleDraw(OR_LOCAL_AXES);
}

void DrawNothing()
{
	pToolkit->DisableDraw(OR_GIZMO);
	pToolkit->DisableDraw(OR_LIGHT);
	pToolkit->DisableDraw(OR_CAMERA);
	pToolkit->DisableDraw(OR_LOCAL_AXES);
}

void ToggleCameraType()
{
	if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
	{
		pToolkit->Select(OR_CAMERA, CamTarget);
		pToolkit->Select(OR_VIEWPORT, SmallViewport);
		pToolkit->SetViewportCamera();
		pToolkit->Select(OR_CAMERA, CamFree);
		pToolkit->Select(OR_VIEWPORT, MainViewport);
		pToolkit->SetViewportCamera();
		IsTargetCamSelected=true;
	}
	else 
	{
		pToolkit->Select(OR_CAMERA, CamFree);
		pToolkit->Select(OR_VIEWPORT, SmallViewport);
		pToolkit->SetViewportCamera();
		pToolkit->Select(OR_CAMERA, CamTarget);
		pToolkit->Select(OR_VIEWPORT, MainViewport);
		pToolkit->SetViewportCamera();
		IsTargetCamSelected=false;
	}
}



/** to handle mouse movements */
void mouse(OR_I32 x, OR_I32 y)
{
	bool BoutG=pToolkit->GetLeftButtonState();
	bool BoutD=pToolkit->GetRightButtonState();
	int xmouse=pToolkit->GetMousePosX();
	int ymouse=pToolkit->GetMousePosY();
	/* 
	 * on mac, rotate upon pressing 'z' then the left mouse button only 
	 * if 2 button mouse available, then can do it the windows way 
	 */
	#ifdef _MAC_OS_
		if ( ( BoutG && RotEnabled && !BoutD) ||
			 (!BoutG &&                BoutD)    )
	#else
		/* on other, rotate upon pressing the right mouse button */
		if (BoutD && !BoutG)
	#endif
	{
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->RotateWorldCamera(Z, (xmouse-x)*0.01);
			pToolkit->RotateCamera(X, (ymouse-y)*0.01);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->RotateCamera(Y, -(xmouse-x)*0.01);
			pToolkit->RotateCamera(X, (ymouse-y)*0.01);
		}
	}

	/* 
	 * on mac, zoom upon pressing 'r' then the left mouse button only 
	 * if 2 button mouse available, then can do it the windows way 
	 */
	#ifdef _MAC_OS_
		else if( (BoutG && ZoomEnabled && !BoutD) ||
				 (BoutG && 				   BoutD)   )
	#else
		else if (BoutG)
	#endif
	{
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(Z, (-ymouse+y)*0.05);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->TranslateCamera(Z, (-ymouse+y)*0.05);
		}
	}
	
    pToolkit->SetMousePosX(x);
    pToolkit->SetMousePosY(y);
}

/** to handle keyboard */
void keyboard(OR_U32 button, OR_I32 x, OR_I32 y)
{
#ifdef _USE_GLUT_
   switch((char) button)
   {
	case ' ' :
		if (Menu_Actif) glutDetachMenu(GLUT_RIGHT_BUTTON);
		else glutAttachMenu(GLUT_RIGHT_BUTTON);
		Menu_Actif=!Menu_Actif;
		break;
	case 'w':
		WireOnOff();
		break;
	case 'a':
		About();
		break;
	case 'h': case 'H':
		PrintHelp();
		break;
	case 'f':
		pToolkit->PrintFPSReport();
		pToolkit->MakeFPSLog();
		break;
	/* allows user to zoom with mouse on mac */
	#ifdef _MAC_OS_
		case 'z':
			ZoomEnabled = !ZoomEnabled;
			/* can't zoom and rotate at the same time */
			if(ZoomEnabled && RotEnabled) RotEnabled = false;
			break;
		case 'r':
			RotEnabled  = !RotEnabled;
			/* can't zoom and rotate at the same time */
			if(ZoomEnabled && RotEnabled) ZoomEnabled = false;
			break;
	#endif
	/* take a screenshot ***********************************/
	case 'x':
		pToolkit->MakeScreenShot();
		break;
	// escape button
	case 27:
		::exit(0);
		break;
	}
#endif
#ifdef _USE_GTK_
	switch (button)
	{
	case GDK_Left:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(X, -10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->RotateCamera(Z, -0.1f);
		}
	    break;
	case GDK_Right:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(X, 10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->RotateCamera(Z, 0.1f);
		}
		break;
	case GDK_Up:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(Z, -10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->TranslateCamera(Z, -1);
		}
		break;
	case GDK_Down:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(Z, 10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->TranslateCamera(Z, 1);
		}
		break;
	case GDK_space:
		break;
	case GDK_e:
		pToolkit->ModifyDebit(200);
		pToolkit->Update();
		pToolkit->PostReDisplay();
		pToolkit->ModifyDebit(-200);
		break;
	case GDK_Escape:
		exit(0);
		break;
	case GDK_w:
		WireOnOff();
		break;
	case GDK_f:
		PrintFPSReport();
		break;
	/* allows user to zoom with mouse on mac */
	#ifdef _MAC_OS_
		case GDK_z:
			ZoomEnabled = !ZoomEnabled;
			/* can't zoom and rotate at the same time */
			if(ZoomEnabled && RotEnabled) RotEnabled = false;
			break;
		case GDK_r:
			RotEnabled  = !RotEnabled;
			/* can't zoom and rotate at the same time */
			if(ZoomEnabled && RotEnabled) ZoomEnabled = false;
			break;
	#endif
	}
#endif
}

/** to handle arrow keys */
void keyboardspec(OR_I32  key, OR_I32 x, OR_I32 y)
{
#ifdef _USE_GLUT_
	switch (key) 
	{
	case GLUT_KEY_UP:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(Z, -10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->TranslateCamera(Z, -1);
		}
		break;
	case GLUT_KEY_DOWN:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(Z, 10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->TranslateCamera(Z, 1);
		}
		break;
	case GLUT_KEY_LEFT:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(X, -10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->RotateCamera(Z, -0.1f);
		}
		break;
	case GLUT_KEY_RIGHT:
		if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Free)
		{
			pToolkit->TranslateCamera(X, 10);
		}
		else if (pToolkit->Geti(OR_CAMERA_GetType)==OR_CAMERA_Target)
		{
			pToolkit->RotateCamera(Z, 0.1f);
		}
		break;
	}
#endif

#if _USE_WIN32_
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
#endif // _USE_WIN32_
}

/** to handle a pop up menu */
void menu(int choix)
{
	switch (choix) 
	{
	case M_Objet:
		LoadKRD();
		break;
	case M_Wire:
		WireOnOff();
		break;
	case M_Roll:
		pToolkit->Toggle(OR_CAMERA_Roll);
		break;
	case M_Shadow:
		pToolkit->Toggle(OR_Shadows);
		break;
	case M_Reflexion:
		pToolkit->Toggle(OR_Reflections);
		break;
	case M_CamType:
		ToggleCameraType();
		break;
	case M_Exit:
		::exit(0);
		break;
	case M_Help:
		PrintHelp();
		break; 
	case M_KSP:
		LoadKSP();
		break;
	case M_BSP:
		LoadBSP();
		break;
	case M_About:
		About();
		break;
	case M_DrawGizmos:
		pToolkit->ToggleDraw(OR_GIZMO);
		break;
	case M_DrawLights:
		pToolkit->ToggleDraw(OR_LIGHT);
		break;
	case M_DrawCameras:
		pToolkit->ToggleDraw(OR_CAMERA);
		break;
	case M_DrawLocalAxes:
		pToolkit->ToggleDraw(OR_LOCAL_AXES);
		break;
	default:
		break;
	}
}

/** load the differents elements */
void init(void)
{
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glClearAccum(0.0f, 0.0f, 0.0f, 0.0f);   // Pour l'antialiasing
	

	/* load the lights */
#ifdef LOAD_LIGHT
	LoadLights();
#endif

	/* load the cameras */
#ifdef LOAD_CAMERAS
	LoadCameras();
#endif
}

/** when nothing occurs */
void idle(void)
{
	
	pToolkit->Update();

	/* re-draw everything */
	pToolkit->PostReDisplay();
}

/** snif ... no more cool graphics ... */
void quit()
{
	::exit(0);
}

/** function executed when the program exit */
void OnExit()
{
	pToolkit->LogAddLine("\n--- OrionViewer terminated ---\n");
	delete pToolkit;
	pToolkit=NULL;
}

/* main function *****************************************************************************************/
/** main function : start an infinite loop */
#if (defined(_USE_GLUT_)|defined(_USE_GTK_))
	int main(int argc, char** argv)
#endif
#ifdef _USE_WIN32_
	int WINAPI WinMain(HINSTANCE hInstance,  
                       HINSTANCE hPrevInstance,   
                       LPSTR lpCmdLine,   
                       int nCmdShow)
#endif
{
	/* register exit function */
	atexit(OnExit);

	/* check if we use an up-to-date version of Orion3D */
	if( OR_Toolkit::GetVersion() < OR_ORION3D_Version )
		pToolkit->Warning("Orionviewer main", "The version of Orion3D.dll is not supported.");

	/* register the wrapper used for input.output */
	pToolkit->SetInputOutput(MyInputOutput);
	MyInputOutput.Initialisation(&argc, argv, "-==[OrionViewer]==-",1024,768);

	printf("\n\n   -==[ OrionViewer ]==-\n");
	printf(" by Gabriel Peyre & Antoche\n\n");
	printf("Visit Orion3D homepage : www.orion3d.fr.st\n");
	printf("\n'Espace' pour activer le menu d'option\n");
	printf("    puis bouton droit pour derouler le menu\n\n");
	printf("\n'Space' to activate the options menu\n");
	printf("    then click right to pop up the menu\n\n");
	printf("\n 'h, H' : Help menu\n");
	fflush(stdout);

	/* set up callback functions */
	pToolkit->SetMotionFunc(mouse);
	pToolkit->SetKeyPressedFunc(keyboard);
	pToolkit->SetSpecialFunc(keyboardspec);
	pToolkit->SetIdleFunc(idle);

	pToolkit->LogAddLine("\n--- Lauching OrionViewer ---\n");
#ifdef _USE_GLUT_
	/* create a menu using the glut */
	glutCreateMenu(menu);
	glutAddMenuEntry("     - OrionViewer - Menu -", M_NONE);
	glutAddMenuEntry("------------------------------------------------------", M_NONE);
	glutAddMenuEntry("To togle menu active on/off : ", M_NONE);
	glutAddMenuEntry("        press 'space'", M_NONE);
	glutAddMenuEntry("------------------------------------------------------", M_NONE);
	glutAddMenuEntry("Satellite/Marche visualisation mode", M_CamType);
	glutAddMenuEntry("Toggle camera roll on/off", M_Roll);
	glutAddMenuEntry("------------------------------------------------------", M_NONE);
	glutAddMenuEntry("Load a .KRD file", M_Objet);
	glutAddMenuEntry("Load a .KSP file", M_KSP);
	glutAddMenuEntry("Load a .BSP file", M_BSP);
	glutAddMenuEntry("------------------------------------------------------", M_NONE);
	glutAddMenuEntry("Toggle wireframe  on/off   [w]", M_Wire);
	glutAddMenuEntry("Toggle shadows    on/off", M_Shadow);
	glutAddMenuEntry("Toggle reflexions on/off", M_Reflexion);
	glutAddMenuEntry("-------------------------------------------------------", M_NONE);
	glutAddMenuEntry("Toggle draw lights on/off", M_DrawLights);
	glutAddMenuEntry("Toggle draw cameras on/off", M_DrawCameras);
	glutAddMenuEntry("Toggle draw gizmos on/off", M_DrawGizmos);
	glutAddMenuEntry("Toggle draw local axis on/off", M_DrawLocalAxes);
	glutAddMenuEntry("-------------------------------------------------------", M_NONE);
	glutAddMenuEntry("Help!!                     [h]", M_Help);
	glutAddMenuEntry("About OrionViewer          [a]", M_About);
	glutAddMenuEntry("-------------------------------------------------------", M_NONE);
	glutAddMenuEntry("Quit                       [esc]", M_Exit);
#endif // _USE_GLUT_

#ifdef _USE_GTK_
	CreateGTKWindows();
#endif // _USE_GTK_

	init();

	if( argc>1 )  
		pToolkit->LoadFile(argv[1]);

	/* run an infinite loop */
	pToolkit->MainLoop();

	return 0;
}


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END  OF FILE	                                 //
///////////////////////////////////////////////////////////////////////////////


