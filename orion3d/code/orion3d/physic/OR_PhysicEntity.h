
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicEntity.h
 *  \brief definition of class OR_PhysicEntity
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_PhysicEntity_h_
#define __OR_PhysicEntity_h_

#include "../configuration/OR_Config.h"

namespace OR {

class OR_ForceManager;

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_PhysicEntity
 *  \brief  Base class for all object that can be handled by the physic engine.
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_PhysicEntity
{

public:

	/** to get the type of the physic object */
	enum T_PhysicEntity_Type
	{
		kPhysicEntity_ParticuleManager,
		kPhysicEntity_RigidBody,
		kPhysicEntity_Deflector
	};

	virtual void UpdatePhysics_RK4( OR_U32 nStepRK4 )=0;
	virtual void UpdatePhysics_Verlet()=0;
	virtual void UpdatePhysics_Euler()=0;

	virtual void ProcessForce( OR_ForceManager& ForceManager )=0;

	virtual T_PhysicEntity_Type GetPhysicType()=0;
	virtual void ResetAccumulators()=0;
    
};

typedef list<OR_PhysicEntity*>			T_PhysicEntityList;
typedef T_PhysicEntityList::iterator	IT_PhysicEntityList;

} // End namespace OR


#endif // __OR_PhysicEntity_h_

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

