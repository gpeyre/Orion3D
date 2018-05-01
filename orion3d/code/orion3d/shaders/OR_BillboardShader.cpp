/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_BillboardShader.cpp
 *  \brief Definition of class \c OR_BillboardShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_BillboardShader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_BillboardShader.h"
#include "OR_ShaderManager.h"

#ifndef OR_USE_INLINE
	#include "OR_BillboardShader.inl"
#endif

using namespace OR;


OR_BillboardShader::OR_BillboardShader(OR_Shader* myshader)
:	OR_Shader()
{
	pTargetShader_=myshader;
}

//-----------------------------------------------------------------------------
// Name: OR_BillboardShader::ProcessShader
/**
*   @param  object the object to render.
*
*	Render the object to screen.
*	\author  Gabriel Peyré 2001-08-10
*/
//-----------------------------------------------------------------------------
void OR_BillboardShader::ProcessShader(OR_Shadable& object)
{
	OR_ASSERT( pTargetShader_!=NULL );

	glPushMatrix();

	UnRotateModelViewMatrix();

	pTargetShader_->ProcessShader(object);

	/* reset rendering context ***********************************************/
	/* enable texture mapping */
	OR_Globals::Context()->SetDefault2DTexturingMode();
	/* re-set the culling */
	OR_Globals::Context()->SetDefaultCullingMode();

	glPopMatrix();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_BillboardShader::SetAmbientDiffuse
 *
 *  \param  color[4] the ambient and diffuse colors.
 *  \author Gabriel Peyré 2001-10-23
 *
 *	This function set up both ambient and diffuse color.
 *	It is used mainly by the particules system.
 *	For example, bilboard shader should overload it to set up the color of the
 *	base shader.
 */ 
/*------------------------------------------------------------------------------*/
void OR_BillboardShader::SetAmbientDiffuse(OR_Float color[4])
{
	OR_ASSERT( pTargetShader_!=NULL );
	pTargetShader_->SetAmbientDiffuse(color);
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_BillboardShader::BuildFromFile
 *
 *  \param  file the target file.
 *  \author Gabriel Peyré 2001-11-12
 *
 *	Note that the callback function is not exprted, so you'll need to reset it by your
 *	own !
 */ 
/*------------------------------------------------------------------------------*/
void OR_BillboardShader::BuildFromFile( OR_File& file )
{
	/* load the basic shader datas */
	OR_Shader::BuildFromFile(file);
	
	/* load the specific datas */
	file >> TargetShaderName_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_BillboardShader::BuildToFile
 *
 *  \param  file the target file.
 *  \author Gabriel Peyré 2001-11-12
 *
 *	Note that the callback function is not exprted, so you'll need to reset it by your
 *	own !
 */ 
/*------------------------------------------------------------------------------*/
void OR_BillboardShader::BuildToFile( OR_File& file )
{
	/* save the basic shader datas */
	OR_Shader::BuildToFile(file);

	/* save the specific datas */
	if( this->GetBaseShader()!=NULL )
		file << this->GetBaseShader()->GetName();
	else
	{
		OR_Globals::MessageHandler()->Warning("OR_BillboardShader::BuildToFile", "The bilboard shader has no target shader. Exporting default one.");
		file << OR_Globals::GetDefaultShader()->GetName();
	}
}

/*------------------------------------------------------------------------------
/** Name : OR_BillboardShader::PostExportPass
 *
 *  \author Gabriel Peyré 2001-11-12
 *
 *	if the shader has not already been set, try to fix the reference.
*/
/*------------------------------------------------------------------------------*/
void OR_BillboardShader::PostExportPass()
{
	/* if the shader has not already been set, try to fix the reference */
	OR_Shader* pRetrievedShader = OR_Globals::ShaderManager()->GetShaderByName(TargetShaderName_);
	this->SetBaseShader( *pRetrievedShader );

	/* free as much memory as possible */
	TargetShaderName_.clear();
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

