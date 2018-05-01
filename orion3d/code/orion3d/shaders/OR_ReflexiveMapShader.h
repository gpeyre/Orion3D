
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ReflexiveMapShader.h
 *  \brief Definition of class \c OR_ReflexiveMapShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ReflexiveMapShader_h_
#define __OR_ReflexiveMapShader_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ReflexiveMapShader
 *  \brief  a shader using cube map to simulate reflexions.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_ReflexiveMapShader: public OR_Shader
{
private:
	OR_Texture *MyTexture[6];
public:
	/** constructor */
	OR_ReflexiveMapShader( const char * adresse1 = NULL, const char * adresse2 = NULL,
	const char * adresse3 = NULL, const char * adresse4 = NULL,
	const char * adresse5 = NULL, const char * adresse6 = NULL );

	/** destructor */
	~OR_ReflexiveMapShader();
	/** re-set the texture */
	void LoadTexture( const char * adresse , OR_I32 num = 0 );
	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER_Reflexive; }
	
	/** check if the hardware support bump mapping */
	virtual OR_Bool IsShaderSupported()
	{ 
		return OR_Globals::GLExtensionsManager()->IsCubeMapSupported(); 
	}
	
	/** get the texture */
	OR_Texture* GetTexture(OR_U32 num)
	{ 
		if (num<6 && num>=0) return MyTexture[num]; 
		else return NULL;
	}
	/** set the texture */
	void SetTexture(OR_Texture* t, OR_U32 num)
	{ if (num<6 && num>=0) MyTexture[num]=t; }
	
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
	OR_DEFINE_SERIALIZATION(OR_ReflexiveMapShader);
	//@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ReflexiveMapShader.inl"
#endif


#endif // __OR_ReflexiveMapShader_h_

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

