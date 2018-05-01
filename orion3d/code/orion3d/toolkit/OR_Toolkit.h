
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Toolkit.h
 *  \brief definition of class \c OR_Toolkit
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Toolkit_h_
#define __OR_Toolkit_h_

/* the toolkit use the font wrapper */
#define _USE_FTGL_

#include "../configuration/OR_Config.h"

#include "../configuration/OR_Config.h"
#include "../hierarchy/OR_HierarchyTree.h"
#include "../objects/OR_Camera.h"
#include "../objects/OR_Mesh.h"
#include "../objects/OR_Skin.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_CubeGizmo.h"
#include "../objects/OR_SphereGizmo.h"
#include "../objects/OR_PointGizmo.h"
#include "../objects/OR_VectorGizmo.h"
#include "../objects/OR_SquareGizmo.h"
#include "../objects/OR_CylinderGizmo.h"
#include "../objects/OR_MeshDataManager.h"
#include "../objects/OR_Light.h"
#include "../objects/OR_LightManager.h"
#include "../objects/OR_MathSurface.h"
#include "../objects/OR_MathSurfaceManager.h"
#include "../physic/OR_Force_ABC.h"
#include "../bsp_portal/OR_Portals.h"
#include "../bsp_portal/OR_Q3BSP.h"
#include "../special_effects/OR_ParticuleSystem.h"
#include "../special_effects/OR_MetaEnv.h"
#include "../special_effects/OR_LensFlare.h"
#include "../special_effects/OR_SpecialEffectManager.h"
#include "../special_effects/OR_Fog.h"
#include "../input_output/OR_Viewport.h"
#include "../animation/OR_Animation.h"
#include "../animation/OR_AnimationManager.h"
#include "../utils/OR_PerformancesManager.h"
#include "../utils/OR_Log.h"
#include "../utils/OR_ExceptionHandler.h"
#include "../utils/OR_MessageHandler.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_MultiShader.h"
#include "../opengl/OR_GLExtensionsManager.h"
#include "../opengl/OR_Context.h"
#include "../input_output/OR_Renderer_ABC.h"
#include "../wrapper_font/OR_PixmapFont.h"
#include "../wrapper_font/OR_PixmapFont.h"
#include "../wrapper_font/OR_FontManager.h"
#include "../shell/OR_ShellKernelManager.h"
#include "../shell/OR_ShellObject_ABC.h"
#include "../shell/OR_ShellConsole_ABC.h"
#include "../shell/OR_ShellKernelManager.h"
#include "../shell/OR_ShellConsoleText.h"
#include "../utils/OR_Serializer.h"

namespace OR {

class OR_PhysicEntityManager;
class OR_InputOutput_ABC;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Toolkit
 *  \brief  encapsulates all 3D engine datas (managers, etc.)
 *  \author Gabriel Peyré 2001-08-31
 *
 *	This class has two main roles :
 *		- store all datas needed by the engine (mainly in managers).
 *		- propose wrapper functions to access important data of the engine.
 */ 
/*------------------------------------------------------------------------------*/

class OR_Toolkit: public OR_Renderer_ABC, public OR_ShellObject_ABC
{

public:
	
    //-------------------------------------------------------------------------
    /** \name constructor/destructor */
    //-------------------------------------------------------------------------
    //@{
	/** constructor */
	OR_Toolkit();
	/** destructor */
	~OR_Toolkit();
    //@}

    //-------------------------------------------------------------------------
    /** \name initialisation */
    //-------------------------------------------------------------------------
    //@{
	/** initialize everything (openg, openil, glut, ...).
		you should have to use it only if you don't use any Orion3D output wrapper, because
		Initialisation() calls InitGraphics() */
	void InitGraphics();
    //@}

    //-------------------------------------------------------------------------
    /** \name version control and error control */
    //-------------------------------------------------------------------------
    //@{
	/** get the current versio of Orion3D. usefull to test if the version of the user is 
		the right one.
		a simple test : if (MyOrion3D->GetVersion() < OR_ORION3D_Version) exit(0); */
	static OR_U32 GetVersion()
	{ return OR_ORION3D_Version; }
	/** get a comprehensive meaning of an error code
		\return The meaning of the error code */
	char* GetErrorInfo(OR_RETURN_CODE error);
    //@}

    //-------------------------------------------------------------------------
    /** \name File importation and exportation  */
    //-------------------------------------------------------------------------
    //@{
	OR_RETURN_CODE LoadFile(const char *name);
	OR_RETURN_CODE SaveFile(const char *name);

	OR_Serializer& GetSerializer();

	void PrepareAnimationExport();
	void PrepareHierarchyExport();
	void PrepareShaderExport();
	void PrepareSpecialEffectExport();
	void PrepareAllExport();
    //@}

    //-------------------------------------------------------------------------
    /** \name update and draw */
    //-------------------------------------------------------------------------
    //@{
	/** update recusivly all the object in the hierarchy and the physic
		@return none */
	void Update();	
	/** Draw the whole scene : called by each viewport, not by the main program : use Display()
		Overload of \c OR_Renderer_ABC method. */
	void RenderToViewport(OR_Viewport& Wiewport);
	/** Draw the scene using the differents viewports.
		Overload of \c OR_Renderer_ABC method.*/
	void RenderAllViewport();
    //@}

    //-------------------------------------------------------------------------
    /** \name state variables management */
    //-------------------------------------------------------------------------
    //@{
	/** enable a state variable of the engine environnement 
		@param state the state variable to enable 
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok*/
	OR_I32 Enable(OR_Types state);
	/** disable a state variable of the engine environnement 
		@param state the state variable to disable 
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Disable(OR_Types state);
	/** toggle on/off a state variable of the engine environnement 
		@param state the state variable to toggle 
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_Bool Toggle(OR_Types state);
    //@}

    //-------------------------------------------------------------------------
    /** \name parameters modifications */
    //-------------------------------------------------------------------------
    //@{
	/** set a OR_OR_Float parameter of the engine 
		@param name the parameter to set
		@param val the new value of the parameter
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Setf(OR_Types name, OR_Float val);
	/** set a OR_Float* parameter of the engine 
		@param name the parameter to set
		@param val the new value of the parameter
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Setfv(OR_Types name, OR_Float *val);
	/** set one component of a OR_Float[3] parameter of the engine 
		@param name the parameter to set
		@param comp the component [X|Y|Z|W] of the vector to set
		@param val the new value of the parameter
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Setf(OR_Types name, OR_Coord_RVBA comp, OR_Float val);
	/** modifiate [add/sub] a parameter 
		@param name the parameter to set
		@param val modification
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Modf(OR_Types name, OR_Float val);
    //@}

    //-------------------------------------------------------------------------
    /** \name selection methods */
    //-------------------------------------------------------------------------
    //@{
	/** select an element of a manager given its number 
		@param element type of the element to select 
		@param num number of the element to select
		@return OR_Unknown_Argument:the variable should not be use by this fonction 0:ok */
	OR_I32 Select(OR_Elements element, OR_I32 num);
    //@}

    //-------------------------------------------------------------------------
    /** \name destruction */
    //-------------------------------------------------------------------------
    //@{
	/** delete selected element of a manager 
		@param type type of the element to delete 
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Delete(OR_Elements type);
    //@}

    //-------------------------------------------------------------------------
    /** \name interogation */
    //-------------------------------------------------------------------------
    //@{
	/** get the value of an OR_I32 parameter of the engine 
		@param name name of the parameter to get the value
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_I32 Geti(OR_Types name);
	/** get the value of an OR_Float parameter of the engine 
		@param name name of the parameter to get the value
		@return OR_Unknown_Argument:the varible should not be use by this fonction 0:ok */
	OR_Float Getf(OR_Types name);
    //@}

    //-------------------------------------------------------------------------
    /** \name log and FPS query */
    //-------------------------------------------------------------------------
    //@{
	/** get the current Frame Per Second 
		@return numbre of frame per second */
	OR_Float GetFPS();
	/** to print a FPS report */
	void PrintFPSReport();
	/** to create a FPS log file */
	void MakeFPSLog();
    //@}

    //-------------------------------------------------------------------------
    /** \name OR_Object modification */
    //-------------------------------------------------------------------------
    //@{
	/** translate the selected element of a manager given the tranlation vector */
	OR_I32 Trans(OR_Elements type, OR_Float vect[3]);
	/** translate the selected element of a manager given the componnent of tranlation */
	OR_I32 Trans(OR_Elements type, OR_Coord_XYZW axe, OR_Float val);
	/** rotate on its axe the selected element of a manager */
	OR_I32 Rotate(OR_Elements type, OR_Float val);
	/** positionnate the selected element of a manager */
	OR_I32 Posit(OR_Elements type, OR_Float pos[3]);
	/** enable the draw of objects in the hierarchy */	
	void EnableDraw(OR_Elements type);
	/** disable the draw of objects in the hierarchy */	
	void DisableDraw(OR_Elements type);
	/** togle on/off the draw of objects in the hierarchy */	
	OR_Bool ToggleDraw(OR_Elements type);
    //@}

    //-------------------------------------------------------------------------
    /** \name camera managment */
    //-------------------------------------------------------------------------
    //@{
	/** add a new free camera */
	OR_I32 AddFreeCamera();
	/** add a new target camera */
	OR_I32 AddTargetCamera();
	/** rotate the camera on one of its own axes : for free and satellite, and target if axe=Z */
	OR_I32 RotateCamera(OR_Coord_XYZW axe, OR_Float angle);
	/** rotate the camera on one of the world's axes  : for free */
	OR_I32 RotateWorldCamera(OR_Coord_XYZW axe, OR_Float angle);
	/** translate the camera on one of its own axes given a component  : for free and satellite */
	OR_I32 TranslateCamera(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of its own axes given a vector  : for free and satellite */
	OR_I32 TranslateCamera(OR_Vector3D vect);
	/** translate the camera on one of the world axes given a component  : for free and satellite */
	OR_I32 TranslateWorldCamera(OR_Coord_XYZW axe, OR_Float val);
	/** translate the camera on one of the world axes given a vector  : for free and satellite */
	OR_I32 TranslateWorldCamera(OR_Vector3D vect);
	/** set the gizmo target : for target and satellite */
	OR_I32 SetCameraGizmoTarget();	
    //@}

    //-------------------------------------------------------------------------
    /** \name light management */
    //-------------------------------------------------------------------------
    //@{
	/** create a new free spot light */
	OR_I32 AddFreeSpotLight();
	/** create a new target spot light */
	OR_I32 AddTargetSpotLight();
	/** create a new free direct light */
	OR_I32 AddFreeDirectLight();
	/** create a new target direct light */
	OR_I32 AddTargetDirectLight();
	/** assgin a gizmo target */
	OR_I32 SetLightGizmoTarget();
    //@}

    //-------------------------------------------------------------------------
    /** \name maths surfaces management */
    //-------------------------------------------------------------------------
    //@{
	/** maths surface set up : add a new surface to the manager */
	OR_I32 AddMathsSurface();
    //@}

    //-------------------------------------------------------------------------
    /** \name viewport management */
    //-------------------------------------------------------------------------
    //@{
	/** reshape the windows : used for the portal renderer */
	void Reshape(OR_I32 w, OR_I32 h);
	/** add a new screen viewport using selected camera */
	OR_I32 AddScreenViewPort(OR_I32 prio);
	/** add a new feedback viewport using selected camera */
	OR_I32 AddFeedBackViewPort(OR_I32 prio);
	/** set the dimension of the selected wiewport */
	OR_I32 SetViewPortDimensions(OR_Float ll_x=0, OR_Float ll_y=0, OR_Float width=1, OR_Float height=1);
	/** set the camera used to reder the selected viewport */
	OR_I32 SetViewportCamera();
	/** set the texture used for feedback mode */
	OR_I32 SetViewportTexture();
    //@}

    //-------------------------------------------------------------------------
    /** \name shaders management */
    //-------------------------------------------------------------------------
    //@{
	/** add new flat shader */
	OR_I32 AddFlatShader();
	/** add new single texture shader */
	OR_I32 AddSingleTextureMapShader(char* adresse);
	/** add new reflexive shader */
	OR_I32 AddReflexiveMapShader(char* adresse1=NULL, char* adresse2=NULL,
						      char* adresse3=NULL, char* adresse4=NULL,
						      char* adresse5=NULL, char* adresse6=NULL);
	/** add new cartoon shader */
	OR_I32 AddCartoonShader(OR_I32 bordershader, OR_I32 middleshader);
	/** add new bilboard shader */
	OR_I32 AddBillboardShader(OR_I32 myshader);

	/** re-set the texture */
	OR_I32 LoadShaderTexture(char* adresse, OR_I32 num);
    //@}

    //-------------------------------------------------------------------------
    /** \name textures management */
    //-------------------------------------------------------------------------
    //@{
	/** add a new texture */
	OR_I32 AddTexture(char* file, OR_Bool iscubemap=false, OR_I32 num=0, OR_Bool ismipmap=false);
	/** load a bipmap from a file */
	OR_I32 LoadTextureBMP(char *File);
    //@}

    //-------------------------------------------------------------------------
    /** \name gizmos management */
    //-------------------------------------------------------------------------
    //@{
	/** create a vector gizmo from a file */
	OR_I32 AddVectorGizmo(OR_Float vZ[3], OR_Float dim=1);
	/** create a cubic gizmo from a file */
	OR_I32 AddCubeGizmo(OR_Float vX[3], OR_Float vY[3], 
					OR_Float vZ[3], OR_Float dim[3]);
	/** create a spheric gizmo from a file */
	OR_I32 AddSphereGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3]);
	/** create a cylindric gizmo from a file */
	OR_I32 AddCylinderGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3]);
	/** create a square gizmo from a file */
	OR_I32 AddSquareGizmo(OR_Float vX[3], OR_Float vY[3],
			 OR_Float vZ[3], OR_Float dim[3]);
    //@}

    //-------------------------------------------------------------------------
    /** \name lens flare management [TODO] */
    //-------------------------------------------------------------------------
    //@{
	/** add a new infinite lens flare */
	OR_I32 AddInfiniteLensFlare();
	/** add a new local lens flare */
	OR_I32 AddLocalLensFlare();
    //@}

	//-------------------------------------------------------------------------
    /** \name log files management */
    //-------------------------------------------------------------------------
    //@{
	/** create a new log */
	OR_I32 AddLog(char* LogName=OR_DEFAULT_LOG_NAME);
	/** add a string into the log file, using printf() usage */
	OR_RETURN_CODE LogAddString(char *error, ...);
	/** add a line of text into the log file */
	OR_RETURN_CODE LogAddLine(char *text);
	/** add date time into the log file */
	OR_RETURN_CODE LogAddTimeDate();
	/** add the OS version into the log file */
	OR_RETURN_CODE LogAddOSVersion();
	/** add the memory status into the log file */
	OR_RETURN_CODE LogAddMemorySatus();
	/** add the Orion3D configuration into the log file */
	OR_RETURN_CODE LogAddOrion3DConfiguration();
	/** add the drivers configuration into the log file */
	OR_RETURN_CODE LogAddDriversConfiguration();
	/** Increment the indent of the log file */
	OR_RETURN_CODE LogAddIndent();
	/** Decrement the indent of the log file */
	OR_RETURN_CODE LogSubIndent();
	/** Set the indent of the log file */
	OR_RETURN_CODE LogSetIndent(OR_I32 indent);
	/** \return the current indent index of the log file */
	OR_I32		   LogGetIndent();
    //@}

    //-------------------------------------------------------------------------
    /** \name access to Orion3D datas */
    //-------------------------------------------------------------------------
    //@{
	/** search for an object in the whole list of managers */
	OR_Object* GetByName(char* name);
	/** search for an object in a given manager */
	OR_Object* GetByName(OR_Elements manager, char* name);
	/** search for a node in the hierarchy tree given its name */
	OR_Node* GetNodeByName(const char* name);
	OR_Node* GetNodeByName(const OR_String& name)
	{ return GetNodeByName(name.const_val()); }

	static OR_CameraManager&		GetCameraManager();
	static OR_MeshManager&			GetMeshManager();
	static OR_SkinManager&			GetSkinManager();
	static OR_LightManager&			GetLightManager();
	static OR_SpecialEffectManager& GetSpecialEffectManager();
	static OR_MathSurfaceManager&	GetMathsSurfaceManager();
	static OR_GizmoManager&			GetGizmoManager();
	static OR_ShaderManager&		GetShaderManager();
	static OR_HierarchyTree&		GetHierarchyTree();
	static OR_AnimationManager&		GetAnimationManager();
	static OR_ExceptionHandler&		GetExceptionHandler();
	static OR_TextureManager&		GetTextureManager();
	static OR_Context&				GetContext();
	static OR_LogManager&			GetLogManager();
	static OR_MessageHandler&		GetMessageHandler();
	static OR_MeshDataManager&		GetMeshDataManager();
	static OR_ViewportManager&		GetViewportManager();	
	
	static OR_ShellKernelManager&	GetShellManager();
	OR_ShellKernel&					GetShellKernel();
	OR_ShellConsole_ABC&			GetShellConsole();
	
	OR_FontManager&					GetFontManager();
	OR_InputOutput_ABC*				GetInputOutput();
	OR_PhysicEntityManager&			GetPhysicEntityManager();
	
	/** get the selected object */
	OR_Object* GetSelectedObject(OR_Elements type);
	
	/** add an OR_Object directly to the hierarchy, and in the corresponding manager */
	OR_I32 AddObject(OR_Object* object);
	/** add a shader directly to the shader manager */
	OR_I32 AddShader(OR_Shader* pShader);

	void RemoveUnusedObjects();
	void DeleteAll();
    //@}

    //-------------------------------------------------------------------------
    /** \name messages and screenshots management */
    //-------------------------------------------------------------------------
    //@{
	/** takes a screenshot, and and saves the image to a Targa file with the filename format of screen%d.tga, 
	where %d is a number from 0 to 126. */
	void MakeScreenShot();
	/** send a info message concerning Orion3D */
	void Info(char* func, char* message, OR_I32 priority=1);
	/** send a warning message concerning Orion3D */
	void Warning(char* func, char* message, OR_I32 priority=1);
	/** send a fatal error message concerning Orion3D */
	void FatalError(char* func, char* message, OR_I32 priority=1);
	/** send a debug message concerning Orion3D */
	void Debug(char* func, char* message, OR_I32 priority=1);
    //@}

	
    //-------------------------------------------------------------------------
    /** \name input/output management */
    //-------------------------------------------------------------------------
    //@{
	void SetInputOutput(OR_InputOutput_ABC& inputoutput);

	void PostReDisplay();
	
	/** function to use when nothing to do */
	void SetIdleFunc(OR_Idle_Func idle);
	/** function to use to render the scene */
	void SetDisplayFunc(OR_Display_Func display);
	/** function to use when a resize occurs */
	void SetReshapeFunc(OR_Reshape_Func reshape);
	/** function to use when a mouse clic occurs */
	void SetMouseClicFunc(OR_Mouseclic_Func mouseclic);
	/** function to use when a mouse move occurs */
	void SetMotionFunc(OR_Mouse_Func mouse);
	/** function to use when a passive mouse move occur */
	void SetPassiveMotionFunc(OR_Passmotion_Func passmotion);
	/** function to use when a key is pressed */
	void SetKeyPressedFunc(OR_KeyPressed_Func  keypressed);
	/** function to use when a key is released */
	void SetKeyReleasedFunc(OR_KeyReleased_Func  keyreleased);
	/** function to use when a special key is pressed */
	void SetSpecialFunc(OR_Special_Func special);
	/** function to use for initialisation */
	void SetInitFunc(OR_Init_Func init);
	/** function to use when the window is destroyed */
	void SetDestroyFunc(OR_Destroy_Func destroy);
	/** function to use when a bsp is being loading */
	void SetBspLoadingFunc(OR_Bsp_Loading bsploading);

	/** get the X position of the mouse poOR_I32er */
	OR_I32 GetMousePosX();
	/** get the Y position of the mouse poOR_I32er */
	OR_I32 GetMousePosY();
	/** set the X position of the mouse poOR_I32er */
	void SetMousePosX(OR_I32 pos);
	/** set the Y position of the mouse poOR_I32er */
	void SetMousePosY(OR_I32 pos);
	/** get the state of the left mouse button */
	OR_Bool GetLeftButtonState();
	/** get the state of the right mouse button */
	OR_Bool GetRightButtonState();
	/** set the state of the left mouse button */
	void SetLeftButtonState(OR_Bool state);
	/** set the state of the right mouse button */
	void SetRightButtonState(OR_Bool state);

	/** an infinite loop */
	void MainLoop();
    //@}

    //-------------------------------------------------------------------------
    /** \name script management */
    //-------------------------------------------------------------------------
    //@{
	OR_Bool OpenConsole();
	void ExecuteScript( const char* address, OR_Bool bVerbose = true );
	//@}

	//-------------------------------------------------------------------------
    /** \name shell methods */
    //-------------------------------------------------------------------------
    //@{	
	virtual void BuildSonList(T_ShellObjectList& SonList);
	virtual void BuildFuncDeclList(T_ShellFuncDeclList& FuncDeclList);

	/** simply wrap statndard shell functions */
	OR_DECL_IMPL_SHELL_FUNC(RemoveUnusedObjects,	OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC(DeleteAll,				OR_Toolkit);

	OR_DECL_IMPL_SHELL_FUNC_1ARG(LogAddLine, String, OR_Toolkit);

	OR_DECL_IMPL_SHELL_FUNC_1ARG(SaveFile, String,		OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC_1ARG(LoadFile, String,		OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC(PrepareAnimationExport,		OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC(PrepareHierarchyExport,		OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC(PrepareShaderExport,		OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC(PrepareSpecialEffectExport,	OR_Toolkit);
	OR_DECL_IMPL_SHELL_FUNC(PrepareAllExport,			OR_Toolkit);


	OR_DECL_SHELL_FUNC(Enable, 1);
	OR_DECL_SHELL_FUNC(Disable, 1);
	OR_DECL_SHELL_FUNC(Toggle, 1);
	OR_DECL_SHELL_FUNC(Setf, 1);
	OR_DECL_SHELL_FUNC(Modf, 1);
	OR_DECL_SHELL_FUNC(Select, 1);
	OR_DECL_SHELL_FUNC(Delete, 1);
	OR_DECL_SHELL_FUNC(Geti, 1);
	OR_DECL_SHELL_FUNC(Getf, 1);

private:
	
	//-------------------------------------------------------------------------
	/** \name serialization management */
	//-------------------------------------------------------------------------
	//@{
	OR_Serializer Serializer_;
	//@}
	
    //-------------------------------------------------------------------------
    /** @name input/output management */
    //-------------------------------------------------------------------------
    //@{
	OR_InputOutput_ABC* pInputOutput_;
    //@}

	//-------------------------------------------------------------------------
    /** \name Physic management */
    //-------------------------------------------------------------------------
    //@{
	OR_PhysicEntityManager* pPhysicManager_;
    //@}

    //-------------------------------------------------------------------------
    /** \name Font management */
    //-------------------------------------------------------------------------
    //@{
	OR_FontManager* pFontManager_;
    //@}

    //-------------------------------------------------------------------------
    /** \name shell management */
    //-------------------------------------------------------------------------
    //@{	
	OR_ShellKernel*		 pKernel_;
	OR_ShellConsoleText* pConsole_;
    //@}
	
    //-------------------------------------------------------------------------
    /** @name for tracking */
    //-------------------------------------------------------------------------
    //@{
	/** for the tracking */
	OR_I32 CurrentArea;
    //@}

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Toolkit.inl"
#endif


#endif // __OR_Toolkit_h_

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
