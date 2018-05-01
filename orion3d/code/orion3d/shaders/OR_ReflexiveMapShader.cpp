/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ReflexiveMapShader.cpp
 *  \brief Definition of class \c OR_ReflexiveMapShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ReflexiveMapShader.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ReflexiveMapShader.h"

#ifndef OR_USE_INLINE
	    #include "OR_ReflexiveMapShader.inl"
#endif

using namespace OR;


OR_ReflexiveMapShader::OR_ReflexiveMapShader( const char * adresse1 , const char * adresse2,
	const char * adresse3 , const char * adresse4,
	const char * adresse5 , const char * adresse6 )
:OR_Shader()
{
	for (OR_I32 i=0; i<6; i++)
		MyTexture[i]=new OR_Texture(true, i, false);
	if (adresse1!=NULL) MyTexture[0]->LoadImage(adresse1);
	if (adresse2!=NULL) MyTexture[1]->LoadImage(adresse2);
	if (adresse3!=NULL) MyTexture[2]->LoadImage(adresse3);
	if (adresse4!=NULL) MyTexture[3]->LoadImage(adresse4);
	if (adresse5!=NULL) MyTexture[4]->LoadImage(adresse5);
	if (adresse6!=NULL) MyTexture[5]->LoadImage(adresse6);
}

OR_ReflexiveMapShader::~OR_ReflexiveMapShader()
{
	/* delete the texture only if they are not in the manager */
	for (OR_I32 i=0; i<6; i++)
		if (!OR_Globals::TextureManager()->ContainsElement(MyTexture[i])) 
		{
			OR_DELETE(MyTexture[i]);
		}
}

void OR_ReflexiveMapShader::LoadTexture( const char* adresse, OR_I32 num )
{
	MyTexture[num]->LoadImage(adresse);
}

//-----------------------------------------------------------------------------
// Name: OR_ReflexiveMapShader::ProcessShader
/**
*   @param  object the object to render.
*
*	Render the object to screen.
*	\author  Gabriel Peyré 2001-08-10
*/
//-----------------------------------------------------------------------------
void OR_ReflexiveMapShader::ProcessShader(OR_Shadable& object)
{
	/* intialize rendering context ******************************************/	
	OR_UnRotateTextureMatrix();	
	/* set up the material */
	this->SetUpColor();
	/* enable cube texture mapping */
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_CUBE_MAP_EXT);
	/* set the environnement mode */
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
	/* bind the texture */
	if( MyTexture[0]!=NULL ) 
		MyTexture[0]->Bind();
	/* set the culling */
	OR_Globals::Context()->SetCullingMode(CullingMode);

	/* render the object *****************************************************/
	/* flush all datas */
	object.ProcessAllFaces();

	/* reset rendering context ***********************************************/
	/* disable cube texture mapping */
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_CUBE_MAP_EXT);
	ReRotateTextureMatrix();
	/* re-set the culling */
	OR_Globals::Context()->SetDefaultCullingMode();
}


/* serialization methods ***************************************/
void OR_ReflexiveMapShader::BuildFromFile( OR_File& file )
{
	for (OR_I32 i=0; i<6; i++)
		if (MyTexture[i]==NULL)
		{
			MyTexture[i]=new OR_Texture;
			OR_Globals::TextureManager()->AddElement(MyTexture[i]);
		}
	/* load the basic shader datas */
	OR_Shader::BuildFromFile(file);
	
	/* load the specific datas */
	file >> MyTexture[0]
		 >> MyTexture[1]
		 >> MyTexture[2]
		 >> MyTexture[3]
		 >> MyTexture[4]
		 >> MyTexture[5];
}

void OR_ReflexiveMapShader::BuildToFile( OR_File& file )
{
	/* save the basic shader datas */
	OR_Shader::BuildToFile(file);
	/* save the specific datas */
	file << MyTexture[0]
		 << MyTexture[1]
		 << MyTexture[2]
		 << MyTexture[3]
		 << MyTexture[4]
		 << MyTexture[5];
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

