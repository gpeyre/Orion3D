/*---------------------------------------------------------------------*/
/*                            OR_Texture.cpp                           */
/*---------------------------------------------------------------------*/
/*              definition de la classe OR_Texture                     */            
/*---------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Texture.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "OR_Texture.h"

namespace OR
{
	
/*-----------------------------------------------------------------------*/
/*                              classe OR_Texture                        */            
/*-----------------------------------------------------------------------*/
/*permet d'importer une texture depuis un fichier bmp                     */
/*-----------------------------------------------------------------------*/
/*        ecrite par Antoche                                             */
/*-----------------------------------------------------------------------*/

OR_Texture::OR_Texture(OR_Bool iscubemap, OR_I32 num, OR_Bool ismipmap)
:	IsCubeMap( iscubemap ),
	IsMipMap( ismipmap ),
	CubeMapNum( num ),
	NumTex( -1 ),
	Data( NULL ),
	FeedBuffer( NULL )
{
	Adresse = "undefined";
}

OR_Texture::~OR_Texture()
{
	/* free opengl memory */
	if( NumTex != -1 )
		glDeleteTextures( 1, &NumTex );
	/* free openil memory */
#ifdef _USE_OPENIL_
	OR_Globals::LogManager()->AddString("\nFreeing texture #%u : %s", OpenIL_id, Adresse.val());
	iluDeleteImage(OpenIL_id);
#endif
	
	OR_DELETEARRAY(FeedBuffer);
}

void OR_Texture::Bind()
{
	if (IsCubeMap)
		//glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT+CubeMapNum, NumTex);
		glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, NumTex);
	else
		glBindTexture(GL_TEXTURE_2D, NumTex);
}

OR_I32 OR_Texture::LoadImage( const char *name )
{
#ifdef _USE_OPENIL_

	ILuint Error;

	/* copy the image adress */
	Adresse=name;

	/* use openil to load the image */
	ilGenImages(1, &OpenIL_id);
	ilBindImage(OpenIL_id);
	ilLoadImage(name);  // Loads into the current bound image

	OR_Globals::LogManager()->AddString("\nLoading texture #%u : %s...", OpenIL_id, Adresse.val());

	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		OR_Globals::LogManager()->AddString("Error %d : %s", Error, (char*) iluErrorString(Error));
		OR_Globals::MessageHandler()->Warning("OR_Texture::LoadImage", "OpenIL warning loading %s : %s", name, (char*) iluErrorString(Error) );
		/** an error has occured */
		return OR_ERROR;
	}

	/* send the image to OpenGL as a texture */
	if( NumTex == -1 ) glGenTextures( 1, (GLuint *)&NumTex );
	glBindTexture( GL_TEXTURE_2D, NumTex );
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		OR_Globals::LogManager()->AddString("Error %d : %s", Error, (char*) iluErrorString(Error));
		OR_Globals::MessageHandler()->Warning("OR_Texture::LoadImage", "OpenIL warning loading %s : %s", name, (char*) iluErrorString(Error) );

		return OR_ERROR;
	}

		
	Data=ilGetData();
	Components=ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); ;
	Type = ilGetInteger(IL_IMAGE_TYPE);
	Format = ilGetInteger(IL_IMAGE_FORMAT);	
	Width = ilGetInteger(IL_IMAGE_WIDTH);
	Height = ilGetInteger(IL_IMAGE_HEIGHT);		

	/* set up texture parameters [filters, ...] */
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (IsMipMap)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	}
	else
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST ?
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST ?
	}
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	if (IsMipMap)
		gluBuild2DMipmaps
		(	
			GL_TEXTURE_2D, 	//target
			Components,		//nb couleurs
			Width,			//largeur
			Height,			//hauteur
			Format,			//type des couleurs
			Type,			//codage de chaque composante
			Data			//Image
		);
	else
	{
		if (IsCubeMap)
		{
			 glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT+(unsigned long)CubeMapNum,	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
		else
		{
			glTexImage2D
			(
				GL_TEXTURE_2D, 	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
	}

	OR_Globals::LogManager()->AddLine("OK");

	return OR_OK;
#else
	OR_Globals::MessageHandler()->FatalError("OR_Texture::LoadImage",
		"You *MUST* define _USE_OPENIL_ if you want to load image files.");
#endif /* #ifdef _USE_OPENIL_ */
}



OR_I32 OR_Texture::LoadImageFileFromMem( const void *lump, OR_I32 size, ILenum type )
{
#ifdef _USE_OPENIL_

	ILuint Error;

	/* copy the image adress */
	Adresse = "undefined";

	/* use openil to load the image */
	ilGenImages(1, &OpenIL_id);
	ilBindImage(OpenIL_id);
	ilLoadL(type, (void*)lump, size);  // Loads into the current bound image

	/* check for error */
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		OR_Globals::MessageHandler()->Warning("OR_Texture::LoadImageFileFromMem", "OpenIL warning loading the lump : %s", (char*) iluErrorString(Error) );
		/** an error has occured */
		return OR_ERROR;
	}

	/* send the image to OpenGL as a texture */
	if( NumTex == -1 ) glGenTextures( 1, (GLuint *)&NumTex );
	glBindTexture( GL_TEXTURE_2D, NumTex );
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		OR_Globals::MessageHandler()->Warning("OR_Texture::LoadImageFileFromMem", "OpenIL warning loading the lump : %s", (char*) iluErrorString(Error) );
		/** an error has occured */
		return OR_ERROR;
	}
		
	Data=ilGetData();
	Components=ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL); ;
	Type = ilGetInteger(IL_IMAGE_TYPE);
	Format = ilGetInteger(IL_IMAGE_FORMAT);	
	Width = ilGetInteger(IL_IMAGE_WIDTH);
	Height = ilGetInteger(IL_IMAGE_HEIGHT);		

	/* set up texture parameters [filters, ...] */
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (IsMipMap)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	}
	else
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST ?
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST ?
	}
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	if (IsMipMap)
		gluBuild2DMipmaps
		(	
			GL_TEXTURE_2D, 	//target
			Components,		//nb couleurs
			Width,			//largeur
			Height,			//hauteur
			Format,			//type des couleurs
			Type,			//codage de chaque composante
			Data			//Image
		);
	else
	{
		if (IsCubeMap)
		{
			 glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT+(unsigned long)CubeMapNum,	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
		else
		{
			glTexImage2D
			(
				GL_TEXTURE_2D, 	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
	}


#else
	OR_Globals::MessageHandler()->FatalError("OR_Texture::LoadImageFileFromMem",
		"You *MUST* define _USE_OPENIL_ if you want to load image files.");
#endif /* #ifdef _USE_OPENIL_ */

	return OR_OK;
}

OR_RETURN_CODE OR_Texture::ReLoadToGL()
{
	ILuint Error;
	if (Data==NULL)
	{
		OR_Globals::MessageHandler()->Warning("OR_Texture::ResetToGL", "No data to ve load.");
		return OR_ERROR;
	}

	/* free opengl memory */
	glDeleteTextures(1, &NumTex);
	NumTex = ilutGLBindTexImage();		// equivalent to : glBindTexture(GL_TEXTURE_2D, NumTex); glGenTextures(1, (GLuint *)&NumTex);
	Error = ilGetError();
	if (Error!=IL_NO_ERROR)
	{
		OR_Globals::MessageHandler()->Warning("OR_Texture::ReLoadToGL", "OpenIL warning loading : %s", (char*) iluErrorString(Error) );
		/** an error has occured */
		return OR_ERROR;
	}

	/* set up texture parameters [filters, ...] */
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (IsMipMap)
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	}
	else
	{
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST ?
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST ?
	}
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	if (IsMipMap)
		gluBuild2DMipmaps
		(	
			GL_TEXTURE_2D, 	//target
			Components,		//nb couleurs
			Width,			//largeur
			Height,			//hauteur
			Format,			//type des couleurs
			Type,			//codage de chaque composante
			Data			//Image
		);
	else
	{
		if (IsCubeMap)
		{
			 glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT+(unsigned long)CubeMapNum,	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
		else
		{
			glTexImage2D
			(
				GL_TEXTURE_2D, 	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
	}

	return OR_OK;
}

void OR_Texture::UnloadData()
{
	/* free openil memory */
	ilDeleteImages(1, &OpenIL_id);
	OR_DELETEARRAY(Data);
}

void OR_Texture::Unload()
{
#ifdef _USE_OPENIL_
	/* free openil memory */
	glDeleteTextures(1, &NumTex);
	ilDeleteImages(1, &OpenIL_id);
#else
	OR_Globals::MessageHandler()->FatalError("OR_Texture::Unload",
		"You *MUST* define _USE_OPENIL_ if you want to load image files.");
#endif /* #ifdef _USE_OPENIL_ */

	OR_DELETEARRAY(Data);
}

OR_I32 OR_Texture::BuildFromScreen(OR_I32 ll_x, OR_I32 ll_y, OR_I32 width, OR_I32 height)
{
  	Width=width;
	Height=height;
	OR_DELETE(Data);
	Data = new unsigned char[3*Width*Height];

	/* les parametre de la texture */	
	if( NumTex == -1 ) glGenTextures( 1, (GLuint *)&NumTex );
	glBindTexture( GL_TEXTURE_2D, NumTex );
	Type = GL_UNSIGNED_BYTE;
	Format = GL_RGB;
	Components = 3;
	
	/* copy the image from screen to buffer */
	glReadPixels(ll_x, ll_y, Width, Height, Format, Type, Data);

	/* creer la texture */
	if (IsMipMap)
		gluBuild2DMipmaps
		(	
			GL_TEXTURE_2D, 	//target
			Components,		//nb couleurs
			Width,			//largeur
			Height,			//hauteur
			Format,			//type des couleurs
			Type,			//codage de chaque composante
			Data			//Image
		);
	else
	{
		if (IsCubeMap)
		{
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT+(unsigned long)CubeMapNum,	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
		else
		{
			glTexImage2D
			(
				GL_TEXTURE_2D, 	//target
				0,				//mipmap level
				Components,		//nb couleurs
				Width,			//largeur
				Height,			//hauteur
				0,			 	//largeur du bord
				Format,			//type des couleurs
				Type,			//codage de chaque composante
				Data			//Image
			);
		}
	}

	return 0;
}

/* serialization methods ***************************************/
void OR_Texture::BuildFromFile( OR_File& file )
{
	file >> Adresse;
	/* translate texture adress */
	OR_String tex_adr(Adresse);
	OR_String base_adr( *OR_Globals::GetBaseFileAdress());
	
	OR_I32 pos=base_adr.lastIndexOf('/');
	if (pos<0) pos=base_adr.lastIndexOf('\\');

	if (pos<0) OR_Globals::MessageHandler()->Warning("OR_HierarchyTree::BuildFromFile", 
										"Could not translate image adress.");
	else
	{
		base_adr.truncate( pos+1 );
		base_adr += tex_adr;
	}
	LoadImage(base_adr.val());
}

void OR_Texture::BuildToFile( OR_File& file )
{
	file << Adresse;
}

/*-------------------------------------------------------------------------*/
/*                          class OR_TextureManager                        */
/*-------------------------------------------------------------------------*/
/* a manager of textures                                                   */
/*-------------------------------------------------------------------------*/

OR_I32 OR_TextureManager::AddTexture( const char* file, OR_Bool iscubemap, OR_I32 num, OR_Bool ismipmap )
{
	/* create a new texture */
	OR_Texture* new_texture=new OR_Texture(iscubemap, num, ismipmap);
	new_texture->LoadImage(file);
	/* add the light to the manager */
	return AddElement(new_texture);
}

OR_I32  OR_TextureManager::LoadImage( const char *File )
{
	if (IsSelectedEmpty()) return OR_Manager_SelectedEmpty;
	return GetElementSelected()->LoadImage(File);
}


/*------------------------------------------------------------------------------
 * Name : OR_Texture::FindTexture
 *
 *  \param  Path EXPLANATION
 *  \return PUT YOUR RETURN VALUE AND ITS EXPLANATION
 *  \author Antoine Bouthors 2001-11-29
 *
 * PUT YOUR COMMENTS HERE
 *------------------------------------------------------------------------------*/
OR_Texture* OR_TextureManager::FindTexture( const char* Path )
{
	if( Path == NULL ) return NULL;
	for( IT_ManagerMap_Template(OR_Texture) it=begin() ; it!=end() ; ++it )
	{
		OR_Texture* CurrentTexture = (*it).second;
		if( CurrentTexture -> GetImageAdress( ).compareTo( Path ) == 0 )
			return CurrentTexture;
	}
	return NULL;
}


} // namespace OR

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////