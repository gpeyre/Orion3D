/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleSystemManager.cpp
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-07-20
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ParticuleSystemManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ParticuleSystemManager.h"

#ifndef OR_USE_INLINE
	    #include "OR_ParticuleSystemManager.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystemManager::Update
 *
 *  \author Gabriel Peyré 2001-07-20
 *
 *	Update each particules system
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleSystemManager::Update()
{
	for( IT_ManagerMap_Template(OR_ParticuleSystem) it=begin(); it!=end(); ++it )
		(*it).second->Update();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleSystemManager::Draw
 *
 *  \author Gabriel Peyré 2001-07-20
 *
 *	Draw each particules system
 */ 
/*------------------------------------------------------------------------------*/
void OR_ParticuleSystemManager::Draw()
{
	for( IT_ManagerMap_Template(OR_ParticuleSystem) it=begin(); it!=end(); ++it )
		(*it).second->Draw();
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

