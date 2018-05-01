
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_DampingForce.h
 *  \brief Definition of class OR_DampingForce
 *  \author Gabriel Peyré 2001-08-04
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_DampingForce_h_
#define __OR_DampingForce_h_

#include "../configuration/OR_Config.h"
#include "OR_Force_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_DampingForce
 *  \brief  A viscous damping force (add viscous drag).
 *  \author Gabriel Peyré 2001-08-04
 *
 *	Damping force are opposed to speed via equation : 
 *	\code
 *		F=-Kf*Speed
 *	\endcode
 *	where Kf is the damping coefficient.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_DampingForce: public OR_Force_ABC
{

public:

    OR_DampingForce(OR_Float rDamping=0.1f);
    virtual ~OR_DampingForce();

	//-------------------------------------------------------------------------
    /** @name OR_Force_ABC overload */
    //-------------------------------------------------------------------------
    //@{
    void ProcessParticule(OR_Particule& particule);
	void ProcessObject(OR_RigidBody& handler);
    //@}
	
    //-------------------------------------------------------------------------
    /** @name accessors */
    //-------------------------------------------------------------------------
    //@{
	void  SetDamping(OR_Float rDamping);
	OR_Float GetDamping();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromFile( OR_File& file );
	void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_DampingForce);
    //@}

private:

	/** Damping coefficient */
	OR_Float rDamping_;

};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_DampingForce.inl"
#endif


#endif // __OR_DampingForce_h_

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

