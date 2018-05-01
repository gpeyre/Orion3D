//*****************************************************************************
/// \author Gabriel Peyré 2001-08-31
//*****************************************************************************

#ifndef __OR_Deflector_ABC_h_
#define __OR_Deflector_ABC_h_

#include "../configuration/OR_Config.h"
#include "OR_Particule.h"
#include "OR_RigidBody.h"
#include "OR_PhysicEntity.h"
#include "OR_ParticuleManager.h"

namespace OR {

//=============================================================================
/**
*   @class  OR_Deflector_ABC
*   @brief  Interface class for all deflector.
*
*	A deflector must be able to check for object/particule collision, and, if necessary, 
*	respond to this collision by reflecting the speed of the particule/object.
*
*	Usualy, deflector are put in an OR_PhysicEntityManager, which is responsible for
*	deflecting a whole bunch of particule.
*/
/// \author Gabriel Peyré 2001-08-31
//=============================================================================
class ORION3D_API OR_Deflector_ABC: public OR_PhysicEntity
{

public:

    OR_Deflector_ABC(OR_Float rBounce=0.7f);
    virtual ~OR_Deflector_ABC();

	virtual void DeflectParticuleManager( OR_ParticuleManager& particuleManager ) {}
	virtual void DeflectObject( OR_RigidBody& object ) {}

    //-------------------------------------------------------------------------
    /** @name accessor */
    //-------------------------------------------------------------------------
    //@{
	OR_Float GetDeflectingBounce();
	void  SetDeflectingBounce(OR_Float rBounce);
    //@}

	//-------------------------------------------------------------------------
    /** \name overload of OR_PhysicEntity methods */
    //-------------------------------------------------------------------------
    //@{
	virtual void UpdatePhysics_RK4( OR_U32 nStepRK4 );
	virtual void UpdatePhysics_Verlet();
	virtual void UpdatePhysics_Euler();
	virtual T_PhysicEntity_Type GetPhysicType();
	virtual void ProcessForce( OR_ForceManager& ForceManager );
	virtual void ResetAccumulators();
    //@}


protected:
	
	/** the bounce coeficient of the surface */
	OR_Float rBounce_;

};

typedef list<OR_Deflector_ABC*>		T_DeflectorList;
typedef T_DeflectorList::iterator	IT_DeflectorList;

} // End namespace OR

#ifdef OR_USE_INLINE
#   include "OR_Deflector_ABC.inl"
#endif


#endif // __OR_Deflector_ABC_h_
