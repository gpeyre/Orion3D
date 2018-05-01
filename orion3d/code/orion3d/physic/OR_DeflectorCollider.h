
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DeflectorCollider.h
 *  \brief Definition of class \c OR_DeflectorCollider
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_DeflectorCollider_h_
#define __OR_DeflectorCollider_h_

#include "../configuration/OR_Config.h"
#include "OR_ParticuleManager.h"
#include "OR_PhysicEntity.h"
#include "OR_Deflector_ABC.h"
#include "OR_CollisionManager.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_DeflectorCollider
 *  \brief  Collider between a deflector and a paticule manager.
 *  \author Gabriel Peyré 2001-09-13
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_DeflectorCollider: public OR_Collider_ABC
{

public:

    OR_DeflectorCollider( OR_ParticuleManager& ParticuleManager, OR_Deflector_ABC& Deflector );
    virtual ~OR_DeflectorCollider();

	//-------------------------------------------------------------------------
    /** \name overload of OR_Collider_ABC methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void PerformCollisionDetection( OR_CollisionManager& CollisionManager );
	virtual OR_PhysicEntity& GetCollidee0();
	virtual OR_PhysicEntity& GetCollidee1();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_ParticuleManager&	GetParticuleManager();
	void					SetParticuleManager(OR_ParticuleManager& ParticuleManager);
	OR_Deflector_ABC&		GetDeflector();
	void					SetDeflector(OR_Deflector_ABC& Deflector);
    //@}


private:

	/** the particule manager involved in collision tracking */
	OR_ParticuleManager*	pParticuleManager_;
	/** the deflector involved in collision tracking */
	OR_Deflector_ABC*		pDeflector_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
    #include "OR_DeflectorCollider.inl"
#endif


#endif // __OR_DeflectorCollider_h_

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

