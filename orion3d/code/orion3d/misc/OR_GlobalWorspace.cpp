/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_GlobalWorspace.cpp
 *  \brief Implementation of class \c OR_GlobalWorspace
 *  \author Gabriel Peyré 2002/03/14
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_GlobalWorspace.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_GlobalWorspace.h"

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_GlobalWorspace::OR_GlobalWorspace();
 *
 *  \author Gabriel Peyré 2002/03/14
 *
 *	Constructor.
 */ 
/*------------------------------------------------------------------------------*/
OR_GlobalWorspace::OR_GlobalWorspace()
{
	#define INIT_NULL( classname ) p##classname##_ = NULL

	INIT_NULL( Context );
	INIT_NULL( MessageHandler );
	INIT_NULL( Data );
	INIT_NULL( AlphaPipeline ); 
	INIT_NULL( GLExtensionsManager );
	INIT_NULL( GizmoManager );
	INIT_NULL( MathSurfaceManager );
	INIT_NULL( CameraManager );
	INIT_NULL( MeshManager );
	INIT_NULL( SkinManager );
	INIT_NULL( LightManager );
	INIT_NULL( SpecialEffectManager );
	INIT_NULL( ShaderManager );
	INIT_NULL( ViewportManager );
	INIT_NULL( TextureManager );
	INIT_NULL( AnimationManager );
	INIT_NULL( LogManager );
	INIT_NULL( PerformancesManager );
	INIT_NULL( MeshDataManager );
	INIT_NULL( ShellKernelManager );
	INIT_NULL( Portal_Renderer );
	INIT_NULL( BSP_Renderer );
	INIT_NULL( HierarchyTree );
	INIT_NULL( ExceptionHandler );

	#undef INIT_NULL

	OR_ASSERT( this->CheckCorrectness() );
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Bool OR_GlobalWorspace::CheckCorrectness();
 *
 *  \author Gabriel Peyré 2002/03/14
 *	\return true if each pointer has been correctly set up.
 *
 *	Check if each pointer has been assigned.
 */ 
/*------------------------------------------------------------------------------*/
OR_Bool OR_GlobalWorspace::CheckCorrectness()
{
	#define CHECK_CORRECTNESS( classname )		\
	if( p##classname##_ == NULL) return false

	CHECK_CORRECTNESS( Context );
	CHECK_CORRECTNESS( MessageHandler );
	CHECK_CORRECTNESS( Data );
	CHECK_CORRECTNESS( AlphaPipeline ); 
	CHECK_CORRECTNESS( GLExtensionsManager );
	CHECK_CORRECTNESS( GizmoManager );
	CHECK_CORRECTNESS( MathSurfaceManager );
	CHECK_CORRECTNESS( CameraManager );
	CHECK_CORRECTNESS( MeshManager );
	CHECK_CORRECTNESS( SkinManager );
	CHECK_CORRECTNESS( LightManager );
	CHECK_CORRECTNESS( SpecialEffectManager );
	CHECK_CORRECTNESS( ShaderManager );
	CHECK_CORRECTNESS( ViewportManager );
	CHECK_CORRECTNESS( TextureManager );
	CHECK_CORRECTNESS( AnimationManager );
	CHECK_CORRECTNESS( LogManager );
	CHECK_CORRECTNESS( PerformancesManager );
	CHECK_CORRECTNESS( MeshDataManager );
	CHECK_CORRECTNESS( ShellKernelManager );
	CHECK_CORRECTNESS( Portal_Renderer );
	CHECK_CORRECTNESS( BSP_Renderer );
	CHECK_CORRECTNESS( HierarchyTree );
	CHECK_CORRECTNESS( ExceptionHandler );

	#undef CHECK_CORRECTNESS

	return true;
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

