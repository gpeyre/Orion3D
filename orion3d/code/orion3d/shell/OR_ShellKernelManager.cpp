/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellKernelManager.cpp
 *  \brief Definition of class \c OR_ShellKernelManager
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_ShellKernelManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_ShellKernelManager.h"

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ShellKernelManager::GetCurrentConsole
 *
 *  \return the console used by the current kernel, NULL is there is no kernel or no console.
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/
OR_ShellConsole_ABC* OR_ShellKernelManager::GetCurrentConsole()
{
	OR_ShellKernel* pKernel = this->GetElementSelected();

	if( pKernel==NULL )
		return NULL;

	return pKernel->GetCurrentConsole();
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

