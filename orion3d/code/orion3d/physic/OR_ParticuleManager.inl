/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleManager.inl
 *  \brief INlined functions of OR_ParticuleManager.
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_ParticuleManager.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager constructor
 *
 *  \param  ConstraintManager constraints acting on the particules.
 *  \author Gabriel Peyré 2001-07-18
 *
 *	If set to NULL, the particule manager won't mess with constraint.
 *	If you want constraints to be resolved just after the resolution of the motion 
 *	of particule, then set the constraints manager.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ParticuleManager::OR_ParticuleManager(OR_ConstraintManager* pConstraintManager)
:	OR_ManagerList_Template<OR_Particule>(),
	pForceManager_( NULL )
{
	pConstraintManager_ = pConstraintManager;
}



/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::GetConstaintManager
 *
 *  \return The constraint manager
 *  \author Gabriel Peyré 2001-07-18
 *
 *	The constraint manager can be NULL either if there is no constraints acting on
 *	the particules of the system, or if constraint are not not resolved in the particules
 *	manager.
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ConstraintManager* OR_ParticuleManager::GetConstaintManager()
{
	return pConstraintManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::SetConstraintManager
 *
 *  \return The constraint manager
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleManager::SetConstraintManager(OR_ConstraintManager* ConstraintManager)
{
	pConstraintManager_=ConstraintManager;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::GetConstraintManager
 *
 *  \return The manager of constraints.
 *  \author Gabriel Peyré 2001-07-31
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ConstraintManager* OR_ParticuleManager::GetConstraintManager()
{
	return pConstraintManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::SetConstraintManager
 *
 *  \param  ConstraintManager The new manager of constraints.
 *  \author Gabriel Peyré 2001-07-31
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleManager::SetConstraintManager(OR_ConstraintManager& ConstraintManager)
{
	pConstraintManager_ = &ConstraintManager;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::GetForceManager
 *
 *  \return The manager of forces.
 *  \author Gabriel Peyré 2001-07-31
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ForceManager* OR_ParticuleManager::GetForceManager()
{
	return pForceManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::GetForceManager
 *
 *  \param  ForceManager The new manager of forces.
 *  \author Gabriel Peyré 2001-07-31
 *
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleManager::SetForceManager(OR_ForceManager& ForceManager)
{
	pForceManager_ = &ForceManager;
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::SetParticuleInvMass
 *
 *  \param  rInvMass Inverse of the mass of each particule.
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_ParticuleManager::SetParticuleInvMass(OR_Float rInvMass)
{
	for( IT_ParticuleList it=begin(); it!=end(); ++it )
		(*it)->SetInvMass(rInvMass);
}

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_ParticuleManager::GetParticuleList
 *
 *  \return List of active particules.
 *  \author Gabriel Peyré 2001-09-04
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
T_ParticuleList& OR_ParticuleManager::GetParticuleList()
{
	return List_;
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

