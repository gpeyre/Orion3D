/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_GlobalWorspace.h
 *  \brief Definition of class \c OR_GlobalWorspace
 *  \author Gabriel Peyré 2002/03/14
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_GlobalWorspace_h_
#define __OR_GlobalWorspace_h_


#include "../configuration/OR_Config.h"


namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_GlobalWorspace
 *  \brief  AddCommentHere
 *  \author Gabriel Peyré 2001-11-17
 *	
 *	This class should be used to communicate with class \c OR_Globals.
 *	It should be used only when an application needs to handle multiple 
 *	3D engines (for example, if one needs multiple hierachy tree).
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_GlobalWorspace
{

public:

    //-------------------------------------------------------------------------
    /** \name Constructor and destructor */
    //-------------------------------------------------------------------------
    //@{
	OR_GlobalWorspace();
	//@}

    //-------------------------------------------------------------------------
    /** \name Helper methods */
    //-------------------------------------------------------------------------
    //@{
    OR_Bool CheckCorrectness();
    //@}
    
	//-------------------------------------------------------------------------
	/** \name  accessors */
	//-------------------------------------------------------------------------
	//@{
	#define DECL_ACCESSOR(classname)			\
	OR_##classname* Get##classname()			\
	{ return p##classname##_; }					\
	void Set##classname(OR_##classname& elt)	\
	{ p##classname##_ = &elt; }

	DECL_ACCESSOR( Context );
	DECL_ACCESSOR( MessageHandler );
	DECL_ACCESSOR( Data );
	DECL_ACCESSOR( AlphaPipeline ); 
	DECL_ACCESSOR( GLExtensionsManager );
	DECL_ACCESSOR( GizmoManager );
	DECL_ACCESSOR( MathSurfaceManager );
	DECL_ACCESSOR( CameraManager );
	DECL_ACCESSOR( MeshManager );
	DECL_ACCESSOR( SkinManager );
	DECL_ACCESSOR( LightManager );
	DECL_ACCESSOR( SpecialEffectManager );
	DECL_ACCESSOR( ShaderManager );
	DECL_ACCESSOR( ViewportManager );
	DECL_ACCESSOR( TextureManager );
	DECL_ACCESSOR( AnimationManager );
	DECL_ACCESSOR( LogManager );
	DECL_ACCESSOR( PerformancesManager );
	DECL_ACCESSOR( MeshDataManager );
	DECL_ACCESSOR( ShellKernelManager );
	DECL_ACCESSOR( Portal_Renderer );
	DECL_ACCESSOR( BSP_Renderer );
	DECL_ACCESSOR( HierarchyTree );
	DECL_ACCESSOR( ExceptionHandler );

	#undef DECL_ACCESSOR
	//@}


private:

	OR_Context*					pContext_;
	OR_MessageHandler*			pMessageHandler_;
	OR_Data*					pData_;
	OR_AlphaPipeline*			pAlphaPipeline_; 
	OR_GLExtensionsManager*		pGLExtensionsManager_;
	OR_GizmoManager*			pGizmoManager_;
	OR_MathSurfaceManager*		pMathSurfaceManager_;
	OR_CameraManager*			pCameraManager_;
	OR_MeshManager*				pMeshManager_;
	OR_SkinManager*				pSkinManager_;
	OR_LightManager*			pLightManager_;
	OR_SpecialEffectManager*	pSpecialEffectManager_;
	OR_ShaderManager*			pShaderManager_;
	OR_ViewportManager*			pViewportManager_;
	OR_TextureManager*			pTextureManager_;
	OR_AnimationManager*		pAnimationManager_;
	OR_LogManager*				pLogManager_;
	OR_PerformancesManager*		pPerformancesManager_;
	OR_MeshDataManager*			pMeshDataManager_;
	OR_ShellKernelManager*		pShellKernelManager_;
	OR_Portal_Renderer*			pPortal_Renderer_;
	OR_BSP_Renderer*			pBSP_Renderer_;
	OR_HierarchyTree*			pHierarchyTree_;
	OR_ExceptionHandler*		pExceptionHandler_;
	
};

} // End namespace OR

#endif // __OR_GlobalWorspace_h_

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

