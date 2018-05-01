/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_CartoonShader.inl
 *  \brief Inlined methods for \c OR_CartoonShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_CartoonShader.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader* OR_CartoonShader::GetBorderShader()
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	\return  the border shader.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Shader* OR_CartoonShader::GetBorderShader()
{
	return BorderShader;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader* OR_CartoonShader::GetBorderShader()
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	\return  the middle shader.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Shader* OR_CartoonShader::GetMiddleShader()
{
	return MiddleShader;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_CartoonShader::SetBorderShader(OR_Shader& border_shader)
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Set the border shader.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_CartoonShader::SetBorderShader(OR_Shader& border_shader)
{
	BorderShader = &border_shader;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_CartoonShader::SetBorderShader(OR_Shader& border_shader)
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Set the middle shader.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_CartoonShader::SetMiddleShader(OR_Shader& middle_shader)
{
	MiddleShader = &middle_shader;
}

} // End namespace OR

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

