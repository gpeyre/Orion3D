
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MathSurfaceManager.h
 *  \brief Definition of class \c OR_MathSurfaceManager
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MathSurfaceManager_h_
#define __OR_MathSurfaceManager_h_

#include "../configuration/OR_Config.h"
#include "OR_MathSurface.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MathSurfaceManager
 *  \brief  a manager of math surface
 *  \author Gabriel Peyré 2001-11-12
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_Manager_Template_Object<OR_MathSurface>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_SmartManagerMap_Template<OR_MathSurface>;
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_MathSurface>;


class OR_MathSurfaceManager: public OR_Manager_Template_Object<OR_MathSurface>
{

};

} // End namespace OR


#endif // __OR_MathSurfaceManager_h_

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

