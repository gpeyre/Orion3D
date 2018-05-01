
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_FlatShader.h
 *  \brief Definition of class \c OR_FlatShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_FlatShader_h_
#define __OR_FlatShader_h_

#include "../configuration/OR_Config.h"
#include "OR_Shader.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_FlatShader
 *  \brief  the most simple shader : just a color.
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_FlatShader: public OR_Shader
{
public:
	/** return the type of the shader */
	virtual OR_Elements GetType()
	{ return OR_SHADER_Flat; }
	
	/* to process the pixel shader stage ******************************/
	/** render the vertex array to screen */
	virtual void ProcessShader(OR_Shadable& object);
	
	//-------------------------------------------------------------------------
	/** \name serialization methods */
	//-------------------------------------------------------------------------
	//@{
	OR_DEFINE_SERIALIZATION(OR_FlatShader);
	//@}
};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_FlatShader.inl"
#endif


#endif // __OR_FlatShader_h_

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

