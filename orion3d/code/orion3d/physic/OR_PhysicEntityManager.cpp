/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_PhysicEntityManager.cpp
 *  \brief implementation of class OR_PhysicEntityManager
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_PhysicEntityManager.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_PhysicEntityManager.h"
#include "OR_Deflector_ABC.h"


#ifndef OR_USE_INLINE
	#include "OR_PhysicEntityManager.inl"
#endif

using namespace OR;


OR_Float OR_PhysicEntityManager::rTimeStep_ = 0.03f;

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager constructor
 *
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntityManager::OR_PhysicEntityManager()
:	OR_ManagerMap_Template<OR_PhysicEntity>(false),
	nLastUpdate_	( -1 ),
	rTimeStepRest_	(  0 ),
	SolverType_		( OR_PhysicEntityManager::kPhysicSolver_RK4 )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager destructor
 *
 *  \author Gabriel Peyré 2001-08-29
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntityManager::~OR_PhysicEntityManager()
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::UpdatePhysics
 *
 *  \author Gabriel Peyré 2001-08-29
 *
 *	The main physic engine drivers :
 *		- manage time step decisions (for the moment, try to maintain a constant time step).
 *		- choose the right solver.
 *		- resolve collision (for the RK4, do it only for last step).
 *		- update movement.
 */ 
/*------------------------------------------------------------------------------*/
void OR_PhysicEntityManager::UpdatePhysics()
{
	OR_ASSERT( rTimeStep_>0 );

	/* time computations ********************************************************/
	OR_I64 nCurTime = OR_GetTime();
	
	if( nLastUpdate_<0 )
	{
		/* first update : just set up the time */
		this->ResetAccumulators();
		nLastUpdate_ = nCurTime;
		return;
	}
	
	OR_Float rDeltaT = ((OR_Float) nCurTime - nLastUpdate_)*0.001f + rTimeStepRest_;
	OR_U32	 nNbrUpdate = (OR_U32) (rDeltaT/rTimeStep_);
	rTimeStepRest_ = rDeltaT - nNbrUpdate*rTimeStep_;

	if( nNbrUpdate>OR_NBR_MAX_PHYSIC_UPDATES_PER_FRAME )
		nNbrUpdate = OR_NBR_MAX_PHYSIC_UPDATES_PER_FRAME;

	
	nLastUpdate_=nCurTime;
		

	/* physics computations *****************************************************/
	for( OR_U32 nNumUpdate=0; nNumUpdate<nNbrUpdate; ++nNumUpdate )
	{
		if( SolverType_==OR_PhysicEntityManager::kPhysicSolver_RK4 )
			this->UpdatePhysics_RK4();
		else if( SolverType_==OR_PhysicEntityManager::kPhysicSolver_Verlet )
			this->UpdatePhysics_Verlet();
		else if( SolverType_==OR_PhysicEntityManager::kPhysicSolver_Euler )
			this->UpdatePhysics_Euler();
	}
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_PhysicEntityManager::AddElement
 *
 *  \param  pNewElement the element to add.
 *	\param	bCheckCollision do we need to check collision for this object.
 *	\return the ID of the object.
 *  \author Gabriel Peyré 2001-09-13
 *
 *	Add the element to the manager, and, if it is asked, add the correct collider to
 *	the collision manager.
 */ 
/*------------------------------------------------------------------------------*/
OR_I32 OR_PhysicEntityManager::AddElement(OR_PhysicEntity* pNewElement, OR_Bool bCheckCollision)
{
	OR_ASSERT( pNewElement!=NULL );
	if( bCheckCollision )
	{
		/* add the object to the collision manager */
		CollisionManager_.AddPhysicEntity( *pNewElement );
	}
	
	return OR_ManagerMap_Template<OR_PhysicEntity>::AddElement( pNewElement );
}


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


