/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Light.inl
 *  \brief Inlined methods for \c OR_Light
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_Light.h"

namespace OR {



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Light::GetLightID
 *
 *  \return The ID of the light.
 *  \author Gabriel Peyré 2001-09-25
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_Light::GetLightID()
{
	return nLightID_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Light::SetDiffuse
 *
*  \param  color diffuse component of the light.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Light::SetDiffuse(OR_Vector4D color)
{
	Diffuse = color;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Light::SetSpecular
 *
 *  \param  color specular component of the light.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Light::SetSpecular(OR_Vector4D color)
{
	Specular = color;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_Light::SetAmbient
 *
*  \param  color ambient component of the light.
 *  \author Gabriel Peyré 2001-10-23
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_Light::SetAmbient(OR_Vector4D color)
{
	Ambient = color;
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

