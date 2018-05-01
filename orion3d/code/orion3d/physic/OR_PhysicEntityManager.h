
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicEntityManager.h
 *  \brief definition of class OR_PhysicEntityManager
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_PhysicEntityManager_h_
#define __OR_PhysicEntityManager_h_

#include "../configuration/OR_Config.h"
#include "OR_PhysicEntity.h"
#include "../utils/OR_ManagerMap_Template.h"
#include "OR_ForceManager.h"
#include "OR_CollisionManager.h"
#include "OR_JointManager.h"

namespace OR {

#define OR_NBR_MAX_PHYSIC_UPDATES_PER_FRAME 3

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_PhysicEntityManager
 *  \brief  A manager of physic objects.
 *  \author Gabriel Peyré 2001-08-29
 *	
 *	This is the core of the physic engine. Drive all physics computations.
 */ 
/*------------------------------------------------------------------------------*/

/**	Instantiate the base template class :
	This does not create an object. It only forces the generation of all
	of the members of the class. */
#pragma warning( disable : 4231 )
ORION3D_API_TEMPLATE template class ORION3D_API OR_ManagerMap_Template<OR_PhysicEntity>;

class ORION3D_API OR_PhysicEntityManager: public OR_ManagerMap_Template<OR_PhysicEntity>
{

public:
	
	/** the type of EDO solver used by the physic engine */
	enum T_PhysicSolver_Type
	{
		kPhysicSolver_Verlet,
		kPhysicSolver_RK4, 
		kPhysicSolver_Euler
	};

    OR_PhysicEntityManager();
    virtual ~OR_PhysicEntityManager();

	void UpdatePhysics();

	OR_I32 AddElement(OR_PhysicEntity* pNewElement, OR_Bool bCheckCollision=true);

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	static OR_Float	GetTimeStep();
	static void     SetTimeStep(OR_Float rTimeStep);
	void                                        SetSolverType( OR_PhysicEntityManager::T_PhysicSolver_Type SolverType );
	OR_PhysicEntityManager::T_PhysicSolver_Type GetSolverType();

	OR_ForceManager&		GetForceManager();
	OR_CollisionManager&	GetCollisionManager();
	OR_JointManager&		GetJointManager();

	OR_Collider_ABC* GetCollider(OR_PhysicEntity& Entity1, OR_PhysicEntity& Entity2);
    //@}

    //-------------------------------------------------------------------------
    /** \name helpers methods */
    //-------------------------------------------------------------------------
    //@{
	void ResetAccumulators();
	void UpdatePhysics_RK4();
	void UpdatePhysics_Verlet();
	void UpdatePhysics_Euler();
    //@}

private:

    //-------------------------------------------------------------------------
    /** \name time step variables */
    //-------------------------------------------------------------------------
    //@{
	/** fixed delta time between to physic updates */
	static OR_Float rTimeStep_;
	/** the fractional time step that has not been used during last update */
	OR_Float rTimeStepRest_;
	/** time of last update */
	OR_I64 nLastUpdate_;
    //@}
	
	/** the force manager common to all entities */
	OR_ForceManager ForceManager_;

	/** check collision between all pair of object */
	OR_CollisionManager CollisionManager_;

	/** constraint between pair of objects */
	OR_JointManager JointManager_;

	/** the EDO solver used */
	OR_PhysicEntityManager::T_PhysicSolver_Type SolverType_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_PhysicEntityManager.inl"
#endif

#endif // __OR_PhysicEntityManager_h_

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

