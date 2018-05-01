/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Globals.inl
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Globals.h"

namespace OR {

#define DEFINE_GLOBAL(c)						\
	OR_INLINE OR_##c* OR_Globals::c()			\
	{ OR_ASSERT(p##c##_!=NULL); return p##c##_; }	\

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

	DEFINE_GLOBAL(Portal_Renderer)
	DEFINE_GLOBAL(BSP_Renderer)

	DEFINE_GLOBAL(ShellKernelManager)

#undef DEFINE_GLOBAL


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetHierarchyRoot
 *
 *  \return The root of the hierarchy.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Gizmo* OR_Globals::GetHierarchyRoot()
{
	OR_ASSERT( pHierarchyRoot_!=NULL );
	return pHierarchyRoot_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetIndexToNumShader		
 *
 *  \param  nIndex The index of the shader (number of shader being exported).
 *  \return Orion3D ID of the shader in the shader manager.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Globals::GetIndexToNumShader(OR_U32 nIndex)
{
	OR_ASSERT( nIndex<nIndexToNumShader_Size_ );
	return aIndexToNumShader_[nIndex];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::SetIndexToNumShader			
 *
 *  \param  nIndex The index of the shader (number of shader being exported).
 *	\param	nNumShader Orion3D ID of the shader in the shader manager.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Globals::SetIndexToNumShader(OR_U32 nIndex, OR_U32 nNumShader)
{
	OR_ASSERT( nIndex<nIndexToNumShader_Size_ );
	aIndexToNumShader_[nIndex] = nNumShader;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::ResizeIndexToNumShader			
 *
 *  \param  nSize The number of shaders being exported.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Globals::ResizeIndexToNumShader(OR_U32 nSize)
{
	OR_DELETEARRAY( aIndexToNumShader_ );
	aIndexToNumShader_ = new OR_U32[nSize];
	nIndexToNumShader_Size_ = nSize;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetNbrShaderImported		
 *
 *  \return The number of shaders that are imported.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Globals::GetNbrShaderImported()
{
	return nIndexToNumShader_Size_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetImportedObject
 *
 *  \param  nNum Number of the object that has been imported.
 *  \return The object of the given number.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Object*	OR_Globals::GetImportedObject(OR_U32 nNum)
{
	OR_ASSERT( nNum<nObjectsList_Size_ );
	return aObjectsList_[nNum];
}	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::SetImportedObject			
 *
 *  \param  nNum Number of the object being imported.
 *  \param  pObj The object being imported.
 *  \author Gabriel Peyré 2001-08-31
 *
 *	This book-keeps the objects being imported, so that they are easyly retrieved.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Globals::SetImportedObject(OR_U32 nNum, OR_Object* pObj)
{
	OR_ASSERT( nNum<nObjectsList_Size_ );
	aObjectsList_[nNum] = pObj;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::ResizeImportedObject			
 *
 *  \param  nSize The number of object being imported.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Globals::ResizeImportedObject(OR_U32 nSize)
{
	OR_DELETEARRAY( aObjectsList_ );
	aObjectsList_ = new OR_Object*[nSize];
	nObjectsList_Size_ = nSize;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetNbrObjectImported		
 *
 *  \return The number of objects that are being exported.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Globals::GetNbrObjectImported()
{
	return nObjectsList_Size_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetCurrentObjectNum		
 *
 *  \return The object being currently imported.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Globals::GetCurrentObjectNum()
{
	return nNumObject_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::SetCurrentObjectNum			
 *
 *  \param  nNum The object being currently imported.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Globals::SetCurrentObjectNum(OR_U32 nNum)
{
	nNumObject_ = nNum;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::GetDrawObject
 *
 *  \param  nNum The ID (class OR_Elements) of the class.
 *  \return True if we needs to draw this class, false otherwise.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Bool OR_Globals::GetDrawObject(OR_U32 nNum)
{
	OR_ASSERT( nNum<OR_Draw_Size );
	return aDraw_[nNum];
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Globals::SetDrawObject
 *
 *  \param  nNum The ID (class OR_Elements) of the class.
 *  \param  bNeedsDraw True if we needs to draw this class, false otherwise.
 *  \author Gabriel Peyré 2001-08-31
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Globals::SetDrawObject(OR_U32 nNum, OR_Bool bNeedsDraw)
{
	OR_ASSERT( nNum<OR_Draw_Size );
	aDraw_[nNum] = bNeedsDraw;
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

