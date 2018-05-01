//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#include "OR_ForceManager.h"

namespace OR {


//-----------------------------------------------------------------------------
// Name: OR_ForceManager::ProcessParticule
/**
*   @param  particule The particule we want to compute the force.
*
*	Compute all force acting on a particule.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_ForceManager::ProcessParticule(OR_Particule& particule)
{
	for( IT_ManagerMap_Template(OR_Force_ABC) it=begin(); it!=end(); ++it )
	{
		OR_Force_ABC *pForce = (*it).second;
		if( pForce->IsActive() )
			pForce->ProcessParticule(particule);
	}
}


//-----------------------------------------------------------------------------
// Name: OR_ForceManager::ProcessObject
/**
*   @param  handler The handler of the object we want to compute the force.
*
*	Compute all force acting on an object.
*/
/// \author Gabriel Peyré 2001-08-31
//-----------------------------------------------------------------------------
OR_INLINE
void OR_ForceManager::ProcessObject(OR_RigidBody& object)
{
	for( IT_ManagerMap_Template(OR_Force_ABC) it=begin(); it!=end(); ++it )
	{
		OR_Force_ABC *pForce = (*it).second;
		if( pForce->IsActive() )
			pForce->ProcessObject(object);
	}
}


} // End namespace OR
