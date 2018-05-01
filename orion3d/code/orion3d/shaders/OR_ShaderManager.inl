/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShaderManager.inl
 *  \brief Inlined methods for \c OR_ShaderManager
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/

#include "OR_ShaderManager.h"

namespace OR {

OR_INLINE	
OR_I32 OR_ShaderManager::SetAmbient(OR_Float ambient[4])
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetAmbient(ambient);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetAmbient(OR_Coord_RVBA c,OR_Float val)
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetAmbient(c, val);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetDiffuse(OR_Float diffuse[4])
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetDiffuse(diffuse);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetDiffuse(OR_Coord_RVBA c,OR_Float val)
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetDiffuse(c, val);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetSpecular(OR_Float specular[4])
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetSpecular(specular);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetSpecular(OR_Coord_RVBA c,OR_Float val)
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetSpecular(c, val);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetEmission(OR_Float emission[4])
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetEmission(emission);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetEmission(OR_Coord_RVBA c,OR_Float val)
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetEmission(c, val);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetShine(OR_Float shine)
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetShine(shine);
	return 0;
}

OR_INLINE	
OR_I32 OR_ShaderManager::SetAlpha(OR_Float val)
{
	if (IsSelectedEmpty()) return 1;
	GetElementSelected()->SetAlpha(val);
	return 0;
}

OR_INLINE	
OR_Elements OR_ShaderManager::GetType()
{
	if (IsSelectedEmpty()) return OR_SHADER;
	return GetElementSelected()->GetType();
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

