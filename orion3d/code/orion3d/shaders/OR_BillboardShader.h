
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_BillboardShader.h
 *  \brief Definition of class \c OR_BillboardShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_BillboardShader_h_
#define __OR_BillboardShader_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_BillboardShader
 *  \brief  a shader that encaspulate another one to force the object to face the screen.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_BillboardShader: public OR_Shader
{

public:
	
	/** constructor */
	OR_BillboardShader(OR_Shader* myshader=NULL);

	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER_Billboard; }
	/** unrotate the modelview matrix  */
	void ActivateBillboarding()
	{ UnRotateModelViewMatrix(); }

	//-------------------------------------------------------------------------
	/** \name Base shader management */
	//-------------------------------------------------------------------------
	//@{
	OR_Shader* GetBaseShader();
	void SetBaseShader( OR_Shader& base_shader );
	//@}
	

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	void SetAmbientDiffuse(OR_Float color[4]);
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
	OR_DEFINE_SERIALIZATION(OR_BillboardShader);
	//@}
	
private:
	
	/** shader to bilboard */
	OR_Shader* pTargetShader_;
	/** just for export, in case were the shader could not be retrieved */
	OR_String TargetShaderName_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_BillboardShader.inl"
#endif


#endif // __OR_BillboardShader_h_

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

