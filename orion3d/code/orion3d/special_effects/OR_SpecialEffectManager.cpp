/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_SpecialEffectManager.cpp
 *  \brief implementation of a manager of special effects.
 *  \author Gabriel Peyré 2001-07-20
 */ 
/*------------------------------------------------------------------------------*/

#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_SpecialEffectManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_SpecialEffectManager.h"

#ifndef OR_USE_INLINE
	#include "OR_SpecialEffectManager.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffectManager::Update
 *
 *  \author Gabriel Peyré 2001-07-20
 *
 *	Update each particules system
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpecialEffectManager::Update()
{
	for( IT_ManagerMap_Template(OR_SpecialEffect) it=begin(); it!=end(); ++it )
		(*it).second->Update();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_SpecialEffectManager::Draw
 *
 *  \author Gabriel Peyré 2001-07-20
 *
 *	Draw each particules system
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpecialEffectManager::Draw()
{
	for( IT_ManagerMap_Template(OR_SpecialEffect) it=begin(); it!=end(); ++it )
		(*it).second->Draw();
}

/*------------------------------------------------------------------------------*/
// Name : OR_SpecialEffectManager::BuildFromFile
/** 
 *  \param  file The file we want to export the object to.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object from a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpecialEffectManager::BuildFromFile( OR_File& file )
{
}



/*------------------------------------------------------------------------------*/
// Name : OR_SpecialEffectManager::BuildToFile
/** 
 *  \param  file The file we want to export the object from.
 *  \author Gabriel Peyré 2001-08-05
 *
 *  Export the object to a file.
 */ 
/*------------------------------------------------------------------------------*/
void OR_SpecialEffectManager::BuildToFile( OR_File& file )
{
}



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