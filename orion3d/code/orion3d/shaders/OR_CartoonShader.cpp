/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CartoonShader.cpp
 *  \brief Definition of class \c OR_CartoonShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_CartoonShader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_CartoonShader.h"
#include "Or_ShaderManager.h"

#ifndef OR_USE_INLINE
	    #include "OR_CartoonShader.inl"
#endif

using namespace OR;

#define OR_DEFAULT_CARTOON_SHADER_BORDER_WIDTH 8

OR_CartoonShader::OR_CartoonShader(OR_Shader* bordershader,
				 OR_Shader* middleshader)
:	OR_Shader(),
	BorderShader	( bordershader ),
	MiddleShader	( MiddleShader ),
	BorderWidth		( OR_DEFAULT_CARTOON_SHADER_BORDER_WIDTH )
{
	/* NOTHING */
}

void OR_CartoonShader::SetBorderWidth(OR_I32 val)
{
	BorderWidth = val;
}

//-----------------------------------------------------------------------------
// Name: OR_Shader::ProcessShader
/**
*   @param  object the object to render.
*	\todo re-write all that stuff
*
*	Render the object to screen.
*	\author  Gabriel Peyré 2001-08-10
*/
//-----------------------------------------------------------------------------
void OR_CartoonShader::ProcessShader(OR_Shadable& object)
{
	/* first pass ***********************************************************/	
	OR_Globals::Context()->SetCullingMode(OR_Culling_Front);
	BorderShader->ProcessShader(object);	
	OR_Globals::Context()->SetCullingMode(OR_Culling_Back);


	/* second pass ***********************************************************/
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	OR_Globals::Context()->SetCullingMode(OR_Culling_Back);
	OR_Globals::Context()->SetLineSize(BorderWidth);
	MiddleShader->ProcessShader(object);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	OR_Globals::Context()->SetDefaultLineSize();
	OR_Globals::Context()->SetCullingMode(OR_Culling_Back);

	/* reset rendering context ***********************************************/
	/* enable texture mapping */
	OR_Globals::Context()->SetDefault2DTexturingMode();
	/* re-set the culling */
	OR_Globals::Context()->SetDefaultCullingMode();
}

/* serialization methods ***************************************/
void OR_CartoonShader::BuildFromFile( OR_File& file )
{
	/* load the basic shader datas */
	OR_Shader::BuildFromFile(file);

	/* load the specific datas */
	file >> BorderWidth
		 >> BorderShaderName_
		 >> MiddleShaderName_;
}

void OR_CartoonShader::BuildToFile( OR_File& file )
{
	/* save the basic shader datas */
	OR_Shader::BuildToFile(file);

	/* save the specific datas */
	file << BorderWidth;

	if( this->GetBorderShader()!=NULL )
		file << this->GetBorderShader()->GetName();
	else
	{
		OR_Globals::MessageHandler()->Warning("OR_CartoonShader::BuildToFile", "The border shader has no target shader. Exporting default one.");
		file << OR_Globals::GetDefaultShader()->GetName();
	}
	if( this->GetMiddleShader()!=NULL )
		file << this->GetBorderShader()->GetName();
	else
	{
		OR_Globals::MessageHandler()->Warning("OR_CartoonShader::BuildToFile", "The middle shader has no target shader. Exporting default one.");
		file << OR_Globals::GetDefaultShader()->GetName();
	}
}

/*------------------------------------------------------------------------------
/** Name : OR_CartoonShader::PostExportPass
 *
 *  \author Gabriel Peyré 2001-11-12
 *
 *	if the shader has not already been set, try to fix the reference.
*/
/*------------------------------------------------------------------------------*/
void OR_CartoonShader::PostExportPass()
{
	/* if the shader has not already been set, try to fix the reference */
	OR_Shader* pRetrievedShader = OR_Globals::ShaderManager()->GetShaderByName(BorderShaderName_);
	this->SetBorderShader( *pRetrievedShader );
	pRetrievedShader = OR_Globals::ShaderManager()->GetShaderByName(MiddleShaderName_);
	this->SetMiddleShader( *pRetrievedShader );
	/* free as much memory as possible */
	BorderShaderName_.clear();
	MiddleShaderName_.clear();
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

