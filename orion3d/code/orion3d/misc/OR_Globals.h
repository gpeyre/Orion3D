
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Globals.h
 *  \brief definition of class OR_Global
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Globals_h_
#define __OR_Globals_h_

#include "../configuration/OR_Config.h"

namespace OR {

class OR_Context;
class OR_MessageHandler;
class OR_Data;
class OR_AlphaPipeline;
class OR_GLExtensionsManager;
class OR_GizmoManager;
class OR_MathSurfaceManager;
class OR_CameraManager;
class OR_MeshManager;
class OR_SkinManager;
class OR_LightManager;
class OR_SpecialEffectManager;
class OR_ShaderManager;
class OR_ViewportManager;
class OR_TextureManager;
class OR_AnimationManager;
class OR_LogManager;
class OR_PerformancesManager;
class OR_HierarchyTree;
class OR_ExceptionHandler;
class OR_Gizmo;
class OR_String;
class OR_Object;
class OR_Renderer_ABC;
class OR_Portal_Renderer;
class OR_BSP_Renderer;
class OR_MeshDataManager;
class OR_MathSurfaceManager;
class OR_File;
class OR_Node;
class OR_ShellKernelManager;
class OR_GlobalWorspace;
class OR_Shader;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Globals
 *  \brief  A class that store all global variables in Orion3D
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Globals
{

public:

    //-------------------------------------------------------------------------
    /** \name constructor & destructor */
    //-------------------------------------------------------------------------
    //@{
    OR_Globals();
    virtual ~OR_Globals();
    //@}

    //-------------------------------------------------------------------------
    /** \name initialisation & destruction */
    //-------------------------------------------------------------------------
    //@{
	static void Initialize(OR_Renderer_ABC* pRenderer);
	static void Destroy();
    //@}

    //-------------------------------------------------------------------------
    /** \name manager & handler access */
    //-------------------------------------------------------------------------
    //@{
	static OR_Context*				Context();
	static OR_MessageHandler*		MessageHandler();
	static OR_Data*					Data();
	static OR_AlphaPipeline*		AlphaPipeline();
	static OR_GLExtensionsManager*	GLExtensionsManager();
	static OR_GizmoManager*			GizmoManager();
	static OR_MathSurfaceManager*	MathSurfaceManager();
	static OR_CameraManager*		CameraManager();
	static OR_MeshManager*			MeshManager();
	static OR_SkinManager*			SkinManager();
	static OR_LightManager*			LightManager();
	static OR_MeshDataManager*		MeshDataManager();

	static OR_SpecialEffectManager*	SpecialEffectManager();
	static OR_ShaderManager*		ShaderManager();
	static OR_ViewportManager*		ViewportManager();
	static OR_TextureManager*		TextureManager();
	static OR_AnimationManager*		AnimationManager();
	static OR_LogManager*			LogManager();
	static OR_PerformancesManager*	PerformancesManager();

	static OR_HierarchyTree*		HierarchyTree();
	static OR_ExceptionHandler*		ExceptionHandler();

	static OR_Portal_Renderer*		Portal_Renderer();
	static OR_BSP_Renderer*			BSP_Renderer();

	static OR_ShellKernelManager*	ShellKernelManager();
	//@}


    //-------------------------------------------------------------------------
    /** \name Global variable access */
    //-------------------------------------------------------------------------
    //@{
	static OR_Gizmo*				GetHierarchyRoot();
	static OR_Shader*				GetDefaultShader();
	static OR_String*				GetBaseFileAdress();
    //@}


	//-------------------------------------------------------------------------
    /** \name Importation helpers */
    //-------------------------------------------------------------------------
    //@{
	static OR_U32		GetIndexToNumShader(OR_U32 nIndex);
	static void			SetIndexToNumShader(OR_U32 nIndex, OR_U32 nNumShader);
	static void			ResizeIndexToNumShader(OR_U32 nSize);
	static OR_U32		GetNbrShaderImported();

	static OR_Object*	GetImportedObject(OR_U32 nNum);
	static void			SetImportedObject(OR_U32 nNum, OR_Object* pObj);
	static void			ResizeImportedObject(OR_U32 nSize);
	static OR_U32		GetNbrObjectImported();

	static OR_U32		GetCurrentObjectNum();
	static void			SetCurrentObjectNum(OR_U32 nNum);
    //@}

    //-------------------------------------------------------------------------
    /** \name Object draw on/off flags state variables */
    //-------------------------------------------------------------------------
    //@{
	static OR_Bool GetDrawObject(OR_U32 nNum);
	static void    SetDrawObject(OR_U32 nNum, OR_Bool bNeedsDraw);
    //@}

    //-------------------------------------------------------------------------
    /** \name Context swapping */
    //-------------------------------------------------------------------------
    //@{
    static void GetGlobalWorskpace(OR_GlobalWorspace& gbwsp);
	static void SwapGlobalWorskpace(OR_GlobalWorspace& new_gbwsp, OR_GlobalWorspace& old_gbwsp);
    //@}
    
private:

	//-------------------------------------------------------------------------
	/** \name Global Orion3D objects */
	//-------------------------------------------------------------------------
	//@{
	/** a wrapper to modify opengl states-variables */
	static OR_Context* pContext_;
	/** to print and handle error/debug/warning/info messages */
	static OR_MessageHandler* pMessageHandler_;
	/** various data (default datas, 3d simple primitives ...). */
	static OR_Data* pData_;
	/** the global alpha pipeline. */
	static OR_AlphaPipeline* pAlphaPipeline_; 
	/** the global extension manager. */
	static OR_GLExtensionsManager* pGLExtensionsManager_;
	//@}
	
	//-------------------------------------------------------------------------
	/** \name OR_Objects managers */
	//-------------------------------------------------------------------------
	//@{
	/** the main gizmo manager */
	static OR_GizmoManager*			pGizmoManager_;
	/** the main MathsSurface manager */
	static OR_MathSurfaceManager*	pMathSurfaceManager_;
	/** the main Camera manager */
	static OR_CameraManager*		pCameraManager_;
	/** the main Mesh manager */
	static OR_MeshManager*			pMeshManager_;
	/** the main Skin manager */
	static OR_SkinManager*			pSkinManager_;
	/** the main Light manager */
	static OR_LightManager*			pLightManager_;
	//@}
	
	//-------------------------------------------------------------------------
	/** \name special effects managers */
	//-------------------------------------------------------------------------
	//@{
	/** the main SpecSpecialEffectManager */
	static OR_SpecialEffectManager*	pSpecialEffectManager_;
	//@}
	//-------------------------------------------------------------------------
	/** \name misc managers */
	//-------------------------------------------------------------------------
	//@{
	/** the main Shader manager */
	static OR_ShaderManager*		pShaderManager_;
	/** to handle different viewport */
	static OR_ViewportManager*		pViewportManager_;
	/** to handle different textures */
	static OR_TextureManager*		pTextureManager_;
	/** to handle different animations */
	static OR_AnimationManager*		pAnimationManager_;
	/** to handle differents log files */
	static OR_LogManager*			pLogManager_;
	/** to handle performances computations */
	static OR_PerformancesManager*	pPerformancesManager_;
	/** to handle mesh data */
	static OR_MeshDataManager*		pMeshDataManager_;
	/** to handle shell kernels */
	static OR_ShellKernelManager*	pShellKernelManager_;
	//@}

	//-------------------------------------------------------------------------
    /** @name static geometry */
    //-------------------------------------------------------------------------
    //@{
	/** the engine that render the static geometry using portals algortithm*/
	static OR_Portal_Renderer *pPortal_Renderer_;
	/** the engine that render the static geometry using pvs algortithm */
	static OR_BSP_Renderer *pBSP_Renderer_;
    //@}
	
	//-------------------------------------------------------------------------
	/** @name scene graph */
	//-------------------------------------------------------------------------
	//@{
	/** the HierarchyTree containing all the objects */
	static OR_HierarchyTree*		pHierarchyTree_;
	//@}
	
	//-------------------------------------------------------------------------
	/** \name Global handler */
	//-------------------------------------------------------------------------
	//@{
	static OR_ExceptionHandler*		pExceptionHandler_;
	//@}

	//-------------------------------------------------------------------------
	/** \name Global variable for the hierarchy */
	//-------------------------------------------------------------------------
	//@{
	/** root node for the hierarchy tree */
	static OR_Gizmo*				pHierarchyRoot_;
	/** default shader for mesh forgetting to define a shader ... */
	static OR_Shader*				pDefaultShader_;
	//@}
	
	//-------------------------------------------------------------------------
	/** \name global variables for import of krd file  */
	//-------------------------------------------------------------------------
	//@{
	/** the path to the krd file */
	static OR_String* pBaseFileAdress_;
	/** list of the shaders numbers */
	static OR_U32* aIndexToNumShader_;
	/** size of the list */
	static OR_U32 nIndexToNumShader_Size_;
	/** the number of the current object */
	static OR_U32 nNumObject_;
	/** the list of the OR_Object that have been loaded */
	static OR_Object** aObjectsList_;
	/** size of the list */
	static OR_U32 nObjectsList_Size_;
	//@}

	//-------------------------------------------------------------------------
	/** \name state variables to draw the different kind of objects */
	//-------------------------------------------------------------------------
	//@{
	#define OR_Draw_Size 80
	/** state variables to draw the different kind of objects */
	static OR_Bool aDraw_[OR_Draw_Size];
	//@}

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_Globals.inl"
#endif


#endif // __OR_Globals_h_

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

