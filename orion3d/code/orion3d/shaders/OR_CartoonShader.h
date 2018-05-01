/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CartoonShader.h
 *  \brief Definition of class \c OR_CartoonShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_CartoonShader_h_
#define __OR_CartoonShader_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"

namespace OR {

/** the default width of the cartoon shader */
#define OR_DEFAULT_CARTOON_SHADER_BORDER_WIDTH 8

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_CartoonShader
 *  \brief  a shader simulating cartoon redering via a 2 pass mathod.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_CartoonShader: public OR_Shader
{
	
public:
	
	/** constructor */
	OR_CartoonShader(OR_Shader* bordershader=NULL,
		OR_Shader* middleshader=NULL);

	/** set the border width */
	void SetBorderWidth(OR_I32 val);
	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER_Cartoon; }

	//-------------------------------------------------------------------------
	/** \name accessors */
	//-------------------------------------------------------------------------
	//@{
	OR_Shader* GetBorderShader();
	OR_Shader* GetMiddleShader();
	void SetBorderShader(OR_Shader& border_shader);
	void SetMiddleShader(OR_Shader& middle_shader);
	//@}

	
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
	void PostExportPass();
	OR_DEFINE_SERIALIZATION(OR_CartoonShader);
	//@}
	
private:
	
	/** shader use to render the border */
	OR_Shader* BorderShader;
	/** shader use to render the middle */
	OR_Shader* MiddleShader;
	/** name of the shader use to render the border (used for import only) */
	OR_String BorderShaderName_;
	/** name of the shader use to render the middle (used for import only) */
	OR_String MiddleShaderName_;
	/** width of the border line */
	OR_I32 BorderWidth;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_CartoonShader.inl"
#endif


#endif // __OR_CartoonShader_h_

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

