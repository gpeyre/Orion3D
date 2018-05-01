/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_FlatShader.cpp
 *  \brief Definition of class \c OR_FlatShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_FlatShader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_FlatShader.h"

#ifndef OR_USE_INLINE
	#include "OR_FlatShader.inl"
#endif

using namespace OR;



//-----------------------------------------------------------------------------
// Name: OR_FlatShader::ProcessShader
/**
*   @param  object the object to render.
*
*	Render the object to screen.
*	\author  Gabriel Peyré 2001-08-10
*/
//-----------------------------------------------------------------------------
void OR_FlatShader::ProcessShader(OR_Shadable& object)
{
	/* intialize rendering context ******************************************/
	/* disable texture mapping */
	OR_Globals::Context()->Disable2DTexturing();
	/* Affectation des materiaux */
	this->SetUpColor();

	/* set the culling */
	OR_Globals::Context()->SetCullingMode(CullingMode);	
	/* set the blending */
	OR_Globals::Context()->SetBlendingMode( this->GetBlendingMode() );

	/* render the object *****************************************************/
	/* flush all datas */
	object.ProcessAllFaces();

	/* reset rendering context ***********************************************/
	/* enable texture mapping */
	OR_Globals::Context()->SetDefault2DTexturingMode();
	/* re-set the culling */
	OR_Globals::Context()->SetDefaultCullingMode();
	/* re-set the blending */
	OR_Globals::Context()->SetDefaultBlendingMode();
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

