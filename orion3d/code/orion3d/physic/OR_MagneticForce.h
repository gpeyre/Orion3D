
/*------------------------------------------------------------------------------*/
/** 
 *  \file  OR_MagneticForce.h
 *  \brief Definition of class OR_MagneticForce
 *  \author Gabriel Peyré 2001-08-05
 */ 
/*------------------------------------------------------------------------------*/

#ifndef __OR_MagneticForce_h_
#define __OR_MagneticForce_h_

#include "../configuration/OR_Config.h"
#include "OR_Force_ABC.h"

namespace OR {

/*------------------------------------------------------------------------------*/
/** 
 *  \class  OR_MagneticForce
 *  \brief  A magnetic force.
 *  \author Gabriel Peyré 2001-08-05
 *  A magntic force compute by Lorentz law with q=1 :
 *	\code
 *	F=v^B
 *	\endcode
 *	Where B is the magntic field.
 */ 
/*------------------------------------------------------------------------------*/

class ORION3D_API OR_MagneticForce: public OR_Force_ABC
{

public:

    OR_MagneticForce(OR_Vector3D& MagneticField=OR_Vector3D(0,0,0));
    virtual ~OR_MagneticForce();

	//-------------------------------------------------------------------------
    /** @name OR_Force_ABC overload */
    //-------------------------------------------------------------------------
    //@{
    void ProcessParticule(OR_Particule& particule);
	void ProcessObject(OR_RigidBody& obj);
    //@}
	
    //-------------------------------------------------------------------------
    /** @name accessors */
    //-------------------------------------------------------------------------
    //@{
	void  SetMagneticField(OR_Vector3D& MagneticField);
	OR_Vector3D& GetMagneticField();
    //@}
	
    //-------------------------------------------------------------------------
    /** \name serialization methods */
    //-------------------------------------------------------------------------
    //@{
	void BuildFromFile( OR_File& file );
	void BuildToFile( OR_File& file );
	OR_DEFINE_SERIALIZATION(OR_MagneticForce);
    //@}

private:

	/** the magnetic field */
	OR_Vector3D MagneticField_;
};

} // End namespace OR

#ifdef OR_USE_INLINE
	#include "OR_MagneticForce.inl"
#endif


#endif // __OR_MagneticForce_h_

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

