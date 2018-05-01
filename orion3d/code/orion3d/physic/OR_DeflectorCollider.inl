/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DeflectorCollider.inl
 *  \brief Inlined methods for \c OR_DeflectorCollider
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
#include "OR_DeflectorCollider.h"

namespace OR {


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider constructor
 *
 *  \param  ParticuleManager the particule manager involved in collision tracking
 *  \param  Deflector the deflector involved in collision tracking
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DeflectorCollider::OR_DeflectorCollider( OR_ParticuleManager& ParticuleManager, OR_Deflector_ABC& Deflector )
:	OR_Collider_ABC(),
	pParticuleManager_	( &ParticuleManager ),
	pDeflector_			( &Deflector )
{
	/* NOTHING */
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider destructor
 *
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_DeflectorCollider::~OR_DeflectorCollider()
{
	/* NOTHING */
}

	

/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::GetParticuleManager
 *
 *  \return the particule manager involved in collision tracking
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_ParticuleManager& OR_DeflectorCollider::GetParticuleManager()
{
	OR_ASSERT( pParticuleManager_!=NULL );
	return *pParticuleManager_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::SetParticuleManager					
 *
 *  \param  ParticuleManager the particule manager involved in collision tracking
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DeflectorCollider::SetParticuleManager(OR_ParticuleManager& ParticuleManager)
{
	pParticuleManager_ = &ParticuleManager;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::GetDeflector
 *
 *  \return the deflector involved in collision tracking
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
OR_Deflector_ABC& OR_DeflectorCollider::GetDeflector()
{
	OR_ASSERT( pDeflector_!=NULL );
	return *pDeflector_;
}


/*------------------------------------------------------------------------------*/
/** 
 * Name : OR_DeflectorCollider::SetDeflector
 *
 *  \param  Deflector the deflector involved in collision tracking
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/
OR_INLINE
void OR_DeflectorCollider::SetDeflector(OR_Deflector_ABC& Deflector)
{
	pDeflector_ = &Deflector;
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

