
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SingleTextureMapShader.h
 *  \brief Definition of class \c OR_SingleTextureMapShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_SingleTextureMapShader_h_
#define __OR_SingleTextureMapShader_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_SingleTextureMapShader
 *  \brief  a shader with just one texture.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_SingleTextureMapShader: public OR_Shader
{
	
public:
	
	/** constructor */
	OR_SingleTextureMapShader( const char* adresse=NULL, OR_Bool ismipmap=false );
	/** destructor */
	virtual ~OR_SingleTextureMapShader();
	
	/** re-set the texture */
	void LoadTexture( const char* adresse );
	/** re-set the texture */
	void LoadTextureFromMem( const void* lump, OR_I32 size, ILenum type = IL_TYPE_UNKNOWN );
	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER_SingleTextureMap; }
	/** get the texture */
	OR_Texture* GetTexture()
	{ return MyTexture; }
	/** set the texture */
	void SetTexture(OR_Texture* t)
	{ MyTexture=t; }
	
	/* to process the pixel shader stage ******************************/
	/** render the vertex array to screen */
	virtual void ProcessShader(OR_Shadable& object);
	
	//-------------------------------------------------------------------------
	/** \name serialization methods */
	//-------------------------------------------------------------------------
	//@{
	/** import the data from an opened file to the object */
	virtual void BuildFromFile( OR_File& file );
	/** export the data from the object to an opened file */
	virtual void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_SingleTextureMapShader);
	//@}
	
private:
	
	/** the texture of the shader */
	OR_Texture* MyTexture;
	
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_SingleTextureMapShader.inl"
#endif


#endif // __OR_SingleTextureMapShader_h_

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

