/*-------------------------------------------------------------------*/
/*                    OR_BumpShader_Emboss.h                         */
/*-------------------------------------------------------------------*/
/* Created : 17 Apr 2001   2h12                                      */
/*-------------------------------------------------------------------*/

/** \file
	Defines an emboss bump map shader.
	\author Gabriel
*/

#ifndef _OR_BUMPSHADER_EMBOSS_H_
#define _OR_BUMPSHADER_EMBOSS_H_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"
#include "../objects/OR_Light.h"

namespace OR
{
	
/*-------------------------------------------------------------------*/
/*                   class OR_BumpShader_Emboss                      */
/*-------------------------------------------------------------------*/
/* an emboss bump map shader.                                        */
/*-------------------------------------------------------------------*/

/// an emboss bump map shader.
/**	This class defines 3 functions, depending on the implementation of the emboss bump mapping.
	These implementation are using 1, 2 or 3 pass, and must be chossen depending on client hardware
	extensions supported.
	\author Gabriel
*/

class ORION3D_API OR_BumpShader_Emboss: public OR_Shader
{
private:
	/** the light used to compute texture decal */
	OR_Light* MyLight;

	/** the bump texture : must have an alpha channel, with
		base texture as color and bump texture as alpha.
		That mean that the image must have 4 component, for example a .png with an alpha channel.
		Note that the bump texture is in fact a height map in gray scale. */
	OR_Texture *MyTexture;

	/** The offset of the bump, ie.the depth of the bump. */
	OR_Float Offset;
public:
	/** constructor */
	OR_BumpShader_Emboss(char* adresse=NULL, OR_Bool ismipmap=false);
	/** destructor */
	~OR_BumpShader_Emboss()
	{
		/* delete the texture only if they are not in the manager */
		if( !OR_Globals::TextureManager()->ContainsElement(MyTexture) ) 
			OR_DELETE(MyTexture);
	}

	/** set the light */
	void SetLight(OR_Light* l)
	{ MyLight=l; }
	/** get the light */
	OR_Light* GetLight()
	{ return MyLight; }
	/** set the offset */
	void SetOffset(OR_Float o)
	{ Offset=o; }
	/** get the offset */
	OR_Float GetOffset()
	{ return Offset; }
	/** get the texture */
	OR_Texture* GetTexture()
	{ return MyTexture; }
	/** set the texture */
	void SetTexture(OR_Texture* t)
	{ MyTexture=t; }
	
	/** re-set the texture */
	void LoadTexture(char* adresse);
	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER_Bump_Emboss; }

	/** check if the hardware support bump mapping */
	virtual OR_Bool IsShaderSupported()
	{
		return (OR_Globals::GLExtensionsManager()->IsMultitextureSupported()      &&
				OR_Globals::GLExtensionsManager()->IsTextureEnvCombineSupported() &&
				OR_Globals::GLExtensionsManager()->GetNbTextureUnits()>1);
	}

	/* to process the pixel shader stage ******************************/
	/** render the vertex array using emboss bump mapping 1 pass */
	void ProcessBump_1Pass(OR_Mesh* object);
	/** render the vertex array using no bump mapping */
	void ProcessBump_Flat(OR_Mesh* object);
	/** select the best algo to use with client hardware
	    [for the moment, emboss bump mapping is only supported with multitexturing] */
	virtual void ProcessShader(OR_Shadable& object);

	
	/* serialization methods ***************************************/
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	
	OR_DEFINE_SERIALIZATION(OR_BumpShader_Emboss);
};




} // namespace OR

#endif // _OR_BUMPSHADEREMBOSS_H_


///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D license.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la license Orion3D.                              //
//  Se reporter a orion3d_license.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////