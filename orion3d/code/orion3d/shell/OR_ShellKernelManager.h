
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ShellKernelManager.h
 *  \brief Definition of class \c OR_ShellKernelManager
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ShellKernelManager_h_
#define __OR_ShellKernelManager_h_

#include "../configuration/OR_Config.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "OR_ShellKernel.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ShellKernelManager
 *  \brief  the manager of kernel
 *  \author Gabriel Peyré 2001-11-19
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_ShellKernel>;

class ORION3D_API OR_ShellKernelManager:	public OR_ManagerMap_Template<OR_ShellKernel>
{

public:

    //-------------------------------------------------------------------------
    /** \name helper methods */
    //-------------------------------------------------------------------------
    //@{
	OR_ShellConsole_ABC* GetCurrentConsole();
    //@}

};

} // End namespace OR


#endif // __OR_ShellKernelManager_h_

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

