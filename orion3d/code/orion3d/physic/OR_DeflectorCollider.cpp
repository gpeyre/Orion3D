/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DeflectorCollider.cpp
 *  \brief Definition of class \c OR_DeflectorCollider
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_DeflectorCollider.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID


#include "../stdafx.h"
#include "OR_DeflectorCollider.h"

#ifndef OR_USE_INLINE
	    #include "OR_DeflectorCollider.inl"
#endif

using namespace OR;


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::PerformCollisionDetection
 *
 *  \param  CollisionManager The manager that store collisions.
 *  \author Gabriel Peyré 2001-09-13
 *
 *	This doesn't use the collision manager, since collision between particule and deflector are
 *	resolved "on the fly" by the deflector.
 */ 
/*------------------------------------------------------------------------------*/
void OR_DeflectorCollider::PerformCollisionDetection( OR_CollisionManager& CollisionManager )
{
	OR_ASSERT( pParticuleManager_!=NULL );
	OR_ASSERT( pDeflector_!=NULL );
	pDeflector_->DeflectParticuleManager( *pParticuleManager_ );
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::GetCollidee0
 *
 *  \return the first collidee.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity& OR_DeflectorCollider::GetCollidee0()
{
	return this->GetDeflector();
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::GetCollidee1
 *
 *  \return the second collidee.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_PhysicEntity& OR_DeflectorCollider::GetCollidee1()
{
	return this->GetParticuleManager();
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

