#error file removed !!
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleSystemManager.h
 *  \brief PUT THE COMMENTS ON THE FILE HERE 
 *  \author Gabriel Peyré 2001-07-20
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ParticuleSystemManager_h_
#define __OR_ParticuleSystemManager_h_

#include "../configuration/OR_Config.h"
#include "OR_ParticuleSystem.h"
#include "../utils/OR_ManagerMap_Template.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ParticuleSystemManager
 *  \brief  A manager of particule system
 *  \author Gabriel Peyré 2001-07-20
 */ 
/*------------------------------------------------------------------------------*/

class OR_ParticuleSystemManager: public OR_ManagerMap_Template<OR_ParticuleSystem>
{

public:

	void Update();
	void Draw();

private:

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ParticuleSystemManager.inl"
#endif


#endif // __OR_ParticuleSystemManager_h_

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

