
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_LightIDManager.h
 *  \brief Definition of class \c OR_LightIDManager
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_LightIDManager_h_
#define __OR_LightIDManager_h_

#include "../configuration/OR_Config.h"
#include "../utils/OR_IDStack.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_LightIDManager
 *  \brief  a stack of Id for the lights.
 *  \author Gabriel Peyré 2001-09-24
 */ 
/*------------------------------------------------------------------------------*/

class OR_LightIDManager: public OR_IDStack
{

public:

    OR_LightIDManager();
    virtual ~OR_LightIDManager();

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_LightIDManager.inl"
#endif


#endif // __OR_LightIDManager_h_

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

