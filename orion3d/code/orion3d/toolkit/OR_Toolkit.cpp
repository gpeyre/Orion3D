/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Toolkit.cpp
 *  \brief implementation of class OR_Toolkit
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Toolkit.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Toolkit.h"
#include "../input_output/OR_InputOutput_ABC.h"
#include "../physic/OR_PhysicEntityManager.h"


/* print a coool build message */
#include "../misc/OR_PrintBuildLog.h"

#ifndef OR_USE_INLINE
	#include "OR_Toolkit.inl"
#endif

using namespace OR;


OR_Toolkit::OR_Toolkit()
:	OR_ShellObject_ABC()
{
	/* initialize maths datas */
	OR_Maths::Init();	
	
	/* register the class for the class factory */
	OR_ClassFactory::RegisterAllClass();

	/* create all global variables */
	OR_Globals::Initialize(this);

	/* for the moment, no input/output wrapper has been linked with Orion3D */
	pInputOutput_	= NULL;

	/* create the physic engine */
	pPhysicManager_ = new OR_PhysicEntityManager;
	/* create a font manager */
	pFontManager_ = new OR_FontManager;

	/* create the shell */
	pKernel_  = new OR_ShellKernel( *this );
	pConsole_ = new OR_ShellConsoleText( pKernel_ );
	this->GetShellManager().AddElement( pKernel_ );

	/* create a log file */
	this->AddLog();
	this->LogAddTimeDate();
	this->LogAddOSVersion();
	this->LogAddMemorySatus();
	this->LogAddOrion3DConfiguration();
}

OR_Toolkit::~OR_Toolkit()
{
	/* Delete all global datas */
	OR_Globals::Destroy();

	OR_DELETE(pPhysicManager_);
	OR_DELETE(pFontManager_);
}

void OR_Toolkit::InitGraphics()
{
	/* initialize opengl */
	OR_Globals::Context()->SetDefaultCullingMode();
	OR_Globals::Context()->SetDefaultDepthTestingMode();
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glEnable(GL_POLYGON_SMOOTH); <-- NEVER TURN GL_POLYGON_SMOOTH ON (it sucks)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DITHER);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDrawBuffer(GL_BACK);

	/* check for opengl extensions */
	OR_Globals::GLExtensionsManager()->SetUpExtensions();

	/* enable vertex weighting */
	glEnable(GL_VERTEX_WEIGHTING_EXT);

	/* initialize DevIL */
	ilInit();
	/* set openil renderer */
	ilutRenderer(ILUT_OPENGL);	
	/* GL cannot use palettes anyway, so convert early. */
	ilEnable(IL_CONV_PAL);
	/* Gets rid of dithering on some nVidia-based cards. */
	ilutEnable(ILUT_OPENGL_CONV);
#if 0
	/* checking openil version */
	if ( (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) ||
		 (iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION) ||
		 (ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) )
	{
		OR_Globals::MessageHandler()->Warning("OR_Toolkit::InitGraphics", "The version of OpenIL.dll is not supported.");
	}
#endif
}

char* GetErrorInfo(OR_RETURN_CODE error)
{
	switch (error)
	{
	case OR_OK:
		return "No error.";
	case OR_ERROR:
		return "An error as occured.";
	case OR_Invalid_Argument:
		return "The argument is not a valide one.";
	case OR_Unknown_Argument:
		return "The argument is unknown.";
	case OR_Manager_SelectedEmpty:
		return "The selected element of the manager is empty."; 
	case OR_Manager_InvalidSelectedType:
		return "The selected element of the manager as not the correct type.";
	case OR_Error_Opening_File:
		return "Impossible to open the file.";
	case OR_Error_File_Not_Supported:
		return "The type of file is not supported.";
	case OR_Error_Animation_Tree:
		return "The animation tree hasn't got the right structure.";
	case OR_Error_Argument_OutOfRange:
		return "The argument is out of range.";
	default:
		return "Unknown error code.";
	};
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RETURN_CODE OR_Toolkit::LoadFile(const char *name)
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Load data from a file.
 */ 
/*------------------------------------------------------------------------------*/
OR_RETURN_CODE OR_Toolkit::LoadFile(const char *name)
{
	/* set the base adress of the krd */
	OR_Globals::GetBaseFileAdress()->clear();
	OR_Globals::GetBaseFileAdress()->concat( name );

	OR_File file(name, "rb");
	/* open the file */
	if (!file.IsOpen())
	{
		OR_Globals::MessageHandler()->Warning("OR_Toolkit::LoadFile", "Can't open %s file.", name);
		return OR_Error_Opening_File;
	}

	OR_Serializer TempSerializer;
	file >> TempSerializer;

	if( TempSerializer.GetError() )
	{
		/* the version of the file is not supported */
		OR_Globals::MessageHandler()->Warning("OR_Toolkit::LoadFile", 
			"The version of the file %s is not supported.", name);
		file.Close();
		return OR_Error_Opening_File;
	}

	file.Close();
	return OR_OK;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_RETURN_CODE OR_Toolkit::SaveFile(const char *name)
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Save \b Orion3D datas into a file.
 */ 
/*------------------------------------------------------------------------------*/
OR_RETURN_CODE OR_Toolkit::SaveFile(const char *name)
{
	/* open the file */
	OR_File file(name, "wb");
	if (!file.IsOpen())
	{
		OR_Globals::MessageHandler()->Warning("OR_Toolkit::SaveFile", 
			"Can't open %s file.", name);
		return OR_Error_Opening_File;
	}

	file << Serializer_;

	file.Close();
	return OR_OK;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Serializer& OR_Toolkit::GetSerializer()
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	\return the serializer that manage the serialization process.
 */ 
/*------------------------------------------------------------------------------*/
OR_Serializer& OR_Toolkit::GetSerializer()
{
	return Serializer_;
}

#define IMPL_PREPARE_EXPORT(name, anim, hier, shader, specialfx)		\
void OR_Toolkit::Prepare##name##Export()								\
{																		\
	Serializer_.SetExportAnimation(anim);								\
	Serializer_.SetExportHierarchy(hier);								\
	Serializer_.SetExportShader(shader);								\
	Serializer_.SetExportSpecialEffect(specialfx);						\
}
IMPL_PREPARE_EXPORT(Animation,		true,  false, false, false);
IMPL_PREPARE_EXPORT(Hierarchy,		false, true,  true,  true);
IMPL_PREPARE_EXPORT(Shader,			false, false, true,  false);
IMPL_PREPARE_EXPORT(SpecialEffect,	false, false, false, true);
IMPL_PREPARE_EXPORT(All,			true,  true,  true,  true);
#undef IMPL_PREPARE_EXPORT

void OR_Toolkit::SetBspLoadingFunc(OR_Bsp_Loading bsploading) 
{ 
	OR_Globals::BSP_Renderer()->SetLoadingCallback(bsploading); 
}

void OR_Toolkit::Update()
{
	/* compute each world relative matrix *****************************************/
	OR_Globals::HierarchyTree()->Update();
	/* resolve special effects ****************************************************/
	OR_Globals::SpecialEffectManager()->Update();
	/* resolve physic computations ************************************************/
	pPhysicManager_->UpdatePhysics();
	/* update the shell ***********************************************************/
	pConsole_->Update();
}

void OR_Toolkit::RenderAllViewport()
{
	/* for FPS computations */
#ifdef _COMPUTE_FPS_
	OR_Globals::PerformancesManager()->UpdateFPS();
#endif
	/* draw each viewport */
	OR_Globals::ViewportManager()->Display();
}

void OR_Toolkit::RenderToViewport(OR_Viewport& Wiewport)
{
	/* setup before rendering ***************************************************/
	/* initialize the model view matrix before drawing the objects */
	glLoadIdentity();
	OR_Globals::CameraManager()->GetActiveCamera()->Put();
	/* positionnate the lights */
glPushMatrix();
	OR_Globals::LightManager()->PutAllLights();
glPopMatrix();

	/* draw the scene ************************************************************/
    glPushMatrix();
	OR_Globals::BSP_Renderer()->Render(OR_Globals::CameraManager()->GetElementSelected());

		/* vive Antoche */
		OR_Vector3D Pos=OR_Globals::CameraManager()->GetPosition();
		CurrentArea = OR_Globals::Portal_Renderer()->FindArea(Pos);
		if (CurrentArea!=-1)
		{
			OR_Globals::Portal_Renderer()->Render(OR_Globals::CameraManager()->GetElementSelected(),CurrentArea);

			OR_Vector3D Dir=-OR_Globals::CameraManager()->GetCamAxe(Z);
			OR_Vector3D Target;OR_Plane* IPlan;
			OR_Globals::Portal_Renderer()->FindIntersection(CurrentArea,Pos,Pos+Dir*500,Target,IPlan);
			glPushMatrix();
			glTranslated(Target[0],Target[1],Target[2]);
			OR_Globals::Data()->SolidSphere(.5,5,5);
			glPopMatrix();
		}

		/* hierarchy *******************************************/
		/* draw the hierarchy */
		OR_Globals::HierarchyTree()->Draw();
		/* special effects *************************************/
		/* draw the special effects */		
		OR_Globals::SpecialEffectManager()->Draw();
		/* fonts ***********************************************/
		pFontManager_->Draw();
		/* alpha pipeline **************************************/
		/* sort the alpha blended faces */
		OR_Globals::AlphaPipeline()->PerformSort();
		/* draw the alpha blended faces */
		OR_Globals::AlphaPipeline()->Flush();
	glPopMatrix();
}

OR_I32 OR_Toolkit::Enable(OR_Types etat)
{
	switch (etat) 
	{
	/* enable draw OR_Object on/off */
	case OR_MATH_SURFACE_OnOff:
		return OR_Globals::MathSurfaceManager()->Enable();
		break;
	case OR_LIGHT_OnOff:
		return OR_Globals::LightManager()->Enable();
		break;
	case OR_MESH_OnOff:
		return OR_Globals::MeshManager()->Enable();
		break;
	case OR_GIZMO_OnOff:
		return OR_Globals::GizmoManager()->Enable();
		break;
	case OR_CAMERA_OnOff:
		return OR_Globals::CameraManager()->Enable();
		break;
	/* default *************************************************/
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Disable(OR_Types etat)
{
	switch (etat) 
	{
	/* disable draw OR_Object on/off */
	case OR_MATH_SURFACE_OnOff:
		return OR_Globals::MathSurfaceManager()->Disable();
		break;
	case OR_LIGHT_OnOff:
		return OR_Globals::LightManager()->Disable();
		break;
	case OR_MESH_OnOff:
		return OR_Globals::MeshManager()->Disable();
		break;
	case OR_GIZMO_OnOff:
		return OR_Globals::GizmoManager()->Disable();
		break;
	case OR_CAMERA_OnOff:
		return OR_Globals::CameraManager()->Disable();
		break;
	/* default *************************************************/
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_Bool OR_Toolkit::Toggle(OR_Types etat)
{
	switch (etat) 
	{
	/* togle draw OR_Object on/off */
	case OR_MATH_SURFACE_OnOff:
		return OR_Globals::MathSurfaceManager()->Toggle();
		break;
	case OR_LIGHT_OnOff:
		return OR_Globals::LightManager()->Toggle();
		break;
	case OR_MESH_OnOff:
		return OR_Globals::MeshManager()->Toggle();
		break;
	case OR_GIZMO_OnOff:
		return OR_Globals::GizmoManager()->Toggle();
		break;
	case OR_CAMERA_OnOff:
		return OR_Globals::CameraManager()->Toggle();
		break;
	/* default *************************************************/
	default:
		return false;
	}
}

OR_I32 OR_Toolkit::Setf(OR_Types type, OR_Float val)
{
	switch (type) 
	{
	/* camera *************************************************/
	case OR_CAMERA_DistanceMin:
		return OR_Globals::CameraManager()->SetDistanceMin(val);
		break;
	case OR_CAMERA_Near:
		return OR_Globals::CameraManager()->SetNear(val);
		break;
	case OR_CAMERA_Far:
		return OR_Globals::CameraManager()->SetFar(val);
		break;
	case OR_CAMERA_Fovy:
		return OR_Globals::CameraManager()->SetFovy(val);
		break;
	/* light **************************************************/
	case  OR_LIGHT_Cutoff:
		return OR_Globals::LightManager()->SetCutOff(val);
		break;
	case OR_LIGHT_Exponent:
		return OR_Globals::LightManager()->SetExponent(val);
		break;
	/* particules system **************************************/
/* TODO
	case OR_PARTICULES_Debit:
		return MyParticulesSystemManager->SetDebit(val);
		break;
	case OR_PARTICULES_InitialSpeed:
		MyParticulesSystemManager->SetInitialSpeed(val);
		break;
	case OR_PARTICULES_EnergyStart:
		return MyParticulesSystemManager->SetEnergyStart(val);
		break;
	case OR_PARTICULES_EnergyStartVariance:
		return MyParticulesSystemManager->SetEnergyStartVariance(val);
		break;
	case OR_PARTICULES_EnergyLost:
		return MyParticulesSystemManager->SetEnergyLost(val);
		break;
	case OR_PARTICULES_EnergyLostVariance:
		return MyParticulesSystemManager->SetEnergyLostVariance(val);
		break;
	case OR_PARTICULES_Mass:
		return MyParticulesSystemManager->SetParticuleMass(val);
		break;
	case OR_PARTICULES_MassVariance:
		return MyParticulesSystemManager->SetParticuleMassVariance(val);
		break;
	case OR_PARTICULES_MaxRadius:
		return MyParticulesSystemManager->SetMaxRadius(val);
		break;
	case OR_PARTICULES_NbMaxParticules:
		return MyParticulesSystemManager->SetNbMaxParticules((OR_I32)val);
		break;
	case OR_PARTICULES_EmissionVariance:
		return MyParticulesSystemManager->SetEmissionVariance(val);
		break;
	case OR_PARTICULES_Bounce:
		return MyParticulesSystemManager->SetParticuleBounce(val);
		break;
*/
	/* shader *************************************************/
	case OR_SHADER_Shine:
		return OR_Globals::ShaderManager()->SetShine(val);
		break;
	case OR_SHADER_Alpha:
		return OR_Globals::ShaderManager()->SetAlpha(val);
		break;
	case OR_SHADER_BorderWidth:
		return OR_Globals::ShaderManager()->SetBorderWidth((OR_I32)val);
		break;
	/* gizmo ***************************************************/
	case OR_GIZMO_Intensity:
		return OR_Globals::GizmoManager()->SetMetaIntensity(val);
		break;
	case OR_GIZMO_InfluenceRadius:
		return OR_Globals::GizmoManager()->SetInfluenceRadius(val);
		break;
	/* default *************************************************/
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Setfv(OR_Types type, OR_Float *vect)
{
	switch (type) 
	{
	/* camera ************************************************/
	case OR_CAMERA_Pos: 
		OR_Globals::CameraManager()->Posit(vect);
		break;
	/* light *************************************************/
	case OR_LIGHT_Ambient:
		OR_Globals::LightManager()->SetAmbient(vect);
		break;
	case OR_LIGHT_Diffuse:
		OR_Globals::LightManager()->SetDiffuse(vect);
		break;
	case OR_LIGHT_Specular:
		OR_Globals::LightManager()->SetSpecular(vect);
		break;
	case OR_LIGHT_GlobalAmbient:
		OR_Globals::LightManager()->SetGlobalAmbient(vect);
		break;
	case OR_LIGHT_Atenuation:
		OR_Globals::LightManager()->SetAtenuation(vect);
		break;
	case OR_LIGHT_Pos:
		OR_Globals::LightManager()->Posit(vect);
		break;
	case OR_LIGHT_Direction:
		OR_Globals::LightManager()->SetDirection(vect);
		break;
	/* mesh **************************************************/
	case OR_MESH_Pos:
		OR_Globals::MeshManager()->Posit(vect);
		break;
	/* shader ************************************************/
	case OR_SHADER_Ambient:
		OR_Globals::ShaderManager()->SetAmbient(vect);
		break;
	case OR_SHADER_Diffuse:
		OR_Globals::ShaderManager()->SetDiffuse(vect);
		break;
	case OR_SHADER_Emission:
		OR_Globals::ShaderManager()->SetEmission(vect);
		break;
	case OR_SHADER_Specular:
		OR_Globals::ShaderManager()->SetSpecular(vect);
		break;
	/* gizmo ***********************************************/
	case OR_GIZMO_Dim:
		OR_Globals::GizmoManager()->SetDim(OR_Vector3D(vect));
		break;
	/* viewport ************************************************/
	case OR_VIEWPORT_Color:
		OR_Globals::ViewportManager()->SetColor(vect);
		break;
	/* default *************************************************/
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Setf(OR_Types type, OR_Coord_RVBA component, OR_Float val)
{
	switch (type) 
	{
	/* light ***************************************************/
	case OR_LIGHT_Ambient:
		OR_Globals::LightManager()->SetAmbient(component, val);
		break;
	case OR_LIGHT_Diffuse:
		OR_Globals::LightManager()->SetDiffuse(component, val);
		break;
	case OR_LIGHT_Specular:
		OR_Globals::LightManager()->SetSpecular(component, val);
		break;
	/* particules **********************************************/
/*
	case OR_PARTICULES_StartColor:
		MyParticulesSystemManager->SetStartColor(component, val);
		break;
	case OR_PARTICULES_EndColor:
		MyParticulesSystemManager->SetEndColor(component, val);
		break;
*/
	/* shader **************************************************/
	case OR_SHADER_Ambient:
		OR_Globals::ShaderManager()->SetAmbient(component, val);
		break;
	case OR_SHADER_Diffuse:
		OR_Globals::ShaderManager()->SetDiffuse(component, val);
		break;
	case OR_SHADER_Emission:
		OR_Globals::ShaderManager()->SetEmission(component, val);
		break;
	case OR_SHADER_Specular:
		OR_Globals::ShaderManager()->SetSpecular(component, val);
		break;
	/* default *************************************************/
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Modf(OR_Types type, OR_Float val)
{
	switch (type) 
	{
	/* camera *************************************************/
	case 0: /* to kill stupid warning */
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Select(OR_Elements type, OR_I32 num)
{
	switch (type) 
	{
	case OR_LIGHT:
		return OR_Globals::LightManager()->Select(num);
		break;
	case OR_CAMERA:
		return OR_Globals::CameraManager()->Select(num);
		break; 
	case OR_MESH:
		return OR_Globals::MeshManager()->Select(num);
		break;
	case OR_MATH_SURFACE:
		return OR_Globals::MathSurfaceManager()->Select(num);
		break;
	case OR_SHADER:
		return OR_Globals::ShaderManager()->Select(num);
		break;
	case OR_GIZMO:
		return OR_Globals::GizmoManager()->Select(num);
		break;
		break;
	case OR_VIEWPORT:
		return OR_Globals::ViewportManager()->Select(num);
		break;
	default:
		return OR_Unknown_Argument; 
	}
}

OR_I32 OR_Toolkit::Delete(OR_Elements type)
{
	switch (type) 
	{
	case OR_LIGHT:
		return OR_Globals::LightManager()->DeleteElement();
		break;
	case OR_CAMERA:
		return OR_Globals::CameraManager()->DeleteElement();
		break; 
	case OR_MESH:
		return OR_Globals::MeshManager()->DeleteElement();
		break;
	case OR_MATH_SURFACE:
		return OR_Globals::MathSurfaceManager()->DeleteElement();
		break;
	case OR_SHADER:
		return OR_Globals::ShaderManager()->DeleteElement();
		break;
	case OR_GIZMO:
		return OR_Globals::GizmoManager()->DeleteElement();
		break;
	case OR_VIEWPORT:
		return OR_Globals::ViewportManager()->DeleteElement();
		break;
	default:
		return OR_Unknown_Argument;
	}
}

OR_I32 OR_Toolkit::Geti(OR_Types type)
{
	switch (type) 
	{
	/* camera *************************************************/

	/* get nb elements **************************************/
	case OR_Nb_CAMERA:
		return OR_Globals::CameraManager()->GetNbElements();
		break; 
	case OR_Nb_MESH: 
		return OR_Globals::MeshManager()->GetNbElements();
		break;  
	case OR_Nb_LIGHT:
		return OR_Globals::LightManager()->GetNbElements();
		break;
	case OR_Nb_MATHS_SURFACE:
		return OR_Globals::MathSurfaceManager()->GetNbElements();
		break;
	case OR_Nb_SHADER:
		return OR_Globals::ShaderManager()->GetNbElements();
		break;
	case OR_Nb_GIZMO:
		return OR_Globals::GizmoManager()->GetNbElements();
		break;
	case OR_Nb_VIEWPORT:
		return OR_Globals::ViewportManager()->GetNbElements();
		break;
	case OR_Nb_TEXTURE:
		return OR_Globals::TextureManager()->GetNbElements();
		break;
	/* get selected ****************************************/
	case OR_Selected_CAMERA:
		return OR_Globals::CameraManager()->GetNumElementSelected();
		break; 
	case  OR_Selected_LIGHT:
		return OR_Globals::LightManager()->GetNumElementSelected();
		break; 
	case  OR_Selected_MESH:
		return OR_Globals::MeshManager()->GetNumElementSelected();
		break;
	case OR_Selected_MATHS_SURFACE:
		return OR_Globals::MathSurfaceManager()->GetNumElementSelected();
		break;
	case OR_Selected_SHADER:
		return OR_Globals::ShaderManager()->GetNumElementSelected();
		break;
	case OR_Selected_GIZMO:
		return OR_Globals::GizmoManager()->GetNumElementSelected();
		break;
	case OR_Selected_VIEWPORT:
		return OR_Globals::ViewportManager()->GetNumElementSelected();
		break;
	case OR_Selected_TEXTURE:
		return OR_Globals::TextureManager()->GetNumElementSelected();
		break;
	/* shader **************************************************/
	case OR_SHADER_GetType:
		return OR_Globals::ShaderManager()->GetType();
		break;
	/* camera ***************************************************/
	case OR_CAMERA_GetType:
		return OR_Globals::CameraManager()->GetType();
		break;
	/* default **************************************************/
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_Float OR_Toolkit::Getf(OR_Types name)
{
	switch (name)
	{
	/* camera *************************************************/
	case OR_CAMERA_DistanceMin:
		/* TODO */
		return 0;//OR_Globals::CameraManager()->GetDistanceMin();
		break;
	case OR_CAMERA_Near:
		return OR_Globals::CameraManager()->GetNear();
		break;
	case OR_CAMERA_Far:
		return OR_Globals::CameraManager()->GetFar();
		break;
	case OR_CAMERA_Fovy:
		return OR_Globals::CameraManager()->GetFovy();
		break;
	case OR_CAMERA_Aspect:
		return OR_Globals::CameraManager()->GetAspect();
		break;
	default:
		return OR_Unknown_Argument;
		break;
	}
}

OR_I32 OR_Toolkit::Trans(OR_Elements type, OR_Coord_XYZW axe, OR_Float val)
{
	switch (type) 
	{
	case OR_LIGHT:
		OR_Globals::LightManager()->Translate(axe, val);
		break;
	case OR_MESH:
		OR_Globals::MeshManager()->Translate(axe, val);
	case OR_CAMERA:
		OR_Globals::CameraManager()->Translate(axe, val); 
		break;
	case OR_MATH_SURFACE:
		OR_Globals::MathSurfaceManager()->Translate(axe, val);
		break;
	case OR_GIZMO:
		OR_Globals::GizmoManager()->Translate(axe, val);
		break;
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Trans(OR_Elements type, OR_Float vect[3])
{
	switch (type) 
	{
	case OR_LIGHT:
		OR_Globals::LightManager()->Translate(OR_Vector3D(vect));
		break;
	case OR_MESH:
		OR_Globals::MeshManager()->Translate(OR_Vector3D(vect));
		break; 
	case OR_CAMERA:
		OR_Globals::CameraManager()->Translate(vect); 
		break;
	case OR_MATH_SURFACE:
		OR_Globals::MathSurfaceManager()->Translate(OR_Vector3D(vect));
		break;
	case OR_GIZMO:
		OR_Globals::GizmoManager()->Translate(vect);
		break;
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Rotate(OR_Elements type, OR_Float val)
{
	switch (type) 
	{
	case OR_MESH:
		OR_Globals::MeshManager()->Rotate(val);
		break;
	case OR_MATH_SURFACE:
		OR_Globals::MathSurfaceManager()->Rotate(val);
		break;
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

OR_I32 OR_Toolkit::Posit(OR_Elements type, OR_Float pos[3])
{
	switch (type) 
	{
	case OR_LIGHT:
		OR_Globals::LightManager()->Posit(pos);
		break;
	case OR_MESH:
		OR_Globals::MeshManager()->Posit(pos);
		break;
	case OR_CAMERA:
		OR_Globals::CameraManager()->Posit(pos); 
		break;
	case OR_MATH_SURFACE:
		OR_Globals::MathSurfaceManager()->Posit(OR_Vector3D(pos));
		break;
	case OR_GIZMO:
		OR_Globals::GizmoManager()->Posit(OR_Vector3D(pos));
		break;
	default:
		return OR_Unknown_Argument;
	}
	return OR_OK;
}

/* enable/disable the draw of objects in the hierarchy **********************/
void OR_Toolkit::EnableDraw(OR_Elements type)	
{
	OR_Globals::SetDrawObject( type, true );
}

void OR_Toolkit::DisableDraw(OR_Elements type)	
{
	OR_Globals::SetDrawObject( type, false );
}

OR_Bool OR_Toolkit::ToggleDraw(OR_Elements type)
{
	OR_Globals::SetDrawObject( type, !OR_Globals::GetDrawObject(type) );
	return OR_Globals::GetDrawObject(type);
}


/* methodes de gestion de la camera *****************************************/
OR_I32 OR_Toolkit::AddFreeCamera()
{
	OR_I32 num = OR_Globals::CameraManager()->AddFreeCamera();
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::CameraManager()->GetElementSelected() );
	return num;
}

OR_I32 OR_Toolkit::AddTargetCamera()
{
	OR_I32 num = OR_Globals::CameraManager()->AddTargetCamera();
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::CameraManager()->GetElementSelected() );
	return num;
}

OR_I32 OR_Toolkit::RotateCamera(OR_Coord_XYZW axe, OR_Float angle)
{
	return OR_Globals::CameraManager()->Rotate(axe, angle);
}

OR_I32 OR_Toolkit::RotateWorldCamera(OR_Coord_XYZW axe, OR_Float angle)
{
	return OR_Globals::CameraManager()->RotateWorld(axe, angle);
}

OR_I32 OR_Toolkit::TranslateCamera(OR_Coord_XYZW axe, OR_Float val)
{
	return OR_Globals::CameraManager()->Translate(axe, val);
}

OR_I32 OR_Toolkit::TranslateCamera(OR_Vector3D vect)
{
	return OR_Globals::CameraManager()->Translate(vect);
}

OR_I32 OR_Toolkit::TranslateWorldCamera(OR_Coord_XYZW axe, OR_Float val)
{
	return OR_Globals::CameraManager()->TranslateWorld(axe, val);
}

OR_I32 OR_Toolkit::TranslateWorldCamera(OR_Vector3D vect)
{
	return OR_Globals::CameraManager()->TranslateWorld(vect);
}

OR_I32 OR_Toolkit::SetCameraGizmoTarget()
{
	return OR_Globals::CameraManager()->SetTarget(
		OR_Globals::GizmoManager()->GetElementSelected() );
}

/* to handle the lights ******************************************************/
OR_I32 OR_Toolkit::AddFreeSpotLight()
{
	OR_I32 num = OR_Globals::LightManager()->AddFreeSpotLight();
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::LightManager()->GetElementSelected() );
	return num;
}

OR_I32 OR_Toolkit::AddTargetSpotLight()
{
	OR_I32 num = OR_Globals::LightManager()->AddTargetSpotLight();
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::LightManager()->GetElementSelected() );
	return num;
}

OR_I32 OR_Toolkit::AddFreeDirectLight()
{
	OR_I32 num = OR_Globals::LightManager()->AddFreeDirectLight();
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::LightManager()->GetElementSelected() );
	return num;
}

OR_I32 OR_Toolkit::AddTargetDirectLight()
{
	OR_I32 num = OR_Globals::LightManager()->AddTargetDirectLight();
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::LightManager()->GetElementSelected() );
	return num;
}

OR_I32 OR_Toolkit::SetLightGizmoTarget()
{
	return OR_Globals::LightManager()->SetTarget(
		OR_Globals::GizmoManager()->GetElementSelected() );
}

/* Procedure de gestion des performances ****************************************/
OR_Float OR_Toolkit::GetFPS()
{
#ifndef _COMPUTE_FPS_
	OR_Globals::MessageHandler()->Debug("OR_Toolkit::GetFPS", 
					"FPS computation is not enable.Use '#define _COMPUTE_FPS_' first.");
	return OR_ERROR;
#else
	return OR_Globals::PerformancesManager()->GetFPS();
#endif /* #ifdef _COMPUTE_FPS_ */
}

void OR_Toolkit::PrintFPSReport()
{
#ifndef _COMPUTE_FPS_
	OR_Globals::MessageHandler()->Debug("OR_Toolkit::FPSReport", 
					"FPS computation is not enable.Use '#define _COMPUTE_FPS_' first.");
#else
	OR_Globals::PerformancesManager()->FPSReport();
#endif /* #ifdef _COMPUTE_FPS_ */
}

void OR_Toolkit::MakeFPSLog()
{
#ifndef _COMPUTE_FPS_
	OR_Globals::MessageHandler()->Debug("OR_Toolkit::MakeFPSLog", 
					"FPS computation is not enable.Use '#define _COMPUTE_FPS_' first.");
#else
	OR_Globals::PerformancesManager()->FPSLog();
#endif /* #ifdef _COMPUTE_FPS_ */
}

/* gestion des surfaces mathematiques **********************************************/
OR_I32 OR_Toolkit::AddMathsSurface()
{
	OR_Globals::MathSurfaceManager()->Select( 
		OR_Globals::MathSurfaceManager()->AddElement( new OR_MathSurface ) );
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::MathSurfaceManager()->GetElementSelected() );
	return OR_Globals::MathSurfaceManager()->GetNumElementSelected();
}

/* to handle the viewport *********************************************************/
void OR_Toolkit::Reshape(OR_I32 w, OR_I32 h)
{
	OR_Globals::ViewportManager()->Reshape(w, h);
//	OR_Globals::Portal_Renderer()->Reshape(60.f,OR_Float(w)/OR_Float(h));
}
	
OR_I32 OR_Toolkit::AddScreenViewPort(OR_I32 prio)
{
	OR_Globals::ViewportManager()->Select( OR_Globals::ViewportManager()->AddScreenViewPort(
		OR_Globals::CameraManager()->GetElementSelected(), prio ) );
	return OR_Globals::ViewportManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddFeedBackViewPort(OR_I32 prio)
{
	OR_Globals::ViewportManager()->Select( OR_Globals::ViewportManager()->AddFeedBackViewPort(
		OR_Globals::CameraManager()->GetElementSelected(), OR_Globals::TextureManager()->GetElementSelected(), prio ) );
	return OR_Globals::ViewportManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::SetViewPortDimensions(OR_Float ll_x, OR_Float ll_y, OR_Float width, OR_Float height)
{
	return OR_Globals::ViewportManager()->SetDimensions(ll_x, ll_y, width, height);
}

OR_I32 OR_Toolkit::SetViewportCamera()
{
	return OR_Globals::ViewportManager()->SetCamera(
		OR_Globals::CameraManager()->GetElementSelected() );
}

OR_I32 OR_Toolkit::SetViewportTexture()
{
	return OR_Globals::ViewportManager()->SetTexture(
		OR_Globals::TextureManager()->GetElementSelected() );
}

/* gestion des shader ************************************************************/
OR_I32 OR_Toolkit::AddFlatShader()
{
	return OR_Globals::ShaderManager()->AddFlatShader();
}

OR_I32 OR_Toolkit::AddSingleTextureMapShader(char* adresse)
{
	return OR_Globals::ShaderManager()->AddSingleTextureMapShader(adresse);
}

OR_I32 OR_Toolkit::AddReflexiveMapShader(char* adresse1, char* adresse2,
					      char* adresse3, char* adresse4,
					      char* adresse5, char* adresse6)
{
	OR_Globals::ShaderManager()->Select( 
		OR_Globals::ShaderManager()->AddReflexiveMapShader(adresse1, adresse2,
											   adresse3, adresse4,
											   adresse5, adresse6) );
	return OR_Globals::ShaderManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddCartoonShader(OR_I32 bordershader, OR_I32 middleshader)
{
	OR_Globals::ShaderManager()->Select( 
		OR_Globals::ShaderManager()->AddCartoonShader(bordershader, middleshader) );
	return OR_Globals::ShaderManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddBillboardShader(OR_I32 myshader)
{
	OR_Globals::ShaderManager()->Select( 
		OR_Globals::ShaderManager()->AddBillboardShader(myshader) );
	return OR_Globals::ShaderManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::LoadShaderTexture(char* adresse, OR_I32 num)
{
	return OR_Globals::ShaderManager()->LoadTexture(adresse, num);
}

/* to handle the textures ***************************************************/
OR_I32 OR_Toolkit::AddTexture(char* file, OR_Bool iscubemap, OR_I32 num, OR_Bool ismipmap)
{
	return OR_Globals::TextureManager()->AddTexture(file, iscubemap, num, ismipmap);
}

OR_I32 OR_Toolkit::LoadTextureBMP(char *file)
{
	return OR_Globals::TextureManager()->LoadImage(file);
}

/* gestion des gizmos **************************************************************/
OR_I32 OR_Toolkit::AddVectorGizmo(OR_Float vZ[3], OR_Float dim)
{
	OR_Globals::GizmoManager()->Select( 
		OR_Globals::GizmoManager()->AddVectorGizmo(vZ, dim) );
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::GizmoManager()->GetElementSelected() );
	return OR_Globals::GizmoManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddCubeGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3])
{
	OR_Globals::GizmoManager()->Select( 
		OR_Globals::GizmoManager()->AddCubeGizmo(vX, vY, vZ, dim) );
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::GizmoManager()->GetElementSelected() );
	return OR_Globals::GizmoManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddSphereGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3])
{
	OR_Globals::GizmoManager()->Select( 
		OR_Globals::GizmoManager()->AddSphereGizmo(vX, vY, vZ, dim) );
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::GizmoManager()->GetElementSelected() );
	return OR_Globals::GizmoManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddCylinderGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3])
{
	OR_Globals::GizmoManager()->Select( 
		OR_Globals::GizmoManager()->AddCylinderGizmo(vX, vY, vZ, dim) );
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::GizmoManager()->GetElementSelected() );
	return OR_Globals::GizmoManager()->GetNumElementSelected();
}

OR_I32 OR_Toolkit::AddSquareGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3])
{
	OR_Globals::GizmoManager()->Select( 
		OR_Globals::GizmoManager()->AddSquareGizmo(vX, vY, vZ, dim) );
	OR_Globals::HierarchyTree()->AddNode( OR_Globals::GizmoManager()->GetElementSelected() );
	return OR_Globals::GizmoManager()->GetNumElementSelected();
}

/* direct acces to orion3d data **********************************************/
OR_Object* OR_Toolkit::GetByName(char* name)
{
	OR_Object* tmp;
	/* serach in the different object manager */
	if ((tmp=OR_Globals::CameraManager()->GetElement(name))!=NULL) return tmp;
	if ((tmp=OR_Globals::MeshManager()->GetElement(name))!=NULL) return tmp;
	if ((tmp=OR_Globals::LightManager()->GetElement(name))!=NULL) return tmp;
	if ((tmp=OR_Globals::MathSurfaceManager()->GetElement(name))!=NULL) return tmp;
	if ((tmp=OR_Globals::GizmoManager()->GetElement(name))!=NULL) return tmp;
	return NULL;
}

OR_Object* OR_Toolkit::GetByName(OR_Elements manager, char* name)
{
	switch (manager)
	{
	case OR_CAMERA:
		return OR_Globals::CameraManager()->GetElement(name);
		break;
	case OR_MESH:
		return OR_Globals::MeshManager()->GetElement(name);
		break;
	case OR_LIGHT:
		return OR_Globals::LightManager()->GetElement(name);
		break;
	case OR_MATH_SURFACE:
		OR_Globals::MathSurfaceManager()->GetElement(name);
		break;
	case OR_GIZMO:
		OR_Globals::GizmoManager()->GetElement(name);
		break;
	default:
		return NULL;
		break;
	};
	return NULL; /* f%£^king warnings */
}

OR_Node* OR_Toolkit::GetNodeByName(const char* name)
{
	return OR_Globals::HierarchyTree()->GetNodeByName(name);
}


OR_Object* OR_Toolkit::GetSelectedObject(OR_Elements type)
{
	switch (type)
	{
	case OR_CAMERA:
		return OR_Globals::CameraManager()->GetElementSelected();
		break;
	case OR_MESH:
		return OR_Globals::MeshManager()->GetElementSelected();
		break;
	case OR_LIGHT:
		return OR_Globals::LightManager()->GetElementSelected();
		break;
	case OR_MATH_SURFACE:
		OR_Globals::MathSurfaceManager()->GetElementSelected();
		break;
	case OR_GIZMO:
		OR_Globals::GizmoManager()->GetElementSelected();
		break;
	default:
		return NULL;
		break;
	};
	return NULL; /* f%£^king warnings */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::AddObject
 *
 *  \param  pObj the object to add to hierarchy and to the manager.
 *  \return the ID of the object in the corresponding manager, or OR_ERROR if it was impossible.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Add the object both in the hierarchy and to the manager corresponding to the type of the object.
 */ 
/*------------------------------------------------------------------------------*/
OR_I32 OR_Toolkit::AddObject(OR_Object* pObj)
{
	OR_ASSERT( pObj!=NULL );

	OR_Globals::HierarchyTree()->AddNode(pObj);
	switch( pObj->GetType() )
	{
	case OR_MESH:
		return OR_Globals::MeshManager()->AddElement( (OR_Mesh*)pObj );
		break;
	case OR_LIGHT:
	case OR_LIGHT_Target_Spot: 
	case OR_LIGHT_Free_Spot:
	case OR_LIGHT_Target_Direct: 
	case OR_LIGHT_Free_Direct:
		return OR_Globals::LightManager()->AddElement( (OR_Light*)pObj );
		break;
	case OR_CAMERA: 
	case OR_CAMERA_Free: 
	case OR_CAMERA_Target:
		return OR_Globals::CameraManager()->AddElement( (OR_Camera*)pObj );
		break;
	case OR_GIZMO: 
	case OR_GIZMO_Sphere: 
	case OR_GIZMO_Cube: 
	case OR_GIZMO_Cylinder:
	case OR_GIZMO_Square: 
	case OR_GIZMO_Vector: 
	case OR_GIZMO_Point:
		return OR_Globals::GizmoManager()->AddElement( (OR_Gizmo*)pObj );
		break;	
	case OR_BONE:
		/** \todo create a bone manager */
//		OR_Globals::BoneManager()->AddElement( (OR_Bone*)pObj );
		break;
	case OR_SKIN:
		return OR_Globals::SkinManager()->AddElement( (OR_Skin*)pObj );
		break;
	case OR_MATH_SURFACE:
		return OR_Globals::MathSurfaceManager()->AddElement( (OR_MathSurface*) pObj );
		break;
	default:
		OR_Globals::MessageHandler()->Warning("OR_Toolkit::AddObject", "This kind of object is not supported.");
		break;
	}

	return OR_ERROR;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::AddShader
 *
 *  \param  pShader the shader to add to Orion3D shader manager.
 *  \return the ID of the shader in the manager.
 *  \author Gabriel Peyré 2001-10-29
 *
 *	Add the shader directly to the global shaders managers.
 */ 
/*------------------------------------------------------------------------------*/
OR_I32 OR_Toolkit::AddShader(OR_Shader* pShader)
{
	OR_ASSERT( pShader!=NULL );
	return OR_Globals::ShaderManager()->AddElement( pShader );;
}


/* to handle the lens flares ************************************************/
OR_I32 OR_Toolkit::AddInfiniteLensFlare()
{
	return OR_Globals::SpecialEffectManager()->AddElement( new OR_LensFlare_Infinite() );
}

OR_I32 OR_Toolkit::AddLocalLensFlare()
{
	return OR_Globals::SpecialEffectManager()->AddElement( new OR_LensFlare_Local() );
}

/* misc functions ***********************************************************/
void OR_Toolkit::MakeScreenShot()
{
	ilutGLScreenie();
}

void OR_Toolkit::Info(char* func, char* message, OR_I32 priority)
{
	OR_Globals::MessageHandler()->Info(func, message, priority);
}

void OR_Toolkit::Warning(char* func, char* message, OR_I32 priority)
{
	OR_Globals::MessageHandler()->Warning(func, message, priority);
}

void OR_Toolkit::FatalError(char* func, char* message, OR_I32 priority)
{
	OR_Globals::MessageHandler()->FatalError(func, message, priority);
}

void OR_Toolkit::Debug(char* func, char* message, OR_I32 priority)
{
	OR_Globals::MessageHandler()->Debug(func, message, priority);
}

/* to handle the log files ***************************************************/
OR_I32 OR_Toolkit::AddLog(char* LogName)
{
	return OR_Globals::LogManager()->AddLog(LogName);
}

OR_RETURN_CODE OR_Toolkit::LogAddString(char *error, ...)
{
	va_list argptr;
	
	va_start (argptr,error);
	return OR_Globals::LogManager()->AddvString(error, argptr);
	va_end (argptr);
	
}

OR_RETURN_CODE OR_Toolkit::LogAddLine(char *text)
{
	return OR_Globals::LogManager()->AddLine(text);
}
OR_RETURN_CODE OR_Toolkit::LogAddTimeDate()
{
	return OR_Globals::LogManager()->AddTimeDate();
}

OR_RETURN_CODE OR_Toolkit::LogAddOSVersion()
{
	return OR_Globals::LogManager()->AddOSVersion();
}

OR_RETURN_CODE OR_Toolkit::LogAddMemorySatus()
{
	return OR_Globals::LogManager()->AddMemorySatus();
}

OR_RETURN_CODE OR_Toolkit::LogAddOrion3DConfiguration()
{
	return OR_Globals::LogManager()->AddOrion3DConfiguration();
}

OR_RETURN_CODE OR_Toolkit::LogAddDriversConfiguration()
{
	return OR_Globals::LogManager()->AddDriversConfiguration();
}

OR_RETURN_CODE OR_Toolkit::LogAddIndent()
{
	return OR_Globals::LogManager()->AddIndent();
}

OR_RETURN_CODE OR_Toolkit::LogSubIndent()
{
	return OR_Globals::LogManager()->SubIndent();
}

OR_RETURN_CODE OR_Toolkit::LogSetIndent(OR_I32 indent)
{
	return OR_Globals::LogManager()->SetIndent(indent);
}

OR_I32 OR_Toolkit::LogGetIndent()
{
	return OR_Globals::LogManager()->GetIndent();
}


/* input/output procedures *******************************/

//-----------------------------------------------------------------------------
// Name: orion3d::PostReDisplay
/**
*	Call the PostRedisplay functioni of the input/output wrapper.
*/
///	\author Gabriel Peyré 2001-08-30
//-----------------------------------------------------------------------------
void OR_Toolkit::PostReDisplay()
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->PostReDisplay();
}

void OR_Toolkit::SetIdleFunc(void (*idle)(void))
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetIdleFunc(idle);
}

void OR_Toolkit::SetDisplayFunc(OR_Display_Func display)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetDisplayFunc(display);
}

void OR_Toolkit::SetReshapeFunc(OR_Reshape_Func reshape)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetReshapeFunc(reshape);
}

void OR_Toolkit::SetMouseClicFunc(OR_Mouseclic_Func mouseclic)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetMouseClicFunc(mouseclic);
}

void OR_Toolkit::SetMotionFunc(OR_Mouse_Func mouse)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetMotionFunc(mouse);
}

void OR_Toolkit::SetPassiveMotionFunc(OR_Passmotion_Func passmotion)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetPassiveMotionFunc(passmotion);
}

void OR_Toolkit::SetKeyPressedFunc(OR_KeyPressed_Func keyboard)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetKeyPressedFunc(keyboard);
}

void OR_Toolkit::SetKeyReleasedFunc(OR_KeyReleased_Func keyboard)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetKeyReleasedFunc(keyboard);
}

void OR_Toolkit::SetSpecialFunc(OR_Special_Func special)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetSpecialFunc(special);
}

void OR_Toolkit::SetInitFunc(OR_Init_Func init)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetInitFunc(init);
}

void OR_Toolkit::SetDestroyFunc(OR_Destroy_Func destroy)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetDestroyFunc(destroy);
}

OR_I32 OR_Toolkit::GetMousePosX()
{
	OR_ASSERT(pInputOutput_!=NULL);
	return pInputOutput_->GetMousePosX();
}

OR_I32 OR_Toolkit::GetMousePosY()
{
	OR_ASSERT(pInputOutput_!=NULL);
	return pInputOutput_->GetMousePosY();
}

void OR_Toolkit::SetMousePosX(OR_I32 pos)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetMousePosX(pos);
}

void OR_Toolkit::SetMousePosY(OR_I32 pos)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetMousePosY(pos);
}

OR_Bool OR_Toolkit::GetLeftButtonState()
{
	OR_ASSERT(pInputOutput_!=NULL);
	return pInputOutput_->GetLeftButtonState();
}

OR_Bool OR_Toolkit::GetRightButtonState()
{
	OR_ASSERT(pInputOutput_!=NULL);
	return pInputOutput_->GetRightButtonState();
}

void OR_Toolkit::SetLeftButtonState(OR_Bool state)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetLeftButtonState(state);
}

void OR_Toolkit::SetRightButtonState(OR_Bool state)
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->SetRightButtonState(state);
}

void OR_Toolkit::MainLoop()
{
	OR_ASSERT(pInputOutput_!=NULL);
	pInputOutput_->MainLoop();
}




/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::RemoveUnusedObjects
 *
 *  \author Gabriel Peyré 2001-09-24
 *
 *	Remove all unsed object from all \c OR_Object manager.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::RemoveUnusedObjects()
{
	this->GetCameraManager().RemoveUnusedObjects();
	this->GetLightManager().RemoveUnusedObjects();
	this->GetMeshManager().RemoveUnusedObjects();
	this->GetGizmoManager().RemoveUnusedObjects();
	this->GetSkinManager().RemoveUnusedObjects();
	this->GetMeshDataManager().RemoveUnusedObjects();
	this->GetShaderManager().RemoveUnusedObjects();
	this->GetTextureManager().RemoveUnusedObjects();
}

/*------------------------------------------------------------------------------ 
* Name : OR_Toolkit::DeleteAll 
* 
*  \author Antoine Bouthors 2002-01-05 
* 
* Remove all objects from all managers 
*------------------------------------------------------------------------------*/ 
void OR_Toolkit::DeleteAll() 
{ 
	this->GetCameraManager().DeleteAll(); 
	this->GetLightManager().DeleteAll(); 
	this->GetMeshManager().DeleteAll(); 
	this->GetGizmoManager().DeleteAll(); 
	this->GetSkinManager().DeleteAll(); 
	this->GetShaderManager().DeleteAll(); 
	this->GetTextureManager().DeleteAll(); 
} 


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::GetPhysicEntityManager
 *
 *  \return The main physic manager.
 *  \author Gabriel Peyré 2001-09-04
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntityManager& OR_Toolkit::GetPhysicEntityManager()
{
	OR_ASSERT(pPhysicManager_!=NULL);
	return *pPhysicManager_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::OpenConsole
 *
 *  \return Was the creation successful ?
 *  \author Gabriel Peyré 2001-09-04
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_Toolkit::OpenConsole()
{
	return ((OR_ShellConsoleText&) this->GetShellConsole()).OpenConsole();
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::ExecuteScript
 *
 *  \param address the adress of the script file.
 *	\param bVerbose print the command line that run the script to screen ?
 *  \author Gabriel Peyré 2001-09-04
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::ExecuteScript( const char* address, OR_Bool bVerbose )
{
	if( bVerbose )
	{
		OR_String cmdLine;
		cmdLine = OR_String("dofile(\"") + address + "\")\n";
		this->GetShellConsole().DoString( cmdLine );
	}
	else
		this->GetShellKernel().GetWrapperLUA().DoFile( address );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Object::BuildSonList
 *
 *  \param  SonList the liste of sons.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::BuildSonList(T_ShellObjectList& ShellSonList)
{
	/* add the hierarchy tree to the list */
	OR_ADD_SHELL_SON(ShellSonList, *OR_Globals::HierarchyTree(), OR_String("hierarchy_tree") );
	/* add the shader manager to the list */
	OR_ADD_SHELL_SON(ShellSonList, *OR_Globals::ShaderManager(), OR_String("shader_manager") );
	/* add the animation manager to the list */
	OR_ADD_SHELL_SON(ShellSonList, *OR_Globals::AnimationManager(), OR_String("animation_manager") );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::BuildFuncDeclList
 *
 *  \param  FuncDeclList the list of additional functions.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList)
{
	OR_ADD_SHELL_FUNC(FuncDeclList, RemoveUnusedObjects,	"Remove all unused objects.");
	OR_ADD_SHELL_FUNC(FuncDeclList, DeleteAll,				"Remove all objects.");

	OR_ADD_SHELL_FUNC(FuncDeclList, LogAddLine,				"Add a line to the log file.");

	OR_ADD_SHELL_FUNC(FuncDeclList, LoadFile,				"Load a KRD fle under the root.");;
	OR_ADD_SHELL_FUNC(FuncDeclList, SaveFile,				"Save the hierarchy in an ACT file.");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrepareAnimationExport,	"Set up serialization for animation export.");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrepareHierarchyExport,	"Set up serialization for hierarchy export.");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrepareShaderExport,	"Set up serialization for shader export.");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrepareSpecialEffectExport,	"Set up serialization for special fx export.");
	OR_ADD_SHELL_FUNC(FuncDeclList, PrepareAllExport,		"Set up serialization for exporting everything.");

	OR_ADD_SHELL_FUNC(FuncDeclList, Enable,					"Enable selected element of target manager.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Disable,				"Disable selected element of target manager.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Toggle,					"Toggle selected element of target manager.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Setf,					"Set target float-state variable.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Modf,					"Modify target float-state variable.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Select,					"Select given element in target manager.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Delete,					"Delete selected element in target manager.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Geti,					"Get target int-state variable.");
	OR_ADD_SHELL_FUNC(FuncDeclList, Getf,					"Get target float-state variable.");
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Enable
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Enable(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Enable, 1 );
	
	OR_SHELL_ACCESS_AND_USE( Enable, 1, String, state, 
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Enable( OR_Conversion::StringTo_OR_Types(state) );
		stack.ReturnValueI32( nRetVal );
	)
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Disable
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Disable(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Disable, 1 );
	
	OR_SHELL_ACCESS_AND_USE( Disable, 1, String, state, 
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Disable( OR_Conversion::StringTo_OR_Types(state) );
		stack.ReturnValueI32( nRetVal );
	)
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Toggle
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Toggle(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Toggle, 1 );
	
	OR_SHELL_ACCESS_AND_USE( Toggle, 1, String, state, 
		OR_Bool nRetVal = OR_ACCESS_THIS(OR_Toolkit).Toggle( OR_Conversion::StringTo_OR_Types(state) );
		stack.ReturnValueBool( nRetVal );
	)
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Setf
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Setf(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Setf, 2 );
	
	OR_SHELL_ACCESS_AND_USE( Setf, 1, String, state,
	OR_SHELL_ACCESS_AND_USE( Setf, 1, Float, val,
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Setf( OR_Conversion::StringTo_OR_Types(state), val );
		stack.ReturnValueI32( nRetVal );
	))
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Modf
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Modf(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Modf, 2 );
	
	OR_SHELL_ACCESS_AND_USE( Modf, 1, String, state,
	OR_SHELL_ACCESS_AND_USE( Modf, 1, Float, val,
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Modf( OR_Conversion::StringTo_OR_Types(state), val );
		stack.ReturnValueI32( nRetVal );
	))
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Select
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Select(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Select, 2 );
	
	OR_SHELL_ACCESS_AND_USE( Select, 1, String, state,
	OR_SHELL_ACCESS_AND_USE( Select, 1, I32, val,
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Select( OR_Conversion::StringTo_OR_Elements(state), val );
		stack.ReturnValueI32( nRetVal );
	))
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Delete
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Delete(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Delete, 2 );
	
	OR_SHELL_ACCESS_AND_USE( Delete, 1, String, state,
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Delete( OR_Conversion::StringTo_OR_Elements(state) );
		stack.ReturnValueI32( nRetVal );
	)
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Geti
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Geti(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Geti, 1 );
	
	OR_SHELL_ACCESS_AND_USE( Geti, 1, String, state,
		OR_I32 nRetVal = OR_ACCESS_THIS(OR_Toolkit).Geti( OR_Conversion::StringTo_OR_Types(state) );
		stack.ReturnValueI32( nRetVal );
	)
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernel::Getf
 *
 *  \param  stack the LUA stack.
 *  \author Gabriel Peyré 2001-11-20
 */ 
/*------------------------------------------------------------------------------*/
void OR_Toolkit::Getf(OR_ShellCallStack& stack)
{
	OR_INIT_SHELL_FUNC( Getf, 1 );
	
	OR_SHELL_ACCESS_AND_USE( Getf, 1, String, state,
		OR_Float rRetVal = OR_ACCESS_THIS(OR_Toolkit).Getf( OR_Conversion::StringTo_OR_Types(state) );
		stack.ReturnValueFloat( rRetVal );
	)
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

