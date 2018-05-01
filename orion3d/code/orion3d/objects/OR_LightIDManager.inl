/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_LightIDManager.inl
 *  \brief Inlined methods for \c OR_LightIDManager
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_LightIDManager.h"

namespace OR {

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LightIDManager constructor
 *
 *  \author Gabriel Peyré 2001-09-24
 *
 *	Create the stack with some opengl IDs .
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_LightIDManager::OR_LightIDManager()
{
	this->Init(GL_LIGHT0, GL_LIGHT0+OR_NB_MAX_LIGHT);
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_LightIDManager destructor
 *
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_LightIDManager::~OR_LightIDManager()
{
	/* NOTHING */
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

