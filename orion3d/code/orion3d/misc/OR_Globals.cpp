/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Globals.cpp
 *  \brief implementation for class OR_Globals
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Globals.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_Globals.h"


#include "../animation/OR_AnimationManager.h"
#include "../opengl/OR_Context.h"
#include "../utils/OR_MessageHandler.h"
#include "../utils/OR_Data.h"
#include "../utils/OR_ExceptionHandler.h"
#include "../utils/OR_String.h"
#include "../utils/OR_Log.h"
#include "../utils/OR_PerformancesManager.h"
#include "../utils/OR_File.h"
#include "../shaders/OR_AlphaPipeline.h"
#include "../shaders/OR_Texture.h"
#include "../shaders/OR_Shader.h"
#include "../shaders/OR_FlatShader.h"
#include "../shaders/OR_ShaderManager.h"
#include "../opengl/OR_GLExtensionsManager.h"
#include "../objects/OR_Gizmo.h"
#include "../objects/OR_PointGizmo.h"
#include "../objects/OR_Object.h"
#include "../objects/OR_Camera.h"
#include "../objects/OR_Mesh.h"
#include "../objects/OR_Skin.h"
#include "../objects/OR_Light.h"
#include "../objects/OR_MeshDataManager.h"
#include "../objects/OR_LightManager.h"
#include "../objects/OR_MathSurface.h"
#include "../objects/OR_MathSurfaceManager.h"
#include "../special_effects/OR_SpecialEffectManager.h"
#include "../input_output/OR_Viewport.h"
#include "../animation/OR_Animation.h"
#include "../hierarchy/OR_HierarchyTree.h"
#include "../input_output/OR_Renderer_ABC.h"
#include "../bsp_portal/OR_Portals.h"
#include "../bsp_portal/OR_Q3BSP.h"
#include "../shell/OR_ShellKernelManager.h"
#include "OR_GlobalWorspace.h"


#ifndef OR_USE_INLINE
	#include "OR_Globals.inl"
#endif

using namespace OR;

#define DEFINE_GLOBAL(c) OR_##c* OR_Globals::p##c##_ = NULL;
	
	DEFINE_GLOBAL(Context)
	DEFINE_GLOBAL(MessageHandler)
	DEFINE_GLOBAL(Data)
	DEFINE_GLOBAL(AlphaPipeline)
	DEFINE_GLOBAL(GLExtensionsManager)
	DEFINE_GLOBAL(GizmoManager)
	DEFINE_GLOBAL(MathSurfaceManager)
	DEFINE_GLOBAL(CameraManager)
	DEFINE_GLOBAL(MeshManager)
	DEFINE_GLOBAL(SkinManager)
	DEFINE_GLOBAL(LightManager)
	DEFINE_GLOBAL(MeshDataManager)

	DEFINE_GLOBAL(SpecialEffectManager)
	DEFINE_GLOBAL(ShaderManager)
	DEFINE_GLOBAL(ViewportManager)
	DEFINE_GLOBAL(TextureManager)
	DEFINE_GLOBAL(AnimationManager)
	DEFINE_GLOBAL(LogManager)
	DEFINE_GLOBAL(PerformancesManager)

	DEFINE_GLOBAL(HierarchyTree)
	DEFINE_GLOBAL(ExceptionHandler)

	DEFINE_GLOBAL(ShellKernelManager)
	
	DEFINE_GLOBAL(Portal_Renderer)
	DEFINE_GLOBAL(BSP_Renderer)

#undef DEFINE_GLOBAL

OR_Gizmo*	OR_Globals::pHierarchyRoot_			= NULL;
OR_Shader*	OR_Globals::pDefaultShader_			= NULL;
OR_String*	OR_Globals::pBaseFileAdress_		= NULL;
OR_U32*		OR_Globals::aIndexToNumShader_		= NULL;
OR_U32		OR_Globals::nIndexToNumShader_Size_	= 0;
OR_U32		OR_Globals::nNumObject_				= 0;
OR_Object**	OR_Globals::aObjectsList_			= NULL;
OR_U32		OR_Globals::nObjectsList_Size_		= 0;
OR_Bool		OR_Globals::aDraw_[OR_Draw_Size];

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals constructor
 *
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_Globals::OR_Globals()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals destructor
 *
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_Globals::~OR_Globals()
{
	/* NOTHING */
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::Initialize
 *
 *  \author Gabriel Peyré 2001-08-31
 *
 *	Create all global datas.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Globals::Initialize(OR_Renderer_ABC* pRenderer)
{
	/* create a gizmo to represent the root of the hierarchy */
	pHierarchyRoot_			= new OR_PointGizmo();
	pHierarchyRoot_->SetName("root_object");
	/* create a default shader */
	pDefaultShader_			= new OR_FlatShader();
	pDefaultShader_->SetName("default_shader");

	/* create the different managers */
	pLogManager_			= new OR_LogManager;
	pMessageHandler_		= new OR_MessageHandler;
	pExceptionHandler_		= new OR_ExceptionHandler;
	pContext_				= new OR_Context;
	pGLExtensionsManager_	= new OR_GLExtensionsManager;
	pData_					= new OR_Data;
	pAlphaPipeline_			= new OR_AlphaPipeline; 
	pGizmoManager_			= new OR_GizmoManager;
	pMathSurfaceManager_	= new OR_MathSurfaceManager;
	pCameraManager_			= new OR_CameraManager;
	pLightManager_			= new OR_LightManager;
	pSpecialEffectManager_	= new OR_SpecialEffectManager;
	pTextureManager_		= new OR_TextureManager;
	pShaderManager_			= new OR_ShaderManager;
	pMeshDataManager_		= new OR_MeshDataManager;
	pMeshManager_			= new OR_MeshManager;
	pSkinManager_			= new OR_SkinManager;
	pViewportManager_		= new OR_ViewportManager(*pRenderer);
	pAnimationManager_		= new OR_AnimationManager;
	pPerformancesManager_	= new OR_PerformancesManager;
	pPortal_Renderer_		= new OR_Portal_Renderer;
	pBSP_Renderer_			= new OR_BSP_Renderer;

	pShellKernelManager_	= new OR_ShellKernelManager;

	/* create the hierarchy at last */
	pHierarchyTree_			= new OR_HierarchyTree();

	/* initialize OR_Draw */
	for (OR_I32 i=0; i<OR_Draw_Size; i++)
		aDraw_[i]=true;

	pBaseFileAdress_=new OR_String("./");
	aIndexToNumShader_=NULL;
	nIndexToNumShader_Size_=0;
	nNumObject_=0;
	aObjectsList_=NULL;
	nObjectsList_Size_=0;

	/* add newly created objects to managers */
	OR_Globals::GizmoManager()->AddElement( pHierarchyRoot_ );
	OR_Globals::ShaderManager()->AddElement( pDefaultShader_ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::Destroy
 *
 *  \author Gabriel Peyré 2001-08-31
 *
 *	Delete all global datas.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Globals::Destroy()
{
	/* delete the hierarchy tree first, because it needs the managers */
	OR_DELETE(pHierarchyTree_);
	
	/* delete the different managers */
	OR_DELETE(pShellKernelManager_);
	
	OR_DELETE(pBSP_Renderer_);
	OR_DELETE(pPortal_Renderer_);
	OR_DELETE(pPerformancesManager_);
	OR_DELETE(pAnimationManager_);
	OR_DELETE(pSkinManager_);
	OR_DELETE(pMeshManager_);
	OR_DELETE(pMeshDataManager_);
	OR_DELETE(pShaderManager_);
	OR_DELETE(pTextureManager_);
	OR_DELETE(pViewportManager_);
	OR_DELETE(pSpecialEffectManager_);
	OR_DELETE(pLightManager_);
	OR_DELETE(pCameraManager_);
	OR_DELETE(pMathSurfaceManager_);
	OR_DELETE(pGizmoManager_);
	OR_DELETE(pAlphaPipeline_);
	OR_DELETE(pData_);
	OR_DELETE(pGLExtensionsManager_);
	OR_DELETE(pContext_);
	OR_DELETE(pLogManager_);
	OR_DELETE(pMessageHandler_);
	OR_DELETE(pExceptionHandler_);

	OR_DELETE(pBaseFileAdress_);
	OR_DELETE(aIndexToNumShader_);
	OR_DELETE(aObjectsList_);
	
	OR_DELETE(pMessageHandler_);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_Globals::GetGlobalWorskpace(OR_GlobalWorspace& gbwsp);
 *
 *  \author Gabriel Peyré 2002/03/14
 *
 *	Set up each pointer of the given worspace.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Globals::GetGlobalWorskpace(OR_GlobalWorspace& gbwsp)
{
	#define SET_POINTER(classname)				\
	OR_ASSERT( p##classname##_!=NULL );			\
	gbwsp.Set##classname( *p##classname##_ )

	SET_POINTER( Context );
	SET_POINTER( MessageHandler );
	SET_POINTER( Data );
	SET_POINTER( AlphaPipeline ); 
	SET_POINTER( GLExtensionsManager );
	SET_POINTER( GizmoManager );
	SET_POINTER( MathSurfaceManager );
	SET_POINTER( CameraManager );
	SET_POINTER( MeshManager );
	SET_POINTER( SkinManager );
	SET_POINTER( LightManager );
	SET_POINTER( SpecialEffectManager );
	SET_POINTER( ShaderManager );
	SET_POINTER( ViewportManager );
	SET_POINTER( TextureManager );
	SET_POINTER( AnimationManager );
	SET_POINTER( LogManager );
	SET_POINTER( PerformancesManager );
	SET_POINTER( MeshDataManager );
	SET_POINTER( ShellKernelManager );
	SET_POINTER( Portal_Renderer );
	SET_POINTER( BSP_Renderer );
	SET_POINTER( HierarchyTree );
	SET_POINTER( ExceptionHandler );

	#undef SET_POINTER

	OR_ASSERT( gbwsp.CheckCorrectness() );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_Globals::SwapGlobalWorskpace(OR_GlobalWorspace& new_gbwsp, OR_GlobalWorspace& old_gbwsp);
 *
 *  \author Gabriel Peyré 2002/03/14
 *
 *	Set up each pointer of \b Orion3D global variables with these provided by \c new_gbwsp.
 *	Save the previous one in \c old_gbwsp.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Globals::SwapGlobalWorskpace(OR_GlobalWorspace& new_gbwsp, OR_GlobalWorspace& old_gbwsp)
{
	OR_ASSERT( new_gbwsp.CheckCorrectness() );

	#define SWAP_POINTER(classname)					\
	OR_ASSERT( p##classname##_!=NULL );				\
	old_gbwsp.Set##classname( *p##classname##_ );	\
	p##classname##_ = new_gbwsp.Get##classname()

	SWAP_POINTER( Context );
	SWAP_POINTER( MessageHandler );
	SWAP_POINTER( Data );
	SWAP_POINTER( AlphaPipeline ); 
	SWAP_POINTER( GLExtensionsManager );
	SWAP_POINTER( GizmoManager );
	SWAP_POINTER( MathSurfaceManager );
	SWAP_POINTER( CameraManager );
	SWAP_POINTER( MeshManager );
	SWAP_POINTER( SkinManager );
	SWAP_POINTER( LightManager );
	SWAP_POINTER( SpecialEffectManager );
	SWAP_POINTER( ShaderManager );
	SWAP_POINTER( ViewportManager );
	SWAP_POINTER( TextureManager );
	SWAP_POINTER( AnimationManager );
	SWAP_POINTER( LogManager );
	SWAP_POINTER( PerformancesManager );
	SWAP_POINTER( MeshDataManager );
	SWAP_POINTER( ShellKernelManager );
	SWAP_POINTER( Portal_Renderer );
	SWAP_POINTER( BSP_Renderer );
	SWAP_POINTER( HierarchyTree );
	SWAP_POINTER( ExceptionHandler );

	#undef SWAP_POINTER

	OR_ASSERT( old_gbwsp.CheckCorrectness() );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetDefaultShader
 *
 *  \return The default shader.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_Shader* OR_Globals::GetDefaultShader()
{
	OR_ASSERT( pDefaultShader_!=NULL );
	return pDefaultShader_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetBaseFileAdress
 *
 *  \return Base adress for file path.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_String*	OR_Globals::GetBaseFileAdress()
{
	OR_ASSERT( pBaseFileAdress_!=NULL );
	return pBaseFileAdress_;
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

