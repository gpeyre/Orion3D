/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DampedSpring.h
 *  \brief Definition of class OR_DampedSpring
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_DampedSpring_h_
#define __OR_DampedSpring_h_

#include "../configuration/OR_Config.h"
#include "OR_SpringConstraint.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_DampedSpring
 *  \brief  A spring with a dampling force.
 *  \author Gabriel Peyré 2001-08-04
 *  
 *	A dampling force is a viscous drag force, opposing to the spring movement.
 *
 *	Here is the way to compute the force acting on particule 1 (opposite to the 
 *	force acting on particule 2) :
 *	\code
 *	delta_P = P1 - P2
 *	delta_V = V1 - V2
 *	rDist   = norm(delta_P)
 *	delta_P_normalized = delta_P/rDist
 *	rFactorD = dot(delta_P, delta_V_normalized)*rDampling_	// dampling coef
 *	rFactorS = (rDist - rRestLength_)*rStiffnedd_			// spring coef
 *	force = (rFactorD + rFactorS)*delta_P_normalized
 *	\code
 *
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_DampedSpring: public OR_SpringConstraint
{

public:

    OR_DampedSpring(OR_Float rStiffness_ = 0.005f, OR_Float rLength = 1, OR_Float rDampling=0,
					OR_Particule* pTarget1=NULL,
					OR_Particule* pTarget2=NULL);
    virtual ~OR_DampedSpring();

	//-------------------------------------------------------------------------
    /** @name overload of OR_Constraint_ABC method */
    //-------------------------------------------------------------------------
	//@{
	void Update();
    //@}

    //-------------------------------------------------------------------------
    /** \name accessors */
    //-------------------------------------------------------------------------
    //@{
	OR_Float GetDampling();
	void  SetDampling(OR_Float rDampling);
    //@}

private:

	/** the dampling coefficient */
	OR_Float rDampling_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_DampedSpring.inl"
#endif




#endif // __OR_DampedSpring_h_

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

