/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Toolkit.inl
 *  \brief inlined methods for class OR_Toolkit
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Toolkit.h"

namespace OR {


/*------------------------------------------------------------------------------ 
* Name : OR_Toolkit::GetViewportManager 
* 
*  \return The main viewport manager
*  \author Antoine Bouthors 2002-01-02 
* 
* PUT YOUR COMMENTS HERE 
*------------------------------------------------------------------------------*/ 
OR_INLINE 
OR_ViewportManager& OR_Toolkit::GetViewportManager() 
{ 
	return *OR_Globals::ViewportManager(); 
} 


/*------------------------------------------------------------------------------
 * Name : OR_Toolkit::GetMeshDataManager
 *
 *  \return The main MeshData Manager
 *  \author Antoine Bouthors 2001-10-17
 *
 *------------------------------------------------------------------------------*/
OR_INLINE
OR_MeshDataManager& OR_Toolkit::GetMeshDataManager()
{
	return *OR_Globals::MeshDataManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetCameraManager
/**
*   @return The main camera manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_CameraManager& OR_Toolkit::GetCameraManager()
{
	return *OR_Globals::CameraManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetMeshManager
/**
*   @return The main mesh manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_MeshManager& OR_Toolkit::GetMeshManager()
{
	return *OR_Globals::MeshManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetLightManager
/**
*   @return The main light manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_LightManager& OR_Toolkit::GetLightManager()
{
	return *OR_Globals::LightManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetSpecialEffectManager
/**
*   @return The main special effect manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_SpecialEffectManager& OR_Toolkit::GetSpecialEffectManager()
{
	return *OR_Globals::SpecialEffectManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetMathsSurfaceManager
/**
*   @return The main mathematic surface manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_MathSurfaceManager& OR_Toolkit::GetMathsSurfaceManager()
{
	return *OR_Globals::MathSurfaceManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetGizmoManager
/**
*   @return The main gizmo manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_GizmoManager& OR_Toolkit::GetGizmoManager()
{
	return *OR_Globals::GizmoManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetShaderManager
/**
*   @return The main shader manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_ShaderManager& OR_Toolkit::GetShaderManager()
{
	return *OR_Globals::ShaderManager();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetHierarchyTree
/**
*   @return The scene graph
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_HierarchyTree& OR_Toolkit::GetHierarchyTree()
{
	return *OR_Globals::HierarchyTree();
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetAnimationManager
/**
*   @return The main animation manager
*
*
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_AnimationManager& OR_Toolkit::GetAnimationManager()
{
	return *OR_Globals::AnimationManager();
}




/*------------------------------------------------------------------------------*/
// Name : orion3d::GetTextureManager
/** 
 *
 *  \return The main texture manager
 *  \author Gabriel Peyré 2001-08-15
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_TextureManager& OR_Toolkit::GetTextureManager()
{
	return *OR_Globals::TextureManager();
}


/*------------------------------------------------------------------------------
/** Name : orion3d::GetContext
 *
 *  \return The main opengl context manager
 *  \author Antoine Bouthors 2001-08-20
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Context& OR_Toolkit::GetContext()
{
	return *OR_Globals::Context();
}


/*------------------------------------------------------------------------------*/
/** Name : orion3d::GetLogManager
 *
 *  \return The main log manager.
 *  \author Antoine Bouthors 2001-08-20
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_LogManager& OR_Toolkit::GetLogManager()
{
	return *OR_Globals::LogManager();
}


/*------------------------------------------------------------------------------
/** Name : orion3d::GetMessageHandler
 *
 *  \return The main message handler.
 *  \author Antoine Bouthors 2001-08-21
 */
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_MessageHandler& OR_Toolkit::GetMessageHandler()
{
	return *OR_Globals::MessageHandler();
}



//-----------------------------------------------------------------------------
// Name: OR_Toolkit::GetInputOutput
/**
*   @return The i/o manager
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
OR_InputOutput_ABC* OR_Toolkit::GetInputOutput()
{
	return pInputOutput_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::GetShellManager
 *
 *  \return the main shell kernel manager.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellKernelManager& OR_Toolkit::GetShellManager()
{
	return *OR_Globals::ShellKernelManager();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::GetShellKernel
 *
 *  \return the main kernel.
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellKernel&	 OR_Toolkit::GetShellKernel()
{
	OR_ASSERT( pKernel_!=NULL );
	return *pKernel_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::GetShellConsole
 *
 *  \return the main shell console.
 *  \author Gabriel Peyré 2001-11-27
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ShellConsole_ABC& OR_Toolkit::GetShellConsole()
{
	OR_ASSERT( pConsole_!=NULL );
	return *pConsole_;
}


//-----------------------------------------------------------------------------
// Name: OR_Toolkit::SetInputOutput
/**
*   @param  inputoutput The wrapper used for input/output
*/
///	\author Gabriel Peyré 2001-08-30
//-----------------------------------------------------------------------------
OR_INLINE
void OR_Toolkit::SetInputOutput(OR_InputOutput_ABC& inputoutput)
{
	pInputOutput_ = &inputoutput;
}




//-----------------------------------------------------------------------------
// Name: orion3d::GetExceptionHandler
/**
*   @return The main exception handler.
*/
///	\author Gabriel Peyré 2001-08-30
//-----------------------------------------------------------------------------
OR_INLINE
OR_ExceptionHandler& OR_Toolkit::GetExceptionHandler()
{
	return *OR_Globals::ExceptionHandler();
}


// Name: OR_Toolkit::GetSkinManager 
/** 
*   @return The main Skin manager 
* 
*/ 
/// \author Antoine Bouthors 2001-10-08 
//----------------------------------------------------------------------------- 
OR_INLINE 
OR_SkinManager& OR_Toolkit::GetSkinManager() 
{ 
       return *OR_Globals::SkinManager(); 
} 
   


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Toolkit::GetFontManager
 *
 *  \return the main font manager.
 *  \author Gabriel Peyré 2001-11-14
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_FontManager& OR_Toolkit::GetFontManager()
{
	OR_ASSERT( pFontManager_!=NULL );
	return *pFontManager_;
}



} // End namespace OR

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

