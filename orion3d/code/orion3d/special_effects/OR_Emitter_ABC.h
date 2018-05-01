
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_Emitter_ABC.h
 *  \brief definition of OR_Emitter_ABC
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_Emitter_ABC_h_
#define __OR_Emitter_ABC_h_

#include "../configuration/OR_Config.h"
#include "../maths/OR_Maths.h"
#include "../physic/OR_Particule.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_Emitter_ABC
 *  \brief  Base class for every emmitter class
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_Emitter_ABC
{

public:

	/** initialize a particule */
	virtual void InitParticule(OR_Particule& particule, OR_Vector3D& AbsoluteSpeed)=0;

private:


};

} // End namespace OR



#endif // __OR_Emitter_ABC_h_

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

