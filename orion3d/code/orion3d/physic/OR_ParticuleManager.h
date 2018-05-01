/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_ParticuleManager.h
 *  \brief OR_ParticuleManager defintion
 *  \author Gabriel Peyré 2001-07-18
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_ParticuleManager_h_
#define __OR_ParticuleManager_h_

#include "../configuration/OR_Config.h"
#include "OR_Particule.h"
#include "OR_ConstraintManager.h"
#include "OR_Force_ABC.h"
#include "OR_ForceManager.h"
#include "OR_PhysicEntity.h"
#include "../utils/OR_ManagerList_Template.h"

// #define OR_INTEGRATOR_VERLET

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_ParticuleManager
 *  \brief  A manager of particule.
 *  \author Gabriel Peyré 2001-07-18
 *  A manager of particule, with two main features  :
 *		- can update each particule
 *		- can handle 
 *
 *	The \c OR_ParticuleManager can be used either :
 *		- in the scene graph.
 *		- in a OR_PhysicEntityManager.
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerList_Template<OR_Particule>;

class ORION3D_API OR_ParticuleManager: public OR_ManagerList_Template<OR_Particule>, public OR_PhysicEntity
{

public:

	OR_ParticuleManager(OR_ConstraintManager* pConstraintManager=NULL);

    //-------------------------------------------------------------------------
    /** \name Constraints management */
    //-------------------------------------------------------------------------
    //@{
	OR_ConstraintManager* GetConstaintManager();
	void                  SetConstraintManager(OR_ConstraintManager* ConstraintManager);
    //@}

	//-------------------------------------------------------------------------
    /** \name accessor */
    //-------------------------------------------------------------------------
    //@{
	OR_ConstraintManager* GetConstraintManager();
	void                  SetConstraintManager(OR_ConstraintManager& ConstraintManager);
	OR_ForceManager*      GetForceManager();
	void                  SetForceManager(OR_ForceManager& ForceManager);
	T_ParticuleList&      GetParticuleList();
    //@}

    //-------------------------------------------------------------------------
    /** @name helpers */
    //-------------------------------------------------------------------------
    //@{
	void SetParticuleInvMass(OR_Float rInvMass);
    //@}

	//-------------------------------------------------------------------------
    /** \name overload of OR_PhysicEntity methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void UpdatePhysics_RK4( OR_U32 nStepRK4 );
	virtual void UpdatePhysics_Verlet();	
	virtual void UpdatePhysics_Euler();
	virtual OR_PhysicEntity::T_PhysicEntity_Type GetPhysicType();
	virtual void ProcessForce( OR_ForceManager& ForceManager );
	virtual void ResetAccumulators();
    //@}

protected:

	/** the manager of constraints */
	OR_ConstraintManager* pConstraintManager_;
	/** a manager of forces */
	OR_ForceManager* pForceManager_;

};

typedef list<OR_ParticuleManager*>			T_ParticuleManagerList;
typedef T_ParticuleManagerList::iterator	IT_ParticuleManagerList;

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_ParticuleManager.inl"
#endif


#endif // __OR_ParticuleManager_h_

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

