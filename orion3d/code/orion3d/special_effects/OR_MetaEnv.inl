/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MetaEnv.inl
 *  \brief Inlined methods for \c OR_MetaEnv
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_MetaEnv.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaEnv::SetIsoLevel
 *
 *  \param  level the new iso-value.
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_MetaEnv::SetIsoLevel(OR_Float level)
{
	IsoSurface_.SetIsoLevel(level);
	bNeedUpdate_ = true;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_MetaEnv::GetIsoLevel
 *
 *  \return the iso-value.
 *  \author Gabriel Peyré 2001-10-29
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Float OR_MetaEnv::GetIsoLevel()
{
	return IsoSurface_.GetIsoLevel();
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

