/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Serializer.cpp
 *  \brief Implementation of class \c OR_Serializer
 *  \author Gabriel Peyré 2002/03/21
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Serializer.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Serializer.h"

using namespace OR;

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Serializer::OR_Serializer()
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Constructor.
 */ 
/*------------------------------------------------------------------------------*/
OR_Serializer::OR_Serializer()
:	bExportHierarchy_		( false ),
	bExportAnimation_		( false ),
	bExportShader_			( false ),
	bExportSpecialEffect_	( false ),
	bError_					( false ),
	pHierarchyStartNode_	( NULL ),
	pAnimationHierarchyRoot_( NULL ),
	pAnimationStartNode_	( NULL )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Serializer::~OR_Serializer()
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	AddCommentHere
 */ 
/*------------------------------------------------------------------------------*/
OR_Serializer::~OR_Serializer()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_Serializer::BuildFromFile( OR_File& file )
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	First import information about \b Orion3D, and check they are compatible with current version.
 *	Then import the boolean values of the class.
 *	Then import each part of the engine.
 *	At last, make a post import pass.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Serializer::BuildFromFile( OR_File& file )
{
	/* for the moment, no error has occured */
	bError_ = false;

	/* check orion3d version compatibility */
	OR_U32 nVersion;
	file >> nVersion;
	if( nVersion<OR_ORION3D_MinSupported_Version )
	{
		/* this version of the file is not supported */
		OR_Globals::MessageHandler()->Debug("OR_Serializer::BuildFromFile", 
			"The version of the file is not supported.\n  - Version of Orion3D.dll : %u\n  - Version of the file : %u.\n  - Minimum supported version %u", 
			OR_ORION3D_Version, OR_ORION3D_MinSupported_Version);
		bError_ = true;
		return;
	}
	if( nVersion>OR_ORION3D_Version)
	{
		/* this version of the file is not supported */
		OR_Globals::MessageHandler()->Debug("OR_Serializer::BuildFromFile", 
			"The version of the file is not supported.\n  - Version of Orion3D.dll : %u\n  - Version of the file : %u.\n  - Minimum supported version %u", 
			OR_ORION3D_Version, OR_ORION3D_MinSupported_Version);
		bError_ = true;
		return;
	}


	/* import the boolean values */
	file	>> bExportAnimation_
			>> bExportShader_
			>> bExportHierarchy_;

	/* import each part of the engine */
	if( bExportShader_ )
		file >> OR_Globals::ShaderManager();
	if( bExportHierarchy_ )
		file >> OR_Globals::HierarchyTree();
	if( bExportSpecialEffect_ )
		file >> OR_Globals::SpecialEffectManager();
	if( bExportAnimation_ )
		file >> OR_Globals::AnimationManager();
	/** \todo export portal and bsp
	if( bExportPortal_ )
		file << OR_Globals::Portal_Renderer();
	if( bExportBSP_ )
		file << OR_Globals::BSP_Renderer();
	*/
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_Serializer::BuildToFile( OR_File& file )
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	First export information about \b Orion3D.
 *	Then export the boolean values of the class.
 *	Then export each part of the engine.
 */ 
/*------------------------------------------------------------------------------*/
void OR_Serializer::BuildToFile( OR_File& file )
{
	/* export orion3d version for compatibility check */
	OR_U32 nVersion = OR_ORION3D_Version;
	file << nVersion;

	/* export the boolean values */
	file	<< bExportAnimation_
			<< bExportShader_
			<< bExportHierarchy_;

	/* export each part of the engine */
	if( bExportShader_ )
		file << OR_Globals::ShaderManager();
	if( bExportHierarchy_ )
	{
		if( pHierarchyStartNode_!=NULL )
			OR_Globals::HierarchyTree()->BuildToFile(file, pHierarchyStartNode_);
		else
			file << OR_Globals::HierarchyTree();
	}
	if( bExportSpecialEffect_ )
		file << OR_Globals::SpecialEffectManager();
	if( bExportAnimation_ )
	{
		if( pAnimationHierarchyRoot_!=NULL && pAnimationStartNode_!=NULL )
			OR_Globals::AnimationManager()->BuildToFile(file, pAnimationHierarchyRoot_, pAnimationStartNode_);
		else
			file << OR_Globals::AnimationManager();
	}
	/** \todo export portal and bsp
	if( bExportPortal_ )
		file << OR_Globals::Portal_Renderer();
	if( bExportBSP_ )
		file << OR_Globals::BSP_Renderer();
	*/
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

