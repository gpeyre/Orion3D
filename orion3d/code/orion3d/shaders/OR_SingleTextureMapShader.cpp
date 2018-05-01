/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SingleTextureMapShader.cpp
 *  \brief Definition of class \c OR_SingleTextureMapShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SingleTextureMapShader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SingleTextureMapShader.h"

#ifndef OR_USE_INLINE
	    #include "OR_SingleTextureMapShader.inl"
#endif

using namespace OR;

OR_SingleTextureMapShader::OR_SingleTextureMapShader( const char * adresse , OR_Bool ismipmap )
 :OR_Shader( ),
 MyTexture( NULL )
{
	if( adresse != NULL ) MyTexture = OR_Globals::TextureManager( )->FindTexture( adresse ); 
    
	if( !MyTexture ) 
	{
		MyTexture=new OR_Texture( false, 0, ismipmap );
		if( adresse != NULL ) MyTexture -> LoadImage( adresse );
		OR_Globals::TextureManager()->AddElement(MyTexture);
	}
	MyTexture->UseIt();  
}

OR_SingleTextureMapShader::~OR_SingleTextureMapShader()
{
	OR_SmartCounter::CheckAndDelete( MyTexture );
}

void OR_SingleTextureMapShader::LoadTexture( const char* adresse )
{
	MyTexture->LoadImage(adresse);
}

void OR_SingleTextureMapShader::LoadTextureFromMem( const void* lump, OR_I32 size, ILenum type )
{
	MyTexture->LoadImageFileFromMem(lump, size, type);
}

//-----------------------------------------------------------------------------
// Name: OR_Shader::ProcessShader
/**
*   @param  object the object to render.
*
*	Render the object to screen.
*	\author  Gabriel Peyré 2001-08-10
*/
//-----------------------------------------------------------------------------
void OR_SingleTextureMapShader::ProcessShader(OR_Shadable& object)
{
	/* intialize rendering context ******************************************/
    this->SetUpColor();

	/* set the culling */
	OR_Globals::Context()->SetCullingMode(CullingMode);
	/* set the blending */
	OR_Globals::Context()->SetBlendingMode( this->GetBlendingMode() );

	/* set up texture */
	if (MyTexture!=NULL) 
		MyTexture->Bind();

	/* render the object *****************************************************/
	/* flush all datas */
	object.ProcessAllFaces();

	/* reset rendering context ***********************************************/
	/* re-set the culling */
	OR_Globals::Context()->SetDefaultCullingMode();
	/* re-set the blending */
	OR_Globals::Context()->SetDefaultBlendingMode();
}


/* serialization methods ***************************************/
void OR_SingleTextureMapShader::BuildFromFile( OR_File& file )
{
//	if (MyTexture==NULL) MyTexture=new OR_Texture;
	/* load the basic shader datas */
	OR_Shader::BuildFromFile(file);
	if (MyTexture==NULL)
	{
		MyTexture=new OR_Texture;
		OR_Globals::TextureManager()->AddElement(MyTexture);
	}
	/* load the specific datas */
	file >> MyTexture;
}

void OR_SingleTextureMapShader::BuildToFile( OR_File& file )
{
	/* save the basic shader datas */
	OR_Shader::BuildToFile(file);
	/* save the specific datas */
	file << MyTexture;
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

