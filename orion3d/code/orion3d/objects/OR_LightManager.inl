/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_LightManager.inl
 *  \brief Inlined methods for \c OR_LightManager
 *  \author Gabriel Peyré 2001-09-25
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_LightManager.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LightManager::GetNewID
 *
 *  \return	an new ID for the light
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_U32 OR_LightManager::GetNewID()
{
	return LightIDStack_.GetNewID();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LightManager::ReleaseID
 *
 *  \param  nID ID of the light removed
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_LightManager::ReleaseID(OR_U32 nID)
{
	LightIDStack_.ReleaseID( nID );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LightManager::GetLightIDStack
 *
 *  \return the stack of light ID's.
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_LightIDManager& OR_LightManager::GetLightIDStack()
{
	return LightIDStack_;
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

