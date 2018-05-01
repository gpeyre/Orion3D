/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_BillboardShader.inl
 *  \brief Inlined methods for \c OR_BillboardShader
 *  \author Gabriel Peyré 2001-11-23
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_BillboardShader.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Shader* OR_BillboardShader::GetBaseShader()
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Return the target base shader.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Shader* OR_BillboardShader::GetBaseShader()
{
	return pTargetShader_;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : void OR_BillboardShader::SetBaseShader( OR_Shader& base_shader )
 *
 *  \author Gabriel Peyré 2002/03/21
 *
 *	Set the target base shader.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_BillboardShader::SetBaseShader( OR_Shader& base_shader )
{
	pTargetShader_ = &base_shader; 
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

